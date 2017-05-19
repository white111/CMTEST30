################################################################################
#
# Module:      Get_System_Serial.txt
#
# Author:      Joe White
#
# Descr:       Collects System serial numbers
#
# Version:    1.0 $Id: Get_System_Serial.inc,v 1.1 2009/05/07 15:50:10 joe Exp $
#
# Changes:    06/12/08 Created
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
<Msg>		"Get System serial numbers"
<Timeout>	60
<Prompt>	"#"
<Send>		"pfeffa show mfg"
<Wait>
<GetData>	ShowMFG
<Include>	Set_Fan_Speed.inc

<Msg>		"Detect Which slots have 5th IXF-IXP link enabled"
<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>		"Check Slot 1"
	<Send>		"on -f /net/nv-1-0 pfeffa rd i2c fic tlv 3"
	<Wait>
	<GetData>  SW55thlink

</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>		"Check Slot 2"
	<Send>		"on -f /net/nv-2-0 pfeffa rd i2c fic tlv 3"
	<Wait>
	<GetData>  SW55thlink

</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>		"Check Slot 3"
	<Send>		"on -f /net/nv-3-0 pfeffa rd i2c fic tlv 3"
	<Wait>
	<GetData>  SW55thlink

</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>		"Check Slot 4"
	<Send>		"on -f /net/nv-4-0 pfeffa rd i2c fic tlv 3"
	<Wait>
	<GetData>   SW55thlink

</Bypass>

