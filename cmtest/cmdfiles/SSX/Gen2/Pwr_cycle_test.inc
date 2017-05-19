################################################################################
#
# Module:      Pwr_cycle_test.inc 
#
# Author:      Joe White
#
# Descr:       Adding power cycling
#
# Version:    1.0 $Id: Onscript_Start.inc,v 1.9 2009/05/07 15:50:10 joe Exp $
#
# Changes:    Created 08/30/12, IDT Clock Issues
#
#
# Includes:
#
# Still ToDo:
#              - Add Looping on each test, start a process for each test
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################

#Loop 10X ~ 300 Sec per loop
#<Loop>		3000
#Loop 20X ~ 100 Sec per loop
<Loop>		2700
##Loop 12 hours
##43200
#<Loop>      43200
#<Loop>		900
<Msg>	"Run Power cycle loop"
<Power>		ON
<TimeOut>	120
<Prompt>	#
<Send>
<Msg>		"Waiting for IMC to Boot"
<Wait>
<prompt>	"^#"
<Msg>		"Waiting for Boards to finish booting"
<TimeOut>	70
<Bypass>    $Slot_INST_1_IMC_GBL
			<Msg>	"Wait for IMC Slot 1 startup"
			<SendSlow>	"time waitfor /net/nv-1-0 10"
			<wait>
			<CheckDatax>	"Unable to access /net/nv-1-0"
			<GetData>
</Bypass>

#</Bypass>
<Bypass>	$Slot_INST_1_GLC_GBL
            <Msg>	"Wait for GLC Slot 1 startup"
			<SendSlow>	"time waitfor /net/nv-1-0 10"
			<wait>
			<CheckDatax>	"Unable to access /net/nv-1-0"
			<GetData>
</Bypass>
<Bypass>	$Slot_INST_2_GBL
            <Msg>	"Wait for GLC Slot 2 startup"
			<SendSlow>	"time waitfor /net/nv-1-0 10"
			<wait>
			<CheckDatax>	"Unable to access /net/nv-1-0"
			<GetData>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
            <Msg>	"Wait for GLC Slot 3 startup"
			<SendSlow>	"time waitfor /net/nv-3-0 10"
			<wait>
			<CheckDatax>	"Unable to access /net/nv-3-0"
			<GetData>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
            <Msg>	"Wait for GLC Slot 4 startup"
			<SendSlow>	"time waitfor /net/nv-4-0 10"
			<wait>
			<CheckDatax>	"Unable to access /net/nv-4-0"
			<GetData>
</Bypass>
#<Sleep>     60
##<Sendslowchr>  'on -p 3r -f /net/nv-0-0 /bin/ksh /net/nv-0-0/cfint/'
#<Sendslowchr>   '/bin/ksh /net/nv-0-0/cfint/'
#<Sendslowchr>   $Stoke_onscript_MC
#<Sendslow>      ' 60 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot0.txt 2>&1 &'
##<SendChar> 'on -f /net/nv-0-0 /bin/ksh /net/nv-0-0/cfint/onscript_MC./bin/ksh '
##<SendChar> $internal_traffic_test_time_GBL
##<Send> ' 0 > /hd/dump/slot0/Onscript_slot0.txt 2>&1 &'
#<Wait>
#<Sleep> 1

#<Bypass>    $Slot_INST_1_IMC_GBL
#   <Msg>   "Start Slot 1 Drive tests"
#   <Sendslowchr>   'on -p 3r -f /net/nv-1-0 /bin/ksh /net/nv-1-0/cfint/'
#   <Sendslowchr>   $Stoke_onscript_MC
#   <Sendslow>      ' 60 1 > /net/nv-1-0/hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
#   #<SendChar> 'on -f /net/nv-1-0 /bin/ksh /net/nv-1-0/cfint/onscript_MC./bin/ksh '
#   #<SendChar> $internal_traffic_test_time_GBL
#   #<Send> ' 0 > /hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
#   <Wait>
#   <Sleep> 1
#</Bypass>

