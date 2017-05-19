################################################################################
#
# Module:      Init_Stoke.pm
#
# Author:      Joe White( mailto:joe@stoke.com )
#
# Descr:       Stoke Globals
#
# Version:    (See below) $Id: Init_Stoke.pm,v 1.33 2012/02/17 17:13:42 joe Exp $
#
# Changes:    Added Varibles for "set fab snake" command  12/14/05
#			  Updated for R1 Release
#			  Added onScript, Mib 3 filter
#			  Updated for 2.0R1 Release
#			  Updated for 2.0R2 Release
#			  Updated for 2.0R2_2006061212 with Cavuium fix
#			  Updated for 2.1 Stokeboot IXP PCI window change c00212
#			  Updated for 4.0B4 6/11/08
#			  Move to Pip C 12/02/08
#			  Updated to Stoke 4.3B4S7 4/27/09
#			  Update for formatto40gigpartition.sh
#			  Moved 4.3 to released 10/16/09
#			  Moved to 4.5 Preliminary 10/09
#			  Updated for 4.6 1/29/10
#			  Added Full Chassis Varilbes 4/8/10
#			  Added Firstboot of Dual IMC system 4/20/10
#			  Moved to 4.6B1S2
#			  Added More tests for Chassis Frus being present 5/2/11
#			Added Support for Fan2 and PEM2 Chassis test 2/6/13
#			  #			13.1.R2 release
#			  Added Support for 1gig, copper, LR per port fan2, power meas
#			 Update to 13.R5 and test new diags 7/8
#             #Name Changes to Mavenir  1/29/15
#			 Added Product_gbl
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
sub Globals_SSX {
	#   Added HA Varialbes
	 &Print2XLog ("Setting up SSX variables");
	our $Product_gbl = 'SSX';
	our $Tmp_HA             =  "$ENV{HOME}/tmp" ;
    our $Opening_session = 0;
    our $HA_Session = 0;
    our $HA_Session_N = 1;
    our $Comm_Log_HA = ''; # Log file for com app (minicom) HA
    our ($Comm_HA);     # Handle for Expect HA
    our ($Comm_Start);  # Our defualt at startup
    our ($Comm_Current);  # What we ar currently pointing too
    our $HA_Msg = ''; # Msg added to Print2Xlog

    #    Imbedded variables
    our $Bench_card_type_gbl = 'null.inc'; #Accuired from GetData POST, used for determing IMC or GLC benchtest
    our $Bench_Prog_card_type_gbl = 'null.inc';
    our $glc_type_str_gbl = "2-port";     # GLC port count for testing, from get_board_info, get_chassis_info, get_config_info
    our $Slot_1_NOT_IMC_GBL = 0;
    our $P20_NOT_INSTALLED_GBL = 0; # This is set during chassis test if tlv 99 returns this string
    our $P20_INSTALLED_GBL = 1;
    our $Firstboot_Dual_IMC_GBL = 0;

    # Version Control variable used during Config checkout - Actual values are set in Get_software_release
    our $release_name_global = "13.1R5S1_2.9_diag" ;
    our $tftp_path_gbl = "/tftpboot/" . $Product_gbl;
    my  $tftp_copypath_release = $Product_gbl . "/OS_" . $CMPipe;     #/tfpboot/SSX/OS_a/
    our $tftp_copypath_release_gbl = "$tftp_copypath_release/";
    our $tftp_bootpath_release_gbl = "$tftp_copypath_release/";
    #Strings presented by Stoke OS show version and ISSU package select
    our $StokeOS_release_gbl = "13.1R5";  #Must match release for links into hdp/images StokeOS Release 6.0 (2011121701).
    our $StokeOS_release_Build_gbl = "";
    our $StokeOS_ISSU_Apply_gbl = "$StokeOS_release_gbl$StokeOS_release_Build_gbl";
    our $StokeOS_ISSU_Install_gbl = "StokeOS-$StokeOS_release_gbl$StokeOS_release_Build_gbl";
    our $StokeOS_builddate_gbl = "2014062706";     #6.0 (2012011901)  StokeOS Release 6.0 (2012071619
    our $Software_OS_release_gbl = "StokeOS Release $StokeOS_ISSU_Apply_gbl .$StokeOS_builddate_gbl";
    our $Stoke_bootloader_ver_gbl = "Stoke Bootloader Release $StokeOS_ISSU_Apply_gbl .$StokeOS_builddate_gbl";
    our $show_sys_ISSU_in_use_gbl = "$StokeOS_ISSU_Apply_gbl  Current Version  .StokeOS Release $StokeOS_ISSU_Apply_gbl .$StokeOS_builddate_gbl";
    #our $show_sys_ISSU_other_gbl = "$StokeOS_release_gbl\\S5  .StokeOS Release $StokeOS_release_gbl\\S5 .$StokeOS_builddate_gbl";

    our $Stoke_boot_ver_gbl = "StokeBoot Release 6.0 .2013011510.";
    our $Stoke_boot_XGLC_ver_gbl = "StokeBoot Release .6.0 2013011510.";

    our $firmware_ver_gbl = "91";
    our $firmware_ver_xglc_gbl = "0B";
    #diag path              xx
    our $diag_ver_gbl = $Product_gbl . "/diag_" . $CMPipe;
    #our $diag_ver_gbl = "layne010307";
    our $tftp_copypath_diag_gbl = "$diag_ver_gbl/";   #diag072106, diag080706
    our $tftp_bootpath_diag_gbl = "$diag_ver_gbl/";

    our $Diag_boot_ver_gbl = "/stoke/bin/dia";
    #our $Diag_boot_ver_gbl = "2253225765.*/stoke/bin/dia";
    our $Diag_boot_ver_cmd_gbl = "cksum /stoke/bin/diag";

    #GLC redunancy settings  Check_GLC_Redundancy
    our $glcredundant_gbl = 0 ;
    our	$noglcredundant_gbl = 1 ;

    #Default names for files copied
    our $Stoke_image = "stoke.bin";
#    our $StokeS1_pkg = "stokeS1.pkg";
    our $Stoke_pkg = "stokepkg.bin";
    our $Stoke_config = "stoke.cfg";
    our $Stoke_uboot = "stokeboot.bin";
    our $Stoke_ubootxglc = "stokebootxglc.bin";
    our $Stoke_bootloader = "bootloader.bin";
    our $Stoke_bootloader2 = "bootloader2.bin";
    our $Stoke_noodle = "noodle.bin";
    our $Stoke_diag_glc = "diag_glc.bin";
    our $Stoke_diag_xglc = "diag_xglc.bin";
    our $Stoke_onscript_GLC = "GLC.ksh";  # local script on cardbus for parallel memory tests during BI/Ext
    our $Stoke_onscript_MC = "IMC.ksh";
    our $Stoke_onscript_XGLC = "XGLC.ksh";
    our $Format_40gig_MC = "formatto40gigpartition.sh";
    our $Format_MC = "storageprep80.sh";
    #our $Diag_cfint_boot_gbl = "boot image file $Stoke_diag ";
    our $Diag_boot_xglc_gbl = "boot image file /hd/mfg/$Stoke_diag_xglc ";
    our $Diag_boot_glc_gbl = "boot image file /hd/mfg/$Stoke_diag_xglc ";
    our $Diag_cfint_boot_gbl = $Diag_boot_glc_gbl;
    print ("Current Software release: $release_name_global \n");
    print ("Current Diag release: $tftp_bootpath_diag_gbl\n");




    # Stoke Specific Globals
    our $AX4000_IP       = 'AX4000';      # Updated by TestCtrl.cfg
    our $AX4000_USER     = 'AX4000';      # Updated by TestCtrl.cfg
    our $Bypass			= 0;			  # Controls command bypassing are we in a by pass section
    our $Cmd_Bypass			= 0;			  # Controls command bypassing, do we want to bypass code
    our $DefFanSpeed     = 'High';        # Updated by TestCtrl.cfg
    #our $Debug_UUT     = 0;        	  	  # Updated by TestCtrl.cfg, Default off
    #our $Development	= 0;      		  # Updated by TestCtrl.cfg, Default off
    our @Email_Config				= ('');       # Email notification list for Config tests
    our @Email_Config_CC				= ('');       # Email notification list for Config tests
    our @Email_Config_Records				= ('');       # Email notification list for Config tests
    our @Email_Ship				= ('');       # Email notification list for Config tests
    our @Email_Ship_CC				= ('');       # Email notification list for Config tests
    our @Email_Ship_Records				= ('');       # Email notification list for Config tests
    our $UUT_Ver_check	= 1; 			  # Default is to check for versions
    # Hashes from parts.cfg, and part number files( need to be added as they are put into use)
    our %partnumber_hash = ('');            # Fixed 7/31/06 JSW
   	our %partnumber_hash_out  = ('');
   	our %partnumber_lookup    = ('');	  # Fixed 7/31/06 jsw
   	our %allowed_partnumber_rev = ('');   # Fixed 7/31/06 jsw
   	our %UUT_Variable_ref	  = ('');     # Fixed 7/31/06 jsw, Holds pointers to varibles in each slot, Read only please
   	our %UUT_Variable	  = ('');
   	our %UUT_02233			 = ('');
   	our %UUT_02159			 = ('');
   	our %UUT_02157			 = ('');      	  # Holds any needed varibles created/changed from UUT_Varible_ref,  Read/Write ok
   	our %UUT_02041			 = ('');
   	our %UUT_01321			 = ('');      # Current hash posiblities from UUTCFG directory, Create on the fly?
   	our %UUT_00722			 = ('');      # Current hash posiblities from UUTCFG directory, Create on the fly?
   	our	%UUT_00722_01        = ('');
   	our	%UUT_00722_02        = ('');
   	our	%UUT_00722_03        = ('');
   	our	%UUT_00722_04        = ('');
   	our	%UUT_00722_05        = ('');
   	our	%UUT_00722_06        = ('');
   	our	%UUT_00722_07        = ('');
   	our	%UUT_00722_08        = ('');
   	our	%UUT_00722_09        = ('');
   	our	%UUT_00722_10        = ('');
   	our	%UUT_00722_11        = ('');
   	our	%UUT_00722_12        = ('');
   	our	%UUT_00722_13        = ('');
   	our %UUT_00292			 = ('');
   	our %UUT_00292_01			 = ('');
   	our %UUT_00292_02			 = ('');
   	our %UUT_00292_03			 = ('');
   	our %UUT_00292_04			 = ('');
   	our %UUT_00292_05			 = ('');
   	our %UUT_00292_06			 = ('');
   	our %UUT_00292_07			 = ('');
   	our %UUT_00292_08			 = ('');
   	our %UUT_00292_09			 = ('');
   	our %UUT_00292_10			 = ('');
   	our %UUT_00292_11			 = ('');
   	our %UUT_00292_12			 = ('');
   	our %UUT_00292_13			 = ('');
   	our %UUT_00293			 = ('');
   	our %UUT_00293_06			 = ('');
   	our %UUT_00293_07			 = ('');
   	our %UUT_00294			 = ('');
   	our %UUT_00375			 = ('');
   	our %UUT_00295			 = ('');
   	our %UUT_00002			 = ('');
   	our %UUT_00648			 = ('');
   	our %UUT_00315			= ('');
   	our %UUT_00301			= ('');
   	our %UUT_00299			= ('');
   	our %UUT_00297			= ('');
   	our @TIDs				= ('');   	# Holds the valid Test Ids in order executed
   	our @CFG_Entrys 		= ('');     # Holds Serial number searches of CFG file, reversed for latest entry first
   	our @Event_Entrys 		= ('');     # Holds Serial number searches and timestamp of Event file, reversed for latest entry first


   	our %partnumbers     = ('');
   	our $Printer       = 'none';      	  # Updated by TestCtrl.cfg
   	our $Post_GBL	= 0;				# Added for Detecting both Gen1 and Gen2 post
   	our $Post_N_GBL	= 1;				# Added for Detecting both Gen1 and Gen2 post
   	our $Last_KeyWord = '';				  # Last send command Keyword
   	our	$Last_Send = '';				  # Holds last Arg from Send command

    our %Cpld_data = ();   				  #Set by Get_CPLD_data
    our $slot_gbl = "" ;
    our $testmemorysize_gbl = 0;			  # Set by Get_CPLD_data, this is when we know our slot id
    our $SW55thlink_gbl = 0;				  # Enabled by TLV 3 = 1 on FIC , Bench test only
    our @SW55thlinkSlot_gbl = (0,0,0,0,0,0);				  # Enabled by TLV 3 = 1 on FIC , 5 Slot Chassis test only



        #our $mib_filter_gbl = ' ';
    our $mib_filter_1_gbl = '| grep  -e "gFrames" -e "disco" -e "dx-sw5" -e "ixf port"  -e "gBytes" -e "gUcast.." -e "sizeTo127"  -e "Pkts65to127" -e "OctetsTotalOK" -e "bBytes.." -e "UcPckts" -e "..FifoOvrn" -e "ollision" -e "Undersize" -e "Frags" -e "badCRC" -e "Err" -e "late coll" -e "jabber" ';
    our $mib_filter_2_gbl = '| grep -e "dx-sw5 port" -e "ixf port" -e "bBytes.." -e "ixf port"  -e  "gBytes..Lo" -e "gUcast.." -e "sizeTo127" -e "..FifoOvrn" -e "ollision" -e "Undersize" -e "Frags" -e "badCRC" -e "Err" -e "late coll" -e "jabber" -e "BAD" ';
    our $mib_filter_3_gbl = '| grep -e "..FifoOvrn" -e "ollision" -e "Undersize" -e "Frags" -e "badCRC" -e "Err" -e "late coll" -e "jabber" -e "BAD" ';
    our $mib_filter_4_gbl = 'if (grep -q -e "..FifoOvrn" -e "ollision" -e "Undersize" -e "Frags" -e "badCRC" -e "Err" -e "late coll" -e "jabber" -e "BAD" ' ;
    our $mib_filter_gbl = 'if (grep -q -e "gBytesTx" -e "gBytesRx" -e "gBytesRxLo" -e "gBytesTxLo" -e "RxOctetsTotalOK" -e "TxOctetsTotalOK" ' ;

#Declared in Init, (re)assigned here...

          # our        $Exit_On_CheckData_Fail  = 0
    if ($Development) {$Exit_On_Error   = 0;} else {$Exit_On_Error   = 1;}
    $Exit_On_Error_Count = 0;  # 0 = Exit now, otherwise decremented
    $Exit_On_Timeout = 0;

    $Stats{'SW_Ver'} =$release_name_global  ;
    $Stats{'Diag_Ver'} =$diag_ver_gbl  ;

    #More imbeded varibles
    #5 slot mapping       Ch, S0, S1, S2, S3, S4,x,x,x,x,x,x,x,x,x,x,S15,x,x,S18,S19,x,S21,S22
    #                     Chasss, Slot 0, Slot 1, Slot 2, Slot 3 , slot 4, S15 Alarm, S18  PEM A, S19 PEM B, S21 Fan 1, S19 Fan 2
    #Full 5 slot Chassis        (1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,1)
    our $Full_Chassis_str_GBL = "none";
    our $Full_Chassis_GBL = 0;  # 0 = Not full chassis, 1 Full Chassis
    our $Full_Chassis_FRU_GBL = 0; # Chassis fru modules  chassis, alarm, fan pem
    our @Slot_INST_GBL = (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);  # variable for Slot installed
    our $Slot_INST_0_1_GBL = 0;    #Product of Slot_INST_GBL
    our $Slot_INST_0_2_GBL = 0;    #Product of Slot_INST_GBL
    our $Slot_INST_0_3_GBL = 0;    #Product of Slot_INST_GBL
    our $Slot_INST_0_4_GBL = 0;    #Product of Slot_INST_GBL
    our $Slot_INST_1_2_GBL = 0;    #Product of Slot_INST_GBL
    our $Slot_INST_1_3_GBL = 0;    #Product of Slot_INST_GBL
    our $Slot_INST_1_4_GBL = 0;    #Product of Slot_INST_GBL
    our $Slot_INST_2_3_GBL = 0;    #Product of Slot_INST_GBL
    our $Slot_INST_2_4_GBL = 0;    #Product of Slot_INST_GBL
    our $Slot_INST_3_4_GBL = 0;    #Product of Slot_INST_GBL
    #Can't use array varibles in cmdfiles
    our	$Slot_INST_0_GBL = 0;
    our	$Slot_INST_1_GBL = 0;
    our	$Slot_INST_2_GBL = 0;
    our	$Slot_INST_3_GBL = 0;
    our	$Slot_INST_4_GBL = 0;
    our $Slot_INST_1_IMC_GBL  = 0;
    our $Slot_INST_1_GLC_GBL  = 0;
    #Varibles for R1.1 Show env(does not work with older rev cards)
    our	$Slot_SHOWENV_0_GBL = 0;
    our	$Slot_SHOWENV_1_GBL = 0;
    our	$Slot_SHOWENV_2_GBL = 0;
    our	$Slot_SHOWENV_3_GBL = 0;
    our	$Slot_SHOWENV_4_GBL = 0;
    our $Production_GBL = 1;  # Variable to indicate in Production or final configuration test, Default Production mode
    #Varible used in "Set fab snake xxxxx" command, sets card type by slot, 0 = not inst, 1 = MC 2 = GLC 2=port, 4 = GLC 4 port
    #Vales set when serial number collected
    our	$Slot_CARD_TYPE_INST_0_GBL = 0;
    our	$Slot_CARD_TYPE_INST_1_GBL = 0;
    our	$Slot_CARD_TYPE_INST_2_GBL = 0;
    our	$Slot_CARD_TYPE_INST_3_GBL = 0;
    our	$Slot_CARD_TYPE_INST_4_GBL = 0;
    #Default used for  Traffic snake test, changed by Get_Mesh_slots
    our $internal_traffic_test_time_GBL = 900;
    our $internal_traffic_test_timeout_GBL = 1000;
    our $internal_traffic_test_time_msg_GBL = "Send Traffic for $internal_traffic_test_time_GBL Seconds";
    #Default fan speeds changed by get_mesh_slots and testctrl.cfg
    our $FanSpeed1_GBL = "wr i2c 9501 fan1 gpio E7"  ;
    our $FanSpeed2_GBL = "wr i2c 9501 fan2 gpio E7"  ;
    our $Fan2Speed1_GBL = "wr i2c adm1029 1 60 BB";
    our $Fan2Speed2_GBL = "wr i2c adm1029 2 60 BB";
    our $FanSpeed_MSG_GBL = "All Fans on High"  ;


    ####################################################################
    ## Global Varibles being pulled from UUT CFG directory



    ###################################################################
#####  Start Potentia compare lists,  these are cutand past from Potenta save as Hex option
#####  Add a line at the start with Key word Potentia and then Potentia number and version
       # GLC Potentia 0  V5
              our %Potentia_0_GLC  = qw (
Potentia 0_V5
00 40
01 02
02 00
03 00
04 5d
05 00
06 00
07 5d
08 12
09 12
0a 12
0b 09
0c b0
0d 80
0e a0
0f 50
10 b4
11 db
12 e0
13 be
14 d1
15 f0
16 00
17 00
18 00
19 0f
1a 00
1b 0f
1c 00
1d 0f
1e 00
1f 02
20 01
21 04
22 01
23 00
24 5d
25 00
26 00
27 5d
28 12
29 12
2a 12
2b 09
2c a0
2d 70
2e 90
2f 50
30 a3
31 c7
32 d0
33 ac
34 be
35 f0
36 00
37 00
38 00
39 0f
3a 00
3b 0f
3c 00
3d 0f
3e 00
3f 02
40 02
41 08
42 03
43 00
44 5d
45 00
46 00
47 5d
48 12
49 12
4a 12
4b 09
4c a0
4d 70
4e 90
4f 50
50 a4
51 c7
52 d0
53 ad
54 be
55 f0
56 00
57 00
58 00
59 0f
5a 00
5b 0f
5c 00
5d 0f
5e 00
5f 02
60 04
61 10
62 07
63 00
64 5d
65 00
66 00
67 5d
68 12
69 12
6a 12
6b 09
6c a0
6d 70
6e 90
6f 50
70 a3
71 c7
72 d0
73 ac
74 be
75 f0
76 00
77 00
78 00
79 0f
7a 00
7b 0f
7c 00
7d 0f
7e 00
7f 02
80 08
81 20
82 0f
83 03
84 5d
85 00
86 00
87 5d
88 12
89 12
8a 12
8b 09
8c a0
8d 70
8e 90
8f 50
90 a6
91 ca
92 d0
93 af
94 c1
95 f0
96 00
97 00
98 00
99 0f
9a 00
9b 0f
9c 00
9d 0f
9e 00
9f 02
a0 10
a1 c0
a2 1f
a3 00
a4 5d
a5 00
a6 00
a7 5d
a8 12
a9 12
aa 12
ab 09
ac a0
ad 70
ae 90
af 50
b0 a2
b1 c6
b2 d0
b3 ac
b4 bd
b5 f0
b6 00
b7 00
b8 00
b9 0f
ba 00
bb 0f
bc 00
bd 0f
be 00
bf 02
c0 7f
c1 02
c2 85
c3 5d
c4 5d
c5 00
c6 00
c7 00
c8 00
c9 00
ca 00
cb 00
cc 00
cd 00
ce 00
cf 00
d0 00
d1 00
d2 00
d3 00
d4 00
d5 00
d6 00
d7 00
d8 00
d9 00
da 00
db 00
dc 00
dd 00
de 00
df 00
e0 00
e1 00
e2 00
e3 02
e4 00
e5 00
e6 00
e7 0a
e8 00
e9 01
ea 00
eb 00
ec 00
ed 00
ee 00
ef 00
f0 00
f1 00
f2 00
f3 00
f4 00
f5 00
f6 00
f7 00
f8 00
f9 00
fa 00
fb 00
fc 00
fd 00
fe f0
ff 29
);

    # GLC Potentia 0  V5
our %Potentia_1_GLC  = qw (
Potentia 1_V5
00 40
01 02
02 80
03 02
04 5d
05 00
06 00
07 5d
08 12
09 12
0a 12
0b 09
0c a0
0d 70
0e 90
0f 50
10 a3
11 c6
12 d0
13 ac
14 bd
15 f0
16 00
17 00
18 00
19 0f
1a 00
1b 0f
1c 00
1d 0f
1e 00
1f 02
20 01
21 04
22 81
23 00
24 5d
25 00
26 00
27 5b
28 12
29 12
2a 12
2b 09
2c a0
2d 70
2e 90
2f 50
30 a3
31 c7
32 d0
33 ac
34 be
35 f0
36 00
37 00
38 00
39 0f
3a 00
3b 0f
3c 00
3d 0f
3e 00
3f 02
40 02
41 08
42 83
43 00
44 5d
45 00
46 00
47 5d
48 12
49 12
4a 12
4b 09
4c a0
4d 70
4e 90
4f 50
50 a4
51 c7
52 d0
53 ad
54 be
55 f0
56 00
57 00
58 00
59 0f
5a 00
5b 0f
5c 00
5d 0f
5e 00
5f 02
60 04
61 10
62 87
63 00
64 5d
65 00
66 00
67 5d
68 12
69 12
6a 12
6b 09
6c a0
6d 70
6e 90
6f 50
70 a3
71 c7
72 d0
73 ac
74 be
75 f0
76 00
77 00
78 00
79 0f
7a 00
7b 0f
7c 00
7d 0f
7e 00
7f 02
80 08
81 20
82 8f
83 00
84 5d
85 00
86 00
87 5d
88 12
89 12
8a 12
8b 09
8c a0
8d 70
8e 90
8f 50
90 a4
91 c7
92 d0
93 ad
94 be
95 f0
96 00
97 00
98 00
99 0f
9a 00
9b 0f
9c 00
9d 0f
9e 00
9f 02
a0 10
a1 40
a2 9f
a3 00
a4 5d
a5 00
a6 00
a7 5d
a8 12
a9 12
aa 12
ab 09
ac a0
ad 70
ae 90
af 50
b0 a2
b1 c6
b2 d0
b3 ac
b4 bd
b5 f0
b6 00
b7 00
b8 00
b9 0f
ba 00
bb 0f
bc 00
bd 0f
be 00
bf 02
c0 ff
c1 02
c2 85
c3 5d
c4 5d
c5 04
c6 00
c7 ff
c8 00
c9 00
ca 00
cb 00
cc 00
cd 00
ce 00
cf 00
d0 00
d1 00
d2 00
d3 00
d4 00
d5 00
d6 00
d7 00
d8 00
d9 00
da 00
db 00
dc 00
dd 00
de 00
df 00
e0 00
e1 00
e2 00
e3 0e
e4 00
e5 08
e6 00
e7 0f
e8 00
e9 01
ea 00
eb 00
ec 00
ed 00
ee 00
ef 00
f0 00
f1 00
f2 00
f3 00
f4 00
f5 00
f6 00
f7 00
f8 00
f9 00
fa 00
fb 00
fc 00
fd 00
fe f0
ff ad
);





       # GLC Potentia 0  V5
              our %Potentia_0_IMC  = qw (
Potentia 0_V5
00 40
01 06
02 00
03 00
04 5d
05 00
06 00
07 5d
08 12
09 12
0a 12
0b 09
0c b0
0d 80
0e a0
0f 50
10 b4
11 db
12 e0
13 be
14 d1
15 f0
16 00
17 00
18 00
19 0f
1a 00
1b 0f
1c 00
1d 0f
1e 00
1f 02
20 01
21 08
22 01
23 00
24 5d
25 00
26 00
27 5d
28 12
29 12
2a 12
2b 09
2c a0
2d 70
2e 90
2f 50
30 a3
31 c7
32 d0
33 ac
34 be
35 f0
36 00
37 00
38 00
39 0f
3a 00
3b 0f
3c 00
3d 0f
3e 00
3f 02
40 01
41 08
42 01
43 00
44 5d
45 00
46 00
47 5d
48 12
49 12
4a 12
4b 09
4c a0
4d 70
4e 90
4f 50
50 a4
51 c7
52 d0
53 ad
54 be
55 f0
56 00
57 00
58 00
59 0f
5a 00
5b 0f
5c 00
5d 0f
5e 00
5f 02
60 06
61 c0
62 07
63 00
64 5d
65 00
66 00
67 5d
68 12
69 12
6a 12
6b 09
6c a0
6d 70
6e 90
6f 50
70 a3
71 c7
72 d0
73 ac
74 be
75 f0
76 00
77 00
78 00
79 0f
7a 00
7b 0f
7c 00
7d 0f
7e 00
7f 02
80 00
81 00
82 00
83 00
84 00
85 00
86 00
87 00
88 00
89 00
8a 00
8b 00
8c 00
8d 00
8e 00
8f 00
90 00
91 00
92 00
93 00
94 00
95 00
96 00
97 00
98 00
99 00
9a 00
9b 00
9c 00
9d 00
9e 00
9f 00
a0 00
a1 00
a2 00
a3 00
a4 00
a5 00
a6 00
a7 00
a8 00
a9 00
aa 00
ab 00
ac 00
ad 00
ae 00
af 00
b0 00
b1 00
b2 00
b3 00
b4 00
b5 00
b6 00
b7 00
b8 00
b9 00
ba 00
bb 00
bc 00
bd 00
be 00
bf 00
c0 4f
c1 02
c2 85
c3 5d
c4 5d
c5 00
c6 00
c7 00
c8 00
c9 00
ca 00
cb 00
cc 00
cd 00
ce 00
cf 00
d0 00
d1 00
d2 00
d3 00
d4 00
d5 00
d6 00
d7 00
d8 00
d9 00
da 00
db 00
dc 00
dd 00
de 00
df 00
e0 00
e1 00
e2 00
e3 02
e4 00
e5 00
e6 00
e7 0a
e8 00
e9 01
ea 00
eb 00
ec 00
ed 00
ee 00
ef 00
f0 00
f1 00
f2 00
f3 00
f4 00
f5 00
f6 00
f7 00
f8 00
f9 00
fa 00
fb 00
fc 00
fd 00
fe f0
ff a1
);

    # GLC Potentia 0  V5
our %Potentia_1_IMC  = qw (
Potentia 1_V5
00 40
01 26
02 80
03 02
04 5d
05 00
06 00
07 5d
08 12
09 12
0a 12
0b 09
0c a0
0d 70
0e 90
0f 50
10 a3
11 c6
12 d0
13 ac
14 bd
15 f0
16 00
17 00
18 00
19 0f
1a 00
1b 0f
1c 00
1d 0f
1e 00
1f 02
20 01
21 40
22 a5
23 00
24 5d
25 00
26 00
27 5d
28 12
29 12
2a 12
2b 09
2c a0
2d 70
2e 90
2f 50
30 a3
31 c7
32 d0
33 ac
34 be
35 f0
36 00
37 00
38 00
39 0f
3a 00
3b 0f
3c 00
3d 0f
3e 00
3f 02
40 01
41 40
42 a3
43 00
44 5d
45 00
46 00
47 5d
48 12
49 12
4a 12
4b 09
4c a0
4d 70
4e 90
4f 50
50 a4
51 c7
52 d0
53 ad
54 be
55 f0
56 00
57 00
58 00
59 0f
5a 00
5b 0f
5c 00
5d 0f
5e 00
5f 02
60 00
61 00
62 00
63 00
64 00
65 00
66 00
67 00
68 00
69 00
6a 00
6b 00
6c 00
6d 00
6e 00
6f 00
70 00
71 00
72 00
73 00
74 00
75 00
76 00
77 00
78 00
79 00
7a 00
7b 00
7c 00
7d 00
7e 00
7f 00
80 00
81 00
82 00
83 00
84 00
85 00
86 00
87 00
88 00
89 00
8a 00
8b 00
8c 00
8d 00
8e 00
8f 00
90 00
91 00
92 00
93 00
94 00
95 00
96 00
97 00
98 00
99 00
9a 00
9b 00
9c 00
9d 00
9e 00
9f 00
a0 01
a1 40
a2 87
a3 00
a4 5d
a5 00
a6 00
a7 5d
a8 12
a9 12
aa 12
ab 09
ac a0
ad 70
ae 90
af 50
b0 a2
b1 c6
b2 d0
b3 ac
b4 bd
b5 f0
b6 00
b7 00
b8 00
b9 0f
ba 00
bb 0f
bc 00
bd 0f
be 00
bf 02
c0 e7
c1 02
c2 85
c3 5d
c4 5d
c5 04
c6 00
c7 a3
c8 00
c9 00
ca 00
cb 00
cc 00
cd 00
ce 00
cf 00
d0 00
d1 00
d2 00
d3 00
d4 00
d5 00
d6 00
d7 00
d8 00
d9 00
da 00
db 00
dc 00
dd 00
de 00
df 00
e0 00
e1 00
e2 00
e3 0e
e4 00
e5 08
e6 00
e7 0f
e8 00
e9 01
ea 00
eb 00
ec 00
ed 00
ee 00
ef 00
f0 00
f1 00
f2 00
f3 00
f4 00
f5 00
f6 00
f7 00
f8 00
f9 00
fa 00
fb 00
fc 00
fd 00
fe f0
ff 0e
);


}
#__________________________________________________________________________
#XGLC Added Variables
our $crc32_match_gbl = 0;
our $crc32_str_gbl = "na";
our $postinfo_XGLC_str_found = 0;
our $xfersizehex_str_gbl = "na";
our $xfersizebyte_str_gbl = "na";
our $linkinfo_XGLC_str_found = 0;
our $compare_gbl = 0;
our @XGLC_1gigSFP_gbl = ([0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],	);   #[Slot][Port];  # 1= enable/do not bypass # Varible to enable use of 1gig SFPs 10/9/12
    						#Added to bench test as of 10/9/12, Remainder TBD
