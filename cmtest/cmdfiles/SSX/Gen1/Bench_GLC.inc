################################################################################
#
# Module:      Bench_GLC.inc
#
# Author:      Joe White
#
# Descr:       Main Execution for GLC 2 and 4 Port test
#
# Version:    1.5  $Id: Bench_GLC.inc,v 1.8 2011/01/21 18:38:55 joe Exp $
#
# Changes:    Created from Bench_GLC.Dat 10/19/06
#			  Added diasable "noreload"
#			  Changed check_thermal to Check_GLC_Thermal.inc 1/22/07
#             2/27/08 dram test nolonger clears ECC errors by default(Support for Background testing)
#             Added support for fic tlv fifth link
#			  11/11/10 Added longer wait for GLC PSOC reading potentia values
#
# Includes:  Check_POST_GLC.inc
#			 Show_GLC_Cpld.inc
#			 i2c_scan_glc.inc
#			 Check_GLC_thermal.inc
#			 Check_Disco_glc.inc
#			 Bench_Test_GLC.inc
#				Check_PCI_V.inc
#            Traffic_Test_GLC_${glc_type_str_gbl}.inc (2 or 4 port)
#
# Still ToDo:
#              - Fix Intermmittent IXP SRAM Parity Errors
#              - Fix Intermitten PCI errors
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################
<ETTC>		700
<Msg>		"Test GLC"
<Msg>		"Verify at Stoke>>.."
<TimeOut>	5
<Send>		""
<WaitFor>	"Stoke>>"

<Prompt>	">"
<TimeOut>	5
<Msg>		"Starting Noodle..."
<Send>		"go ffe00100"
<Wait>

<Send>		"show version"
<Wait>
<GetData>

#Dummy Read to syncronize Expect
<Send>		"rd i2c U67 tlv"
<Wait>

<TimeOut>	10
<Msg>		"Getting Product / Serial info ..."
<Send>		"rd i2c U67 tlv"
<Wait>
<GetData>	Board

<TimeOut>	10

<Send>		"rd i2c fic tlv"
<Wait>
<GetData>   SW55thlink
<Bypass>	$SW55thlink_gbl
	<Msg> "Check if 5th link tlv present"
	<CheckData>	"type: 03, len: 03,              FIC TRUNKING BLOCK"
</Bypass>


# For some reason, this is required - UUT timing problem
<Send>
<Wait>

<Msg>		"Test Voltages..."
<Send>		"test volt"
<Wait>
<GetData>
<CheckData>	PASS


<Msg>		"Checking DC voltages ..."
<Send>		"show volt"
<Wait>
<GetData>	Volts

#	<Msg>		"*** TEST Abort *** ..."
#	<Power>		OFF
#	<End>

# For some reason, this is required - UUT timing problem
<Send>
<Wait>


<Include>	Show_GLC_Cpld.inc
<TimeOut>	40
<Bypass>   $UUT_Variable_ref[0]->{Potentia}
	<Msg>		Check Potentia
	<Send>		"rd potentia 0 nvreg 00 100"
	<Wait>
	<GetData>	Potentia_0_GLC
	<Send>		"rd potentia 1 nvreg 00 100"
	<Wait>
	<GetData>	Potentia_1_GLC
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

# Moved after CPLD check, so we know the slotnumber

<Msg>		"Running DRAM test ..."
<Msg>		$testmemorysize_gbl
<Send>		"test dram clear_ecc"
<Wait>
<TimeOut>	500
#<Send>		"test dram 00000000 40000000 random"
<sendchr>   "test dram random 00000000 "
<sendchr>   $testmemorysize_gbl
<send>      " "
#<Send>		"test dram 00000000 10000 rndm"
#<Msg>		"Full Dram test bypassed for development"
<Wait>
<GetData>
<CheckData>	"PASS"
<TimeOut>	10


 # For some reason, this is required - UUT timing problem
<Send>
<Wait>


<Include>	i2c_scan_glc.inc
# For some reason, this is required - UUT timing problem
<Send>
<Wait>


<Include>	Check_GLC_thermal.inc

<Msg>		"Check if booted on Primary Flash..."
<TimeOut>	2
<Send>		"r8 F400002B"
<WaitFor>	"F400002B   04"
<Send>
<Wait>
<GetData>

#<Msg>		"Removed until programmed on both sides, Check if booted on Secondary Flash..."
<Prompt>	"#"
<TimeOut>	30

<Msg>		"Booting IFS flash ..."
<Send>		"boot flash"
<Waitfor>	"Starting application"
<Wait>
<Send>
<Wait>
#For 3.0
<Msg>		"Disable system reload"
<Send>		"ls > /dev/shmem/system_noreload"
<Wait>


<TimeOut>	5
<Msg>		"Bootup from Secondary flash..."
<Send>		"pfeffa w8 F400002B 02"
<Wait>
<TimeOut>	30
<Prompt>	"Stoke>>"
<Send>		"reset board"

<Include>	Stop_stoke_boot.inc
<Send>
<Wait>
#<Msg>		"Stopping Stoke bootup.."
#<WaitFor>	"now to use STOKE boot monitor"
#<SendChr>		"uboot"
## For backward compatability to 2.0R2 Only need to keep this until the next release
#<Sleep>		1
#<SendChr>		"stoke"
#<Wait>

<Prompt>	">"
<TimeOut>	5
<Msg>		"Starting Noodle..."
<Send>		"go ffe00100"
<Wait>

<Msg>		"Check if booted on Secondary Flash..."
<TimeOut>	2
<Send>		"r8 F400002B"
# 0x20 Fail Count 1 , bank 0
#<WaitFor>	"F400002B   20"  # Failing in 11/15/07 image from don and layne
<Wait>
<CheckData>	"F400002B   20"
<Send>
<Wait>
<GetData>


<Include>	Check_Disco_glc.inc

<Prompt>	"#"
<TimeOut>	30

<Msg>		"Booting IFS flash ..."
<Send>		"boot flash"
<Waitfor>	"Starting application"
<Wait>

<Include>	Bench_Test_GLC.inc

#<Include>	Config_Traffic.inc
<Msg>       $glc_type_str_gbl
#<Include>	Traffic_Test_GLC_2-port.inc

<Include>	Traffic_Test_GLC_${glc_type_str_gbl}.inc


