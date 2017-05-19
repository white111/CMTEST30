################################################################################
#
# Module:      Mav.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#			   Joe White ( mailto:joe@stoke.com )
#
# Descr:      Stoke Specific Libray
#
# Version:    (See below) $Id: Stoke.pm,v 1.25 2012/02/17 17:13:42 joe Exp $
#
# Changes:     Added CheckDataX command (check for exclusion of $Arg)
#              Added Check_GLC_Thermal
#			   Enabled exit on Timeout
#			   Modified Temp upper limit
#			   Added ORT test for MTBF validation
#			   Added Chassis Fuctional Full slot test 2/16/10
#			   Added Check for first boot of dual IMC 4/20/10
#			   Added PSOC  1/11/11
#			   XGLC Changes in progress - Menu/Submenu, Buadrate set, added Stoke3.lib
#			Added Support for Fan2 and PEM2 Chassis test 2/6/13
#				&Check_IMC_0_Standby_Prompt  ($Data) if $Key eq 'Check_IMC_0_Standby_Prompt' 6.1/13.1 software
#			   Added Support for 4 XGLCs, 1gig,copper, ler SFP per port, SFP power meas
#
# Still ToDo:
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1995 - 2005 Paul Tindle. All rights reserved.
#            Copyright (c) 2005-2015 Mavenir. All rights reserved.
#
################################################################################
my $Ver = '18.3   012915'; #             #Name Changes to Mavenir  1/29/15
my $CVS_Ver = ' [ CVS: $Id: Stoke.pm,v 1.25 2012/02/17 17:13:42 joe Exp $ ]';
$Version{'Stoke'} = $Ver . $CVS_Ver;
#____________________________________________________________________________

use Init_SSX;   # Gen1 hardware
use SSX2;   # Gen1 hardware
use SSX3;   # Gen2 Hardware

#__________________________________________________________________________
sub Check_GLC_Thermal {    # Called by Screen_Data

    &Print2XLog ("Checking Thermal Values");
    &Print2XLog ("Check_GLC_Thermal: $Buffer",1) if 1;

    our %TData = ();

#      > show thermal
#      Tppci   =  26     C
#      TppcRem1=  46     C
#      TppcRem2=  37     C
#      TppcRem3=   0     C
#      TppcRem4=   0     C
#      Tixpi   =  34.025 C
#      Tixpe   = 255.035 C
#      Tinlet  =  39.5   C
#      Toutlet =  29.0   C
#      >



    foreach ( split /\n/, $Buffer) {
        if (/(\w+)\s*\=\s*(\w+)\s*C/i) {
            $TData{$1} = $2;
            &Print2XLog ("TData{$1} = $2",1);
        }
    }

    foreach (keys %TData) {
        if ((/Tppci|TppcRem1|TppcRem2|Tinlet|Toutlet/) and
           ($TData{$_} < 20) or ($TData{$_} > 60) and ($Bench_card_type_gbl eq 'Bench_IMC.inc')) {
               &Log_Error ("Thermal Data: \"$_\"  = $TData{$_}  Failed out of range");
        } elsif ( (/Tppci|TppcRem1|TppcRem2|Tinlet|Toutlet|Tixpi/) and
           ($TData{$_} < 20) or ($TData{$_} > 60) and ($Bench_card_type_gbl eq 'Bench_GLC.inc')) {
               &Log_Error ("Thermal Data: \"$_\"  = $TData{$_}  Failed out of range");
         } elsif (($Bench_card_type_gbl ne 'Bench_GLC.inc') and ($Bench_card_type_gbl ne 'Bench_IMC.inc') ){
         	&Log_Error ("Bench_card_type_gbl [$Bench_card_type_gbl] not supported in Check_GLC_Thermal")
		}
    }

}
#__________________________________________________________________________
sub Check_GLC_Thermal_Display {    # Called by Screen_Data
	# Ranges allowed 0 to 40 Deg ambiaent calibrated to actuals

    &Print2XLog ("Displaying Thermal Values");
    &Print2XLog ("Check_GLC_Thermal: $Buffer",1) if 1;

    our %TData = ();

#      > show thermal
#      Tppci   =  26     C
#      TppcRem1=  46     C
#      TppcRem2=  37     C
#      TppcRem3=   0     C
#      TppcRem4=   0     C
#      Tixpi   =  34.025 C
#      Tixpe   = 255.035 C
#      Tinlet  =  39.5   C
#      Toutlet =  29.0   C
#      >



    foreach ( split /\n/, $Buffer) {
        if ((/(\w+)\s+=\s+(\w+)\s+C/i) || (/(\w+)=\s+(\w+)\s+C/i) || (/(\w+)=\s+(\w+)\.\w+\s+C/i)) {
            $TData{$1} = $2;
            &Print2XLog ("TData{$1} = $2");
        }
    }

    foreach (keys %TData) {
        if ((/Tppci|TppcRem1|TppcRem2|Tinlet|Toutlet/) and
           ($TData{$_} < 0) or ($TData{$_} > 60) and ($Bench_card_type_gbl eq 'Bench_IMC.inc')) {
               &Log_Error ("Thermal Data: \"$_\"  = $TData{$_}  Failed out of range");
        } elsif ( (/Tppci|TppcRem1|Tinlet|Toutlet|Tixpi/) and
           ($TData{$_} < 0) or ($TData{$_} > 60) and ($Bench_card_type_gbl eq 'Bench_GLC.inc')) {
               &Log_Error ("Thermal Data: \"$_\"  = $TData{$_}  Failed out of range");
         }
    }

#         let fail+=1
#        echo "Temp_Tinlet:Failed:$fail" >> ${testpath}status.tmp
#        echo "Slot:${slot} Tinlet Tempurature out of range:\n `grep Tinlet ${testpath}thermal.tmp`\n Shutting Down..." >> ${testpath}status.tmp
#        #Emergency shutdown from IMC sot 0
#        sleep 1
#        on -p3r -f /net/nv-0-0 slay -f devb-mvSata >> /dev/null  2>&1
#        #slay -f devb-eide >> /dev/null  2>&1
#        on -p3r -f /net/nv-0-0 slay -f storaged  >> /dev/null  2>&1
#        sleep 1 >> /dev/null   2>&1
#        pfeffa on 0 w8 f4000042 1 >> /dev/null  2>&1
}
#__________________________________________________________________________

