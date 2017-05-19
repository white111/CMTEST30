################################################################################
#
# Module:      Check_Log_Error_BI_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_PRE_BI.dat, Chassis BI, Chassis_Post_BI.dat,Config.dat
#
# Version:    1.5 $Id: Check_Log_Error_BI_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#			  12/21/12 6/0B3 new message <CheckData>    "Local clock adjustment from Active IMC"
#
#
# Changes:   Created 12/2/11
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
	<CheckData>	"Peer synchronization complete"
#	<CheckDatax>	"FAIL"
	<CheckDatax>	"Error"
	<CheckDatax>	"ERROR"
	<GetData>
</Bypass>

<Msg>		"Check log for  Errors"
<Sendslow>		"show log | grep -i erro"
<Wait>
<CheckDatax>	"Error"
<CheckDatax>	"ERROR"
<GetData>
#<Msg>       "Check log for Failures"
#<Sendslow>      "show log | grep -i fai"
#<Wait>
#<CheckDatax>    "Fail"
#<CheckDatax>    "FAIL"
#<GetData>


<Msg>		"Check log for Warnings"
<Sendslow>		"show log | grep -i war"
<Wait>
<CheckData>    ".1. WARN CardAgt-CLOCK_ADJ: Local clock adjustment"
<CheckDatax>	"SINGLE_BIT_ECC"
<CheckDatax>	"CardAgt-CLOCK_ADJ"
<CheckDatax>	"EXCESSIVE_CLOCK_DRIFT"
# other warnings ignored




