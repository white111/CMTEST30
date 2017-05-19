################################################################################
#
# Module:      Bench_Prog_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Main Execution for IMC Programming
#
# Version:    1.1 $Id: Bench_Prog_GLC.inc,v 1.6 2011/01/21 18:38:55 joe Exp $
#
#
#
# Changes:    Created from Bench_Prog_GLC.inc Vs 1.5 5/23/11
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
<WaitFor>	"Stoke>"

<Prompt>	">"
<TimeOut>	5
<Msg>		"Found Stoke Prompt"



# For some reason, this is required - UUT timing problem
<Send>
<Wait>

<Send>		"version"
<Wait>
<GetData>


#<Msg>       "Test Voltages..."
#<Send>      "test volt"
#<Wait>
#<GetData>
#<CheckData> PASS


#<Msg>       "Checking DC voltages ..."
#<Send>      "show volt"
#<Wait>
#<GetData>   Volts

##   <Msg>       "*** TEST Abort *** ..."
##   <Power>     OFF
##   <End>

#<Msg>       "Running DRAM test ..."
#<Send>      "test dram clear_ecc"
#<Wait>

#<TimeOut>   250
#<Send>      "test dram random 00000000 100000 "
#<Waitfor>   ">"
#<GetData>
#<CheckData> PASS

## For some reason, this is required - UUT timing problem
#<Send>
#<Wait>
#<Include>   Show_GLC_Cpld.inc


#<Timeout>   60

#<Msg>       "Program EEPROMs"
#<Send>      "set ver 1"
#<Wait>

# Get operator input
<Exec>		XGLC_Program
<Alert>		"Stop Here"
<TimeOut>	60
<Msg>		"Program U67, 9501 TLV 0 Board type, Major, Minor rev"
<Send>		$xglc_local_erase_gbl
<Wait>
<GetData>
<CheckDatax>	"failure"
<CheckDatax>	"error"


<Send>		$xglc_local_tlv_0_gbl
#<Waitfor>   "Done"
#<Send>
<Wait>
<GetData>
<CheckDatax>	"failure"
<CheckDatax>	"error"

<Send>		$xglc_global_erase_gbl
<Wait>
<GetData>
<CheckDatax>	"failure"
<CheckDatax>	"error"

<Send>		$xglc_global_tlv_0_gbl
#<Waitfor>   "Done"
#<GetData>
#<Send>
<Wait>
<GetData>
<CheckDatax>	"failure"
<CheckDatax>	"error"



<Msg>		"Program Local Global TLV 7 Serial number String"
<Send>		$xglc_local_tlv_7_gbl
#<Waitfor>   "Done"
#<GetData>
#<Send>
<Wait>
<GetData>
<CheckDatax>	"failure"
<CheckDatax>	"error"

<Send>		$xglc_global_tlv_7_gbl
#<Waitfor>   "Done"
#<GetData>
#<Send>
<Wait>
<GetData>
<CheckDatax>	"failure"
<CheckDatax>	"error"



<Msg>		"Program Local Global TLV 8 MAC String"
<Send>		$xglc_local_tlv_8_gbl
#<Waitfor>   "Done"
#<GetData>
#<Send>
<Wait>
<GetData>
<CheckDatax>	"failure"
<CheckDatax>	"error"

<Send>		$xglc_global_tlv_8_gbl
#<Waitfor>   "Done"
#<GetData>
#<Send>
<Wait>
<GetData>
<CheckDatax>	"failure"
<CheckDatax>	"error"


<TimeOut>	5
<Msg>		"Verify local global TLV 0 Board type, Major, Minor rev"
<Send>		"tlvread local tlv 0"
<Wait>
<GetData>
<CheckData>	$xglc_tlv_0_verify_gbl
<CheckDatax>	"failure"
<CheckDatax>	"error"

#<Send>		"rd i2c 9501 ${slot_gbl} tlv 0"
#<SendChar>      "rd i2c 9501 "
#<SendChar>      $slot_gbl
#<Send>      " tlv 0"
<Send>      " tlvread global-slot2 tlv 0"
<Wait>
<GetData>
<CheckData>	$xglc_tlv_0_verify_gbl
<CheckDatax>	"failure"
<CheckDatax>	"error"



<Msg>		"Verify Verify TLV 7 Serial number String"
<Send>		"tlvread local tlv 7"
<Wait>
<CheckData>	$xglc_sernumber_gbl
<CheckDatax>	"failure"
<CheckDatax>	"error"

#<Send>		"rd i2c 9501 ${slot_gbl} tlv 7"
#<SendChar>      "rd i2c 9501 "
#<SendChar>      $slot_gbl
#<Send>      " tlv 7"
<Send>		"tlvread global-slot2 tlv 7"
<Wait>
<GetData>
<CheckData>	$xglc_sernumber_gbl
<CheckDatax>	"failure"
<CheckDatax>	"error"



<Msg>		"Verify Local Global TLV 8 MAC String"
<Send>		"tlvread local tlv 8"
<Wait>
<GetData>
<CheckData>	$xglc_MAC_tlv_8_verify_gbl
<CheckDatax>	"failure"
<CheckDatax>	"error"
#<Send>		"rd i2c 9501 ${slot_gbl} tlv 8"
#<SendChar>      "rd i2c 9501 "
#<SendChar>      $slot_gbl
#<Send>      " tlv 8"
<Send>		"tlvread  global-slot2 tlv 8"
<Wait>
<GetData>
<msg>         $xglc_MAC_tlv_8_verify_gbl
<CheckData>	$xglc_MAC_tlv_8_verify_gbl
<CheckDatax>	"failure"
<CheckDatax>	"error"


<Bypass>	$xglc_global_tlv_16_verify_gbl
	<Msg>		"Program Local Global Deviation String"
	<Send>		$xglc_local_tlv_16_gbl
	#<Waitfor>   "Done"
	#<GetData>
	#<Send>
	<Wait>
	<GetData>
	<CheckDatax>	"failure"
	<CheckDatax>	"error"
	<Send>		$xglc_local_tlv_16_gbl
	#<Waitfor>   "Done"
	#<GetData>
	#<Send>
	<Wait>
	<GetData>
	<CheckDatax>	"failure"
	<CheckDatax>	"error"
	<Msg>		"Read Local Global Deviation String"
	<Send>		"tlvread local tlv 22"
	<Wait>
	<GetData>
	<CheckData>	$xglc_global_tlv_16_verify_gbl
	<CheckDatax>	"failure"
	<CheckDatax>	"error"
	#<Send>		"rd i2c 9501 ${slot_gbl} tlv 8"
	#<SendChar>      "rd i2c 9501 "
	#<SendChar>      $slot_gbl
	#<Send>      " tlv 8"
	<Send>		"tlvread  global-slot2 tlv 16"
	<Wait>
	<GetData>
	<msg>         $xglc_global_tlv_16_gbl
	<CheckData>	$xglc_global_tlv_16_verify_gbl
	<CheckDatax>	"failure"
	<CheckDatax>	"error"
</Bypass>

 <Alert>		"Stop Here"

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



