################################################################################
#
# Module:      Logs.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#			 Joe White( mailto:joe@stoke.com )
#
# Descr:      Subs for log files operations
#
# Version:    (See below) $Id: Logs.pm,v 1.10 2011/01/21 18:38:56 joe Exp $
#
# Changes:
#			$Version{'Logs'} = '16   2006/05/19'; #Log_Error can now &Exit
#           Modified Log_error, to finalize logs on toomay Checkdata errors
#           Modified log error to send errors to XML file, Added Log_MAC
#			$Version{'Logs'} = '1.3.2   2006/08/18'; #Added &Get_Cfg_Recs ( Yield.pl, ...)
#           HiRes logging
#           print2xlog() $Msg = $HA_Msg . ' ' . $Msg if (defined $HA_Msg && $HA_Msg ne '');  # Added For HA
#			Ver= 'v16.1 1/31/2008'; # Updated versioning
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
my $Ver= 'v16.2 1/31/2008'; # Add ANSI color, Print Log errors in red
my $CVS_Ver = ' [ CVS: $Id: Logs.pm,v 1.10 2011/01/21 18:38:56 joe Exp $ ]';
$Version{'Logs'} = $Ver . $CVS_Ver;
#_____________________________________________________________________________

use Time::HiRes qw(gettimeofday tv_interval);
use Term::ANSIColor;
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
#__________________________________________________________________________
sub Get_Cfg_Recs {   # Called by someone with an Event rec data looking for child cfg
                     # records. It requires handle <CFG> to already be open for read

    my ($Date, $Location, $HostID, $Parent_ID, @SN_Masks) = @_;
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
            &PrintLog ($_, 1);
        };
     }

       #0: $Type, 1: $Date, 2: $Location, $HostID, $OpID, $Parent_ID, $Slot, $PN, $SN)
#    &PETC("Cont.d...");
    my $Msg = '';
    foreach (@gBuf) {

        my ( @Rec )  = split /\;/;
        my $SNum = $Rec[8];

        my $SN_Match = (@SN_Masks) ? 0 : 1; # Assume a match if no mask list provided
        &PrintLog("SN_Match[0]=$SN_Match",1) if $Debug;

        foreach ( @SN_Masks ) {
            $SN_Match = 1 if $SNum =~ /^$_/;
        }
        &PrintLog("SN_Match[1]=$SN_Match",1) if $Debug;

#        #!!! Still in debug ...
#        foreach ( @Exclude ) {
#            $SN_Match = 0 if $SNum =~ /^$_/;
#        }
#        &PrintLog("SN_Match[2]=$SN_Match",1) if $Debug;

        if (($Rec[2] eq $Location)   and
            ($Rec[3] eq $HostID)     and
            ($Rec[5] eq $Parent_ID)) {
            #  and
            # ($SN_Match)){

                $Msg .= ', ' . $SNum;
                push @Cfg_Recs, $SNum;
       }
        #, $Date, $Location, $HostID, $OpID, $Parent_ID, $Slot, $PN, $SN)
    }
    &PrintLog("Returned: $Msg", 1);

    our (@gBuf) = $Buf;        # Just the last one

    return ( @Cfg_Recs )
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

        print OUT "2;$Stats{'TimeStamp'};$Location;$Host_ID;$Op_ID;$Sys_ID;$Slot;$PN;$SN;\n";
        &File_Close (OUT);
}
#__________________________________________________________________________
sub Log_Cfg_Record {        # Write a single (parent / child) record. Caller must construct
                                # sequence of invocations to create all the necessary records
                                # to describe the DUT

        # Event log is a 'Type 2' record:
        # 2;Date;Location;HostID;OpID;Parent_ID;Slot;Part_No;Serial_No;

        my ($OpID, $Sys_ID, $Slot, $PN, $SN) = @_;
        # (NB $TimeStamp, $Location, $Host_ID and $Op_ID are global, declared in &Init_All)

        my ($File) = "$Tmp/Cfg.log";           # Send to $tmp dir so we can email or export record

        &Exit (1, $File) if &File_Open ($File, OUT, '>>');

        print OUT "2;$Stats{'TimeStamp'};$Location;$Host_ID;$Op_ID;$Sys_ID;$Slot;$PN;$SN;\n";
        &File_Close (OUT);
}
#__________________________________________________________________________
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
    print color 'red';
    &Print_Log (2, 'Log_Error: ' . $Msg);
    #Added JSW 051906 Adding Error Messages to XML file
    &Print_Out_XML_Tag("Error");
    	&Print_Out( '		Log_Error: ' . $Msg);
    &Print_Out_XML_Tag();
    print color 'reset';
    if ($Exit_On_Error) {
       $Exit_On_Error_Count--;
       # THis must be Erc=0 to avoid dancing forever with $Exit
       #&Exit (0, "Exit_On_Error") if $Exit_On_Error_Count < 1;
       if ($Exit_On_Error_Count < 1){  # if Error count reached Exit
       &Print_Log (2, 'Exit on too Many Errors ');
       #&Exit (0, "Exit_On_Error");
       &Final;
       }
    }
    return (0);
}
#__________________________________________________________________________________
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

        print OUT "1;$Stats{'TimeStamp'};$Location;$Host_ID;$Op_ID;$PN;$SN;$TID;$Result;$Data;$Ptr;\n";
        &File_Close (OUT);
}
#__________________________________________________________________________________
sub Log_Event_Record {                # Write a test event record

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

        my ($File) = "$Tmp/Event.log";          #Send to Current directory so we can Email or export data

        foreach $Key ( sort keys %TestData ) {
                $Data .= "$Key=$TestData{$Key},"
                        if $TestData{$Key} ne '';
        }
        chop $Data;
        print "We are in Log_Event_Record\n" if $Debug;
        &Exit (1, $File) if &File_Open ($File, OUT, '>>');

        print OUT "1;$Stats{'TimeStamp'};$Location;$Host_ID;$Op_ID;$PN;$SN;$TID;$Result;$Data;$Ptr;\n";
        &File_Close (OUT);
}
#__________________________________________________________________________________

