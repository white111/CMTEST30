################################################################################
#
# Module:      Check_GLC_thermal.inc
#
# Author:      Joe White
#
# Descr:       Display Thermal sensors for IMC and GLC
#
# Version:    1.3 $Id: Check_GLC_thermal.inc,v 1.2 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Created from check_glc_thermal.inc 1/22/07
#			  Added Checks for Temp alarms(IXP always in alarm) 011607
#              Fixes for faster serial ports 4/3/12
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2007-2008 Stoke. All rights reserved.
#
################################################################################

# Done at the Noodle level
<Prompt>	"slot 2"
<TimeOut>	3
<Msg>		"Check Thermal sensors..."
<Send>		"show thermal"
<Wait>
<GetData>	GLC_Thermal
<Msg>		"Check Default Temp Alarms..."
<Send>		"r8 f4000017"
<Wait>
<CheckData> "F4000017   18"
<Msg>		"Check Inlet Temp alarm..."
<Send>		"wr i2c temp inlet 01 0F"
<Wait>
<GetData>
<Send>		"r8 f4000017"
<Wait>
<CheckData> "F4000017   19"
<GetData>
<Msg>		"Check Outlet Temp alarm..."
<Send>		"wr i2c temp outlet 01 0F"
<Wait>
<GetData>
<Send>		"r8 f4000017"
<Wait>
<CheckData> "F4000017   1B"
<GetData>
<Msg>		"Check PPC Temp alarm..."
<Send>		"wr i2c temp ppc 13 00"
<Wait>
<GetData>
<Send>		"r8 f4000017"
<Wait>
<CheckData> "F4000017   1F"
<GetData>

#Typical numbers at room temp
# Tppci   =  26     C
#TppcRem1=  46     C
#TppcRem2=  37     C
#TppcRem3=   0     C
#TppcRem4=   0     C
#Tixpi   =  37.000 C
#Tixpe   = 255.035 C  <=== Non fuctional due to IXP issues
#Tinlet  =  42.0   C
#Toutlet =  29.5   C

