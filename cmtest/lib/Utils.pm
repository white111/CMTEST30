################################################################################
#
# Module:     Utils.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      SCommon BEGIN block code
#
# Version:    (See below) $Id: Utils.pm,v 1.3 2008/02/21 00:00:27 joe Exp $
#
# Changes:   1 09/18/05 Cloned from PT. These are cmtest released functions
#
# Still ToDo:
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
my $Ver= 'v1.1 1/31/2008'; # Updated versioning
my $CVS_Ver = ' [ CVS: $Id: Utils.pm,v 1.3 2008/02/21 00:00:27 joe Exp $ ]';
$Version{'Utils'} = $Ver . $CVS_Ver;
#______________________________________________________________________________

package Utils;

require Exporter;

@ISA = qw(Exporter);
@EXPORT_OK = qw(
        Abort
);

use strict;
use Globals;


#__________________________________________________________________________________
sub Abort {

=head1 NAME

 Abort - sets or checks for an abort flag (file).

=head1 SYNOPSIS

 use PT;
 .
 .
 &Abort (check);
 OR
 &Abort (run_check);
 OR
 &Abort (set);

=head1 DESCRIPTION

 &Abort (check)        : Checks for the exsistance of the abort flag and Exits if found
                   returns 0 or exits as appropriate
 OR

 &Abort (run_check) : Checks to make sure that a particular session is actually running
                        return 1 if it is, 0 if not

 OR

 &Abort (set)        : Sets the abort flag for the next check, returns 0


=cut

    my ($Op) = @_;

    my $File =
      $main::Stats_Path . '/system/' . $main::Stats{'Host_ID'} . '-'
      . $main::Stats{'Session'};

    if ( $Op eq 'run_check' ) {    # Checks to see if session is running

        # Acts on the system stat file, not the abort file

        if ( -f $File ) {
            return (1);
        }
        else {
            return (0);
        }
    }

    if ( $Op eq 'rm' ) {
        $Erc = system "rm -f $File";
        exit(0);    #This should only be called by Exit
    }

    if ( $Op eq 'set' ) {
        return (0) if !-f $File;    # It's not running ...
        $Erc = system "rm -f $File";
        &Exit( 10, $File ) if $Erc;
    }

    $File .= '-ABORT';

    if ( ( $Op eq 'check' ) or ( $Op eq 'clear' ) ) {
        if ( -f $File ) {

            $Erc = system "rm $File";
            &Exit( 10,  'Unable to delete Abort flag file' ) if $Erc;
            &Exit( 199, 'Operator Aborted' ) if ( $Op eq 'check' );
        }
        return (0);
    }

    if ( $Op eq 'set' ) {
        $Erc = system "touch $File";
        &Exit( 9, 'Unable to touch Abort file' ) if $Erc;
        return (0);
    }

    # Since every one of the above have an unconditional return ...
    &Exit( 999, "Invalid call to \&Abort ($Op)" );

    #_______________

}

#____________________________________________________________________________
sub xChk_Sub {    # Init use it!

    my ($Sub) = @_;
    $Sub =~ s/\//\\/g unless $Unix;

    if ( !-d $Sub ) {
        if ( -f $Sub ) {
            die "Attempting to create \$Sub: file $Sub exists!";
        }
        else {
#            die "Can\'t create tmp directory $Sub" if system "mkdir $Sub";
#            die "Can\'t change mode on $Sub" if system "chmod 777 $Sub";
            die "Can\'t create directory $Sub" if mkdir $Sub;
            die "Can\'t change mode on $Sub" if chmod '777', $Sub;
        }
    }
}

