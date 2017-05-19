################################################################################
#
# Module:      Onscript_Start_XGLC.txt
#
# Author:      Joe White
#
# Descr:       Starts Background execution of GLC memory tests
#
# Version:    1.2 $Id: Onscript_Start_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 11/23/11
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

<Msg>	"Run 120 second test Drive and Memory test, Test all SRAM"
#Wait for GLC to finish loading
#<Sleep>	30
#<send>  "slay -v glc_download_server"
#<wait>
#<sleep> 2
<Msg>	"Start Slot 0 Drive tests"
<Send>	"ls /hd/dump/slot0"
<wait>
#<Sendslowchr>	'on -p 3r -f /net/nv-0-0 /bin/ksh /net/nv-0-0/cfint/'
<Sendslowchr>	'/bin/ksh /net/nv-0-0/hd/mfg/'
<Sendslowchr>	$Stoke_onscript_MC
<Sendslow>		' 130 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot0.txt 2>&1 &'
#<SendChar>	'on -f /net/nv-0-0 /bin/ksh /net/nv-0-0/cfint/onscript_MC./bin/ksh '
#<SendChar>	$internal_traffic_test_time_GBL
#<Send>	' 0 > /hd/dump/slot0/Onscript_slot0.txt 2>&1 &'
<Wait>
<Sleep>	1

<Bypass>	$Slot_INST_1_IMC_GBL
   <Msg>   "Start Slot 1 Drive tests"
   <Send>	"ls /hd/dump/slot1"
	<wait>
	<Send>	"ls /net/nv-1-0/hd/dump/slot1"
	<wait>
	<Send>	"ls /net/nv-1-0/hd"
	<wait>
   <Sendslowchr>   'on -p 3r -f /net/nv-1-0 /bin/ksh /net/nv-1-0/hd/mfg/'
   <Sendslowchr>   $Stoke_onscript_MC
   <Sendslow>      ' 130 1 > /net/nv-0-0/hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
   #<SendChar> 'on -f /net/nv-1-0 /bin/ksh /net/nv-1-0/cfint/onscript_MC./bin/ksh '
   #<SendChar> $internal_traffic_test_time_GBL
   #<Send> ' 0 > /hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
   <Wait>
   <Sleep> 1
</Bypass>



<Bypass>    $Slot_INST_1_GLC_GBL
    <Msg>   "Start Slot 1 Memory tests"
    <Send>	"ls /hd/dump/slot2"
	<wait>
    <Sendslowchr>   'on -p 3r -f /net/nv-1-0 /bin/ksh /net/nv-0-0/hd/mfg/'
    <Sendslowchr>    $Stoke_onscript_XGLC
    <Sendslow>      ' 130  1 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
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
    <Sendslow>      ' 130  2 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
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
    <Sendslow>      ' 130  3 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
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
    <Sendslow>      ' 130  4 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
    #<SendChar> 'on -f /net/nv-4-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
    #<SendChar> $internal_traffic_test_time_GBL
    #<Send> ' 4 0 > /hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
    <Wait>
    <Sleep> 1
</Bypass>


#<Bypass>    $Slot_INST_2_GBL
#    <Msg>   "Start Slot 2 Memory tests"
#     <Msg>      "Test XLP 0 Fixed Slot ID 2"
#     <send>     "on -p3r -f  /net/nv-2-0 imcxglctest -t 0 diagtest checkalive > /net/nv-0-0/hd/dump/slot2/Slot2_XLP0_ALIVE.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-2-0 imcxglctest -t 0 diagtest kbpdiag -regtest > /net/nv-0-0/hd/dump/slot2/Slot2_XLP0_KBPREG.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-2-0 imcxglctest -t 0 diagtest kbpdiag -pwrtest > /net/nv-0-0/hd/dump/slot2/Slot2_XLP0_KBPPWR.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-2-0 imcxglctest -t 0 diagtest memtest -b -l -t 32 16M 1 > /net/nv-0-0/hd/dump/slot2/Slot2_XLP0.txt &"
#     <wait>
#     <Msg>      "Test XLP 1 Fixed Slot ID 2"
#     <send>     "on -p3r -f  /net/nv-2-0 imcxglctest -t 1 diagtest checkalive > /net/nv-0-0/hd/dump/slot2/Slot2_XLP1_ALIVE.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-2-0 imcxglctest -t 1 diagtest kbpdiag -regtest > /net/nv-0-0/hd/dump/slot2/Slot2_XLP1_KBPREG.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-2-0 imcxglctest -t 1 diagtest kbpdiag -pwrtest > /net/nv-0-0/hd/dump/slot2/Slot2_XLP1_KBPPWR.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-2-0 imcxglctest -t 1 diagtest memtest -b -l -t 1 16M 1 > /net/nv-0-0/hd/dump/slot2/Slot2_XLP1.txt &"
#     <wait>
##     <prompt>       "login"
##     <send>     "SOCK=/nv telnet 192.168.203.202"
##    <wait>
##    <Prompt>    #
##    <send>      "root"
##    <wait>
##    <timeout>   60
##    <Timeout>   180
##    <msg>       "Testing XLP0 DDR 32 cores 5M each"
##    <send>          "nohup memtest -t 32 5M 1 > /tmp/Slot_2_XLP0_5M.txt &"
##    <wait>
##    <GetData>
##    <Msg>       "Exit XLP0"
##    <Send>      "exit"
##    <wait>

