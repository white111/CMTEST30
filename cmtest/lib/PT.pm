################################################################################
#
# Module:      PT.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      ??
#
# Version:    (See below) $Id: PT.pm,v 1.9 2008/02/22 21:00:51 joe Exp $
#
# Changes:
#			$Ver = '24.3  2006/10/26'; #    Fixed return (0) unless $Erc;  in Read_Data_File# Reads list items from cfg file, ps -u $Owner
#            Merged DataFile.pm  V 1.2A
#             Added &Init_HA::Session('delete') to Exit_TestExec
#			Copied from PT.pm v24 (to avoid a full scale merge! )
#			!!! Should be removed with next major release
#			$Ver= 'v24.4 1/31/2008'; # Updated versioning
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
my $Ver= 'v24.5 1/31/2008'; # Added ANSI Color
my $CVS_Ver = ' [ CVS: $Id: PT.pm,v 1.9 2008/02/22 21:00:51 joe Exp $ ]';
$Version{'PT'} = $Ver . $CVS_Ver;
#______________________________________________________________________________

use Logs;
use Term::ANSIColor;
our $WebData = ();



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
      $Stats_Path . '/system/' . $Stats{'Host_ID'} . '-'
      . $Stats{'Session'};

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
            if ( $Op eq 'check' ) {
                &Power ('OFF');
                &Exit( 199, 'Operator Aborted' );
            }
        }
        return (0);
    }

    if ( $Op eq 'set' ) {
        my $UMask = umask;
        umask 0;
        $Erc = system "touch $File";
        umask $UMask;
        &Exit( 9, 'Unable to touch Abort file' ) if $Erc;
        return (0);
    }

    # Since every one of the above have an unconditional return ...
    &Exit( 999, "Invalid call to \&Abort ($Op)" );

    #_______________

}

