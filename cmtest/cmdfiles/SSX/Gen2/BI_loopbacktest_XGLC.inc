################################################################################
#
# Module:      BI_loopbacktest_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI.dat
#
# Version:    1.1    $Id: BI_loopbacktest_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 11/22/11
#			  Swapped 10G test to fron 1g test causes failure
#			  Added Support for XGLC in Slot 1 9/3/13
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################
#
# Version 5a1	11/12/05
#


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

<Msg>		"Starting Pfeffa 10g, Test 10g path Timed All packets looped back..."

<Timeout>	90
#<Prompt>   "> "
<Prompt>   "#"
#<Send>     "pfeffa"
#<Wait>
<Timeout>	500
<sleep>		10

<Msg>       $internal_traffic_test_time_msg_GBL

<Timeout>     $internal_traffic_test_timeout_GBL
<Sendchr>   "time pfeffa test snaketime10g  "
<sendchr>   $internal_traffic_test_time_GBL
<send>
<wait>
<GetData>
#<CheckData>	"Test Status:"
<Bypass>	$Slot_INST_1_GLC_GBL
	<CheckData>	"Slot 1 Passed"
	<CheckDatax> "Slot 1: FAILED"
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<CheckData>	"Slot 2 Passed"
	<CheckDatax> "Slot 2: FAILED"
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<CheckData>	"Slot 3 Passed"
	<CheckDatax> "Slot 3: FAILED"
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<CheckData>	"Slot 4 Passed"
	<CheckDatax> "Slot 2: FAILED"
</Bypass>
<CheckDatax>	"ERROR: Loop ended before receiving ok"
<CheckDatax> "test_results_snake does not exist"



<Msg>		"Starting Pfeffa 1g, Test 1g path Timed All packets looped back..."

#Pfeffa may be slow starting due to background testing of memory
<Timeout>	90
#<Prompt>   "> "
<Prompt>   "#"
#<Send>     "pfeffa"
#<Wait>
<Timeout>	500
<sleep>		10

<Msg>       $internal_traffic_test_time_msg_GBL

<Timeout>     $internal_traffic_test_timeout_GBL
<Sendchr>   "time pfeffa test snaketime  "
<sendchr>   $internal_traffic_test_time_GBL
<send>
<wait>
<GetData>
<CheckData>	"Test Status:"
<Bypass>	$Slot_INST_4_GBL
	<CheckData>	"Slot 4: PASSED"
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<CheckData>	"Slot 3: PASSED"
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<CheckData>	"Slot 2: PASSED"
</Bypass>
<Bypass>	$Slot_INST_1_GBL
	<CheckData>	"Slot 1: PASSED"
</Bypass>

<CheckData>	"Slot 0: PASSED"
<CheckDatax>	"ERROR: Loop ended before receiving ok"
<CheckDatax> "test_results_snake does not exist"


<Timeout>   30
<send>
<wait>

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

