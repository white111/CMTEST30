#!/usr/bin/perl
################################################################################
#
# Module:      yield.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      cmtest event log yield analyser
#
# Version:    3.1 $Id: yield.pl,v 1.2 2008/02/20 23:05:33 joe Exp $
#
# Changes:   v1 2006-06-14 Uses ../cfgfiles/yield_<x>.cfg where <x> is
#                               unqualified arg. No getopts support yet
#                v2 2006-06-27 Added getopts support, usage, etc
#                v3 2006-07-20 default to current date for date args
#
# Still ToDo:
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1995 - 2005 Paul Tindle. All rights reserved.
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################

$| = 1;

BEGIN { # 2005-09-12 v2

    our $OS = ($ENV {'OS'} eq 'Windows_NT') ? 'Win32' : 'Linux';

    my (@Check_Path) = split (/\/|\\/, $0);
    pop @Check_Path;  pop @Check_Path;      # $FN, then 'bin'
    our $PPath = join '/', @Check_Path;   # Now contains our root directory
        $PPath = '..' if $PPath eq '';      # for a $0 of ./
    our $Cfg_File;
    our $Tmp;

    if ($OS eq 'Win32') {
         $Cfg_File = "$PPath/cfgfiles/testctrl.defaults.cfg";
         $Tmp = $ENV{'TMP'};
    } else {
         $Cfg_File = '/usr/local/cmtest/testctrl.cfg';
         $Tmp = "$ENV{'HOME'}/tmp";
    }

    pop @INC;
    unshift @INC, "$PPath/lib";
#    unshift @INC, "$ENV{'LIB'}/lib";
    unshift @INC, '.';

    our $CmdFilePath = "$PPath/cmdfiles";
}

#print "\n\t\$PPath=$PPath\n\n";

use Cwd qw( abs_path );
use Getopt::Std qw(:DEFAULT);
use Time::HiRes qw(gettimeofday usleep tv_interval);
use Time::Local;


################################################################################

use Init;
use PT;
#use Stats;
use Logs;

our $LogPath          = ($ENV{OS} eq 'Linux') ? "$ENV{HOME}/tmp" : 'C:/Tmp';
our $XLog             = $LogPath . '/Yield.log';
our $Test_Log_Source  = 'undef';
our @TIDs             = ('undef');
our @Test_Results_1st = ( 0, 0, 0 ); # PASS FAIL TOTAL
our @Test_Results_All = ( 0, 0, 0 );
our @Exclude          = ('');
our @SN_Masks         = ('');

#&getopts ('E:S:D:') || sub {
#    print "Invalid Arg(s)";
#    exit;
#}
my $Usage = "
    Usage: $0 [-d] [-B Begin_Date] [ -D Duration ][ -E End_date ] [ cfg_file_option ]\n
      Where:
         -B:     Begin Date ( DD | MM/DD | MM/DD/YY[YY] ) [1969]
         -c:    *Recurse through cfg records
         -d:     Debug mode
         -D:     Duration ( n[s] | nD | nW | nM )          [All]
         -E:     End Date ( DD | MM/DD | MM/DD/YY)    [Today]
         -h:     Print this screen and exit
         -i:    *Recurse each TID separately
         -q:     Quiet mode – allow output redirection
         -T:     TID (overrides any cfg file definitions)
