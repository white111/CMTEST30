################################################################################
#
# Module:      Check_Log_Error_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_PRE_BI.dat, Chassis BI, Chassis_Post_BI.dat,Config.dat
#
# Version:    1.5 $Id: Check_HDP_Log_Error_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 11/18/11
#			  Added Checks for XLP consols and screen for non errors
#			  Added Support for XGLC in Slot 1 9/3/13
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2013 Stoke. All rights reserved.
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


 <Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>		"Check Console Logs Slot 1"
     # filter non errors
	<Sendslow>      "grep -inv -e "failed.NAK." -e "failed .No error" -e "IMC 1 failed .Host is down" -e "IMC 1 failed .Bad file descriptor" /hdp/glc-console-1 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /tmp/greptmp.txt) then (  echo "Slot_1_FAILED:$?") else (echo "Slot_1_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_1_PASSED"
	<GetData>
 </Bypass>

  <Bypass>	$Slot_INST_2_GBL
	<Msg>		"Check Console Logs Slot 2"
     # filter non errors
	<Sendslow>      "grep -inv -e "failed.NAK." -e "failed .No error" -e "IMC 1 failed .Host is down" -e "IMC 1 failed .Bad file descriptor" /hdp/glc-console-2 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /tmp/greptmp.txt) then (  echo "Slot_2_FAILED:$?") else (echo "Slot_2_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_2_PASSED"
	<GetData>
 </Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>		"Check Console Logs Slot 3"
    # filter non errors
	<Sendslow>      "grep -inv -e "failed.NAK." -e "failed .No error" -e "IMC 1 failed .Host is down" -e "IMC 1 failed .Bad file descriptor" /hdp/glc-console-3 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /tmp/greptmp.txt) then ( echo "FAILED:$?") else (echo "Slot_3_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_3_PASSED"
	<GetData>
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>		"Check Console Logs Slot 4"
     # filter non errors
	<Sendslow>      "grep -inv -e "failed.NAK." -e "failed .No error" -e "IMC 1 failed .Host is down" -e "IMC 1 failed .Bad file descriptor" /hdp/glc-console-4 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /tmp/greptmp.txt) then (  echo "FAILED:$?") else (echo "Slot_4_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_4_PASSED"
	<GetData>
</Bypass>
#    <Prompt>    ">"
#    #<Send>      'if (pidin | grep -i -e "pfeffa") then ( exit) else (pfeffa)  fi'
#    <send>      "exit"
#    <Wait>
<Msg>		"Check for Core Dumps"
<Sendslow>      "if (ls -als /hd/dump/slot0/*core.gz ) then ( echo "Slot 0 CORE DUMP CHK FAILED:$?") else (echo "Slot 0 CORE DUMP CHK PASSED:$?")  fi"
<Wait>
<CheckData>	"Slot 0 CORE DUMP CHK PASSED"
<GetData>
<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>    "Slot 0 CORE DUMP CHK Bypassed Bug 14440"
</Bypass>
<Bypass>	$Slot_INST_1_IMC_GBL
#<Bypass>	$Slot_INST_1_GBL
 			<Sendslow>      "if (ls -als /hd/dump/slot1/*core.gz ) then ( echo "Slot 1 CORE DUMP CHK FAILED:$?") else (echo "Slot 1 CORE DUMP CHK PASSED:$?")  fi"
			<Wait>
			<CheckData>	"Slot 1 CORE DUMP CHK PASSED"
			<GetData>
</Bypass>

<Bypass>	$Slot_INST_2_GBL
 			<Sendslow>      "if (ls -als /hd/dump/slot2/*core.gz ) then ( echo "Slot 2 CORE DUMP CHK FAILED:$?") else (echo "Slot 2 CORE DUMP CHK PASSED:$?")  fi"
			<Wait>
			<CheckData>	"Slot 2 CORE DUMP CHK PASSED"
			<GetData>
</Bypass>

<Bypass>	$Slot_INST_3_GBL
 			<Sendslow>      "if (ls -als /hd/dump/slot3/*core.gz ) then ( echo "Slot 3 CORE DUMP CHK FAILED:$?") else (echo "Slot 3 CORE DUMP CHK PASSED:$?")  fi"
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