sub Get_Data_SSX {       # Called by &Screen_Data to parse the comm buffer

    my ($Key, $Data) = @_;
    $Key = ucfirst $Key;
    #print ("Get_Data $Key, $Data\n");
    &Get_Serial_Info if $Key eq 'Serial'; # No need to pass $Data since we're
                                          # using global @Screen_Data
    &Get_show_mfg_serial if $Key eq 'ShowMFG' ;
    &Get_Board_Info if $Key eq 'Board'; # No need to pass $Data since we're
    &Get_Chassis_Info if $Key eq 'Chassis';
    &Get_SW55thlink  if $Key eq 'SW55thlink';
    &Get_Volts if $Key eq 'Volts';
    &Check_GLC_Thermal ($Data) if $Key eq 'GLC_Thermal';
    &Check_GLC_Thermal_Display ($Data) if $Key eq 'GLC_Thermal_Display';
    &Get_CPLD_data if $Key eq 'CPLD'; # No need to pass $Data since we're
    &Check_IMC_0_Standby  ($Data) if $Key eq 'Check_IMC_0_Standby';
    &Check_IMC_0_Standby_Prompt  ($Data) if $Key eq 'Check_IMC_0_Standby_Prompt'  ;
    &Check_IMC_Clock  ($Data) if $Key eq 'IMC_Clock';
    &Check_IMC_Clock_OS  ($Data) if $Key eq 'IMC_Clock_OS';
    &Check_IMC_Clock_QNX  ($Data) if $Key eq 'IMC_Clock_QNX';
    &Get_BootPrompt  ($Data) if $Key eq 'BootPrompt' ;
    &Get_FistbootIMC  ($Data) if $Key eq 'Get_FistbootIMC';
    &Get_MAC  ($Data) if $Key eq 'GetMAC' ;
    &Get_Show_Env  ($Data) if $Key eq 'Show_Env' ;
    &Get_Memory_size  ($Data) if $Key eq 'Memory_size';
    &Get_Port_Counter_Det ($Data) if $Key eq 'Port_Counter_Det';
    &Get_FPD ($Data) if $Key eq 'Get_FPD';
    &Get_FPD ($Data) if $Key eq 'Get_DOS';
    &Check_Chassis_FRU_TEST if $Key eq 'Check_Chassis_FRU_TEST';
    &Check_Chassis_TACH($Key) if $Key =~ /^Check_Chassis_TACH/;
    &Check_POST_INFO  ($Data) if $Key eq 'POST' ;
    &Check_Potenita(%Potentia_0_GLC) if $Key eq 'Potentia_0_GLC';
    &Check_Potenita(%Potentia_1_GLC) if $Key eq 'Potentia_1_GLC';
    &Check_PSOC() if $Key eq 'PSOC';
    &Verify_Chassis_LED($Key) if $Key =~ /^Verify_Chassis_LED/;
    &Check_U200 if $Key eq 'U200';
    ####  XGLC Related ####
    #Check_CRC32
    &Check_CRC32  ($Data) if $Key eq 'Check_CRC32';
    &Check_tftp_size  ($Data) if $Key eq 'Check_tftp_size';
    &Check_XGLC_CPLD  ($Data) if $Key eq 'Check_XGLC_CPLD';
    &Check_XGLC_CPLD_Diag  ($Data) if $Key eq 'Check_XGLC_CPLD_Diag';
    &Check_tftp_Ping  ($Data) if $Key eq 'Check_tftp_Ping';
    &Check_XGLC_Diag  ($Data) if $Key eq 'Check_XGLC_Diag';
 	&Check_XGLC_voltage  ($Data) if $Key eq 'Check_XGLC_voltage';
 	&Check_XGLC_voltage_Margin_low  ($Data) if $Key eq 'Check_XGLC_voltage_Margin_low';
 	&Check_XGLC_voltage_Margin_high  ($Data) if $Key eq 'Check_XGLC_voltage_Margin_high';
 	&Check_XGLC_BMR  ($Data) if $Key eq 'Check_XGLC_BMR';
 	&Check_XGLC_Thermal ($Data) if $Key eq 'Check_XGLC_Thermal';
    &Check_bytecompare  ($Data) if $Key eq 'Check_bytecompare';
    &Check_XGLC_Bench_Links  ($Data) if $Key eq 'Check_XGLC_Bench_Links';
    &Check_XGLC_I2C  ($Data) if $Key eq 'Check_XGLC_I2C';
    &Check_GLC_Redundancy  ($Data) if $Key eq 'Check_GLC_Redundancy';
    &Check_GLC_Slot4_Enable  ($Data) if $Key eq 'Check_GLC_Slot4_Enable';
    &Detect_SFP_1GIG  ($Data) if $Key eq 'Detect_SFP_1GIG';
    &Detect_SFP_10GIG  ($Data) if $Key eq 'Detect_SFP_10GIG';
    &Check_XGLC_HD_Copytime  ($Data) if $Key eq 'Check_XGLC_HD_Copytime';
    &Get_SFP_HextoASCII  ($Data) if $Key eq 'Get_SFP_HextoASCII';
    &Get_SFP  ($Data) if $Key eq 'Get_SFP';

    #

}
#__________________________________________________________________________
sub Get_Volts {  # This isn't really necessary unless we want parametrics
                 # since the screen data has already been written to the log

    return;

#POT PC     RAIL-NAME           SENSE-NAME      NOM     VSMP       %
#  0  0      VCC_CORE    VO_SENSE_PPC_CORE   1.100V   1.100V  100.0%
#  0  1    VDD_CPUBUS     VO_SENSE_VCC_1V8   1.800V   1.794V   99.6%
#  0  2        VCC1_2   VO_SENSE_TCAM_CORE   1.200V   1.194V   99.5%
#  0  3       VCC_2V5     VO_SENSE_VCC_2V5   2.500V   2.506V  100.2%
#  0  4      VCC_1V35    VO_SENSE_IXP_CORE   1.350V   1.351V  100.0%
#  0  5        VCC1_5     VO_SENSE_QDR_1V5   1.500V   1.503V  100.2%
#  0  6     VSTL_1V25    VO_SENSE_DDR_TERM   1.250V   1.245V   99.6%
#  0  7        unused
#  1  0       VCC_3V3     VO_SENSE_VCC_3V3   3.300V   3.275V   99.2%
#  1  1          VCC5       VO_SENSE_VCC_5   5.000V   4.985V   99.7%
#  1  2                       FIC_PWR_GOOD      n/a   4.957V     n/a
#  1  3   VCC_NTX_DDR     VO_SENSE_NTX_DDR   2.500V   2.437V   97.4%
#  1  4        VCC_1V    VO_SENSE_NTX_CORE   1.050V   1.034V   98.4%
#  1  5   VCC_GT_CORE  VO_SENSE_DISCO_CORE   1.500V   1.494V   99.6%
#  1  6         VCC12         VO_SENSE_12V  12.000V  11.989V   99.9%
#  1  7       VTT_QDR    VO_SENSE_QDR_TERM   0.750V   0.748V   99.7%

    foreach (@Screen_Data) {
        if (/(.*)/) {
#            $ = $1;
        }
    }
}

