#!/usr/bin/perl
################################################################################
#
# Module:      chkrel.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      'Check Release' - Run a showdiffs on the push.cfg list
#
# Version:    5.1 $Id: chkrel.pl,v 1.3 2008/02/20 23:05:33 joe Exp $
#
# Changes:   v5 - 2005-11-16 New BEGINing
#			 5.1 Updated Versioning
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

BEGIN { # Disty 2005-11-16 v3

    our $OS = ($ENV {'OS'} eq 'Windows_NT') ? 'Win32' : 'Linux';

    my (@Check_Path) = split (/\/|\\/, $0);
    pop @Check_Path;  pop @Check_Path;      # $FN, then 'bin'
    our $PPath = join '/', @Check_Path;   # Now contains our root directory
        $PPath = '..' if $PPath eq '';      # for a $0 of ./

    our $Tmp;

    if ($OS eq 'Win32') {
        die "Nah!";
         $Tmp = $ENV{'TMP'};
    } else {
         $Tmp = "$ENV{'HOME'}/tmp";
    }

    pop @INC;
    unshift @INC, "$PPath/lib";
    unshift @INC, "$ENV{'LIB'}/lib";
    unshift @INC, '.';

}

print "\n\t\$PPath=$PPath\n\n";

use Cwd qw( abs_path );
use Getopt::Std qw(:DEFAULT);
use File;
use Logs;
use PT;

&Show_INCs;

################################################################################
# Globals:


our @Files = ();
our $ChkSumIt = 1;        # Only update a samesize file if

our $Start_Time = time;

################################################################################
# Show include paths:

    my $opt_s = 0;

    our $XLog = $Tmp . '/' . &fnstrip ($0,7) . '.log';
    &Rotate_Log ($XLog, 10);

################################################################################
# Get args:

    our $Usage = "
    Usage: $0 [-dfghqv] [-L Local Dir] [-M Master] [Local [Master]]\n

      Where:
         -d:     Debug mode
         -h:     Print this message
         -L:     = Local Dir to check
         -M:     = Master Dir to use
         -q:     Quiet mode
         -s:     Include Server files

       [* = WIP feature - not yet implemented / released]
";
     $Erc = 101;

     $opt_d = 0;
     $opt_h = 0;
     $opt_q = 0;

     &getopts ('L:M:dfghqsv') || &Invalid ($Usage);
     $Erc = 0;

     if ($opt_h) { print "$Usage\n\n"; exit; }

     our $Debug  = 1 if $opt_d;
     our $Quiet  = 1 if $opt_q;

    if ($Debug) {
        print "OS = $OS\n";
        foreach $i (@INC) {

                print "$i\n";
        }
    }

sub Invalid {
     print $Bell, $Usage;
     exit;
}


################################################################################
# Determine local execution/lib paths

my $Dir1 = shift; $Dir1 = '/var/local/cmtest/dist' if $Dir1 eq '';
my $Dir2 = shift;  $Dir2 = $PPath if $Dir2 eq '';

#$Dir1 = abs_path ( $Dir1);
#$Dir2 = abs_path ( $Dir2);

################################################################################
# Read push.cfg file for file list...

# We should be able to use &PT_Disty::Init here, but for now...
# Clone:
    my $Push_File = ($OS eq 'Win32') ?
                     "$PPath/cfgfiles/push.cfg":
                     '/var/local/cmtest/dist/push.cfg';

    $Push_File = "${PPath}/cfgfiles/push.cfg" unless -f $Push_File;
    $Push_File = "$File1/cfgfiles/push.cfg" unless -f $Push_File; # s/b master

    if ($Debug) {
        print "\n\tDir1 (Master) = $Dir1\n\tDir2 (Clone) = $Dir2\n\tPush_File = $Push_File\n\n";
        &PETC();
    }

    &Exit (2,  "(No push.cfg files ($Push_File) found)") if ! -s $Push_File;
    $Erc = &Read_Init_File ($Push_File);
    &Exit (2,  "(Error reading Push Cfg file \'$Push_File\')") if $Erc;

    if ($opt_s) {
       foreach (@Server_Files) {
           push @Files, $_;
       }
    }

# /Clone

################################################################################
# The meat ...!

&Show_File_Attrs ($Dir1, $Dir2);

################################################################################
# Diff any discrepancies ...

if ($Debug) {
    my $Diff_Dir = $ENV{'HOME'} . '/diffs';
    if (@Files4Update) {
        print "\nCreating file diff(s) in $Diff_Dir ...\n";
    } else {
        print "\n\tNo files to diff!\n";
        exit;
    }

    die "Can't run diff here! Don't be silly...!" if $OS eq 'Win32';
    die "Diff dir \'$Diff_Dir\' doesn\'t exist" if !-d $Diff_Dir;

    my $Count = 0;
    foreach (@cp_args) {
        my ($DF1, $DF2) = split;
        next if !-f $DF1 or !-f $DF2;
        $Count++;
        my $FN = &fnstrip ($DF1, 7);                 # cmtest
           $FN = &fnstrip ($DF1, 3) if $FN eq '';    # .bashrc
        my $F2;
           $F2 = $ENV{'HOSTNAME'} . '-'
                 unless $ENV{'HOSTNAME'} =~ /^ptex/;
           $F2 .= "$Diff_Dir/$FN.diff";
        my $Cmd = "diff $_ > $F2";
         print &Pad ("Diff\'ing $FN ", 40, '.');
         open (OUT, ">$F2");
         print OUT "$Cmd\n\n";
         close OUT;
         system $Cmd;
         if (-s $F2) {
             print " done.\n";
         } else {
             system "rm -f $F2";
             print " (null)\n";
         }
    }
    print "\nDiff'd $Count files\n";

}

&Exit();

# Done.
################################################################################
# Redefine &Exit for a clean getaway ...!

sub Exit {

    my ( $Erc, $Msg ) = @_;
    print "Exiting with Erc = $Erc: " if $Erc;
    print "\"$Msg\"\n" unless $Msg eq '';
    print 'Run time = ', time - $Start_Time, " secs\n";
    exit;
}


################################################################################

=head2 New Functions:
=cut

