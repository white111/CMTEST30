################################################################################
#
# Script:    CMTest_CGI.pm
#
# Author:    Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:     Main entry from CMTest.cgi and all underlying subs
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1993 - 2005 Paul Tindle. All rights reserved.
#
################################################################################
sub Version { return ('v1.7.3  2007/01/11'); } #Common header
											   # Corrected #unless ($Erc) {   # Was JSW 01/11/07  in Event_Log_Search

#package CmTest_CGI;
#use strict;

#require Exporter;
#our @ISA = qw(Exporter);
#our @EXPORT_OK = qw(Get_Stats);

use CGI qw(:standard);
use PTML qw ( Body Comment Debug $Paint Table_Head Table_Row Table_Tail );
#use PT qw ( Cleanup) ;       #JSW
use Stats qw( %Stats %TestData %Globals );
use Logs;

=pod

    [was]

    summary.cgi, status.cgi
        &Show_Stats ( <title>, <version>, <info> )
            {print header}
            {readdir}
            foreach Stats File
                &Show_Stats_File [summary.cgi] or
                &Print_Stats_TestData_tables [status.cgi]
            }
        &Sort_Stats_Fake_Data_4Demo (if no real data )
        &Stats_File_Summary
        &Tail

    [now]

    &CM_Test_Main

        CGI::header

        ?param: Serial
            &Event_Log_Search (Serial)
            &Display_Event_Log {!NEW}
        ?param: ""
            &Query_Form -------------> [hyperlink -> &Event_Log_Search]

            &Get_Stats
                {print H1 , H2}
                {open & readdir}
                foreach Stats File
                    &Load_Stats_File
                }
            &Sort_Stats_Fake_Data_4Demo (if no real data )
            &Stats_File_Summary ---------------> [hyperlink -> &Event_Query]
                &Stats_File_Summary_Table ( Active )
                &Stats_File_Summary_Table ( Recent )
                &Stats_File_Summary_Table ( Defunct )

        CGI::end_html

    [hyperlinks]
        &Print_Stats_TestData_tables
        &Event_Query


=cut

#_______________________________________________________________________________
sub CM_Test_Main {  #  CMTest.cgi entry

    &Init;
    #&Rotate_Log ($LogFile, 10); # Added JSW  rotate /var/www/cgi.log
    print header,   # Content-Type: text/html
          start_html ("$OEM - Production Test");

          # %Param is defined in Init;

    if ( $Param{'Type'} eq 'show') {
        my $URL = 'file://' . $Param{'File'};
        &PrintLog("CM_Test_Main::Show->URL=$URL");
#    print $query->redirect(-uri=>'http://somewhere.else/in/movie/land',
#        print redirect ($URL);
        &File2HTML;

    } elsif ( $Param{'Type'} eq 'status') {
        &Floor_Status;

    } elsif ( $Param{'Type'} eq 'Stats') {  #prints stats from a  file passed into function
        &Print_Stats_TestData_tables ($Param{'Stats_File'});

    } elsif ( $Param{'Type'} eq 'Stats_all') {
    	$Show_Defunct = 1; # override init
        &Stats_Show;

    } elsif ( $Param{'Type'} eq 'Stats_active') {
    	$Show_Defunct = 0; # override init
        &Stats_Show;

    } elsif ( $Param{'Type'} eq 'Search') {
        &Query_Form;

    } else {
        &Query_Form;
        &Floor_Status;
    }

    print end_html;
    exit;

}

