################################################################################
#
# Module:      check_fabric.inc
#
# Author:      Joe White
#
# Descr:       Main Execution for IMC Bench test
#
# Version:    2.1 $Id: check_fabric.inc,v 1.6 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Added <GetData>  12/05/05
#			  Changed to use fabd instead of pfeffa test fabric
#			  Added Selction of GLC or IMC in Slot 1
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
	<Msg>		"Wait for GLC in slot 1 to be ready"
	<Send>		"waitfor /net/nv-1-0/stoke/bin/diag/ixtest 90"
	<Wait>
	<GetData>

</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>		"Wait for GLC in slot 2 to be ready"
	<Send>		"waitfor /net/nv-2-0/stoke/bin/diag/ixtest 90"
	<Wait>
	<GetData>

</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>		"Wait for GLC in slot 3 to be ready"
	<Send>		"waitfor /net/nv-3-0/stoke/bin/diag/ixtest 90"
	<Wait>
	<GetData>

</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>		"Wait for GLC in slot 4 to be ready"
	<Send>		"waitfor /net/nv-4-0/stoke/bin/diag/ixtest 90"
	<Wait>
	<GetData>

</Bypass>

<Sleep> 5
<TimeOut>	30
<Msg>	"Check Base Channel to Slot 0 to All Slots"
<Msg>		"Start Fabric Slot 0"
<Send>		"fabd -l"
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

<Bypass>	$Slot_INST_1_4_GBL
	<Msg>	"Check Fabric Slot 1 to Slot 4"
	<CheckData>	"Port  3 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  4 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  5 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  6 : Link UP, adjacency: Slot 4"
</Bypass>

<Bypass>	$Slot_INST_1_3_GBL
	<Msg>	"Check Fabric Slot 1 to Slot 3"
	<CheckData>	"Port  7 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port  8 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port  9 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port 10 : Link UP, adjacency: Slot 3"
</Bypass>

<Bypass>	$Slot_INST_1_2_GBL
	<Msg>	"Check Fabric Slot 1 to Slot 2"
	<CheckData>	"Port 11 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port 12 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port 13 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port 14 : Link UP, adjacency: Slot 2"
</Bypass>

<Bypass>	$Slot_INST_0_1_GBL
	<Msg>	"Check Fabric Slot 1 to Slot 0"
	<CheckData>	"Port 15 : Link UP, adjacency: MC Slot 0"
</Bypass>

<Bypass>	$Slot_INST_0_2_GBL
	<Msg>	"Check Base Channel Slot 2"
	<Send>		"on -f /net/nv-2-0 fabd -l"
	<Wait>
	<GetData>
	<CheckData>	"Ports with link up on Base Switch."
	<CheckData>	"Port  0 : Link UP, adjacency: Disco"
	<CheckData>	"Port  4 : Link UP, adjacency: MC Slot 0"
	<Msg>		"Check Fabric Slot 2 to all slots"
	<CheckData>	"Ports with link up on Fabric Switch.SW5."
</Bypass>

<Bypass>	$Slot_INST_2_4_GBL
	<Msg>	"Check Fabric Slot 2 to Slot 4"
	<CheckData>	"Port  3 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  4 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  5 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  6 : Link UP, adjacency: Slot 4"
</Bypass>

<Bypass>	$Slot_INST_2_3_GBL
	<Msg>	"Check Fabric Slot 2 to Slot 3"
	<CheckData>	"Port  7 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port  8 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port  9 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port 10 : Link UP, adjacency: Slot 3"
</Bypass>

<Bypass>	$Slot_INST_1_2_GBL
	<Msg>	"Check Fabric Slot 2 to Slot 1"
	<CheckData>	"Port 11 : Link UP, adjacency: Slot 1"
	<CheckData>	"Port 12 : Link UP, adjacency: Slot 1"
	<CheckData>	"Port 13 : Link UP, adjacency: Slot 1"
	<CheckData>	"Port 14 : Link UP, adjacency: Slot 1"
</Bypass>

