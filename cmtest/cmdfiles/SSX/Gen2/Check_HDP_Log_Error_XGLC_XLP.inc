################################################################################
#
# Module:      Check_Log_Error_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_PRE_BI.dat, Chassis BI, Chassis_Post_BI.dat,Config.dat
#
# Version:    1.7 $Id: Check_HDP_Log_Error_XGLC_XLP.inc,v 1.1 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 11/18/11
#			  Added Checks for XLP consols and screen for non errors, corrected 3/1/12.
#			  Added -e "Error.*NOP"
#			  07/09/12 Added -e "MBist. Fail"    , -e "PCIE..B0:D1:F1..link failed" , -e "Error..Unable to detect SGMII"
#			  Added Support for XGLC in Slot 1 9/3/13
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2012 Stoke. All rights reserved.
#
################################################################################


<TimeOut>	60
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
	<Sendslow>      "grep -inv -e "nak" -e "failed .No error" -e "IMC 1 failed .Host is down" -e "IMC 1 failed .Bad file descriptor"  /hdp/glc-console-1 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /tmp/greptmp.txt) then (  echo "Slot_1_FAILED:$?") else (echo "Slot_1_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_1_PASSED"
	<GetData>
	#XLP0
    # filter non errors
	<Sendslow>      "grep -inv -e "nak" -e "failed .No error"  -e "FDT_ERR_NOTFOUND" -e "xlpmon: Error in writing" -e "Error.*NOP" -e "MBist. Fail" -e "PCIE..B0:D1:F1..link failed" -e "Error..Unable to detect SGMII" /hdp/glc-console-fu0-1 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "error" -e "unhandled" -e "timeout" -e "dumped" -e "timed out" /tmp/greptmp.txt) then (  echo "Slot1_XLP0_FAILED:$?") else (echo "Slot_1_XLP0_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_1_XLP0_PASSED"
	<GetData>
	#XLP1
    # filter non errors
	<Sendslow>      "grep -inv -e "nak" -e "failed .No error"  -e "FDT_ERR_NOTFOUND" -e "xlpmon: Error in writing" -e "Error.*NOP" -e "MBist. Fail" -e "PCIE..B0:D1:F1..link failed" -e "Error..Unable to detect SGMII" /hdp/glc-console-fu1-1 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "error" -e "unhandled" -e "timeout" -e "dumped" -e "timed out" /tmp/greptmp.txt) then ( echo "Slot1_XLP1_FAILED:$?") else (echo "Slot_1_XLP1_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_1_XLP1_PASSED"
	<GetData>

</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>		"Check Console Logs Slot 2"
     # filter non errors
	<Sendslow>      "grep -inv -e "nak" -e "failed .No error" -e "IMC 1 failed .Host is down" -e "IMC 1 failed .Bad file descriptor"  /hdp/glc-console-2 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /tmp/greptmp.txt) then (  echo "Slot_2_FAILED:$?") else (echo "Slot_2_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_2_PASSED"
	<GetData>
	#XLP0
    # filter non errors
	<Sendslow>      "grep -inv -e "nak" -e "failed .No error"  -e "FDT_ERR_NOTFOUND" -e "xlpmon: Error in writing" -e "Error.*NOP" -e "MBist. Fail" -e "PCIE..B0:D1:F1..link failed" -e "Error..Unable to detect SGMII" /hdp/glc-console-fu0-2 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "error" -e "unhandled" -e "timeout" -e "dumped" -e "timed out" /tmp/greptmp.txt) then (  echo "Slot2_XLP0_FAILED:$?") else (echo "Slot_2_XLP0_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_2_XLP0_PASSED"
	<GetData>
	#XLP1
    # filter non errors
	<Sendslow>      "grep -inv -e "nak" -e "failed .No error"  -e "FDT_ERR_NOTFOUND" -e "xlpmon: Error in writing" -e "Error.*NOP" -e "MBist. Fail" -e "PCIE..B0:D1:F1..link failed" -e "Error..Unable to detect SGMII" /hdp/glc-console-fu1-2 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "error" -e "unhandled" -e "timeout" -e "dumped" -e "timed out" /tmp/greptmp.txt) then ( echo "Slot2_XLP1_FAILED:$?") else (echo "Slot_2_XLP1_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_2_XLP1_PASSED"
	<GetData>

