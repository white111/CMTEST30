################################################################################
#
# Module:      Init.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#			 Joe White( mailto:joe@stoke.com )
#
# Descr:      Subs for log files operations
#
# Version:    (See below) $Id: Init.pm,v 1.19 2011/12/12 22:54:28 joe Exp $
#
# Changes:
#			$Ver = 'v1.4 2006/03/01'; # Merge /w v29.2, +userid control, CVS Version #s
#			$Ver = 'v1.5 2006/03/03'; # Fixed 'ambiguous' warning line 531, typo
#			$Ver = 'v1.6 2006/03/29'; # Modified UID Check to give warning only on Development station
#			$Ver = 'v1.7 2006/04/05'; # Added MAC Array
#			$Ver = 'v1.8 2006/04/11'; # Added XML_Tail() to Final(), moved &Print_Out_XML_Tag (); after stats update
#			$Ver = 'v1.9 2006/04/21'; # updates path for user.cfg file
#			$Ver = 'v1.10 2006/07/31'; # fixed partnumber_hash declaration(Thnks PT)
#			$Ver = 'v1.11 2006/07/31'; # Added Secondary IP to Init_also  $UUT_IP_SEC
#			$Ver = 'v1.12 2006/12/07'; # Worked on Status settings, now show UserId,Menu,Started,Active,Exit
#			$Ver = 'v1.13 2007/10/07'; # Updated loop count for CFG log
#			$Ver= 'v1.15 2007/10/07'; # Updated versioning
#			$Ver= 'v1.16 03/09/2010'; #added use Sys::Hostname; to use inplace of EVNV{HOSTNAME}, Linux_gbl
#									Added LogEvent/Cfg Record to support exporting via Email or other
#           $Ver= 'v1.17 2013/10/08'; #Added SFP logging
#
# Still ToDo:
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1993 - 2005 Paul Tindle. All rights reserved.
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################

