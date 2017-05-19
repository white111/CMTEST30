##############################################################################
#
# Module:    Logs.pm
#
# Author:    Paul Tindle ( mailto:Paul@Tindle.org )
#
# Version:   (see below)
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 2005-2006 Paul Tindle. All rights reserved.
#
###############################################################################
my $CVS_Ver = ' [ CVS: $Id: Logs.pm,v 1.2 2006/12/15 17:46:17 joe Exp $ ]';
my $Ver;

#$Version{'Logs'} = '15   2005/12/22'; #Exit_On_Error -> &Final
#$Version{'Logs'} = '16   2006/05/15'; #Added a 'sub Log_MAC'
#$Version{'Logs'} = 'CVS 1.3   2006/05/16';
$Version{'Logs'} = '1.3.5   2006/08/07'; #Added &Get_Cfg_Recs ( Yield.pl, ...)
                                         # HiRes logging, Inits $Start_Time
                                         # PrintLog alias, moved Log_eTime from yield.pl
                                         # Added Session to qualify Host_ID field

use Time::HiRes qw(gettimeofday tv_interval);

our $Start_Time = [gettimeofday];         # This needs to move to &Init

#__________________________________________________________________________
sub Arc_Logs {   # Alternative to Rotate_Logs, creates a folder based on the
                 # creation date of the first file arc'd, and moves any files
                 # (not dirs) found to the new sub-dir.

     my ($Path, $Label) = @_;
     my ($Move) = 'mv';
     my ($Delete) = 'rm -f';
     my ($From, $To, $fh, $Arc_File);

     if ($ENV {'OS'} eq 'Windows_NT') {
         $Move = 'ren';
         $Delete = 'del';
     }

     opendir( $fh, "$Path" );
     foreach (readdir($fh)) {
        if (/2arc2(.*)/) {
            $Arc_File = $1;
            system "rm -f $Path/$_";
            last;
        }
     }
     closedir $fh;

     my $File_Count = &File_List ($Path, 1); # Don't recurse any subs
     return unless $File_Count;

     if ($Arc_File eq '') {
         $Arc_File = $^T - ( ( -C $File_List[0] ) * 3600 * 24 );
         $Arc_File = "$Label\_" . &PT_Date( $Arc_File, 2 );
         $Arc_File =~ s/\s/_/g;
         $Arc_File =~ s/[\/\:]/-/g;
     }
     $Arc_File = "$Path/$Arc_File";

     mkdir $Arc_File;

     foreach (@File_List) {
         $Erc = system "$Move $_ $Arc_File\n";
     }

     &Exit (999,"Arc_Logs returned a $Erc") if $Erc;
}