#_______________________________________________________________________________
sub Event_Log_Search {  # Called by Query_Form->Action->search

    &PrintLog ("Starting Event_Log Search for $Serial_No [All=$All, Show?=$Show_UnIDd]");

    our @SN_Masks  = ($Serial_No);
    my ($Erc, $Msg) = &Cfg_Events ($Logs_Path,1);

    my $cRecs = @Event_Recs;
    $Msg = "Found $cRecs records";
    &PrintLog ($Msg);
    #unless ($Erc) {   # Was JSW 01/11/07
    if ($Erc eq 2) {
        &Body ("<H3>No Records found ERC=$Erc!</H3>");
        return;
    }

    &Table_Head qw( Location Date Test_ID Serial_No Result Log_File );

    foreach (@Event_Recs) {
#        my ($RecType, $Date, $Location, $HostID, $OpID, $PN, $SN, $TestID, $Result, $Data, $LogFileP) = split (/\;/);
        my ($Date, $Location, $SN, $TestID, $Result, $LogFileP) = split (/\;/);
        my $Log_File = "$Logs_Path/logfiles/$LogFileP";
        my $Log_File_Ref = ($LogFileP eq '') ? '' : "$LogFileP (MIA!)";
        if (-f $Log_File) {
            my ($TooBig, $Brace) = &Check_File_Size ($Log_File, 5000000);
            $Log_File_Ref = (!$TooBig)
                ? "<A HREF=$URL?Type=show;File=$Log_File>$LogFileP</A> $Brace"
                : "$LogFileP $Brace";
        }

        $Paint = $BG_Color{$Result};
                                           #Changed to display the year JSW
        &Table_Row ( $Location,
                     &PT_Date ($Date,0),
                     $TestID,
                     "<A HREF=$URL?Serial_No=$SN>$SN</A>",
                     $Result,
#                           $Version,
                     $Log_File_Ref
        );
    }

    &Table_Tail ();

    &Body ("<H3>$Msg</H3>");

}

#_______________________________________________________________________________
sub Event_Log_Search_old {  # Called by Query_Form->Action->search

    open (FH, "<$Logs_Path/Event.log") or die "Can\'t open Event log";

        # 0 1    2        3      4    5       6         7      8      9    10
        # 1;Date;Location;HostID;OpID;Part_No;Serial_No;TestID;Result;Data;LogFilePtr;

    &PrintLog ("File open! - Serial No = $Serial_No, All=$All, Show?=$Show_UnIDd",1);
#    &Table_Head qw( Location Date Test_ID Serial_No Result Version Log_File );
    &Table_Head qw( Location Date Test_ID Serial_No Result Log_File );

    my $i = 0;
    my $j = 0;
    while (<FH>) {

        my $Msg = '';

        $i++;
        my ($RecType, $Date, $Location, $HostID, $OpID, $PN, $SN, $TestID, $Result, $Data, $LogFileP) = split (/\;/);

        next if $RecType != 1;

        my $Version = '';
        my $Var_Val;
        $Msg = "$Data:\t";
        foreach $Var_Val (split /,/, $Data) {
            $Msg .= "Var_Val = $Var_Val";
            my ($Var, $Val) = split /=/, $Var_Val;
            $Msg .= ", Var = $Var, Val = $Val";
            my ($Which, $Ver) = split /_/, $Var;
            ($Val) = split /---/, $Val if $Which eq 'Diag';
            $Msg .= ", Which = $Which, Ver = $Ver";
            $Version = "$Which=$Val" if $Ver eq 'Ver';
        }

        unless ($Serial_No eq '') {   # Not passed via the form or the script
            next if $SN !~ /$Serial_No/;
        }

         # or $Show_UnIDd) {
        #&PrintLog($Msg);

        unless ($All) {
            my $OK = 0;
            my $TID;
            foreach $TID (@TIDs) {

                    $OK = 1 if $TestID eq $TID;
            }
            next unless $OK;
        }

        next if $SN eq '' and !$Show_UnIDd;

        $j++;

        my $Log_File = "$Logs_Path/logfiles/$LogFileP";
        my $Log_File_Ref = ($LogFileP eq '') ? '' : "$LogFileP (MIA!)";
        if (-f $Log_File) {
            my ($TooBig, $Brace) = &Check_File_Size ($Log_File, 5000000);
            $Log_File_Ref = (!$TooBig)
                ? "<A HREF=$URL?Type=show;File=$Log_File>$LogFileP</A> $Brace"
                : "$LogFileP $Brace";
        }

        $Paint = $BG_Color{$Result};

        &Table_Row ( $Location,
                     &PT_Date ($Date,1),
                     $TestID,
                     "<A HREF=$URL?Serial_No=$SN>$SN</A>",
                     $Result,
#                           $Version,
                     $Log_File_Ref
        );
    }
    close FH;

    &PrintLog ("$j out of $i recs matched");
    &Table_Tail ();

    &Body ("<H3>Found $j records</H3>");

}

