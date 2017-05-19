################################################################################
#
# Module:      Show_Card_Stoke.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Pre_BI,POST_BI and Config
#
# Version:    1.5 $Id: Show_Card_Stoke.inc,v 1.8 2010/03/12 18:50:59 joe Exp $
#
# Changes:    Added <GetData>   12/05/05
#			  Modified for R1  010806
#			  Updated to select IMC or GLC in slot 1
#			  5/28/09 updated to sheck SFP I2C
#			  3/3/10 update for 4.6 bug 14440 GLC in slot 1
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"Stoke[local]#"
<Send>
<Wait>
<TimeOut>	20
<Send>		"terminal length infinite"
<Wait>
<Msg>		"Show Cards"
<Send>		"show card"
<Waitfor>	"Slot"
<Wait>
<GetData>

<CheckData>	    "0 IMC.*Running.*Stoke IMC"
<Bypass>	$Slot_INST_1_IMC_GBL
	<CheckData>	    "1 IMC.*Running.*Stoke IMC"
</Bypass>
<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>          "1 GLC.*Running.*1000Base-X check bypassed Bug 14440"
	#<CheckData>	    "1 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<CheckData>	    "2 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<CheckData>	    "3 GLC.*Running.*1000Base-X"
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<CheckData>	    "4 GLC.*Running.*1000Base-X"
</Bypass>



<Msg>          "show port 1/x detail check bypassed Bug 14440"
#<Bypass>    $Slot_INST_1_GLC_GBL
#    <msg>       "Check slot 1 SFP I2C"
#    <send>      "show port 1/0 detail"
#    <wait>
#    <getdata>
#    <CheckData>        "1000BASE-SX"
#    <send>      "show port 1/1 detail"
#    <wait>
#    <getdata>
#    <CheckData>        "1000BASE-SX"
#    <send>      "show port 1/2 detail"
#    <wait>
#    <getdata>
#    <CheckData>        "1000BASE-SX"
#    <send>      "show port 1/2 detail"
#    <wait>
#    <getdata>
#    <CheckData>        "1000BASE-SX"
#</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<msg>		"Check slot 2 SFP I2C"
	<send>		"show port 2/0 detail"
	<wait>
	<getdata>
	<CheckData>	    "1000BASE-SX"
		<send>		"show port 2/1 detail"
	<wait>
	<getdata>
	<CheckData>	    "1000BASE-SX"
		<send>		"show port 2/2 detail"
	<wait>
	<getdata>
	<CheckData>	    "1000BASE-SX"
		<send>		"show port 2/3 detail"
	<wait>
	<getdata>
	<CheckData>	    "1000BASE-SX"
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<msg>		"Check slot 3 SFP I2C"
	<send>		"show port 3/0 detail"
	<wait>
	<getdata>
	<CheckData>	    "1000BASE-SX"
		<send>		"show port 3/1 detail"
	<wait>
	<getdata>
	<CheckData>	    "1000BASE-SX"
		<send>		"show port 3/2 detail"
	<wait>
	<getdata>
	<CheckData>	    "1000BASE-SX"
		<send>		"show port 3/3 detail"
	<wait>
	<getdata>
	<CheckData>	    "1000BASE-SX"
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<msg>		"Check slot 4 SFP I2C"
	<send>		"show port 4/0 detail"
	<wait>
	<getdata>
	<CheckData>	    "1000BASE-SX"
		<send>		"show port 4/1 detail"
	<wait>
	<getdata>
	<CheckData>	    "1000BASE-SX"
		<send>		"show port 4/2 detail"
	<wait>
	<getdata>
	<CheckData>	    "1000BASE-SX"
		<send>		"show port 4/3 detail"
	<wait>
	<getdata>
	<CheckData>	    "1000BASE-SX"
</Bypass>

<Send>
<Wait>



