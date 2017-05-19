#!/usr/bin/perl -I /usr/local/cmtest
################################################################################
#
# Module:      console.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      Script to interact with a serial or telnet connection
#
# Version:    10.1 $Id: console.pl,v 1.2 2008/02/20 23:05:33 joe Exp $
#
# Changes:    10   08/17/05  Converted
#			 10.1 Updated versioning
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
BEGIN { use Begin; }

#use warnings;

use Connect;
use File;
use Getopt::Std qw(:DEFAULT);
use Init;
use Logs;
use Stoke;
use PT;

#_______________________________________________________________
# main:

        &Init;

        &Cmd_Expect ($Connect, $Port, $Cmd_File);

        my ($RunTime) = time - $Stats{'TimeStamp'};

        &Exit (0, "done ($RunTime secs)");

#_____________________________________________________________________________
sub Init {

        #Globals:

        $Connect = 'Serial';
        $Port = '0';

        &Init_All (0);                                # <- Init::Init_All

        print "\n" unless $Quiet;

    our $Usage = "
    Usage: $0 [-dhqv] -C <Cmd_File> [-O <OutFile>]
                     [-S <serial port> | -T <IP_Addr>]
                     [-Z <Session>]
      Where:
         -d:     Debug mode
         -h:     Print this message
         -q:     Quiet mode
         -v:     Verbose mode (ignored with -q)
         -C:     <Cmd_File>
         -O:     <Out_File> (default: ~/tmp/cmtest.out)
         -S:     Serial <port> to use (default: S0 (comm1))
         -T:     Telnet <IP_Address>
         -Z:     Session no [Default: first available from 1 ]

";

        $Erc = 101;

                # Process the command line arguments...

        &getopts ('C:O:S:T:Z:dhqv') || &Invalid ($Usage);

        $Erc = 0;

        &Init_Also (0);

                # Check that everythings cool...!

        &Exit (26, "No Cmd file specified") if $opt_C eq '';

        $Cmd_File = $opt_C;
        if (! -f $Cmd_File) {
                $Cmd_File = "$CmdFilePath/$Cmd_File";
        }

        &Exit (27, "Can't find Cmd File $opt_C") if ! -f $Cmd_File;

        &Exit (106, "Both -S & -T switches used") if
                $opt_S ne '' and $opt_T ne '';

        if ($opt_S ne '') {
                $Connect = 'Serial';
                $Port = $opt_S;
        }

        if ($opt_T ne '') {
                $Connect = 'Telnet';
                $Port = $opt_T;
        }

}

#____________________________________________________________________________________