#<Bypass>    $Slot_INST_1_GLC_GBL
#    <Msg>   "Start Slot 1 Memory tests"
#    <Sendslowchr>   'on -p 3r -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/'
#    <Sendslowchr>    $Stoke_onscript_GLC
#    <Sendslow>      ' 60  1 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
#    #<SendChar> 'on -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
#    #<SendChar> $internal_traffic_test_time_GBL
#    #<Send> ' 1 0 > /hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
#    <Wait>
#    <Sleep> 1
#</Bypass>
#<Bypass>    $Slot_INST_2_GBL
#    <Sendslow>      'time on -p3r -f /net/nv-2-0 /bin/ksh /net/nv-0-0/cfint/GLCSRAM.ksh 60 2  > /hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
#    <wait>
#</Bypass>
#<Bypass>    $Slot_INST_3_GBL
#    <Sendslow>      'time on -p3r -f /net/nv-3-0 /bin/ksh /net/nv-0-0/cfint/GLCSRAM.ksh 60 3  > /hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
#    <wait>
#</Bypass>
#<Bypass>    $Slot_INST_4_GBL
#    <Sendslow>      'time on -p3r -f /net/nv-4-0 /bin/ksh /net/nv-0-0/cfint/GLCSRAM.ksh 60 4  > /hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
#    <wait>
#</Bypass>

#<Msg>       "Wait for Jobs to finish"
#<send>      "wait"
#<wait>
#<Msg>   "Check Slot 0 Drive tests"
#<SendSlow>  'cat /hd/dump/slot0/onfile.txt'
#<Wait>
#<GetData>
##   <SendSlow>  'cat /hd/dump/slot1/status.tmp'
##   <Wait>
##   <GetData>
#<SendSlow>  'cat /hd/dump/slot0/Onscript_slot0.txt'
#<Wait>
#<GetData>
#<CheckData> "DRIVE_TEST.Passed"

#<Bypass>    $Slot_INST_1_IMC_GBL
#   <Msg>   "Check Slot 1 Drive tests"
#   <SendSlow>  'cat /hd/dump/slot1/onfile.txt'
#   <Wait>
#   <GetData>
##   <SendSlow>  'cat /hd/dump/slot1/status.tmp'
##   <Wait>
##   <GetData>
#   <SendSlow>  'cat /hd/dump/slot1/Onscript_slot1.txt'
#   <Wait>
#   <GetData>
#   #<CheckData> "DRIVE_TEST.Passed"
#</Bypass>

#<Bypass>    $Slot_INST_1_GLC_GBL
#    <Msg>   "Check Slot 1 Memory tests"
#    <SendSlow>  'cat /hd/dump/slot1/onfile.txt'
#    <Wait>
#    <GetData>
#    <SendSlow>  'cat /hd/dump/slot0/Onscript_slot1.txt'
#    <Wait>
#    <GetData>
#    <CheckData> "Memory.Passed"
#</Bypass>
#<Bypass>    $Slot_INST_2_GBL
#    <Msg>       "Check Slot 2"
#    <SendSlow>  'cat /hd/dump/slot2/onfile.txt'
#    <Wait>
#    <GetData>
#    <SendSlow>  'cat /hd/dump/slot0/Onscript_slot2.txt'
#    <Wait>
#    <GetData>
#    <CheckData> "Memory.Passed"
#</Bypass>
#<Bypass>    $Slot_INST_3_GBL
#    <Msg>       "Check Slot 3"
#        <SendSlow>  'cat /hd/dump/slot3/onfile.txt'
#    <Wait>
#    <GetData>
#    <SendSlow>  'cat /hd/dump/slot0/Onscript_slot3.txt'
#    <Wait>
#    <GetData>
#    <CheckData> "Memory.Passed"
#</Bypass>
#<Bypass>    $Slot_INST_4_GBL
#    <Msg>       "Check Slot 4"
#    <SendSlow>  'cat /hd/dump/slot4/onfile.txt'
#    <Wait>
#    <GetData>
#    <SendSlow>  'cat /hd/dump/slot0/Onscript_slot4.txt'
#    <Wait>
#    <GetData>
#    <CheckData> "Memory.Passed"
</Bypass>
 	<power>		OFF
 	<Sleep>		6

 </Loop>

 <Power>		ON
 <TimeOut>	120
<Prompt>	#
<Send>
<Msg>		"Waiting for IMC to Boot"
<Wait>
<prompt>	"^#"