#_______________________________________________________________________________
sub File2HTML {

    my $File = $Param {'File'};

    my $Msg;

    &PrintLog ("File=$File");

    my $Title = 'File Viewer';
    my $Heading = "File: $File";

    &Body ("<H2 ALIGN=\"LEFT\">File: $File</H2>");

#    if (&fnstrip ($File, 8) eq 'xml') {
#        $Msg = 'It\'s an XML file!';
#        Have the browser render it instead (but we have illegal chars, so...
#            `cat $File`;
#            print "</Test>";
#     } else {
#        $Msg = 'It\'s a ' . &fnstrip ($File, 8) . 'file!';
#    }
#                                                 1G 1M 1K 1)
    my ($TooBig, $Brace) = &Check_File_Size ($File, 10000000);

    if ($TooBig) {
        $Msg = "File too big ($Size $Dim) to view";
        &PrintLog ($Msg);
        print "<H3>$Msg</H3>";
    } elsif (-f $File) {
        open (IN, "<$File") or die "can\'t open file $File";
        print '<P></P>',"\n</center><LEFT>\n";
        while (<IN>) {
            chomp;
            print "<BR>$_\n";
        }
        close IN;
        print '<P></P>',"\n</LEFT><center>\n";
    } else {
        $Msg = "File $File doesn\'t exist";
        &PrintLog ($Msg);
        print "<H3>$Msg</H3>";
    }
}

#_______________________________________________________________________________
sub Floor_Status {

    &PrintLog ("Mode = $Mode",1);
#    return unless $Mode eq '';

#    my $Now = &PT_Date (time, 1);
    my $Now = localtime();

    &Body ("<H2 ALIGN=\"center\">Production Test Status</H2>");
    &Body ("<H3  ALIGN=\"center\">Last updated: $Now</H3>");

    &Get_Stats (); # Open the Stat_Path directory and call &Read_Stats_File for each

    my $Count = (keys %Started);
    &PrintLog ("Found $Count Stats files");

    &Sort_Stats_Fake_Data_4Demo unless $Count;

    &Stats_File_Summary;

}

#_______________________________________________________________________________
sub Get_Stats {      # Called by cgi's: status and summary
                      #!!! -> Load_Stats_File called by CM_Test_Main

    opendir (DIR, $Stats_Path) or
       die "Can't open Stats File Path $Stats_Path";

    my ($Stats_File);
    foreach $Stats_File (readdir(DIR)) {

        unless (($Stats_File eq '.') ||
                ($Stats_File eq '..') ||
                ($Stats_File eq 'system') ||
                (-d $Stats_File)) {

            &PrintLog ("Opening stats file $Stats_File",2);
            &Load_Stats_File ("$Stats_Path/$Stats_File");
# or status.cfg would have called: Print_Stats_TestData_tables ("$Stats_Path/$Stats_File")

        }

    }

    closedir (DIR);

    return;
}