<Bypass>	$Slot_INST_0_2_GBL
	<Msg>	"Check Fabric Slot 2 to Slot 0"
	<CheckData>	"Port 15 : Link UP, adjacency: MC Slot 0"
</Bypass>

<Bypass>	$Slot_INST_0_3_GBL
	<Msg>	"Check Base Channel Slot 3"
	<Send>		"on -f /net/nv-3-0 fabd -l"
	<Wait>
	<GetData>
	<CheckData>	"Ports with link up on Base Switch."
	<CheckData>	"Port  0 : Link UP, adjacency: Disco"
	<CheckData>	"Port  4 : Link UP, adjacency: MC Slot 0"
	<Msg>		"Check Fabric Slot 3 to all slots"
	<CheckData>	"Ports with link up on Fabric Switch.SW5."
</Bypass>

<Bypass>	$Slot_INST_3_4_GBL
	<Msg>	"Check Fabric Slot 3 to Slot 4"
	<CheckData>	"Port  3 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  4 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  5 : Link UP, adjacency: Slot 4"
	<CheckData>	"Port  6 : Link UP, adjacency: Slot 4"
</Bypass>

<Bypass>	$Slot_INST_2_3_GBL
	<Msg>	"Check Fabric Slot 3 to Slot 2"
	<CheckData>	"Port  7 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port  8 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port  9 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port 10 : Link UP, adjacency: Slot 2"
</Bypass>

<Bypass>	$Slot_INST_1_3_GBL
	<Msg>	"Check Fabric Slot 3 to Slot 1"
	<CheckData>	"Port 11 : Link UP, adjacency: Slot 1"
	<CheckData>	"Port 12 : Link UP, adjacency: Slot 1"
	<CheckData>	"Port 13 : Link UP, adjacency: Slot 1"
	<CheckData>	"Port 14 : Link UP, adjacency: Slot 1"
</Bypass>

<Bypass>	$Slot_INST_0_3_GBL
	<Msg>	"Check Fabric Slot 3 to Slot 0"
	<CheckData>	"Port 15 : Link UP, adjacency: MC Slot 0"
</Bypass>

<Bypass>	$Slot_INST_0_4_GBL
	<Msg>	"Check Base Channel Slot 4"
	<Send>		"on -f /net/nv-4-0 fabd -l"
	<Wait>
	<GetData>
	<CheckData>	"Ports with link up on Base Switch."
	<CheckData>	"Port  0 : Link UP, adjacency: Disco"
	<CheckData>	"Port  4 : Link UP, adjacency: MC Slot 0"
	<Msg>		"Check Fabric Slot 4 to all slots"
	<CheckData>	"Ports with link up on Fabric Switch.SW5."
</Bypass>

<Bypass>	$Slot_INST_3_4_GBL
	<Msg>	"Check Fabric Slot 4 to Slot 3"
	<CheckData>	"Port  3 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port  4 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port  5 : Link UP, adjacency: Slot 3"
	<CheckData>	"Port  6 : Link UP, adjacency: Slot 3"
</Bypass>

<Bypass>	$Slot_INST_2_4_GBL
	<Msg>	"Check Fabric Slot 4 to Slot 2"
	<CheckData>	"Port  7 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port  8 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port  9 : Link UP, adjacency: Slot 2"
	<CheckData>	"Port 10 : Link UP, adjacency: Slot 2"
</Bypass>

<Bypass>	$Slot_INST_1_4_GBL
	<Msg>	"Check Fabric Slot 4 to Slot 1"
	<CheckData>	"Port 11 : Link UP, adjacency: Slot 1"
	<CheckData>	"Port 12 : Link UP, adjacency: Slot 1"
	<CheckData>	"Port 13 : Link UP, adjacency: Slot 1"
	<CheckData>	"Port 14 : Link UP, adjacency: Slot 1"
</Bypass>

<Bypass>	$Slot_INST_0_4_GBL
	<Msg>	"Check Fabric Slot 4 to Slot 0"
	<CheckData>	"Port 15 : Link UP, adjacency: MC Slot 0"
</Bypass>












