################################################################################
#
# Module:      Onscript_Full_Scan.txt
#
# Author:      Joe White
#
# Descr:       Starts Background execution of GLC memory tests
#
# Version:    1.3 $Id: Onscript_Full_scan.inc,v 1.3 2009/05/07 15:50:10 joe Exp $
#
# Changes:    From Onscript Start V1.6 3/10/08
#			  IMC slot one logs to IMC slot 1 4/21/08
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

<Msg>	"Run Full memory and drive tests, aprox 1 hr to complete...."
#Wait for GLC to finish loading
#<Sleep>	30
#<send>  "slay -v glc_download_server"
#<wait>
#<sleep> 2
<Msg>	"Start Slot 0 Drive tests"

#<Sendslowchr>	'time on -p 3r -f /net/nv-0-0 /bin/ksh /net/nv-0-0/cfint/'
<Sendslowchr>	'/bin/ksh /net/nv-0-0/cfint/'
<Sendslowchr>	$Stoke_onscript_MC
<Sendslow>		' 4000 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot0.txt 2>&1 &'
#<SendChar>	'on -f /net/nv-0-0 /bin/ksh /net/nv-0-0/cfint/onscript_MC./bin/ksh '
#<SendChar>	$internal_traffic_test_time_GBL
#<Send>	' 0 > /hd/dump/slot0/Onscript_slot0.txt 2>&1 &'
<Wait>
<Sleep>	1

<Bypass>	$Slot_INST_1_IMC_GBL
   <Msg>   "Start Slot 1 Drive tests"
   <Sendslowchr>   'on -p 3r -f /net/nv-1-0 /bin/ksh /net/nv-1-0/cfint/'
   <Sendslowchr>   $Stoke_onscript_MC
   <Sendslow>      ' 4000 1 > /net/nv-1-0/hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
   #<SendChar> 'on -f /net/nv-1-0 /bin/ksh /net/nv-1-0/cfint/onscript_MC./bin/ksh '
   #<SendChar> $internal_traffic_test_time_GBL
   #<Send> ' 0 > /hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
   <Wait>
   <Sleep> 1
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>	"Start Slot 1 Memory tests"
	<Sendslowchr>	'on -p 3r -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/'
	<Sendslowchr>	 $Stoke_onscript_GLC
	<Sendslow>		' 4000  1 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
	#<SendChar>	'on -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
	#<SendChar>	$internal_traffic_test_time_GBL
	#<Send>	' 1 0 > /hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
	<Wait>
	<Sleep>	1
</Bypass>

<Bypass>    $Slot_INST_2_GBL
    <Msg>   "Start Slot 2 Memory tests"
    <Sendslowchr>   'time on -p 3r -f /net/nv-2-0 /bin/ksh /net/nv-0-0/cfint/'
    <Sendslowchr>    $Stoke_onscript_GLC
    <Sendslow>      ' 4000  2 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
    #<SendChar> 'on -f /net/nv-2-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
    #<SendChar> $internal_traffic_test_time_GBL
    #<Send> ' 2 0 > /hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
    <Wait>
    <Sleep> 1
</Bypass>

<Bypass>    $Slot_INST_3_GBL
    <Msg>   "Start Slot 3 Memory tests"
    <Sendslowchr>   'on -p 3r -f /net/nv-3-0 /bin/ksh /net/nv-0-0/cfint/'
    <Sendslowchr>    $Stoke_onscript_GLC
    <Sendslow>      ' 4000  3 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
    #<SendChar> 'on -f /net/nv-3-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
    #<SendChar> $internal_traffic_test_time_GBL
    #<Send> ' 3 0 > /hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
    <Wait>
    <Sleep> 1
</Bypass>

<Bypass>    $Slot_INST_4_GBL
    <Msg>   "Start Slot 4 Memory tests"
    <Sendslowchr>   'on -p 3r -f /net/nv-4-0 /bin/ksh /net/nv-0-0/cfint/'
    <Sendslowchr>   $Stoke_onscript_GLC
    <Sendslow>      ' 4000  4 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
    #<SendChar> 'on -f /net/nv-4-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
    #<SendChar> $internal_traffic_test_time_GBL
    #<Send> ' 4 0 > /hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
    <Wait>
    <Sleep> 1
</Bypass>

#<Timeout>	20
<Prompt>	'#'
<TimeOut>	5500
# Wait for background jobs to finish
<Msg>   "Wait for background jobs to finish..."
<Send>  "wait"
<Wait>
<Send>
<Wait>
<TimeOut>	400
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
   <SendSlow>  'cat /net/nv-1-0/hd/dump/slot1/onfile.txt'
   <Wait>
   <GetData>
#   <SendSlow>  'cat /net/nv-1-0/hd/dump/slot1/status.tmp'
#   <Wait>
#   <GetData>
   <SendSlow>  'cat /net/nv-1-0/hd/dump/slot1/Onscript_slot1.txt'
   <Wait>
   <GetData>
   <CheckData> "DRIVE_TEST.Passed"
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



