################################################################################
#
# Module:      Internal_Snake_setup_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Pe,BI,POST.dat
#
# Version:    1.5   $Id: Internal_Snake_setup_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 11/22/11
#			  3/6/12 send -> SendSlow
#			  Added Support for XGLC in Slot 1 9/3/13
#			  Changes for 13.1 Based Diags 8/4/14
#
# Still ToDo:
#
#
#
#            Copyright (c) 2005-2014 Stoke. All rights reserved.
#
################################################################################
#
# Version 5a1	11/12/05
#
<Msg>		"Setup Fabric ..."
<Prompt>	"#"
<Timeout>	150

<Bypass>	$Slot_INST_1_IMC_GBL
	<Msg>	"Wait for Slot 1 IMC"
	<sendslow>	'waitfor /net/nv-1-0/stoke/bin/diag/mc.setup.fabsnake 100'
	<Wait>
	<CheckDatax> "on: No such file or directory .mc.setup.fabsnake"
</Bypass>


<Bypass>    	$Slot_INST_1_GLC_GBL
    <Msg>   "Wait for Slot 1"
    <Send>  'waitfor /net/nv-1-0/stoke/bin/diag/*[Dd]iag* 100'
    <Wait>
    <CheckDatax> "Unable to access"
</Bypass>

<Bypass>    $Slot_INST_2_GBL
    <Msg>   "Wait for Slot 2"
    <Send>  'waitfor /net/nv-2-0/stoke/bin/diag/*[Dd]iag* 100'
    <Wait>
    <CheckDatax> "Unable to access"
</Bypass>

<Bypass>    $Slot_INST_3_GBL
    <Msg>   "Wait for Slot 3"
    <Send>  'waitfor /net/nv-3-0/stoke/bin/diag/*[Dd]iag* 100'
    <Wait>
    <CheckDatax> "Unable to access"
</Bypass>

<Bypass>    $Slot_INST_4_GBL
    <Msg>   "Wait for Slot 4"
    <Send>  'waitfor /net/nv-4-0/stoke/bin/diag/*[Dd]iag* 100'
    <Wait>
    <CheckDatax> "Unable to access"
</Bypass>

<Msg>	"Wait 60 Sec..."
<sleep>	60

<Bypass>    $Slot_INST_1_GLC_GBL
    <Msg>   "Check XLP0 Slot 1"
    <sendslow> 'on -f /net/nv-1-0/ imcxglctest -t 0 diagtest checkalive > /tmp/XLP0_ALIVE.tmp'
	<wait>
	<sendslow>	'if (grep -q "XLP is alive" /tmp/XLP0_ALIVE.tmp) then (echo "XLP0_ALIVE:passed") else (on -f /net/nv-1-0 nvctl -R;sleep 120; echo "XLP0_ALIVE:restarted")  fi'
	<wait>
	<Getdata>
	<Msg>   "Check XLP1 Slot 1"
    <sendslow> 'on -f /net/nv-1-0/ imcxglctest -t 1 diagtest checkalive > /tmp/XLP1_ALIVE.tmp'
	<wait>
	<sendslow>	'if (grep -q "XLP is alive" /tmp/XLP1_ALIVE.tmp) then (echo "XLP1_ALIVE:passed") else (on -f /net/nv-1-0 nvctl -R;sleep 120; echo "XLP1_ALIVE:restarted")  fi'
	<wait>
	<Getdata>
	#enable active led
    <sendslow> 'on -f /net/nv-1-0/ xglcdiag cpldacc wr 66 f'
	<wait>
</Bypass>

<Bypass>    $Slot_INST_2_GBL
    <Msg>   "Check XLP0 Slot 2"
    <sendslow> 'on -f /net/nv-2-0/ imcxglctest -t 0 diagtest checkalive > /tmp/XLP0_ALIVE.tmp'
	<wait>
	<sendslow>	'if (grep -q "XLP is alive" /tmp/XLP0_ALIVE.tmp) then (echo "XLP0_ALIVE:passed") else (on -f /net/nv-2-0 nvctl -R;sleep 120; echo "XLP0_ALIVE:restarted")  fi'
	<wait>
	<Getdata>
	<Msg>   "Check XLP1 Slot 2"
    <sendslow> 'on -f /net/nv-2-0/ imcxglctest -t 1 diagtest checkalive > /tmp/XLP1_ALIVE.tmp'
	<wait>
	<sendslow>	'if (grep -q "XLP is alive" /tmp/XLP1_ALIVE.tmp) then (echo "XLP1_ALIVE:passed") else (on -f /net/nv-2-0 nvctl -R;sleep 120; echo "XLP1_ALIVE:restarted")  fi'
	<wait>
	<Getdata>
	#enable active led
    <sendslow> 'on -f /net/nv-2-0/ xglcdiag cpldacc wr 66 f'
	<wait>
