#!/usr/bin/perl
################################################################################
#
# Module:      abort.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      Standalone utility to create the abort flag to stop a test cleanly
#
# Version:    4.1 $Id: abort.pl,v 1.3 2008/02/20 23:05:33 joe Exp $
#
# Changes:   4   10/10/05  Now v2 Begin
#			 4.1 Updated Versioning
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
#__________________________________________________________________________
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

#_______________________________________________________________

use warnings;

#use File;
#use Getopt::Std qw(:DEFAULT);
#use Init;
#use Logs;
use PT;

#_______________________________________________________________
# main:

my ($Session) = shift;

if ( $Session eq '' ) {
    print $Bell, "No session specified ... Aborting (this!)\n";
    exit(0);
}

&Init;
$Stats{'Session'} = $Session;

unless ( &Abort('run_check') ) {
    print $Bell, "Session doesn't appear to be running ... Aborting (this!)\n";
    exit(0);
}

&Abort('set');

print
"Session $Stats{'Session'} on $Stats{'Host_ID'} will abort before next command\n";
exit 0;

#_____________________________________________________________________________
sub Init {

    #Globals:

    $Bell       = "";
    $Stats_Path = '/var/local/cmtest/stats';
    %Stats      = (
      Host_ID => $ENV{HOSTNAME},                # HostID for logging purposes
      Session => '' );

    $Erc = 0;    # Error code ( non-zero denotes an error occurred )

    #        &Init_All (1);
    #        &Init_Also (1);

}

#_______________________________________________________________
