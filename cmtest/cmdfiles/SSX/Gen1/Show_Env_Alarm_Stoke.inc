 ################################################################################
#
# Module:      Show_Env_Alarm_Stoke.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Post_BI.dat,Config.dat
#
# Version:    1.7  $Id: Show_Env_Alarm_Stoke.inc,v 1.12 2011/01/21 18:38:55 joe Exp $
#
# Changes:    Added <GetData>  12/05/05
#			  Updated for Changes in 2.0B1 030206
#			  Fix for Command timeouts 8/31/06
#			  Updated for 4.0 changes
#			  Updates for 4.3 Changes ( ALarms with breaker off) 1/13/08
#			  Fix change show env timeout to 10 sec, ocasional failures
#			  Added Check for board and Fans 1/14/11
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

<Include>	Shell_imc.inc
<Msg>		'Check F4000029   00, PEM 1(RIGHT) off PEM 2(Left) on'
<Send>		"pfeffa r8 F4000029"
<wait>
<CheckData>	"F4000029   00"
<Prompt>	"Stoke[local]#"
<send>		"exit"
<wait>

<Alert>		"Power off PEM 1, Right Side of Chassis"
<Msg>		"Waiting 60 Seconds for Alarm"
<Sleep>		65
<TimeOut>	10
<Msg>		"Check PEM1 and Alarm Status"
<Msg>		"Show Environmental"
<Send>		"show env"
<Wait>
<GetData>
<CheckData>	"Voltage readings:"
<CheckData>	"Slot"
#		 Source				 Level"
<CheckData>	"Power status"
<CheckData>	"Slot.*Source.*Level"
#<CheckData>	"PEMA.*No errors detected"
#<CheckData>	"PEMA.*-48V Powergood.*Major"
<CheckData>	"PEMA.*Power Trip.*Minor"
<CheckData>	"PEMB.*No errors detected"
<CheckData> "FANTRAY1.*No errors detected"
<CheckData> "FANTRAY2.*No errors detected"
<CheckData>	"Alarm status:"
#<CheckData>	"No.*System-Wide Alarm triggered"
#<CheckData>	"Major.*System-Wide Alarm triggered by.*PEM -48V Powergood"
<CheckData>	"Minor.*System-Wide Alarm triggered by.*PEM Trip.*event"
<Send>		"show card"
<Waitfor>	"Slot"
<Wait>
<GetData>

<CheckData>	    "0 IMC.*Running.*Stoke IMC"
<Bypass>	$Slot_INST_1_IMC_GBL
	<CheckData>	    "1 IMC.*Running.*Stoke IMC"
</Bypass>
<Bypass>	$Slot_INST_1_GLC_GBL
	<CheckData>	    "1 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<CheckData>	    "2 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<CheckData>	    "3 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<CheckData>	    "4 GLC.*Running.*1000Base-X"
</Bypass>

# Not displayed in 3.0 <CheckData>	"ALARMM1.*No errors detected"

<Include>	Shell_imc.inc
<Msg>		'Check F4000029   04, PEM 1(RIGHT) off PEM 2(Left) on'
<Send>		"pfeffa r8 F4000029"
<wait>
<CheckData>	"F4000029   04"
<Prompt>	"Stoke[local]#"
<send>		"exit"
<wait>


<Alert>		"Power on PEM 1, Right Side of Chassis, Press Alarm ACO button"
<Msg>		"Waiting 60 Seconds for Alarm to clear"
<Sleep>		65
<TimeOut>	10
<Msg>		"Show Environmental"
<Send>		"show env"
<Wait>
<GetData>
<Msg>		"Check PEM1 and Alarm Status"
<Msg>		"Check for Alarm cleared"
<CheckData>	"Voltage readings:"
<CheckData>	"Slot"
#		 Source				 Level"

<CheckData>	"Power status"
<CheckData>	"Slot.*Source.*Level"
<CheckData>	"PEMA.*No errors detected"
<CheckData>	"PEMB.*No errors detected"
<CheckData>	"Fan status:"
<CheckData> "FANTRAY1.*No errors detected"
<CheckData> "FANTRAY2.*No errors detected"
<CheckData>	"Alarm status:"
#<CheckData>	"Minor.*System-Wide Alarm triggered by.*ALARMM Alarm Cut. event"
#<CheckData>	"ALARMM1.*Alarm Cutfoff.*On"
<Send>		"show card"
<Waitfor>	"Slot"
<Wait>
<GetData>

<CheckData>	    "0 IMC.*Running.*Stoke IMC"
<Bypass>	$Slot_INST_1_IMC_GBL
	<CheckData>	    "1 IMC.*Running.*Stoke IMC"
</Bypass>
<Bypass>	$Slot_INST_1_GLC_GBL
	<CheckData>	    "1 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<CheckData>	    "2 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<CheckData>	    "3 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<CheckData>	    "4 GLC.*Running.*1000Base-X"
</Bypass>
<Send>		"clear env alarm"
<Wait>
<Include>	Shell_imc.inc
<Msg>		'Check F4000029   00, PEM 1(RIGHT) on PEM 2(Left) on'
<Send>		"pfeffa r8 F4000029"
<wait>
<CheckData>	"F4000029   00"
<Prompt>	"Stoke[local]#"
<send>		"exit"
<wait>

