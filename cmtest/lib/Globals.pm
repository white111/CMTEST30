################################################################################
#
# Module:     Globals.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#			 Joe White( mailto:joe@stoke.com )
#
# Descr:      Define Cmtest globals
#
# Version:    (See below) $Id: Globals.pm,v 1.9 2011/12/12 22:54:28 joe Exp $
#
# Changes:
#			1 09/18/05  Cloned from init
#			1.2	Added AX4000_IP to global assignments
#           1.3 Added Addtion CFG file definitions
#			1.4 Added MAC array
#			1.5 use Sys::Hostname;
#			1.6 Added PSOC_GLB for change to PSOC power controller
#			1.7 Added Power_Switch2_IP for second APC control
#
# Still ToDo:
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1993 - 2005 Paul Tindle. All rights reserved.
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################
my $Ver= 'v1.7 5/4/2012'; #1.7 Added Power_Switch2_IP for second APC control
my $CVS_Ver = ' [ CVS: $Id: Globals.pm,v 1.9 2011/12/12 22:54:28 joe Exp $ ]';
$Version{'Globals'} = $Ver . $CVS_Ver;
#______________________________________________________________________________

use Sys::Hostname;    #Added for Ubuntu 9.10 support should work with Fedora
                # Global var defs
    our $Products = 'SSX';
    our $CMPipe=$ENV{'CmTest_Release_Pipe'};
    #our $AX4000_IP       = 'AX4000';      # Updated by TestCtrl.cfg
    #our $AX4000_USER     = 'AX4000';      # Updated by TestCtrl.cfg
    our $DefFanSpeed     = 'High';        # Updated by TestCtrl.cfg
    our $Debug_UUT     = 0;        	  	  # Updated by TestCtrl.cfg, Default off
    our $Development	= 0;      		  # Updated by TestCtrl.cfg, Default off
    our $UUT_Ver_check	= 1; 			  # Default is to check for versions
    our @UUT_Variable_ref = ();			  # Reference to hash values pulled from uutcfg dir
    our $Term_Msg		  = "";			  # Modifies the output prompt when set(used by Init Termserver
    our $TelnetEscape	  = "[";		      # ctrl[ modifies the telnet excape when using a daisy chanied terminal server (test equipment->dut)

    our $Baud            = '9600';               # Updated by TestCtrl.cfg
    our $Bell            = "";
    our $Comm_Log        = '';                   # Log file for com app (minicom)
    #        %Data            = ();                   # Array used by Connect for screen data
    our @Screen_Data     = ();                   # use this instead
    our $Debug           = 0;
    our $Erc             = 0;
    our $Enable_EE_Write = 0;                    # Update EEPROM data if required
    our @Errors          = (0,0,0);              # $Errors[0] = total error count since start of test
    our $Exit_On_Timeout = 1;                    # Normal state, may be changed in a cmd file
    our $Email_Notification = 0;          # 0 = No email notifications 1 = Send email to test step
    our $FH              = 'F00';                # Global File Handle
    our $FTest_Ptr       = 0;                    # Pointer to $TestData{FTEST}
    our $GUI             = 0;                    # enable Tk interfaces, turned on by -g
    our $GUID            = 0;                    # Global Unit ID (SigmaProbe)
    our $Home            = $ENV{HOME};           # Will be '' if Win32, but that's OK!
    #our $Host_ID         = $ENV{HOSTNAME};
    our $Host_ID         = hostname;      # uses use Sys::Hostname;
    our @LBuffer         = ();                   # Loop buffer
    our $Log_Str         = '';                   # For passing messages between subs
    our $MacAddr         = '';
    our $Main            = &fnstrip ($0,7);      # Script file name without the path

    our $Op_ID           = (defined $ENV{USERNAME}) ? $ENV{USERNAME}
                         : (defined $ENV{USER}) ? $ENV{USER} : 'Unknown';

    our @PN              = ();                   # @PN & @SN: [0] = system, [1] = MoBo, ...
    our $Quiet           = 0;                    # $opt_q parameter
    our @SN              = ();
    our @MAC              = ();      			 # Added JW format "xx.xx.xx.xx.xx:x"(mac:qty)

    our %Stats           = (                     # Used by the Stats mechanism
            'ECT'        => '',                  # Expected Completion Time
            'ELT'        => '',                  # Expected Loop Time
            #'Host_ID'    => $ENV{HOSTNAME},      # HostID for logging purposes
            'Host_ID'    => hostname,      # # uses use Sys::Hostname; for ubuntu and fedora
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
            'Pipe'        => $ENV{CmTest_Release_Pipe}                   # Code Pipe Selected
        );

    our $Test_Log        = '';                   # File name of the (possibly permenant) test results log
    our $TestLogPath     = '';                   # subdirectory of $LogPath
    #        $TimeStamp       = time;                 # OBSOLETE - use $Stats
    #        $TOLF            = '';;                  # OBSOLETE - Time of last failure
    our $UUT_IP          = '';                   # The IP Address to be assigned for this session
    our $UUT_IP2         = '';                   # The IP Address to be assigned to the next session
                                                 #  (we need to know this for systest run)
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
            CmdFilePath     => 21,
            HashDefPath     => 21,
            Location        => 21,
            LogPath         => 21,
            Out_File        => 0,
            PC_IP1          => 0,
            PC_IP2          => 0,
            Power_Switch_IP => 0,
            Power_Switch2_IP => 0,
            Stats_Path      => 21,
            UUT_IP_Base     => 21,
            UUT_IP_Range    => 21
        );
#__________________________________________________________________________
1;
