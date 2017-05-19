################################################################################
#
# Module:      Onscript_Start_XGLC.txt
#
# Author:      Joe White
#
# Descr:       Starts Background execution of GLC memory tests
#
# Version:    1.3 $Id: Onscript_Start_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 11/23/11
#			  Added 20 Second timeout for script startup 7/9/12
#			  Added support for 4 XGLC 10/30/13
#			  11/20/13 Changed IMC test to short test bug/HD issues
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################

<Msg>	"Run Full memory and drive tests, aprox 1 hr to complete...."
<Timeout>	20
#Wait for GLC to finish loading
#<Sleep>	30
#<send>  "slay -v glc_download_server"
#<wait>
#<sleep> 2
<Msg>	"Start Slot 0 Drive tests"
<Send>  "ls /hd/dump/slot0"
<wait>
#<Sendslowchr>  'on -p 3r -f /net/nv-0-0 /bin/ksh /net/nv-0-0/cfint/'
<Sendslowchr>   '/bin/ksh /net/nv-0-0/hd/mfg/'
<Sendslowchr>   $Stoke_onscript_MC
<Sendslow>      ' 4000 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot0.txt 2>&1 &'
#<SendChar> 'on -f /net/nv-0-0 /bin/ksh /net/nv-0-0/cfint/onscript_MC./bin/ksh '
<Sleep> 5

<Bypass>	$Slot_INST_1_IMC_GBL
   <Msg>   "Start Slot 1 Drive tests"
   <Send>	"ls /hd/dump/slot1"
	<wait>
   <Sendslowchr>   'on -p 3r -f /net/nv-1-0 /bin/ksh /net/nv-1-0/hd/mfg/'
   <Sendslowchr>   $Stoke_onscript_MC
   #<Sendslow>      ' 5 1 > /net/nv-0-0/hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
   <Sendslow>      ' 4000 1 > /net/nv-0-0/hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
   #<SendChar> 'on -f /net/nv-1-0 /bin/ksh /net/nv-1-0/cfint/onscript_MC./bin/ksh '
   #<SendChar> $internal_traffic_test_time_GBL
   #<Send> ' 0 > /hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
   <Wait>
   <Sleep> 1
</Bypass>


<Bypass>    $Slot_INST_1_GLC_GBL
    <Msg>   "Start Slot 1 Memory tests"
    <Send>	"ls /hd/dump/slot1"
	<wait>
    <Sendslowchr>   'on -p 3r -f /net/nv-1-0 /bin/ksh /net/nv-0-0/hd/mfg/'
    <Sendslowchr>    $Stoke_onscript_XGLC
    <Sendslow>      ' 4000  1 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
    #<SendChar> 'on -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
    #<SendChar> $internal_traffic_test_time_GBL
    #<Send> ' 1 0 > /hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
    <Wait>
    <Sleep> 1
</Bypass>

<Bypass>    $Slot_INST_2_GBL
    <Msg>   "Start Slot 2 Memory tests"
    <Send>	"ls /hd/dump/slot2"
	<wait>
    <Sendslowchr>   'on -p 3r -f /net/nv-2-0 /bin/ksh /net/nv-0-0/hd/mfg/'
    <Sendslowchr>    $Stoke_onscript_XGLC
    <Sendslow>      ' 4000  2 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
    #<SendChar> 'on -f /net/nv-2-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
    #<SendChar> $internal_traffic_test_time_GBL
    #<Send> ' 2 0 > /hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
    <Wait>
    <Sleep> 1
</Bypass>

<Bypass>    $Slot_INST_3_GBL
    <Msg>   "Start Slot 3 Memory tests"
    <Send>	"ls /hd/dump/slot3"
	<wait>
    <Sendslowchr>   'on -p 3r -f /net/nv-3-0 /bin/ksh /net/nv-0-0/hd/mfg/'
    <Sendslowchr>    $Stoke_onscript_XGLC
    <Sendslow>      ' 4000  3 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
    #<SendChar> 'on -f /net/nv-3-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
    #<SendChar> $internal_traffic_test_time_GBL
    #<Send> ' 3 0 > /hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
    <Wait>
    <Sleep> 1
</Bypass>

<Bypass>    $Slot_INST_4_GBL
    <Msg>   "Start Slot 4 Memory tests"
    <Send>	"ls /hd/dump/slot4"
	<wait>
    <Sendslowchr>   'on -p 3r -f /net/nv-4-0 /bin/ksh /net/nv-0-0/hd/mfg/'
    <Sendslowchr>   $Stoke_onscript_XGLC
    <Sendslow>      ' 4000  4 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
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
    <Send>	"ls /hd/dump/slot0"
	<wait>
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
   <Send>	"ls /hd/dump/slot1"
	<wait>
   <SendSlow>  'cat /hd/dump/slot1/onfile.txt'
   <Wait>
   <GetData>
#   <SendSlow>  'cat /hd/dump/slot1/status.tmp'
#   <Wait>
#   <GetData>
   <SendSlow>  'cat /hd/dump/slot1/Onscript_slot1.txt'
   #<SendSlow>  '/net/nv-1-0/hd/dump/slot1/Onscript_slot1.txt"
   <Wait>
   <GetData>
   <CheckData> "DRIVE_TEST.Passed"
</Bypass>


<Bypass>    $Slot_INST_1_GLC_GBL
    <Msg>   "Check Slot 1 Memory tests"
    <Send>	"ls /hd/dump/slot1"
	<wait>
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
    <Send>	"ls /hd/dump/slot2"
	<wait>
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
    <Send>	"ls /hd/dump/slot3"
	<wait>
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
    <Send>	"ls /hd/dump/slot4"
	<wait>
    <SendSlow>  'cat /hd/dump/slot4/onfile.txt'
    <Wait>
    <GetData>
    <SendSlow>  'cat /hd/dump/slot0/Onscript_slot4.txt'
    <Wait>
    <GetData>
    <CheckData> "Memory.Passed"
</Bypass>