#__________________________________________________________________________
sub Get_Serial_Info {

    # Extract the Part number and Serial number info
    #  from global @Screen_Data and update @PN & @SN, then incr $Cfg_Ptr

    foreach (@Screen_Data) {
        if (/.*(\w{16}).*/) {
           $SN[$Cfg_Ptr] = $1;
           $SN[$Cfg_Ptr] =~ /(\w{3})(\w{2})(\w{4})(\w{1})(\w{1})(\w{5})/;
           $PN[$Cfg_Ptr] = $1;    #!!! Need a lookup
        }
    }
    &Print2XLog ("PN = \'$PN[$Cfg_Ptr]\',SN = \'$SN[$Cfg_Ptr]\'");

    $Stats{'UUT_ID'} = $SN[0] unless $Cfg_Ptr;
    &Stats::Update_All;
    $Cfg_Ptr++;

    if ($Debug) {
        print "[Get_Serial_Info:] Serial Data->\n$Data{Serial}\n<-\n";
        for $i( 0 .. 2 ) {
            print "$i)\tPN=$PN[$i]\tSN=$SN[$i]\n";
        }
        &PETC('-230');
    }

#!!!    &Create_SigmaQuest_Unit_Report if $First_Time and $PN[0] ne '';
}

#__________________________________________________________________________

