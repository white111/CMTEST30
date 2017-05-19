################################################################################
#
# Module:      Onscript_Check.txt
#
# Author:      Joe White
#
# Descr:       Starts Background execution of GLC memory tests
#
# Version:    1.9 $Id: Onscript_Check.inc,v 1.11 2009/05/07 15:50:10 joe Exp $
#
# Changes:    Added Cat of onfile.txt
#			  Added MC tests 04/04/06
#			  Increased wait time for background jobs to finish.
#			  Swapped file cat order to see failure info.
#			  Added Bypass inst 08/01/06
#			  Added Selection for IMC or GLC in Slot1
#			  Extened Job Timout to 1200 seconds for ORT tests
#			  Added SPD read moved from Sow Ship Config
#			  Changed to Check for ^# prompt, found dram spd that had a # in the dump 9/26/12
#
# Includes:
#
# Still ToDo:
#              - Add Looping on each test, start a process for each test
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
#<Timeout>	20
<Prompt>	'^#'
<TimeOut>	1200
# Wait for background jobs to finish
<Msg>   "Wait for background jobs to finish..."
<Send>  "time wait"
<Wait>
<Send>
<Wait>
<TimeOut>	60
<Msg>   "Check Slot 0 Drive tests"
<SendSlow>  'cat /hd/dump/slot0/onfile.txt'
<Wait>
<GetData>
#   <SendSlow>  'cat /hd/dump/slot1/status.tmp'
#   <Wait>
#   <GetData>
<SendSlow>  'cat /hd/dump/slot0/Onscript_slot0.txt'
<Wait>
<GetData>
<CheckData> "DRIVE_TEST.Passed"

<Bypass>    $Slot_INST_1_IMC_GBL
   <Msg>   "Check Slot 1 Drive tests"
   <SendSlow>  'cat /hd/dump/slot1/onfile.txt'
   <Wait>
   <GetData>
#   <SendSlow>  'cat /hd/dump/slot1/status.tmp'
#   <Wait>
#   <GetData>
   <SendSlow>  'cat /hd/dump/slot1/Onscript_slot1.txt'
   <Wait>
   <GetData>
   #<CheckData> "DRIVE_TEST.Passed"
</Bypass>

<Bypass>    $Slot_INST_1_GLC_GBL
    <Msg>   "Check Slot 1 Memory tests"
    <SendSlow>  'cat /hd/dump/slot1/onfile.txt'
    <Wait>
    <GetData>
    <SendSlow>  'cat /hd/dump/slot0/Onscript_slot1.txt'
    <Wait>
    <GetData>
    <CheckData> "Memory.Passed"
</Bypass>

<Bypass>    $Slot_INST_2_GBL
    <Msg>   "Check Slot 2 Memory tests"
    <SendSlow>  'cat /hd/dump/slot2/onfile.txt'
    <Wait>
    <GetData>
    <SendSlow>  'cat /hd/dump/slot0/Onscript_slot2.txt'
    <Wait>
    <GetData>
    <CheckData> "Memory.Passed"
</Bypass>

<Bypass>    $Slot_INST_3_GBL
    <Msg>   "Check Slot 3 Memory tests"
    <SendSlow>  'cat /hd/dump/slot3/onfile.txt'
    <Wait>
    <GetData>
    <SendSLow>  'cat /hd/dump/slot0/Onscript_slot3.txt'
    <Wait>
    <GetData>
    <CheckData> "Memory.Passed"
</Bypass>

<Bypass>    $Slot_INST_4_GBL
    <Msg>   "Check Slot 4 Memory tests"
    <SendSlow>  'cat /hd/dump/slot4/onfile.txt'
    <Wait>
    <GetData>
    <SendSlow>  'cat /hd/dump/slot0/Onscript_slot4.txt'
    <Wait>
    <GetData>
    <CheckData> "Memory.Passed"
</Bypass>

#<Include>	Shell_imc.inc
<timeout>	20
<Msg>		'Get DRAM SPD info"
<Msg>	"Slot 0 IMC"
<Send>	'pfeffa on 1 rd i2c spd 0 100'
<Wait>
<GetData>
<CheckDatax>	"bad"
<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>	"Slot 1 GLC"
	<Send>	'pfeffa on 1 rd i2c spd 0 100'
	<Wait>
	<GetData>
	<CheckDatax>	"bad"
</Bypass>

<Bypass>	$Slot_INST_1_IMC_GBL
	<Msg>	"Slot 1 IMC"
	<Send>	'pfeffa on 1 rd i2c spd 0 100'
	<Wait>
	<GetData>
	<CheckDatax>	"bad"
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>	"Slot 2 GLC"
	<Send>	'pfeffa on 2 rd i2c spd 0 100'
	<Wait>
	<GetData>
	<CheckDatax>	"bad"
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>	"Slot 3 GLC"
	<Send>	'pfeffa on 3 rd i2c spd 0 100'
	<Wait>
	<GetData>
	<CheckDatax>	"bad"
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>	"Slot 4 GLC"
	<Send>	'pfeffa on 4 rd i2c spd 0 100'
	<Wait>
	<GetData>
	<CheckDatax>	"bad"
</Bypass>
