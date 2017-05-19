################################################################################
#
# Module:      show port FPD.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_POST_BI and Config
#
# Version:    1.2 $Id: Show_Port_FPD.inc,v 1.1 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 11/18/11
#			  6/10/13 Prompt changes in 6.1R2 
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
<Prompt>	"[local]#"
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