sub SSX_Menu_main {
    &Globals_SSX;
    @Menu_List = ();
    @Menu_Desc = ();
    @Menu_Cmd  = ();
    $User_Level = 0 if ($Debug_UUT eq 1 || $Development eq 1);
    our $CmdFilePath = "$GP_Path/cmdfiles/SSX/Gen1";
    #use Init_SSX;  # <- Stoke Specific Globals defined here
    &Globals_SSX;

    &Menu_Add ('Exit', '', 'Menu_Exit');
    &Menu_Add ('Gen 1', 'Test 1 Gig interface product', 'SSX_Menu1') if $User_Level > 1  or $User_Level eq 0;
    &Menu_Add ('Gen 2', 'Test 10 Gig interface product', 'SSX_Menu2') if $User_Level > 1  or $User_Level eq 0;


   if ($opt_1 or $opt_M ne '') {
        &Menu_Add ('Test', 'Regression test vehicle', 'Run_Test');
#        &Menu_Add ('Test_ssh', 'Regression test vehicle', 'Run_Test_ssh');
    }

    if ($opt_M eq '') {
        &Menu_Show ( 'Main' );
    } else {
        &Menu_Exec ($opt_M-1);
    }
}
#__________________________________________________________________________
sub SSX_Menu1 {
   @Menu_List = ();
    @Menu_Desc = ();
    @Menu_Cmd  = ();
    $User_Level = 0 if ($Debug_UUT eq 1 || $Development eq 1);
    &Menu_Add ('Exit', '', 'Menu_main');
    our $CmdFilePath = "$GP_Path/cmdfiles/SSX/Gen1";
    &Menu_Add ('Bench Program', 'Initial PCB bringup Programming', 'Run_Prog') if $User_Level > 1  or $User_Level eq 0;
    &Menu_Add ('Bench Test', 'Initial PCB bringup', 'Run_Bench_Test') if $User_Level > 2  or $User_Level eq 0;
    &Menu_Add ('Chassis Pre BI', 'Chassis Test IMC and GLC Pre-BI', 'Run_Chassis_Test_Pre_BI') if $User_Level > 3 or $User_Level eq 0;
    &Menu_Add ('Chassis BI', '12 Hour BI test', 'Run_Chassis_BI') if $User_Level > 4  or $User_Level eq 0;
    &Menu_Add ('Chassis POST BI', 'Chassis Test IMC and GLC POST-BI', 'Run_Chassis_Test_Post_BI') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Chassis Config', 'Chassis Configuration', 'Run_Chassis_Config') if $User_Level > 6  or $User_Level eq 0;
    &Menu_Add ('Chassis Extended', 'Long term system tests', 'Run_Chassis_Extended') if $User_Level > 7  or $User_Level eq 0;
    &Menu_Add ('Chassis ORT', 'MTBF Validation', 'Run_Chassis_ORT') if $User_Level > 7  or $User_Level eq 0;
    &Menu_Add ('Chassis Program', 'Chassis Program', 'Run_Chassis_Prog') if $User_Level > 7  or $User_Level eq 0;
    &Menu_Add ('Chassis TEST Pre BI', 'Chassis TEST', 'Run_Chassis_TEST_PRE') if $User_Level > 7  or $User_Level eq 0;
    &Menu_Add ('Chassis TEST Post BIProgram', 'Chassis TEST', 'Run_Chassis_TEST_POST') if $User_Level > 7  or $User_Level eq 0;
    &Menu_Add ('Chassis TEST Functionl Full', 'Chassis TEST', 'Run_Chassis_Functional_Full') if $User_Level > 7  or $User_Level eq 0;
    &Menu_Add ('Order Entry', 'Enter Sales Order', 'Run_GetOrder') if $User_Level  > 8  or $User_Level eq 0;
    &Menu_Add ('Debug', 'Debug Sub menu', 'SSX_Debug_Menu1') if $User_Level > 1  or $User_Level eq 0;


   if ($opt_1 or $opt_M ne '') {
        &Menu_Add ('Test', 'Regression test vehicle', 'Run_Test');
#        &Menu_Add ('Test_ssh', 'Regression test vehicle', 'Run_Test_ssh');
    }

    if ($opt_M eq '') {
        &Menu_Show ( 'Main' );
    } else {
        &Menu_Exec ($opt_M-1);
    }
}

