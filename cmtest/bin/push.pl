#!/usr/bin/perl -I /usr/local/cmtest
################################################################################
#
# Module:      push.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:       Utility to distribute Test Automation code to the various
#           test controllers.  It uses a configuration file [~ptindle/push.cfg, but will use  ]/usr/local/mfgtest/push.cfg
#           that defines destination [hosts], [paths] and [files], and
#           requires a -M to declare the master path to use
#
# Version:    15.1 $Id: push.pl,v 1.4 2008/03/11 18:29:43 joe Exp $
#
# Changes:    13a3  09/13/05 New Begin'ing! Now uses Release_ID instead of Bucket
#           14    11/10/05 Moved code out of PT_Disty::Distr_Files
#           15    11/15/05 Now uses &Copy_Files
#			15.1  Updated versioning
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
# Notes:     The -f and -c options are coded but not yet tested. Should the
#            mount / unmount functions be included, or require the operator
#            to pre-perform them?
################################################################################
my $Ver= 'v15.2 2/25/2008'; # Added Opt_f to cp tftp files only when requested
my $CVS_Ver = ' [ CVS: $Id: push.pl,v 1.4 2008/03/11 18:29:43 joe Exp $ ]';
$Version{'push'} = $Ver . $CVS_Ver;
#_____________________________________________________________________________
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

#use warnings;
use File;
use Getopt::Std qw(:DEFAULT);
use Logs;
use PT;
use PT_Disty;

#_______________________________________________________________
# main:

     &Init_1st;
     my $Usage = "
    Usage: $0 [-dhqsbvx] [-C <Cfg File>] [-F <Out Path>] [-H Host] [-X VSS_Path]\n
      Where:
         -a:     Dist to All hosts listed in cfg file
         -C:     override default cfgfile [SCCS_Path]
         -d:     Debug mode
         -F:     Push to an explicit File system path
         -h:     Print this Help message
         -H:     Push to <Host> only, ignoring [host] list
         -m:	 Check and create paths as needed with a prompt
         -s:     include site Server files
         -b:	 include site Server tftp files(tftpboot)
         -t:     Test only, don't execute
         -v:     Verbose mode (ignored with -q)
         -x:     eXtract files from sccs (VSS) work area first
         -X:     Force -x and use this VSS path

";
            # Process the command line arguments...

    &getopts ('C:F:H:X:adhmqsbtvx') || &Invalid ($Usage);

    &Init ($Usage);  #PT_Disty::Init

    &Exit (101,  "(Invalid switch combination \(no action!\))")
        if  ! $opt_t
        and ! $opt_a
        and ! $opt_x
        and $opt_F eq ''
        and $opt_H eq '';

    &Show_INCs;
    &Mains_Init;
    $Pipe_It = 0;
    &Proceed;
    &Copy_Files;        # PT_Disty:: Copy all files listed in the cfg file

    &Exit (0, "Done!");
#_______________________________________________________________


