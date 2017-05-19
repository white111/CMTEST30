################################################################################
#
# Module:     Begin.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      SCommon BEGIN block code
#
# Version:    (See below) $Id: Begin.pm,v 1.4 2011/12/12 22:54:28 joe Exp $
#
# Changes:   v1    08/17/05  Made Win_Dev more generic
#                v2    08/21/05  $OS is global
#                v3r2 08/31/05 New schema!
#				 Added hostname to tmp dir for non MFG accounts(Multiple servers logged to same account)
#
# Still ToDo:
#              - Move breaks from main loop to after the stats update
#              - Change <Include> to &   eg &Power
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1993 - 2005 Paul Tindle. All rights reserved.
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
my $Ver= 'v3.3 1/31/2008'; # Updated versioning
my $CVS_Ver = ' [ CVS: $Id: Begin.pm,v 1.4 2011/12/12 22:54:28 joe Exp $ ]';
$Version{'Begin'} = $Ver . $CVS_Ver;
#______________________________________________________________________________
 $| = 1;

 our $OS = ($ENV {'OS'} eq 'Windows_NT') ? 'Win32' : 'Linux';

 my (@Check_Path) = split (/\/|\\/, $0);
 pop @Check_Path;  pop @Check_Path;      # $FN, then 'bin'
 our $PPath = join '/', @Check_Path;   # Now contains our root directory

 our $Cfg_File;
 our $Tmp;

 if ($OS eq 'Win32') {
      $Cfg_File = "$PPath/cfgfiles/testctrl.defaults.cfg";
      $Tmp = $ENV{'TMP'};
#    } elsif ($ENV{'USER'} ne 'mfg') {           # Add 10/4/11 JSW
#      $Cfg_File = '/usr/local/cmtest/testctrl.cfg';
#      $Tmp = "$ENV{'HOME'}/tmp/$ENV{'HOSTNAME'}";
#      print "$Tmp\n";
    } else {
      $Cfg_File = '/usr/local/cmtest/testctrl.cfg';
      $Tmp = "$ENV{'HOME'}/tmp";
 }

 pop @INC;
 unshift @INC, "$PPath/lib";
 unshift @INC, '.';

 our $CmdFilePath = "$PPath/cmdfiles";

 1;