#_______________________________________________________________________________
sub Init {

    $| = 1;

    our $Debug       = 0;
    our $OEM         = 'Stoke';
    our $Recently    = 60 * 60 * 8; # 8 hours
    our $Logs_Path   = '/var/local/cmtest/logs';
    our $Stats_Path  = '/var/local/cmtest/stats';
    our $Background  = 'Stoke4.gif';
    our $Quiet       = 1; # (CGI!)

    our $URL         = 'CMTest.cgi';
    our ($Host_Name) = split /\./, $ENV{HTTP_HOST};

    our $Show_Defunct= ($Host_Name !~ /^mfg/) ? 1 : 0;
    our $Verbose     = ($Host_Name !~ /^mfg/) ? 3 : 0;

    if (defined $ENV{WINDIR}) {
        $Logs_Path   = 'X:/NAS-2/NAS/Tmp/cmtest.d/Log_arc/logs-2006-07-30';
        $Stats_Path  = 'X:/NAS-2/NAS/Tmp/cmtest.d/Log_arc/stats';
        $URL         = 'CMTest-win.cgi';
    }

       if (defined $Development) {
        $Logs_Path   = '//harp/joe/loglink/logs';
        $Stats_Path  = 'loglink/stats';
        $URL         = 'CMTest-win.cgi';
    }

    die "Can't write to log file $LogFile" if
        &PrintLog( '#' x 15 . "Starting CMTest.cgi - " . &Version . ' ' . '#' x 15);

    if ($Debug and 1) {
        &PrintLog ( "\%ENV dump:" );
        my $Key;
        foreach $Key (sort keys %ENV) {
            &PrintLog ( "\t$Key =\t$ENV{$Key}");
            print "\<\!-- $Key =\t$ENV{$Key} --\>\n";
        }
        &PrintLog ( "End [\%ENV dump]" );
        foreach $Key (sort keys %INC) {
            my $File = $INC{$Key};
            my $Old = int ( ( (-M $File) * 24 * 60) + 0.5); # Mins old
            &PrintLog ( $File, 1 ) unless $File =~ /perl/;
            &PrintLog ( "$File [$Old mins]\n" ) unless $Old > 30;
        }

#    } else {
#        foreach $Key (sort keys %INC) {
#            my $File = $INC{$Key};
#            my $Old = int ( ( (-M $File) * 24 * 60) + 0.5); # Mins old
#            &PrintLog ( $File, 1 ) unless $File =~ /perl/;
#            &PrintLog ( "$File [$Old mins]\n" ) unless $Old > 30;
#        }
    }

    unless ($ENV{'QUERY_STRING'} eq '') {
        our %Params = ();
        &PrintLog ("QStr=$ENV{'QUERY_STRING'}",1);
        foreach (split /[\&|\;]/, $ENV{'QUERY_STRING'}) {
            &PrintLog ($_,1);
            my ($Var, $Val) = split /\=/;
            $Param {$Var} = $Val;
        }
    }
#    &PrintLog ( 'or as an alternative using param ():',3);

#    my $Param;
#    foreach $Param qw ( Serial_No show status) {
#        &PrintLog ( param ( $Param),3);
#    }

    our %TD_Desc = (
        ATT        =>        'Actual Test Time',
        ECT        =>        'Estimated Completion',
        ERC        =>        'Last Error Code',
        Power      =>        'Power Supply',
        TEC        =>        'Total Error Count',
        TOLF       =>        'Time Of Last Failure',
        TSLF       =>        'Time Since Last Failure',
        TTF        =>        'Time To [1st] Failure',
        TTT        =>        'Total Test Time',
        TTT        =>        'Time To Go'
    );

    our %BG_Color = (
        active  => 'yellow',
        Active  => 'yellow',
 #       pass    => 'lime',
 #       fail    => 'red',
        pass    => '#88FFB0',
        fail    => '#FF6050',
        default => '#E0D0D0',
    );

#    $BG_Color{'pass'} = '#DDFFDD'; # too pale
#    $BG_Color{'pass'} = '#88FF88'; # better

#    $BG_Color{'fail'} = '#E08080'; # too pink
#    $BG_Color{'fail'} = '#FF8080'; # too salmon
#    $BG_Color{'fail'} = '#FFB080'; # too flesh
#    $BG_Color{'fail'} = '#FFB060'; # too orange
#    $BG_Color{'fail'} = '#FFB050'; #

    foreach ( keys %BG_Color ) { #Now both 'red' and 'RED' are synonymous
        $BG_Color{uc $_} = $BG_Color{$_}
    }

    our ($Indent) = 0;                # Indentation for html code

    opendir (DIR, $Stats_Path) or &PrintLog ("Can\'t open stats dir $Stats_Path");

    &Init_Vars;

#New...

    our $All         = 0;        # Instead of passing param('all')
    our $Bullet      = '  ';
    our %Data        = ();       # $Data{'Location'}{$UUT_ID} = ...
    our $Inc_Remote  = 0;        # Include searching files from remote sites (slow!)
    our $Serial_No   = $Param{'Serial_No'};
    our @SN_Masks    = ($Serial_No); # Used by &Logs::Cfg_Events -> Check_SN_Mask
    our $Show_UnIDd  = 0;
    our @TIDs        = qw (Program Bench BI EXT FCT IST FST ORT SHIP);
    our @TID_Defs    = qw (Program Bench BI FCT SHIP);
    our $Mode      = $Param{'Mode'};

    $Bullet      = ' <img src="../icons/continued.gif"> ';


}

