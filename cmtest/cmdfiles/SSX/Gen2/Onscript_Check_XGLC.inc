################################################################################
#
# Module:      Onscript_Check_XGLC.txt
#
# Author:      Joe White
#
# Descr:       Starts Background execution of GLC memory tests
#
# Version:    1.3 $Id: Onscript_Check_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 11/23/11
#			  Changed Timeoute to 1400
#			  Added Support for XGLC in Slot 1 9/3/13
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################
#<Timeout>	20
<Prompt>	'#'
<TimeOut>	1400
# Wait for background jobs to finish
<Msg>   "Wait for background jobs to finish..."
<Send>  "time wait"
<Wait>
<Send>
<Wait>
<TimeOut>	120
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
	<Send>	"ls /net/nv-1-0/hd/dump/slot1"
	<wait>
	<Send>	"ls /net/nv-1-0/hd"
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
    <SendSlow>  'cat /hd/dump/slot1/thermaltrack.txt'
    <Wait>
    <GetData>
   	<SendSlow>  'cat /hd/dump/slot1/testvoltstrack.txt'
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
    <SendSlow>  'cat /hd/dump/slot2/thermaltrack.txt'
    <Wait>
    <GetData>
   	<SendSlow>  'cat /hd/dump/slot2/testvoltstrack.txt'
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
    <SendSlow>  'cat /hd/dump/slot3/thermaltrack.txt'
    <Wait>
    <GetData>
   	<SendSlow>  'cat /hd/dump/slot3/testvoltstrack.txt'
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
    <SendSlow>  'cat /hd/dump/slot4/thermaltrack.txt'
    <Wait>
    <GetData>
   	<SendSlow>  'cat /hd/dump/slot4/testvoltstrack.txt'
    <Wait>
    <GetData>
    <SendSlow>  'cat /hd/dump/slot0/Onscript_slot4.txt'
    <Wait>
    <GetData>
    <CheckData> "Memory.Passed"
</Bypass>




########################################################
#Bypass>    $Slot_INST_2_GBL
#    <Msg>   "Check Slot 2 Memory tests"
#    <Msg>      "Test XLP 0 Fixed Slot ID 2"
#     <send>     "cat /hd/dump/slot2/Slot2_XLP0_ALIVE.txt &"
#     <wait>
#     <CheckData>  "XLP is alive"
#     <GetData>
#     <send>     "cat /hd/dump/slot2/Slot2_XLP0_KBPREG.txt &"
#     <wait>
#     <CheckData>  "KBP Register test Passed"
#     <GetData>
#     <send>     "cat /hd/dump/slot2/Slot2_XLP0_KBPPWR.txt &"
#     <wait>
#     <CheckData>  "KBP Power test Passed"
#     <GetData>
#     <send>     "cat /hd/dump/slot2/Slot2_XLP0.txt &"
#     <wait>
#     <CheckData>  "Memory test Passed"
#     <GetData>
#     <Msg>      "Test XLP 1 Fixed Slot ID 2"
#     <send>     "cat /hd/dump/slot2/Slot2_XLP1_ALIVE.txt &"
#     <wait>
#     <CheckData>  "XLP is alive"
#     <GetData>
#     <send>     "cat /hd/dump/slot2/Slot2_XLP1_KBPREG.txt &"
#     <wait>
#     <CheckData>  "KBP Register test Passed"
#     <GetData>
#     <send>     "cat /hd/dump/slot2/Slot2_XLP1_KBPPWR.txt &"
#     <wait>
#     <CheckData>  "KBP Power test Passed"
#     <GetData>
#     <send>     "cat /hd/dump/slot2/Slot2_XLP1.txt &"
#     <Wait>
#     <CheckData>  "Memory test Passed"
#     <GetData>

##    <SendSlow>  'cat /hd/dump/slot2/onfile.txt'
##    <Wait>
##    <GetData>
##    <SendSlow>  'cat /hd/dump/slot0/Onscript_slot2.txt'
##    <Wait>
##    <GetData>
##    <CheckData> "Memory.Passed"
#</Bypass>

#<Bypass>    $Slot_INST_3_GBL