#__________________________________________________________________________________
sub Cleanup {

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
sub Debug_Cat {

    my ($File) = shift;

    if ($Debug) {
        print "\n\n$File\n\n";
        if ( -f $File ) {
            system "cat $File";
            print "\n\n";
        }
        else {
            print "... doesn't exist!\n";
        }
    }

=head2 Debug_Cat

Takes a fully qualified filename as an argument and, if $Debug
cats the file to STDOUT

=cut
}

#_____________________________________________________________________________
sub Exit {

    my ( $erc, $Msg ) = @_;
    &Exit_TestExec ( $erc, $Msg );
}

#_____________________________________________________________________________
sub Exit_TestExec {    # A cleaner variant of bye or exit!
                       # Renamed (from &Exit) 03-09-22 to avoid redef.
                       # &Exit must be the responsibility of 'main' (even
                       #   if it's just "sub Exit { &Exit_TestExec (@_) }

    # - Assigns global $Erc
    # - Tag msg with ERROR... if nz $Erc
    # - prints msg to screen
    # - Logs Msg to $0 xlog

    # ?? cat Msg to the $0 history log

    my ( $erc, $Msg ) = @_;
    $Erc = $erc;    # Assign the global $Erc
    chomp $Msg;

    my $Type = ($Erc) ? 2 : 1;

    if ( $Erc == 198 ) {         # (PETC Abort)
        print "Bailing on Exit without logging...\n";
        &Abort('rm');
        exit(0);
    }

    if ($Erc) {
        &Log_Error($Msg);
    }
    else {
        &Print_Log( $Type, $Msg ) unless $Msg eq '';
    }

#    &Power ('OFF');

    &Log_History(2);
    &Stats::Session('delete')    # Release this session
        unless $Erc == 107 and !$opt_f;

    exit($Erc);
}
#____________________________________________________________________________
sub Get_INCs {

    my @List = ();

    my $Module;
    foreach $Module ( keys %INC ) {
                                           #Value (Full path / filename)
        push @List, $INC{$Module}
            unless lc $Module =~ /perl/;
    }

    return (@List);
}

#____________________________________________________________________________
sub Set_Time_Now {

    # This is here to enabling a tickle function to update $Nyear, $N...etc...

    &PT_Date (time+1);
}

#________________________________________________________________
sub HexDump {    # Return a string in a printable format

    # similar to the Unix 'od' (Octal Dump) cmd

    # 1:

    my ( $Str, $Format ) = @_;

    $Format = 1 if !defined $Format;

    my $Count = 0;    # Char on a line
    my ( $A, $B, ) = '';
    my $Set = 0;

    #        my @Out = ();
    my $Out = '';
    my $Val;

    foreach $i( 0 .. length($Str) - 1 ) {

        $Count++;

        $Sub = substr( $Str, $i, 1 );
        $SubVal = ord $Sub;
        $Hex    = sprintf "%lx", $SubVal;
        $Val    = uc $Hex;

        $Val = &Pad( $Val, 2, '0', 2 );

        # Substitute the non-printable chars ...

        my $Char = ( $SubVal < 30 ) ? '*' : $Sub;

        $A .= &Pad( $Val,  3, ' ', 2 ) . ' ';    # 1st line
        $B .= &Pad( $Char, 3, ' ', 2 ) . ' ';    # 2nd line

        if ( ( $Count == 16 ) || ( $i == length($Str) - 1 ) ) {

            my $Addr = &Pad( $Set, 6, '0', 2 );

            #                        $Out[1] .= "$Addr  $A\n        $B\n\n";
            $Out .= "$Addr  $A\n        $B\n\n";

            $Count = 0;
            $A     = '';
            $B     = '';
            $Set   = $Set + 10;
        }

        if (0) {

            foreach $Var qw( SubVal Hex Val Hash HexHash  Char )
              { print "\$$Var=>$$Var<, ";
            } print "\nA=$A\nB=$B\nOut=$Out\n";
            &PETC();
        }

    }

    #        return ($Out [$Format]);
    return ($Out);
}

#________________________________________________________________
sub Load_Hash {

    my ($File) = @_;
    &Print_Log( 11, "Loading hash(es) from cfg file $File ... " );

    open( IN, "<$File" ) || return (1);

    chomp( my (@Hash) = split /\t/, <IN> );    # Load the first line

    # &PETC('PT-234');
    &Exit( 23, "($File line 1 \"<hash>\:\")" ) if $Hash[0] ne '<hash>:';

    # &PETC('PT-236');
    shift @Hash;    # Remove '<hash>:'. @Hash now contains

    #  a list of hash names (only)
    while (<IN>) {

        next if /^\#/;    # Commented out
        chomp;
        next if /^$/;     # Blank line

        &PETC("\nIn: >$_<") if $Debug;
        my (@Data) = split /\t/;    # Key, Data1, Data2, ...

        my ($Key) = $Data[0];
        my ($i)   = 0;
        foreach $HashName(@Hash) {
            $i++;
            $$HashName{$Key} = $Data[$i];
            &PETC("Hash $i) $HashName\{$Key\} =  $Data[$i]") if $Debug;
        }
    }
    print "\n" unless $Quiet;

    close IN;
    return (0);
}

#__________________________________________________________________________________
sub NDT {

    return ( &PT_Date( time, 9 ) );
}

#__________________________________________________________________________________
sub xNDT {    # Obsolete: use &PT_Date (time, 9)

    # Returns current (local) time in Numeric Date-Time format

    ( $Nsec, $Nmin, $Nhour, $Nmday, $Nmon, $Nyear, $Nwday, $Nyday, $Nisdst ) =
      localtime;

    $Nmon++;    # Base [0] to month
    $Nyear = 1900 + $Nyear;
    foreach $Var qw (Nsec Nmin Nhour Nmday Nmon) {

        # print "$Var = >$$Var<\t";
        $$Var = &Pad( $$Var, 2, '0', 2 );

        # print ">$$Var<\n";
    }

    return ("$Nyear$Nmon$Nmday\.$Nhour$Nmin$Nsec");
}

#__________________________________________________________________________________
sub Pad {    # Return a string with things added (<sp> default)

    my ( $Orig_Str, $Len_Int, $Pad_Str, $Where ) = @_;
    # $Where = 1 pads on the right (Default)
    #          2 on the left
    #          3 pads on both sides, centering
    # original string in a new string $Len_Int long

    $Pad_Str = ' ' if $Pad_Str eq '';

    while ( length($Orig_Str) < $Len_Int ) {

        if ( $Where == 2 ) {
            $Orig_Str = $Pad_Str . $Orig_Str;
        }
        elsif ( $Where == 3 ) {
            $Orig_Str = $Pad_Str . $Orig_Str . $Pad_Str;
            if ( length($Orig_Str) > $Len_Int ) { chop($Orig_Str); }
        }
        else {
            $Orig_Str = $Orig_Str . $Pad_Str;
        }
    }

    while ( length($Orig_Str) > $Len_Int ) {

        chop($Orig_Str);
    }

    return ($Orig_Str);
}

#__________________________________________________________________________________
sub Parse {    #Return the front Nth of $_

    # stripping any leading / trailing ' 's
    # and update $_

    my ($Length) = @_;
    my ($Chunk)  = '';

    if ($Length) {
        $Chunk = substr( $_, 0, $Length );
        $_ = substr( $_, $Length + 1 ) if $Length < length($_);
    }
    else { $Chunk = $_; }

    $Chunk =~ s/^ *//;      # Remove leading spaces
    $Chunk =~ s/ *$//;      # Remove trailing spaces

    #        &PETC("\n\nParse:\n\tReturn >$Chunk<\n\t\$_ = >$_<\nNext");

    return $Chunk;

}

#__________________________________________________________________________________
sub PT_Date {

=head1 NAME

 PT_Date - return a date in various formats.

=head1 SYNOPSIS

 use PT;
 .
 .
 &PT_Date (time, format);        [default format = 0]

=head1 DESCRIPTION

 &PT_Date ();                        OR
 &PT_Date (time);                -> returns current time as a string
 &PT_Date (1234567);                -> returns a date string for specified time int

 Format:    Returns:

  0          2002/06/30 08:59        [default]
  1          06/30 08:59
  2          06/30 08:59:01
  6          06/30/02
  9          20020630.085901        [same as NTD function]

=cut

    my ( $Time, $Type ) = @_;
    my @Date_Str;

    ( $Nsec, $Nmin, $Nhour, $Nmday, $Nmon, $Nyear, $Nwday, $Nyday, $Nisdst ) =
      localtime($Time);

    $Nmon++;    # Base [0] to month
    $Nyear = 1900 + $Nyear;
    foreach $Var qw (Nsec Nmin Nhour Nmday Nmon)
      { $$Var = &Pad( $$Var, 2, '0', 2 );
    }

    $Date_Str[0] = "$Nyear/$Nmon/$Nmday $Nhour\:$Nmin";
    $Date_Str[1] = "$Nmon/$Nmday $Nhour\:$Nmin";
    $Date_Str[2] = $Date_Str[1] . ":$Nsec";
    $Date_Str[6] = "$Nmon/$Nmday/" . substr( $Nyear, 2, 2 );
    $Date_Str[8] = "$Nyear-$Nmon-$Nmday";                      #New!
    $Date_Str[9] = "$Nyear$Nmon$Nmday\.$Nhour$Nmin$Nsec";

    return ( $Date_Str[$Type] );
}
#________________________________________________________________
sub Read_Cfg_File {

    # Sources parametric data from a file like:
      # LogFile = /tmp/log.txt
    # Returns the # found

    my ($File) = @_;
    my $fh;
    my $Count = 0;
    open( $fh, "<$File" ) || return (1);

    while (<$fh>) {

        next if /^\s*\#/;    # Comment
        next if /^$/;        # Blank line

        chomp;
        my ( $Param, $Data ) = split (/\=/);

        $Param =~ s/\s+//g;    #Remove any white spaces
        $Data  =~ s/^\s+//;    #Remove any leading/trailing white spaces
        $Data  =~ s/\s+$//;    #Remove any leading/trailing white spaces

        next if $Param eq '';
        next if $Param eq 'CmdFilePath';

        $$Param = $Data;
        $Count++;
    }

    close $fh;
    return (0);
}
#________________________________________________________________
sub Read_Init_File {

    # Sources list information from a file like:
    #
    # [Hosts]
    # mfg1
    # mfg3
    # and loads the array @Hosts
    # The array must be a pre-declared global list

    my ($File) = @_;
    my $fh;
    my $List;

    &Print_Log( 11, "Reading cfg file $File ... \n" );

    open( $fh, "<$File" ) || return (2);

    while (<$fh>) {

        chomp;

        next if /^\s*\#/;    # Comment
        next if /^\s*$/;     # Blank line

        if (/\[(.*)\]/) {    # It's a section marker
            $List = $1;
        }
        else {    # It's just data
            push @{$List}, $_;
        }

    }

    close $fh;
    return (0);
}

#__________________________________________________________________________________
sub Show {

    my ($Var) = @_;

    &PETC("$Var = ${$Var}");


# This is of limited usage. Careful about using it with a 'local' or 'my' var
    # since it won't be determined here, since it's outside it's primary block

#    my (@Vars) = @_;

#    print "\n";
#    foreach $Var(@Vars) {
#        print "Var \$$Var = $$Var\n";
#    }
#    &PETC();
}

#__________________________________________________________________________________
sub Show_INCs {  # Pulled from Init

    if ($Debug) {
        print "OS = $OS\n";
        foreach (@INC) {
            print "$_\n" unless /perl/;
        }
        print "\nNew Files ( warmer than 30 mins ):\n\n";
    }
    my $Key;
    foreach $Key (sort keys %INC) {
        my $File = $INC{$Key};
        my $Old = int ( ( (-M $File) * 24 * 60) + 0.5); # Mins old
        print "$File [$Old mins]\n" unless $Old > 30;
    }
}
#__________________________________________________________________________________
sub PETC {

=xml

<XML>
  <Callers>
           cron.pl
  </Callers>
  <State options=" Untested | Debug | Test | Pilot | Released>
    <WinXP val="Released" />
    <Linux val="Released" />
  </State>
  <Final>
    lib/PT2.pm
  </Final>
</XML>

=cut


    #   Press
    #   _ Enter
    #     _ To
    #       _ Continue
    #         _

    my ($MSG) = @_;
    my ($X);
    my $Start_Wait = time;
#    my $Silent = 1; #!!!

    if ($GUI) {
        my $Button =
          &Message( $MSG . "\n\n\nPress [OK] to continue, [Cancel] to Abort", 3,
          1 );
        return () if lc $Button eq 'ok';
        exit if lc $Button eq 'cancel';
    }
    else {
        unless (@_) { $MSG = 'Press <CR> to Continue, Q to End, R to Run'; }
        unless ($PETC_Dont_Stop) {
            $MSG .= "" unless $Silent;
            printf "$MSG:";
            chop( $X = <STDIN> );
            $X = "\U$X";
            if ( $X eq 'Q' ) { exit }
            if ( $X eq 'R' ) { $PETC_Dont_Stop = 1; }
        }
    }

    $Wait_Time += time - $Start_Wait;

    return $X;
}
#__________________________________________________________________________________
sub PT_Sleep {

    my ($Time) = @_;
    while ($Time) {
        $Time--;
        system("echo -n .") unless $Quiet;
        sleep 1;
    }
}

#_____________________________________________________________________________
sub YN {    # Copied from PT2 (for cmtest)
            # Prompt user for a Y(es), N(o) or Q(uit)

    # Return a 1, 0 or exit resp'ly

    local ($Msg, $Default) = @_;
    local ($Var);

    $Msg = "$Msg(y/n/q)";
    $Msg .= "[$Default]" unless $Default eq '';

    while (1) {
        $PETC_Dont_Stop = 0;    # To avoid a hang!
        $Var = &PETC("$Msg?");
        $Var = uc $Default if $Var eq '' and $Default ne '';
        return 1 if $Var eq 'Y';
        return 0 if $Var eq 'N';
    }
}
#_______________________________________________________________________________
1;