#_______________________________________________________________________________
sub Init_Vars {

    our $Age        = ();
    our %Location   = ();
    our %Product_ID = ();
    our %Result     = ();
    our %Started    = ();
    our %Status     = ();
    our %Test_ID    = ();
    our %TTG    	= ();   # JSW
    our %TTT    	= ();   # JSW
#    our $TimeStamp  = ();

    our %Active     = ();    # $Active{Active|Recent|Defunct}{$UUT_ID}
    our @State      = ();    # List of Lists [ Active, Recent, Defunct ] => key
    our @Count      = (0,0,0);    # Count of each

    our %Data        = ();   # While we run parallel
}

#_______________________________________________________________________________
sub Load_Stats_Data {  # Called by Load_Stats_File
                       # Load the Stats Data hashes

    my ($Stats_File, $Demo) = @_;


    if ( $Stats{'UUT_ID'} eq '') {
        # In case we want to show unID'd activity ...
        $Stats{'UUT_ID'} = &fnstrip ($Stats_File,7);
    }

    my $Key = $Stats{'UUT_ID'};

    $Age{$Key}        = time - $Stats{'Updated'};
    $Location{$Key}   = $Stats{'Host_ID'} . '-' . $Stats{'Session'};
    $Product_ID{$Key} = $Stats{'UUT_ID'};
    $Result{$Key}     = $Stats{'Result'};
# $Stats{'Started'} gets munged by Stats::Reads RE so ...
    $Started{$Key}    = &PT_Date ($Stats{'TimeStamp'},1);
    $Status{$Key}     = $Stats{'Status'};
    $Test_ID{$Key}    = $TestData{'TID'};
    $TTG{$Key}    = $Stats{'TTG'};
    $TTT{$Key}    = $TestData{'TTT'};
    $Version{$Key}    = $TestData{'Version'};  #UUT Version info str
                       # CMTest vers / UUT Vers info
    $Version{$Key}    = "$TestData{'Ver'} / $Version{$Key}";

    $Result{$Key}     = '' if $Result{$Key} eq 'INCOMPLETE' and
                           $Status{$Key} eq 'Running';

    &Loaded_Stats_Data_Show ($Key) if $Debug and 0;
}

#_____________________________________________________________________________
sub Loaded_Stats_Data_Show {

    my ($Key) = @_;

    &PrintLog ("Key=$Key, " .
               "Age=$Age{$Key}, " .
               "Location=$Location{$Key}, " .
               "Product_ID=$Product_ID{$Key}, " .
               "Result=$Result{$Key}, " .
               "Started=$Started{$Key}," .
               "Status=$Status{$Key}, " .
               "TID=$Test_ID{$Key}," .
#               "Time=$TimeStamp{$Key}," .
               "Version=$Version{$Key}," .
               "TTG=$TTG{$Key}," .
               "TTT=$TTT{$Key}," .
               "BG=$Paint,3"
    );
}

#_____________________________________________________________________________
sub Load_Stats_File { #  Was: Show_Stats_File

    my ($Stats_File) = @_;

    %Stats =();
    %TestData =();
    %Globals =();

    &Stats::Read ($Stats_File);
    &Load_Stats_Data;
}

#_______________________________________________________________________________
sub main_Show_Matrix {

     my ($Stats_File) = param('Stats_File');

     &Head ('Production Test Status Summary Matrix');

#     my $Now = &PT_Date (time, 1);

     &Body ("<H2 ALIGN=\"center\">Production Test Status Summary Matrix</H2>");
     &Body ("<H2 ALIGN=\"center\">Last updated: $Now</H2>");
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
          &PrintLog ("Found $Count active tests");

          &Sort_Stats_Fake_Data_4Demo unless $Count;
     } else {
         &Sort_Stats_File ($Stats_File);
     }

     &Stats_File_Summary;  # Print the data

     &Tail ();

}

