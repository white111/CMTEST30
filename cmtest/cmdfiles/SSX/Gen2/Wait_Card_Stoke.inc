################################################################################
#
# Module:      Show_Card_Stoke.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Pre_BI,POST_BI and Config
#
# Version:    1.10 $Id: Wait_Card_Stoke.inc,v 1.1 2011/12/12 22:54:27 joe Exp $
#
# Changes:    Added <GetData>   12/05/05
#			  Modified for R1  010806
#			  Updated to select IMC or GLC in slot 1
#			  Updated to Make IMC in slot 0 always master
#			  Increased Wait time
#			  08/24/08 change to IPC Connection to CardMgr avaialble to wait for GLC
#			  Removed reset of IMC in SLot1
#			  Changed GLC wait message to Waiting for XLPs UP\.\.\.\.\.\.\.\.\. 8/8/12
#			  6/10/13 Prompt changes in 6.1R2/13.1
#			  Added Addtional wait time
#			  Added Support for XGLC in Slot 1 9/3/13
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


#<Bypass>    $Slot_INST_1_GLC_GBL
#            <Msg>   "Wait for GLC Slot 1 startup"
#            <SendSLow>  'echo -n Waiting;while  (  ( ! (grep -q "Waiting for XLPs UP\.\.\.\.\.\.\.\.\." /hdp/glc-console-1) && ((${mytime} > (`date -t`))) ) )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT) fi ; sleep 2; echo -n .) done; echo'
#            <wait>
#            <CheckDatax>    "TIMEOUT"
#            <GetData>
#</Bypass>
#<Bypass>    $Slot_INST_2_GBL
#            <Msg>   "Wait for GLC Slot 2 startup"
#            <SendSLow>  'echo -n Waiting;while  (  ( ! (grep -q "Waiting for XLPs UP\.\.\.\.\.\.\.\.\." /hdp/glc-console-2) && ((${mytime} > (`date -t`))) ) )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT) fi ; sleep 2; echo -n .) done; echo'
#            <wait>
#            <CheckDatax>    "TIMEOUT"
#            <GetData>
#</Bypass>
#<Bypass>    $Slot_INST_3_GBL
#            <Msg>   "Wait for GLC Slot 3 startup"
#            <SendSlow>  'echo -n Waiting;while  (  ( ! (grep -q "Waiting for XLPs UP\.\.\.\.\.\.\.\.\." /hdp/glc-console-3) && ((${mytime} > (`date -t`))) ) )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT) fi ; sleep 2; echo -n .) done; echo'
#            <wait>
#            <CheckDatax>    "TIMEOUT"
#            <GetData>
#</Bypass>
#<Bypass>    $Slot_INST_4_GBL
#            <Msg>   "Wait for GLC Slot 4 startup"
#            <SendSlow>  'echo -n Waiting;while  (  ( ! (grep -q "Waiting for XLPs UP\.\.\.\.\.\.\.\.\." /hdp/glc-console-4) && ((${mytime} > (`date -t`))) ) )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT) fi ; sleep 2; echo -n .) done; echo'
#            <wait>
#            <GetData>
#            <CheckDatax>    "TIMEOUT"
#</Bypass>
<Send>		'integer long mytimetotal=${mytime}-`date -t`'
<Wait>
#<Send>      'echo GLC remaining GLC startup time ${mytimetotal}'
#<Wait>
<GetData>
<Msg>		'echo Waiting 180 Seconds for Polling'
<Send>		'echo Waiting 180 Seconds for Polling'

<Wait>
<Sleep>		180


<Send>
<Wait>
<Timeout>	5
<Prompt>	"[local]#"
<Send>		"exit"
<Wait>

<Msg>		"Show Cards"
<Send>		"show card"
<Waitfor>	"Slot"
<Wait>
<GetData>


