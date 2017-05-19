################################################################################
#
# Module:      Chassis_test_Fan_TACH.inc
#
# Author:      Joe White
#
# Descr:       Test Chassis Fan operation
#
# Version:    1.1 $Id: Chassis_test_Fan_TACH.inc,v 1.3 2008/02/20 22:03:49 joe Exp $
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

<Bypass> 	$Slot_INST_GBL[21]
	<Msg>	"Check Fan 1 TACH Speeds"
	<Msg>	"Fan 1 One fan On, Low Speed"
	<Send> "wr i2c 9501 fan1 gpio 47"
	<Wait>
	<Sleep>	4
	<Include>	Chassis_test_config_Fan1.inc
	<Sleep>	4
	<Send>	"rd i2c adm 1 70"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_21_A_FAN_A_OFF_FAN_B_ON_LOW
	<Send>	"rd i2c adm 1 71"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_21_B_FAN_A_OFF_FAN_B_ON_LOW

	<Msg>	"Fan 1 1 Fan on, High Speed"
	<Send> "wr i2c 9501 fan1 gpio C7"
	<Wait>
	<Sleep>	4
	<Include>	Chassis_test_config_Fan1.inc
	<Sleep>	4
	<Send>	"rd i2c adm 1 70"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_21_A_FAN_A_OFF_FAN_B_ON_HIGH
	<Send>	"rd i2c adm 1 71"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_21_B_FAN_A_OFF_FAN_B_ON_HIGH



	<Msg>	"Fan 1 2 Fans on, Low Speed"
	<Send> "wr i2c 9501 fan1 gpio 67"
	<Wait>
	<Sleep>	4
	<Include>	Chassis_test_config_Fan1.inc
	<Sleep>	4
	<Send>	"rd i2c adm 1 70"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_21_A_FAN_A_ON_FAN_B_ON_LOW
	<Send>	"rd i2c adm 1 71"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_21_B_FAN_A_ON_FAN_B_ON_LOW



	<Msg>	"Fan 1 2 Fans on, High Speed"
	<Send> "wr i2c 9501 fan1 gpio E7"
	<Wait>
	<Sleep>	4
	<Include>	Chassis_test_config_Fan1.inc
	<Sleep>	4
	<Send>	"rd i2c adm 1 70"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_21_A_FAN_A_ON_FAN_B_ON_HIGH
	<Send>	"rd i2c adm 1 71"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_21_B_FAN_A_ON_FAN_B_ON_HIGH

	<Msg>	"Fan 1 1 Fan on, Low Speed"
	<Send> "wr i2c 9501 fan1 gpio 47"
	<Wait>
	<Sleep>	4
</Bypass>

<Bypass> 	$Slot_INST_GBL[22]
	<Msg>	"Check Fan 2 TACH Speeds"
	<Msg>	"Fan 2 One fan On, Low Speed"
	<Send> "wr i2c 9501 fan2 gpio 47"
	<Wait>
	<Sleep>	4
	<Include>	Chassis_test_config_Fan2.inc
	<Sleep>	4
	<Send>	"rd i2c adm 2 70"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_22_A_FAN_A_OFF_FAN_B_ON_LOW
	<Send>	"rd i2c adm 2 71"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_22_B_FAN_A_OFF_FAN_B_ON_LOW

	<Msg>	"Fan 2 1 Fan on, High Speed"
	<Send> "wr i2c 9501 fan2 gpio C7"
	<Wait>
	<Sleep>	4
	<Include>	Chassis_test_config_Fan2.inc
	<Sleep>	4
	<Send>	"rd i2c adm 2 70"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_22_A_FAN_A_OFF_FAN_B_ON_HIGH
	<Send>	"rd i2c adm 2 71"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_22_B_FAN_A_OFF_FAN_B_ON_HIGH



	<Msg>	"Fan 2 2 Fans on, Low Speed"
	<Send> "wr i2c 9501 fan2 gpio 67"
	<Wait>
	<Sleep>	4
	<Include>	Chassis_test_config_Fan2.inc
	<Sleep>	4
	<Send>	"rd i2c adm 2 70"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_22_A_FAN_A_ON_FAN_B_ON_LOW
	<Send>	"rd i2c adm 2 71"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_22_B_FAN_A_ON_FAN_B_ON_LOW



	<Msg>	"Fan 2 2 Fans on, High Speed"
	<Send> "wr i2c 9501 fan2 gpio E7"
	<Wait>
	<Sleep>	4
	<Include>	Chassis_test_config_Fan2.inc
	<Sleep>	4
	<Send>	"rd i2c adm 2 70"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_22_A_FAN_A_ON_FAN_B_ON_HIGH
	<Send>	"rd i2c adm 2 71"
	<Wait>
	<Getdata>  Check_Chassis_TACH_FAN_22_B_FAN_A_ON_FAN_B_ON_HIGH
    <Send> "wr i2c 9501 fan1 gpio 47"
	<Wait>

	<Msg>	"Fan 2 1 Fan on, Low Speed"
	<Send> "wr i2c 9501 fan2 gpio 47"
	<Wait>
	<Sleep>	4
</Bypass>