#_______________________________________________________________________________
sub Cfg_Events {   # Was &Yield() now called by &yield.pl pc.pl or cmtest_CGI

# Open and read the Test Event Log, then the Cfg Log, reading each
#        chronologically, match record keys, and returning cfg SNs for inclusion
#   in event recs. Users globals: @TIDs , @SN_Masks (either prefix or complete)

    my ($Test_Log_Source, $set_by_opt_c) = @_;

    my %Unit = ();  # Tags each ProductID
    my %TID_List = ();

    my $File = "$Test_Log_Source/Cfg.log";
    &PrintLog("Opening cfg log $File");
    open (CFG, "<$File") or die "Can\'t open Cfg log \'$File\'";

#1;1141946601;SMV;mfg-svr1;joe;00292-02 Rev 01;0020128050000001;Bench;FAIL;ATT=743,ERC=0,TEC=4,TID=Bench,TOLF=1141946716,TSLF=633,TTF=34,TTT=748,Ver=1.5.2;0020128050000001-20060309.152321.xml;
#1;1141947392;SMV;mfg-svr1;joe;;;IST;FAIL;ATT=171,ERC=0,TEC=6,TID=IST,TOLF=1141947566,TSLF=0,TTF=34,TTT=174,Ver=1.5.2;;

    $File = "$Test_Log_Source/Event.log";
    &PrintLog("Opening Event log $File");
    open (FH, "<$File") or die "Can\'t open Event log \'$File\'";

        # 0 1    2        3      4    5       6         7      8      9    10
        # 1;Date;Location;HostID;OpID;Part_No;Serial_No;TestID;Result;Data;LogFilePtr;

    my $i    = 0;
    my $j    = 0;
    my $cSN  = 0;
    my $Erc  = 2; # The 'no-record-found' value
    my $Msg  = '';
    my $RDate;

    while (<FH>) {        # Event log

        &PrintLog ("\t***\tRead Event Log line $.", 1) if $Debug and 0;

        chomp;
        $i++;
        $Msg = '';
        my ($RecType, $Date, $Location, $HostID, $OpID, $PN, $SN,
            $TestID, $Result, $Data, $LogFileP) = split (/\;/);

        if ($RecType != 1) {     # Only type 1 recs allowed
            &PrintLog ("Event log line $. not recognized!");
            next
        }

        my $Version = '';
        my $Var_Val;
#        $Msg = "$Data\n";
        foreach $Var_Val (split /,/, $Data) {
#            $Msg .= "Var_Val = $Var_Val";
            my ($Var, $Val) = split /=/, $Var_Val;
#            $Msg .= ", Var = $Var, Val = $Val";
#            my ($Which, $Ver) = split /_/, $Var;
#            ($Val) = split /---/, $Val if $Which eq 'Diag';
#            $Msg .= ", Which = $Which, Ver = $Ver";
#            $Version = "$Which=$Val" if $Ver eq 'Ver';
        }

        $TID_List{$TestID} = 1;
        if ($SN eq '') {
            &PrintLog ("Event log line $. has no SN!",1) if $Debug and 0;
            $cSN++;
            next;
        }

        if ($Date < $Last_Rec_Date) {
#!!!            &PrintLog ("Warning! Misordered data in $File line $i",1);
        }
        our $Last_Rec_Date = $Date;

        my $cTIDs = @TIDs;   # How many on the list
        my $OK    = ($cTIDs) ? 0 : 1;
        my @Parts = ();

        foreach my $TID (@TIDs) {

            $OK = 1 if $TestID eq $TID;
        }
        next unless $OK;

        $OK = 0 if $Date < $Beg_Time and defined $Beg_Time;
        $OK = 0 if $Date > $End_Time and defined $End_Time;

        if ($OK) { # TID matches, SN matches, dates are in range ...

            $j++;
            $RDate = $Date;        # Time stamp from the last record matched
            if ($set_by_opt_c) {
               ( @Parts ) = &Get_Cfg_Recs ($Date, $Location, $HostID,
                                                   $SN); #, @SN_Masks);
 my $cC = @Parts; &PrintLog("Get_Cfg_Recs returned $cC child records [$Line_No_Cfg_Log]",1) if $Debug and 1;
             }
 # Pulled from Logs::Get_Cfg_Rec   -  should be done here
 #        #!!! Still in debug ...
#        foreach ( @Exclude ) {
#            $SN_Match = 0 if $SNum =~ /^$_/;
#        }
#        &PrintLog("SN_Match[3]=$SN_Match",1) if $Debug;

            if (&Check_SN_Mask ($SN)) {
                push @Parts, $SN ;  # Add the Event SN to this list
                $Msg = "Event_Log # $i <<<";
            }

            foreach $SN ( @Parts ) {

                if ($Result eq 'PASS') {
                    $Test_Results_1st[0] ++ if !defined $Unit{$SN};
                    $Test_Results_All[0] ++;
                    $Erc = 0; # unless $Erc == 1; # Remember a 'FAIL'
                } elsif ($Result eq 'FAIL') {
                    $Test_Results_1st[1] ++ if !defined $Unit{$SN};
                    $Test_Results_All[1] ++;
                    $Erc = 1;
                }
                $Msg = "Event_Log # $i - Cfg Log # $Line_No_Cfg_Log";
                &PrintLog ($Msg, 1);
                $Test_Results_1st[2] ++ if !defined $Unit{$SN};
                $Test_Results_All[2] ++;
                $Unit{$SN} = 1;
                push @Event_Recs, "$Date;$Location;$SN;$TestID;$Result;$LogFileP";
            }
        } # end if OK
     } # end while <FH>
    close FH;
    close CFG;
    &Log_eTime;

    if ($Debug and !$Quiet) {
        print "$j out of $i recs matched (No SN = $cSN)\n";
        $i = 0;
        print "TIDs found:\n\n";
        foreach my $TID (sort keys %TID_List ) {
            print "\t$TID\n";
            $i++;
        }
        print "<end> [$i recs]\n\n";
        print "Serial Nos matched:\n\n";
        $i = 0;
        foreach my $SN (sort keys %Unit ) {
            print "\t$SN\n";
            $i++;
        }
       print "<end> [$i recs]\n\n";
     }
    $Msg = &PT_Date($RDate, 0) . ": $Msg" if $RDate;
    return ($Erc, $Msg);
}

