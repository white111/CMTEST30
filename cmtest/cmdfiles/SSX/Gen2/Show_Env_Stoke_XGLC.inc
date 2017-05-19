################################################################################
#
# Module:      Show_ENV_Stoke_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Pre_BI,Post_BI.inc
#
# Version:    1.2   $Id: Show_Env_Stoke_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 11/18/11
#			  6/10/13 Prompt changes in 6.1R2 
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"[local]#"
<TimeOut>	5
<Send>		'terminal length infinite'
<Wait>
<Msg>		"Show Environmental"
<Send>		"show env"
#<Waitfor>   "Environmental"
<Wait>
<GetData>
<CheckData>	"Alarm summary"
<CheckData>	"No.*System-Wide Alarm triggered"
#<CheckData>	"ALARMM1.*No errors detected"
<CheckData>	"Voltage readings:"
<CheckData>	"Slot"
#		 Source				 Level"
<CheckData>	"0.*No errors detected"
<Bypass>	$Slot_INST_1_IMC_GBL
    <Bypass>    $Slot_SHOWENV_1_GBL
        <Msg>   "Check Slot 1"
        <CheckData> "1.*No errors detected"
    </Bypass>
</Bypass>
<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>    "Show Environmenta Slot 1 Bypassed Bug 14440"
</Bypass>
#<Bypass>    $Slot_INST_1_GBL
#    <Bypass>    $Slot_SHOWENV_1_GBL
#        <Msg>   "Check Slot 1"
#        <CheckData> "1.*No errors detected"
#    </Bypass>
#</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<Bypass>	$Slot_SHOWENV_2_GBL
		<CheckData>	"2.*No errors detected"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<Bypass>	$Slot_SHOWENV_3_GBL
		<CheckData>	"3.*No errors detected"
    </Bypass>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<Bypass>	$Slot_SHOWENV_4_GBL
		<CheckData>	"4.*No errors detected"
	</Bypass>
</Bypass>
<CheckData>	"Temperature readings:"

<CheckData>	"0.*No errors detected"
<Bypass>	$Slot_INST_1_GBL
	<Bypass>	$Slot_SHOWENV_1_GBL
		<CheckData>	"1.*No errors detected"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<Bypass>	$Slot_SHOWENV_2_GBL
		<CheckData>	"2.*No errors detected"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<Bypass>	$Slot_SHOWENV_3_GBL
		<CheckData>	"3.*No errors detected"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<Bypass>	$Slot_SHOWENV_4_GBL
		<CheckData>	"4.*No errors detected"
	</Bypass>
</Bypass>
<CheckData>	"Power status"
<CheckData>	"Slot.*Source.*Level"
<CheckData>	"PEMA.*No errors detected"
<CheckData>	"PEMB.*No errors detected"
<CheckData>	"Fan status:"
<CheckData>	"FANTRAY1.*No errors detected"
<CheckData>	"FANTRAY2.*No errors detected"

