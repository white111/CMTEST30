################################################################################
#
# Module:      Check_Log_Error_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_PRE_BI.dat, Chassis BI, Chassis_Post_BI.dat,Config.dat
#
# Version:    1.2   $Id: Check_Log_Error_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 11/18/11
#			  12/21/12 6/0B3 new message <CheckData>    "Local clock adjustment from Active IMC"
#			  6/10/13 Prompt changes in 6.1R2/13.1
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2013 Stoke. All rights reserved.
#
################################################################################

<Prompt>	"[local]#"
<TimeOut>	10
<Send>
<Wait>
<TimeOut>	35
<Send>		"terminal length infinite"
<Wait>
<Msg>		"Check log for Errors"

<Bypass>	$HA_Session
	<Msg>		"Check log for Sync Errors"
	<Sendslow>		"show log | grep -i SYNC"
	<Wait>
	<GetData>
	<CheckData>	"Peer synchronization complete"
	<CheckDatax>	"FAIL"
	<CheckDatax>	"Error"
	<CheckDatax>	"ERROR"
</Bypass>

<Msg>		"Check log for  Errors"
<Sendslow>		"show log | grep -i error"
<Wait>
<GetData>
<CheckDatax>	"Error"
<CheckDatax>	"ERROR"

<Msg>		"Check log for Failures"
<Sendslow>		"show log | grep -i fai"
<Wait>
<GetData>
<CheckDatax>	"Fail"
<CheckDatax>	"FAIL"


<Msg>		"Check log for Warnings"
<Sendslow>		"show log | grep -i war"
<Wait>
#ec 21 19:05:28 [0] INFO CardMgr-CARD_DETECT: IMC1 detected in slot 1
#Dec 21 19:05:28 [1] WARN CardAgt-CLOCK_ADJ: Local clock adjustment from Active IMC (-7s 86998us)
#Dec 21 19:05:41 [0
<GetData>
<Bypass>	$HA_Session
	<CheckData>    ".1. WARN CardAgt-CLOCK_ADJ: Local clock adjustment"
</Bypass>
<CheckDatax>	"SINGLE_BIT_ECC"
<CheckDatax>	"ECC"
<CheckDatax>	"CardAgt-CLOCK_ADJ"
<CheckDataX>	"WARN Fsync-CLEANUP_FAIL"

<Msg>		"Check log for Critical"
<Sendslow>		"show log | grep -i CRI"
<Wait>
<GetData>
<CheckDatax>	"CRIT"