#__________________________________________________________________________
sub Check_SN_Mask {

    my ($SN) = @_;
    my $SN_Match = (@SN_Masks) ? 0 : 1; # Assume a match if no mask list

    foreach ( @SN_Masks ) { # if there are none, $SN_Match has already been
        $SN_Match = 1 if $SN =~ /^$_/;
        &PrintLog("\'$_\' : SN_Match=$SN_Match",1) if $Debug;
    }

    return $SN_Match;
}
#_______________________________________________________________________________
sub Get_Cfg_Recs {   # Returns a list of component/child serial numbers
                                         # corresponding to the Keys passed from the Event log record
                                         # Requires handle <CFG> to already be open for read

#    my ($Date, $Location, $HostID, $Parent_ID, @SN_Masks) = @_;
    my ($Date, $Location, $HostID, $Parent_ID) = @_;
    my @Cfg_Recs = ();
    my @Rec = ();
    my $Buf = '';

    &PrintLog ("\&Get_Cfg_Recs: Date=$Date, Location=$Location, HostID=$HostID, Parent_ID=$Parent_ID",1);

    my ( @Last_Rec ) = split  /\;/, $gBuf[0];
    if ($Date < $Last_Rec[1]) {
        return;  # The date we want is earlier than the last record read,
                 #   so don't bother with any more
    }

    my $Done = 0;
    while (!$Done) {

        $_ = <CFG>;
        $Line_No_Cfg_Log++;

        chomp;
        &PrintLog ("Read CfgLog line $.", 1);
        $Done = 1 if eof;
        $Buf = $_;           # Save it in case we overrun the date (-> gBuf[0])

        ( @Rec )  = split /\;/;

        if ($Rec[0] != 2 and !$Done) {
            &Exit (999, "Unrecognized file format for CFG record line $.");
        } elsif ($Rec[1] < $Date) {   # Cfg rec is too early
            next;                     # Skip
        } elsif ($Rec[1] > $Date) {   # Too late, we'll stop with this record
            $Done = 1;                #  still loaded in gBuf[0]
        } else {
            push @gBuf, $_;
            &PrintLog ("Pushed $_ on \@gBuf", 1);
        };
     }

       #0: $Type, 1: $Date, 2: $Location, $HostID, $OpID, $Parent_ID, $Slot, $PN, $SN)
#    &PETC("Cont.d...");
    my $Msg = '';
    foreach (@gBuf) {

        my ( @Rec )  = split /\;/;

        if (($Rec[2] eq $Location)   and
            ($Rec[3] eq $HostID)     and
            ($Rec[5] eq $Parent_ID)  and
            &Check_SN_Mask ($Rec[8]))  {

                $Msg .= ', ' unless $Msg eq '';
                $Msg .= $Rec[8];
                push @Cfg_Recs, $Rec[8];
       }
        #, $Date, $Location, $HostID, $OpID, $Parent_ID, $Slot, $PN, $SN)
    }
    &PrintLog("Returned: $Msg", 1);

    our (@gBuf) = $Buf;        # Just the last one

    return ( @Cfg_Recs )   # <- List of Serial Nos matching the mask
}


#__________________________________________________________________________
sub Log_Cfg {        # Write a single (parent / child) record. Caller must construct
                                # sequence of invocations to create all the necessary records
                                # to describe the DUT

        # Event log is a 'Type 2' record:
        # 2;Date;Location;HostID;OpID;Parent_ID;Slot;Part_No;Serial_No;

        my ($OpID, $Sys_ID, $Slot, $PN, $SN) = @_;
        # (NB $TimeStamp, $Location, $Host_ID and $Op_ID are global, declared in &Init_All)

        my ($File) = "$LogPath/Cfg.log";

        &Exit (1, $File) if &File_Open ($File, OUT, '>>');

        print OUT "2;$Stats{'TimeStamp'};$Location;$Host_ID-$Stats{'Session'};" .
                          "$Op_ID;$Sys_ID;$Slot;$PN;$SN;\n";
        &File_Close (OUT);
}

#__________________________________________________________________________________
sub Log_Error {                        # An error just occured, log it!

    my ($Msg) = @_;

    $TestData{'TOLF'} = time;      # Time of Last Failure

    $Errors[0]++;
    $Errors[1]++;
    $TestData{'TEC'}++;
    $Stats{'Result'} = 'FAIL';

    $TestData{'TTF'} = $TestData{'TOLF'} - $Stats{'TimeStamp'}
            if $TestData{'TTF'} eq '';        # Only the first time

    &Stats::Update_All;

    &Print_Log (2, 'Log_Error: ' . $Msg);

    if ($Exit_On_Error) {
       $Exit_On_Error_Count--;
       # THis must be Erc=0 to avoid dancing forever with $Exit
       #&Exit (0, "Exit_On_Error") if $Exit_On_Error_Count < 1;
       if ($Exit_On_Error_Count < 1){  # if Error count reached Exit, and finalize
           &Print_Log (2, 'Exiting - Too many errors ');
       #   &Exit (0, "Exit_On_Error");
           $Erc = 0;
           &Final;
       }
    }
    return (0);
}

