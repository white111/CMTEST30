 ################################################################################
#
# Module:      Set_Fan_Speed.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI, Pre_BI,POst_BI, Config, Extended, ORT Dat files
#
# Version:    1.5 $Id: Set_Fan_Speed.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 10/12/06
#			  Adding Display of thermal 08/25/08
#			  Hard Coded XGLC Fan1 to High speed 2/21/12
#			  Added Slow down for Fan2 3/13/13
#			  Cleanup 10/21/13 cuasing down strem scripts to fail(expect_after)
#			  Updated for Fan2  10/30/13
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2013 Stoke. All rights reserved.
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



    #<Bypass>	$UUT_Variable_ref[22]->{FAN2}
    	<Msg>		"XGLC Fan1 type Hardcoded to High Speed"
    #</Bypass>
    <prompt>	"#"
# Non pfeffa
	<SendChr>		"pfeffa "
	#<Send>		$FanSpeed1_GBL
	<Send>		"wr i2c 9501 fan1 gpio E7"
	<Wait>
	<SendChr>		"pfeffa "
	#<Sendchr>		"wr i2c 9501 fan2 gpio E7"
	<Send>		$FanSpeed2_GBL
	<Wait>
	#<Send> 		"pfeffa wr i2c adm1029 1 60 55"
	<SendChr>		"pfeffa "
	<Send> 		"$Fan2Speed1_GBL"
	<Wait>
	<SendChr>		"pfeffa "
	<Send> 		"$Fan2Speed2_GBL"
	<Wait>
#Pfeffa

	#<Send>		$FanSpeed1_GBL
	<Send>		"wr i2c 9501 fan1 gpio E7"
	<Wait>
	#<Send>		$FanSpeed2_GBL
	<Send>		"wr i2c 9501 fan2 gpio E7"
	<Wait>
	<Send> 		"$Fan2Speed1_GBL"
	<Wait>
	<Send> 		"$Fan2Speed2_GBL"
	<Wait>

<Send>		"show version"
<Wait>
<GetData>

<Send>		"pfeffa show version"
<Wait>
<GetData>
