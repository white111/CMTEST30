################################################################################
#
# Module:      PT_Query.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      Subs associated with query forms and log files
#
# Version:    (See below) $Id: PT_Query.pm,v 1.4 2010/03/12 18:50:59 joe Exp $
#
# Changes:    v9r2 - 08/23/05   Now uses PTML::Print_Log
#			  V10.0  Updates to support ubuntu apache
#
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
# Notes:
#  			event_query.cgi -> &Main_Event_Query -> &Event_Query_Search
#  			matrix.cgi      -> &Main_Show_Matrix
#  			status.cgi      -> &Read_Stats_Dir  -> {foreach} &Read_Stats_File
#  			stats.cgi       -> &Read_Stats_File
#  			summary.cgi     -> &Main_Show_Summary -> &Sort_Stats_File
#                       -> &Sort_Stats_Data -> &Stats_File_Summary
#
################################################################################
my $Ver= '10.1 3/8/2010'; # Ubuntu 9.10 support
my $CVS_Ver = ' [ CVS: $Id: PT_Query.pm,v 1.4 2010/03/12 18:50:59 joe Exp $ ]';
$Version{'PT_Query'} = $Ver . $CVS_Ver;
#_____________________________________________________________________________
#package PT_Query;
#use strict;
#use CGI::Carp qw(fatalsToBrowser);

use CGI qw(:standard);
use File;        # (fnstrip)
use Logs;
use PT;        # (PT_Date
use PTML qw ( PrintLog );
use Stats;

#_______________________________________________________________________________
sub Event_Query_Search {

warn "LogPath = >$LogPath<";

    open (FH, "<$LogPath/Event.log") or die "Can\'t open Event log";

        # 0 1    2        3      4    5       6         7      8      9    10
        # 1;Date;Location;HostID;OpID;Part_No;Serial_No;TestID;Result;Data;LogFilePtr;

    &PTML::Debug ("File open! <BR> Serial No = $Serial_No<BR>");
    &PTML::Table_Head qw( Location Date Test_ID Serial_No Result Version Log_File );

    my $i = 0;
    my $j = 0;
    while (<FH>) {

        my $Msg = '';

        $i++;
        my ($RecType, $Date, $Location, $HostID, $OpID, $PN, $SN, $TestID, $Result, $Data, $LogFileP) = split (/\;/);

        next if $RecType != 1;

        my $Version = '';
        my $Var_Val;
        $Msg = "$Data\n";
        foreach $Var_Val (split /,/, $Data) {
            $Msg .= "Var_Val = $Var_Val";
            my ($Var, $Val) = split /=/, $Var_Val;
            $Msg .= ", Var = $Var, Val = $Val";
            my ($Which, $Ver) = split /_/, $Var;
            ($Val) = split /---/, $Val if $Which eq 'Diag';
            $Msg .= ", Which = $Which, Ver = $Ver";
            $Version = "$Which=$Val" if $Ver eq 'Ver';
        }


        unless ($Serial_No eq '') {
                next if $SN !~ /$Serial_No/;
        }

        my $OK = 0;
        foreach $TID (@TIDs) {

                $OK = 1 if $TestID eq $TID;
        }
        next unless $OK;

        $j++;

#        $BG_Color = $BG_Color_Def;
#        $BG_Color = $Fail_Color    if $Result eq 'FAIL';
#        $BG_Color = 'lime'         if $Result eq 'OK';
#        $BG_Color = $Pass_Color    if $Result eq 'PASS';
        $BG_Color_Ptr = 0;
        $BG_Color_Ptr = 1 if $Result eq 'PASS';
        $BG_Color_Ptr = 2 if $Result eq 'FAIL';


        my $Log_File = "$LogPath/logfiles/$LogFileP";
        my $HRef = (-f $Log_File) ? "<A HREF=file2html.cgi?File=$Log_File>" : '';

        &PTML::Table_Row ( $Location,
                           &PT_Date ($Date,1),
                           $TestID,
                           "<A HREF=event_query.cgi?Serial_No=$SN>$SN",
                           $Result,
                           $Version,
                           $HRef . $LogFileP
                         );

        $Msg .= ", version = $Version";
#        &Print_Log ($Msg, 0);
    }
    close FH;

    &Print_Log ("$j out of $i recs matched");
    &PTML::Body ("<H3>Results: $j out of $i recs matched</H3>");
    &PTML::Table_Tail ();

}

