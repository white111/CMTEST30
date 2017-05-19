#!/usr/bin/perl -I /var/local/cmtest/dist/lib
################################################################################
#
# Module:      settestenv.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:       tility to set release pip
#
# Version:    5.2 $Id: settestenv.pl,v 1.3 2008/02/20 23:05:33 joe Exp $
#
# Changes:    Updated versioning
#			  Release 2005-11-17
#			  Changed to allow 10 pipes (k) jsw 3/20/12
#
#
# Still ToDo:
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
BEGIN { # 2005-10-27 v3

    our $OS = ($ENV {'OS'} eq 'Windows_NT') ? 'Win32' : 'Linux';

    my (@Check_Path) = split (/\/|\\/, $0);
    pop @Check_Path;  pop @Check_Path;      # $FN, then 'bin'
    our $PPath = join '/', @Check_Path;   # Now contains our root directory
        $PPath = '..' if $PPath eq '';      # for a $0 of ./
    our $Cfg_File;
    our $Tmp;

    if ($OS eq 'Win32') {
         die "win32: NFW";
    } else {
         $Cfg_File = '/usr/local/cmtest/testctrl.cfg';
         $Tmp = "/tmp";
    }

    pop @INC;
    unshift @INC, "$PPath/lib";
#    unshift @INC, "$ENV{'LIB'}/lib";
    unshift @INC, '.';

    our $CmdFilePath = "$PPath/cmdfiles";
}
#_______________________________________________________________________________
$|=1;

use PT;
#use Getopt::Std qw(:DEFAULT);
my $Arg             = $ARGV[0];
my $Arg2             = $ARGV[1];
my $Local_Cfg       = '/usr/local/cmtest/.cmtestrc';
my $Local_Cfg_Saved = $Local_Cfg . '__saved';
my $NewPR_Cfg       = '/var/local/cmtest/dist/cfgfiles/.cmtestrc';
my $Max_Pipe        = 'k';
my $debug=			0;
our $TmpFile        = '/tmp/bash.tmp';

my $Pipe = $ENV{'CmTest_Release_Pipe'};   # What its currently set to
our $CmTest_Prod_Pipe;                    # the predefined production release

my $Erc = &Read_Cfg_File ($Local_Cfg) if -f $Local_Cfg;
$CmTest_Prod_Pipe =~ s/\'//g; # $CmTest_Prod_Pipe is now set from .cmtesrc

our $Usage = "
    Usage: ste [ + | - | -h | -d | -pr | -rb | -t ]
      Where:
            +  = Step FORWARD 1 release step
            -  = Step BACK 1 release step
           -d  = debug
           -h  = print this message
           -sr = Jump to new release(a-k)
           -pr = Set new release to production \(permenantly\!\)
           -rb = Return to previous release \(permenantly\!\)
           -t  = Test run \(temporarily\) from new release!\)
";

if ($Arg eq '-d') {
  	$debug=1;
  	print "Debugmode\n" if $debug;
  	print " Max Pipe $Max_Pipe \n" if debug;
}

if ($Arg eq '-h' or
    $Arg eq '--help') {
      print "$Usage\n\n";
      exit;
}

if ($Pipe eq '') {
    print "Current production pipe not defined! Exiting...\n";
    exit;
}

if ($Arg eq '') {
    print "\n\tTestEnv set to \'Production' release (pipe $Pipe)\n\n";
    if ($Pipe eq $CmTest_Prod_Pipe) {
        exit;
    } else {
        $Pipe = $CmTest_Prod_Pipe;
    }
}
elsif ($Arg eq '+') {
    if ($Pipe eq $Max_Pipe) {
        $Pipe = 'a';
    } else {
        $Pipe++;
    }
    print "\n\tTestEnv set to \'Pilot'  release (pipe $Pipe)\n\n";
}
elsif ($Arg eq '-sr') {
    if ($Pipe > $Max_Pipe) {
        print "\n\tTestEnv set to pipe $Pipe not valid, exiting without change..\n\n";
        exit;
    } else {
        $Pipe = $Arg2;
    }
    print "\n\tFound Arg $Arg2 TestEnv set to release (pipe $Pipe)\n\n";
}
elsif ($Arg eq '-') {
    if ($Pipe eq 'a') {
        $Pipe = $Max_Pipe;
    } else {
        my $AS = ord ($Pipe);
        $AS--;
        $Pipe = chr ($AS);
    }
    print "\n\tTestEnv set to \'Previous'  release (pipe $Pipe)\n\n";
}
elsif ($Arg eq '-pr') {

    die "This may only be performed by a super-user!"
        if $> != 0;

    `mv $Local_Cfg $Local_Cfg_Saved` unless -f $Local_Cfg_Saved;
    `cp -p $NewPR_Cfg $Local_Cfg`;
    print "\n\tTestEnv switch to new release\n\n";
    exit;

}
elsif ($Arg eq '-rb') {

    die "This may only be performed by a super-user!"
        if $> != 0;

    `mv $Local_Cfg_Saved $Local_Cfg` if -f $Local_Cfg_Saved;
    print "\n\tTestEnv rolled back to prior release\n\n";
    exit;
}
elsif ($Arg eq '-t') {

    `cp -p $NewPR_Cfg $TmpFile`;
    print "\n\tTestEnv set for proto testing\n\n";
    exit;
}
else
{
    printf "\n";
    die "Unknown switch $Arg\n$Usage\n";
    exit;
}

&Set ($Pipe);
exit;

#_______________________________________________________________________________
sub Set {

    my ($New_Pipe) = @_;

    open IN,  "<$Local_Cfg" || die "Can\'t open .cmtestrc file $$Local_Cfg";
    open OUT, ">$TmpFile"   || die "Can\'t open tmp file $TmpFile";

    while (<IN>) {
        if (/^CmTest_Release_Pipe=/) {
            print OUT  "CmTest_Release_Pipe=\'$New_Pipe\'\n";
        } elsif (/^# .cmtestrc/) {
            print OUT  "# .cmtestrc - Created by $0 - " . localtime() . "\n";
        } else {
            print OUT $_;
        }
    }
    close OUT;
    close IN;

    system "chmod 777 $TmpFile" || die 'Can\'t chmod tmp file';
}
#_______________________________________________________________________________