#_______________________________________________________________________________
sub Log_eTime {

    my ($Msg) = @_;
    $Msg = 'ETime' if $Msg eq '';

    &PrintLog ("\t\t\t\t$Msg: " . tv_interval ($Start_Time) . ' secs');

}

#__________________________________________________________________________
sub Log_Event {                # Write a test event record

                        # Note that, as of 05/12/02 the Data list is no longer passed as an arg

        # Event log is a 'Type 1' record:
        # 1;Date;Location;HostID;OpID;Part_No;Serial_No;TestID;Result;Data;LogFilePtr;

        my ($Data);
        my (@Args) = @_;                # Convert any ';' -> ',' (field separator!)
        foreach (@Args) {
                s/\;/\,/g;
        }

#        my ($OpID, $PN, $SN, $TID, $Result, $Data, $Ptr) = @Args; ->05/12/02
        my ($OpID, $PN, $SN, $TID, $Result, $Ptr) = @Args;

        # (NB $TimeStamp, $Location, $Host_ID and $Op_ID are global, declared in &Init_All)

        my ($File) = "$LogPath/Event.log";

        foreach $Key ( sort keys %TestData ) {
                $Data .= "$Key=$TestData{$Key},"
                        if $TestData{$Key} ne '';
        }
        chop $Data;

        &Exit (1, $File) if &File_Open ($File, OUT, '>>');

        print OUT "1;$Stats{'TimeStamp'};$Location;$Host_ID-$Stats{'Session'};" .
                          "$Op_ID;$PN;$SN;$TID;$Result;$Data;$Ptr;\n";
        &File_Close (OUT);
}

#__________________________________________________________________________________
sub Log_History {                        # Log script start / end activity

        my ($Type) = @_;
        my ($LogFile) = "$LogPath/history.log";
        my ($Msg) = &PT_Date (time, 1) . ":\t$Stats{'TimeStamp'}";
        local $Session = $Stats{'Session'};

        $Msg .= "\t$Op_ID\t" . $Stats{'Host_ID'};
        $Msg .= '-S' . $Session if $Session;
        $Msg .= "\t";
        $Session = '?' unless $Session;

        die "\$LogPath not defined in \&Logs::Log_History"
                if $LogPath eq '';

        SWITCH: {
                if ($Type == 1) { $Msg .= "Starting $Main ... "; last SWITCH; }
                if ($Type == 2) { $Msg .= "Ending $Main";                last SWITCH; }
                &Exit (999, '(Invalid call to Log_History)');
        }

        $Msg .= ' [';
        my $Var;
        foreach $Var qw ( Session PPath GP_Path XLog ) {
                $Msg .= "$Var=${$Var}," unless $$Var eq '';
        }
        $Msg .= ']';
                                                # This next one needs to be a 'die' since &Exit will &Log_History!
        open (LOG, ">>$LogFile") || die ("Can\'t open History file $LogFile");
        print LOG "$Msg\n";
        close LOG;

        return (0);
}

#__________________________________________________________________________________
sub Log_MAC {   # First checks to make sure this MAC address has not been used before
                # then cats a new record to MAC.log

    # MAC log is a 'Type 4' record:
    # 4;Date;Product_ID;MAC_Address;
    # eg:    4;1134001942;0020140050000031;00-12-73-00-0E-40

#    our @ID4MAC = ();

    my ($Product_ID, $MAC_Addr) = @_;

    my ($File) = "$LogPath/MAC.log";

    &Exit (1, "Can\'t open $File for read") if &File_Open ($File, IN, '<');

    my $Found = 0;
    while (<IN>) {

        chomp;
        my ($Type, $Date, $Prod_ID, $MAC) = split /;/;

        if ($MAC eq $MAC_Addr) {
            $Found = 1;
            if ($Prod_ID ne $Product_ID) {
               return (3, "MAC $MAC already assigned to $Prod_ID on " .&PT_Date ($Date, 7));
           }
        }
    }
    &File_Close (IN);
    return (0) if $Found;

#    $ID4MAC{$MAC_Addr} = $Product_ID; # from args

#    foreach $Key ( sort keys %TestData ) {
#            $Data .= "$Key=$TestData{$Key},"
#                    if $TestData{$Key} ne '';
#    }
#    chop $Data;

    &Exit (1, "Can\'t open $File for cat") if &File_Open ($File, OUT, '>>');

    my $Time = (defined $Stats{'TimeStamp'}) ? $Stats{'TimeStamp'} : time;

    print OUT "4;$Time;$Product_ID;$MAC_Addr\n";
    &File_Close (OUT);

    return (0);
}