our @XGLC_10gigSFP_gbl = ([0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],	);   #[Slot][Port]
our @XGLC_10gigLRSFP_gbl = ([0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],	);   #[Slot][Port]
our @XGLC_1gigCopperSFP_gbl = ([0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],
						  [0,0,0,0],	);   #[Slot][Port]
our $SFPCount_gbl=0;
    #our $XGLC_10gigSFP_detected_gbl = 0;
    #our $XGLC_1gigSFP_detected_gbl = 0;


our $checksfppower_gbl=0;
#our %SFPData = (
#            'TYPE'        => 'null',                   # Actual Test Time (excl. wait time) (secs)
#            'Vendor'   => 'null',                  # Diag version extracted from header
#            'ModelNo'        => 'null',                  # The last $Erc reported
#            'SerialNo'      => 'null',                  # Which power module (A|B) was in use (last or on 1st error
#            'Transcvr'        => 'null',                  # Test ID
#            'PowerdBm'       => 'null',                  # Time Of Last Failure (time code) [set in &Logs::Log_Error]
#        );
#our @SFPData_port_ar = (%SFPData,%SFPData,%SFPData,%SFPData,%SFPData,%SFPData,%SFPData,%SFPData);
#our @SFPData_slot_ar = (@SFPData_port_ar,@SFPData_port_ar,@SFPData_port_ar,@SFPData_port_ar,@SFPData_port_ar,@SFPData_port_ar);
our @SFPData_slot_ar = ();
#push @SFPData_slot_ar, {@SFPData_port_ar}; #Push a copy , IMC Slot0

#__________________________________________________________________________

1;
