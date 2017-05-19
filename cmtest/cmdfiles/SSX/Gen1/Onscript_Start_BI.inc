################################################################################
#
# Module:      Onscript_Start.txt
#
# Author:      Joe White
#
# Descr:       Starts Background execution of GLC memory tests
#
# Version:    1.5  $Id: Onscript_Start_BI.inc,v 1.7 2011/05/26 19:31:26 joe Exp $
#
# Changes:    03/30/06 lowered priority, default prioriy causing a watchdog
#			  Added Slot Selection  10/09/06
#			  Added commands to stop Pfeffa on each slot(New diags)
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
#<Include>	Check_Diag_Start.inc
<Prompt>	"#"
#<Msg>   $internal_traffic_test_time_msg_GBL
<Timeout>   20
<Msg>   "Start Slot 0 Drive tests"

#<Send> 'on -p5r -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/onscriptR1./bin/ksh 60  0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
<SendslowChar>  'time on -p3r -f /net/nv-0-0 /bin/ksh /net/nv-0-0/cfint/'
<SendslowChar>    $Stoke_onscript_MC
<SendslowChar>   ' '
<SendChar>  $internal_traffic_test_time_GBL
<Sendslow>  ' 0 > /hd/dump/slot0/Onscript_slot0.txt 2>&1 &'
<Wait>

<Bypass>    $Slot_INST_1_IMC_GBL
    <Msg>   "Start Slot 1 Drive tests"
    <SendslowChar>  'time on -p3r -f /net/nv-1-0 /bin/ksh /net/nv-1-0/cfint/'
    <SendslowChar>    $Stoke_onscript_MC
    <SendslowChar>   ' '
    <SendslowChar>  $internal_traffic_test_time_GBL
    <Sendslow>  ' 1 > /hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
    <Wait>
    <Sleep> 1
</Bypass>

<Bypass>    $Slot_INST_1_GLC_GBL
    <Msg>   "Start Slot 1 Memory tests"

    #<Send> 'on -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh 60  1 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
    <SendslowChar>  'time on -p3r -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/'
    <SendslowChar>    $Stoke_onscript_GLC
    <SendslowChar>   ' '
    <SendslowChar>  $internal_traffic_test_time_GBL
    <Sendslow>  ' 1 0 > /hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
    <Wait>
 </Bypass>

<Bypass>    $Slot_INST_2_GBL
    <Msg>   "Start Slot 2 Memory tests"

    #<Send> 'on -p3r -f /net/nv-2-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh 60  2 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
    <SendslowChar>  'time on -p3r -f /net/nv-2-0 /bin/ksh /net/nv-0-0/cfint/'
    <SendslowChar>    $Stoke_onscript_GLC
    <SendslowChar>   ' '
    <SendslowChar>  $internal_traffic_test_time_GBL
    <Sendslow>  ' 2 0 > /hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
    <Wait>
</Bypass>


<Bypass>    $Slot_INST_3_GBL
    <Msg>   "Start Slot 3 Memory tests"

    #<Send> 'on -p3r -f /net/nv-3-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh 60  3 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
    <SendslowChar>  'time on -p3r -f /net/nv-3-0 /bin/ksh /net/nv-0-0/cfint/'
    <SendslowChar>    $Stoke_onscript_GLC
    <SendslowChar>   ' '
    <SendslowChar>  $internal_traffic_test_time_GBL
    <Sendslow>  ' 3 0 > /hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
    <Wait>
</Bypass>


<Bypass>    $Slot_INST_4_GBL
    <Msg>   "Start Slot 4 Memory tests"

    #<Send> 'on -p3r -f /net/nv-4-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh 60  4 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
    <SendslowChar>  'time on -p3r -f /net/nv-4-0 /bin/ksh /net/nv-0-0/cfint/'
    <SendslowChar>    $Stoke_onscript_GLC
    <SendslowChar>   ' '
    <SendslowChar>  $internal_traffic_test_time_GBL
    <Sendslow>  ' 4 0 > /hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
    <Wait>
</Bypass>

