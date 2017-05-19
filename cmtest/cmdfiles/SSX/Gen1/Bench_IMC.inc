################################################################################
#
# Module:      Bench_IMC.inc
#
# Author:      Joe White
#
# Descr:       Main Execution for IMC Bench test
#
# Version:    1.11 $Id: Bench_IMC.inc,v 1.14 2011/01/21 18:38:55 joe Exp $
#
# Changes:    Created from Bench_IMC.dat  10/19/06
#			  Changed check_thermal to Check_IMC_Thermal
#			  032907 Fixed intermittent issue on reboot after formatting drives
#			  10/19/2007 added preformat in bootloader
#			  Updated for 12/1/07 image
#			  2/27/08 dram test nolonger clears ECC errors by default(Support for Background testing
#			  Added Second boot after final format of drives, IMC occasionally reboots after SSH keys generated)
#			  Added Addtional QNX set of clock to UTC and Check
#			  05/08/09 Added Update all  with fash on Primary, Fix for bug 12687 workaround using stokeboot 4.0
#			  Changes for PSOC 1/11/11
#			  Edits for 6.x software  10/22/13
#		      added addtional time to boot to secondary flash 150sec 8//27/14
#			  Changes for 13.1 Based Diags 8/4/14

#
#
# Includes:  Check_POST_IMC.inc
#			 Show_IMC_Cpld.inc
#			 i2c_scan_imc.inc
#			 Check_IMC_thermal.inc
#			 tftp_boot_imc_diag.inc
#			 format_IMC_drives.inc
#			 Check_IMC_PCI_V.inc
#			 Check_Disco_imc.inc
#            Check_IMC_drives.inc
#			 tftpcopy_stoke.inc
#			 cfint_boot_imc.inc
#			 Bench_Test_IMC.inc
#				Check_PCI_V.inc
#
# Still ToDo:
#              - Fix Intermitten PCI errors
#
#
#            Copyright (c) 2005-2014 Stoke. All rights reserved.
#
################################################################################
<Msg>		"Test IMC"
<ETTC>		900
<Msg>		"Verify at Stoke>>.."
<TimeOut>	1
<Send>		""
<WaitFor>	"Stoke>>"

<Prompt>	">"
<TimeOut>	5
<Msg>		"Starting Noodle..."
<Send>		"go ffe00100"
<Wait>

<TimeOut>	10
<Send>		"show version"
<Wait>
<GetData>

#Dummy Read to syncronize Expect
<Send>		"rd i2c U67 tlv"
<Wait>


<Msg>		"Getting Product / Serial info ..."
<Send>		"rd i2c U67 tlv"
<Wait>
<GetData>	Board

<Send>		"rd i2c fic tlv"
<Wait>
<GetData>

<Send>		"rd mmz i2c tlv"
<Wait>
<GetData>

# For some reason, this is required - UUT timing problem
<Send>
<Wait>

<Msg>		"Test IMC Voltages..."
<Send>		"test volt"
<Wait>
<CheckData>	PASS


<Msg>		"Checking IMC DC voltages ..."
<Send>		"show volt"
<Wait>
<GetData>	Volts

<Msg>		"Slow Fans"
<Send>		"wr i2c 9501 fan1 gpio 47"
<Waitfor>	">"
<Send>		"wr i2c 9501 fan2 gpio 47"
<Waitfor>	">"
# Set a bogus date
<Send>		"set clock FRI, 10/21/2004, 7:2:01"
<Wait>

<Msg>		'Set and Check Time'
<Exec>		Getmytime

<Send>		$sysclock_set_glb
<Wait>
<GetData>
<CheckData>	$sysclock_nosec_glb
#<Include>	Check_Potentia_Bench.inc
<TimeOut>	40
<Bypass>   $UUT_Variable_ref[0]->{Potentia}
	<Msg>		Check Potentia
	<Send>		"rd potentia 0 nvreg 00 100"
	<Wait>
	<GetData>	Potentia_0_IMC
	<Send>		"rd potentia 1 nvreg 00 100"
	<Wait>
	<GetData>	Potentia_1_IMC
</Bypass>

<Bypass>   $UUT_Variable_ref[0]->{PSOC}
     <Msg>		Check PSOC Version
	<Send>		"rd potentia 0 cs 60 10"
	<Wait>
	<Checkdata> $UUT_Variable_ref[0]->{PSOC_VER}
	<GetData>
	<Send>		"rd potentia 0 cs 00 100;rd potentia 1 cs 00 100"
	<Wait>
	<GetData>
	#Reset Static Counters
	<Send>		"wr potentia 0 csrs 1 5a"
	<Wait>
	<GetData>
	<Send>		"rd potentia 0 cs 00 100;rd potentia 1 cs 00 100"
	<Wait>
	<GetData>
</Bypass>