</Bypass>

<Bypass>    $Slot_INST_3_GBL
   <Msg>   "Check XLP0 Slot 3"
    <sendslow> 'on -f /net/nv-2-0/ imcxglctest -t 0 diagtest checkalive > /tmp/XLP0_ALIVE.tmp'
	<wait>
	<sendslow>	'if (grep -q "XLP is alive" /tmp/XLP0_ALIVE.tmp) then (echo "XLP0_ALIVE:passed") else (on -f /net/nv-3-0 nvctl -R;sleep 120; echo "XLP0_ALIVE:restarted")  fi'
	<wait>
	<Getdata>
    <Msg>   "Check XLP1 Slot 3"
    <sendslow> 'on -f /net/nv-3-0/ imcxglctest -t 1 diagtest checkalive > /tmp/XLP1_ALIVE.tmp'
	<wait>
	<sendslow>	'if (grep -q "XLP is alive" /tmp/XLP1_ALIVE.tmp) then (echo "XLP1_ALIVE:passed") else (on -f /net/nv-3-0 nvctl -R;sleep 120; echo "XLP1_ALIVE:restarted")  fi'
	<wait>
	<Getdata>
	#enable active led
    <sendslow> 'on -f /net/nv-3-0/ xglcdiag cpldacc wr 66 f'
	<wait>
</Bypass>

<Bypass>    $Slot_INST_4_GBL
   <Msg>   "Check XLP0 Slot 4"
    <sendslow> 'on -f /net/nv-4-0/ imcxglctest -t 0 diagtest checkalive > /tmp/XLP0_ALIVE.tmp'
	<wait>
	<sendslow>	'if (grep -q "XLP is alive" /tmp/XLP0_ALIVE.tmp) then (echo "XLP0_ALIVE:passed") else (on -f /net/nv-4-0 nvctl -R;sleep 120; echo "XLP0_ALIVE:restarted")  fi'
	<wait>
	<Getdata>
    <Msg>   "Check XLP1 Slot 4"
    <sendslow> 'on -f /net/nv-4-0/ imcxglctest -t 1 diagtest checkalive > /tmp/XLP1_ALIVE.tmp'
	<wait>
	<sendslow>	'if (grep -q "XLP is alive" /tmp/XLP1_ALIVE.tmp) then (echo "XLP1_ALIVE:passed") else (on -f /net/nv-4-0 nvctl -R;sleep 120; echo "XLP1_ALIVE:restarted")  fi'
	<wait>
	<Getdata>
	#enable active led
    <sendslow> 'on -f /net/nv-4-0/ xglcdiag cpldacc wr 66 f'
	<wait>
</Bypass>


<Include>	Check_1gig_SFP.inc



##########  Clear any XGLC Error Counters? ##############
<Timeout>   20
<Bypass>    $Slot_INST_1_GLC_GBL
 	#disable active led
    <sendslow> 'on -f /net/nv-1-0/ xglcdiag tdnt clear counters all'
	<wait>
</Bypass>

<Bypass>    $Slot_INST_2_GBL
	#disable active led
    <sendslow> 'on -f /net/nv-2-0/ xglcdiag tdnt clear counters all'
	<wait>
</Bypass>

<Bypass>    $Slot_INST_3_GBL
	#disable active led
    <sendslow> 'on -f /net/nv-3-0/ xglcdiag tdnt clear counters all'
	<wait>
</Bypass>

<Bypass>    $Slot_INST_4_GBL
 	#disable active led
    <sendslow> 'on -f /net/nv-4-0/ xglcdiag tdnt clear counters all'
	<wait>
</Bypass>


<Msg>		"Starting Pfeffa 1g, Test 1gig path 1/100 packets looped back..."
#

<Prompt>   "slot 0:>"
<sendslow>     "pfeffa"
<Wait>
<Timeout>	300

<sendslow>		"show vers"
<Sleep>		2
<sendslow>		"show version"
<Wait>
<sendslow>		"show version"
<Wait>
<sendslow>		"show version"
<Wait>
<sendslow>
<Wait>
<Sendslow>      "test snake"
<Wait>
<GetData>
<CheckData> "Test Status:"
<Bypass>    $Slot_INST_4_GBL
    <CheckData> "Slot 4: PASSED"
</Bypass>
<Bypass>    $Slot_INST_3_GBL
    <CheckData> "Slot 3: PASSED"
</Bypass>
<Bypass>    $Slot_INST_2_GBL
    <CheckData> "Slot 2: PASSED"
