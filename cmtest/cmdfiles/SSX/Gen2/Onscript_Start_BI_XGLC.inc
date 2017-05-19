################################################################################
#
# Module:      Onscript_Start_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Starts Background execution of GLC memory tests
#
# Version:    1.2  $Id: Onscript_Start_BI_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 11/22/11
#			  Added Support for XGLC in Slot 1 9/3/13
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
#<Include>	Check_Diag_Start.inc
<Prompt>	"#"
#<Msg>   $internal_traffic_test_time_msg_GBL
<Timeout>   20
<Msg>   "Start Slot 0 Drive tests"

#<Send> 'on -p5r -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/onscriptR1./bin/ksh 60  0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
<SendslowChar>  'time on -p3r -f /net/nv-0-0 /bin/ksh /net/nv-0-0/hd/mfg/'
<SendslowChar>    $Stoke_onscript_MC
<SendslowChar>   ' '
<SendChar>  $internal_traffic_test_time_GBL
<Sendslow>  ' 0 > /hd/dump/slot0/Onscript_slot0.txt 2>&1 &'
<Wait>

<Bypass>    $Slot_INST_1_IMC_GBL
    <Msg>   "Start Slot 1 Drive tests"
    <SendslowChar>  'time on -p3r -f /net/nv-1-0 /bin/ksh /net/nv-1-0/hd/mfg/'
    <SendslowChar>    $Stoke_onscript_MC
    <SendslowChar>   ' '
    <SendslowChar>  $internal_traffic_test_time_GBL
    <Sendslow>  ' 1 > /hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
    <Wait>
    <Sleep> 1
</Bypass>

<Bypass>    $Slot_INST_1_GLC_GBL
    <Msg>   "Start Slot 1 Memory tests"
    <Send>	"ls /hd/dump/slot1"
	<wait>
     #<Send> 'on -p3r -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh 60  1 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
    <SendslowChar>  'time on -p3r -f /net/nv-1-0 /bin/ksh /net/nv-0-0/hd/mfg/'
    <SendslowChar>    $Stoke_onscript_XGLC
    <SendslowChar>   ' '
    <SendslowChar>  $internal_traffic_test_time_GBL
    <Sendslow>  ' 1  > /hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
    <Wait>
</Bypass>

<Bypass>    $Slot_INST_2_GBL
    <Msg>   "Start Slot 2 Memory tests"
    <Send>	"ls /hd/dump/slot2"
	<wait>
     #<Send> 'on -p3r -f /net/nv-2-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh 60  2 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
    <SendslowChar>  'time on -p3r -f /net/nv-2-0 /bin/ksh /net/nv-0-0/hd/mfg/'
    <SendslowChar>    $Stoke_onscript_XGLC
    <SendslowChar>   ' '
    <SendslowChar>  $internal_traffic_test_time_GBL
    <Sendslow>  ' 2  > /hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
    <Wait>
</Bypass>

<Bypass>    $Slot_INST_3_GBL
    <Msg>   "Start Slot 3 Memory tests"
     <Send>	"ls /hd/dump/slot3"
	<wait>
    #<Send> 'on -p3r -f /net/nv-3-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh 60  3 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
    <SendslowChar>  'time on -p3r -f /net/nv-3-0 /bin/ksh /net/nv-0-0/hd/mfg/'
    <SendslowChar>    $Stoke_onscript_XGLC
    <SendslowChar>   ' '
    <SendslowChar>  $internal_traffic_test_time_GBL
    <Sendslow>  ' 3 > /hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
    <Wait>
</Bypass>


<Bypass>    $Slot_INST_4_GBL
    <Msg>   "Start Slot 4 Memory tests"
    <Send>	"ls /hd/dump/slot4"
	<wait>
    #<Send> 'on -p3r -f /net/nv-4-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh 60  4 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
    <SendslowChar>  'time on -p3r -f /net/nv-4-0 /bin/ksh /net/nv-0-0/hd/mfg/'
    <SendslowChar>    $Stoke_onscript_XGLC
    <SendslowChar>   ' '
    <SendslowChar>  $internal_traffic_test_time_GBL
    <Sendslow>  ' 4  > /hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
    <Wait>
</Bypass>