#__________________________________________________________________________
sub Ask_User {

    my ($Type, $Var, $Prompt) = @_;
    if ($Prompt eq '') {  # &Ask_User ( Type Prompt ) [no Var] supported
        $Prompt = $Var;
        $Var = '';
    }

    my $Data;
    my $Start_Wait = time;

    $Prompt =~ s/^\"(.*)\"$/$1/;
    &Print_Log (11, "Asking User \'$Prompt\' [ type = $Type, $Var = ] ...");

#    return () unless lc $Type =~ /text/;

    if ($GUI) {
        ($Erc, $Data) = system "java -jar Input.jar $Prompt";
        &Exit (999, "Java failed to run") if $Erc;
    } else {

        printf  "$Prompt: ";
        chop( $Data = <STDIN> );
        if ( $Data eq "\[" ) { &Exit( 198, "Get UI Abort" ); }
        $Wait_Time += time - $Start_Wait;

    }

   if ($Var ne '') {
        ${$Var} = $Data;
        return (0);
    } else {
        return ($Data);
    }
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
sub DataFile_Read {

=pod
# Sources list information from a file like:

    # [Hosts]
    # mfg1
    # mfg3
    # and loads the array @Hosts

    # or

    # [Part_Number_Key]

    # 001 = 00002
    # 002 = 00292
    # =
    # %Part_Number_Key {
    #    001 => '00002'
    #    002 => '00292'
    #  }
=cut

    # The array/hash must be a pre-declared global

    my ($File) = @_;
    my $fh;
    my $Label = '';  # Could be a list name or a hash name

    &PrintLog ( "Reading data file $File ... \n", 1);
    open( $fh, "<$File" ) || return (1);

    while (<$fh>) {

        chomp;
        #print "DataFile - $.\n";
         #print " we are in Datafileread $_\n";
        next if /^\s*\#.*/;    # Comment
        next if /^(\s*)$/;     # Blank line
        next if $_ eq '';      # Blank line

        s/^\s*//;
        if (/\[(.*)\]/) {    # It's a list/hash name
            $Label = $1;
            if ($Label eq 'Record') {   # It's a new hash
                &Load_Web_Data ($Label);         #  so load the last one
                                                 #  and clear the buffers
            } elsif ($Label eq 'Data') {   # It's a new hash
            } else {
                %{$Label} = ();
                @{$Label} = ();
            }
        } else {             # It's data
            if (/^\s*(\S+)\s*\=\s*(.*)\s*$/) {
                 if ($Label eq '') { # It's a scalar assignment
                    my $Var = $1;   # Should remove $ in cfg file but don't
                    $Var =~ s/\$//;
                    return (2, '$' . $Var) if !defined ${$Var};
                    ${$Var} = $2;
                } else {                   # It's a hash
                    return (3, '%' . $Label) if !defined %{$Label};
                    ${$Label}{$1} = $2;
                    chomp(${$Label}{$1});
                    #print " we are in Datafileread $Label $Label->$1 ${$Label}{$1} = $2\n";
                }
            } else {                                    # It's a list
                return (4, '@' .$Label) if !defined @{$Label};
                # s/^\s*(.*)\s*/$1/;
                push @{$Label}, $_;
            }
#            &PETC("$Label: 1=$1, 2=$2");
        }
    }
    &Load_Web_Data ($Label) unless $First; #Once again at the end of the file

    close $fh;
    return (0);
}

#________________________________________________________________
sub DataFile_Write {

    # &Write_Data_File (FullFS-File, [new|(cat)], [hash|list|scalar], VarName)
    #           Note: The array/hash must be a pre-declared global

#    my ($File, $Action, $Type, $Label) = @_;

     # v1.2 ->
    my $File            = shift;
    my $Label           = pop;
    my ($Action, $Type) = @_;     # Whatever's left!
    my $Pr_             = '  ';   # Line Preamble

    if ($Label =~ /^([\%|\@|\$])(.*)/) {
        $Type = 'hash'   if $1 eq '%';
        $Type = 'list'   if $1 eq '@';
        $Type = 'scalar' if $1 eq '$';
        $Label = $2
    }
    if ($Type eq '') {
        if ($Action =~ /[hash|list|scalar]/) {
            $Type   = $Action;
            $Action = '';
        }
        return (7, "Don\'t understand call \&DataFile_Write " .
                   "(File=$File, Action=$Action, Type=$Type, Label=$Label)");
    }

    my $fh;
    &PrintLog("Writing data file $File ($Action, $Type, $Label)... \n" );

    my $Op = ($Action eq 'new' or $Action eq '>') ? '>' : '>>';

    open( $fh, $Op . $File ) || return (2);

    print $fh "# Created by &Data_File::Write ($Action, $Type, $Label) on ",
              localtime(time) . "! Do not edit!\n\n",
              "# \$Id\$\n\n" if $Action eq 'new';

    print "\n\n";

    my $Str = "$Type $Label not defined!";
    if ($Type eq 'hash') {
        return (3, $Str) if !defined %{$Label};
        print $fh "\n\[$Label\]\n\n";
        foreach ( sort keys %{$Label}) {
             print $fh $Pr_, $_, &FPad($_), ${$Label}{$_}, "\n"
                 unless ${$Label}{$_} eq '';
        }
    } elsif ($Type eq 'list') {
        return (4, $Str) if !defined @{$Label};
        print $fh "\n\[$Label\]\n\n";
        foreach ( @{$Label}) {
            print $fh "$Pr_$_\n";
        }

    } elsif ($Type eq 'scalar') {
        return (5, $Str) if !defined \${$Label};
        print $fh "\n\n$Pr_$Label\t\= ${$Label}\n\n";
    } else {
        return (6, "Don\'t understand call \&DataFile::Write_ ('File', $Action, $Type, $Label)");
    }
    print $fh "\n";

    close $fh;
    return (0);
}

#_______________________________________________________________________________
sub FPad {

    my ($Label)   = @_;
    my $Field_Pad = 12;
    $Field_Pad = $Field_Pad - length($Label);
    return (' ' x $Field_Pad . '= ');
}

#_______________________________________________________________________________
sub Load_Web_Data_dep {       #found 2 of the same JW 2/5/15

    my ( $Label ) = @_;

    return unless $Label =~ /Data|Record/;
#    return unless $Label eq 'Data' or
#                  $Label eq 'Record';

    my ($Key) = &Set_RecKey (@Rec_Keys);

    &PrintLog ("[Load_Web_Data \%$Label] Key = \'$Key\'", 1 );
    return if $Key eq '';

    foreach $Attr ( keys %{$Label}) {
        $WebData{$Key}{$Attr} = ${$Label}{$Attr} if defined ${$Label}{$Attr};
    }
}

#________________________________________________________________
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

  	if ($Stats{'Status'} eq 'Active')  {    # Remove any active tests
    	$Stats{'Status'} = 'Error' ;
    }
    &Stats::Update_All ;

    if ( $Erc == 198 ) {         # (PETC Abort)
        print "Bailing on Exit without logging...\n";
        &Abort('rm');
        exit(0);
    }


    print color 'red' if $Stats{'Result'} ne "PASS";
    print color 'green' if $Stats{'Result'} eq "PASS";
    if ($Erc) {
        &Log_Error($Msg);
    }
    else {
        &Print_Log( $Type, $Msg ) unless $Msg eq '';
    }
   print color 'reset';

#    &Power ('OFF');   # This will power off on a decline !!! Not good!

    &Log_History(2);

    &Stats::Session('delete')    # Release this session
        unless $Erc == 107 and !$opt_f;
    if (defined $HA_Session && HA_Session ne 0)   {
    	&Stats::Session('delete',$HA_Session)     # Release this HA session
        unless $Erc == 107 and !$opt_f;
    }
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

#____________________________________________________________________________
sub Is_Running {        # Copied from PT2 (10/05

                        # Test to see if something is
                        #  in the process table
#
# State: [ Untested | Debug | Test | Pilot | Released ]
#   WinXP:     Test
#   Linux:     Test
#
# Caller(s):   cron.pl cmtest.pl (Init.pm)
# Final:       lib/PT2.pm

     my ($Grep_Str, $Check_PID, $Owner) = @_;
     my $Its_Running = 0;
     $Check_PID = 1 if $Check_PID eq '';
#!!!     return 1 if $Grep_Str eq '';  # Added 8/2/04 !

     my ($Cmd, $pField);

     if ($OS eq 'Linux') {
         $Owner = 'root' if $Owner eq '';
         #$Cmd = 'ps -u $Owner';
         $Cmd = 'ps -a';
         $pField = ($Check_PID) ? 0 : 3;
     } else {
         $Cmd = 'qprocess';
         $pField = ($Check_PID) ? 3 : 4;
     }
#     &PETC("Grep = $Grep_Str, PID = $Check_PID, ptr = $pField");
     open PS, "$Cmd|" || &Exit (999, "Error opening pipe to ps");

     while (<PS>) {
          chomp;
          s/^\s+//;
          my (@PS) = split (/\s+/);
          $Its_Running = 1 if $PS[$pField] =~ /^$Grep_Str/;
#          &PETC("($OS) Looking for $Grep_Str in $PS[$pField]: = " . $Its_Running)
     }
     close PS;

     &Print_Log (11, "Grep_Str running = $Its_Running");

     return ($Its_Running);
}


#________________________________________________________________
sub Load_Web_Data {

    my ( $Label ) = @_;

    return unless $Label =~ /Data|Record/;
#    return unless $Label eq 'Data' or
#                  $Label eq 'Record';

    my ($Key) = &Set_RecKey (@Rec_Keys);

    &PrintLog ("[Load_Web_Data \%$Label] Key = \'$Key\'", 1 );
    return if $Key eq '';

    foreach $Attr ( keys %{$Label}) {
        $WebData{$Key}{$Attr} = ${$Label}{$Attr} if defined ${$Label}{$Attr};
    }
}

#________________________________________________________________
sub xLoad_Hash {

    my ($File) = @_;
    &Print_Log( 11, "Loading hash(es) from file $File ... " );

    open( IN, "<$File" ) || return (1);

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
# This cannot be, be cause of the problem of variable dereferencing
# NO package DataFile;
sub PrintLog { &Print2XLog (@_)}
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

#__________________________________________________________________________________
sub PT_Sleep {

    my ($Time) = @_;
    while ($Time) {
        $Time--;
        system("echo -n .") unless $Quiet;
        sleep 1;
    }
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

        if ($Param =~ /(\w+)\s*\[(\d+)\]/) {
            ${$1}[$2] = $Data;
        } else {
            ${$Param} = $Data;
        }
        $Count++;
    }

    close $fh;
    return (0);
}
#________________________________________________________________
sub Read_Data_File {  # Might have been written by &Write_Data_File (below)

    my ($File) = @_; # FullFileSpec::DataFile

    my ($Erc, $Data)  = &DataFile_Read ($File);
    return (0) unless $Erc;

    if ($Erc == 1) {
        &PrintLog ("Unable to read Data File $File");
        return (2);
    } elsif ($Erc) {
        &Exit ($Erc, "Attempt to load undefined var: $Data");
    }

    return (0);
}


#________________________________________________________________
#sub Read_Init_File_dep {
#               # Added updates to have sub sections/ multidimensional array 2/9/15 JSW
#    my ($File) = @_;

##    &Read_Data_File ($File);
##    return;

#    # Sources list information from a file like:
#    #
#    # [Hosts]
#    # mfg1
#    # mfg3
#    # and loads the array @Hosts
#    # The array must be a pre-declared global list

#    &Print_Log( 11, "Reading cfg file $File ... \n" );
#    my $fh;
#    my $List;
#    our $Subsection = '';


#    open( $fh, "<$File" ) || return (2);

#    while (<$fh>) {

#        chomp;

#        next if /^\s*\#/;    # Comment
#        next if /^\s*$/;     # Blank line

#        if (/\[(Files)\[(.*)\]\]/) {    # It's a section marker with a sub section
#            if ( ! $List) {
#                $List = $1;
#                push (@{$List}, $1);
#                print " Push $1\n)";
#            } else {
#                    $List = $1;
#            }
#            $Subsection = $2;
#            #print "Sec Sub $List $Subsection\n";
#            #print " My list sub @{$List[$Subsection]}\n";
#        }
##        elsif (/\[(.*)\]/) {    # It's a section marker
##            $List = $1;
##           $Subsection = '';
##            #print "List $List\n";
##        }
#        else {    # It's just data
#            #push @{$List}, $Directory . "\/" . $_ if $Directory ;
#            if ( $Subsection ) {
#            #push @{$List},$Subsection;
#           print "push @{$List[$Subsection]}, $_ \n";
#            push (@{$Subsection}, $_);
#            }
#            #push @{$List},  $_ if ! $Subsection ;
#        }

#    }
#        print " Varibles $List $Subsection\n";
##        print " My list @{$List}$_\n";
#        close $fh;
#           print " My list stat @{$List} @{$Subsection}\n";
#           push @{$List}, @{$Subsection};
#           print " My list stat2 @{$List}\n";


#    return (0);
#}
#____________________________________________________________________________
#sub Read_Init_File_dep2 {

#    my ($File) = @_;

##    &Read_Data_File ($File);
##    return;

#    # Sources list information from a file like:
#    #
#    # [Hosts]
#    # mfg1
#    # mfg3
#    # and loads the array @Hosts
#    # The array must be a pre-declared global list

#    &Print_Log( 11, "Reading cfg file $File ... \n" );
#    my $fh;
#    my $List;
#    my $Path;
#    our @Files if undef;


#    open( $fh, "<$File" ) || return (2);

#    while (<$fh>) {

#        chomp;
#        $$List = "";
#        #$Path = "";

#        next if /^\s*\#/;    # Comment
#        next if /^\s*$/;     # Blank line

#        if (/^\[(.*)\]$/) {    # It's a section marker
#            $List = $1;
#            print "List $List\n";
#            if (/^\[(.*)\[(.*)\]\]$/) {   # It's a section marker and Path
#                $List = $1;
#                $Path = $2;
#                my $LastPath = $Path;
#                my $LastList = $List;
#                push @{$List}, $Path;
#                print "push section marker and path Array $List @{$List} Path $Path\n";

##                push @{$List[$Path]}, $_;
##                print "push List $List  Path $Path , Data $_;\n"
#            } elsif (/\[(.*)\]/) {    # It's a section marker
#                $List = $1;
#                $Path = "";
#                push @{$List}, $_;
#                print "push section marker $List _ @{$List}, $_/n";
#            }
#        }
##        elsif (/\[(.*)\]/) {    # It's a section marker
##            $List = $1;
##        }
#       elsif ( $List =~ /./ && $Path =~ /./ )  {    # It's  Section & path
#            push @{$List[$Path]}, $_;
#            print "push lastList $List  lastPath $Path , Data $_;\n"
#        }
#        else {    # It's just data
#            push @{$List}, $_;
#            print "push data last List $List  No Path $Path , Data $_;\n"
#        }

#    }
#         print " All Array $List|$Path @{$List[$Path]}\n";
#    close $fh;
#    return (0);
#}
#________________________________________________________________
sub Read_Init_File {

    my ($File) = @_;
    my $Path= "";
#    &Read_Data_File ($File);
#    return;

    # Sources list information from a file like:
    #
    # [Hosts]
    # mfg1
    # mfg3
    # and loads the array @Hosts
    # The array must be a pre-declared global list

    &Print_Log( 11, "Reading cfg file $File ... \n" );
    my $fh;
    my $List;


    open( $fh, "<$File" ) || return (2);

    while (<$fh>) {

        chomp;

        next if /^\s*\#/;    # Comment
        next if /^\s*$/;     # Blank line
        if (/\[(.*)\[(.*)\]\]/) {   # It's a section marker and Path   added 2/12/15 JSW
        	$List = $1;
        	$Path=$2;
       } elsif (/\[(.*)\]/) {    # It's a section marker
            $List = $1;
            $Path= "";
        } else {    # It's just data
            push @{$List}, $Path.$_;
            #print "push push $List  @{$List}, $Path.$_\n";
        }

    }
      #print " list @{$List} \n";
    close $fh;
    return (0);
}

#____________________________________________________________________________
sub Set_RecKey {

    # Returns an extrapolated string (to be used for global $RecKey
    # &PrintLog ("");

    my (@Fields) = @_;
    my $Key   = '';

    foreach my $Var (@Fields) {
        my $Val = $Record{$Var};
        my $Key2Add = $Record{$Var};
        $Key .= '|' unless $Key eq '';
        $Key .= $Key2Add;
        $Key = '' if $Key2Add eq ''; # Null it if any element is null
    }
    &PrintLog ("[Set_RecKey]\tKey=\'$Key\'", 1 );

    return ($Key);
}


#________________________________________________________________
sub Set_Time_Now {

    # This is here to enabling a tickle function to update $Nyear, $N...etc...

    &PT_Date (time+1);
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

#________________________________________________________________
sub Write_Data_File {  #

    # &Write_Data_File (FullFS-File, [new|(cat)], [hash|list|scalar], VarName)
    #   Note: The array/hash must be a pre-declared global

    my ($Erc, $Data)  = &DataFile_Write (@_);
    if ($Erc == 2) {
        &PrintLog ("Unable to read Data File $File");
        return (2);
    } elsif ($Erc) {
        &Exit ($Erc, "Attempt to write undefined var: $Data");
    }

    return (0);

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