#__________________________________________________________________________

sub SSX_Debug_Menu1 {
   @Menu_List = ();
    @Menu_Desc = ();
    @Menu_Cmd  = ();
    $User_Level = 0 if ($Debug_UUT eq 1 || $Development eq 1);
    our $CmdFilePath = "$GP_Path/cmdfiles/SSX/Gen1";
    &Menu_Add ('Exit', '', 'Menu_main');
    &Menu_Add ('Debug', 'Temporary', "Run_Debug")  if $User_Level eq 0; # if ($Debug);
    &Menu_Add ('Debug', 'Power Cycle GLC on Bench', "Run_Debug_GLC_Bench_Power")  if $User_Level eq 0; # if ($Debug);
    &Menu_Add ('Debug', 'Power Cycle IMC on Bench', "Run_Debug_IMC_Bench_Power")  if $User_Level eq 0; # if ($Debug);
    &Menu_Add ('Debug', 'BI Debug', "Run_Debug_Chassis_BI")  if $User_Level eq 0; # if ($Debug);

   if ($opt_1 or $opt_M ne '') {
        &Menu_Add ('Test', 'Regression test vehicle', 'Run_Test');
#        &Menu_Add ('Test_ssh', 'Regression test vehicle', 'Run_Test_ssh');
    }

    if ($opt_M eq '') {
        &Menu_Show ( 'Main' );
    } else {
        &Menu_Exec ($opt_M-1);
    }
}

#__________________________________________________________________________

