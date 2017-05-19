#!/usr/bin/perl
################################################################################
#
# Module:      fixdevs.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      Temp Test platform, not used, Status ???
#
# Version:    1.1 Sept-20 $Id: fixdevs.pl,v 1.2 2008/02/20 23:05:33 joe Exp $
#
# Changes:    1 Sept-20
#			 1.1 Updated versioning
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

BEGIN { # Special 2005-09-18

    our $OS = ($ENV {'OS'} eq 'Windows_NT') ? 'Win32' : 'Linux';
    $OS = 'Linux'; #Shut up OptiPerl

    if ($OS eq 'Win32') {
        die "this only runs on a Linux based Test Controller";
    }
    unshift @INC, "/home/ptindle/lib";
}

my @Devs = qw(
           /dev/ttyS0
           /dev/ttyUSB0
           /dev/parport1
           );

my $Debug = 1;

foreach (@Devs) {

    my $Dev = $_;
    my $Str = $Dev;

    while (-e $Dev) {
        open IN, "ls -l $_|";
        my $ls = <IN>;
        chomp $ls;
        ($ls) = split /\s+/, $ls;
        $Str .= " ($ls):\t";
        $ls = substr ($ls, 7, 3);
        close IN;
        if ($ls eq '---') {
            $Str .= "NOT ";
            if ($> == 0) {
                my $Erc = system "chmod 666 $Dev";
                if ($Erc) {
                    $Str .= "[Erc=$Erc] Can't \"chmod 666 $Dev\"!!\n";
                    exit (1);
                }
            } else {
                print "\n\n\tPlease ask your admin to \"chmod 666 $Dev\"\n";
                exit (0);
            }
            &Print_Log ("Changed mode on $Dev");
        }
        $Str .= "world writable\n";
        print "$Str\n" if $Debug;
        $Dev++;
    }
    print "\n" if $Debug;
}
exit;

sub Print_Log {

    my ($Msg) = @_;
    open FH, ">>/var/log/fixtabs.log" || return (1);
    print FH time . "\t$Msg\n";
    close FH;

}




