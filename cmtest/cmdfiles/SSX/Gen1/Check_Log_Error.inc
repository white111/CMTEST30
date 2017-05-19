################################################################################
#
# Module:      Check_Log_Error.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_PRE_BI.dat, Chassis BI, Chassis_Post_BI.dat,Config.dat
#
# Version:    1.8   $Id: Check_Log_Error.inc,v 1.10.4.1 2012/02/10 04:48:16 joe Exp $
#
# Changes:    Created 10/17/06
#			  08/28/07 Added Check for Single bit ECC warnings
#             11/07/07 Added Clock drift warnings
#			  02/12/10 Increased time for 4.6
#			  11/10/10 Added Critical Check
#			  01/21/11 Added Addtional ECC check
#			  12/19/11 Added Addtional Check for SRAM memory failure lowercase fail
#			  01/12/12 modified <Sendslow>		"show log | grep -i rror"  - issue on terminal server
#			  05/31/12 modified for case 1296 , added detection of hotswap,set terminal witdth 160
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
<Send>		"terminal width 160"
<Wait>
<Msg>		"Check log for Errors"

<Bypass>	$HA_Session
	<Msg>		"Check log for Sync Errors"
	<Sendslow>		"show log | grep -i SYNC"
	<Wait>
	<CheckData>	"Peer synchronization complete"
	<CheckDatax>	"FAIL"
	<CheckDatax>	"fail"
	<CheckDatax>	"Error"
	<CheckDatax>	"ERROR"
	<CheckDatax>	"error"
	<GetData>
</Bypass>

<Msg>		"Check log for  Errors"
<Sendslow>		"show log | grep -i rror"
<Wait>
<CheckDatax>	"Error"
<CheckDatax>	"ERROR"
<CheckDatax>	"error"

<Sendslow>      "show log | grep -i rr"
<Wait>
<CheckDatax>    "Err"
<CheckDatax>    "ERR"
<CheckDatax>    "err"
<GetData>

<Msg>		"Check log for Failures"
<Sendslow>		"show log | grep -i ail"
<Wait>
<CheckDatax>	"Fail"
<CheckDatax>	"FAIL"
<CheckDatax>	"fail"
<CheckDatax>	"SRAM memory test failed"
<GetData>

<Msg>		"Check log for Hotswap"
<Sendslow>		"show log | grep -i hot"
<Wait>
#Detect first insertion ( system startup)
# Expect log includs control char after Fant
#<CheckData>	"detected hotswap. FANTRAY1"
<CheckData>	"detected hotswap. FAN"
#<CheckData>	"detected hotswap. FANTRAY2"
<CheckData>	"detected hotswap. FAN"
<CheckData>	"detected hotswap. PEMA"
<CheckData>	"detected hotswap. PEMB"
<CheckData>	"hotswap. ALAR"
#Check that no addtional hotswaps have occured
<CheckDatax>	"detected hotswap. FAN"
<CheckDatax>	"detected hotswap. PEMA"
<CheckDatax>	"detected hotswap. PEMB"
<CheckDatax>	"hotswap. ALAR"

<GetData>

<Msg>		"Check log for Warnings"
<Sendslow>		"show log | grep -i warn"
<Wait>
<CheckDatax>	"SINGLE_BIT_ECC"
<CheckDatax>	"ECC"
<CheckDatax>	"CardAgt-CLOCK_ADJ"
<CheckDataX>	"WARN Fsync-CLEANUP_FAIL"
<GetData>
# Was in 121506 3.0 build removed in 010807 3.0 build, Intermittent
#<Bypass>	$HA_Session
#	<CheckData>	'WARN SysMgr-GO_ACTIVE: IMC in slot 1 has taken Active role'
#	<CheckData>	'WARN SysMgr-GO_ACTIVE: IMC in slot 0 has taken Active role'
#</Bypass>
#<CheckDatax>	"WARN"
#<CheckDatax>	"Warn"
<GetData>
<Msg>		"Check log for Critical"
<Sendslow>		"show log | grep -i RIT"
<Wait>
<CheckDatax>	"CRIT"
<GetData>