sub SSX_Menu2 {   # Gen 2 boards
    @Menu_List = ();
    @Menu_Desc = ();
    @Menu_Cmd  = ();
    our $CmdFilePath = "$GP_Path/cmdfiles/SSX/Gen2";
    $User_Level = 0 if ($Debug_UUT eq 1 || $Development eq 1);
    &Menu_Add ('Exit', '', 'Menu_main');
    &Menu_Add ('Bench Program XGLC', 'Initial PCB bringup Programming', 'Run_Prog2') if $User_Level > 1  or $User_Level eq 0;
    &Menu_Add ('Bench Test XGLC', 'Initial PCB bringup', 'Run_Bench_Test2') if $User_Level > 2  or $User_Level eq 0;
    &Menu_Add ('Chassis Pre BI XGLC', 'Chassis Test IMC and XGLC Pre-BI', 'Run_Chassis_Test_Pre_BI_XGLC') if $User_Level > 3 or $User_Level eq 0;
    &Menu_Add ('Chassis BI XGLC', 'Chassis Test IMC and XGLC BI', 'Run_Chassis_Test_BI_XGLC') if $User_Level > 3 or $User_Level eq 0;
    &Menu_Add ('Chassis POST BI XGLC', 'Chassis Test IMC and XGLC POST-BI', 'Run_Chassis_Test_Post_BI_XGLC') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Chassis Config XGLC', 'Chassis Test Config', 'Run_Chassis_Test_Config_XGLC') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Chassis Extended XGLC', 'Long term system tests', 'Run_Chassis_Extended_XGLC') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Chassis ORT XGLC', 'Long term system tests', 'Run_Chassis_ORT_XGLC') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Chassis Program', 'Program chassis', 'Run_Chassis_Prog_gen2') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Chassis TEST Pre BI', 'Chassis TEST', 'Run_Chassis_TEST_PRE_gen2') if $User_Level > 7  or $User_Level eq 0;
    &Menu_Add ('Chassis TEST Post BIProgram', 'Chassis TEST', 'Run_Chassis_TEST_POST_gen2') if $User_Level > 7  or $User_Level eq 0;
     &Menu_Add ('Debug Gen 2', 'Debug Sub menu', 'SSX_Debug_Menu2') if $User_Level > 1  or $User_Level eq 0;

   if ($opt_1 or $opt_M ne '') {
        &Menu_Add ('Test', 'Regression test vehicle', 'Run_Test');
#        &Menu_Add ('Test_ssh', 'Regression test vehicle', 'Run_Test_ssh');
    }

    if ($opt_M eq '') {
        &Menu_Show ( 'Main' );
    } else {
        &Menu_Exec ($opt_M-1);
    }
}

#_______________________________________________________________________________

sub SSX_Debug_Menu2 {   # Gen 2 boards
    @Menu_List = ();
    @Menu_Desc = ();
    @Menu_Cmd  = ();
    our $CmdFilePath = "$GP_Path/cmdfiles/SSX/Gen2";
    $User_Level = 0 if ($Debug_UUT eq 1 || $Development eq 1);
    &Menu_Add ('Exit', '', 'Menu_main');
    &Menu_Add ('Debug Bench Test XGLC', 'Debug', 'Run_Bench_Debug') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Bench Flash XGLC', 'Flash Programming', 'Run_Prog_Flash2') if $User_Level > 1  or $User_Level eq 0;
    &Menu_Add ('StokeOS Reload', 'StokeOS startup Stability', 'Run_Debug_XGLC_StokeOSReload') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Debug Temp', 'Debug XGLC', 'Run_Debug_XGLC') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Debug', 'Debug Reboot XLP', 'Run_Debug_Reboot_XLP') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Debug', 'Debug Power Cycle XGLC', 'Run_Debug_Bench_XGLC_PowerCycle') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Debug', 'Debug Power Cycle XGLC Selct margin', 'Run_Debug_Bench_XGLC_PowerCycle_Select_Margin') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Debug', 'Debug Power Cycle XGLC GPP DRAM', 'Run_Debug_Bench_XGLC_PowerCycle_GPP_DRAM') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Debug', 'Debug Reboot XGLC', 'Run_Debug_Bench_XGLC_Reboot') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Debug', 'Debug XGLC Flashimage', 'Run_Debug_Flashimage_XGLC') if $User_Level > 5  or $User_Level eq 0;
    &Menu_Add ('Debug', 'Debug', 'Run_Debug_Gen2') if $User_Level > 5  or $User_Level eq 0;



   if ($opt_1 or $opt_M ne '') {
        &Menu_Add ('Test', 'Regression test vehicle', 'Run_Test');
#        &Menu_Add ('Test_ssh', 'Regression test vehicle', 'Run_Test_ssh');
    }

    if ($opt_M eq '') {
        &Menu_Show ( 'Main' );
    } else {
        &Menu_Exec ($opt_M-1);
    }
}

