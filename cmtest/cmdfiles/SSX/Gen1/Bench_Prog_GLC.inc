################################################################################
#
# Module:      Bench_Prog_GLC.inc
#
# Author:      Joe White
#
# Descr:       Main Execution for IMC Programming
#
# Version:    1.5 $Id: Bench_Prog_GLC.inc,v 1.6 2011/01/21 18:38:55 joe Exp $
#             2/27/08 dram test nolonger clears ECC errors by default(Support for Background testing)
#			  3/19/08 Added IC2 erase
#             Added support for fic tlv fifth link
#			  11/11/10 Added longer wait for GLC PSOC reading potentia values
#
#
# Changes:    Created from Program_GLC.inc 10/19/06
#
# Includes:  Check_POST_GLC.inc
#			 Show_GLC_Cpld.inc
#			 Check_Disco_glc.inc
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
<Msg>		"Program GLC"

<Msg>		"Verify at Stoke>>.."
<TimeOut>	1
<Send>		""
<WaitFor>	"Stoke>>"

<Prompt>	">"
<TimeOut>	5
<Msg>		"Starting Noodle..."
<Send>		"go ffe00100"
<Wait>


# For some reason, this is required - UUT timing problem
<Send>
<Wait>

<Send>		"show version"
<Wait>
<GetData>

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

<Msg>		"Running DRAM test ..."
<Send>		"test dram clear_ecc"
<Wait>

<TimeOut>	250
<Send>		"test dram random 00000000 100000 "
<Waitfor>	">"
<GetData>
<CheckData>	PASS

# For some reason, this is required - UUT timing problem
<Send>
<Wait>
<Include>	Show_GLC_Cpld.inc


<Timeout>	60

<Msg>		"Program EEPROMs"
<Send>		"set ver 1"
<Wait>

# Get operator input
<Exec>		GLC_Program

<TimeOut>	60
<Msg>		"Program U67, 9501 TLV 0 Board type, Major, Minor rev"
<Send>		$glc_U67_erase_gbl
<Wait>
<GetData>

<Send>		$glc_U67_tlv_0_gbl
<Waitfor>	"Done"
<Send>
<Wait>
<GetData>
<Send>		$glc_9501_erase_gbl
<Wait>
<GetData>
<Send>		$glc_9501_tlv_0_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>


<Msg>		"Program U67,9501 TLV 7 Serial number String"
<Send>		$glc_U67_tlv_7_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>
<Send>		$glc_9501_tlv_7_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>


<Msg>		"Program U67,9501 TLV 8 MAC String"
<Send>		$glc_U67_tlv_8_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>
<Send>		$glc_9501_tlv_8_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>

<TimeOut>	5
<Msg>		"Verify U67, 9501 TLV 0 Board type, Major, Minor rev"
<Send>		"rd i2c U67 tlv 0"
<Wait>
<GetData>
<CheckData>	$glc_tlv_0_verify_gbl
#<Send>		"rd i2c 9501 ${slot_gbl} tlv 0"
<SendChar>		"rd i2c 9501 "
<SendChar>		$slot_gbl
<Send>		" tlv 0"
<Wait>
<GetData>
<CheckData>	$glc_tlv_0_verify_gbl


<Msg>		"Verify U67,9501 TLV 7 Serial number String"
<Send>		"rd i2c U67 tlv 7"
<Wait>
<CheckData>	$glc_sernumber_gbl
#<Send>		"rd i2c 9501 ${slot_gbl} tlv 7"
<SendChar>		"rd i2c 9501 "
<SendChar>		$slot_gbl
<Send>		" tlv 7"
<Wait>
<GetData>
<CheckData>	$glc_sernumber_gbl


<Msg>		"Verify U67,9501 TLV 8 MAC String"
<Send>		"rd i2c U67 tlv 8"
<Wait>
<GetData>
<CheckData>	$glc_MAC_tlv_8_verify_gbl
#<Send>		"rd i2c 9501 ${slot_gbl} tlv 8"
<SendChar>		"rd i2c 9501 "
<SendChar>		$slot_gbl
<Send>		" tlv 8"
<Wait>
<GetData>
<CheckData>	$glc_MAC_tlv_8_verify_gbl

<TimeOut>	120
<Msg>		"Program FIC TLV 0 Board type, Major, Minor rev"
<Send>		$glc_fic_erase_gbl
<Wait>
<GetData>
<Send>		$glc_fic_tlv_0_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>

<Msg>		"Program FIC TLV 7 Serial number String"
<Send>		$glc_fic_tlv_7_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>

<Bypass>	$UUT_Variable_ref[1]->{DX55thlink}
	<Msg>		"Program FIC TLV 3 5th link enabled"
	<Send>		"wr i2c fic tlv 3 h 1"
	<Waitfor>	"Done"
	<GetData>
	<Send>
	<Wait>
</Bypass>


<TimeOut>	5
<Msg>		"Verify FIC TLV 0 Board type, Major, Minor rev"
<Send>		"rd i2c fic tlv 0"
<Wait>
<GetData>
<CheckData>	$glc_fic_tlv_0_verify_gbl


<Msg>		"Verify FIC TLV 7 Serial number String"
<Send>		"rd i2c fic tlv 7"
<Wait>
<GetData>
<CheckData>	$glc_fic_sernumber_gbl

<Bypass>	$UUT_Variable_ref[1]->{DX55thlink}
	<Msg>		"Verify FIC TLV 3 5th link enabled"
	<Send>		"rd i2c fic tlv 3"
	<Wait>
	<GetData>
	<CheckData>	"type: 03, len: 03,              FIC TRUNKING BLOCK"
</Bypass>

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


<Send>		"set ver 0"
<Wait>

<Msg>		"Check LEDs..."
<Msg>		"Turn on all LEDs RED"
<Send>		"w8 F400001A 8"
<Wait>

<Send>		"w8 F400001B 2"
<Wait>

<Send>		"w8 F400001C 4"
<Wait>

<Msg>		"Operator:Verify Status LEDs are Red"
<Exec>		Verify_LED_RED
<Msg>		"Turn on all LEDs Green"
<Send>		"w8 F400001A 1"
<Wait>

<Send>		"w8 F400001B 1"
<Wait>

<Send>		"w8 F400001C 0"
<Wait>
<Msg>		"Operator:Verify Status LEDs are Green"
<Exec>		&Verify_LED_GREEN
<Msg>		" "
<Msg>		"Operator:Verify Press and Hold S2 Reset"
<Msg>		"Verify All Port LEDs are Green"
<Exec>		&Verify_GLCPortLED