#_______________________________________________________________________________
sub Init {

     our $Debug           = 0;
     our $Show_Defunct    = 0;

     our $LogPath         = '/var/local/cmtest/logs';
     our $Stats_File_Path = '/var/local/cmtest/stats';

     #orig Fedora install
     #our $Log_File        = '/var/log/httpd/cgi.log';
     #our $XLog            = '/var/log/httpd/cgix.log';
     #Fedora or Ubuntu install
     our $Log_File        = '/var/log/appache2/cgi.log';
     our $XLog            = '/var/log/appache2/cgix.log';
     if (-d '/var/log/appache2' ) {
     	$Log_File        = '/var/log/appache2/cgi.log';
     	$XLog            = '/var/log/appache2/cgix.log';
     } else {
     	$Log_File        = '/var/log/httpd/cgi.log';
     	$XLog            = '/var/log/httpd/cgix.log';
     };

     our $Stats_Path      = '/var/local/cmtest/stats';
     our $OldAge          = 1 * 60 * 60;        # 1 hour

     my $Main = &fnstrip ($0,7);

     &PTML::Init_CGI;

#        $BG_Color = $BG_Color_Def;
#        $BG_Color = $Fail_Color    if $Result eq 'FAIL';
#        $BG_Color = 'lime'         if $Result eq 'OK';
#        $BG_Color = $Pass_Color    if $Result eq 'PASS';

     our ($Indent) = 0;                # Indentation for html code

     opendir (DIR, $Stats_Path);

     our %Location = ();
     our %Product_ID = ();
     our %Result = ();
     our %Started = ();
     our %Status = ();
     our %Test_ID = ();

     &Rotate_Log ($XLog, 10);
     &Print_Log ("Starting $Main at " . &PT_Date(time, 2));

     open (LOG, ">$XLog") || die "Can\'t init log $XLog";
     print LOG "Starting $Main version ",
           &PT_Query_Version,
           ' at ', &PT_Date(time, 2), "\n";

     if (1) {
          print LOG "Includes:\n";
          foreach (sort keys %INC) {
              print LOG "\t$INC{$_}\n";
          }
          print LOG "Args:\n";
          foreach (@ARGV) {
              print LOG "\t$_\n";
          }
          print LOG "params:\n";

          foreach (param()) {
              print LOG "\t$_\=", param($_), "\n";
          }
          print LOG "\n";
     }
     close LOG;

}

#_______________________________________________________________________________
sub Main_Event_Query {  #Called by Event_Query.cgi, Display the Event
                        # Query Form, then run &Event_Query_Search ...


    our ($Serial_No) = param ('Serial_No');
#    our @TIDs = ('DIAGS', 'BI', 'TC', 'ORT', 'FACTORY_DEF', 'SYSTEST', 'QTEST', 'EEPROM');
    our @TIDs = ('FCT', 'BI', 'TC', 'ORT', 'DEMO', 'SYSTEST');

    &Print_Log ("1)Serial_No=$Serial_No");

    my $Title = 'Event Log Query';

    print header;

    if ($Serial_No ne '') {   # Don't define the form yet

        print h1($Title),
              h2("Serial No =  $Serial_No"),
              hr;

        &Event_Query_Search;

    } else {

    print start_html($Title),
        h1($Title),
        start_form,
        "Product Serial No? ",textfield('Serial_No'),
        p,
        "Include what tests (TID)?      ",
#        p,
        checkbox_group(-name=>'TIDs',
                       -values=>[@TIDs],
                       -defaults=>['FCT','BI','TC','ORT']),
        p,
        "Sort by? ",
        popup_menu(-name=>'Sort_By',
                   -values=>['TID','Location','Date','Result','Other']),
        '[WIP feature]',
        p,
        submit,
#        reset,
        end_form,
        hr;


         if (param()) {                 # param() = number of parameters passed from form

             (@TIDs) = param ('TIDs');
             ($Serial_No) = param ('Serial_No');
             ($Sort_By) = param ('Sort_By');

             &Event_Query_Search;
         }
    }

    print end_html;

}