(e.g.)   B3:     Load cfg from ../cfgfiles/Yield_B3.cfg (def:Yield_defaults.cfg)

       [ value 0 = today ]
       [* = WIP feature - not yet implemented / released]
       [# = Deprecated]
";

&getopts ('B:D:E:T:cdhiq') || &Exit (1, $Usage);

if ($opt_h) {
    print $Usage;
    exit;
}

our $Quiet = ($opt_q) ? 1 : 0;

my $Cfg = shift;
$Cfg = 'defaults' if $Cfg eq '';

#die "-c not implemented yet" if $opt_c;
die "-i not implemented yet" if $opt_i;

our $Start_Time = [gettimeofday];

                    #open (LOG, ">>$XLog") || die;   close LOG;
our $New_Log = 1;   #Tell &Logs::PrintLog not to try to open it for append
open (LOG, ">$XLog") || die;

&PrintLog ("Starting $0");

our $SetupFile = $PPath . "/cfgfiles/Yield_defs.cfg";
my $Erc = &Read_Data_File ($SetupFile) if -f $SetupFile;  #optional, ignore $Erc
my $Msg = "Def setup file\t= $SetupFile";
$Msg .= ' (not found)' if $Erc; $Msg .= "\n";

$SetupFile = $PPath . "/cfgfiles/Yield_$Cfg.cfg";
$Erc = &Read_Data_File ($SetupFile);

@TIDs = ($opt_T) unless $opt_T eq '';

if ($Erc and $Cfg ne 'defaults') {
    &Exit ($Erc, $Msg);
} else {
    $Msg .= "Cfg file\t= $SetupFile\n";
    print "\nTest_Log_Source\t= $Test_Log_Source\n$Msg\n" unless $Quiet;
    unless ($Quiet) {
        print "\n\tTIDs:\t";
        foreach my $TID (@TIDs) {
            print "$TID  ";
        }
        print "\n";
    }
}

$Msg = 'Duration = ';

our $Duration = 0;
our $Beg_Time = 0;
our $End_Time = 0;
our $Debug = ($opt_d) ? 1 : 0;

if ($opt_D eq '') {
    $Msg .= '<undef>, ';
} else {
    if ($opt_D =~ /(\d+)(\D+)/) {      # num / non-num
        $Duration = $1;
        my $Dim = lc $2;
        if ($Dim eq 'h') {
            $Duration = $Duration * 60 * 60;
        } elsif ($Dim eq 'd') {
            $Duration = $Duration * 60 * 60 * 24;
        } elsif ($Dim eq 'w') {
            $Duration = $Duration * 60 * 60 * 24 * 7;
        } elsif ($Dim eq 'm') {
            $Duration = $Duration * 60 * 60 * 24 * 365 / 12;
        } elsif ($Dim eq 'y') {
            $Duration = $Duration * 60 * 60 * 24 * 365;
        }
    } else {
        $Duration = $opt_D;
    }
    $Msg .= "$opt_D ( $Duration secs )";
}

# If these were defined in either cfg file, they'll be over-written here...
$Beg_Time = &Get_Time ($opt_B) unless $opt_B eq '';
$End_Time = &Get_Time ($opt_E) unless $opt_E eq '';

if ($Duration) {
    if (!$Beg_Time) {
        if (!$End_Time){
#             &PrintLog ("No Time args!");
             $End_Time = time;
        }
        $Beg_Time = $End_Time - $Duration;
    } elsif (!$End_Time) {
        $End_Time = $Beg_Time + $Duration
    }
} elsif (!$End_Time) {
       $End_Time = time;
}
$Msg .= "\tStart = $Beg_Time, End = $End_Time, Delta = " . int ($End_Time - $Beg_Time);
print $Msg if $Debug; $Msg = '';

print "\n\tDates:\t" . &PT_Date ($Beg_Time, 8) .
      ' - ' .  &PT_Date ($End_Time, 8) . "\n\n" unless $Quiet;

($Erc, $Msg) = &Yield ();

if ($Erc) {
    print "Returned a $Erc: $Msg\n";
} else {
    print "OK\n" unless $Quiet;
}

exit;

#_______________________________________________________________________________
sub Exit {

    my ($Erc, $Msg) = @_;
    print "Exiting with Erc = $Erc \"$Msg\"\n";
    exit;
}

#_______________________________________________________________________________
sub Get_Time {      # Takes a date string as an arg and returns the time int
                    #  corresponding to midnight on that date

    my ($Str) = @_;
    my ($mon,$mday,$year);

    return (time) if $Str eq '0';
    #!!! Get current mth and year here!
    my $year = 6;                         # <- change this before 2007!
    my $mon  = 7;                         # <- change this before Aug 06!

    if ($Str =~ /(\d+)\/(\d+)\/(\d+)/) {
        ($mon,$mday,$year) = ($1,$2,$3);
    } elsif ($Str =~ /(\d+)\/(\d+)/) {
        ($mon,$mday) = ($1,$2);
    } elsif ($Str =~ /(\d+)/) {
         $mday = $1;
    } else {
        return (0);
        return (time);
    }
    $year += 2000 unless $year > 1999;

#    timelocal($sec,$min,$hour,$mday,$mon,$year);
    return (timelocal(0,0,0,$mday,$mon-1,$year));
}

#_______________________________________________________________________________
sub Log_eTime {

    my ($Msg) = @_;
    $Msg = 'ETime' if $Msg eq '';

    &PrintLog ("\t\t\t\t$Msg: " . tv_interval ($Start_Time) . ' secs');

}

#_______________________________________________________________________________
sub PrintLog {

    my $Erc = &Print2XLog (@_); #($Msg, $DontPrint2Screen, $NoNewLine, $TagAsError)
    if ($Erc) {
        print "PrintLog failed with Erc = $Erc \( \$XLog = '$XLog' \)\n";
        exit;
    }

}  # Logs.pm

#_______________________________________________________________________________
sub Yield {

    my %Unit = ();  # Tags each ProductID
    my %TID_List = ();

    if ($opt_c) {
#    if (1) {
        my $File = "$Test_Log_Source/Cfg.log";
        &PrintLog("Opening cfg log $File");
        open (CFG, "<$File") or die "Can\'t open Cfg log \'$File\'";
    }

#1;1141946601;SMV;mfg-svr1;joe;00292-02 Rev 01;0020128050000001;Bench;FAIL;ATT=743,ERC=0,TEC=4,TID=Bench,TOLF=1141946716,TSLF=633,TTF=34,TTT=748,Ver=1.5.2;0020128050000001-20060309.152321.xml;
#1;1141947392;SMV;mfg-svr1;joe;;;IST;FAIL;ATT=171,ERC=0,TEC=6,TID=IST,TOLF=1141947566,TSLF=0,TTF=34,TTT=174,Ver=1.5.2;;

    $File = "$Test_Log_Source/Event.log";
    open (FH, "<$File") or die "Can\'t open Event log \'$File\'";

        # 0 1    2        3      4    5       6         7      8      9    10
        # 1;Date;Location;HostID;OpID;Part_No;Serial_No;TestID;Result;Data;LogFilePtr;

    my $i    = 0;
    my $j    = 0;
    my $NoSN = 0;

    while (<FH>) {

        &PrintLog ("\t*** \&Yield ***\tRead Event Log line $.", 1);
        my $Msg = '';

        $i++;
        my ($RecType, $Date, $Location, $HostID, $OpID, $PN, $SN,
            $TestID, $Result, $Data, $LogFileP) = split (/\;/);

        if ($RecType != 1) {
            &PrintLog ("Event log line $. not recognized!");
            next
        }

        my $Version = '';
        my $Var_Val;
#        $Msg = "$Data\n";
        foreach $Var_Val (split /,/, $Data) {
#            $Msg .= "Var_Val = $Var_Val";
            my ($Var, $Val) = split /=/, $Var_Val;
#            $Msg .= ", Var = $Var, Val = $Val";
#            my ($Which, $Ver) = split /_/, $Var;
#            ($Val) = split /---/, $Val if $Which eq 'Diag';
#            $Msg .= ", Which = $Which, Ver = $Ver";
#            $Version = "$Which=$Val" if $Ver eq 'Ver';
        }

        $TID_List{$TestID} = 1;
        if ($SN eq '') {
            &PrintLog ("Event log line $. has no SN!",1);
            $NoSN++;
            next;
        }

        my $OK = 0;
        my @Parts = ();

        foreach my $TID (@TIDs) {

                $OK = 1 if $TestID eq $TID;
        }
        next unless $OK;

        $OK = 0 if $Date < $Beg_Time;
        $OK = 0 if $Date > $End_Time;

        if ($OK) {

            $j++;

            if ($opt_c) {
                ( @Parts ) = &Get_Cfg_Recs ($Date, $Location, $HostID,
                                                   $SN, @SN_Masks);
            }

            push @Parts, $SN;    # Add the parent to this list
                                 #  so we'll have at least 1


            #            @Test_Results_1st = ( 0, 0, 0 ); # PASS FAIL TOTAL

            foreach $SN ( @Parts ) {
                if ($Result eq 'PASS') {
                    $Test_Results_1st[0] ++ if !defined $Unit{$SN};
                    $Test_Results_All[0] ++;
                } elsif ($Result eq 'FAIL') {
                    $Test_Results_1st[1] ++ if !defined $Unit{$SN};
                    $Test_Results_All[1] ++;
                }
                $Test_Results_1st[2] ++ if !defined $Unit{$SN};
                $Test_Results_All[2] ++;
                $Unit{$SN} = 1;
            }
        }
     }
    close FH;
    close CFG if $opt_c;
    &Log_eTime;

    if ($Debug) {
        print "$j out of $i recs matched (No SN = $NoSN)\n";
        $i = 0;
        print "TIDs found:\n\n";
        foreach my $TID (sort keys %TID_List ) {
            print "\t$TID\n";
            $i++;
        }
        print "<end> [$i recs]\n\n";
        print "Serial Nos matched:\n\n";
        $i = 0;
        foreach my $SN (sort keys %Unit ) {
            print "\t$SN\n";
            $i++;
        }
       print "<end> [$i recs]\n\n";
     }
    my @Desc = qw ( Pass Fail Total );
    print "\n\tResult\t1st\tAll\n",
          "\t______\t_____\t_____\n";
    foreach (0..2) {
        print "\t", $Desc[$_], "\t",
              $Test_Results_1st [$_], "\t",
              $Test_Results_All [$_], "\n"
    }
    my $Yield = ($Test_Results_1st[2]) ?
                int $Test_Results_1st[0]/$Test_Results_1st[2]*100
                : '-';
    print "\tYield\t$Yield %\t";
    $Yield =  ($Test_Results_All[2]) ?
                int $Test_Results_All[0]/$Test_Results_All[2]*100
                : '-';
    print "$Yield %\n";
    &Log_eTime;

    return ($Erc, $Msg);
}
#_______________________________________________________________________________


