################################################################################
#
# Module:      Show_ENV_Stoke_BI.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI.inc
#
# Version:    1.8  $Id: Show_Env_Stoke_BI.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Added Bypass for 2port cards(no display)
#			  Created 12/8/05
#			  Bypassed slot 1 4.6 bug 14440
#			  Show alarm status changed to show alarm sum and moved to top
#			  Added show env det
#			  Removed IMC slot 1 Check  03/19/12 Getting Minor alarm, likly from XGLC above in BI. 39 DegC inlet 50DegC outlet
#		      Corrected Check to under tempurture readings 8/9/12
#			  Prompt changes for 6.1/13.1
#			  Updates for Creation Chamber at 44C 11/22/13
#
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
<Wait>
<GetData>
<CheckData>	"Alarm summary"
#Removed Temporay for BI - Triggers a minor alarm at 40degc tempurature
#Removed Major Alarm Creation Oven is at 42Deg C causing a Major Alarm
#Allowing a Minor alarm for now
#<CheckData>	"No.*System-Wide Alarm triggered"
#<CheckDataX>	"Major"
<CheckDataX>	"Critical"

<Msg>		"Check Voltages"
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
<Msg>		"Check Temperature"
<CheckData>    "Temperature readings:"

#<CheckData>    "0.*No errors detected"
<CheckDatax> "0.*Crit"
<Bypass>   $Slot_INST_1_GBL
       <Msg>   "Check Slot 1"
        # 03/19/12 Getting Minor alarm, likly from XGLC above in BI. 39 DegC inlet 50DegC outlet
        #<CheckData> "1.*No errors detected"
        #<CheckDatax> "1.*Major"
        <CheckDatax> "1.*Crit"
    </Bypass>
</Bypass>
<Bypass>   $Slot_INST_2_GBL
	<Msg>   "Check Slot 2"
   #<CheckData> "2.*No errors detected"
   <CheckDatax> "2.*Crit"
</Bypass>
<Bypass>   $Slot_INST_3_GBL
	<Msg>   "Check Slot 3"
   #<CheckData> "3.*No errors detected"
   <CheckDatax> "3.*Crit"
</Bypass>
<Bypass>   $Slot_INST_4_GBL
	<Msg>   "Check Slot 3"
   #<CheckData> "4.*No errors detected"
   <CheckDatax> "4.*Crit"
</Bypass>
<CheckData>	"Power status"
<CheckData>	"Slot.*Source.*Level"
<CheckData>	"PEMA.*No errors detected"
<CheckData>	"PEMB.*No errors detected"
<CheckData>	"Fan status:"
<CheckData>	"FANTRAY1.*No errors detected"
<CheckData>	"FANTRAY2.*No errors detected"

<TimeOut>	30
<Msg>		"Show Environmental Detail"
<Send>		"show env det"
<Wait>
<GetData>


