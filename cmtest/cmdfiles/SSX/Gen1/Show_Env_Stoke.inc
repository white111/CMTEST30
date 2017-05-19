################################################################################
#
# Module:      Show_ENV_Stoke.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Pre_BI,Post_BI.inc
#
# Version:    1.4   $Id: Show_Env_Stoke.inc,v 1.7 2010/03/12 18:50:59 joe Exp $
#
# Changes:    Added Bypass for 2port cards(no display)
#			  Added <GetData>  12/05/05
#			  Prob @ 9600 Baud - Modified Waitfor ater show env
#             Bypassed slot 1 4.6 bug 14440
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"Stoke[local]#"
<TimeOut>	5
<Send>		'terminal length infinite'
<Wait>
<Msg>		"Show Environmental"
<Send>		"show env"
#<Waitfor>   "Environmental"
<Wait>
<GetData>
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
<CheckData>	"Alarm status:"
<CheckData>	"No.*System-Wide Alarm triggered"
<CheckData>	"ALARMM1.*No errors detected"


