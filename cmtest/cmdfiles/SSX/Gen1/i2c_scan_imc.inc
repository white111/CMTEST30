################################################################################
#
# Module:      i2c_scan_imc.inc
#
# Author:      Joe White
#
# Descr:       Called by Bench_Test_IMC.dat
#
# Version:    1.4 $Id: i2c_scan_imc.inc,v 1.6.2.1 2011/01/21 17:45:26 joe Exp $
#
# Changes:    Updates to noodle I2C display
#			  1/12/08 Updates to noodle for I2C displayed
#			  Changes for PSOC 11/16/10
#			  Fixes for faster serial ports 4/3/12
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################
<Prompt>	"slot 0"
<TimeOut>	2
<Msg>		"Check I2C...."
<Send>		"set ver 2"
<wait>
<sleep>		2
<TimeOut>	55
<Send>		"show i2c scan local"
#<WaitFor>	"slot number"
<Wait>
#<CheckData>	'35 SPD_MYSTERY'
<CheckData>	'50 U67_EEPROM'
<CheckData>	'55 SPD_EEPROM'
<CheckData>	'70 9546'
<CheckData>	'04 U200_GPIO'
#<CheckData>	'35 SPD_MYSTERY'
<CheckData>	'44 U200_EEPROM'
<CheckData>	'50 U67_EEPROM'
<CheckData>	'55 SPD_EEPROM'
<CheckData>	'70 9546'
<CheckData>	'35 SPD_MYSTERY'
<CheckData>	'48 THERMAL_INLET'
<CheckData>	'4A THERMAL_OUTLET'
<CheckData>	'4E THERMAL_PPC'
<CheckData>	'50 U67_EEPROM'
<CheckData>	'55 SPD_EEPROM'
<CheckData>	'70 9546'
#<CheckData> '04 POTENTIA-.*0 MYSTERY'
#<CheckData> '06 POTENTIA-.*1 MYSTERY'
#<CheckData> '0C POTENTIA-.*0 MYSTERY'
#<CheckData> '0E POTENTIA-.*1 MYSTERY'
#<CheckData> '14 POTENTIA-.*0 MYSTERY'
#<CheckData> '16 POTENTIA-.*1 MYSTERY'
#<CheckData> '1C POTENTIA-.*0 MYSTERY'
#<CheckData> '1E POTENTIA-.*1 MYSTERY'
#<CheckData> '24 POTENTIA-.*0 MYSTERY'
#<CheckData> '26 POTENTIA-.*1 MYSTERY'
#<CheckData> '2C POTENTIA-.*0 MYSTERY'
#<CheckData> '2E POTENTIA-.*1 MYSTERY'
#<CheckData> '34 POTENTIA-.*0 MYSTERY'
#<CheckData>	'35 SPD_MYSTERY'
#<CheckData> '36 POTENTIA-.*1 MYSTERY'
#<CheckData> '3C POTENTIA-.*0 MYSTERY'
#<CheckData> '3E POTENTIA-.*1 MYSTERY'
#<CheckData> '44 POTENTIA-.*0 MYSTERY'
#<CheckData> '46 POTENTIA-.*1 MYSTERY'
#<CheckData> '4C POTENTIA-.*0 MYSTERY'
#<CheckData> '4E POTENTIA-.*1 MYSTERY'
<CheckData>	'50 U67_EEPROM'
#<CheckData> '54 POTENTIA-.*0 NVRAM'
<CheckData>	'55 SPD_EEPROM'
#<CheckData> '56 POTENTIA-.*1 NVRAM'
#<CheckData> '5C POTENTIA-.*0 MYSTERY'
#<CheckData> '5E POTENTIA-.*1 MYSTERY'
#<CheckData> '64 POTENTIA-.*0 MYSTERY'
#<CheckData> '66 POTENTIA-.*1 MYSTERY'
#<CheckData> '6C POTENTIA-.*0 SHADOW'
#<CheckData> '6E POTENTIA-.*1 SHADOW'
<CheckData>	'70 9546'
#<CheckData> '74 POTENTIA-.*0 NVRAM-X'
#<CheckData> '76 POTENTIA-.*1 NVRAM-X'
<CheckData>	'7C POTENTIA-.*0 CTL/STAT'
<CheckData>	'7E POTENTIA-.*1 CTL/STAT'
#<CheckData>	'local:    3 35 SPD_MYSTERY'
<CheckData>	'50 U67_EEPROM'
<CheckData>	'54 FIC_EEPROM'
<CheckData>	'55 SPD_EEPROM'
<CheckData>	'57 U128_EEPROM'
<CheckData>	'70 9546'


<sleep>		2
<TimeOut>	2
<Send>		"set ver 0"
<Wait>
<TimeOut>	2
