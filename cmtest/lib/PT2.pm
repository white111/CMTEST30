################################################################################
#
# Module:      PT2.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      subs from PT.pl
#
# Version:    (See below) $Id: PT2.pm,v 1.3 2008/02/21 00:00:27 joe Exp $
#
# Changes:
#    		v1 - 03/10/02   Initial
#    		v2 - 03/28/04   Pulled more stuff from PT.pm
#    		v3 - 12/13/04   Moved some PT.pm functions here, added &Time_HiRes
#                     Added LDIF functions, &YN uses default
#    		v4 - 02/13/05   Fixed email list -> LDIF problem,
#                     re-ordered to include PT.pm imports, since strategy is to
#                     move any used functions from PT.pm, then obsolete it.
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
my $Ver= 'v4.1 1/31/2008'; # Updated versioning
my $CVS_Ver = ' [ CVS: $Id: PT2.pm,v 1.3 2008/02/21 00:00:27 joe Exp $ ]';
$Version{'PT2'} = $Ver . $CVS_Ver;
#______________________________________________________________________________
use Time::HiRes qw( gettimeofday tv_interval );
#!!!#sub gettimeofday {
#}
#sub tv_interval {
#}

#____________________________________________________________________________
sub Chk_Sub {    # Init use it!

    my ($Sub) = @_;
    $Sub =~ s/\//\\/g unless $Unix;

    if ( !-d $Sub ) {
        if ( -f $Sub ) {
            die "Attempting to create \$Sub: file $Sub exists!";
        }
        else {
            die "Can\'t create directory $Sub" if mkdir $Sub;
            die "Can\'t change mode on $Sub" if chmod '777', $Sub;
        }
    }
}