#_______________________________________________________________________________
sub Print_Stats_TestData_tables {

    my ($Stats_File) = @_;

    my $Key;
    my $Defunct = 0;

    &Stats::Read ("$Stats_Path/$Stats_File");

    $Defunct = 1 if time - $Stats{'Updated'} > 43200;  # Changed to 12hours for ORT

    if ($Defunct) {
            $Stats{'Status'} = 'Defunct';
             return if ! $Show_Defunct;
    }

    &Body ("<P><HR></P>");
    &Body ("<H2 ALIGN=\"LEFT\">" . &fnstrip ($Stats_File,7) . ":</H2>");
    &Body ("<H3 ALIGN=\"center\">Stats:</H3>");
    &Table_Head qw( Parameter Value );

    foreach $Key (sort keys %Stats) {

        unless ($Stats{$Key} eq '') {

                $Stats{$Key} = &PT_Date ($Stats{$Key},1) if
                        $Key =~ /ECT|TimeStamp|Updated/;

                &Table_Row ( $Key, $Stats{$Key} );
        }
    }
    &Table_Tail ();

    &Body ("<H3 ALIGN=\"center\">Test Data:</H3>");
    &Table_Head qw( Parameter Value );

    foreach $Key (sort keys %TestData) {

        $TestData{$Key} = &PT_Date ($TestData{$Key},1) if
                $TestData{$Key} and $Key =~ /TOLF/;

        $TD_Desc{$Key} = $Key if $TD_Desc{$Key} eq ''; # Just in case
        &Table_Row ( $TD_Desc{$Key}, $TestData{$Key} ) unless
                $TestData{$Key} eq '';
    }
    &Table_Tail ();
}

#__________________________________________________________________________________
sub xPrintLog {     # Copied from PTML to use predeclared LogFile (BEGIN)

    my ($Msg, $Verb) = @_;
    chomp $Msg;

    # $Verb $Verbose
    # undef    X      log it
    # $Verb => $Verbose

    return (0) if defined $Verb
              and !$Verbose;

    my $Time = scalar(localtime);
    $Time = substr ($Time, 4, 15);

    my $fh;

    flock $fh, 2;   # Grap exclusive
    open ($fh, ">>$LogFile") || return (3);
    print $fh $Time, ":\t$Msg\n";
    close $fh;
    flock $fh, 8;   # Grap exclusive

    return (0);
}

#_____________________________________________________________________________
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

    &Load_Stats_Data ($Stats{'UUT_ID'}, 1);
}

#_______________________________________________________________________________
sub Query_Form {

#    our ($Serial_No) = param ('Serial_No');  # Take the form value 1st, else
#    $Serial_No = $Param{'Serial_No'} if $Serial_No eq ''; # from ..cgi?Serial_No=001...

    &PrintLog ("\&Query_Form: Serial_No=$Serial_No");

    my $Title = "$Host_Name - Event Log Search - recursive";

    if ($Serial_No ne '') {   # Don't define the form yet

        print h1($Title),
              h2("Serial No =  $Serial_No"),
              $Bullet, "<A HREF=$URL>Start New Search</A>  ",
              $Bullet, "<A HREF=$URL?Serial_No=$Serial_No>Repeat Search</A>  ",
              $Bullet, "<A HREF=$URL?Type=status>Return to Production Floor Status</A>  ",
              $Bullet, hr;

        &Event_Log_Search;

    } else {

        print   h1($Title),
                start_form,
                "<B>Product Serial No? </B>",
                textfield('Serial_No'), '   ',
                'Include: ', checkbox ('remote'), ' sites? ',
                checkbox ('unIDd'), '?   ',
#                reset,
                submit('Search'),
                p,
                "<B>Include Test-IDs?:</B>     ",
                radio_group(
                  -name=>'All',
                  -values=>['All','Specify'],
                  -default=>'Specify'
                ),
                ":  ",
                checkbox_group(-name=>'TIDs',
                               -values=>[@TIDs],
                               -defaults=>[@TID_Defs]),
                p,
            #        "Sort by? ",
            #        popup_menu(-name=>'Sort_By',
            #                   -values=>['TID','Location','Date','Result','Other']),
            #        '[WIP feature]',
            #        p,
            #    reset, (all this does is reload defaults (no action)
                end_form,
                hr;

#         if (param()) {                 # param() = number of parameters passed from form

         if (param ('Serial_No')) {

             @TIDs         =  param ('TIDs');
             $Serial_No    =  param ('Serial_No');
             $All          = (param ('All') eq 'All')    ? 1 : 0;;
             $Inc_Remote   = (param ('remote') eq 'on') ? 1 : 0;
             $Show_UnIDd   = (param ('unIDd') eq 'on')    ? 1 : 0;

             &Event_Log_Search;
         }
    }
}

