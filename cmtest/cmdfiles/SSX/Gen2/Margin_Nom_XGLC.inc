################################################################################
#
# Module:      Margin_nom_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Pe,BI,POST.dat
#
# Version:    1.2   $Id: Internal_Snake_setup_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 03/04/12
#			  Added Support for XGLC in Slot 1 9/3/13
#
# Still ToDo:
#
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################
#
# Version 5a1	11/12/05
#

<Prompt>	"#"
<Timeout>	20



<Bypass>    $Slot_INST_1_GLC_GBL
    <Msg>       "Margin Slot 1 Voltages Nominal ..."
	<Send>      "on -p 7f -f /net/nv-1-0 xglcdiag monitor margin all nominal"
	<Wait>
	<GetData>
 	<Msg>       "Monitor Slot 2 Voltages Nominal ..."
    <Send>      "on -p 7f -f /net/nv-1-0 xglcdiag monitor voltage all"
	<Wait>
	<GetData>   Check_XGLC_voltage
</Bypass>
<Bypass>    $Slot_INST_2_GBL
    <Msg>       "Margin Slot 2 Voltages Nominal ..."
	<Send>      "on -p 7f -f /net/nv-2-0 xglcdiag monitor margin all nominal"
	<Wait>
	<GetData>
 	<Msg>       "Monitor Slot 2 Voltages Nominal ..."
    <Send>      "on -p 7f -f /net/nv-2-0 xglcdiag monitor voltage all"
	<Wait>
	<GetData>   Check_XGLC_voltage
</Bypass>

<Bypass>    $Slot_INST_3_GBL
    <Msg>       "Margin Slot 3 Voltages Nominal ..."
	<Send>      "on -p 7f -f /net/nv-3-0 xglcdiag monitor margin all nominal"
	<Wait>
	<GetData>
 	<Msg>       "Monitor Slot 3 Voltages Nominal ..."
    <Send>      "on -p 7f -f /net/nv-3-0 xglcdiag monitor voltage all"
	<Wait>
	<GetData>   Check_XGLC_voltage
</Bypass>

<Bypass>    $Slot_INST_4_GBL
    <Msg>       "Margin Slot 4 Voltages Nominal ..."
	<Send>      "on -p 7f -f /net/nv-4-0 xglcdiag monitor margin all nominal"
	<Wait>
	<GetData>
 	<Msg>       "Monitor Slot 4 Voltages Nominal ..."
    <Send>      "on -p 7f -f /net/nv-4-0 xglcdiag monitor voltage all"
	<Wait>
	<GetData>   Check_XGLC_voltage
</Bypass>

