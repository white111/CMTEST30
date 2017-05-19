################################################################################
#
# Module:      Check_BI_loopbacktest.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI.dat , Extended test.dat
#
# Version:    1.1 $Id: Check_EXT_loopbacktest.inc,v 1.2 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Created 10/13/06
#			  removed Check dx-sw5
#			  removed all checks except errors 03/30/06
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006 Stoke. All rights reserved.
#
################################################################################

<Msg>		"Exiting Pfeffa..."
<GetData>
<Timeout>	30
<Prompt>	"#"
<Sleep>		1
<Send> 		"exit"

<Wait>
<Msg>		"Check Packet path Slot 0"

<Send>		"pfeffa show mib > /net/nv-0-0/hd/dump/slot0/traffic.log"
<Wait>
<SendCharSlow>		$mib_filter_4_gbl
<SendSlow>		"  /net/nv-0-0/hd/dump/slot0/traffic.log ) then (cat /net/nv-0-0/hd/dump/slot0/traffic.log) fi"
<Wait>
<GetData>
<Include>	Check_BI_loopbacktest_Err.inc

<Bypass>	$Slot_INST_1_IMC_GBL
	<Msg>		"Check Packet path Slot 1 IMC"

	<Send>		"pfeffa on 1 show mib > /net/nv-1-0/hd/dump/slot1/traffic.log"
	<Wait>
	<SendCharSlow>		$mib_filter_4_gbl
	<SendSlow>		"  /net/nv-1-0/hd/dump/slot1/traffic.log ) then (cat /net/nv-1-0/hd/dump/slot1/traffic.log)  else (echo PASSED) fi"
	<Wait>
	<GetData>
	<CheckData>		"PASSED"
	<Include>	Check_BI_loopbacktest_Err.inc
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>		"Check Packet path Slot 1 GLC"
	<Sendslow>		"on -f /net/nv-1-0 ixtest errors"
	<Wait>
	<CheckData>	"XSCALE ERROR STATUS REGISTER = "
	<CheckDataX> "Bit"
	<GetData>
	<Send>		"pfeffa on 1 show mib > /net/nv-0-0/hd/dump/slot1/traffic.log"
	<Wait>
	<Send>		"pfeffa on 1 show n2 count >> /net/nv-0-0/hd/dump/slot1/traffic.log"
	<Wait>
	<SendCharSlow>		$mib_filter_4_gbl
	<SendSlow>		"  /net/nv-0-0/hd/dump/slot1/traffic.log ) then (cat /net/nv-0-0/hd/dump/slot1/traffic.log) else (echo PASSED) fi"
	<Wait>
	<GetData>
	<CheckData>		"PASSED"
	<Include>	Check_BI_loopbacktest_Err.inc
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>		"Check Packet path Slot 2"
	<Send>		"on -f /net/nv-2-0 ixtest errors"
	<Wait>
	<CheckData>	"XSCALE ERROR STATUS REGISTER = "
	<CheckDataX> "Bit"
	<GetData>

	<Send>		"pfeffa on 2 show mib> /net/nv-0-0/hd/dump/slot2/traffic.log"
	<Wait>
	<Send>		"pfeffa on 2 show n2 count >> /net/nv-0-0/hd/dump/slot2/traffic.log"
	<Wait>
	<SendCharSlow>		$mib_filter_4_gbl
	<SendSlow>		"  /net/nv-0-0/hd/dump/slot2/traffic.log ) then (cat /net/nv-0-0/hd/dump/slot2/traffic.log)  else (echo PASSED) fi"
	<Wait>
	<GetData>
	<CheckData>		"PASSED"
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>		"Check Packet path Slot 3"
	<Send>		"on -f /net/nv-3-0 ixtest errors"
	<Wait>
	<CheckData>	"XSCALE ERROR STATUS REGISTER = "
	<CheckDataX> "Bit"
	<GetData>

	<Send>		"pfeffa on 3 show mib > /net/nv-0-0/hd/dump/slot3/traffic.log"
	<Wait>
	<Send>		"pfeffa on 3 show n2 count >> /net/nv-0-0/hd/dump/slot3/traffic.log"
	<Wait>
	<SendCharSlow>		$mib_filter_4_gbl
	<SendSlow>		"  /net/nv-0-0/hd/dump/slot3/traffic.log ) then (cat /net/nv-0-0/hd/dump/slot3/traffic.log)  else (echo PASSED) fi"
	<Wait>
	<GetData>
	<CheckData>		"PASSED"
	<Include>	Check_BI_loopbacktest_Err.inc
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>		"Check Packet path Slot 4"
	<Send>		"on -f /net/nv-4-0 ixtest errors"
	<Wait>
	<CheckData>	"XSCALE ERROR STATUS REGISTER = "
	<CheckDataX> "Bit"
	<GetData>

	<Send>		"pfeffa on 4 show mib > /net/nv-0-0/hd/dump/slot4/traffic.log"
	<Wait>
	<Send>		"pfeffa on 4 show n2 count >> /net/nv-0-0/hd/dump/slot4/traffic.log"
	<Wait>
	<SendCharSlow>		$mib_filter_4_gbl
	<SendSlow>		"  /net/nv-0-0/hd/dump/slot4/traffic.log ) then (cat /net/nv-0-0/hd/dump/slot4/traffic.log)  else (echo PASSED) fi"
	<Wait>
	<GetData>
	<CheckData>		"PASSED"
	<Include>	Check_BI_loopbacktest_Err.inc
</Bypass>

#<Prompt>	"# "
#<Send>		"exit"
#<Wait>

