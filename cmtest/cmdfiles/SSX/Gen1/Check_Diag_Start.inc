################################################################################
#
# Module:      Check_Diag_Start.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_PRE_BI.dat, Chassis BI, Chassis_Post_BI.dat,Config.dat
#
# Version:    1.1 $Id: Check_Diag_Start.inc,v 1.2 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Created 10/18/06
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################

<Timeout>	20
<Prompt>	'#'
<Timeout>	100
<Bypass>	$Slot_INST_1_IMC_GBL
	<Msg>	"Wait for Slot 1 IMC"
	<Send>	'waitfor /net/nv-1-0/stoke/bin/diag/mc.setup.fabsnake 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>	"Wait for Slot 1 GLC"
	<Send>	'waitfor /net/nv-1-0/stoke/bin/diag/ixtest 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>	"Wait for Slot 2"
	<Send>	'waitfor /net/nv-2-0/stoke/bin/diag/ixtest 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>	"Wait for Slot 3"
	<Send>	'waitfor /net/nv-3-0/stoke/bin/diag/ixtest 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>	"Wait for Slot 4"
	<Send>	'waitfor /net/nv-4-0/stoke/bin/diag/ixtest 100'
	<Timeout>	20
</Bypass>


