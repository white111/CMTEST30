################################################################################
#
# Module:      check_chassis_i2c.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI.dat
#
# Version:    1.0  $Id: check_chassis_i2c.inc,v 1.2 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Depreciated
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
##############################################################################
# Done at the Noodle level
<Prompt>	"#"
<TimeOut>	3
<Msg>		"Check Chassis I2C PMIA comunications.."
<Send>		"pfeffa rd i2c 9501 chassis tlv"
<Wait>
<CheckData>	'SERIAL NUMBER BLOCK'

<Msg>		"Check Chassis I2C PMIB comunications.."
<Send>		'pfeffa w8 f400001f 07'
<Wait>
<Send>		'pfeffa r8 f400001f'
<Wait>
<CheckData>	'F400001F   07'

<Send>		"pfeffa rd i2c 9501 chassis tlv"
<Wait>
<CheckData>	'SERIAL NUMBER BLOCK'

<Msg>		"Change Chassis I2C to PMIA comunications.."
<Send>		'pfeffa w8 f400001f 01'
<Wait>
<Send>		'pfeffa r8 f400001f'
<Wait>
<CheckData>	'F400001F   09'

<Msg>		"Check Chassis U200"
<Send>		"pfeffa rd i2c 9501 U200 GPIO"
<Wait>
<CheckData>		'C3'
<CheckDataX>		'C2'
#<CheckDataX>	'00'
<CheckDataX>	'FF'



