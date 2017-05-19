################################################################################
#
# Module:      Internal_Snake_setup.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Pe,BI,POST.dat
#
# Version:    1.5   $Id: Internal_Snake_setup.inc,v 1.13 2009/05/07 15:50:10 joe Exp $
#
# Changes:    Added <GetData> 12/05/05
#  			  Added Clear of IXP errors
#			  Added Selection for IMC in Slot 1
#			  Added <chechkdatax> for on command
#			  Added ixtest -i to setup (more time to init sram) 10/7/13
#
# Still ToDo:
#
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
#
# Version 5a1	11/12/05
#
<Msg>		"Setup Fabric ..."
<Prompt>	"#"
<Timeout>	120

#<Send>		'ksh < /proc/boot/mc.setup.fabsnake'
# 04/24/06   post test snake [slot1] [slot2] ...
#<Wait>
#<Include>	Setup_Fab_Snake.inc
#<Msg>		"Wait 5 seconds for Setup to Complete"
#<Sleep>		5
<Bypass>	$Slot_INST_1_IMC_GBL
	<Msg>	"Wait for Slot 1 IMC"
	<Send>	'waitfor /net/nv-1-0/stoke/bin/diag/mc.setup.fabsnake 100'
	<Wait>
	<CheckDatax> "on: No such file or directory .mc.setup.fabsnake"
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>	"Wait for Slot 1 GLC"
	<Send>	'waitfor /net/nv-1-0/stoke/bin/diag/ixtest 100'
	<Wait>
	<CheckDatax> "on: No such file or directory .ixtest"
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>	"Wait for Slot 2"
	<Send>	'waitfor /net/nv-2-0/stoke/bin/diag/ixtest 100'
	<Wait>
	<CheckDatax> "on: No such file or directory .ixtest"
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>	"Wait for Slot 3"
	<Send>	'waitfor /net/nv-3-0/stoke/bin/diag/ixtest 100'
	<Wait>
	<CheckDatax> "on: No such file or directory .ixtest"
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>	"Wait for Slot 4"
	<Send>	'waitfor /net/nv-4-0/stoke/bin/diag/ixtest 100'
	<Wait>
	<CheckDatax> "on: No such file or directory .ixtest"
</Bypass>
<Timeout>	60
<Bypass>	$Slot_INST_1_GLC_GBL
	<Send>		"on -f /net/nv-1-0 ixtest -i > /dev/null"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-1-0 ixtest errors > /dev/null"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-1-0 ixtest mt"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-1-0 ixtest mt -s0"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-1-0 ixtest errors"
	<Wait>
	<GetData>
	<Sendslow>		"pfeffa on 1 show n2 count > /dev/null"
	<Wait>
	<GetData>
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<Send>		"on -f /net/nv-2-0 ixtest -i > /dev/null"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-2-0 ixtest errors > /dev/null"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-2-0 ixtest mt"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-2-0 ixtest mt -s0"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-2-0 ixtest errors"
	<Wait>
	<GetData>
	<Sendslow>		"pfeffa on 2 show n2 count > /dev/null"
	<Wait>
	<GetData>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<Send>		"on -f /net/nv-3-0 ixtest -i > /dev/null"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-3-0 ixtest errors > /dev/null"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-3-0 ixtest mt"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-3-0 ixtest mt -s0"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-3-0 ixtest errors"
	<Wait>
	<GetData>
	<Sendslow>		"pfeffa on 3 show n2 count > /dev/null"
	<Wait>
	<GetData>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<Send>		"on -f /net/nv-4-0 ixtest -i > /dev/null"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-4-0 ixtest errors > /dev/null"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-4-0 ixtest mt"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-4-0 ixtest mt -s0"
	<Wait>
	<GetData>
	<Send>		"on -f /net/nv-4-0 ixtest errors"
	<Wait>
	<GetData>
	<Sendslow>		"pfeffa on 4 show n2 count > /dev/null"
	<Wait>
	<GetData>
</Bypass>
#
<Msg>		"Starting Pfeffa, Test All slots 1 and 100 packets looped back..."
#

<Prompt>   "> "
<Send>     "pfeffa"
<Wait>
<Timeout>	300

<Send>		"test snake"
<Wait>
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
#<GetData>

<Sleep>     3
<Sendslow>      'clear mibs *'
<Wait>
<GetData>


#Clear ixtest errors
<Bypass>	$Slot_INST_1_GLC_GBL
	<SendSlow>		"sys on -f /net/nv-1-0 ixtest errors > /dev/null"
	<Wait>
	<GetData>
	<Sendslow>		"on 1 show n2 count > /dev/null"
	<Wait>
	<GetData>
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<SendSlow>		"sys on -f /net/nv-2-0 ixtest errors > /dev/null"
	<Wait>
	<GetData>
	<Sendslow>		"on 2 show n2 count > /dev/null"
	<Wait>
	<GetData>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<SendSlow>		"sys on -f /net/nv-3-0 ixtest errors > /dev/null"
	<Wait>
	<GetData>
	<Sendslow>		"on 3 show n2 count > /dev/null"
	<Wait>
	<GetData>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<SendSlow>		"sys on -f /net/nv-4-0 ixtest errors > /dev/null"
	<Wait>
	<GetData>
	<Sendslow>		"on 4 show n2 count > /dev/null"
	<Wait>
	<GetData>
</Bypass>

<Msg>		"Exiting Pfeffa..."
<GetData>
<Timeout>	30
<Prompt>	"#"
<Sleep>		1
<Sendslow> 		"exit"
<Wait>