#_____________________________________________________________________________
sub Stats_Show {



        #&Init;
        &Show_Stats_dep ('Stoke - Production Test Status',
                     $Version, $Info);
        &PTML::Tail ();
 # copied from status.cgi
}
#_____________________________________________________________________________
sub Show_Stats_dep {      # Called by cgi's: status and summary

    my ($Head, $Version, $Info) = @_;

#    my $Type = ($0 =~ /summary/) ? 1 : 0;

    our $Stats_Path   = '/var/local/cmtest/stats';
    opendir (DIR, $Stats_Path) or
       die "Can't open Stats File Path $Stats_Path";

    #&PTML::Head ($Head);

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
            &main::Show_Stats_File ($Stats_File);

        }

    }

    closedir (DIR);

    return;
}



# Copied (less POD) from PT ... then copied from PT_CGI JSW

#__________________________________________________________________________________
sub Show_Stats_File {

        my ($Stats_File) = @_;

        %Stats =();
        %TestData =();
        %Globals =();

        my $Key;
        my $Defunct = 0;

#        &Stats::Read ("/home/ptindle/tmp/stats/$Stats_File");
        &Stats::Read ("/var/local/cmtest/stats/$Stats_File");

        $BG_Color = $BG_Color_Def;
        $BG_Color = $Fail_Color    if $Stats{'Result'} eq 'FAIL';
        $BG_Color = 'lime'        if $Stats{'Result'} eq 'OK';
        $BG_Color = $Pass_Color    if $Stats{'Result'} eq 'PASS';

        &PTML::PrintLog ("BackGroundColor=$BG_Color");

        $Defunct = 1 if time - $Stats{'Updated'} > 43200;  # Changed to one week JSW for ORT

        if ($Defunct) {
                $Stats{'Status'} = 'Defunct';
                 return if ! $Show_Defunct;
        }

        &PTML::Body ("<P><HR></P>");
        &PTML::Body ("<H2 ALIGN=\"LEFT\">" . &fnstrip ($Stats_File,7) . ":</H2>");
        &PTML::Body ("<H3 ALIGN=\"CENTER\">Stats:</H3>");
        &PTML::Table_Head qw( Parameter Value );

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
}  # Copied from Status.cgi...
#_____________________________________________________________________________
sub Sort_Stats_Fake_Data_4Demo {        # A fake &Sort_Stats_File for demo purposes

    &Body ("<H2 ALIGN=\"center\">No Active Tests found! Example data:</H2>");

#                       Product_ID Result       Status   ACT      TID
    &Push_Stats qw( SN001234 PASS         Finished 1200     BI   );
    &Push_Stats qw( SN001235 FAIL         Running  5000     Test );
    &Push_Stats qw( SN001236 FAIL         Running  1800     Diag );
    &Push_Stats qw( SN001237 INCOMPLETE   Running  25000    Systest );
    &Push_Stats qw( SN001238 INCOMPLETE   Running  3000     Test );

}

