################################################################################
#
# Module:      check_fabric_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Main Execution for IMC Bench test
#
# Version:    1.2 $Id: check_fabric_XGLC.inc,v 1.1 2011/12/12 22:54:27 joe Exp $
#
# Changes:    Created 12/1/11
#			  Updated for 13.1 based diags 7/25/14
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
#
# Version 5a1	10/02/05 JSW
#
<Msg>		"Checking Backplane fabric"
<Prompt>	"#"
<Timeout>	95
<Msg>		"Start Fabric Slot 0"
#<Send>		"fabd"
#<Wait>
#<GetData>

<Bypass>	$Slot_INST_1_GLC_GBL
     <Msg>   "Wait for Slot 1"
    <Send>  'waitfor /net/nv-1-0/stoke/bin/diag/*[Dd]iag* 100'
    <Wait>
    <CheckDatax> "Unable to access"
</Bypass>

<Bypass>    $Slot_INST_2_GBL
    <Msg>   "Wait for Slot 2"
    <Send>  'waitfor /net/nv-2-0/stoke/bin/diag/*[Dd]iag* 100'
    <Wait>
    <CheckDatax> "Unable to access"
</Bypass>

<Bypass>    $Slot_INST_3_GBL
    <Msg>   "Wait for Slot 3"
    <Send>  'waitfor /net/nv-3-0/stoke/bin/diag/*[Dd]iag* 100'
    <Wait>
    <CheckDatax> "Unable to access"
</Bypass>

<Bypass>    $Slot_INST_4_GBL
    <Msg>   "Wait for Slot 4"
    <Send>  'waitfor /net/nv-4-0/stoke/bin/diag/*[Dd]iag* 100'
    <Wait>
    <CheckDatax> "Unable to access"
</Bypass>

<Sleep> 5
<TimeOut>	30
<Msg>	"Check Base Channel to Slot 0 to All Slots"
<Msg>		"Start Fabric Slot 0"
<Sendslow>		"fabd -l"
<Wait>
<GetData>
<CheckData>	"Ports with link up on Base Switch."
<CheckData>	"Port  0 : Link UP, adjacency: Disco"


<Bypass>	$Slot_INST_0_1_GBL
<Msg>		"Check Base Switch to Slot 0 to 1"
	<CheckData>	"Port  6 : Link UP, adjacency: Slot 1"
</Bypass>
<Bypass>	$Slot_INST_0_2_GBL
<Msg>		"Check Base Switch to Slot 0 to 2"
	<CheckData>	"Port  8 : Link UP, adjacency: Slot 2"
</Bypass>
<Bypass>	$Slot_INST_0_3_GBL
<Msg>		"Check Base Switch to Slot 0 to 3"
	<CheckData>	"Port  9 : Link UP, adjacency: Slot 3"
</Bypass>
<Bypass>	$Slot_INST_0_4_GBL
<Msg>		"Check Base Channel to Slot 0 to 4"
	<CheckData>	"Port 11 : Link UP, adjacency: Slot 4"
</Bypass>




<Msg>	"Check Base Channel to Slot 0 to All Slots"
<Send>		"fabd -l"
<Wait>
<GetData>
<CheckData>	"Ports with link up on Fabric Switch.SW5."
<CheckData>	"Port  0 : Link UP, adjacency: Disco"
<Bypass>	$Slot_INST_0_4_GBL
	<Msg>	"Check Fabric Switch(SW5) 0 to 4"
	<CheckData>	"Port  3 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  4 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  5 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  6 : Link UP, adjacency: Slot 4"
</Bypass>

<Bypass>	$Slot_INST_0_3_GBL
	<Msg>	"Check Fabric Switch(SW5) 0 to 3"
	<CheckData>	"Port  7 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port  8 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port  9 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port 10 : Link UP, adjacency: Slot 3"
</Bypass>

<Bypass>	$Slot_INST_0_2_GBL
	<Msg>	"Check Fabric Switch(SW5) 0 to 2"
	<CheckData>	"Port 11 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port 12 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port 13 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port 14 : Link UP, adjacency: Slot 2"
</Bypass>

<Bypass>	$Slot_INST_0_1_GBL
 	<Msg>	"Check Fabric Switch(SW5) 0 to 1"
	<CheckData>	"Port 15 : Link UP, adjacency: Slot 1"
	<CheckData>	"Port 16 : Link UP, adjacency: Slot 1"
	<CheckData>	"Port 17 : Link UP, adjacency: Slot 1"
	<CheckData>	"Port 18 : Link UP, adjacency: Slot 1"
</Bypass>

<Bypass>    $Slot_INST_1_IMC_GBL
 <Bypass>	$Slot_INST_0_1_GBL
	<Msg>	"Check Base Channel Slot 1"
	<Send>		"on -f /net/nv-1-0 fabd -l"
	<Wait>
	<GetData>
	<CheckData>	"Ports with link up on Base Switch."
	<CheckData>	"Port  0 : Link UP, adjacency: Disco"
	<CheckData>	"Port  6 : Link UP, adjacency: MC Slot 0"
	<Msg>		"Check Fabric Slot 1 to all slots"
	<CheckData>	"Ports with link up on Fabric Switch.SW5."