#_______________________________________________________________________________
sub Main_File2HTML {

    our ($File) = @_;

    my $Msg;

    &Print_Log ("File=$File");

    my $Title = 'File Viewer';

    &PTML::Head ($Title);

    &PTML::Body ("<H1 ALIGN=\"LEFT\">File: $File</H2>");

    if (&fnstrip ($File, 8) eq 'xml') {
        $Msg = 'It\'s an XML file!';
        if (-f $File) {
#            `cat $File`;
#            print "</Test>";
        } else {
            &Print_Log ("File $File doesn\'t exist");
        }
    } else {
        $Msg = 'It\'s a ' . &fnstrip ($File, 8) . 'file!';
    }

    open (IN, "<$File") or die "can\'t open file $File";
    print '<P></P>',"\n</CENTER><LEFT>\n";
    while (<IN>) {
            chomp;
            print "<BR>$_\n";
    }
    close IN;
    print '<P></P>',"\n</LEFT><CENTER>\n";

    &Print_Log ($Msg);
    &PTML::Tail ();

}

#_______________________________________________________________________________
sub Main_Show_Matrix {

     my ($Stats_File) = param('Stats_File');

     my $Version = &PT_Query_Version;

     &PTML::Head ('Production Test Status Summary Matrix');

     my $Now = &PT_Date (time, 1);

     &PTML::Body ("<H1 ALIGN=\"CENTER\">Production Test Status Summary Matrix</H2>");
     &PTML::Body ("<H2 ALIGN=\"CENTER\">Last updated: $Now</H2>");
     &PTML::Debug ("CGI Script $Main - version $Version");

     &PTML::Comment ("CGI Script $Main - version $Version");
     &PTML::Comment ("Arg=$Info");
#        &PTML::Body ("<P> Arg=$Info </P>");

    if ($Stats_File eq '') {

          foreach $Stats_File (readdir(DIR)) {

             unless (($Stats_File eq '.') ||
                    ($Stats_File eq '..') ||
                    ($Stats_File eq 'system') ||
                    (-d $Stats_File)) {

                 &Sort_Stats_File ($Stats_File);
             }

          }

          closedir (DIR);

          my $Count = (keys %TimeStamp);
          &PTML::Debug ("Found $Count active tests");

          &Sort_Stats_Fake_Data_4Demo unless $Count;
     } else {
         &Sort_Stats_File ($Stats_File);
     }

     &Stats_File_Summary;  # Print the data

     &PTML::Tail ();

}

#__________________________________________________________________________
sub Main_Show_Summary {

    my $Version = &PT_Query_Version;

        &PTML::Head ('Production Test Status Summary');

        my $Now = &PT_Date (time, 1);

        &PTML::Body ("<H1 ALIGN=\"CENTER\">Production Test Status Summary</H2>");
        &PTML::Body ("<H2 ALIGN=\"CENTER\">Last updated: $Now</H2>");
        &PTML::Debug ("CGI Script $Main - version $Version");

        &PTML::Comment ("CGI Script $Main - version $Version");
        &PTML::Comment ("Arg=$Info");
#        &PTML::Body ("<P> Arg=$Info </P>");

        my ($Stats_File);
        foreach $Stats_File (readdir(DIR)) {


                unless (($Stats_File eq '.') ||
                        ($Stats_File eq '..') ||
                        ($Stats_File eq 'system') ||
                        (-d $Stats_File)) {

                        &Sort_Stats_File ($Stats_File);
                }

        }

        closedir (DIR);

        my $Count = (keys %TimeStamp);
        &PTML::Debug ("Found $Count active tests");

        &Sort_Stats_Fake_Data_4Demo unless $Count;
        &Stats_File_Summary;

        &PTML::Tail ();

}

