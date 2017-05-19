################################################################################
#
# Module:      Chassis_test_config_Fan2.inc
#
# Author:      Joe White
#
# Descr:       Test Chassis Fan operation
#
# Version:    1.1 $Id: Chassis_test_config_Fan2.inc,v 1.2 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Created 11/1/06
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################
#<MSG> "Config Fan 2 Tach"

<Send> "wr i2c adm 2 3 3"
<Wait>
<Sleep>  1
<Send>  "wr i2c adm 2 68 ab"
<Wait>
<Sleep>  1
<Send>  "wr i2c adm 2 69 ab"
<Wait>
<Sleep>  1
<Send>  "wr i2c adm 2 1 94"
<Wait>
<Sleep>  1

