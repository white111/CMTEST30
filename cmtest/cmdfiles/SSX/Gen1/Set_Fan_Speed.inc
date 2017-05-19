 ################################################################################
#
# Module:      Set_Fan_Speed.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI, Pre_BI,POst_BI, Config, Extended, ORT Dat files
#
# Version:    1.2 $Id: Set_Fan_Speed.inc,v 1.4 2009/05/07 15:50:10 joe Exp $
#
# Changes:    Created 10/12/06
#			  Adding Display of thermal 08/25/08
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################
#    <Msg>       "Check/Display Thermal sensors..."
#<Send>      "pfeffa show thermal"
#<Wait>
#<GetData>   GLC_Thermal_Display

#<Bypass>    $Slot_INST_1_IMC_GBL
#            <Send>      "pfeffa on 1 show thermal"
#            <Wait>
#            <GetData>   GLC_Thermal_Display
#</Bypass>
#<Bypass>    $Slot_INST_1_GLC_GBL
#            <Send>      "pfeffa on 1 show thermal"
#            <Wait>
#            <GetData>   GLC_Thermal_Display
#</Bypass>
#<Bypass>    $Slot_INST_2_GBL
#            <Send>      "pfeffa on 3 show thermal"
#            <Wait>
#            <GetData>   GLC_Thermal_Display
#</Bypass>
#<Bypass>    $Slot_INST_3_GBL
#            <Send>      "pfeffa on 3 show thermal"
#            <Wait>
#            <GetData>   GLC_Thermal_Display
#</Bypass>
#<Bypass>    $Slot_INST_4_GBL
#            <Send>      "pfeffa on 4 show thermal"
#            <Wait>
#            <GetData>   GLC_Thermal_Display
#</Bypass>



 	<Msg>		$FanSpeed_MSG_GBL



# Non pfeffa
	<SendChr>		"pfeffa "
	<Send>		$FanSpeed1_GBL
	<Waitfor>	"#"
	<SendChr>		"pfeffa "
	<Send>		$FanSpeed2_GBL
	<Waitfor>	"#"
#Pfeffa

	<Send>		$FanSpeed1_GBL
	<Waitfor>	"#"
	<Send>		$FanSpeed2_GBL
	<Waitfor>	"#"

<Send>		"show version"
<Wait>
<GetData>

<Send>		"pfeffa show version"
<Wait>
<GetData>