#_____________________________________________________________________________
sub Read_Stats_Dir {

    &Print_Log ("Opening stats directory $Stats_Path");
    opendir (DIR, $Stats_Path)|| die "Can't open stats dir $Stats_Path";


    my $Now = &PT_Date (time, 1);
    &PTML::Head ('Production Test Status');

    &PTML::Body ("<H1 ALIGN=\"CENTER\">Production Test Status</H2>");
    &PTML::Body ("<H2 ALIGN=\"CENTER\">Last updated: $Now</H2>");
    &PTML::Debug ("CGI Script $Main - version $Version");

    &PTML::Comment ("CGI Script $Main - version $Version");
    &PTML::Comment ("Arg=$Info");

    my ($Stats_File);
    foreach $Stats_File (readdir(DIR)) {

        unless (($Stats_File eq '.') ||
               ($Stats_File eq '..') ||
               ($Stats_File eq 'system') ||
               (-d $Stats_File)) {

            &Read_Stats_File ($Stats_File, $Show_Defunct, 1);
        }

    }

    closedir (DIR);

#        &PTML::Colors;

     &PTML::Tail ();
     exit;
}

#_____________________________________________________________________________
sub Read_Stats_File {     #Read and render 1 stats file

     my ($Stats_File, $Show_All, $Show_UUT_ID) = @_;

     %Stats =();
     %TestData =();
     %Globals =();

     my $Key;
     my $Defunct = 0;

     &Stats::Read ("$Stats_File_Path/$Stats_File");

     $BG_Color = $BG_Color_Def;
     $BG_Color = $Fail_Color    if $Stats{'Result'} eq 'FAIL';
     $BG_Color = 'lime'        if $Stats{'Result'} eq 'OK';
     $BG_Color = $Pass_Color    if $Stats{'Result'} eq 'PASS';

     &Print_Log ("Stats_File=$Stats_File");

     $Defunct = 1 if time - $Stats{'Updated'} > $OldAge;

     if ($Defunct) {
         $Stats{'Status'} = 'Defunct';
         return unless $Show_All;
     }

     &PTML::Head ('');
     &PTML::Body ("<P><HR></P>");
     &PTML::Body ("<H2 ALIGN=\"LEFT\">" . &fnstrip ($Stats_File,7) . ":</H2>")
         if $Show_UUT_ID;
     &PTML::Body ("<H3 ALIGN=\"CENTER\">Stats:</H3>");
     &PTML::Table_Head qw( Parameter Value );

     &Print_Log ("UUT=$Stats{'UUT_ID'}");

     foreach $Key (sort keys %Stats) {

          unless ($Stats{$Key} eq '') {

               $Stats{$Key} = &PT_Date ($Stats{$Key},1) if
                       $Key =~ /ECT|TimeStamp|Updated/;

               &PTML::Table_Row ( $Key, $Stats{$Key} );
         }
     }
     &PTML::Table_Tail ();

     &PTML::Body ("<H3 ALIGN=\"CENTER\">Test Data:</H3>");
     &PTML::Table_Head qw( Parameter Value );

     foreach $Key (sort keys %TestData) {

          $TestData{$Key} = &PT_Date ($TestData{$Key},1) if
                  $TestData{$Key} and $Key =~ /TOLF/;

          $PTML::TD_Desc{$Key} = $Key if $PTML::TD_Desc{$Key} eq ''; # Just in case
          &PTML::Table_Row ( $PTML::TD_Desc{$Key}, $TestData{$Key} ) unless
                  $TestData{$Key} eq '';
     }
     &PTML::Table_Tail ();
     &Print_Log ("Finished \&Read_Stats_File for $Stats_File");
}