#_____________________________________________________________________________
sub Stats_File_Summary {  # Print the table header, one line per Stats file
                          #  and pushes @Record onto %{field}{system_id}

    my $Key;
    foreach $Key (sort keys %Product_ID) {

        &Loaded_Stats_Data_Show ($Key) if $Debug and 0;

        my $Which;  # $Count[$Which]
        if ($Status{$Key} eq 'Active') {
            $Which = 0;
        }elsif ($Age{$Key} < $Recently) {
            $Which = 1;
        } else {
            $Which = 2;
        }
        &PrintLog ("Which = $Which") if $Debug and 0;
#            $Active{$Key}{$Type} = $Age{$Key}; # Just for something to put there
        push @{ $State[$Which] }, $Key;
        $Count[$Which]++;
    }
    &PrintLog ("Active = $Count[0], Recent = $Count[1], Defunct = $Count[2]");

    my @Section = qw( Active Recent );
    push @Section, 'Defunct' if $Show_Defunct;
    my @Fields = qw( Location Started Test_ID Product_ID Status Result TTG TTT );

    my $i = 0;
    my $Label;
    foreach $Label (@Section) {
        $Label .= ' None!' unless $Count[$i];
        &Body ("<H3>$Label</H3>");
#        h3 ($Label);
        if ($Count[$i]) {
            &Table_Head (@Fields);
            foreach $Key (@{ $State[$i] }) {

                my $Stats_File = $Product_ID{$Key} . '.txt';

                my %FLink = (
                     Location   => "<A HREF=$URL?Type=Stats;Stats_File=$Stats_File>",
                     Product_ID => "<A HREF=$URL?Serial_No=$Key>"
                );
                if (!-f "$Stats_Path/$Stats_File") {
                    delete $FLink{'Location'};
                    &PrintLog ("FLink to $Stats_File deleted",2) ;
                }

                $FLink{'Status'} = "<A HREF=$URL?Type=show;File=$Stats_Path/$Stats_File>";
#                $FLink{'Status'} = "<A HREF=file://$Stats_Path/$Stats_File>";

                my @Record = ();

                foreach $Field (@Fields) {
                      my $Field_Data = $FLink{$Field} . ${$Field}{$Key};
                      $Field_Data .= '</A>' unless $FLink{$Field} eq '';
                      push @Record, $Field_Data;
                }
                $Paint = $BG_Color{$Result{$Key}};
                &Table_Row (@Record);
            }
            &Table_Tail ();
        }
        $i++;
    }
}

#____________________________________________________________________________________

# To go elsewhere ...

#____________________________________________________________________________________

sub Check_File_Size {   # takes a file name (full file-spec) and an optional
                        # size limit, and returns 1|0 (bigger or smaller than limit
                        # and a string contaning a formatted filesize eg (4.1MB)

     my ($File, $Size_Limit) = @_;

     my $Size = -s $File;
     my $TooBig = ($Size > $Size_Limit) ? 1 : 0;
     # &PrintLog("File=$File, Size=$Size, Limit=$Size_Limit, TooBig=$TooBig ");
     return (0,'') unless $Size;

     my @Dim  = qw(K M G);
     unshift @Dim, '';
     my $i = 0;
     while ($Size > 1000 and  $i < 4) {
           $Size = $Size/1000;
           $i++;
     }
     $Size = sprintf "%.1d", $Size;

     return ($TooBig, '(' . $Size . $Dim[$i] .')');
}

#____________________________________________________________________________________

# Copied (less POD) from PT ...
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
}    # Copied from PT.pm JSW

#__________________________________________________________________________________

#__________________________________________________________________________________
sub Pad {    # Called here only by PT_Date...

    # Return a string with things added (<sp> default)

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
sub PrintLog {     # Copied from PTML to use predeclared LogFile (BEGIN)

    my ($Msg) = @_;
    chomp $Msg;

    my $Time = scalar(localtime);
    $Time = substr ($Time, 4, 15);

    my $fh;

    flock $fh, 2;   # Grap exclusive
    open ($fh, ">>$LogFile") || return (3);
    print $fh $Time, ":\t$Msg\n";
    close $fh;
    flock $fh, 8;   # Grap exclusive

    return (0);
}

#_____________________________________________________________________________
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

#!!! ???    die "Exiting PT_Date: Ptr = $Type" unless $Type == 1;

    return ( $Date_Str[$Type] );
}

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


1;
