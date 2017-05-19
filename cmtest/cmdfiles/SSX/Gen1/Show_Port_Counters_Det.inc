################################################################################
#
# Module:      Show Port CounterDet.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_POST_BI and Config
#
# Version:    2.1 $Id: Show_Port_Counters_Det.inc,v 1.2 2008/12/02 01:42:02 joe Exp $
#
# Changes:    Created 081308
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
<Msg>		"Check Port Counters..."
<Bypass>	$Slot_INST_1_GLC_GBL

### Slot 1 ###
#<Msg>		"Show Port Counters Slot 1 port 0"
<Send>		"show port 1/0 count det"
<Wait>
<GetData>	Port_Counter_Det

#<Msg>		"Show Port Counters Slot 1 port 1"
<Send>		"show port 1/1 count det"
<Wait>
<GetData>	Port_Counter_Det

#<Msg>		"Show Port Counters Slot 1 port 2"
<Send>		"show port 1/2 count det"
<Wait>
<GetData>	Port_Counter_Det

#<Msg>		"Show Port Counters Slot 1 port 3"
<Send>		"show port 1/3 count det"
<Wait>
<GetData>	Port_Counter_Det
</Bypass>

### Slot 2 ###
<Bypass>	$Slot_INST_2_GBL

#<Msg>		"Show Port Counters Slot 2 port 0"
<Send>		"show port 2/0 count det"
<Wait>
<GetData>	Port_Counter_Det

#<Msg>		"Show Port Counters Slot 2 port 1"
<Send>		"show port 2/1 count det"
<Wait>
<GetData>	Port_Counter_Det

#<Msg>		"Show Port Counters Slot 2 port 2"
<Send>		"show port 2/2 count det"
<Wait>
<GetData>	Port_Counter_Det

#<Msg>		"Show Port Counters Slot 2 port 3"
<Send>		"show port 2/3 count det"
<Wait>
<GetData>	Port_Counter_Det
</Bypass>

### Slot 3 ###
<Bypass>	$Slot_INST_3_GBL

#<Msg>		"Show Port Counters Slot 3 port 0"
<Send>		"show port 3/0 count det"
<Wait>
<GetData>	Port_Counter_Det

#<Msg>		"Show Port Counters Slot 3 port 1"
<Send>		"show port 3/1 count det"
<Wait>
<GetData>	Port_Counter_Det

#<Msg>		"Show Port Counters Slot 3 port 2"
<Send>		"show port 3/2 count det"
<Wait>
<GetData>	Port_Counter_Det

#<Msg>		"Show Port Counters Slot 3 port 3"
<Send>		"show port 3/3 count det"
<Wait>
<GetData>	Port_Counter_Det
</Bypass>

### Slot 4 ###
<Bypass>	$Slot_INST_4_GBL

#<Msg>		"Show Port Counters Slot 4 port 0"
<Send>		"show port 4/0 count det"
<Wait>
<GetData>	Port_Counter_Det

#<Msg>		"Show Port Counters Slot 4 port 1"
<Send>		"show port 4/1 count det"
<Wait>
<GetData>	Port_Counter_Det

#<Msg>		"Show Port Counters Slot 4 port 2"
<Send>		"show port 4/2 count det"
<Wait>
<GetData>	Port_Counter_Det

#<Msg>		"Show Port Counters Slot 4 port 3"
<Send>		"show port 4/3 count det"
<Wait>
<GetData>	Port_Counter_Det
</Bypass>