#__________________________________________________________________________________
sub Print2XLog {   # Print a line to the execution log
                   # Replacement for Print_Log

     my ($Msg, $DontPrint2Screen, $NoNewLine, $TagAsError) = @_;

     #!!! Find out whos calling with $NoNewLine set, and who cant just use Global Quiet the same as everyone else!!

     chomp $Msg;
     my $EOL_Ch = ($NoNewLine) ? '' : "\n";

     print $Msg . $EOL_Ch unless $Quiet or $DontPrint2Screen;
     my $Run_Time = tv_interval $Start_Time;  # Also at PT2.pm

# Tagging the date after so many minutes DOES NOT WORK (yet)
     my $ReDate = 2; # Time stamp every $ReDate sec
     my $Last_Log_Interval = time - $Last_Log_Time;


     my $Tag = ($TagAsError) ? "ERR $Erc:" : '   ';
     my $TimeField = ( $Last_Log_Interval > $ReDate) ? &PT_Date (time, 2) :
                       "\t" . sprintf ("%.3f", $Run_Time);
 #&PETC ($Last_Log_Interval);
     return (0) if lc $Msg =~ /^done/;

     my $XLog = $LogFile if !defined $XLog and defined $LogFile; # (CGI style)

     unless ($New_Log) { #!!! Required for Win32 - otherwise really slow! (Opened in Yield.pl)
         flock LOG, 2;   # Grap exclusive
         open (LOG, ">>$XLog") || return (3);
     }
     print LOG $TimeField, ":\t$Tag\t$Msg\n";
     unless ($New_Log) {
         close LOG;
         flock LOG, 8;
     }

     our $Last_Log_Time = time;

     return (0);
}
#Alias...
sub PrintLog { &main::Print2XLog (@_)}

#__________________________________________________________________________________
sub Print_Log {    # obsolete! use Print2XLog instead

    my ($Mode, $Msg) = @_;

    $TagAsError = (substr ($Mode, -1, 1) == 2) ? 1 : 0;
    $DontPrint2Screen = substr ($Mode, -2, 1);

    my $RC = &Print2XLog ($Msg, $DontPrint2Screen, 0, $TagAsError);

    return ($RC);
}
#__________________________________________________________________________________
sub Print_Out {         # Print a line to the output file $Out_File

     my ($Msg) = @_;

     my $fh;
     open ($fh, ">>$Out_File") || return (3);
     print $fh $Msg;
     close $fh;

     return (0);
}
#__________________________________________________________________________________
sub Print_Out_XML_Tag {

    my ($Tag) = @_;
    if ($Tag eq '') {                 # It's an end tag - pop it off the stack
        $Tag = '/' . pop @XML_Tags;
    } else {
                                      #!!! may want to do a split of any attribute later...
        push @XML_Tags, $Tag;
    }

    $RC = &Print_Out ("\<$Tag\>\n");
}
#__________________________________________________________________________
sub Rotate_Log {                # Copy file.log.{n-1} to file.log.{n} ...
                                                # Copy file.log.1 to file.log.2
                                                # Copy file.log to file.log.1
                                                # Delete file.log

     my ($LogFile, $Count) = @_;
     my ($Move) = 'mv';
     my ($Delete) = 'rm -f';
     my ($From, $To);

     if ($ENV {'OS'} eq 'Windows_NT') {
         $Move = 'ren';
         $Delete = 'del';
     }

     my $PFN = &fnstrip ($LogFile,2);
     my $Ext = &fnstrip ($LogFile,8);

     while ($Count) {
         $To = "$PFN\.$Count\.$Ext";
         $Count--;
         $From   = "$PFN\.$Count\.$Ext";
         system "$Move $From $To" if -f $From;
     }
     # This will only work if the logfile hasn't been opened yet!
     system "$Move $LogFile $From" if -f $LogFile;
     # $From still contains the ...0.log

     &Exit ($Erc,'') if $Erc;
     &Print2XLog ("Rotating log files ... -> $To", 1);    # To the new log file!
}
#__________________________________________________________________________
1;
