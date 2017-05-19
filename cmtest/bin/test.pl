#!/usr/bin/perl
################################################################################
#
# Module:      test.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:       Temp test platform
#
# Version:    1.1 $Id: test.pl,v 1.2 2008/02/20 23:05:33 joe Exp $
#
# Changes:    1 Sept-18
#			  1.1 Updated versioning
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
    unshift @INC, "$ENV{'LIB'}/lib";
        unshift @INC, '.';

    our $CmdFilePath = "$PPath/cmdfiles";
}

print "\n\t\$PPath=$PPath\n\n";

use Cwd qw( abs_path );
use Getopt::Std qw(:DEFAULT);
#use Sys::PortIO;
use Device::ParallelPort;
#use Device::ParallelPort::drv::parport;
use Power;

#use File;
#use Logs;
#use PT;

################################################################################
# Globals:

my $State = "Off";;
while (1) {
    $State = ($State eq 'Off') ? 'On' : 'Off';
    print "Current State is " . &LPT_Power (8, 'Show') . "\n";
    &LPT_Power (8, $State);
    sleep 2;
}
exit;




