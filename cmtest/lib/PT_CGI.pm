################################################################################
#
# Module:      PT_CGI.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      Subs associated with query forms and log files
#
# Version:    (See below) $Id: PT_CGI.pm,v 1.3 2008/02/21 00:00:27 joe Exp $
#
# Changes:
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
my $Ver= 'v1.1 1/31/2008'; # Updated versioning
my $CVS_Ver = ' [ CVS: $Id: PT_CGI.pm,v 1.3 2008/02/21 00:00:27 joe Exp $ ]';
$Version{'PT_CGI'} = $Ver . $CVS_Ver;
#____________________________________________________________________________
#In module ModuleName.pm:
#
package PT_CGI;
require Exporter;
use strict;

require Exporter;
our @ISA = qw(Exporter);

our @EXPORT_OK = qw(Show_Stats);

#use CGI qw(:standard);
#use File;        # (fnstrip)
#use Logs;

use PTML qw ( Body Debug Comment PrintLog );
#use PT qw ( PT_Date );


#_______________________________________________________________________________
sub Show_Stats {      # Called by cgi's: status and summary

    my ($Head, $Version, $Info) = @_;

#1
    my $Type = ($0 =~ /summary/) ? 1 : 0;

    our $Stats_Path   = '/var/local/cmtest/stats';
    opendir (DIR, $Stats_Path) or
       die "Can't open Stats File Path $Stats_Path";

    &PTML::Head ($Head);

#!!! ??? why does this barf???    my $Now = &PT::PT_Date (time, 1);
    my $Now = &PT_Date (time, 1);

    &PTML::Body ("<H1 ALIGN=\"CENTER\">Production Test Status</H2>");
    &PTML::Body ("<H2 ALIGN=\"CENTER\">Last updated: $Now</H2>");
    &PTML::Debug ("CGI Ver: $Version");

    &PTML::Comment ("CGI Ver: $Version");
    &PTML::Comment ("Arg=$Info");
#        &PTML::Body ("<P> Arg=$Info </P>");

    my ($Stats_File);
    foreach $Stats_File (readdir(DIR)) {

        unless (($Stats_File eq '.') ||
                ($Stats_File eq '..') ||
                ($Stats_File eq 'system') ||
                (-d $Stats_File)) {

            &PrintLog ("PT_CGI::Show_Stats: $Stats_File");
            # Note: Each main (status.cgi and summary.cgi) each have their own!
            &main::Show_Stats_File ($Stats_File);

        }

    }

    closedir (DIR);

    return;
}



# Copied (less POD) from PT ...

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
sub PT_Date {

    my ( $Time, $Type ) = @_;
    my @Date_Str;

    my ( $Nsec, $Nmin, $Nhour, $Nmday, $Nmon, $Nyear, $Nwday, $Nyday, $Nisdst ) =
      localtime($Time);

    $Nmon++;    # Base [0] to month
    $Nyear = 1900 + $Nyear;
    $Nsec  = &Pad( $Nsec, 2, '0', 2 );
    $Nmin  = &Pad( $Nmin, 2, '0', 2 );
    $Nhour = &Pad( $Nhour, 2, '0', 2 );
    $Nmday = &Pad( $Nmday, 2, '0', 2 );
    $Nmon  = &Pad( $Nmon, 2, '0', 2 );

    $Date_Str[0] = "$Nyear/$Nmon/$Nmday $Nhour\:$Nmin";
    $Date_Str[1] = "$Nmon/$Nmday $Nhour\:$Nmin";
    $Date_Str[2] = $Date_Str[1] . ":$Nsec";
    $Date_Str[6] = "$Nmon/$Nmday/" . substr( $Nyear, 2, 2 );
    $Date_Str[8] = "$Nyear-$Nmon-$Nmday";                      #New!
    $Date_Str[9] = "$Nyear$Nmon$Nmday\.$Nhour$Nmin$Nsec";

    return ( $Date_Str[$Type] );
}

1;
