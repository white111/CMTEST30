################################################################################
#
# Module:      Show_ENV_Stoke_BI.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI.inc
#
# Version:    1.2  $Id: Show_Env_Stoke_BI.inc,v 1.6 2010/03/12 18:50:59 joe Exp $
#
# Changes:    Added Bypass for 2port cards(no display)
#			  Created 12/8/05
#			  Bypassed slot 1 4.6 bug 14440
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
<TimeOut>	5
<Send>		'terminal length infinite'
<Wait>
<Msg>		"Show Environmental"
<Send>		"show env"
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
		<Msg>	"Check Slot 2"
		<CheckData>	"2.*No errors detected"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<Bypass>	$Slot_SHOWENV_3_GBL
		<Msg>	"Check Slot 3"
		<CheckData>	"3.*No errors detected"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<Bypass>	$Slot_SHOWENV_4_GBL
		<Msg>	"Check Slot 4"
		<CheckData>	"4.*No errors detected"
	</Bypass>
</Bypass>

# removed for due to system software bug
#<CheckData>	"Temperature readings:"

#<CheckData>	"0.*No errors detected"
#<Bypass>	$Slot_INST_1_GBL
#	<CheckData>	"1.*No errors detected"
#</Bypass>
#<Bypass>	$Slot_INST_2_GBL
#	<CheckData>	"2.*No errors detected"
#</Bypass>
#<Bypass>	$Slot_INST_3_GBL
#	<CheckData>	"3.*No errors detected"
#</Bypass>
#<Bypass>	$Slot_INST_4_GBL
#	<CheckData>	"4.*No errors detected"
#</Bypass>
<CheckData>	"Power status"
<CheckData>	"Slot.*Source.*Level"
<CheckData>	"PEMA.*No errors detected"
<CheckData>	"PEMB.*No errors detected"
<CheckData>	"Fan status:"
<CheckData>	"FANTRAY1.*No errors detected"
<CheckData>	"FANTRAY2.*No errors detected"
<CheckData>	"Alarm status:"
#Removed Temporay for BI - Triggers a minor alarm at 40degc tempurature
#Removed Major Alarm Creation Oven is at 42Deg C causing a Major Alarm
#Allowing a Minor alarm for now
#<CheckData>	"No.*System-Wide Alarm triggered"
#<CheckDataX>	"Major"
<CheckDataX>	"Critical"
# Not deiplayed in 3.0 <CheckData>	"ALARMM1.*No errors detected"



