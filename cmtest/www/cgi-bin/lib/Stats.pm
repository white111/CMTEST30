################################################################################
#
# Module:    Stats.pm
#
# Author:    Paul Tindle ( mailto:Paul@Tindle.org )
#
# Version:   v6
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 2005 Paul Tindle. All rights reserved.
#
################################################################################

package Stats;
use strict qw(vars);

sub Cleanup {    # From PT.pm 112/12/06 JSW

    my ($Var) = shift;

    #        $Var =~ s/^\s*(.*)\s*$/$1/;
    #        &PETC("$Foo: $Var");

    $Var =~ s/^\s*//;
    $Var =~ s/\s*$//;

    return ($Var);

    #_______________

=head1 NAME

 Cleanup - strip leading and trailing white space(s).

=head1 SYNOPSIS

 use PT;
 .
 .
 $Var = &Cleanup ($Var);

=head1 DESCRIPTION

 $X = &Cleanup ("\n\t\t  Foo  \n\n\n\t\n")

 returns 'Foo'

=cut
}

#__________________________________________________________________________________

#__________________________________________________________________________________
sub Read {

        my ($Stats_File) = @_;
        my $Section;

        open (STATS, "<$Stats_File") || &main::Exit (8, "Can\'t open $Stats_File for read");

        while (<STATS>) {

                chomp;

                next if /^\s*\#/;                        # Comment
                next if /^\s*$/;                        # Blank line

                my ($Param, $Data ) = split (/\=/);

                $Data  = &Cleanup ($Data);    # was $Data  = &main::Cleanup ($Data);  JSW
                $Param = &Cleanup ($Param);   # was $Param = &main::Cleanup ($Param); JSW

#                $Data =~ s/^\s*//;
#                $Data =~ s/\s*$//;
#                $Param =~ s/^\s*//;
#                $Param =~ s/\s*$//;


                $Section = $1 if (/\[(.*)\]/);                        # It's a section marker

#                $main::$Section{$Param} = $Data if $Section eq 'Stats';

                $main::Stats{$Param} = $Data if $Section eq 'Stats';
                $main::TestData{$Param} = $Data if $Section eq 'TestData';
                $main::Globals{$Param} = $Data if $Section eq 'Globals';

        }

        close STATS;
}
#__________________________________________________________________________________
sub Session {

        my ($Op, $Sess) = @_;                # Normally it would be its own $Session
                                        # But this allows for a partner (+1) check ...

        $Sess = $main::Stats{'Session'} if ! defined $Sess;

        my $File = $main::Stats_Path . '/system/' .
                        $main::Stats{'Host_ID'} . '-';
        my $Tag;
        my $FileName = $File . $Sess;

        SWITCH: {
                if ($Op eq 'delete') {
                        system "rm -f $FileName";
                        return (0);
                }
                if ($Op eq 'next') {
                        $main::Stats{'Session'} = 1;
                        while (-f $File . $main::Stats{'Session'}) { $main::Stats{'Session'}++; }
                        $FileName = $File . $main::Stats{'Session'};
                        $main::Erc = system "touch $FileName; chmod 777 $FileName";
                        &main::Print_Log (2, "Problem touching $FileName") if $main::Erc;
                        $Tag = '>';
                        last SWITCH;
                }
                if ($Op eq 'read') {
                        return (0) if ! -f $FileName;
                        $Tag = '<';
                        last SWITCH;
                }
                if ($Op eq 'write') {
                        $Tag = '>';
                        last SWITCH;
                }

        }

        open (STATS, "$Tag$FileName") || &main::Exit (8, "Can\'t open Stats File: $File for $Op");

        if ($Op eq 'read') {
                my $PID = <STATS>;
                return ($PID);
        } else {
                print STATS $main::Stats{'PID'};
        }

        close STATS;

        return (0);
}
#__________________________________________________________________________________
sub Update {

        my ($Stat, $Value) = @_;

        $main::Stats{$Stat} = $Value;
        &Stats::Write;

}
#__________________________________________________________________________________
sub Update_All {

        my $Key;

        &Update_Test_Times();

        &Stats::Write;
}
#__________________________________________________________________________________
sub Update_Test_Times {

        $main::Stats{'TTG'}        = $main::Stats{'ECT'} - time if $main::Stats{'ECT'};
        $main::Stats{'TTG'}        = 0 if $main::Stats{'Status'} eq 'Finished';
        $main::TestData{'TTT'}        = time - $main::Stats{'TimeStamp'};
        $main::TestData{'ATT'}        = $main::TestData{'TTT'} - $main::Wait_Time;
        $main::TestData{'TSLF'}        = time - $main::TestData{'TOLF'} if
                $main::TestData{'TEC'};

        $main::TestData{'ERC'}        = $main::Erc;

        if ($main::Debug) {
            $main::Globals{'Loop_Time'} = $main::Loop_Time;
        }
}
#__________________________________________________________________________________
sub Write {

        my $Key;

        $main::Stats{'Updated'} = time;


                # Because of the Package declaration ...

        my $Stats_Path    = $main::Stats_Path;
        my $Host_ID       = $main::Host_ID;
        my $LogSN         = $main::LogSN;

        my $File1 = "$Stats_Path/$Host_ID" . '-' . getppid . '.txt';
        my $File2 = "$Stats_Path/$main::Stats{'UUT_ID'}" . '.txt';

        my $Stats_File;

        if ($main::Stats{'UUT_ID'} eq '') {
                $Stats_File = $File1;
        } else {
                if (-f $File1) {
                        &main::Print_Log (11, "Renaming stats file from $File1 to $File2");
                        system "mv -f $File1 $File2";
                }
                $Stats_File = $File2;
        }

        $Stats_File = "$main::Tmp/TmpStats.txt" if ! -d $Stats_Path;        #For early debug!

        open (STATS, ">$Stats_File") || &main::Exit (8, "Can\'t open Stats File: $Stats_File for write");
        print STATS "\n[Stats]\n";

        my $L1 = 15;        # Pad (right of key) amount

        foreach $Key (sort keys %main::Stats) {
                print STATS &main::Pad ($Key, $L1) . "= $main::Stats{$Key}\n";
        }

        print STATS "\n[TestData]\n";

        foreach $Key (sort keys %main::TestData) {
                print STATS &main::Pad ($Key, $L1) . "= $main::TestData{$Key}\n";
        }

        print STATS "\n[Globals]\n";

        foreach $Key (sort keys %main::Globals) {
                my $Var = 'main::' . $Key;
                print STATS &main::Pad ($Key, $L1) . "= $$Var\n";
        }
        close STATS;
}
#_____________________________________________________________________________
1;
