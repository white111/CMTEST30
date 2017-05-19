################################################################################
#
# Module:      Bench_Prog_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Main Execution for IMC Programming
#
# Version:    1.2 $Id: Bench_Prog_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
#
#
# Changes:    Created from Bench_Prog_GLC.inc Vs 1.5 5/23/11
#			  Added Voltage tests  2/29/12
#			  Increased waittime on memory test 30-40sec 10/22/12
#
# Includes:
#
# Still ToDo:
#             	Add CPLD Check
#		 		Check for Debug Jumper installed
#			   	TFTP update if Ethernet board installed and CRC does not match
#				Add Reset at end to Ceck LEDs
#				mw.b FFDF001C 0 does not make LED green, only green during reset
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################
<Msg>		"Program GLC"

<Msg>		"Verify at Stoke>>.."
<TimeOut>	1
<Send>		""
<WaitFor>	"Stoke>"

<Prompt>	"Stoke>"
<TimeOut>	5
<Msg>		"Found Stoke Prompt"



# For some reason, this is required - UUT timing problem
<Send>
<Wait>

<Send>		"version"
<Wait>
<GetData>
#


#<Msg>       "Test Voltages..."
#<Send>      "test volt"
#<Wait>
#<GetData>
#<CheckData> PASS


#<Msg>       "Checking DC voltages ..."
#<Send>      "run psocdump"
#<Wait>
#<GetData>

<msg>   "Check I2C bus 0 "
#enable local i2c bus in cpld
#<Send>      "tlvread local tlv 0"
#<Wait>

##Volts
#<Send>      "cpld show"
#<Wait>
#<GetData>   Check_XGLC_CPLD

<Include>   Check_Voltage_XGLC.inc


<TimeOut>	40
<Msg>       "Running DRAM test ..."
# mtest [start [end [pattern [iterations]]]]
# Testing area used for Flashing only
<Send>      "mtest 1000000 4000000 a3d633adba453e8f332a7de39fdae7c66b634f89f116c9a3 1"
<Wait>
<getdata>
<checkdata>  'Tested . iteration... with 0 errors'
<checkdatax>   "FAILURE"


# Get operator input
<Exec>		XGLC_Program
#<Alert>		"Stop Here"
<TimeOut>	60
<Msg>		"Program U67, 9501 TLV 0 Board type, Major, Minor rev"
<Send>		$xglc_local_erase_gbl
<Wait>
<GetData>
<CheckDatax>	"failure"
<CheckDatax>	"error"
<Sleep>		1

<Send>		$xglc_local_tlv_0_gbl
#<Waitfor>   "Done"
#<Send>
<Wait>
<GetData>
<CheckData>		"TLV write succesful"
<CheckDatax>	"failure"
<CheckDatax>	"error"
<Sleep>		1
<Send>		$xglc_global_erase_gbl
<Wait>
<GetData>
<CheckDatax>	"failure"
<CheckDatax>	"error"
<Sleep>		1
<Send>		$xglc_global_tlv_0_gbl
#<Waitfor>   "Done"
#<GetData>
#<Send>
<Wait>
<GetData>
<CheckData>		"TLV write succesful"
<CheckDatax>	"failure"
<CheckDatax>	"error"
<Sleep>		1


<Msg>		"Program Local Global TLV 7 Serial number String"
<Send>		$xglc_local_tlv_7_gbl
#<Waitfor>   "Done"
#<GetData>
#<Send>
<Wait>
<GetData>
<CheckData>		"TLV write succesful"
<CheckDatax>	"failure"
<CheckDatax>	"error"

<Send>		$xglc_global_tlv_7_gbl
#<Waitfor>   "Done"
#<GetData>
#<Send>
<Wait>
<GetData>
<CheckData>		"TLV write succesful"
<CheckDatax>	"failure"
<CheckDatax>	"error"



<Msg>		"Program Local Global TLV 8 MAC String"
<Send>		$xglc_local_tlv_8_gbl
#<Waitfor>   "Done"
#<GetData>
#<Send>
<Wait>
<GetData>
<CheckData>		"TLV write succesful"
<CheckDatax>	"failure"
<CheckDatax>	"error"

<Send>		$xglc_global_tlv_8_gbl
#<Waitfor>   "Done"
#<GetData>
#<Send>
<Wait>
<GetData>
<CheckData>		"TLV write succesful"
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
	<Send>		$xglc_global_tlv_16_gbl
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


<Msg>       "Check LEDs..."
<Msg>       "Turn on all LEDs RED"
<Send>      "mw.b FFDF001A 8"
<Wait>

<Send>      "mw.b FFDF001B 2"
<Wait>

<Send>      "mw.b FFDF001C 4"
<Wait>

<Msg>       "Operator:Verify Status LEDs are Red"
<Exec>      Verify_LED_RED
<Msg>       "Turn on all LEDs Green"
<Send>      "mw.b FFDF001A 1"
<Wait>

<Send>      "mw.b FFDF001B 1"
<Wait>

<Send>      "mw.b FFDF001C 0"
<Wait>
#1E	I2C Global Enable	R/W	1	0	cs_en_i2c_global_l

<Msg>       "Operator:Verify Status LEDs are Green"
<Exec>      &Verify_LED_GREEN
<Msg>       " "
<Msg>       "Operator:Verify Press and Hold S2 Reset"
<Msg>       "Verify All Port LEDs are Green"
<Exec>      &Verify_GLCPortLED



