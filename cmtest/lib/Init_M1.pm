################################################################################
#
# Module:      Init_Mav.pm
#
# Author:      Joe White( mailto:joe@stoke.com )
#
# Descr:       Stoke Globals
#
# Version:    (See below) $Id: Init_Stoke.pm,v 1.33 2012/02/17 17:13:42 joe Exp $
#
# Changes:    Created 1/5/15

#
# Still ToDo:
#
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1993 - 2005 Paul Tindle. All rights reserved.
#            Copyright (c) 2005-2015 Mavenir. All rights reserved.
#
################################################################################
my $Ver= 'v3.18 012915'; #Name Changes to Mavenir
my $CVS_Ver = ' [ CVS: $Id: Init_Stoke.pm,v 1.33 2012/02/17 17:13:42 joe Exp $ ]';
$Version{'Init_SSX'} = $Ver . $CVS_Ver;
#__________________________________________________________________________
sub Globals_M1 {
	#   Added HA Varialbes
	 &Print2XLog ("Setting up M1 variables");
	our $Product_gbl = 'M1';
	our $Tmp_HA             =  "$ENV{HOME}/tmp" ;
    our $Opening_session = 0;
    our $HA_Session = 0;
    our $HA_Session_N = 1;
    our $Comm_Log_HA = ''; # Log file for com app (minicom) HA
    our ($Comm_HA);     # Handle for Expect HA
    our ($Comm_Start);  # Our defualt at startup
    our ($Comm_Current);  # What we ar currently pointing too
    our $HA_Msg = ''; # Msg added to Print2Xlog

 # Hashes from uutcfg/* ( need to be added as they are put into use)
 	#uutcfg/termserver.cfg
     	our %Default_Termserver_Config = ('');
     	our %Ship_Config_TermServer = ('');
        our %Term_Slot_Port_Map  = ('');


    ## SSX Stuff for Reference
#    #    Imbedded variables
#    our $Bench_card_type_gbl = 'null.inc'; #Accuired from GetData POST, used for determing IMC or GLC benchtest
#    our $Bench_Prog_card_type_gbl = 'null.inc';
#    our $glc_type_str_gbl = "2-port";     # GLC port count for testing, from get_board_info, get_chassis_info, get_config_info
#    our $Slot_1_NOT_IMC_GBL = 0;
#    our $P20_NOT_INSTALLED_GBL = 0; # This is set during chassis test if tlv 99 returns this string
#    our $P20_INSTALLED_GBL = 1;
#    our $Firstboot_Dual_IMC_GBL = 0;

#    # Version Control variable used during Config checkout - Actual values are set in Get_software_release
#    our $release_name_global = "13.1R5S1_2.9_diag" ;
#    our $tftp_path_gbl = "/tftpboot";
#    my  $tftp_copypath_release = "OS_A";
#    our $tftp_copypath_release_gbl = "$tftp_copypath_release/";
#    our $tftp_bootpath_release_gbl = "$tftp_copypath_release/";
#    #Strings presented by Stoke OS show version and ISSU package select
#    our $StokeOS_release_gbl = "13.1R5";  #Must match release for links into hdp/images StokeOS Release 6.0 (2011121701).
#    our $StokeOS_release_Build_gbl = "";
#    our $StokeOS_ISSU_Apply_gbl = "$StokeOS_release_gbl$StokeOS_release_Build_gbl";
#    our $StokeOS_ISSU_Install_gbl = "StokeOS-$StokeOS_release_gbl$StokeOS_release_Build_gbl";
#    our $StokeOS_builddate_gbl = "2014062706";     #6.0 (2012011901)  StokeOS Release 6.0 (2012071619
#    our $Software_OS_release_gbl = "StokeOS Release $StokeOS_ISSU_Apply_gbl .$StokeOS_builddate_gbl";
#    our $Stoke_bootloader_ver_gbl = "Stoke Bootloader Release $StokeOS_ISSU_Apply_gbl .$StokeOS_builddate_gbl";
#    our $show_sys_ISSU_in_use_gbl = "$StokeOS_ISSU_Apply_gbl  Current Version  .StokeOS Release $StokeOS_ISSU_Apply_gbl .$StokeOS_builddate_gbl";
#    #our $show_sys_ISSU_other_gbl = "$StokeOS_release_gbl\\S5  .StokeOS Release $StokeOS_release_gbl\\S5 .$StokeOS_builddate_gbl";

#    our $Stoke_boot_ver_gbl = "StokeBoot Release 6.0 .2013011510.";
#    our $Stoke_boot_XGLC_ver_gbl = "StokeBoot Release .6.0 2013011510.";

#    our $firmware_ver_gbl = "91";
#    our $firmware_ver_xglc_gbl = "0B";
#    #diag path              xx
#    our $diag_ver_gbl = "diag_A";
#    #our $diag_ver_gbl = "layne010307";
#    our $tftp_copypath_diag_gbl = "$diag_ver_gbl/";   #diag072106, diag080706
#    our $tftp_bootpath_diag_gbl = "$diag_ver_gbl/";

#    our $Diag_boot_ver_gbl = "/stoke/bin/dia";
#    #our $Diag_boot_ver_gbl = "2253225765.*/stoke/bin/dia";
#    our $Diag_boot_ver_cmd_gbl = "cksum /stoke/bin/diag";

#    #GLC redunancy settings  Check_GLC_Redundancy
#    our $glcredundant_gbl = 0 ;
#    our $noglcredundant_gbl = 1 ;

#    #Default names for files copied
#    our $Stoke_image = "stoke.bin";
##    our $StokeS1_pkg = "stokeS1.pkg";
#    our $Stoke_pkg = "stokepkg.bin";
#    our $Stoke_config = "stoke.cfg";
#    our $Stoke_uboot = "stokeboot.bin";
#    our $Stoke_ubootxglc = "stokebootxglc.bin";
#    our $Stoke_bootloader = "bootloader.bin";
#    our $Stoke_bootloader2 = "bootloader2.bin";
#    our $Stoke_noodle = "noodle.bin";
#    our $Stoke_diag_glc = "diag_glc.bin";
#    our $Stoke_diag_xglc = "diag_xglc.bin";
#    our $Stoke_onscript_GLC = "GLC.ksh";  # local script on cardbus for parallel memory tests during BI/Ext
#    our $Stoke_onscript_MC = "IMC.ksh";
#    our $Stoke_onscript_XGLC = "XGLC.ksh";
#    our $Format_40gig_MC = "formatto40gigpartition.sh";
#    our $Format_MC = "storageprep80.sh";
#    #our $Diag_cfint_boot_gbl = "boot image file $Stoke_diag ";
#    our $Diag_boot_xglc_gbl = "boot image file /hd/mfg/$Stoke_diag_xglc ";
#    our $Diag_boot_glc_gbl = "boot image file /hd/mfg/$Stoke_diag_xglc ";
#    our $Diag_cfint_boot_gbl = $Diag_boot_glc_gbl;
#    print ("Current Software release: $release_name_global \n");
#    print ("Current Diag release: $tftp_bootpath_diag_gbl\n");




#    # Stoke Specific Globals
#    our $Bypass         = 0;              # Controls command bypassing are we in a by pass section
#    our $Cmd_Bypass         = 0;              # Controls command bypassing, do we want to bypass code
#    our $DefFanSpeed     = 'High';        # Updated by TestCtrl.cfg
#    #our $Debug_UUT     = 0;                  # Updated by TestCtrl.cfg, Default off
#    #our $Development   = 0;              # Updated by TestCtrl.cfg, Default off
#    our @Email_Config               = ('');       # Email notification list for Config tests
#    our @Email_Config_CC                = ('');       # Email notification list for Config tests
#    our @Email_Config_Records               = ('');       # Email notification list for Config tests
#    our @Email_Ship             = ('');       # Email notification list for Config tests
#    our @Email_Ship_CC              = ('');       # Email notification list for Config tests
#    our @Email_Ship_Records             = ('');       # Email notification list for Config tests
#    our $UUT_Ver_check  = 1;              # Default is to check for versions
#    # Hashes from parts.cfg, and part number files( need to be added as they are put into use)
#    our %partnumber_hash = ('');            # Fixed 7/31/06 JSW
#    our %partnumber_hash_out  = ('');
#    our %partnumber_lookup    = ('');     # Fixed 7/31/06 jsw
#    our %allowed_partnumber_rev = ('');   # Fixed 7/31/06 jsw
#    our %UUT_Variable_ref     = ('');     # Fixed 7/31/06 jsw, Holds pointers to varibles in each slot, Read only please
#    our %UUT_Variable     = ('');
#    our %UUT_02233           = ('');  #example

#    our @TIDs               = ('');     # Holds the valid Test Ids in order executed
#    our @CFG_Entrys         = ('');     # Holds Serial number searches of CFG file, reversed for latest entry first
#    our @Event_Entrys       = ('');     # Holds Serial number searches and timestamp of Event file, reversed for latest entry first


#    our %partnumbers     = ('');
#    our $Printer       = 'none';          # Updated by TestCtrl.cfg
#    our $Post_GBL   = 0;                # Added for Detecting both Gen1 and Gen2 post
#    our $Post_N_GBL = 1;                # Added for Detecting both Gen1 and Gen2 post
#    our $Last_KeyWord = '';               # Last send command Keyword
#    our $Last_Send = '';                  # Holds last Arg from Send command

#    our $slot_gbl = "" ;



# #Declared in Init, (re)assigned here...

#          # our        $Exit_On_CheckData_Fail  = 0
#    if ($Development) {$Exit_On_Error   = 0;} else {$Exit_On_Error   = 1;}
#    $Exit_On_Error_Count = 0;  # 0 = Exit now, otherwise decremented
#    $Exit_On_Timeout = 0;

#    $Stats{'SW_Ver'} =$release_name_global  ;
#    $Stats{'Diag_Ver'} =$diag_ver_gbl  ;

##    #More imbeded varibles
##    #5 slot mapping       Ch, S0, S1, S2, S3, S4,x,x,x,x,x,x,x,x,x,x,S15,x,x,S18,S19,x,S21,S22
##    #                     Chasss, Slot 0, Slot 1, Slot 2, Slot 3 , slot 4, S15 Alarm, S18  PEM A, S19 PEM B, S21 Fan 1, S19 Fan 2
##    #Full 5 slot Chassis        (1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,1)
##    our $Full_Chassis_str_GBL = "none";
##    our $Full_Chassis_GBL = 0;  # 0 = Not full chassis, 1 Full Chassis
##    our $Full_Chassis_FRU_GBL = 0; # Chassis fru modules  chassis, alarm, fan pem
##    our @Slot_INST_GBL = (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);  # variable for Slot installed
##    our $Slot_INST_0_1_GBL = 0;    #Product of Slot_INST_GBL
##    our $Slot_INST_0_2_GBL = 0;    #Product of Slot_INST_GBL
##    our $Slot_INST_0_3_GBL = 0;    #Product of Slot_INST_GBL
##    our $Slot_INST_0_4_GBL = 0;    #Product of Slot_INST_GBL
##    our $Slot_INST_1_2_GBL = 0;    #Product of Slot_INST_GBL
##    our $Slot_INST_1_3_GBL = 0;    #Product of Slot_INST_GBL
##    our $Slot_INST_1_4_GBL = 0;    #Product of Slot_INST_GBL
##    our $Slot_INST_2_3_GBL = 0;    #Product of Slot_INST_GBL
##    our $Slot_INST_2_4_GBL = 0;    #Product of Slot_INST_GBL
##    our $Slot_INST_3_4_GBL = 0;    #Product of Slot_INST_GBL
##    #Can't use array varibles in cmdfiles
##    our $Slot_INST_0_GBL = 0;
##    our $Slot_INST_1_GBL = 0;
##    our $Slot_INST_2_GBL = 0;
##    our $Slot_INST_3_GBL = 0;
##    our $Slot_INST_4_GBL = 0;
##    our $Slot_INST_1_IMC_GBL  = 0;
##    our $Slot_INST_1_GLC_GBL  = 0;
##    #Varibles for R1.1 Show env(does not work with older rev cards)
##    our $Slot_SHOWENV_0_GBL = 0;
##    our $Slot_SHOWENV_1_GBL = 0;
##    our $Slot_SHOWENV_2_GBL = 0;
##    our $Slot_SHOWENV_3_GBL = 0;
##    our $Slot_SHOWENV_4_GBL = 0;
##    our $Production_GBL = 1;  # Variable to indicate in Production or final configuration test, Default Production mode
##    #Varible used in "Set fab snake xxxxx" command, sets card type by slot, 0 = not inst, 1 = MC 2 = GLC 2=port, 4 = GLC 4 port
##    #Vales set when serial number collected
##    our $Slot_CARD_TYPE_INST_0_GBL = 0;
##    our $Slot_CARD_TYPE_INST_1_GBL = 0;
##    our $Slot_CARD_TYPE_INST_2_GBL = 0;
##    our $Slot_CARD_TYPE_INST_3_GBL = 0;
##    our $Slot_CARD_TYPE_INST_4_GBL = 0;
##    #Default used for  Traffic snake test, changed by Get_Mesh_slots
##    our $internal_traffic_test_time_GBL = 900;
##    our $internal_traffic_test_timeout_GBL = 1000;
##    our $internal_traffic_test_time_msg_GBL = "Send Traffic for $internal_traffic_test_time_GBL Seconds";
##    #Default fan speeds changed by get_mesh_slots and testctrl.cfg
##    our $FanSpeed1_GBL = "wr i2c 9501 fan1 gpio E7"  ;
##    our $FanSpeed2_GBL = "wr i2c 9501 fan2 gpio E7"  ;
##    our $Fan2Speed1_GBL = "wr i2c adm1029 1 60 BB";
##    our $Fan2Speed2_GBL = "wr i2c adm1029 2 60 BB";
##    our $FanSpeed_MSG_GBL = "All Fans on High"  ;


#    ####################################################################
#    ## Global Varibles being pulled from UUT CFG directory



#    ###################################################################
######  Start Potentia compare lists,  these are cutand past from Potenta save as Hex option
######  Add a line at the start with Key word Potentia and then Potentia number and version
#       # GLC Potentia 0  V5

##__________________________________________________________________________
##XGLC Added Variables
#our $crc32_match_gbl = 0;
#our $crc32_str_gbl = "na";
#our $postinfo_XGLC_str_found = 0;
#our $xfersizehex_str_gbl = "na";
#our $xfersizebyte_str_gbl = "na";
#our $linkinfo_XGLC_str_found = 0;
#our $compare_gbl = 0;
#our @XGLC_1gigSFP_gbl = ([0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],    );   #[Slot][Port];  # 1= enable/do not bypass # Varible to enable use of 1gig SFPs 10/9/12
#                            #Added to bench test as of 10/9/12, Remainder TBD
#our @XGLC_10gigSFP_gbl = ([0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],    );   #[Slot][Port]
#our @XGLC_10gigLRSFP_gbl = ([0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],    );   #[Slot][Port]
#our @XGLC_1gigCopperSFP_gbl = ([0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],
#                          [0,0,0,0],    );   #[Slot][Port]
#our $SFPCount_gbl=0;
#    #our $XGLC_10gigSFP_detected_gbl = 0;
#    #our $XGLC_1gigSFP_detected_gbl = 0;
#our $checksfppower_gbl=0;
##our %SFPData = (
##            'TYPE'        => 'null',                   # Actual Test Time (excl. wait time) (secs)
##            'Vendor'   => 'null',                  # Diag version extracted from header
##            'ModelNo'        => 'null',                  # The last $Erc reported
##            'SerialNo'      => 'null',                  # Which power module (A|B) was in use (last or on 1st error
##            'Transcvr'        => 'null',                  # Test ID
##            'PowerdBm'       => 'null',                  # Time Of Last Failure (time code) [set in &Logs::Log_Error]
##        );
##our @SFPData_port_ar = (%SFPData,%SFPData,%SFPData,%SFPData,%SFPData,%SFPData,%SFPData,%SFPData);
##our @SFPData_slot_ar = (@SFPData_port_ar,@SFPData_port_ar,@SFPData_port_ar,@SFPData_port_ar,@SFPData_port_ar,@SFPData_port_ar);
#our @SFPData_slot_ar = ();
##push @SFPData_slot_ar, {@SFPData_port_ar}; #Push a copy , IMC Slot0
}
#__________________________________________________________________________
1;
