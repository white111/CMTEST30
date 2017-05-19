################################################################################
#
# Module:      Check_swbase.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI.dat , Extended test.dat
#
# Version:    1.1 $Id: Check_swbase.inc,v 1.1 2009/05/07 15:50:10 joe Exp $
#
# Changes:    Created 4/1/09

#
#
# Still ToDo:
#
#            Copyright (c) 2006-2009 Stoke. All rights reserved.
#
################################################################################

#<Msg>       "Exiting Pfeffa..."
<GetData>
<Timeout>   30
#<Prompt>    "#"
#<Sleep>     1
#<Send>      "exit"

#<Wait>
<Msg>		"Check Swbase Slot 0"

<Send>		"pfeffa show swbase mib-cntrs > /net/nv-0-0/hd/dump/slot0/swbase.log"
<Wait>
<SendCharSlow>		$mib_filter_4_gbl
<SendSlow>		"  /net/nv-0-0/hd/dump/slot0/swbase.log ) then (cat /net/nv-0-0/hd/dump/slot0/swbase.log) fi"
<Wait>
<GetData>
<Include>	Check_loopbacktest_Err.inc

<Bypass>	$Slot_INST_1_GBL
	<Msg>		"Check Swbase Slot 1 IMC"

	<Send>		"pfeffa on 1 show swbase mib-cntrs > /net/nv-1-0/hd/dump/slot1/swbase.log"
	<Wait>
	<SendCharSlow>		$mib_filter_4_gbl
	<SendSlow>		"  /net/nv-1-0/hd/dump/slot1/swbase.log ) then (cat /net/nv-1-0/hd/dump/slot1/swbase.log)  else (echo PASSED) fi"
	<Wait>
	<GetData>
	<CheckData>		"PASSED"
	<Include>	Check_loopbacktest_Err.inc
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>		"Check Swbase Slot 2"
	<Send>		"pfeffa on 2 show swbase mib-cntrs > /net/nv-0-0/hd/dump/slot2/swbase.log"
	<Wait>
	<SendCharSlow>		$mib_filter_4_gbl
	<SendSlow>		"  /net/nv-0-0/hd/dump/slot2/swbase.log ) then (cat /net/nv-0-0/hd/dump/slot2/swbase.log)  else (echo PASSED) fi"
	<Wait>
	<GetData>
	<CheckData>		"PASSED"
	<Include>	Check_loopbacktest_Err.inc
	<SendCharSlow>		$mib_filter_gbl
	<SendSlow>		"  /net/nv-0-0/hd/dump/slot2/swbase.log ) then (echo PASSED) else (cat /net/nv-0-0/hd/dump/slot2/swbase.log; echo FAILED) fi"
	<Wait>
	<GetData>
	<CheckData>		"PASSED"
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>		"Check Swbase Slot 3"
	<Send>		"pfeffa on 3 show swbase mib-cntrs > /net/nv-0-0/hd/dump/slot3/swbase.log"
	<Wait>
	<SendCharSlow>		$mib_filter_4_gbl
	<SendSlow>		"  /net/nv-0-0/hd/dump/slot3/swbase.log ) then (cat /net/nv-0-0/hd/dump/slot3/swbase.log)  else (echo PASSED) fi"
	<Wait>
	<GetData>
	<CheckData>		"PASSED"
	<Include>	Check_loopbacktest_Err.inc
	<SendCharSlow>		$mib_filter_gbl
	<SendSlow>		"  /net/nv-0-0/hd/dump/slot3/swbase.log ) then (echo PASSED) else (cat /net/nv-0-0/hd/dump/slot3/swbase.log; echo FAILED) fi"
	<Wait>
	<GetData>
	<CheckData>		"PASSED"
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>		"Check Swbase Slot 4"
	<Send>		"pfeffa on 4 show swbase mib-cntrs > /net/nv-0-0/hd/dump/slot4/swbase.log"
	<Wait>
	<SendCharSlow>		$mib_filter_4_gbl
	<SendSlow>		"  /net/nv-0-0/hd/dump/slot4/swbase.log ) then (cat /net/nv-0-0/hd/dump/slot4/swbase.log)  else (echo PASSED) fi"
	<Wait>
	<GetData>
	<CheckData>		"PASSED"
	<Include>	Check_loopbacktest_Err.inc
	<SendCharSlow>		$mib_filter_gbl
	<SendSlow>		"  /net/nv-0-0/hd/dump/slot4/swbase.log ) then (echo PASSED) else (cat /net/nv-0-0/hd/dump/slot4/swbase.log; echo FAILED) fi"
	<Wait>
	<GetData>
	<CheckData>		"PASSED"
</Bypass>


