################################################################################
#
# Module:      Check_Log_Error_BI.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_PRE_BI.dat, Chassis BI, Chassis_Post_BI.dat,Config.dat
#
# Version:    1.5 $Id: Check_Log_Error_BI.inc,v 1.6.4.1 2012/02/10 04:48:16 joe Exp $
#
# Changes:    Created 01/04/07 from Check_log_error, Warnings removed due to Minir larms for tempature.
#			  092807 Added warning check back check for ECC errors only
#			  110207 Added check for clock adjust warning
#			  061109 Added <CheckDatax> "EXCESSIVE_CLOCK_DRIFT", Message changed
#			  02/12/10 Increased time for 4.6
#			  12/19/11 Added Addtional Check for SRAM memory failure lowercase fail
#01/		4/25 modified <Sendslow>		"show log | grep -i rror"  - issue on terminal server

#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################

<Prompt>	"^Stoke.local.#"
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
<Sendslow>		"show log | grep -i rror"
<Wait>
<CheckDatax>	"Error"
<CheckDatax>	"ERROR"
<CheckDatax>	"error"
<GetData>
<Msg>       "Check log for Failures"
<Sendslow>      "show log | grep -i ail"
<Wait>
<CheckDatax>    "SRAM memory test failed"
#<CheckDatax>    "FAIL"
#<GetData>


<Msg>		"Check log for Warnings"
<Sendslow>		"show log | grep -i arn"
<Wait>
<CheckDatax>	"SINGLE_BIT_ECC"
<CheckDatax>	"CardAgt-CLOCK_ADJ"
<CheckDatax>	"EXCESSIVE_CLOCK_DRIFT"
# other warnings ignored