##     <Msg>      "Test XLP 1 Fixed Slot ID 2"
##     <send>     "imcxglctest -t 0 diagtest memtest -b -l -t 32 16M 1 > /hd/dump/slot2/Slot2_XLP0.txt &
##     <wait>
##     <prompt>       "login"
##     <send>     "SOCK=/nv telnet 192.168.204.202"
##    <wait>
##    <Prompt>    #
##    <send>      "root"
##    <wait>
##    <timeout>   60
##    <Timeout>   180
##    <msg>       "Testing XLP1 DDR 32 cores 5M each"
##    <send>          "nohup memtest -t 32 5M 1 > /tmp/Slot_2_XLP0_5M.txt &"
##    <wait>
##    <GetData>
##    <Msg>       "Exit XLP1"
##    <Send>      "exit"
##    <wait>

##    #<Send> 'on -p3r -f /net/nv-2-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh 60  2 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
##    <SendslowChar>  'time on -p3r -f /net/nv-2-0 /bin/ksh /net/nv-0-0/hd/mfg/'
##    <SendslowChar>    $Stoke_onscript_GLC
##    <SendslowChar>   ' '
##    <SendslowChar>  $internal_traffic_test_time_GBL
##    <Sendslow>  ' 2 0 > /hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
##    <Wait>
#</Bypass>


#<Bypass>    $Slot_INST_3_GBL
#    <Msg>   "Start Slot 3 Memory tests"
#         <Msg>      "Test XLP 0 Fixed Slot ID 3"
#     <send>     "on -p3r -f  /net/nv-3-0 imcxglctest -t 0 diagtest checkalive > /net/nv-0-0/hd/dump/slot3/Slot3_XLP0_ALIVE.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-3-0 imcxglctest -t 0 diagtest kbpdiag -regtest > /net/nv-0-0/hd/dump/slot3/Slot3_XLP0_KBPREG.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-3-0 imcxglctest -t 0 diagtest kbpdiag -pwrtest > /net/nv-0-0/hd/dump/slot3/Slot3_XLP0_KBPPWR.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-3-0 imcxglctest -t 0 diagtest memtest -b -l -t 32 16M 1 > /net/nv-0-0/hd/dump/slot3/Slot3_XLP0.txt &"
#     <wait>
#     <Msg>      "Test XLP 1 Fixed Slot ID 3"
#     <send>     "on -p3r -f  /net/nv-3-0 imcxglctest -t 1 diagtest checkalive > /net/nv-0-0/hd/dump/slot3/Slot3_XLP1_ALIVE.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-3-0 imcxglctest -t 1 diagtest kbpdiag -regtest > /net/nv-0-0/hd/dump/slot3/Slot3_XLP1_KBPREG.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-3-0 imcxglctest -t 1 diagtest kbpdiag -pwrtest > /net/nv-0-0/hd/dump/slot3/Slot3_XLP1_KBPPWR.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-3-0 imcxglctest -t 1 diagtest memtest -b -l -t 1 16M 1 > /net/nv-0-0/hd/dump/slot3/Slot3_XLP1.txt &"
#     <wait>

##     <Msg>      "Test XLP 0 Fixed Slot ID 3"
##     <prompt>       "login"
##     <send>     "SOCK=/nv telnet 192.168.203.203"
##    <wait>
##    <Prompt>    #
##    <send>      "root"
##    <wait>
##    <timeout>   60
##    <Timeout>   180
##    <msg>       "Testing XLP0 DDR 32 cores 5M each"
##    <send>          "nohup time memtest -t 32 5M 1 > /tmp/Slot_2_XLP0_5M.txt &"
##    <wait>
##    <GetData>
##    <Msg>       "Exit XLP0"
##    <Send>      "exit"
##    <wait>

##     <Msg>      "Test XLP 1 Fixed Slot ID 3"
##     <prompt>       "login"
##     <send>     "SOCK=/nv telnet 192.168.204.203"
##    <wait>
##    <Prompt>    #
##    <send>      "root"
##    <wait>
##    <timeout>   60
##    <Timeout>   180
##    <msg>       "Testing XLP1 DDR 32 cores 5M each"
##    <send>          "nohup time memtest -t 32 5M 1 > /tmp/Slot_2_XLP0_5M.txt &"
##    <wait>
##    <GetData>
##    <Msg>       "Exit XLP1"
##    <Send>      "exit"
##    <wait>

