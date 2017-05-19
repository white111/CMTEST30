################################################################################
#
# Module:      i2c_scan_glc.inc
#
# Author:      Joe White
#
# Descr:       Called by Bench_GLC.dat
#
# Version:    1.5 $Id: i2c_scan_glc.inc,v 1.5.2.1 2011/01/21 17:45:26 joe Exp $
#
# Changes:    First Release  12/05/05
#			  11/28/07 Output format changed adding 2610-
#			  Updates for diag image 9/19/08
#			  Updates for PSOC replacement of Potentia
#              Fixes for faster serial ports 4/3/12 
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"slot 2"
<TimeOut>	2
<Msg>		"Check I2C...."
<Send>		"set ver 2"
<Wait>
<TimeOut>	45
<Sendslow>		"show i2c scan local"
#<WaitFor>	"slot num"
<Wait>
<GetData>
#<CheckData>	'local:  off 35 SPD_MYSTERY'
<CheckData>	'50 U67_EEPROM'
<CheckData>	'55 SPD_EEPROM'
<CheckData>	'70 9546'
<CheckData>	'31 RDRAM0 MYSTERY'
<CheckData>	'32 RDRAM1 MYSTERY'
<CheckData>	'33 RDRAM2 MYSTERY'
#<CheckData>	'35 SPD_MYSTERY'
<CheckData>	'50 U67_EEPROM'
<CheckData>	'51 RDRAM0'
<CheckData>	'52 RDRAM1'
<CheckData>	'53 RDRAM2'
<CheckData>	'55 SPD_EEPROM'
<CheckData>	'70 9546'
#<CheckData>	'local:    1 35 SPD_MYSTERY'
<CheckData>	'48 THERMAL_INLET'
<CheckData>	'4A THERMAL_OUTLET'
<CheckData>	'4C THERMAL_IXP'
<CheckData>	'4E THERMAL_PPC'
<CheckData>	'50 U67_EEPROM'
<CheckData>	'55 SPD_EEPROM'
<CheckData>	'70 9546'
# Removed for PSOC replacement
#<CheckData> '04 POTENTIA-2610-0 MYSTERY'
#<CheckData> '06 POTENTIA-2610-1 MYSTERY'
#<CheckData> '0C POTENTIA-2610-0 MYSTERY'
#<CheckData> '0E POTENTIA-2610-1 MYSTERY'
#<CheckData> '14 POTENTIA-2610-0 MYSTERY'
#<CheckData> '16 POTENTIA-2610-1 MYSTERY'
#<CheckData> '1C POTENTIA-2610-0 MYSTERY'
#<CheckData> '1E POTENTIA-2610-1 MYSTERY'
#<CheckData> '24 POTENTIA-2610-0 MYSTERY'
#<CheckData> '26 POTENTIA-2610-1 MYSTERY'
#<CheckData> '2C POTENTIA-2610-0 MYSTERY'
#<CheckData> '2E POTENTIA-2610-1 MYSTERY'
#<CheckData> '34 POTENTIA-2610-0 MYSTERY'
#<CheckData>	'35 SPD_MYSTERY'
#<CheckData> '36 POTENTIA-2610-1 MYSTERY'
#<CheckData> '3C POTENTIA-2610-0 MYSTERY'
#<CheckData> '3E POTENTIA-2610-1 MYSTERY'
#<CheckData> '44 POTENTIA-2610-0 MYSTERY'
#<CheckData> '46 POTENTIA-2610-1 MYSTERY'
#<CheckData> '4C POTENTIA-2610-0 MYSTERY'
#<CheckData> '4E POTENTIA-2610-1 MYSTERY'
<CheckData>	'50 U67_EEPROM'
#<CheckData> '54 POTENTIA-2610-0 NVRAM'
<CheckData>	'55 SPD_EEPROM'
#<CheckData> '56 POTENTIA-2610-1 NVRAM'
#<CheckData> '5C POTENTIA-2610-0 MYSTERY'
#<CheckData> '5E POTENTIA-2610-1 MYSTERY'
#<CheckData> '64 POTENTIA-2610-0 MYSTERY'
#<CheckData> '66 POTENTIA-2610-1 MYSTERY'
#<CheckData> '6C POTENTIA-2610-0 SHADOW'
#<CheckData> '6E POTENTIA-2610-1 SHADOW'
<CheckData>	'70 9546'
#<CheckData> '74 POTENTIA-2610-0 NVRAM-X'
#<CheckData> '76 POTENTIA-2610-1 NVRAM-X'
<CheckData>	'7C POTENTIA-2610-0 CTL/STAT'
<CheckData>	'7E POTENTIA-2610-1 CTL/STAT'
#<CheckData>	'local:    3 35 SPD_MYSTERY'
<CheckData>	'50 U67_EEPROM'
<CheckData>	'54 FIC_EEPROM'
<CheckData>	'55 SPD_EEPROM'
<CheckData>	'57 U128_EEPROM'
<CheckData>	'70 9546'



<Send>		"set ver 0"
<TimeOut>	2
<Wait>