sub Log_History {                        # Log script start / end activity

        my ($Type) = @_;
        my ($LogFile) = "$LogPath/history.log";
        my ($Msg) = &PT_Date (time, 1) . ":\t$Stats{'TimeStamp'}";

        $Msg .= "\t$Op_ID\t" . $Stats{'Host_ID'};
        $Msg .= "-$Stats{'Session'}" if $Stats{'Session'};
        $Msg .= "\t";

        die "\$LogPath not defined in \&Logs::Log_History"
                if $LogPath eq '';

        SWITCH: {
                if ($Type == 1) { $Msg .= "Starting $Main ... "; last SWITCH; }
                if ($Type == 2) { $Msg .= "Ending $Main";                last SWITCH; }
                &Exit (999, '(Invalid call to Log_History)');
        }

                                                # This next one needs to be a 'die' since &Exit will &Log_History!
        open (LOG, ">>$LogFile") || die ("Can\'t open History file $LogFile");
        print LOG "$Msg\n";
        close LOG;

        return (0);
}
#________________________________________________________________________________________
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
             	#my $orig_date  = &PT_Date($Date, 7);
                return (3, "MAC $MAC already assigned to $Prod_ID");
            }
         }
      }
     &File_Close (IN);
     return (0) if $Found;
+
+ #    $ID4MAC{$MAC_Addr} = $Product_ID; # from args
+
+ #    foreach $Key ( sort keys %TestData ) {
+ #            $Data .= "$Key=$TestData{$Key},"
+ #                    if $TestData{$Key} ne '';
+ #    }
+ #    chop $Data;

     &Exit (1, "Can\'t open $File for cat") if &File_Open ($File, OUT, '>>');

     my $Time = (defined $Stats{'TimeStamp'}) ? $Stats{'TimeStamp'} : time;

     print OUT "4;$Time;$Product_ID;$MAC_Addr\n";
     &File_Close (OUT);

      return (0);
  }

  #________________________________________________________________________________________
 sub Log_MAC_Record {   # First checks to make sure this MAC address has not been used before
                 # then cats a new record to MAC.log

     # MAC log is a 'Type 4' record:
     # 4;Date;Product_ID;MAC_Address;
     # eg:    4;1134001942;0020140050000031;00-12-73-00-0E-40

 #    our @ID4MAC = ();

     my ($Product_ID, $MAC_Addr) = @_;

     my ($File) = "$LogPath/MAC.log";

     &Exit (1, "Can\'t open $File for Record read") if &File_Open ($File, IN, '<');

     my $Found = 0;
     while (<IN>) {

         chomp;
         my ($Type, $Date, $Prod_ID, $MAC) = split /;/;
         if ($MAC eq $MAC_Addr) {
             $Found = 1;
             if ($Prod_ID ne $Product_ID) {
             	#my $orig_date  = &PT_Date($Date, 7);
                return (3, "MAC $MAC already assigned to $Prod_ID");
            }
         }
      }
     &File_Close (IN);
     return (0) if $Found;
+
+ #    $ID4MAC{$MAC_Addr} = $Product_ID; # from args
+
+ #    foreach $Key ( sort keys %TestData ) {
+ #            $Data .= "$Key=$TestData{$Key},"
+ #                    if $TestData{$Key} ne '';
+ #    }
+ #    chop $Data;

     &Exit (1, "Can\'t open $File for cat") if &File_Open ($File, OUT, '>');

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

     unless ($New_Log) { #!!! Required for Win32 - otherwise really slow! (Opened in Yield.pl)
         open (LOG, ">>$XLog") || return (3);
     }
     print LOG $TimeField, ":\t$Tag\t$Msg\n";
     unless ($New_Log) {
         close LOG;
     }

     our $Last_Log_Time = time;

     return (0);
}

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