#     <Msg>   "Check Slot 3 Memory tests"
##     <Msg>      "Check XLP 0 Fixed Slot ID 3
##     <prompt>       "login"
##     <send>     "SOCK=/nv telnet 192.168.203.203"
##    <wait>
##    <Prompt>    #
##    <send>      "root"
##    <wait>
##    <timeout>   60
##    <Timeout>   180
##    <msg>       "Checking Output File"
##    <Sendslow>      "if (tail /tmp/Slot_3_XLP0_*.txt | grep -iHln -e "Done" ) then (  echo "XLP0_DRAM_Done:$?") else (echo "XLP0_DRAM_Not_Done:$?")  fi"
##    <wait>
##    <GetData>
##    <CheckData>     "XLP0_DRAM_Done"
##    <Sendslow>      "if (grep -iHln -e "fail" -e "error" /tmp/Slot_3_XLP0_*.txt) then ( echo "XLP0_DRAM_FAILED:$?") else (echo "XLP0_DRAM_PASSED:$?")  fi"
##    <wait>
##    <GetData>
##    <CheckData>     "XLP0_DRAM_PASSED"
##    <Msg>       "Exit XLP0"
##    <Send>      "exit"
##    <wait>
##    <Msg>       "Check XLP 1 Fixed Slot ID 3"
##     <prompt>       "login"
##     <send>     "SOCK=/nv telnet 192.168.204.203"
##    <wait>
##    <Prompt>    #
##    <send>      "root"
##    <wait>
##    <timeout>   60
##    <Timeout>   180
##    <msg>       "Checking Output File"
##    <Sendslow>      "if (grep -iHln -e "Done" /tmp/XLP1_*.txt) then ( echo "XLP1_DRAM_Done:$?") else (echo "XLP1_DRAM_Not_Done:$?")  fi"
##    <wait>
##    <GetData>
##    <CheckData>     "XLP0_DRAM_Done"
##    <Sendslow>      "if (grep -iHln -e "fail" -e "error" /tmp/XLP0_*.txt) then (  echo "XLP1_DRAM_FAILED:$?") else (echo "XLP1_DRAM_PASSED:$?")  fi"
##    <wait>
##    <GetData>
##    <CheckData>     "XLP1_DRAM_PASSED"
##    <Msg>       "Exit XLP1"
##    <Send>      "exit"
##    <wait>
##    #    <SendSlow>  'cat /hd/dump/slot3/onfile.txt'
###    <Wait>
###    <GetData>
###    <SendSLow>  'cat /hd/dump/slot0/Onscript_slot3.txt'
###    <Wait>
###    <GetData>
###    <CheckData> "Memory.Passed"
#</Bypass>

#<Bypass>    $Slot_INST_4_GBL
#    <Msg>   "Check Slot 4 Memory tests"
##     <Msg>      "Check XLP 0ixed Slot ID 4"
##     <prompt>       "login"
##     <send>     "SOCK=/nv telnet 192.168.203.204"
##    <wait>
##    <Prompt>    #
##    <send>      "root"
##    <wait>
##    <timeout>   60
##    <Timeout>   180
##    <msg>       "Checking Output File"
##    <Sendslow>      "if (tail /tmp/XLP0_*.txt | grep -iHln -e "Done" ) then (  echo "XLP0_DRAM_Done:$?") else (echo "XLP0_DRAM_Not_Done:$?")  fi"
##    <wait>
##    <GetData>
##    <CheckData>     "XLP0_DRAM_Done"
##    <Sendslow>      "if (grep -iHln -e "fail" -e "error" /tmp/XLP0_*.txt) then ( echo "XLP0_DRAM_FAILED:$?") else (echo "XLP0_DRAM_PASSED:$?")  fi"
##    <wait>
##    <GetData>
##    <CheckData>     "XLP0_DRAM_PASSED"
##    <Msg>       "Exit XLP0"
##    <Send>      "exit"
##    <wait>
##    <Msg>       "Check XLP 1 Fixed Slot ID 4"
##     <prompt>       "login"
##     <send>     "SOCK=/nv telnet 192.168.204.204"
##    <wait>
##    <Prompt>    #
##    <send>      "root"
##    <wait>
##    <timeout>   60
##    <Timeout>   180
##    <msg>       "Checking Output File"
##    <Sendslow>      "if (tail /tmp/XLP1_*.txt | grep -iHln -e "Done" ) then ( ; echo "XLP1_DRAM_Done:$?") else (echo "XLP1_DRAM_Not_Done:$?")  fi"
##    <wait>
##    <GetData>
##    <CheckData>     "XLP1_DRAM_Done"
##    <Sendslow>      "if (grep -iHln -e "fail" -e "error" /tmp/XLP1_*.txt) then ( echo "XLP1_DRAM_FAILED:$?") else (echo "XLP1_DRAM_PASSED:$?")  fi"
##    <wait>
##    <GetData>
##    <CheckData>     "XLP1_DRAM_PASSED"
##    <Msg>       "Exit XLP1"
##    <Send>      "exit"
##    <wait>
###    <SendSlow>  'cat /hd/dump/slot4/onfile.txt'
###    <Wait>
###    <GetData>
###    <SendSlow>  'cat /hd/dump/slot0/Onscript_slot4.txt'
###    <Wait>
###    <GetData>
###    <CheckData> "Memory.Passed"
#</Bypass>
