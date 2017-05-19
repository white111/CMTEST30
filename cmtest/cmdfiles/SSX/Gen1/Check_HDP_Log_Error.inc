################################################################################
#
# Module:      Check_Log_Error.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_PRE_BI.dat, Chassis BI, Chassis_Post_BI.dat,Config.dat
#
# Version:    1.3 $Id: Check_HDP_Log_Error.inc,v 1.5 2010/03/12 18:50:59 joe Exp $
#
# Changes:    Created 10/17/06
#			  2/26/08 Added checks for Event log
#			  1/27/09 missing -e fixed im IMC slot 0
#			  Removed tiemout check for dual IMC cases 2/3/09
#			  Changes for 4.6 Bug 14440 3/3/10
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################


<TimeOut>	30
<Prompt>	"#"

<Msg>		"Check Console Logs"
<Sendslow>      "if (grep -in  -e "unhandled" -e "core dumped" /hdp/logs/event*	) then ( cat /hdp/logs/event*; echo "FAILED:$?") else (echo "EVENT_LOG_PASSED:$?")  fi"
#<Sendslow>      "if (grep -in  -e "unhandled" -e "timeout" -e "core dumped" /hdp/logs/event*	) then ( cat /hdp/logs/event*; echo "FAILED:$?") else (echo "EVENT_LOG_PASSED:$?")  fi"
#<Sendslow>      "if (grep -in -e "ERR" -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /hdp/logs/event*	) then ( cat /hdp/logs/event*; echo "FAILED:$?") else (echo "EVENT_LOG_PASSED:$?")  fi"
<Wait>
<CheckData>	"EVENT_LOG_PASSED"
<GetData>

<Msg>    "Check Console Logs Slot 1 bypassed bug 14440"
#<Bypass>    $Slot_INST_1_GLC_GBL
#    <Sendslow>      "if (grep -in -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /hdp/glc-console-1) then ( cat /hdp/glc-console-1; echo "FAILED:$?") else (echo "Slot_1_PASSED:$?")  fi"
#    <Wait>
#    <CheckData> "Slot_1_PASSED"
#    <GetData>
#</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Sendslow>      "if (grep -in -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /hdp/glc-console-2) then ( cat /hdp/glc-console-2; echo "FAILED:$?") else (echo "Slot_2_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_2_PASSED"
	<GetData>
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Sendslow>      "if (grep -in -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /hdp/glc-console-3) then ( cat /hdp/glc-console-3; echo "FAILED:$?") else (echo "Slot_3_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_3_PASSED"
	<GetData>
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Sendslow>      "if (grep -in -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /hdp/glc-console-4) then ( cat /hdp/glc-console-4; echo "FAILED:$?") else (echo "Slot_4_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_4_PASSED"
	<GetData>
</Bypass>
#    <Prompt>    ">"
#    #<Send>      'if (pidin | grep -i -e "pfeffa") then ( exit) else (pfeffa)  fi'
#    <send>      "exit"
#    <Wait>
<Msg>		"Check for Core Dumps"
<Sendslow>      "if (ls -als /hd/dump/slot0/*core.gz	) then ( echo "Slot 0 CORE DUMP CHK FAILED:$?") else (echo "Slot 0 CORE DUMP CHK PASSED:$?")  fi"
<Wait>
<CheckData>	"Slot 0 CORE DUMP CHK PASSED"
<GetData>
<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>    "Slot 0 CORE DUMP CHK Bypassed Bug 14440"
</Bypass>
<Bypass>	$Slot_INST_1_IMC_GBL
#<Bypass>	$Slot_INST_1_GBL
 			<Sendslow>      "if (ls -als /hd/dump/slot1/*core.gz	) then ( echo "Slot 1 CORE DUMP CHK FAILED:$?") else (echo "Slot 1 CORE DUMP CHK PASSED:$?")  fi"
			<Wait>
			<CheckData>	"Slot 1 CORE DUMP CHK PASSED"
			<GetData>
</Bypass>

<Bypass>	$Slot_INST_2_GBL
 			<Sendslow>      "if (ls -als /hd/dump/slot2/*core.gz	) then ( echo "Slot 2 CORE DUMP CHK FAILED:$?") else (echo "Slot 2 CORE DUMP CHK PASSED:$?")  fi"
			<Wait>
			<CheckData>	"Slot 2 CORE DUMP CHK PASSED"
			<GetData>
</Bypass>

<Bypass>	$Slot_INST_3_GBL
 			<Sendslow>      "if (ls -als /hd/dump/slot3/*core.gz	) then ( echo "Slot 3 CORE DUMP CHK FAILED:$?") else (echo "Slot 3 CORE DUMP CHK PASSED:$?")  fi"
			<Wait>
			<CheckData>	"Slot 3 CORE DUMP CHK PASSED"
			<GetData>
</Bypass>

<Bypass>	$Slot_INST_4_GBL
 			<Sendslow>      "if (ls -als /hd/dump/slot4/*core.gz	) then ( echo "Slot 4 CORE DUMP CHK FAILED:$?") else (echo "Slot 4 CORE DUMP CHK PASSED:$?")  fi"
			<Wait>
			<CheckData>	"Slot 4 CORE DUMP CHK PASSED"
			<GetData>
</Bypass>






