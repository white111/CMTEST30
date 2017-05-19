#!/usr/bin/perl
################################################################################
#
# Module:      TestStatus.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:       Utility for checking last test status( debug only)
#
# Version:    See Below
#
# Changes:
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
my $Ver= 'v1.1 1/31/2008'; # Updated versioning
my $CVS_Ver = ' [ CVS: $Id: TestStatus.pl,v 1.1 2008/02/20 23:05:33 joe Exp $ ]';
$Version{'TestStatus'} = $Ver . $CVS_Ver;


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
#use Init_Stoke;
#use Stoke2;

my  $Event_Error = 0;
my  $CFG_Error = 0;

my  $Event_Msg = 0;
my  $CFG_Msg = 0;

my  $Status_Msg = 0;
my  $Status_Msg = 0;

&Globals_Stoke();

#our $LogPath          = ($ENV{OS} eq 'Linux') ? "$ENV{HOME}/tmp" : 'C:/Tmp';
our $LogPath          = ($ENV{OS} eq 'Linux') ? "/var/local/cmtest/logs" : 'C:/Tmp';

our $XLog             = $LogPath . '/Yield.log';
our $Test_Log_Source  = 'undef';
#our @TIDs             = ('undef');
#our %UUT_00292 = ('');
our @Exclude          = ('');
our @SN_Masks         = ('');

#&getopts ('E:S:D:') || sub {
#    print "Invalid Arg(s)";
#    exit;
#}
my $Usage = "
    Usage: $0 -S [Serial_Number] -T [TID] -C [ cfg_file_option ] -L [Logpath]\n
      Where:
         -S:     Serial number to search
         -T:     TID to Search
         -C:     TID configuratin file(typically Partnumber configuration
         -h:     Print this screen and exit
         -q:     Quiet mode – allow output redirection
         -L:	 Optional: Logfile path (def: /var/local/cmtest/logs)
         -d:	 Turn on Debug messages
(e.g.)   B3:     Load cfg from ../cfgfiles/Yield_B3.cfg (def:Yield_defaults.cfg)

       [ value 0 = today ]
       [* = WIP feature - not yet implemented / released]
       [# = Deprecated]
";

&getopts ('C:S:T:L:hqd') || &Exit (1, $Usage);

if ($opt_h) {
    print $Usage;
    exit;
}

if ($opt_d) {
    $Debug = 1;
}


if ($opt_S) {
    print ("Entered Serial Number(s): $opt_S\n");

} else {
	print $Usage;
	exit;
}

if ($opt_T) {
    print ("Entered TID: $opt_T\n");

} else {
	print $Usage;
	exit;
}

if ($opt_L) {
    print ("Entered LogPath: $opt_L\n");
    if (-e $opt_L) {
    	$LogPath = $opt_L
    } else {
    	print "Invalid Logpath specified: $opt_L\n";
    	print $Usage;
		exit;
	}
}

my $Cfg = "";
if ($opt_C) {
   if (-e  $PPath . "/uutcfg/" . $opt_C) {
    	print ("Entered Config File: $opt_C\n");
    	$Cfg = $opt_C;
   } else {
   	    print "Invalid Config File specified: $opt_C\n";
    	print $Usage;
		exit;
   }

} else {
	print ("Use Default Config File: UUT_default.cfg\n");
    #my $Cfg = shift;
	$Cfg = 'UUT_default.cfg' if $Cfg eq ''
}


#my $configfile = ($opt_C) unless $opt_C eq '';
my $SetupFile = $PPath . "/uutcfg/" .$Cfg;
my $Erc = &Read_Data_File ($SetupFile) if -f $SetupFile;  #optional, ignore $Erc
my $Msg = "Def setup file\t= $SetupFile";
$Msg .= ' (not found)' if $Erc; $Msg .= "\n";
my $Prev_TID = "";
#$Erc = &Read_Data_File ($SetupFile);
if ($Erc and $Cfg ne 'defaults') {
    &Exit ($Erc, $Msg);
} else {
    $Msg .= "Cfg file\t= $SetupFile\n";
    print "\nTest_Log_Source\t= $LogPath\n" unless $Quiet;
    unless ($Quiet) {
        print "\n\t$Cfg TIDs:\t";
        foreach my $TID (@TIDs) {
            print "$TID  ";
            last if $TID eq $opt_T;
            $Prev_TID = $TID;
        }
        print "\n";
    }
}

print ("our TID Prev TID $Prev_TID\n");


our $Quiet = ($opt_q) ? 1 : 0;



#die "-c not implemented yet" if $opt_c;
die "-i not implemented yet" if $opt_i;

our $Start_Time = [gettimeofday];

                    #open (LOG, ">>$XLog") || die;   close LOG;
our $New_Log = 1;   #Tell &Logs::PrintLog not to try to open it for append
open (LOG, ">$XLog") || die;

&PrintLog ("Starting $0");

#if $Debug {

    print ("Getting CFG info ...\n");

    ($CFG_Error, $CFG_Msg) = &Get_Cfg_entry ($opt_S);
    if ($Event_Error) {
        print "Get_Cfg_entry Returned a $CFG_Error: $CFG_Msg\n";
    } else {
        print "OK\n" unless $Quiet;
    }
    print ("Getting Event info ...\n");
    ($Event_Error, $Event_Msg) = &Get_Event_entry ($opt_S);

    if ($Event_Error) {
        print "Get_Event_entry Returned a $Event_Error: $Event_Msg\n";
    } else {
        print "OK\n" unless $Quiet;
    }

 my  $Event_rec = '';       #&Get_Cfg_entry ($opt_S) ||
if ($Event_Error || $CFG_Error) {
	my @serial_list = split(/\|/, $opt_S);
	print ("my serial list @serial_list\n");
	foreach  (@serial_list) {
	$Erc = ""; $Msg = "";
		print ("Checking Serial: $_ \n");
		($Status_Error, $Status_Msg,$Event_rec) = &Get_Test_status ($_,$opt_T);
		my $time = &PT_Date($Status_Error,0);
		if ($Status_Error && ( $Status_Msg eq 'PASS')) {

    		print "Last Test passed on $time($Status_Error)\n";
		} else {
    		print "Last Test did not pass $time($Status_Error) Test Result: $Status_Msg\n";
    		if ($Event_rec) {
    			print ("$Event_rec\n");
    		}
		}
	}

} else {
    print "No Records found\n" unless $Quiet;
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