#_______________________________________________________________________________
sub Sort_Stats_Data {  # Decide if this particular stat files will be displayed

     my ($Stats_File, $Demo) = @_;

     my $Delta = time - $Stats{'Updated'};
     my $Defunct = ($Delta > $OldAge) ? 1 : 0;

#        &PTML::Debug ("Updated = $Stats{'Updated'}, Delta = $Delta, Defunct=$Defunct");
     if ($Defunct and ! $Demo) {
             $Stats{'Status'} = 'Defunct';
              return unless $Show_Defunct;
     }
#        &PTML::Debug ("File = $Stats_File - Not Defunct!!!");

     return if &fnstrip ($Stats_File,7) ne $Stats{'UUT_ID'};        # Dont show the tmp 'host-PID' files

#        &PTML::Debug ("Still there !!!");

     my $Key = $Stats{'UUT_ID'};
     my $Which = ($TestData{'TID'} eq 'DIAGS') ? 'Diag' : 'SW';

     $Location{$Key}   = $Stats{'Host_ID'} . '-' . $Stats{'Session'};
     $Product_ID{$Key} = $Stats{'UUT_ID'};
     $Result{$Key}     = $Stats{'Result'};
     $Started{$Key}    = $Stats{'Started'};
     $Status{$Key}     = $Stats{'Status'};
     $Test_ID{$Key}    = $TestData{'TID'};
     $TimeStamp{$Key}  = $Stats{'TimeStamp'};
#       ($Version{$Key}, $Foo)   = split /\s*/, $TestData{'Diag_Ver'};  # 1st word only
     $Version{$Key}    = $TestData{'Diag_Ver'};
     $Version{$Key}    = $TestData{'SW_Ver'} if
                                   $TestData{'TID'} =~ /FACT/;

     $Version{$Key}    = "$TestData{'Ver'} / $Version{$Key}";

     $Result{$Key} = '' if $Result{$Key} eq 'INCOMPLETE' and
                           $Status{$Key} eq 'Running';

     &Print_Log ("Key=$Key, Which=$Which, Location=$Location{$Key}, TID=$Test_ID{$Key}, Product_ID=$Product_ID{$Key}, Started=$Started{$Key}, Status=$Status{$Key}, Result=$Result{$Key}");

}
#_____________________________________________________________________________
sub Sort_Stats_Fake_Data_4Demo {        # A fake &Sort_Stats_File for demo purposes

        &PTML::Body ("<H2 ALIGN=\"CENTER\">No Active Tests found! Example data:</H2>");

#                       Product_ID Result       Status   ACT      TID
        &Push_Stats qw( USSX001234 PASS         Finished 1200     BI   );
        &Push_Stats qw( USSX001235 FAIL         Running  5000     Test );
        &Push_Stats qw( USSX001236 FAIL         Running  1800     Diag );
        &Push_Stats qw( USSX001237 INCOMPLETE   Running  25000    Systest );
        &Push_Stats qw( USSX001238 INCOMPLETE   Running  3000     Test );

}
sub Push_Stats {                        # Basic data to appear as examples

        %Stats = (
                Host_ID    => 'Tester1',
                Session    => 'n',
                UUT_ID     => shift,
                Result     => shift,
                Status     => shift,
                TimeStamp  => time - shift,
        );

        $Stats{'Started'}    = &PT_Date($Stats{'TimeStamp'}, 1);

        %TestData = (
                TID => shift
        );

        &Sort_Stats_Data ($Stats{'UUT_ID'}, 1);
}

#_____________________________________________________________________________
sub Sort_Stats_File {    # Initialize the main hashes and read 1 stat file

        my ($Stats_File) = @_;

        %Stats =();
        %TestData =();
        %Globals =();
        &Stats::Read ("$Stats_File_Path/$Stats_File");

        &Sort_Stats_Data ($Stats_File, 0);
}

#_____________________________________________________________________________
sub Stats_File_Summary {

     my @Fields = qw( Location Started Test_ID Product_ID Version Status Result );

     &PTML::Table_Head (@Fields);

     foreach $System (sort keys %TimeStamp) {

          $BG_Color = $BG_Color_Def;
          $BG_Color = $Fail_Color    if $Result{$System} eq 'FAIL';
          $BG_Color = 'lime'         if $Result{$System} eq 'OK';
          $BG_Color = $Pass_Color    if $Result{$System} eq 'PASS';

          my $Stats_File = $System . '.txt';

          my %FLink = (
               Location   => "<A HREF=stats.cgi?Stats_File=$Stats_File>",
               Product_ID => "<A HREF=event_query.cgi?Serial_No=$System>"
          );

          delete $FLink{'Location'} if !-f "$Stats_File_Path/$Stats_File";
          &Print_Log ("FLink to $Stats_File deleted") if !-f "$Stats_File_Path/$Stats_File";

#Huh?          $FLink{'Status'} = "<A HREF=file2html?File=$Stats_File>"

          my @Data = ();
          my $Field;
          foreach $Field (@Fields) {
              my $Field_Data = $FLink{$Field} . ${$Field}{$System};
              push @Data, $Field_Data;
          }
          &PTML::Table_Row (@Data);
     }

     &PTML::Table_Tail ();
}
#____________________________________________________________________________________
1;
