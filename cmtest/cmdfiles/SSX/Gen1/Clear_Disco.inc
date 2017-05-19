################################################################################
#
# Module:      Clear Disco.txt
#
# Author:      Joe White
#
# Descr:       Clear Disco errors after startup
#
# Version:    1.1 $Id: Clear_Disco.inc,v 1.1 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Created 01/23/08
#
# Includes:
#
# Still ToDo:
#              - Add Looping on each test, start a process for each test
#
#
#            Copyright (c) 2008 Stoke. All rights reserved.
#
################################################################################

<Msg>	"Clear Disco Errors"

<Prompt>	"#"
<Timeout>	10

<Send>	"pfeffa show disco prob > /dev/null"
<Wait>
<Sleep>	1

<Bypass>	$Slot_INST_1_IMC_GBL
	#<Msg>	"Clear Disco Errors IMC Slot 1"
	<Send>	"pfeffa on 1 show disco prob  > /dev/null"
	<Wait>
   <Sleep> 1
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Send>	"pfeffa on 1 show disco prob > /dev/null"
	<Wait>
   <Sleep> 1
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Send>	"pfeffa on 2 show disco prob > /dev/null"
	<Wait>
   <Sleep> 1
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Send>	"pfeffa on 3 show disco prob > /dev/null"
	<Wait>
   <Sleep> 1
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Send>	"pfeffa on 4 show disco prob > /dev/null"
	<Wait>
   <Sleep> 1
</Bypass>




