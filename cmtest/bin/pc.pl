#!/usr/bin/perl
################################################################################
#
# Module:      pc.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      cmtest event log SN/TID process checker
#				 > pc.pl [-dq] <SN> <TID>
#				 Returns: 0, "<Last Rec>" where Result = 'PASS'
#						  1, "<Last Rec>" where Result = 'FAIL'
#						  2, "" where no records found in either Event Log
#							          or any related via cfg log
#
# Version:    v0.1 2006-07-25 $Id: pc.pl,v 1.2 2008/02/20 23:05:33 joe Exp $
#
# Changes:    Cloned from yield.pl, and used for
#								   common &CFG_Events sub
#			  1/31/08 Depreciated, use TestStatus.pl
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
our $Start_Time = [gettimeofday];

#use Init;
use DataFile;
#use Stats;
use Logs;
use PT;

#&Init_All (1);

our $LogPath          = ($OS eq 'Linux') ? "$ENV{HOME}/tmp" : 'C:/Tmp';
our $XLog             = $LogPath . '/pc.log';
our $Test_Log_Source  = 'undef';
our @TIDs             = ('undef');
our @Test_Results_1st = ( 0, 0, 0 ); # PASS FAIL TOTAL
our @Test_Results_All = ( 0, 0, 0 );
our @Exclude          = ('');
our @SN_Masks         = ('');
our $Line_No_Cfg_Log  = 0;
#&getopts ('E:S:D:') || sub {
#    print "Invalid Arg(s)";
#    exit;
#}
my $Usage = "
    Usage: $0 [-dq] <Serial_No> [ <TID> ]
      Where:
         -d:     Debug mode
         -h:     Print this screen and exit
         -q:     Quiet mode – allow output redirection
(e.g.)   B3:     Load cfg from ../cfgfiles/Yield_B3.cfg (def:Yield_defaults.cfg)

       [ value 0 = today ]
       [* = WIP feature - not yet implemented / released]
       [# = Deprecated]
";

our ($opt_d, $opt_h, $opt_q);

&getopts ('dhq') || &Exit (1, $Usage);

if ($opt_h) {
    print $Usage;
    exit;
}

our $Quiet = ($opt_q) ? 1 : 0;
our $Debug = ($opt_d) ? 1 : 0;

our $SN = shift;
my $TID = shift;
&Exit (11, "No SN defined") if $SN eq '';
&Exit (12, "Unrecognized SN format") if length $SN != 16;
&Exit (13, "No TID defined") if $TID eq '';
@TIDs = ($TID);  # Allows us to share the &GFG_Events

our $Beg_Time = 0;  #No time constraints
our $End_Time = time;

                    #open (LOG, ">>$XLog") || die;   close LOG;
our $New_Log = 1;   #Tell &Logs::PrintLog not to try to open it for append
open (LOG, ">$XLog") || die;

&PrintLog ("Starting $0");

my $Erc = &Read_Data_File ($Cfg_File);  #normal cmtest cfgfile
$LogPath = 'X:/NAS-2/NAS/Tmp\cmtest.d\/Log_arc/logs-2006-07-30'
     unless $OS eq 'Linux';

      #### Call to main procedure ...
@SN_Masks = ($SN);
($Erc, $Msg) = &Cfg_Events ($LogPath, 1);

if ($Erc) {
    print "Returned a $Erc: $Msg\n";
} else {
    print "Last rec for SN: $SN  PASSED: TID: $TID:\n\n\t$Msg\nOK\n" unless $Quiet;
}

exit;

# All cloned (maybe updates) from yield.pl. Only one may prevail!

#_______________________________________________________________________________
sub Exit {

    my ($Erc, $Msg) = @_;
    print "Exiting with Erc = $Erc \"$Msg\"\n" unless $Quiet;
    exit;
}

#_______________________________________________________________________________
sub Get_Time {      # Takes a date string as an arg and returns the time int
                    #  corresponding to midnight on that date

    my ($Str) = @_;
    my ($mon,$mday,$year);

    return (time) if $Str eq '0';
    #!!! Get current mth and year here!
    $year = 6;                         # <- change this before 2007!
    $mon  = 7;                         # <- change this before Aug 06!

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


