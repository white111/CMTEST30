################################################################################
#
# Module:      show port FPD.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_POST_BI and Config
#
# Version:    1.2 $Id: Show_Port_Counters_Det.inc,v 1.2 2008/12/02 01:42:02 joe Exp $
#
# Changes:    Created 11/18/11
#			  1/15/13 Added addtional fast path checks
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"Stoke[local]#"
<Send>
<Wait>
<TimeOut>	10
<Send>		"terminal length infinite"
<Wait>
<Msg>		"Check FPD Port Counters..."
<Bypass>	$Slot_INST_1_GLC_GBL

### Slot 1 ###
#<Msg>		"show fpd driver Counters Slot 1 port 0"
<Send>		"show fpd driver slot 1"
<Wait>
<GetData>	Get_FPD
 <CheckDatax> "FCS Error"
<CheckDatax> "Tx MAC Error"
<CheckDatax> "Rx Bad Frame"
<Msg>		"show dos slot 1 counters"
<Send>		"show dos slot 1 counters"
<Wait>
<GetData> Get_DOS

</Bypass>

### Slot 2 ###
<Bypass>	$Slot_INST_2_GBL

<Msg>		"show fpd driver Counters Slot 2 "
<Send>		"show fpd driver slot 2"
<Wait>
<GetData> Get_FPD
<CheckDatax> "FCS Error"
<CheckDatax> "Tx MAC Error"
<CheckDatax> "Rx Bad Frame"

<Msg>		"show dos slot 2 counters"
<Send>		"show dos slot 2 counters"
<Wait>
<GetData> Get_DOS

</Bypass>

### Slot 3 ###
<Bypass>	$Slot_INST_3_GBL

<Msg>		"show fpd driver Counters Slot 3"
<Send>		"show fpd driver slot 3"
<Wait>
<GetData>	Get_FPD
<CheckDatax> "FCS Error"
<CheckDatax> "Tx MAC Error"
<CheckDatax> "Rx Bad Frame"

<Msg>		"show dos slot 3 counters"
<Send>		"show dos slot 3 counters"
<Wait>
<GetData> Get_DOS
</Bypass>

### Slot 4 ###
<Bypass>	$Slot_INST_4_GBL

<Msg>		"show fpd driver Counters Slot 4"
<Send>		"show fpd driver slot 4"
<Wait>
<GetData>	Get_FPD
<CheckDatax> "FCS Error"
<CheckDatax> "Tx MAC Error"
<CheckDatax> "Rx Bad Frame"

<Msg>		"show dos slot 4 counters"
<Send>		"show dos slot 4 counters"
<Wait>
<GetData> Get_DOS


</Bypass>


<Msg>		"show fast-path  counters"
<Send>		"show fast-path  counters  | grep -i "encap tag" "
<Wait>
<GetData>
<CheckDataX>	"Encap Tag Error"

<Msg>		"Check Log"
<Send>		"show log | grep -i _PATH_FAIL"
<Wait>
<GetData>
<CheckDataX>	"FAST"

<Msg>		"Check Log"
<Send>		"show log  | grep -i TAIL"
<Wait>
<GetData>
<CheckDataX>	"RED"

<Include>	Shell_imc.inc
<Msg>		"Check GLC Board Logs"
<Bypass>	$Slot_INST_1_GLC_GBL

### Slot 1 ###
<Msg>		"Check GLC Internal Board slot 1 Logs"
<Send>		" on -f /net/nv-1-0/ /stoke/bin/showlog"
<Wait>
<GetData>
 <iCheckDatax> "error"
<iCheckDatax> "_INTR"
<CheckDatax> "LONG_CALLBACK"

</Bypass>

### Slot 2 ###
<Bypass>	$Slot_INST_2_GBL

<Msg>		"Check GLC Internal Board slot 2 Logs"
<Send>		" on -f /net/nv-2-0/ /stoke/bin/showlog"
<Wait>
<GetData>
 <iCheckDatax> "error"
<iCheckDatax> "_INTR"
#<CheckDatax> "LONG_CALLBACK"

</Bypass>

### Slot 3 ###
<Bypass>	$Slot_INST_3_GBL

<Msg>		"Check GLC Internal Board slot 3 Logs"
<Send>		" on -f /net/nv-3-0/ /stoke/bin/showlog"
<Wait>
<GetData>
 <iCheckDatax> "error"
<iCheckDatax> "_INTR"
#<CheckDatax> "LONG_CALLBACK"
</Bypass>

### Slot 4 ###
<Bypass>	$Slot_INST_4_GBL
<Msg>		"Check GLC Internal Board slot 4 Logs"
<Send>		" on -f /net/nv-4-0/ /stoke/bin/showlog"
<Wait>
<GetData>
 <iCheckDatax> "error"
<iCheckDatax> "_INTR"
#<CheckDatax> "LONG_CALLBACK"


</Bypass>


<TimeOut>	10
<Prompt>	"Stoke[local]#"
<Send> "exit"
<Wait>