</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>		"Check Console Logs Slot 3"
    # filter non errors
	<Sendslow>      "grep -inv -e "nak" -e "failed .No error" -e "IMC 1 failed .Host is down" -e "IMC 1 failed .Bad file descriptor" /hdp/glc-console-3 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /tmp/greptmp.txt) then ( echo "FAILED:$?") else (echo "Slot_3_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_3_PASSED"
	<GetData>
	#XLP0
    # filter non errors
	<Sendslow>      "grep -inv -e "nak" -e "failed .No error"  -e "FDT_ERR_NOTFOUND" -e "xlpmon: Error in writing" -e "Error.*NOP" -e "MBist. Fail" -e "PCIE..B0:D1:F1..link failed" -e "Error..Unable to detect SGMII" /hdp/glc-console-fu0-3 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "error" -e "unhandled" -e "timeout" -e "dumped" -e "timed out" /tmp/greptmp.txt) then (  echo "Slot3_XLP0_FAILED:$?") else (echo "Slot_3_XLP0_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_3_XLP0_PASSED"
	<GetData>
	#XLP1
    # filter non errors
	<Sendslow>      "grep -inv -e "nak" -e "failed .No error" -e "FDT_ERR_NOTFOUND" -e "xlpmon: Error in writing" -e "Error.*NOP" -e "MBist. Fail" -e "PCIE..B0:D1:F1..link failed" -e "Error..Unable to detect SGMII" /hdp/glc-console-fu1-3 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "error" -e "unhandled" -e "timeout" -e "dumped" -e "timed out" /tmp/greptmp.txt) then (  echo "Slot3_XLP1_FAILED:$?") else (echo "Slot_3_XLP1_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_3_XLP1_PASSED"
	<GetData>
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>		"Check Console Logs Slot 4"
     # filter non errors
	<Sendslow>      "grep -inv -e "nak" -e "failed .No error" -e "IMC 1 failed .Host is down" -e "IMC 1 failed .Bad file descriptor" /hdp/glc-console-4 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "unhandled" -e "timeout" -e "core dumped" /tmp/greptmp.txt) then (echo "FAILED:$?") else (echo "Slot_4_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_4_PASSED"
	<GetData>
	#XLP0
    # filter non errors
	<Sendslow>      "grep -inv -e "nak" -e "failed .No error" -e "FDT_ERR_NOTFOUND" -e "xlpmon: Error in writing" -e "Error.*NOP" -e "MBist. Fail" -e "PCIE..B0:D1:F1..link failed" -e "Error..Unable to detect SGMII" /hdp/glc-console-fu0-4 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "error" -e "unhandled" -e "timeout" -e "dumped" -e "timed out" /tmp/greptmp.txt) then (  echo "Slot4_XLP0_FAILED:$?") else (echo "Slot_4_XLP0_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_4_XLP0_PASSED"
	<GetData>
	#XLP1
    # filter non errors
	<Sendslow>      "grep -inv -e "nak" -e "failed .No error" -e "FDT_ERR_NOTFOUND" -e "xlpmon: Error in writing" -e "Error.*NOP" -e "MBist. Fail" -e "PCIE..B0:D1:F1..link failed" -e "Error..Unable to detect SGMII" /hdp/glc-console-fu1-4 > /tmp/greptmp.txt"
	<Wait>
	<Sendslow>      "if (grep -in -e "fail" -e "error" -e "unhandled" -e "timeout" -e "dumped" -e "timed out" /tmp/greptmp.txt) then (  echo "Slot4_XLP1_FAILED:$?") else (echo "Slot_4_XLP1_PASSED:$?")  fi"
	<Wait>
	<CheckData>	"Slot_4_XLP1_PASSED"
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






