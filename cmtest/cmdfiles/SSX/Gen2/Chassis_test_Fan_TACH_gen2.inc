################################################################################
#
# Module:      Chassis_test_Fan_TACH_gen2.inc
#
# Author:      Joe White
#
# Descr:       Test Chassis Fan operation
#
# Version:    1.1 $Id: Chassis_test_Fan_TACH.inc,v 1.3 2008/02/20 22:03:49 joe Exp $
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

<Bypass> 	$Slot_INST_GBL[21]
	<Msg>	"Check Fan 1 TACH Speeds"
	<Msg>	"Fan 1, Low Speed"
	<Send> "wr i2c adm1029 1 60 55"
	<Wait>
	<Sleep>	4
	<Include>	Chassis_test_config_Fan1_gen2.inc
	<Sleep>	8
	<Send>	"rd i2c adm 1 70"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN2_21_LOW
	<Send>	"rd i2c adm 1 71"
	<Wait>
	<Getdata>

	<Msg>	"Fan 1, High Speed"
	<Send> "wr i2c adm1029 1 60 FF"
	<Wait>
	<Sleep>	12
	<Send>	"rd i2c adm 1 70"
	<Wait>
	<Getdata>   Check_Chassis_TACH_FAN2_21_HIGH
	<Send>	"rd i2c adm 1 71"
	<Wait>
	<Getdata>
	<Sleep>	4

	<Msg>	"Fan 1, Low Speed"
	<Send> "wr i2c adm1029 1 60 55"
	<Wait>
	<Sleep>	4
</Bypass>

<Bypass> 	$Slot_INST_GBL[22]
	<Msg>	"Check Fan 2 TACH Speeds"
	<Msg>	"Fan 2, Low Speed"
	<Send> "wr i2c adm1029 2 60 55"
	<Wait>
	<Sleep>	4
	<Include>	Chassis_test_config_Fan2_gen2.inc
	<Sleep>	8
	<Send>	"rd i2c adm 2 70"
	<Wait>
	<Getdata>   Check_Chassis_TACH_FAN2_22_LOW
	<Send>	"rd i2c adm 2 71"
	<Wait>
	<Getdata>

	<Msg>	"Fan 2, High Speed"
	<Send> "wr i2c adm1029 2 60 FF"
	<Wait>
	<Sleep>	12
	<Send>	"rd i2c adm 2 70"
	<Wait>
	<Getdata>   Check_Chassis_TACH_FAN2_22_HIGH
	<Send>	"rd i2c adm 2 71"
	<Wait>
	<Getdata>


	<Msg>	"Fan 2, Low Speed"
	<Send> "wr i2c adm1029 2 60 55"
	<Wait>
	<Sleep>	4
</Bypass>