</Bypass>
 </Bypass>

<Bypass>    $Slot_INST_1_IMC_GBL
 <Bypass>	$Slot_INST_1_4_GBL
	<Msg>	"Check Fabric Slot 1 to Slot 4"
	<CheckData>	"Port  3 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  4 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  5 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  6 : Link UP, adjacency: Slot 4"
</Bypass>
 </Bypass>

<Bypass>    $Slot_INST_1_IMC_GBL
 <Bypass>	$Slot_INST_1_3_GBL
	<Msg>	"Check Fabric Slot 1 to Slot 3"
	<CheckData>	"Port  7 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port  8 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port  9 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port 10 : Link UP, adjacency: Slot 3"
</Bypass>
</Bypass>

<Bypass>    $Slot_INST_1_IMC_GBL
 <Bypass>	$Slot_INST_1_2_GBL
	<Msg>	"Check Fabric Slot 1 to Slot 2"
	<CheckData>	"Port 11 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port 12 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port 13 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port 14 : Link UP, adjacency: Slot 2"
</Bypass>
</Bypass>

<Bypass>    $Slot_INST_1_IMC_GBL
 <Bypass>	$Slot_INST_0_1_GBL
	<Msg>	"Check Fabric Slot 1 to Slot 0"
	<CheckData>	"Port 15 : Link UP, adjacency: MC Slot 0"
</Bypass>
</Bypass>

<Msg>	"Bypassed remaining slots, telnet fail and Need command to show links"
#<Bypass>    $Slot_INST_0_2_GBL
#    <Msg>   "Check Internal Fabric to Poert, CPU and XLP"
#    <Send>      "on -p 7f -f /net/nv-2-0 xglcdiag linkstatus"
#    <Wait>
#     <GetData>
#    <CheckData> "Front Panel Port 0 (xe0) is UP"
#    <CheckData> "Front Panel Port 1 (xe1) is UP"
#    <CheckData> "Front Panel Port 2 (xe2) is UP"
#    <CheckData> "Front Panel Port 3 (xe3) is UP"
#    <CheckData> "P4080-CPU XAUI0 (xe4) is UP"
#    <CheckData> "P4080-CPU XAUI1 (xe5) is UP"
#    <CheckData> "Trident-NPU0 XAUI-A (xe6) is UP"
#    <CheckData> "Trident-NPU0 XAUI-B (xe7) is UP"
#    <CheckData> "Trident-NPU0 XAUI-C (xe8) is UP"
#    <CheckData> "Trident-NPU0 XAUI-D (xe9) is UP"
#    <CheckData> "Trident-NPU1 XAUI-A (xe10) is UP"
#    <CheckData> "Trident-NPU1 XAUI-B (xe11) is UP"
#    <CheckData> "Trident-NPU1 XAUI-C (xe12) is UP"
#    <CheckData> "Trident-NPU1 XAUI-D (xe13) is UP"
#</Bypass>
#<Bypass>    $Slot_INST_2_3_GBL
#    <Msg>   "Check Fabric Slot 2 to Slot 3"
##    <CheckData> "10G CHAN3 XGLC (xe14) is UP"
##    <CheckData> "10G CHAN4 XGLC (xe15) is UP"
#</Bypass>
<Bypass>    $Slot_INST_2_4_GBL
#    <Msg>   "Check Fabric Slot 2 to Slot 4"
##    <CheckData> "10G CHAN7 XGLC (xe16) is UP"
##    <CheckData> "10G CHAN8 XGLC (xe17) is UP"
#</Bypass>
#<Bypass>    $Slot_INST_0_2_GBL
#    <Msg>   "Check Fabric Base to NPU"
#    <CheckData> "NPU0 Base Channel (ge0) is UP"
#    <CheckData> "NPU1 Base Channel (ge1) is UP"
#</Bypass>
#<Bypass>    $Slot_INST_0_2_GBL
#    <Msg>   "Check Fabric Base to IMC0"
#    <CheckData> "IMC0 Base Channel (ge2) is UP"
#</Bypass>
#<Bypass>    $Slot_INST_1_2_GBL
#    <Msg>   "Check Fabric Base to IMC1"
#    <CheckData> "IMC1 Base Channel (ge3) is UP"
#</Bypass>
#<Bypass>    $Slot_INST_0_2_GBL
#    <Msg>   "Check Fabric Channel Slot 2 to IMC0"
#    <CheckData> "IMC0 Fabric Channel (ge4) is UP"
#    <CheckData> "IMC0 Fabric Channel (ge5) is UP"
#    <CheckData> "IMC0 Fabric Channel (ge6) is UP"
#    <CheckData> "IMC0 Fabric Channel (ge7) is UP"
#</Bypass>
#<Bypass>    $Slot_INST_1_2_GBL
#    <Msg>   "Check Fabric Channel Slot 2 to IMC1"
##    <CheckData> "IMC1 Fabric Channel (ge8) is UP"
##    <CheckData> "IMC1 Fabric Channel (ge9) is UP"
##    <CheckData> "IMC1 Fabric Channel (ge10) is UP"
##    <CheckData> "IMC1 Fabric Channel (ge11) is UP"
#</Bypass>



