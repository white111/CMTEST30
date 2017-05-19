################################################################################
#
# Module:      Chassis_test_config_Fan1_gen2.inc
#
# Author:      Joe White
#
# Descr:       Test Chassis Fan operation
#
# Version:    1.1  $Id: Chassis_test_config_Fan1.inc,v 1.2 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Created 02/06/13
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2013 Stoke. All rights reserved.
#
################################################################################
#<MSG> "Config Fan 1 Tach"

<Send> "wr i2c adm 1 3 3"
<Wait>
<Sleep>  1
<Send>  "wr i2c adm 1 68 ab"
<Wait>
<Sleep>  1
<Send>  "wr i2c adm 1 69 ab"
<Wait>
<Sleep>  1
<Send>  "wr i2c adm 1 1 94"
<Wait>
<Sleep>  1

