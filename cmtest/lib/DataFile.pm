################################################################################
#
# Module:     DataFile.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#			 Joe White( mailto:joe@stoke.com )
#
# Descr:      Subs for ??
#
# Version:    (See below) $Id: DataFile.pm,v 1.6 2008/02/21 00:00:27 joe Exp $
#
# Changes:
#			my $CVS_Ver = ' [CVS: $Id: DataFile.pm,v 1.6 2008/02/21 00:00:27 joe Exp $ ]';
#   		$Ver = '1   - 2005-12-15'; # Pulled from PT.pm
#   		$Ver = '1.1 - 2006-03-02'; # Make "Created by ..." a comment!
#   		$Ver = '1.2 - 2006-03-02'; # Implied type and opt cat/new for DataFile_Write
#			#CVS Version = 1.2
#    		$Ver = '1.2.1';  # 03-02 Different -re for Read
#    		$Ver = '1.2.2';  # 03-03 (yet another) Different -re for Read
#    		$Ver = '1.2.4';  # 03-06 SetKey, fixed error handling bug in DataFile_Read
#    		$Ver = '1.2.5a - 2006-03-09'; # try creating globals on the fly
#    		$Ver = '1.2.6  - 2006-06-15'; # Incorrect merge - check with diffs
#    		$Ver = '1.2.6a - 2006-06-27'; # Remove any leading white-space(s)
#			#CVS Version = 1.3
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
my $Ver= 'v1.2.7 1/31/2008'; # Updated versioning
my $CVS_Ver = ' [ CVS: $Id: DataFile.pm,v 1.6 2008/02/21 00:00:27 joe Exp $ ]';
$Version{'DataFile'} = $Ver . $CVS_Ver;

#_______________________________________________________________________________

our %WebData = ();
our @gBuf    = ();

#_______________________________________________________________________________
sub DataFile_Read_depreciated {       # Current version in PT.pM

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
        # print "DataFile - $.\n";

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
                } else {# It's a hash
                    return (3, '%' . $Label) if !defined %{$Label};
                    ${$Label}{$1} = $2;
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
sub Read_Data_File_depreciated {  #  Back to using verin in PT.pm JW 10/26/06# Replaces the version in PT.pm (un-packaged)
                      # Might have been written by &Write_Data_File (below)

    my ($File) = @_; # FullFileSpec::DataFile

    my ($Erc, $Data)  = &DataFile_Read ($File);

    return (0) unless $Erc;

    if ($Erc == 1) {
        &PrintLog ("Unable to read Data File $File");
        return (2);
    } elsif ($Erc) {
        &Exit ($Erc, "Attempt to load undefined var: $Data");
    }
}


#________________________________________________________________
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
sub Write_Data_File {  # Replaces the version in PT.pm (un-packaged)

    # &Write_Data_File (FullFS-File, [new|(cat)], [hash|list|scalar], VarName)
    #   Note: The array/hash must be a pre-declared global

    my ($Erc, $Data)  = &DataFile_Write (@_);
    if ($Erc == 2) {
        &PrintLog ("Unable to read Data File $Data");
        return (2);
    } elsif ($Erc) {
        &Exit ($Erc, "Attempt to write undefined var: $Data");
    }

    return (0);

}
#_______________________________________________________________________________

1;