</Bypass>
<Bypass>    $Slot_INST_1_GBL
    <CheckData> "Slot 1: PASSED"
</Bypass>

<CheckData> "Slot 0: PASSED"
<CheckDatax>	"ERROR: Loop ended before receiving ok"
<CheckDatax> "test_results_snake does not exist"
#<GetData>

<Sleep>     3
<Sendslow>      'clear mibs'
<Wait>
<GetData>


<Msg>		"Starting Pfeffa 10g, Test All slots 10gig path 20 Sec..."
#


<sendslow>		"show vers"
<Sleep>		2
<sendslow>		"show version"
<Wait>
<sendslow>		"show version"
<Wait>
<sendslow>		"show version"
<Wait>
<sendslow>
<Wait>
<Sendslow>		"test snaketime10g 20"
<Wait>
<GetData>
#<CheckData>	"Test Status:"
<Bypass>	$Slot_INST_1_GLC_GBL
	<CheckData>	"Slot 1 Passed"
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<CheckData>	"Slot 2 Passed"
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<CheckData>	"Slot 3 Passed"
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<CheckData>	"Slot 4 Passed"
</Bypass>
<CheckDatax>	"ERROR: Loop ended before receiving ok"
<CheckDatax> "test_results_snake does not exist"

#<Sleep>     3
#<Sendslow>      'clear mibs'
#<Wait>
#<GetData>





<Msg>		"Exiting Pfeffa..."
<GetData>
<Timeout>	30
<Prompt>	"#"
<Sleep>		1
<Sendslow> 		"exit"
<Wait>
<Bypass>    $Slot_INST_1_GLC_GBL
	#disable active led
    <sendslow> 'on -f /net/nv-1-0/ xglcdiag cpldacc wr 66 0'
	<wait>

	<sendslow> 'on -f /net/nv-1-0/ xglcdiag tdnt show error'
	<wait>
	<GetData>
 	#
    <sendslow> 'on -f /net/nv-1-0/ xglcdiag tdnt show int'
	<wait>
	<GetData>
	#
    <sendslow> 'on -f /net/nv-1-0/ xglcdiag tdnt show counters NZ'
	<wait>
	<GetData>
 	#
    <sendslow> 'on -f /net/nv-1-0/ xglcdiag tdnt show counter ErDisc'
	<wait>
	<GetData>
</Bypass>

<Bypass>    $Slot_INST_2_GBL
	#disable active led
    <sendslow> 'on -f /net/nv-2-0/ xglcdiag cpldacc wr 66 0'
	<wait>

	<sendslow> 'on -f /net/nv-2-0/ xglcdiag tdnt show error'
	<wait>
	<GetData>
 	#
    <sendslow> 'on -f /net/nv-2-0/ xglcdiag tdnt show int'
	<wait>
	<GetData>
	#
    <sendslow> 'on -f /net/nv-2-0/ xglcdiag tdnt show counters NZ'
	<wait>
	<GetData>
 	#
    <sendslow> 'on -f /net/nv-2-0/ xglcdiag tdnt show counter ErDisc'
	<wait>
	<GetData>
</Bypass>

<Bypass>    $Slot_INST_3_GBL
	#disable active led
    <sendslow> 'on -f /net/nv-3-0/ xglcdiag cpldacc wr 66 0'
	<wait>

    <sendslow> 'on -f /net/nv-3-0/ xglcdiag tdnt show error'
	<wait>
	<GetData>
 	#
    <sendslow> 'on -f /net/nv-3-0/ xglcdiag tdnt show int'
	<wait>
	<GetData>
	#
    <sendslow> 'on -f /net/nv-3-0/ xglcdiag tdnt show counters NZ'
	<wait>
	<GetData>
 	#
    <sendslow> 'on -f /net/nv-3-0/ xglcdiag tdnt show counter ErDisc'
	<wait>
	<GetData>
</Bypass>

<Bypass>    $Slot_INST_4_GBL
 	#disable active led
    <sendslow> 'on -f /net/nv-4-0/ xglcdiag cpldacc wr 66 0'
	<wait>
 	#
    <sendslow> 'on -f /net/nv-4-0/ xglcdiag tdnt show error'
	<wait>
	<GetData>
 	#
    <sendslow> 'on -f /net/nv-4-0/ xglcdiag tdnt show int'
	<wait>
	<GetData>
	#
    <sendslow> 'on -f /net/nv-4-0/ xglcdiag tdnt show counters NZ'
	<wait>
	<GetData>
 	#
    <sendslow> 'on -f /net/nv-4-0/ xglcdiag tdnt show counter ErDisc'
	<wait>
	<GetData>
</Bypass>