<Alert>		"Power off PEM 2, Left Side of Chassis"
<Msg>		"Waiting 60 Seconds for Alarm"
<Sleep>		65
<TimeOut>	10
<Msg>		"Show Environmental"
<Send>		"show env"
<Wait>
<GetData>
<Msg>		"Check PEM2 and Alarm Status"
<CheckData>	"Voltage readings:"
<CheckData>	"Slot"
#		 Source				 Level"
<CheckData>	"Power status"
<CheckData>	"Slot.*Source.*Level"
<CheckData>	"PEMA.*No errors detected"
<CheckData>	"PEMB.*Power Trip.*Minor"
#<CheckData>	"PEMB.*No errors detected"
#<CheckData>	"PEMB.*-48V Powergood.*Major"
<CheckData> "FANTRAY1.*No errors detected"
<CheckData> "FANTRAY2.*No errors detected"
<CheckData>	"Alarm status:"
#<CheckData>	"No.*System-Wide Alarm triggered"
#<CheckData>	"Major.*System-Wide Alarm triggered by.*PEM -48V Powergood"
<CheckData>	"Minor.*System-Wide Alarm triggered by.*PEM Trip.*event"
<CheckData>	"ALARMM1.*No errors detected"
<Send>		"show card"
<Waitfor>	"Slot"
<Wait>
<GetData>

<CheckData>	    "0 IMC.*Running.*Stoke IMC"
<Bypass>	$Slot_INST_1_IMC_GBL
	<CheckData>	    "1 IMC.*Running.*Stoke IMC"
</Bypass>
<Bypass>	$Slot_INST_1_GLC_GBL
	<CheckData>	    "1 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<CheckData>	    "2 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<CheckData>	    "3 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<CheckData>	    "4 GLC.*Running.*1000Base-X"
</Bypass>

<Include>	Shell_imc.inc
<Msg>		'Check F4000029   08, PEM 1(RIGHT) on PEM 2(Left) off'
<Send>		"pfeffa r8 F4000029"
<wait>
<CheckData>	"F4000029   08"
<Prompt>	"Stoke[local]#"
<send>		"exit"
<wait>

<Alert>		"Power on PEM 2, Left Side of Chassis, Press Alarm ACO button"
<Msg>		"Waiting 60 Seconds for Alarm to clear"
<Sleep>		65
<TimeOut>	10
<Msg>		"Show Environmental"
<Send>		"show env"
<Wait>
<GetData>
<Msg>		"Check PEM1 and Alarm Status"
<Msg>		"Check for Alarm cleared"
<CheckData>	"Voltage readings:"
<CheckData>	"Slot"
#		 Source				 Level"

<CheckData>	"Power status"
<CheckData>	"Slot.*Source.*Level"
<CheckData>	"PEMA.*No errors detected"
<CheckData>	"PEMB.*No errors detected"
<CheckData>	"Fan status:"
<CheckData> "FANTRAY1.*No errors detected"
<CheckData> "FANTRAY2.*No errors detected"
<CheckData>	"Alarm status:"
#<CheckData>	"Minor.*System-Wide Alarm triggered by.*ALARMM Alarm Cut. event"
#<CheckData>	"ALARMM1.*Alarm Cutfoff.*On"
<Send>		"show card"
<Waitfor>	"Slot"
<Wait>
<GetData>

<CheckData>	    "0 IMC.*Running.*Stoke IMC"
<Bypass>	$Slot_INST_1_IMC_GBL
	<CheckData>	    "1 IMC.*Running.*Stoke IMC"
</Bypass>
<Bypass>	$Slot_INST_1_GLC_GBL
	<CheckData>	    "1 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<CheckData>	    "2 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<CheckData>	    "3 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<CheckData>	    "4 GLC.*Running.*1000Base-X"
</Bypass>

<Send>		"clear env alarm"
<Wait>
<Include>	Shell_imc.inc
<Msg>		'Check F4000029   00, PEM 1(RIGHT) on PEM 2(Left) on'
<Send>		"pfeffa r8 F4000029"
<wait>
<CheckData>	"F4000029   00"
<Prompt>   "Stoke[local]#"
<send>     "exit"
<wait>
<Msg>		"Shutting down system..."
<Timeout>	60
<Prompt>	"Proceed"
<Send>		"reload"
<wait>
<Prompt>    "Initializing Network Hardware..."
<Send>		"y"
<sleep>		1
<Send>		"y"
<Wait>
<Prompt>	"Stoke>>"

<Msg>		"Stopping Stoke bootup.."

<SendChr>		uboot
# For backward compatability to 2.0R2 Only need to keep this until the next release
<Sleep>		1
<SendChr>		"stoke"
<Wait>
<Msg>		"Verify at Stoke>>.."
<TimeOut>	1
<Send>		""
<WaitFor>	"Stoke>>"

<Prompt>	">"
<TimeOut>	5
<Msg>		"Starting Noodle..."
<Send>		"go ffe00100"
<Wait>
<sleep>		1
<Send>
<Wait>
<Msg>		"Trigger breakers, Both pems should be powered off"
#<Include>	Shell_imc.inc
#<Send>		"pfeffa w8 f4000042 1"
<Send>		"w8 f4000042 1"
<Sleep> 	1
#<Prompt>	"."
<Send>
#<wait>
<Msg>		"Check system is powered off"
<GetData>
<CheckDataX>	">"






