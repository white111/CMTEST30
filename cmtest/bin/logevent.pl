#!/usr/bin/perl -I /usr/local/cmtest
################################################################################
#
# Module:      logevent.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      Script to add to event and CFG logs ( not used, Status ???)
#
# Version:    5.1 08/20/05 $Id: logevent.pl,v 1.2 2008/02/20 23:05:33 joe Exp $
#
# Changes:    5 08/20/05  Revised BEGIN block
#			 5.1 Updated versioning
#
# Still ToDo:
#             UID, Data field and LogFilePtr not supported! Yet?
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
#
#__________________________________________________________________________
BEGIN {

    use Begin;

#    my $DChar;
#    our ($Base, $Bin_Path);

#    $OS = ($ENV {'OS'} eq 'Windows_NT') ? 'Win32' : 'Linux';

#    pop @INC;
#    if ($OS eq 'Win32') {
#        unshift @INC, 'C:/dev/lib';
#            $DChar = '\\';
#            $Cfg_File = "C:/dev/bin/test.cfg";
#            $Base = 'U:/lib';
#      } else {
#            $DChar = '/';
#    $Cfg_File = '/usr/local/mfgtest/test.cfg';
#            chop ($Base = `which $0`);
#    }

#    unshift @INC, "$ENV{HOME}${DChar}lib";
#    my (@Seg) = split ($Base); #/$DChar/

#    pop @Seg;        # FileName
#    my ($Sub, $Bucket) = split (/-/, pop @Seg);        # bin-x
#    $Base = join $DChar, @Seg;

#    $Sub = 'lib';
#        $Bin_Path = "$Base/bin";
#        unless ($Bucket eq '') {
#            $Sub .= "-$Bucket";
#            $Bin_Path .= "$Base/bin-$Bucket";
#        }

#        unshift @INC, $Base . $DChar . $Sub;
#        unshift @INC, '.';

#        our $CmdFilePath = $Base . $DChar . 'cmdfiles';
}
#____________________________________________________________________________________

#use warnings;
#use strict;

use File;
use Getopt::Std qw(:DEFAULT);
use Init;
use Logs;
use Stoke;
use PT;

#_______________________________________________________________
# main:

        &Init;

        &Exit ($Erc, "(PN=$PN)") if &Check_PN ($PN);                # Is the PartNo valid?

        &Check_Sys_ID ($SN) if &Check_SN ($SN);                                # Check SN, then if bad check SysID

        &Exit ($Erc, "(SN=$SN)") if $Erc;                                        # Is the SerialNo valid?

        print "Writing new EventLog record ... " unless $Quiet;        # OK, do it
        &Log_Event ('', $PN, $SN, $TID, $Result, '');
        &Exit (0, "done!");
#_____________________________________________________________________________
sub Init {

                #Globals:

        $Erc = 0;        # Error code ( non-zero denotes an error occurred )
        $PN = '';        # Part No
        $Result = '';
        $SN = '';        # Serial No
        $TID = '';        # Test ID

        &Init_All;        # <- Init::Init_All

        print "\n";

    my $Usage = "
    Usage: $0 [-dhq] -P <Part No> -R <Result> -S <Serial No> -T <TestID>\n
      Where:
         -d:     Debug mode
         -h:     Print this message
         -q:     Quiet mode
         -P:     <Part No>
         -R:     <Result>
         -S:     <Serial No>
         -T:     <TestID>

";

                #Just to keep warnings quiet!:

        $opt_d = 0;
        $opt_h = 0;
        $opt_q = 0;
        $opt_P = '';
        $opt_R = '';
        $opt_S = '';
        $opt_T = '';

        $Erc = 101;

                # Process the command line arguments...

        &getopts ('P:R:S:T:dhq') || &Invalid ($Usage);

    $Debug = 1 if $opt_d;
    $Quiet = 1 if $opt_q;

    if ($opt_h) {
                print "$Usage\n";
                exit (0);
    }

                # Check that everythings cool...!

        $Erc = 102;

        $TID = ($opt_T eq '') ? &Invalid ("TestID required!\n$Usage") :        uc $opt_T;
        $PN = ($opt_P eq '') ? &Invalid ("Part No required!\n$Usage") :        uc $opt_P;
        $SN = ($opt_S eq '') ? &Invalid ("Serial No required!\n$Usage") : uc $opt_S;
        $Result = ($opt_R eq '') ? &Invalid ("Result required!\n$Usage") :        uc $opt_R;

        &Exit (103, "(Result=$Result)") unless ($Result =~ /^PASS$|^FAIL$/);

        $Erc = 0;
}
#_______________________________________________________________

