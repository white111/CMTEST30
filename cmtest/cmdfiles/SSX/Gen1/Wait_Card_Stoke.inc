################################################################################
#
# Module:      Show_Card_Stoke.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Pre_BI,POST_BI and Config
#
# Version:    1.7 $Id: Wait_Card_Stoke.inc,v 1.7 2010/03/02 00:37:48 joe Exp $
#
# Changes:    Added <GetData>   12/05/05
#			  Modified for R1  010806
#			  Updated to select IMC or GLC in slot 1
#			  Updated to Make IMC in slot 0 always master
#			  Increased Wait time
#			  08/24/08 change to IPC Connection to CardMgr avaialble to wait for GLC
#			  Removed reset of IMC in SLot1
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
<TimeOut>	120
<Send>		"terminal length infinite"
<Wait>
<Msg>		"Show Cards"
<Send>		"show card"
<Waitfor>	"Slot"
<Wait>
<GetData>
<Include>	Shell_imc.inc
#		Timeout after 3 minutes of waiting for card
<send> 'integer long mytime=`date -t`+(60*3)'
<wait>
<GetData>
<TimeOut>	190
#cmd  wait for LCMgr message in glc log for x seconds, print timeout if not found in that time
#<Send>	'echo -n Waiting;while  (  ( ! (grep -q "LcMgr Started" /hdp/glc-console-1) && ((${mytime} > (`date -t`))) ) )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT) fi ; sleep 2; echo -n .) done; echo'

#<Bypass>	$Slot_INST_1_IMC_GBL
#Added to insure card in slot 0 starts as Master if a IMC is installed in slot 1
# The following is needed when IMCs move to a new chassis
# Ch Ser# is stroed in IMC NVRAM, if no match IMC slot 0   will start in standby
# We need the IMC in slot 0 to be master
#<Bypass>    $Slot_INST_1_IMC_GBL
#            <Send> "pfeffa on 1 reset bo"
#            <Wait>
#</Bypass>
<prompt>	"^#"
#</Bypass>
<Bypass>	$Slot_INST_1_GLC_GBL
            <Msg>	"Wait for GLC Slot 1 startup"
			<SendSlow>	'echo -n Waiting;while  (  ( ! (grep -q "IPC Connection to CardMgr available" /hdp/glc-console-1) && ((${mytime} > (`date -t`))) ) )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT) fi ; sleep 2; echo -n .) done; echo'
			<wait>
			<CheckDatax>	"TIMEOUT"
			<GetData>
</Bypass>
<Bypass>	$Slot_INST_2_GBL
            <Msg>	"Wait for GLC Slot 2 startup"
			<SendSLow>	'echo -n Waiting;while  (  ( ! (grep -q "IPC Connection to CardMgr available" /hdp/glc-console-2) && ((${mytime} > (`date -t`))) ) )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT) fi ; sleep 2; echo -n .) done; echo'
			<wait>
			<CheckDatax>	"TIMEOUT"
			<GetData>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
            <Msg>	"Wait for GLC Slot 3 startup"
			<SendSlow>	'echo -n Waiting;while  (  ( ! (grep -q "IPC Connection to CardMgr available" /hdp/glc-console-3) && ((${mytime} > (`date -t`))) ) )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT) fi ; sleep 2; echo -n .) done; echo'
			<wait>
			<CheckDatax>	"TIMEOUT"
			<GetData>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
            <Msg>	"Wait for GLC Slot 4 startup"
			<SendSlow>	'echo -n Waiting;while  (  ( ! (grep -q "IPC Connection to CardMgr available" /hdp/glc-console-4) && ((${mytime} > (`date -t`))) ) )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT) fi ; sleep 2; echo -n .) done; echo'
			<wait>
			<GetData>
			<CheckDatax>	"TIMEOUT"
</Bypass>
<Send>		'integer long mytimetotal=${mytime}-`date -t`'
<Wait>
<Send>		'echo GLC remaining GLC startup time ${mytimetotal}'
<Wait>
<GetData>
<Msg>		'echo Waiting 120 Seconds for Polling'
<Send>		'echo Waiting 120 Seconds for Polling'

<Wait>
<Sleep>		120


<Send>
<Wait>
<Timeout>	5
<Prompt>	"Stoke[local]#"
<Send>		"exit"
<Wait>


