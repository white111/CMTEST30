################################################################################
#
# Module:      BI_loopbacktest.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI.dat
#
# Version:    1.7    $Id: BI_loopbacktest.inc,v 1.5 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Added <GetData> 12/05/05
#			  Changed traffic command to "start/Stop Fabric from "gen2 cont"  02/21/06
#			  Changed to log to HD by slot then grep result for errors only  03/30/06
#			  Added ixtest errors
#			  Fixed $Slot_CARD_TYPE_INST_0_GBL naming  10/09/06
#			  Added Slot Selection 10/09/06
#			  Updates for new diags
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
#
# Version 5a1	11/12/05
#
<Msg>		"Starting Pfeffa, Test Timed All packets looped back..."

#Pfeffa may be slow starting due to background testing of memory
<Timeout>	90
#<Prompt>   "> "
<Prompt>   "#"
#<Send>     "pfeffa"
#<Wait>
<Timeout>	500
<sleep>		10
#<Send>      set verb 1
#<Wait>

#<Msg>       "Setup Fabric for Snake to all slots"
##<Send>     "set fab sna 14222"
#<SendChr>       "set fab sna "
#<SendChr>       $Slot_CARD_TYPE_INST_0_GBL
#<SendChr>       $Slot_CARD_TYPE_INST_1_GBL
#<SendChr>       $Slot_CARD_TYPE_INST_2_GBL
#<SendChr>       $Slot_CARD_TYPE_INST_3_GBL
#<SendChr>       $Slot_CARD_TYPE_INST_4_GBL
#<Send>
#<Wait>
#<GetData>


# for reference - old method
#<Timeout>   120
#<Prompt>    ">"
#<Msg>       "Setup Fabric"
#<Send>      "pfeffa"
#<Wait>

#<Bypass>    $Slot_INST_1_GBL
#    <Msg>       "Setup Fabric for Snake test MC to Slot 1"
#    #<Send>     "set fab sna 12000"
#    <SendChr>       "set fab sna "
#    <SendChr>       $Slot_CARD_TYPE_INST_0_GBL
#    <SendChr>       $Slot_CARD_TYPE_INST_1_GBL
#    <SendChr>       "0"
#    <SendChr>       "0"
#    <SendChr>       "0"
#    <Send>
#    <Wait>
#    <GetData>
#    <Sleep>     3
#    <Msg>       "Send Packets for 20 seconds"
#    <Send>      "test fabric as-is"
#    <Wait>
#    <GetData>
#    <CheckData> "PASS"
#</Bypass>


<Msg>       $internal_traffic_test_time_msg_GBL
#<Send>     "start fabric"
#<Wait>
#<GetData>
#<Sleep>        $internal_traffic_test_time_GBL
#<Send>      "stop fabric"
#<Wait>
<Timeout>     $internal_traffic_test_timeout_GBL
<Sendchr>   "time pfeffa test snaketime  "
<sendchr>   $internal_traffic_test_time_GBL
<send>
<wait>
<GetData>
<CheckData>	"Test Status:"
<Bypass>	$Slot_INST_4_GBL
	<CheckData>	"Slot 4: PASSED"
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<CheckData>	"Slot 3: PASSED"
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<CheckData>	"Slot 2: PASSED"
</Bypass>
<Bypass>	$Slot_INST_1_GBL
	<CheckData>	"Slot 1: PASSED"
</Bypass>

<CheckData>	"Slot 0: PASSED"



<Timeout>   30
<send>
<wait>

<Include>	Check_BI_loopbacktest.inc
<Send>
<Wait>


