 ################################################################################
#
# Module:      Reload_all_slots
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI, Pre_BI,POst_BI, Config, Extended, ORT Dat files
#
# Version:    1.1 $Id: Reload_all_slots.inc,v 1.2 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Created 10/12/06
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################
<Prompt>	"Stoke[local]"
<Timeout>	10
<Msg>		"Reload All Slots"
<Bypass>	$Slot_INST_1_GBL
 	<Send>		"reload card 1"
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_2_GBL
 	<Send>		"reload card 2"
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_3_GBL
 	<Send>		"reload card 3"
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_4_GBL
 	<Send>		"reload card 4"
	<Wait>
</Bypass>