my $Ver= 'v1.17 2013/10/08'; #Added SFP logging
my $CVS_Ver = ' [ CVS: $Id: Init.pm,v 1.19 2011/12/12 22:54:28 joe Exp $ ]';
$Version{'Stoke'} = $Ver . $CVS_Ver;
#_____________________________________________________________________________
use Sys::Hostname;    #Added for Ubuntu 9.10 support should work with Fedora
use File;
use Logs;
use PT;
#use DataFile;
use Stats qw( %Stats %TestData %Globals $Stats_Path);
use Cwd qw( abs_path );
use Time::HiRes qw(gettimeofday usleep);
#use SigmaProbe::SPUnitReport;
use SigmaProbe::SPTestRun;
use SigmaProbe::SPTimeStamp;
use SigmaProbe::Local;
use Banner;
#__________________________________________________________________________
sub Final {
                                # Last thing that's run before completion
                                # Figures status and creates Event log

    #&Print_Out_XML_Tag ();
    my $ID = $Stats{'UUT_ID'};
    my $slot=0;
    if ( (-s $Out_File) and
        !(($Stats{'UUT_ID'} eq '') and !$Log_All )) {

        my $Stamp = &PT_Date ($Stats{'TimeStamp'}, 9);
              $ID = 'unknown' if $ID eq '';
        $Test_Log = "$TestLogPath/$ID-$Stamp.xml";

        &Exit (999, "Undefined test log path for $Test_Log")
                if ($TestLogPath eq '');

        system "cp -p $Out_File $Test_Log";
        &Exit (7, 'Failed log file copy')
                if (-M $Out_File) != (-M $Test_Log);
    }

    &Stats::Update_Test_Times();

#        $Stats{'Result'} = 'PASS' if $Errors[0] == 0 and
#                                ! $Erc and
#                                $Stats{'Result'} ne 'FAIL';

    $Stats{'Result'} = 'PASS' if $TestData{'TEC'} == 0 and
                                 $Stats{'Result'} eq 'INCOMPLETE';

    $Stats{'Status'} = 'Finished';
    $Stats{'TTG'} = 0;
    &Stats::Update_All;
    &XML_Tail();  #Added JSW - Stoke
    &Print_Out_XML_Tag ();
    &Print_Log (1, "Writing new Event & Cfg Log records ... ");
    &Log_Event ($Op_ID, $PN[0], $SN[0], $TestData{'TID'}, $Stats{'Result'}, fnstrip ($Test_Log,3));
    &Log_Event_Record ($Op_ID, $PN[0], $SN[0], $TestData{'TID'}, $Stats{'Result'}, fnstrip ($Test_Log,3));
    foreach (1..25) {        # Updated for 14 Slot Chassis 1/10/07
        &Log_Cfg ($Op_ID, $SN[0], ($_ - 1), $PN[$_], $SN[$_]) unless $SN[$_] eq '';
        &Log_Cfg_Record ($Op_ID, $SN[0], ($_ - 1), $PN[$_], $SN[$_]) unless $SN[$_] eq '';
        $slot=$_-1;
        if ( $SFPData_slot_ar[($slot)][0]->{'TYPE'} ne '') {
        	foreach (0..15) {
        		if ( $SFPData_slot_ar[($slot)][$_]->{'PowerdBm'} ne '') {
        	        &Log_Cfg ($Op_ID, $SN[0],"$slot:$_","$SFPData_slot_ar[($slot)][$_]->{'Vendor'} $SFPData_slot_ar[($slot)][$_]->{'ModelNo'} $SFPData_slot_ar[($slot)][$_]->{'PowerdBm'}dBm", $SFPData_slot_ar[($slot)][$_]->{'SerialNo'}) unless $SFPData_slot_ar[($slot)][$_]->{'SerialNo'} eq '';
       	        	&Log_Cfg_Record ($Op_ID, $SN[0],"$slot:$_","$SFPData_slot_ar[($slot)][$_]->{'Vendor'} $SFPData_slot_ar[($slot)][$_]->{'ModelNo'} $SFPData_slot_ar[($slot)][$_]->{'PowerdBm'}dBm", $SFPData_slot_ar[($slot)][$_]->{'SerialNo'}) unless $SFPData_slot_ar[($slot)][$_]->{'SerialNo'} eq '';
       	        } else {
        	        &Log_Cfg ($Op_ID, $SN[0],"$slot:$_","$SFPData_slot_ar[($slot)][$_]->{'Vendor'} $SFPData_slot_ar[($slot)][$_]->{'ModelNo'}", $SFPData_slot_ar[($slot)][$_]->{'SerialNo'}) unless $SFPData_slot_ar[($slot)][$_]->{'SerialNo'} eq '';
       	        	&Log_Cfg_Record ($Op_ID, $SN[0],"$slot:$_","$SFPData_slot_ar[($slot)][$_]->{'Vendor'} $SFPData_slot_ar[($slot)][$_]->{'ModelNo'}", $SFPData_slot_ar[($slot)][$_]->{'SerialNo'}) unless $SFPData_slot_ar[($slot)][$_]->{'SerialNo'} eq '';
       	        }
          	}
        }


    }

#       foreach (1..25) {        # Updated for 14 Slot Chassis 1/10/07
#        &Log_Cfg ($Op_ID, $SN[0], ($_ - 1), $PN[$_], $SN[$_]) unless $SN[$_] eq '';
#        &Log_Cfg_Record ($Op_ID, $SN[0], ($_ - 1), $PN[$_], $SN[$_]) unless $SN[$_] eq '';

#    }

     &Send_Email();  #Send our EMail Notifications

#!!!    &Submit_SigmaQuest_Unit_Report;
    &Result ($Stats{'Result'}) if $GUI;

    my @TTime = ($TestData{'TTT'});
    if ($TTime[0] > 60) {
        $TTime[1] = int ($TTime[0]/60);
        $TTime[0] = $TTime[0] - $TTime[1]*60;
        $Test_Time .= "$TTime[1] mins $TTime[0] secs"
    } else {
        $Test_Time .= "$TestData{'TTT'} secs";
    }
   #Create Banner
   my $Result_Txt=Banner->new;
   $Result_Txt->set($Stats{'Result'});
   $Result_Txt->fill($Stats{'Result'});
   my $banner_result = $Result_Txt->get;
   $Result_Txt->set($TestData{'TID'});
   $Result_Txt->fill($TestData{'TID'});
   #$Result_Txt->size(1);
   my $TID_result = $Result_Txt->get;
    &Exit (0, "Finished! ($Test_Time) - $TestData{'TID'} Session:$Stats{'Session'} Result:$Stats{'Result'}!\n$TID_result$banner_result");
}
#_______________________________________________________________
sub First_Time {

    &Print_Log ( 1, "Running First_Time");

    print "\n\tThe main Test Controller configuration file ($Cfg_File) is MIA!\n";
    print "\tPlease copy the defaults file '/var/local/cmtest/dist/cfgfiles/testctrl.defaults.cfg'\n";
    print "\tto /usr/local/cmtest and then edit the definitions as appropriate\n";
    print "\tAborting...\n\n";

    exit;

    # OR eventually ...

    system "java -jar First_Time.jar $Test_Cfg_XMLFile"
        or die "Can't run java form";

    &XML2Hash ($Test_Cfg_XMLFile); #This is now the one modified by Jez's jar

    # Then return to continue reading reading the cfg file
}
#_______________________________________________________________
sub Get_Release_Info {

    my $File = "$GP_Path/bin/Release.id";
    my $Str  = '';

    if (-f $File){

        $Erc = &Read_Cfg_File ($File);
        die "Init died with Erc=$Erc trying to read Cfg_File" if $Erc;                # NB: No Erc translation yet!
        $TestData{'Ver'} = $Version;
        $TestData{'Pipe'} = $Pipe;
        $Str = "Release_Info: File = $File: Version=$Version Pipe=$Pipe";
        if ($Pipe ne $ENV{'CmTest_Release_Pipe'} ) {
        	die  "Init died with Pipe mismatch CMtest pipe:$Pipe diff from ENV pipe:$ENV{'CmTest_Release_Pipe'}";
           }
    } else {
        $Str = "File $File not found!";
    }

    return ($Str) unless $Version eq '';
}
#__________________________________________________________________________
sub Globals {

	#in Cmtest.pl   to support transistion to Ubuntu
	#	$Linux_gbl = 'Ubuntu'; or Fedora

    #use Init_Stoke;  # <- Stoke Specific Globals defined here
    #&Globals_Stoke;



                # Global var defs

    our $Baud            = '9600';        # Updated by TestCtrl.cfg
    our $Bell            = "";
    our $Buffer;                          # Screen Buffer Used by Connect and <OEM>
    our $Cfg_Ptr;                         # pointer to the current child in the Cfg record
    our $CmdFileNestLmt  = 10;            # The max nesting allowed ( recursion limit )
    our $Comm_Log        = '';            # Log file for com app (minicom)
    our $Debug           = 0;
    our $Erc             = 0;
    our $Enable_EE_Write = 0;             # Update EEPROM data if required
    our @Errors          = (0,0,0);       # $Errors[0] = total error count since start of test
    our $Exit_On_Error   = 0;             # Normal State, may be changed in a cmd file
    our $Exit_On_Error_Count;             # 0 = Exit now, otherwise decrement
    our $Exit_On_Timeout = 0;             # Normal state, may be changed in a cmd file
    our $Email_Notification = 0;          # 0 = No email notifications 1 = Send email to test step
#    our $FH              = 'F00';         # Since we now want to test for depth...
    our $FH              = '00';          # Global File Handle
    our $FTest_Ptr       = 0;             # Pointer to $TestData{FTEST}
    our $GUI             = 0;             # enable Tk/Java interfaces, turned on by -g
    our $GUID            = 0;             # Global Unit ID (SigmaProbe)
    our $Home            = $ENV{HOME};    # Will be '' if Win32, but that's OK!
    #our $Host_ID         = $ENV{HOSTNAME};
    our $Host_ID         = hostname;        # usese use Sys::Hostname; for ubuntu and fedora
    our $Key             = 'jThn7zpg';
    our @LBuffer         = ();            # Loop buffer
    our $Log_All         = 0;             # Log unidentified UUTs
    our $Log_Str         = '';            # For passing messages between subs
    our $MacAddr         = '';
    our $Main            = &fnstrip ($0,7); # Script file name without the path

    our $Op_ID           = (defined $ENV{USERNAME}) ? $ENV{USERNAME}
                         : (defined $ENV{USER}) ? $ENV{USER} : 'Unknown';

    our @PN              = ();            # @PN & @SN: [0] = system, [1] = MoBo, ...
    our $Quiet           = 0;             # $opt_q parameter
    our @Screen_Data     = ();            # Array used by Connect for screen data
    our $Startup         = 1;             # Used to deal with startup related errors
    our @SN              = ();
    our @MAC              = ();      			 # Added JW format "xx.xx.xx.xx.xx:x"(mac:qty)
    our $Netmask	  	 = '255.255.255.0'; 		  # Added 1/2/08 format  255.255.255.254.0

    #Use $Exit_On[1] or $Exit_On_Error instead.
#    our $Exit_On_CheckData_Fail  = 0;     # Normal State, may be changed in a cmd file
#!!! From cmtest10_debug...
    our $Exit_On_CheckData_Fail  = 1;     # Normal State, may be changed in a cmd file

    our %Stats           = (                     # Used by the Stats mechanism
            'ECT'        => '',                  # Expected Completion Time
            'ELT'        => '',                  # Expected Loop Time
            #'Host_ID'    => $ENV{HOSTNAME},      # HostID for logging purposes
            'Host_ID'    => hostname,      # HostID for logging purposes use Sys::Hostname; for ubuntu and Fedora
            'Loop'       => 0,                   # Loop counter (and flag!)
            'PID'        => $$,                  # PID for this process
            'PPID'       => getppid,             # PID for shell that launched this
            'Power'      => '',                  # Which power module to switch
            'Result'     => 'INCOMPLETE',        # Final Result
            'Session'    => 0,                   # Session no [1..#Ports on the system]
            'Started'    => &PT_Date (time,1),   # Ascii version of TimeStamp
            'Status'     => '',                  # OK|Running|Finished fluff
            'TimeStamp'  => time,                # Start-time - used for all logging finctions
            'TTG'        => '',                  # (Test) Time To Go ($Stats{ECT} - time)
            'Updated'    => time,                # Time stamp of last update
            'UserID'     => '',                  # User ID / Badge #
            'UUT_ID'     => ''                   # Primary Serial no to be used for logging purposes
        );

    our $Stats_Path      = '';
    our $Tmp             =  "$Home/tmp";

    our %TestData = (
            'ATT'        => 0,                   # Actual Test Time (excl. wait time) (secs)
            'Diag_Ver'   => '',                  # Diag version extracted from header
            'ERC'        => '',                  # The last $Erc reported
            'Power'      => '',                  # Which power module (A|B) was in use (last or on 1st error
            'TID'        => '',                  # Test ID
            'TOLF'       => '',                  # Time Of Last Failure (time code) [set in &Logs::Log_Error]
            'TSLF'       => '',                  # Time Since Last Failure (secs)
            'TEC'        => 0,                   # Total Error Count
            'TTF'        => '',                  # Time To Failure (secs)
            'TTT'        => 0,                   # Total Test Time (secs)
            'SW_Ver'     => '',                  # (UUT Installed) SW Version
            'Ver'        => ''                   # Code version
        );

    our $Test_Log        = '';                   # File name of the (possibly permenant) test results log
    our $TestLogPath     = '';                   # subdirectory of $LogPath
#        $TimeStamp       = time;                 # OBSOLETE - use $Stats
#        $TOLF            = '';;                  # OBSOLETE - Time of last failure
    our $UserID          = '',                   # User ID / Badge #
    our	$User_Level		 = '',					 # User Access level, Coded Decimal in config.
    our %User_ID         = ('');                   # Used [here] for authentication
    our %User_Level         = ('');                   # Used [here] for authentication  Added 7/31/06 JSW
    our $UUT_IP          = '';                   # The IP Address to be assigned for this session
    our $UUT_IP_SEC      = '';           		 # The  Secondary IP Address to be assigned for this session
    our $UUT_Type        = '';;                  # Specific product discovered in boot banner
    our $Verbose         = 0;                    # $opt_v parameter
    our $Wait_Time       = 0;                    # This one will be incremented during waits to offset TTT
    our $XLog            = '';                   # Rotated eXecution Log
    our @XML_Tags        = ();                   # Somewhere to save the tags so to create the end tag

        #
        # The %Globals hash is used to:
        #
        # Define ligitimate global variables:
        #                - if ! defined $$Globals{$Which_Key} then
        #                -                abort with $Erc = $DErc
        #                - elsif $$Globals{$Which_Key} [is non-zero]
        #                -                abort with $Erc = $$Globals{$Which_Key}
        #
        #                - Declare ligitimate but unessential vars by
        #                                'Var' => 0

    our %Globals = (
            CmdFileNestLmt  => 0,
            CmdFilePath     => 21,
            FH              => 0,
            HashDefPath     => 21,
            Location        => 21,
            LogPath         => 21,
            Out_File        => 0,
            PC_IP1          => 0,
            PC_IP2          => 0,
            Power_Switch_IP => 0,
            Startup         => 21,
            Stats_Path      => 21,
            UUT_IP_Base     => 21,
            UUT_IP_Range    => 21
        );
}
#__________________________________________________________________________
sub Init_All {  # This is the 1st Init stage, done before getopts,
                 #  usually called at the beginning of &main::Init

    my ($Util_only) = @_;

    die "\n\tLet\'s not let \'root\' run a test - parochial ownership of files awaits!\n\n"
        if $> == 0 and !$Util_only;

# Acquired from cmtest.pl BEGIN block in v30 2006/02/15

    our $OS = ($ENV {'OS'} eq 'Windows_NT') ? 'Win32' : 'Linux';

    my (@Check_Path) = split (/\/|\\/, $0);
    pop @Check_Path;  pop @Check_Path;      # $FN, then 'bin'
    our $GP_Path = join '/', @Check_Path;   # Now contains our root directory
        $GP_Path = '..' if $GP_Path eq '';      # for a $0 of ./

    our $Cfg_File;
    our $Tmp;

    if ($OS eq 'Win32') {
         $Cfg_File = "$GP_Path/cfgfiles/testctrl.defaults.cfg";
         $Tmp = $ENV{'TMP'};
    } else {
         $Cfg_File = '/usr/local/cmtest/testctrl.cfg';
         $Tmp = "$ENV{'HOME'}/tmp";

    }
          print  ("Tmp directory set to $Tmp \n") if $Debug;

    our $CmdFilePath = "$GP_Path/cmdfiles";

# end [acquired]

    &Globals;

    if (! -d $Tmp) {                # $Tmp is declared in $Globals
        if (-f $Tmp) {
            die "Attempting to create \$Tmp: file $Tmp exists!";
        } else {
            die "Can\'t create tmp directory $Tmp" unless
                mkdir $Tmp;
        }
    }
    if ($Host_ID =~ /^(.*)\..*/) {
        $Host_ID = $1 ; # Remove domain name if appended
    }
#    $Host_ID = $No_Domain[0];

            #Just to keep warnings quiet!:

    $opt_C = '';
    $opt_d = 0;
    $opt_h = 0;
    $opt_q = 0;
    $opt_U = '';
    $opt_v = 0;
    $opt_V = 0;
    $opt_O = '';


    unless ($Util_only) {          # Required for test oriented scripts only ...

        &First_Time unless (-f $Cfg_File);

        $Erc = &Read_Cfg_File ($Cfg_File);  # $Cfg_File is defined in main:: BEGIN block
        die "Init died with Erc=$Erc trying to read Cfg_File \'$Cfg_File\'" if $Erc;                # NB: No Erc translation yet!

        die "Cfg_File doesn\'t exist" unless -f $Cfg_File;    # Temporary, until ...
#        &Check_Global_Vars;

        $Erc = &Log_History (1);
        die "Init died with Erc=$Erc trying to open History log" if $Erc;

        #!!! This where the APC_IP was set up...

#!! Check to make sure that GUID is set

        $TestLogPath = "$LogPath/logfiles";
        &Exit (999, "No permenant log file path >$TestLogPath<") unless
            -d $TestLogPath;

#?!!!         &Stats::Update_All();

    }

}
#__________________________________________________________________________
sub Init_Also {  # This is the 3rd Init stage, done after getopts, etc
                 #  usually called at the end of &main::Init

    my ($Util_only) = @_;

                            # Items to be defined after calling &getopts
    $Debug     = 1 if $opt_d;
    $Quiet     = 1 if $opt_q;
    $GUI       = 1 if $opt_g;
    $Verbose   = ($opt_q) ? 0 : $opt_V;

    print "\n\tDebug=1\n\tQuiet=$Quiet\n\tVerbose=$Verbose\n\n" if $Debug;

    &Show_INCs;

    if ($opt_h) {
            print "$Usage\n";
            exit (0);
    }

    our $GUI = ($ENV{DISPLAY} eq '') ? 0 : 1;        # !!! but what about Win32?
$GUI = 0;

    #!!! we can probably lose this test, since disty.pm is the only declarer
    #     of $Util_Only, since no one else uses Init.pm!
    unless ($Util_only) {        # Session = '' ...

        if ($opt_Z eq '') {
            &Stats::Session ('next');                # Sets the next Session No.
        } else {
            $Stats{'Session'} = $opt_Z;
            my $Pid = &Stats::Session ('read');        # Returns 0 if available
                 # check the process table ...
            if (($Pid and $Pid ne $Stats{'PID'}) or &Is_Running ($Pid, 1)) {
                 # The requested session is already running!
                &Exit (107, "Session $opt_Z declined") unless $Force;
                &Print_Log (11, "Forcing session $opt_Z");
            }
            &Stats::Session ('write');                # Tags the Session.
        }
        $Tmp .= '/s' . $Stats{'Session'};
        mkdir $Tmp unless -d $Tmp;
        &Arc_Logs ($Tmp, '_logs');
        umask 0;

        my $Arc_File = "2arc2\_logs\_" . &PT_Date( $^T, 2 );
        $Arc_File =~ s/\s/_/g;
        $Arc_File =~ s/[\/\:]/\~/g;
        $Arc_File = "$Tmp/$Arc_File";
        system "touch $Arc_File";
    }

            # Set up log files...
    $XLog = "$Tmp/$Main.log";
#    &Rotate_Log ($XLog, 10);

        #!!!    &Read_Version;
    my $Msg = &Get_Release_Info;      # Sets $Version, etc
                                          # Aborts on error!
    print "\n\n" unless $Quiet;
    $Log_Str .= "Session $Stats{'Session'}: " if $Stats{'Session'};
    $Log_Str .= "Starting $Main version $TestData{'Ver'} at " . &PT_Date(time, 2);

    $Erc = &Print_Log (1, $Log_Str);
    $Log_Str = '';
    &Exit (3, "($XLog)") if $Erc;
    &Print_Log (11,"This PID = $Stats{'PID'}, ShellPID = $Stats{'PPID'}");
    &Print_Log (11, 'path = ' . abs_path ($GP_Path));

    foreach $Module ( keys %INC ) {
        my $Vers = $Version{fnstrip ($Module, 7)};
        $Module  = $INC{$Module};  #Value (Full path / filename)
        if (substr ($Module, 0, 1) eq '.') {
            $Module = `pwd` . "/$Module";
        }
        $Log_Str = "Lib: $Module";
        $Log_Str .= "\t[Ver: $Vers]" unless $Vers eq '';
        &Print_Log (11, $Log_Str)
                    unless $Module =~ /perl/;
        my $IncAge = time - (-M $Module);
        &Print_Log (1, "Using new $Module") if $IncAge < 1000;
    }
    $Log_Str = '';

    unless ($Util_only) {                 # Required for test oriented scripts only ...

        &Abort ('clear');             # Remove any lurking abort flags
        $Stats{'Status'} = 'UserID';
        $Stats {'Power'} = 0;  #Power supply on count
     	&Stats::Update_All ;
        print "\n";
        if ($opt_U eq '') {
            my $X = &Ask_User ( 'text16', 'UserID', 'Please enter your UserID#' );
        } else {
            $UserID = $opt_U;
        }

        my $UserID_tmp = $UserID;
        $UserID = crypt $UserID, $Key;
        &UID_Check ($UserID_tmp);  #Exit on fail!  Use adduser.pl ...

        $Stats{'UserID'} = $UserID;
        $Stats{'Status'} = 'Menu';
        &Stats::Update_All();

        $Comm_Log = "$Tmp/Comm.log";
        # system "rm -f $Comm_Log";        # OR
#        &Rotate_Log ($Comm_Log, 10);
                                                        # Aborts on error!
        &Abort ('check');             # Make sure there isn't an ABORT flag lurking

                                      # Figure the UUT_IP address ...

        my (@IPA) = split (/\./, $UUT_IP_Base);
        my $UUT_IP_Top = $IPA[3] + $UUT_IP_Range - 1;        # Highest sub allowed
        $IPA[3] += ($Stats{'Session'} - 1);            # 1 per session or
        &Exit (28, "No IP addr available for this session") if $IPA[3] > $UUT_IP_Top;
        $UUT_IP  = "$IPA[0]\.$IPA[1]\.$IPA[2]\.$IPA[3]";
        $IPA[3]++; ##$IPA[3]++;  There is a possibility of conflict, but we shuld end up using 2 session if the second IP is used.
        &Exit (28, "No Secondary IP addr available for this session") if $IPA[3] > $UUT_IP_Top;
        $UUT_IP_SEC  = "$IPA[0]\.$IPA[1]\.$IPA[2]\.$IPA[3]";

        &Print_Log (11, "UUT_IP  = $UUT_IP");
        &Print_Log (11, "CmdFilePath = $CmdFilePath");

                        # Assign the output file ...

        $Out_File = ($opt_O eq '') ? "$Tmp/cmtest.xml" : $opt_O;
        system "rm -f $Out_File";
        &Print_Out_XML_Tag ('Test');

        $Erc = 0;
        &Stats::Update_All;

        $PT_Log = "$Tmp/Expect.log";
        system "rm -f $PT_Log";

        $shucks = 0;
        $SIG{INT} = \&catch_zap;
#        $SIG{QUIT} = \&catch_zap;
    }
        # "Get set, ..... GO!....."
}
#----------------------------------------------------------------
sub catch_zap { # Striaght out of PPv3:413
    my $signame = shift;
    our $shucks++;
    &Power ('OFF');
    $Stats{'Status'} = 'Aborted';

    &Exit(998,"<Ctrl>-C Aborted");

}
#_______________________________________________________________
sub Invalid {

        my ($Usage) = @_;
        print "$Bell$Usage";
        exit ($Erc);

}
#_______________________________________________________________
sub Mk_Port {

    my $Port = $Stats{'Session'};
    my $File = "/etc/minirc.$Port";
    $File = "/etc/minicom/minirc.$Port" if $Linux_gbl eq 'Ubuntu';

    my $UMask = umask; umask 0;

    open OUT, ">$File" or &Exit (35, "Can\'t cpen minicom cfg file $File for port $Port");

    print OUT "# Machine-generated file created " . localtime() . "\n";
    print OUT "pr port             $SPort[$Port]\n";
    print "Setting buad rate to $Baud \n";  # Baud is from testctlr.cfg and menu execution
    print OUT "pu baudrate         $Baud\n";
    print OUT "pu minit\n";
    print OUT "pr rtscts           No\n";
    print OUT "pu histlines        4000\n";

    close OUT;
    umask $UMask;
}
#_______________________________________________________________
sub UID_Check {  # $UserID strarts out as an encypted pw, then ->user_name

    my ($Tmp) = @_;

    # $UserID is our global, to be retrieved from %User_ID{PW}

    $Erc = &Read_Data_File ("/usr/local/cmtest/users.cfg");   # was $GP_Path/cfgfiles/users.cfg
    &Exit ( 999, "Can't read User cfg file") if $Erc;

#    &Print_Debug;  $uid.pl

    my $Msg = "UID_Check: Key=\'$UserID\', ";
    $User_Level = $User_Level{$UserID};
    $UserID = $User_ID{$UserID};
    $Msg .= "UID=" . $Tmp . ', ' if $UserID eq '';
    $Msg .= "User=$UserID Level=$User_Level";
    &Print_Log (11, $Msg);
    if ($Development eq 0) {
    	&Exit ( 999, "Failed user authentication")  if ($UserID eq '') ;
    } else {
    	&Print2XLog ("Warning: Failed user authentication\n") if ($UserID eq '');
    	}

    return ();
}

#__________________________________________________________________________
1;