<Msg>		Wait 5 Seconds.. Check Clock.."
<Send>		$sysclock_set_glb
<Wait>
<Sleep>		5
<Send>		'show clock'
<Wait>
<GetData>   IMC_Clock


#	<Msg>		"*** TEST Abort *** ..."
#	<Power>		OFF
#	<End>

<Msg>		"Running DRAM test ..."
<Send>		"test dram clear_ecc"
<Wait>

#<TimeOut>	250
#<Send>		"test dram 00000000 10000 rndm"
# 1 GIG
#<Send>		"test dram 00000000 40000000 rndm"
<TimeOut>	500
# 2 GIG
<Send>		"test dram random 00000000 80000000"
#<Msg>		"Full Dram test bypassed for development"
<Waitfor>	">"
<GetData>
<CheckData>	PASS
<TimeOut>	10
# For some reason, this is required - UUT timing problem
<Send>
<Wait>


<Include>	Show_IMC_Cpld.inc

<Include>	Bench_Test_IMC.inc
<Include>	i2c_scan_imc.inc
# For some reason, this is required - UUT timing problem
<Send>
<Wait>


 # For some reason, this is required - UUT timing problem
 # Test sequence changed for PR 4320
<Send>
<Wait>
<Msg>		'Test NVRAM'
<Send>		'test nvram'
<Wait>
<GetData>
<CheckData>	PASS

<Include>	Check_IMC_thermal.inc

<Msg>		"Check if booted on Primary Flash..."
<TimeOut>	2
<Send>		"r8 F400002B"
<WaitFor>	"F400002B   04"
<Sleep>		1
<Send>
<Wait>
<GetData>

<Msg>		"Reset board"
<TimeOut>	60
<Prompt>	"Stoke>>"
<Send>		"reset board"
<Include>	Stop_stoke_bootloader.inc
<Include>	format_IMC_drives_bootloader.inc
<Msg>		"TFTP Boot ..."
<Include>	tftp_boot_imc_diag.inc

<Sleep>		20
<Include>	Check_Disco_imc.inc
<Include>	Check_IMC_PCI_V.inc
<Include>	tftpcopy_stoke_diag.inc
<Include>	format_IMC_drives.inc
<TimeOut>	150
#restart to bring drives up


<Msg>		"Boot From Secondary Flash..."
<Send>		"pfeffa w8 F400002B 02"
<Wait>
<Prompt>	"#"
<Send>		"reset board; reload"
<TimeOut>	150
<Wait>
<GetData>
# Make sure this system message does not pop out in the miidle of tests
#<WaitFor>     "System process not started within designated time"
<sleep>		5
<Send>
<Wait>

<Send>
<Wait>
<Msg>		"Check if booted on Secondary Flash"
<Send>		"pfeffa r8 F400002B"
<Wait>
#<CheckData>	"F400002B   20
<CheckData>	"F400002B   01"

#Second boot for occasional reboots after generating SSH keys for the first time
<Msg>		"Re-Boot From Primary Flash..."
<Send>      "pfeffa w8 F400002B 02"
<Wait>
<Prompt>	"#"
<Send>		"reset board ;reload"
<wait>
# Make sure this system message does not pop out in the miidle of tests
#<WaitFor>     "System process not started within designated time"
<Sleep>		5
<Send>
<Wait>

<Send>
<Wait>


<TimeOut>	5
<Msg>		"Check if booted on Primary Flash"
<Send>		"pfeffa r8 F400002B"
<Wait>
#<CheckData> "F400002B   40"
#<CheckData> "F400002B   01"
<CheckData> "F400002B   05"
#<Sleep>		1
#<Send>
#<Wait>
<GetData>
<Sleep>		10
<Include>	Check_Disco_imc.inc

<Include>	Check_IMC_drives.inc
<Include>	tftpcopy_stoke_diag.inc
<Include>	Update_all.inc
<Include>	HD_Copy_check.inc

<msg>		"Set RTC clock"
<Exec>		Getmytime
<Send>      $sysclock_QNX_set_glb
<Wait>
<CheckData>	"PASS"
<GetData>

<send>		"if (rtc -s hw) then (echo ClockHWset:PASS) fi"
<wait>
<CheckData>	"PASS"
<GetData>

<Send>		"if (date -t) then (echo ClockDisplay:PASS) fi"
<wait>
<CheckData>	"PASS"
<Getdata>   IMC_Clock_QNX


<Msg>		"Reset IMC"
<Send>		"pfeffa w8 f400002b 11"
<Wait>
<Send>		"reset;reload"
<TimeOut>	120


<Include>	Stop_stoke_bootloader.inc
<Msg>		"Booting from HD Flash"
#<Include>	cfint_boot_imc.inc
<Include>	hd_boot_imc.inc
<Include>	Enable_ISSU.inc
<Include>   Ship_config.inc


