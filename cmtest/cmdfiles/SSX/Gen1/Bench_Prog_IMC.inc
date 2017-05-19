################################################################################
#
# Module:      Bench_Prog_IMC.inc
#
# Author:      Joe White
#
# Descr:       Main Execution for IMC Programming
#
# Version:    1.7 $Id: Bench_Prog_IMC.inc,v 1.5.2.1 2011/01/21 17:45:25 joe Exp $
#
# Changes:    Created from Program_IMC.dat 10/19/06
#             2/27/08 dram test nolonger clears ECC errors by default(Support for Background testing)
#			  03/19/08 Added erase to i2c
#			  11/16/10 changes for PSOC
#
# Includes:  Check_POST_IMC.inc
#			 Show_IMC_Cpld.inc
#			 Check_Disco_glc.inc
#			 Added Link LEDs check Cas1290
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################

<Msg>		"Program IMC"
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
<Send>		"test dram random 00000000 100000"
<Waitfor>	">"
<CheckData>	PASS
<TimeOut>	2
<Msg>		"Slow Fans"
<Send>		"wr i2c 9501 fan1 gpio 47"
<Waitfor>	">"
<Send>		"wr i2c 9501 fan2 gpio 47"
<Waitfor>	">"

# For some reason, this is required - UUT timing problem
<Send>
<Wait>
<Include>	Show_IMC_Cpld.inc
#<Send>		"show cpld"
#<Wait>
# Needs Debug <Exec>		Get_CPLD_info


<Timeout>	60

<Msg>		"Program EEPROMs"
<Send>		"set ver 1"
<Wait>

# Get operator input
<Exec>		IMC_Program

<TimeOut>	120
<Msg>		"Program U67, 9501 TLV 0 Board type, Major, Minor rev"
<Send>		$imc_U67_erase_gbl
<Wait>
<GetData>
<Send>		$imc_9501_erase_gbl
<Wait>
<GetData>

<Send>		$imc_U67_tlv_0_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>
<Send>		$imc_9501_tlv_0_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>

<Msg>		"Program U67,9501 TLV 7 Serial number String"
<Send>		$imc_U67_tlv_7_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>
<Send>		$imc_9501_tlv_7_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>

<TimeOut>	5
<Msg>		"Verify U67, 9501 TLV 0 Board type, Major, Minor rev"
<Send>		"rd i2c U67 tlv 0"
<Wait>
<GetData>
<CheckData>	$imc_tlv_0_verify_gbl
<Send>		$imc_9501_tlv_0_rd_gbl
<Wait>
<GetData>
<CheckData>	$imc_tlv_0_verify_gbl


<Msg>		"Verify U67,9501 TLV 7 Serial number String"
<Send>		"rd i2c U67 tlv 7"
<Wait>
<GetData>
<CheckData>	$imc_sernumber_gbl
<Send>		$imc_9501_tlv_7_rd_gbl
<Wait>
<GetData>
<CheckData>	$imc_sernumber_gbl


<TimeOut>	120
<Msg>		"Program FIC TLV 0 Board type, Major, Minor rev"
<Send>		$imc_fic_erase_gbl
<Wait>
<GetData>
<Send>		$imc_fic_tlv_0_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>

<Msg>		"Program FIC TLV 7 Serial number String"
<Send>		$imc_fic_tlv_7_gbl
<Waitfor>	"Done"
<GetData>
<Send>
<Wait>

<TimeOut>	5
<Msg>		"Verify FIC TLV 0 Board type, Major, Minor rev"
<Send>		"rd i2c fic tlv 0"
<Wait>
<GetData>
<CheckData>	$imc_fic_tlv_0_verify_gbl


<Msg>		"Verify FIC TLV 7 Serial number String"
<Send>		"rd i2c fic tlv 7"
<Wait>
<GetData>
<CheckData>	$imc_fic_sernumber_gbl

<TimeOut>	120
<Msg>		"Program MicMezz TLV 0 Board type, Major, Minor rev"
<Send>		$imc_mmz_erase_gbl
<Wait>

<GetData>
<Send>		$imc_mmz_tlv_0_gbl
#<Waitfor>	"setup CRC and exit"
<Wait>
<GetData>

<Msg>		"Program MicMezz TLV 7 Serial number String"
<Send>		$imc_mmz_tlv_7_gbl
#<Waitfor>	"Done"
<Wait>
<GetData>

<TimeOut>	15
<Msg>		"Verify MicMezz TLV 0 Board type, Major, Minor rev"
<Send>		"rd mmz i2c tlv 0"
<Wait>
<GetData>
<CheckData>	$imc_mmz_tlv_0_verify_gbl


<Msg>		"Verify MicMezz TLV 7 Serial number String"
<Send>		"rd mmz i2c tlv 7"
<Wait>
<GetData>
<CheckData>	$imc_mmz_sernumber_gbl

 <TimeOut>	40
<Bypass>   $UUT_Variable_ref[0]->{Potentia}
    <Msg>       Check Potentia
    <Send>      "rd potentia 0 nvreg 00 100"
    <Wait>
    <GetData>   Potentia_0_IMC
    <Send>      "rd potentia 1 nvreg 00 100"
    <Wait>
    <GetData>   Potentia_1_IMC
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

<Send>		"w32 800904f0 04000000"
<Wait>
<Send>		"write disco cfg 0 3 0 8c 101100"
<Wait>
<Send>		"write disco cfg 0 3 0 ac 100000"
<Wait>
<Msg>		"Operator:Verify CF Flash and HD Leds are Green"
<Exec>		&Verify_LED_GREEN


<Send>		"wr lil 0 19 fff"
<Wait>
<Msg>		"Operator:Verify TX RX and Link LEDs are Green"
<Exec>		&Verify_LED_GREEN


