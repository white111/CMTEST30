################################################################################
#
# Module:      check_thermal.inc
#
# Author:      Joe White
#
# Descr:       Check Thermal used by GLC IMC Program and bench tests
#
# Version:    1.1  $Id: check_thermal.inc,v 1.2 2008/02/20 22:03:49 joe Exp $
#
# Changes:
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	">"
<TimeOut>	3
<Msg>		"Check Thermal sensors..."
<Send>		"show thermal"
<Wait>
<GetData>	GLC_Thermal
#Typical numbers at room temp
# Tppci   =  26     C
#TppcRem1=  46     C
#TppcRem2=  37     C
#TppcRem3=   0     C
#TppcRem4=   0     C
#Tixpi   =  37.000 C
#Tixpe   = 255.035 C
#Tinlet  =  42.0   C
#Toutlet =  29.5   C