#_______________________________________________________________
sub Exit {

    my ($Msg) = @_;
    print "\n" unless $Quiet;
    &Print2Log2 ("Exit: $Msg");
    exit;
}
#____________________________________________________________________________
sub Get_INCs { #Copied from PT.pm

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
sub Is_Running {        # Test to see if something is
                        #  in the process table
#
# State: [ Untested | Debug | Test | Pilot | Released ]
#   WinXP:     Test
#   Linux:     Untested
#
# Caller(s):   cron.pl
# Final:       lib/PT2.pm

     my ($Grep_Str) = @_;
     my $Its_Running = 0;

     return 1 if $Grep_Str eq '';  # Added 8/2/04 !

     my $Cmd = 'qprocess';
     my $pField = 4;

     open PS, "$Cmd|" || &Exit (999, "Error opening pipe to ps");

     while (<PS>) {
          chomp;
          my (@PS) = split (/\s+/);
          $Its_Running = 1 if $PS[$pField] =~ /^$Grep_Str/;
     }
     close PS;



     return $Its_Running;
}

#_______________________________________________________________________________
sub OnList { # Check to see if value is on List, return 1 if there's an
             #  intersection

    my ($Value, @List) = @_;
    my $Found = 0;
    my $Attr;
    foreach $Attr (@List) {
        $Found = 1 if $Value eq $Attr;
    }
    return $Found;
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
#______________________________________________________________________________
sub Print_DT { # Print "Something......................."
               #!!! THis is duplicated now in PT3

     my ($Msg, $Length) = @_;
     chomp $Msg;

     return if $Msg eq '';
     $Length = 75 unless $Length;

     print &Pad ($Msg . ' ', $Length, '.');
     our $f_Print_DT = 1;
}

#______________________________________________________________________________
sub Print_Status { # Print "Something.......................OK\n" or
                   # Print "Something.......................FAILED\n"
                   #       "         <info here>\n"

     print " $Status\n" if $f_Print_DT;
     our $f_Print_DT = 0;
}

#______________________________________________________________________________
sub Print2Log2 { # Prints to log file and stdout when needed

#!!! Integrate the new carp browser 'warn' function here!!!

     my ($Msg, $Quiet_) = @_;
     chomp $Msg;

     print $Msg . "\n" unless $Quiet_ or $Quiet;

     $Msg = localtime() . "\:\t$Msg" unless $Msg eq '';

     open (LOG, ">>$Log_File") || die "\&Test::Print2Log2: Can't open log file $Log_File for cat";
     print LOG "$Msg\n";
     close LOG;

     return (0);
}

#______________________________________________________________________________
sub Print_Out {

    my ($Msg, $Out_File) = @_;

    my $Erc = open (OUT, ">>$Out_File");

    unless ($Erc == 1) {
          &Print2Log2 ("Error ($Erc) opening out-file \"$Out_File\"");
          close OUT;
          return (1);
    }
    print OUT $Msg . "\n";
    close OUT;

    return (0);
}

#_______________________________________________________________________
sub Print_Info { # As a quieter alternative to verbose logging
                 #  The ifo file is a rotated log showing globals

    our $Updated_at        = localtime ();
    our $Running           = &Run_Time;
    my ($Hrs, $Mins, $Sec) = 0;

    if ($Running < 100) {
        $Secs = $Running;
        $Running  = "$Secs sec(s)";
    } elsif ($Running < 3600) {
        $Mins = int $Running / 60;
        $Secs = $Running - ($Mins * 60);
        $Running = "$Mins min $Secs sec";
    } else {
        $Hrs = int ($Running / 3600);
        $Running = $Running - ($Hrs * 3600);
        $Mins = int $Running / 60;
        $Secs = $Running - ($Mins * 60);
        $Running = "$Hrs hrs $Mins min $Secs sec";
     }

    my @List = qw (Main  Unix Started_at Updated_at Running Home
                   Tmp Info_File Log_File Out_File );

# Maybe future(so main can control adds)
#    foreach (@Info_List_Adds) {
#        push @List;
#    }

    my $Field_width = 15;

    if ($Info_File eq '') {
          &Print2Log2 ("Info-file not declared");
          return (1);
    }

#    &Rotate_Log ($Info_File, 10);

    my $Erc = open (INFO, ">$Info_File");

    unless ($Erc == 1) {
        &Print2Log2 ("Error ($Erc) opening Info-file \"$Info_File\"");
        return (1);
    }

    foreach $Var ( @List ) {
        print INFO $Var,
                   ' ' x ($Field_width - length ($Var)),
                   "= ${$Var}\n";
                       # Huh - this only works with globals!!
    }

    foreach $Var ( sort values %Label) {
        print INFO "$Var temp",
                   ' ' x ($Field_width - length ($Var) - 5),
                   "= $Temp{$Var}oF (since $Time{$Var})\n";
    }
    close INFO;
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
    return ($Count);
}

#________________________________________________________________
sub Read_LDIF_File {

# Normal:
#        dn: cn=Paul Tindle,mail=ptindle@pacbell.net
#        objectclass: top
#        objectclass: person
#        objectclass: organizationalPerson
#        objectclass: inetOrgPerson
#        objectclass: mozillaAbPersonObsolete
#        givenName: Paul
#        sn: Tindle
#        cn: Paul Tindle
#        mail: ptindle@pacbell.net
#        modifytimestamp: 0Z

# List:
#        dn: cn=Farley Ave
#        objectclass: top
#        objectclass: groupOfNames
#        cn: Farley Ave
#        member: cn=Ellen Mellon,mail=emellon66@earthlink.net
#        member: cn=Sue Bruemmer,mail=sbruemmer@aol.com
#        member: cn=Mike Mellon,mail=mmellon@pacbell.net
#        member: cn=Martha Latta,mail=martha.latta@plantronics.com
#        member: cn=Kitty Slow,mail=kslow@santacruz.k12.ca.us
#        member: cn=Jim Mathewson,mail=jmathew1@pacbell.net
#        member: cn=Carrie Shook,mail=ckshook@pacbell.net
#        member: cn=Bobby Witham,mail=bobby.witham@plantronics.com
#        member: cn=cove,mail=cove@matsonbritton.com


# We use the 'dn' label to signal a new record

    my ($File, $Check) = @_; #$Check = 0: Load unique master, return count
                             #         1: Check each record,

    my $fh;
    my $Count = 0;
    our @Rec_Keys   = 'dn';      # 'Distinguished name - The required key
    my $Key_Suffix = '00';

    %ARecord = ();  #Clear the array (maybe again!)

    print "Reading LDIF file $File ...\n" unless $Quiet;

    open( $fh, "<$File" ) || return (1);

    while (<$fh>) {

        next if /^\s*\#/;    # Comment
        next if /^$/;        # Blank line

        chomp;
        my ( $Param, $Data ) = split (/\:/);

        $Param =~ s/\s+//g;    #Remove any white spaces
        $Data  =~ s/^\s+//;    #Remove any leading/trailing white spaces
        $Data  =~ s/\s+$//;    #Remove any leading/trailing white spaces

        if ($Param eq 'dn') {
            &WebData_Record ($Check) unless $ARecord{'dn'} eq '';
            $Count++;
            $Key_Suffix = '00';
        } else {
            if (($Param eq 'objectclass') or
            ($Param eq 'member')) {
                $Key_Suffix++;
                $Param .= $Key_Suffix;
            }
        };
        $ARecord{$Param} = $Data;
        &Tag_Field2 ($Param)
    }

    &WebData_Record ($Check) unless $ARecord{'dn'} eq '';

    close $fh;
    return ($Count);
}

#________________________________________________________________
sub Run_Time { # Returns HiRes version since $Started

    my $Now = [gettimeofday];

        return tv_interval $Started, $Now;

}

#________________________________________________________________
sub Choose_Path { # [defines and ] sets a global variable with the last match
               #  or the corresponding environment variable

               # Uses the last value from the list, but will overwrite
               # that if the correcponding environment var is defined.

                        # ( pathname, val1, val2, ... )
    my $Path = shift;
    my @List = @_;      # or my ( $Path, @List) = $_; ??


    foreach (@List) {
        ${$Path} = $_ if -d $_; # add a "and $Path eq ''" for a 1st match
    }

    ${$Path} = $ENV{$Path} unless $ENV{$Path} eq '';
    ${$Path} =~ s/\\/\//g;
    print 'Path $' . "$Path set to ${$Path}\n";
}

#________________________________________________________________
sub WebData_Record { # Add or Check a master record

    my ($Check) = @_;

    &Set_RecKey;

    if ($Check) {
        my ($RC, $Msg) = &WebData_Record_Check;
        print "$Msg\n";
        if ($RC == 0) {
             &WebData_Record_Add (0) if &YN('Add it', 'y');
        } elsif ($RC == 1) {
        } else {
            my $Def = ($RC == 3) ? 'y' : 'n';
            &WebData_Record_Add (1) if &YN('Update it', $Def);
        }
    } else {
        &WebData_Record_Add (0);
        #!!! This should really be a call to PT_XML::Record_Add
        ##&Record_Add; but this is using XML dumper!!
    }

    %ARecord = ();  #Clear the array (maybe again!)

}
sub WebData_Record_Add { # Write a complete record to the WebData hash

    my ($OverwriteOK) = @_;

    our $Updated++;       # Will force an archive and file write

    foreach $Key (@Rec_Keys) {
        die "RecKey $Key is not defined" if $ARecord{$Key} eq '';
    }

#!!!    $RecKey = $ARecord{$RecKeyAttr};

    unless ($OverwriteOK) {
        # This is where we check for duplicate keys
        if (defined $WebData{$RecKey}) {
            print "Line $.: A record using the key \"$RecKey\" already exists ! Aborting!\n";
            exit;
        }
    }

    my $Attr;
    foreach $Attr ( sort keys %ARecord ) {
        $WebData{$RecKey}{$Attr} = $ARecord{$Attr};
    }

    %ARecord = ();  #Clear the array
}
sub WebData_Record_Check {
                             # returns:
                             #     0: Not in current master
                             #     1: Exact match in master
                             #     2: Exists with differences
                             #     3: Exists with new information

    &Set_RecKey;
    #&PETC("Line $. Key=$RecKey");

    my $Msg   = "$RecKey: ";

    if (!defined $WebData {$RecKey}) {
        $Msg .= 'not in master - line ' . $.;
        return (0, $Msg);
    }

    my $Key;
    my $Attr;
    my $RC    = 1;

#    my %AllKeys = ();
#    foreach $Attr ( keys %ARecord ) { $AllKeys{$Attr} = 1 }
#    foreach $Attr ( keys %{ $WebData{$RecKey} }){ $AllKeys{$Attr} = 1; }
#    foreach $Attr ( keys %AllKeys ) {
     foreach $Attr ( keys %ARecord ) {    # This will ignore any incoming null fields
         if ($WebData{$RecKey}{$Attr} eq $ARecord{$Attr}) {
#             $Msg .= "OK \'$ARecord{$Attr}\'";
         } else {
             $Msg .= &Pad ("\n\t$Attr:",25);
             $RC = ($ARecord{$Attr} eq '') ? 2 : 3;
#             $Msg .= "   \'" . &Pad ($WebData{$RecKey}{$Attr},20) .
#                     "\' vs \'$ARecord{$Attr}\'";
             if ($WebData{$RecKey}{$Attr} eq '') {
                 $Msg .= '<null> vs ';
             } else {
                 $Msg .= " \'$WebData{$RecKey}{$Attr}\' vs ";
             }

             if ($ARecord{$Attr} eq '') {
                 $Msg .= ' <null>';
             } else {
                 $Msg .= "\'$ARecord{$Attr}\'";
             }
         }
    }
    $Msg = &Pad ($Msg, 70, '.') . " OK" if $RC == 1;
    return ($RC, $Msg);

}

#_______________________________________________________________________________
sub Write_LDIF_File {

    my ($LDIF_File) = @_;

    &Print2Log2 ("Opening master LDIF file $LDIF_File for write ...");
    open( OUT, ">$LDIF_File" )
        || &Exit ( "Can\'t open output file $LDIF_File for write");

    foreach $Rec (sort keys %WebData ) {
        next if $Inactive_Recs{$Rec};

        $WebData{$Rec}{'xmozillausehtmlmail'} = 'true' if !defined
            $WebData{$Rec}{'xmozillausehtmlmail'};
        foreach (@WDFields) {
            my $Field = $_;
            $Field = 'objectclass' if /objectclass/; # Remove the suffix
            $Field = 'member' if /member/; # Remove the suffix
            print OUT "$Field: $WebData{$Rec}{$_}\n"
                 if defined $WebData{$Rec}{$_};
        }
        print OUT "\n";
    }
    close OUT;

}


#_____________________________________________________________________________
sub YN {    # Prompt user for a Y(es), N(o) or Q(uit)

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