###    #<Send> 'on -p3r -f /net/nv-3-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh 60  3 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
###    <SendslowChar>  'time on -p3r -f /net/nv-3-0 /bin/ksh /net/nv-0-0/hd/mfg/'
###    <SendslowChar>    $Stoke_onscript_GLC
###    <SendslowChar>   ' '
###    <SendslowChar>  $internal_traffic_test_time_GBL
###    <Sendslow>  ' 3 0 > /hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
###    <Wait>
#</Bypass>


#<Bypass>    $Slot_INST_4_GBL
#    <Msg>   "Start Slot 4 Memory tests"
#             <Msg>      "Test XLP 0 Fixed Slot ID 4"
#     <send>     "on -p3r -f  /net/nv-4-0 imcxglctest -t 0 diagtest checkalive > /net/nv-0-0/hd/dump/slot4/Slot4_XLP0_ALIVE.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-4-0 imcxglctest -t 0 diagtest kbpdiag -regtest > /net/nv-0-0/hd/dump/slot4/Slot4_XLP0_KBPREG.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-4-0 imcxglctest -t 0 diagtest kbpdiag -pwrtest > /net/nv-0-0/hd/dump/slot4/Slot4_XLP0_KBPPWR.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-4-0 imcxglctest -t 0 diagtest memtest -b -l -t 32 16M 1 > /net/nv-0-0/hd/dump/slot4/Slot4_XLP0.txt &"
#     <wait>
#     <Msg>      "Test XLP 1 Fixed Slot ID 4"
#     <send>     "on -p3r -f  /net/nv-4-0 imcxglctest -t 1 diagtest checkalive > /net/nv-0-0/hd/dump/slot4/Slot4_XLP1_ALIVE.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-4-0 imcxglctest -t 1 diagtest kbpdiag -regtest > /net/nv-0-0/hd/dump/slot4/Slot4_XLP1_KBPREG.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-4-0 imcxglctest -t 1 diagtest kbpdiag -pwrtest > /net/nv-0-0/hd/dump/slot4/Slot4_XLP1_KBPPWR.txt &"
#     <wait>
#     <send>     "on -p3r -f  /net/nv-4-0 imcxglctest -t 1 diagtest memtest -b -l -t 1 16M 1 > /net/nv-0-0/hd/dump/slot4/Slot4_XLP1.txt &"
#     <wait>

##     <Msg>      "Test XLP 0 Fixed Slot ID 4"
##     <prompt>       "login"
##     <send>     "SOCK=/nv telnet 192.168.203.204"
##    <wait>
##    <Prompt>    #
##    <send>      "root"
##    <wait>
##    <timeout>   60
##    <Timeout>   180
##    <msg>       "Testing XLP0 DDR 32 cores 5M each"
##    <send>          "nohup time memtest -t 32 5M 1 > /tmp/Slot_4_XLP0_5M.txt &"
##    <wait>
##    <GetData>
##    <Msg>       "Exit XLP0"
##    <Send>      "exit"
##    <wait>

##     <Msg>      "Test XLP 1 Fixed Slot ID 4"
##     <prompt>       "login"
##     <send>     "SOCK=/nv telnet 192.168.204.204"
##    <wait>
##    <Prompt>    #
##    <send>      "root"
##    <wait>
##    <timeout>   60
##    <Timeout>   180
##    <msg>       "Testing XLP1 DDR 32 cores 5M each"
##    <send>          "nohup time memtest -t 32 5M 1 > /tmp/Slot_4_XLP0_5M.txt &"
##    <wait>
##    <GetData>
##    <Msg>       "Exit XLP1"
##    <Send>      "exit"
##    <wait>

###    #<Send> 'on -p3r -f /net/nv-4-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh 60  4 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
###    <SendslowChar>  'time on -p3r -f /net/nv-4-0 /bin/ksh /net/nv-0-0/hd/mfg/'
###    <SendslowChar>    $Stoke_onscript_GLC
###    <SendslowChar>   ' '
###    <SendslowChar>  $internal_traffic_test_time_GBL
###    <Sendslow>  ' 4 0 > /hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
###    <Wait>
#</Bypass>


##<Bypass>    $Slot_INST_1_GLC_GBL
##    <Msg>   "Start Slot 1 Memory tests"
##    <Sendslowchr>   'on -p 3r -f /net/nv-1-0 /bin/ksh /net/nv-0-0/hd/mfg/'
##    <Sendslowchr>    $Stoke_onscript_GLC
##    <Sendslow>      ' 60  1 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
##    #<SendChar> 'on -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
##    #<SendChar> $internal_traffic_test_time_GBL
##    #<Send> ' 1 0 > /hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
##    <Wait>
##    <Sleep> 1
##</Bypass>

