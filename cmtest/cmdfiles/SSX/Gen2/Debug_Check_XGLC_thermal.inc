################################################################################
#
# Module:      Check_XGLC_thermal.inc
#
# Author:      Joe White
#
# Descr:       Display Thermal sensors for IMC and GLC
#
# Version:    1.2 $Id: Check_XGLC_thermal.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 10/05/11
#			  03/05/12 Bypasing BMR status
#
#
# Includes:
#
# Still ToDo:
#              Test Tempurature alarms
#			Find and check all Temp sensors
#			Added Triden check - Need to add test
#			Added 12V brick(Shows Current as well) Need to add Check
#
#            Copyright (c) 2007-2012 Stoke. All rights reserved.
#
################################################################################

# Done at the Diag level
<Prompt>	"DIAG >"
<TimeOut>	3
<Msg>		"Check Thermal sensors..."
<Send>		"temp show"
<Wait>
<GetData>	Check_XGLC_Thermal

<Prompt>	"DIAG >"
<TimeOut>	3
<Msg>		"Check Thermal sensors..."
<Send>		"tdnt show temp"
<Wait>
<GetData>

<Msg>		 "Bypassing BMR Access"
<Prompt>    "DIAG >"
<TimeOut>   3
#<Msg>       "Skip..Check BMR power and thermal sensors..."
#<Send>      "bmrstatus"
#<Wait>
##<GetData>   Check_XGLC_BMR
#<GetData>





#<Msg>       "Check Default Temp Alarms..."
#<Send>      "r8 f4000017"
#<Wait>
#<CheckData> "F4000017   18"
#<Msg>       "Check Inlet Temp alarm..."
#<Send>      "wr i2c temp inlet 01 0F"
#<Wait>
#<GetData>
#<Send>      "r8 f4000017"
#<Wait>
#<CheckData> "F4000017   19"
#<GetData>
#<Msg>       "Check Outlet Temp alarm..."
#<Send>      "wr i2c temp outlet 01 0F"
#<Wait>
#<GetData>
#<Send>      "r8 f4000017"
#<Wait>
#<CheckData> "F4000017   1B"
#<GetData>
#<Msg>       "Check PPC Temp alarm..."
#<Send>      "wr i2c temp ppc 13 00"
#<Wait>
#<GetData>
#<Send>      "r8 f4000017"
#<Wait>
#<CheckData> "F4000017   1F"
#<GetData>

##Typical numbers at room temp
## Tppci   =  26     C
##TppcRem1=  46     C
##TppcRem2=  37     C
##TppcRem3=   0     C
##TppcRem4=   0     C
##Tixpi   =  37.000 C
##Tixpe   = 255.035 C  <=== Non fuctional due to IXP issues
##Tinlet  =  42.0   C
##Toutlet =  29.5   C

