#!/usr/bin/perl
################################################################################
#
# Module:      power.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      Temp test platform (depreciated)
#
# Version:    1.1 $Id: power.pl,v 1.2 2008/02/20 23:05:33 joe Exp $
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
# Notes:     powerswitch.pl is used by cmtest.pl
################################################################################
my $Version =    'v1.0.2 - 2005-11-05';

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

print "\n\nStarting $0 version $Version\n\t\$PPath=$PPath\n\n";

use Cwd qw( abs_path );
use Getopt::Std qw(:DEFAULT);

use Init;
use Power;
use PT;


#use File;
#use Logs;
#use PT;

################################################################################
# Globals:

my $Action  = shift;
my $Session = shift;

$Util_Only = 1;
&Init_All;
$XLog = "/home/ptindle/tmp/power.log";
$Stats{'Session'} = $Session;
&Print_Log(11, "### Starting power.pl: ($Power_type) $Action $Session");

if ($Action eq '') {
    $Stats{'Session'} = 0; # Show all
    my $State;
    while (1) {
       system 'clear';
       print "\n" . localtime() . "\n\n";
       $Erc =  &Power ('status');
       die "\&Power died with Erc=$Erc" if $Erc;
       sleep 4;
    }
} else {
    $Erc = &Power ($Action);
    print "Exited with Erc=$Erc" if $Erc;
}


#_______________________________________________________________________________