#__________________________________________________________________________
sub Run_Debug_GLC_Bench_Power {
            #caller(0))[3];

    my $Cmd_File = "$CmdFilePath/Debug_Bench_GLC_Powercyle.dat";
     print "Debug\n";
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;

    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Debug_IMC_Bench_Power {
            #caller(0))[3];

    my $Cmd_File = "$CmdFilePath/Debug_Bench_IMC_Powercyle.dat";
     print "Debug\n";
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;

    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Debug_Chassis_BI {

    my $Cmd_File = "$CmdFilePath/Debug_Chassis_BI.dat";
     print "Debug\n";
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;

    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_GetOrder {

    my $Cmd_File = "$CmdFilePath/Order_entry.dat";

    $TestData{'TID'} = 'SO';
    $Exit_On_Timeout = 0;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Chassis_Extended {

    my $Cmd_File = "$CmdFilePath/Chassis_Extended.dat";

    $TestData{'TID'} = 'EXT';
    $Exit_On_Timeout = 0;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Chassis_TEST_PRE {

    my $Cmd_File = "$CmdFilePath/Chassis_test.dat";

    $TestData{'TID'} = 'CHP';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Chassis_TEST_PRE_gen2 {

    my $Cmd_File = "$CmdFilePath/Chassis_test_gen2.dat";

    $TestData{'TID'} = 'CHP';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Chassis_TEST_POST {

    my $Cmd_File = "$CmdFilePath/Chassis_test.dat";

    $TestData{'TID'} = 'CHF';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Chassis_TEST_POST_gen2 {

    my $Cmd_File = "$CmdFilePath/Chassis_test_gen2.dat";

    $TestData{'TID'} = 'CHF';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Chassis_Config {

    my $Cmd_File = "$CmdFilePath/Chassis_Config.dat";

    $TestData{'TID'} = 'SHIP';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Chassis_Prog {

    my $Cmd_File = "$CmdFilePath/Chassis_Prog.dat";

    $TestData{'TID'} = 'Program';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Chassis_Prog_gen2 {

    my $Cmd_File = "$CmdFilePath/Chassis_Prog_gen2.dat";

    $TestData{'TID'} = 'Program';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
 sub Run_Chassis_Functional_Full {

    my $Cmd_File = "$CmdFilePath/Chassis_Functional_Full.dat";

    $TestData{'TID'} = 'CHA';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________


sub Run_Chassis_Test_Post_BI {

    my $Cmd_File = "$CmdFilePath/Chassis_Post_BI.dat";

    $TestData{'TID'} = 'FST';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Chassis_BI {

    my $Cmd_File = "$CmdFilePath/Chassis_BI.dat";

    $TestData{'TID'} = 'BI';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Chassis_ORT {

    my $Cmd_File = "$CmdFilePath/Chassis_ORT.dat";

    $TestData{'TID'} = 'ORT';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Chassis_Test_Pre_BI {

    my $Cmd_File = "$CmdFilePath/Chassis_Pre_BI.dat";

    $TestData{'TID'} = 'IST';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Bench_Test {

    my $Cmd_File = "$CmdFilePath/Bench.dat";

    $TestData{'TID'} = 'Bench';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________

sub Run_Prog {       #GLC Generation

    my $Cmd_File = "$CmdFilePath/Bench_Prog.dat";
    $TestData{'TID'} = 'Program';
    $Exit_On_Timeout = 0;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}

#__________________________________________________________________________
sub Run_Prog2 {         #XGLC Generation(gen2)

    my $Cmd_File = "$CmdFilePath/Bench_Prog.dat";
    print ("Command File path:  $CmdFilePath\n");
    $Baud = "115200";    #  Gen 2 currently runs at 115200 buad
    $TestData{'TID'} = 'Program';
    $Exit_On_Timeout = 0;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}

#__________________________________________________________________________
sub Run_Prog_Flash2 {         #XGLC Generation(gen2)

    my $Cmd_File = "$CmdFilePath/Bench_Prog_Flash.dat";
    print ("Command File path:  $CmdFilePath\n");
    $Baud = "115200";    #  Gen 2 currently runs at 115200 buad
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 0;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}

#__________________________________________________________________________
sub Run_Bench_Test2 {         #XGLC Generation(gen2)
    ;
    my $Cmd_File = "$CmdFilePath/Bench.dat";
    print ("Command File path:  $CmdFilePath\n");
    $Baud = "115200";    #  Gen 2 currently runs at 115200 buad
    $TestData{'TID'} = 'Bench';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Chassis_Test_Pre_BI_XGLC {

    my $Cmd_File = "$CmdFilePath/Chassis_Pre_BI_XGLC.dat";

    $TestData{'TID'} = 'IST';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________

sub Run_Chassis_Test_BI_XGLC {

    my $Cmd_File = "$CmdFilePath/Chassis_BI_XGLC.dat";

    $TestData{'TID'} = 'BI';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________

sub Run_Chassis_Test_Post_BI_XGLC {

    my $Cmd_File = "$CmdFilePath/Chassis_Post_BI_XGLC.dat";

    $TestData{'TID'} = 'FST';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________

sub Run_Chassis_Test_Config_XGLC {

    my $Cmd_File = "$CmdFilePath/Chassis_Config_XGLC.dat";

    $TestData{'TID'} = 'SHIP';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________

sub Run_Chassis_Extended_XGLC {

    my $Cmd_File = "$CmdFilePath/Chassis_Extended_XGLC.dat";

    $TestData{'TID'} = 'EXT';
    $Exit_On_Timeout = 0;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________

sub Run_Chassis_ORT_XGLC {    #xglc

    my $Cmd_File = "$CmdFilePath/Chassis_ORT_XGLC.dat";

    $TestData{'TID'} = 'ORT';
    $Exit_On_Timeout = 0;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Bench_Debug {         #XGLC Generation(gen2)

    my $Cmd_File = "$CmdFilePath/Debug_Bench.dat";
    print ("Command File path:  $CmdFilePath\n");
    $Baud = "115200";    #  Gen 2 currently runs at 115200 buad
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________

sub Run_Debug_XGLC_StokeOSReload {

    my $Cmd_File = "$CmdFilePath/Debug_Boot_StokeOS_Loop.dat";

    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
 #__________________________________________________________________________
#Run_Debug_Reboot_XLP
sub Run_Debug_Bench_XGLC_PowerCycle {

    my $Cmd_File = "$CmdFilePath/Debug_Bench_XGLC_PowerCycle.dat";
    $Baud = "115200";    #  Gen 2 currently runs at 115200 buad
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
 #__________________________________________________________________________
 #Run_Debug_Reboot_XLP
sub Run_Debug_Bench_XGLC_PowerCycle_Select_Margin {

    my $Cmd_File = "$CmdFilePath/Debug_Bench_XGLC_PowerCycle_select_margin.dat";
    $Baud = "115200";    #  Gen 2 currently runs at 115200 buad
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
 #__________________________________________________________________________
#Run_Debug_Reboot_XLP
sub Run_Debug_Bench_XGLC_PowerCycle_GPP_DRAM {

    my $Cmd_File = "$CmdFilePath/Debug_Bench_XGLC_PowerCycle_GPP_DRAM.dat";
    $Baud = "115200";    #  Gen 2 currently runs at 115200 buad
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
#Run_Debug_Reboot_XLP
sub Run_Debug_Bench_XGLC_Reboot {

    my $Cmd_File = "$CmdFilePath/Debug_Bench_XGLC_Reboot.dat";
    $Baud = "115200";    #  Gen 2 currently runs at 115200 buad
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Debug_Flashimage_XGLC {

    my $Cmd_File = "$CmdFilePath/Debug_Flashimage_XGLC.dat";
    $Baud = "115200";    #  Gen 2 currently runs at 115200 buad
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Debug_Gen2 {

    my $Cmd_File = "$CmdFilePath/Debug.dat";
    $Baud = "9600";    #  Gen 2 currently runs at 115200 buad
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
#Run_Debug_Reboot_XLP
sub Run_Debug_Reboot_XLP {

    my $Cmd_File = "$CmdFilePath/Debug_XLP_Reboot.dat";
    $Baud = "115200";    #  Gen 2 currently runs at 115200 buad
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Debug_XGLC {

    my $Cmd_File = "$CmdFilePath/Debug.dat";
    $Baud = "9600";    #  Gen 2 currently runs at 115200 buad
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
1;