#<Bypass>    $Slot_INST_0_3_GBL
#    <Msg>   "Check Base Channel Slot 3"
#    <Send>      "on -f /net/nv-3-0 fabd -l"
#    <Wait>
#    <GetData>
#    <CheckData> "Ports with link up on Base Switch."
#    <CheckData> "Port  0 : Link UP, adjacency: Disco"
#    <CheckData> "Port  4 : Link UP, adjacency: MC Slot 0"
#    <Msg>       "Check Fabric Slot 3 to all slots"
#    <CheckData> "Ports with link up on Fabric Switch.SW5."
#</Bypass>

#<Bypass>    $Slot_INST_3_4_GBL
#    <Msg>   "Check Fabric Slot 3 to Slot 4"
#    <CheckData> "Port  3 : Link UP, adjacency: Slot 4"
#    <CheckData> "Port  4 : Link UP, adjacency: Slot 4"
#    <CheckData> "Port  5 : Link UP, adjacency: Slot 4"
#    <CheckData> "Port  6 : Link UP, adjacency: Slot 4"
#</Bypass>

#<Bypass>    $Slot_INST_2_3_GBL
#    <Msg>   "Check Fabric Slot 3 to Slot 2"
#    <CheckData> "Port  7 : Link UP, adjacency: Slot 2"
#    <CheckData> "Port  8 : Link UP, adjacency: Slot 2"
#    <CheckData> "Port  9 : Link UP, adjacency: Slot 2"
#    <CheckData> "Port 10 : Link UP, adjacency: Slot 2"
#</Bypass>

#<Bypass>    $Slot_INST_1_3_GBL
#    <Msg>   "Check Fabric Slot 3 to Slot 1"
#    <CheckData> "Port 11 : Link UP, adjacency: Slot 1"
#    <CheckData> "Port 12 : Link UP, adjacency: Slot 1"
#    <CheckData> "Port 13 : Link UP, adjacency: Slot 1"
#    <CheckData> "Port 14 : Link UP, adjacency: Slot 1"
#</Bypass>

#<Bypass>    $Slot_INST_0_3_GBL
#    <Msg>   "Check Fabric Slot 3 to Slot 0"
#    <CheckData> "Port 15 : Link UP, adjacency: MC Slot 0"
#</Bypass>

#<Bypass>    $Slot_INST_0_4_GBL
#    <Msg>   "Check Base Channel Slot 4"
#    <Send>      "on -f /net/nv-4-0 fabd -l"
#    <Wait>
#    <GetData>
#    <CheckData> "Ports with link up on Base Switch."
#    <CheckData> "Port  0 : Link UP, adjacency: Disco"
#    <CheckData> "Port  4 : Link UP, adjacency: MC Slot 0"
#    <Msg>       "Check Fabric Slot 4 to all slots"
#    <CheckData> "Ports with link up on Fabric Switch.SW5."
#</Bypass>

#<Bypass>    $Slot_INST_3_4_GBL
#    <Msg>   "Check Fabric Slot 4 to Slot 3"
#    <CheckData> "Port  3 : Link UP, adjacency: Slot 3"
#    <CheckData> "Port  4 : Link UP, adjacency: Slot 3"
#    <CheckData> "Port  5 : Link UP, adjacency: Slot 3"
#    <CheckData> "Port  6 : Link UP, adjacency: Slot 3"
#</Bypass>

#<Bypass>    $Slot_INST_2_4_GBL
#    <Msg>   "Check Fabric Slot 4 to Slot 2"
#    <CheckData> "Port  7 : Link UP, adjacency: Slot 2"
#    <CheckData> "Port  8 : Link UP, adjacency: Slot 2"
#    <CheckData> "Port  9 : Link UP, adjacency: Slot 2"
#    <CheckData> "Port 10 : Link UP, adjacency: Slot 2"
#</Bypass>

#<Bypass>    $Slot_INST_1_4_GBL
#    <Msg>   "Check Fabric Slot 4 to Slot 1"
#    <CheckData> "Port 11 : Link UP, adjacency: Slot 1"
#    <CheckData> "Port 12 : Link UP, adjacency: Slot 1"
#    <CheckData> "Port 13 : Link UP, adjacency: Slot 1"
#    <CheckData> "Port 14 : Link UP, adjacency: Slot 1"
#</Bypass>

#<Bypass>    $Slot_INST_0_4_GBL
#    <Msg>   "Check Fabric Slot 4 to Slot 0"
#    <CheckData> "Port 15 : Link UP, adjacency: MC Slot 0"
#</Bypass>












