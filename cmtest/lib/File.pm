################################################################################
#
# Module:     File.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#			 Joe White( mailto:joe@stoke.com )
#
# Descr:      Subs for file IO
#
# Version:    (See below) $Id: File.pm,v 1.6 2008/02/21 00:00:27 joe Exp $
#
# Changes:
#			$Version{'File'} = '19   2006/12/06';    # Exposed $FH
#           Show_File_Attrs() Added Support for tftpboot dir in push.pl
#           Updated for www push/update
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
my $Ver= 'v19.1 1/31/2008'; # Updated versioning
my $CVS_Ver = ' [ CVS: $Id: File.pm,v 1.6 2008/02/21 00:00:27 joe Exp $ ]';
$Version{'File'} = $Ver . $CVS_Ver;
#__________________________________________________________________________________


our @File  = ();         #List of Files and directory paths
our @Dir_List  = ();    # List of (sub)dirs in a spec'd dir (&File_List)
our @File_List = ();    # List of files in a spec'd dir (&File_List)
our $FH = 'FH00';       # The nested (recursive) File Handle

#__________________________________________________________________________________
sub fnstrip {

    #        Returns specified portions of a filename

    #        Invocation: fnstrip (c:/usr/tmp/foo.txt, X)

    #        X:        Returns:
    #        0        c:/usr/tmp/foo.txt     # Unchanged
    #*       1        c:/usr/tmp             # Parent path
    #        2        c:/usr/tmp/foo         # Parent dir + base filename
    #        3        foo.txt                # File name + extension
    #        4        tmp                    # Parent dir
    #*       6        c:/usr                 # Grand-parent path
    #        7        foo                    # Base filename
    #        8        txt                    # File extension

    my ( $Full_FN, $Specifier ) = @_;
    my @Ret;

    $Ret[0] = $Full_FN;
    $Full_FN =~ s|\\|/|g;               # Just in case is DOS format!

    my @Chunks = split ( /\//, $Full_FN );

    $Ret[3] = pop (@Chunks);            # foo.txt

    $Ret[1] = join '/', @Chunks;        # Everything utai parent
    $Ret[4] = pop (@Chunks);            # parent
    $Ret[6] = join '/', @Chunks;        # Everything utai grant-parent

#    ( $Ret[7], $Ret[8] ) = split ( /\./, $Ret[3] );

    @Chunks = split ( /\./, $Ret[3] );  # Just on the FN this time
    $Ret[8]  = pop @Chunks;
    if (@Chunks) {         # If there's anything left...!
        $Ret[7] = join '.', @Chunks;        # In case of foo.bar.txt
    } else {
        $Ret[7] = $Ret[8];                  # The ext is really the Base
        $Ret[8] = '';                       #   with NO file Ext
    }
#
    $Ret[2] = $Ret[1] . '/' . $Ret[7];

    return ( $Ret[$Specifier] );
}
#__________________________________________________________________________________
sub File_List {

    #    Updates:
    #       our @Dir_List  - List of (sub)dirs in a spec'd dir (&File_List)
    #       our @File_List - List of files in a spec'd dir (&File_List)

    my ($File_Path, $No_Recurse) = @_;
    my $DSep = '/';
    my $Count = 0;

    $File_Path = '.' if $File_Path eq '';

    $FH++;
    $Erc = opendir( $FH, "$File_Path" );
    &PETC ("File_List failed to open \'$File_Path\' (Erc = $Erc)") unless $Erc == 1;
    # &PETC("X:$FH: $File_Path");
    my ($Item);
    foreach $Item( grep !/^\.\.?\z/, readdir($FH) ) {
        $Item = $File_Path . $DSep . $Item;
        # print "$Item\n";
        if ( -d $Item ) {
            push @Dir_List, $Item;
            &File_List($Item, 0) unless $No_Recurse;
        }
        else {
            $Count++;
            push @File_List, $Item;
        }

    }
    #!!! This could be broken
    #&PETC("Y:$FH: $File_Path");

    closedir($FH);
    $FH--;

    return ($Count);
}

#_______________________________________________________________________________
sub File_Checksum {

    my ($File) = @_;
    my $Chksum = 0;
    my $Byte;

    open FHC, "<$File" || return ('');
    while (!eof FHC) {
           read FHC, $Byte, 1;
           $Chksum = $Chksum ^ ord $Byte,
    }
    close FHC;
    return ($Chksum);
}
#_______________________________________________________________________________
sub File_Close {

    my ($FH) = @_;
    close $FH;
    $FH--;
}

#_______________________________________________________________________________
sub File_Open {

    my ( $File, $FH, $Mode ) = @_;

    $Mode = "\U$Mode";
    $Mode = '<' if $Mode eq '';              # Default
    $Mode = '<' if $Mode eq 'IN';
    $Mode = ( $Mode eq '' ) ? '<' : $Mode;

    #        &PETC("Mode=$Mode");

    &PT_Exit("Attempt to open <null> file") if $File eq '';
    open( $FH, "$Mode$File" ) || return (1);
    return (0);
}

#_______________________________________________________________________________
sub File_Open_Recursive {

    my ($File) = @_;

    $FH = 'FH00' if not defined $FH;
    $FH++;

    &File_Open( $File, $FH, '<' );     #In only!
    return $FH;
}

#_______________________________________________________________________________
sub Get_File_Stats {

=item

# Originally &Show_Files_Attrs__Get_Stats for

=invocation
my ( $Date, $Size, $DateStr, $MIA ) =
          &Get_File_Stats ("$Dir1/$Name");

=cut

    my ($File_Spec) = @_;
    my $Date     = 0;
    my $Size     = '  -?-';
    my $Date_Str = '   -';
    my $MIA      = 0;

    if ( -f $File_Spec ) {
        $Size     = ( -s $File_Spec );                           # Size
        $Date     = $^T - ( ( -M $File_Spec ) * 3600 * 24 );    # Mod Date
        $Date_Str = &PT_Date( $Date, 1 );
    }
    else {
        $MIA = 1;
    }

    return ( $Date, $Size, $Date_Str, $MIA );
}

#_______________________________________________________________________________
sub Show_File_Attrs {  #Mofified for improved www distribution

    my ( $Dir1, $Dir2, @File2do ) = @_;
    our @Files = @File2do if @File2do;
    my $Debug2;

    our %FileList;         # Composite list of files (either path)
    our @Files4Update;     # List of files (no leading path)
    our @cp_args;          # List of 'file1 file2' where master is newer
    our @Files4Archive;    # List of files where copy is newer than master

    my @Offset = ( 35, 6, 11 );    # Name   Size Date   Size Date
    my @Gap = ( 3, 1 );            #      0     1     0     1
    my $Next_Col = $Offset[1] + $Gap[1] + $Offset[2];
    #$Dir1 =~ s/\/$//;  #Don't completely understand, but appears to be an extra / in base path
    				   # if I remove in ptdisty::setvar, push path fails
    my ( @Files1, @Files2 );    # !!!WTF are these used for?
    if (@Files) {
        foreach (@Files) {
            push @Files1, "$Dir1/$_";
            if ($opt_s && $WWW_Path ne '' && $Dir1 =~ /www/) {
            	push @Files2, "$WWW_Path$_";  # Modified for Site server WWW files
            	#print ("show file attr push @Files2, $WWW_Path$_\n");
            } else {
            	push @Files2, "$Dir2/$_";  # original JSW
            }
            	$FileList{$_} = 1;
        }
    }
    else {
    	@Files1 = &Show_Files_Attrs__Get_Files($Dir1);
        @Files2 = &Show_Files_Attrs__Get_Files($Dir2);
    }

    unless ($Quiet) {

        print '_' x 110, "\n\n";

#        my $Msg = ($ChkSumIt) ? 'ON!' : 'disabled (force copy!)';
#        print "\nCopy on \'same-size \/ checksum-fail only\' is $Msg\n\n";

        my $GapStr = ();
        foreach (@Gap) {
            push @GapStr, ' ' x $_;
        }

        #                &PETC(">$GapStr[0]<, >$GapStr[1]<" );
        #                &PETC(($Gap[0] + $Next_Col)*2);

        print &Pad( 'System hostname:', $Offset[0], ' ', 2 ),
              $GapStr[0], $ENV{'HOSTNAME'}, "\n";
        print &Pad ('Search Path:', 35, ' ', 2), '   ', $Dir2;


        print "\n";

        print "\n", '_' x $Offset[0], "\n";

        print &Pad( 'Master Path:', $Offset[0], ' ', 2 ), $GapStr[0],
              'V' x $Next_Col,
              '-' x ($Gap[0] * 2 + $Next_Col), $Dir1, "\n";

        print &Pad( 'Copy Path:', $Offset[0], ' ', 2 ), $GapStr[0],
              ' ' x ($Gap[0]  + $Next_Col),
              'V' x $Next_Col,
              '-' x $Gap[0], $Dir2, "\n";

        &Show_Files_Attrs__Bars ($Offset[0], $GapStr[0], $Next_Col);

        #  &Pad( $Dir1, $Next_Col ), $GapStr[0], &Pad( $Dir2, $Next_Col ), "\n";

        print &Pad( 'FileName', $Offset[0]), $GapStr[0],
          &Pad( 'Size', $Offset[1] + $Gap[1] ),
          &Pad( 'Date', $Offset[2] + $Gap[0] ),
          &Pad( 'Size', $Offset[1] + $Gap[1] ),
          &Pad( 'Date', $Offset[2] + $Gap[0] ), "\n";

        &Show_Files_Attrs__Bars ($Offset[0], $GapStr[0], $Next_Col);
#        print '_' x $Offset[0], $GapStr[0], '_' x $Offset[1], $GapStr[1],
#          '_' x $Offset[2], $GapStr[0], '_' x $Offset[1], $GapStr[1],
#          '_' x $Offset[2], "\n";
    }

    # Compare each file ...
    my $Name;
    foreach $Name( sort keys %FileList ) {

        my $Msg   = '';

        my ( $Date1, $Size1, $DS1, $MIA1 ) = &Get_File_Stats("$Dir1/$Name");

        my $Name2 = $Name;
        my $Dir_2 = $Dir2;
        my ($D1,$F1) = split /\//, $Name;     # Dest only
        next if $D1 eq 'tftpboot' ; #and ! $Verbose;  # Added JW - Skip showing tftp

        if ($D1 eq 'cfgfiles') {
            $Name2 = $F1;
            $Dir_2 =~ s/\/\w{1}$//;            # Remove the release pipe
        }
        if ($D1 eq 'www' and $WWW_Path ne '') {
            $Dir_2 = $WWW_Path;            # We have alread remove release pipe, change DIR2 to /
            $Dir_2 =~ s/www\/$//i;            # Remove WWW
        }
        my ( $Date2, $Size2, $DS2, $MIA2 ) = &Get_File_Stats("$Dir_2/$Name2");

        my $SizeDiff = $Size1 - $Size2;
        $Size2 = '' unless $SizeDiff;     # No need to reprint it!

        my $Age = $Date1 - $Date2;            # +ve if master (1st) is newer
        $Age   = 0 if 2 > $Age and $Age > -2; # A 1 sec diff	 on identical files!

        my $NotTheSame = ( $SizeDiff or $Age ) ? 1 : 0;
        my $MIA = ($MIA1 or $MIA2) ? 1 : 0;

        if ( $MIA ) {
            $Msg .= 'MIA';
#        &PETC ("$Date1, $Size1, $DS1, $MIA1, $Date2, $Size2, $DS2, $MIA2");

        }
        elsif ($NotTheSame and !$SizeDiff) { # different Dates only

             if ($ChkSumIt and
                 &File_Checksum ("$Dir1/$Name") ==
                 &File_Checksum ("$Dir2/$Name2")) {
                   $Msg .= '(CS passed!)' if $ChkSumIt;
                   $NotTheSame = 0;
             }
             else {
                 $Msg .= 'CS failed!' if $ChkSumIt;
                 $DS2 = '' unless $Age;      # No need to reprint it!
             }


        }

        if ($NotTheSame) {

            unless ($MIA1) {

                push @Files4Update, $Name;
                push @cp_args, "$Dir1/$Name $Dir2/$Name2";
            }
            if ( $Age > 0 ) {   # The Master has been updated
                $Msg .= '*';
            } else {
                $Msg .= '*' x 10;
                push @Files4Archive, "$Dir2/$Name2";
            }
        }

        my $Str = &Pad( $Name2, $Offset[0]) . $GapStr[0] ;    # Name
        $Str .= &Pad( $Size1, $Offset[1], ' ', 2 ) . $GapStr[1];
        $Str .= &Pad( $DS1, $Offset[2] ) . $GapStr[0];
        if ($NotTheSame or $MIA2) {
            $Str .= &Pad( $Size2, $Offset[1], ' ', 2 ) . $GapStr[1]
              . &Pad( $DS2, $Offset[2] ) . "  <-! $Msg";
        }
        elsif ($Age and !$SizeDiff) {      # Must have passed the chksum!
            $Str .= 'ok'. ' ' x ($Offset[1] - 1) . &Pad( $DS2, $Offset[2] );
        }
        else {
#            $Str .= "\t/-/";
#            $Str .= "\t\< \"";
            $Str .= "ok";
        }

        print "$Str\n" unless $Quiet;

        if ($Debug2) {
            print "\n", "\tName1 \t= $Name\n", "\tName2 \t= $Name2\n",
              "\tMIA1 \t= $MIA1\n", "\tMIA2 \t= $MIA2\n",
              "\tDate1\t= $Date1\n", "\tDate2\t= $Date2\n", "\tAge  \t= $Age\n",
              "\tSize1\t= $Size1\n", "\tSize2\t= $Size2\n",
              "\tSDiff\t= $SizeDiff\n", "\t\!Same\t= $NotTheSame\n";
            &PETC();
        }
    }
    &Show_Files_Attrs__Bars ($Offset[0], $GapStr[0], $Next_Col);
}


sub Show_Files_Attrs__Bars {

    my ($Offset, $GapStr, $Next_Col) = @_;

    print '_' x $Offset, $GapStr, '_' x $Next_Col, $GapStr,
          '_' x $Next_Col, "\n";
}

sub Show_Files_Attrs__Get_Files {

    my ($Path) = @_;

    @File_List = ();
    my @New_List = ();
    &File_List($Path);
    foreach (@File_List) {    # $Path/the/file.txt -> the/file.txt
        my $FNwoPath = substr( $_, length($Path) + 1 );
        push @New_List, $FNwoPath;
        $FileList{$FNwoPath} = 1;  # !!!WTF
    }

    return (@New_List);
}

sub xShow_Files_Attrs__Sub_File_Name {

    my ($Dir, $MyName) = @_;
    my $Old_Name = $MyName;

    if (!-f "$Dir/$MyName") {              # Try any known substitutions

         my ($D1,$F1) = split /\//, $MyName;     # Because .xxxrc files are buried
         $MyName = $F1 if $D1 eq 'cfgfiles';
#         $MyName = &fnstrip ($MyName, 2) if &fnstrip ($MyName, 8) eq 'pl';
    }
    &Print2XLog ("Dir=$Dir, Old=$Old_Name, New=$MyName", 1) if $Old_Name ne $MyName;
    return $MyName;
}

#_______________________________________________________________________________
1;
