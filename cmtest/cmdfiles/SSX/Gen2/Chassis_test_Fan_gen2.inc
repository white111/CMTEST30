################################################################################
#
# Module:      Chassis_test_Fan_gen2.inc
#
# Author:      Joe White
#
# Descr:       Test Chassis Fan operation
#
# Version:    1.2 $Id: Chassis_test_Fan.inc,v 1.4 2008/12/02 01:42:02 joe Exp $
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
	<Msg>	"Check Fan 1 GPIO"
	<Send> "sho fan 1 gpios"
	<Wait>
	#<Sleep>	1
	<Getdata>
	<Checkdata>	"FAN CARD 1 .on the RIGHT viewed from front. 9501 I/Os = 47"
	<Sendslow> "rd i2c 9501 fan1 gpio"
	<Wait>

	<GetData>
</Bypass>

<Bypass> 	$Slot_INST_GBL[22]
	<Msg>	"Check Fan 2 GPIO"
	<Send> "sho fan 2 gpios"
	<Wait>
	#<Sleep>	1
	<Getdata>
	<Checkdata>	"FAN CARD 2 .on the LEFT viewed from front. 9501 I/Os = 47"
	<Sendslow> "rd i2c 9501 fan2 gpio"
	<Wait>

	<GetData>
</Bypass>

<Bypass> 	$Slot_INST_GBL[21]
	<Msg>	"Check Fan 1 GPIO FF"
	<Send>	"wr i2c 9501 fan1 gpio ff"
	<Wait>
	<Send> "sho fan 1 gpios"
	<Wait>
	#<Sleep>	1
	<Getdata>
	<Checkdata>	"FAN CARD 1 .on the RIGHT viewed from front. 9501 I/Os = e7"
	<Sendslow> "rd i2c 9501 fan1 gpio"
	<Wait>

	<GetData>
	<Send>	"wr i2c 9501 fan1 gpio 47"
	<Wait>
	<Send> "wr i2c adm1029 1 60 55"
	<Wait>
	<Sleep>	4
</Bypass>

<Bypass> 	$Slot_INST_GBL[22]
	<Msg>	"Check Fan 2 GPIO FF"
	<Send>	"wr i2c 9501 fan2 gpio ff"
	<Wait>
	<Send> "sho fan 2 gpios"
	<Wait>
	#<Sleep>	1
	<Getdata>
	<Checkdata>	"FAN CARD 2 .on the LEFT viewed from front. 9501 I/Os = e7"
	<Sendslow> "rd i2c 9501 fan2 gpio"
	<Wait>

	<GetData>
	<Send>	"wr i2c 9501 fan2 gpio 47"
	<Wait>
</Bypass>

<Bypass> 	$Slot_INST_GBL[21]
	<Msg>	"Verify Fan 1 3.3v LED GREEN"
	<Send>	"wr i2c 9501 fan1 gpio 47"
	<Wait>
	<Send> "sho fan 1 gpios"
	<Wait>
	<GetData>
	<Checkdata>	"FAN CARD 1 .on the RIGHT viewed from front. 9501 I/Os = 47"
	#<Sleep>	1
	<Sendslow> "rd i2c 9501 fan1 gpio"
	<Wait>
	<GetData>

	<Getdata> Verify_Chassis_LED_FAN1_3V3_GREEN
</Bypass>

<Bypass> 	$Slot_INST_GBL[21]
	<Msg>	"Verify Fan 1 3.3v LED RED"
	<Send>	"wr i2c 9501 fan1 gpio 43"
	<Wait>
	<Send> "sho fan 1 gpios"
	<Wait>
	#<Sleep>	1
	<GetData>
	<Checkdata>	"FAN CARD 1 .on the RIGHT viewed from front. 9501 I/Os = 43"
	<Sendslow> "rd i2c 9501 fan1 gpio"
	<Wait>
	<GetData>

	<Getdata> Verify_Chassis_LED_FAN1_3V3_RED
</Bypass>

<Bypass> 	$Slot_INST_GBL[21]
	<Msg>	"Verify Fan 1 OK LED GREEN"
	<Send>	"wr i2c 9501 fan1 gpio 47"
	<Wait>
	<Send> "sho fan 1 gpios"
	<Wait>
	#<Sleep>	1
	<GetData>
	<Checkdata>	"FAN CARD 1 .on the RIGHT viewed from front. 9501 I/Os = 47"
	<Sendslow> "rd i2c 9501 fan1 gpio"
	<Wait>
	<GetData>

	<Getdata> Verify_Chassis_LED_FAN1_OK_GREEN
</Bypass>

<Bypass> 	$Slot_INST_GBL[21]
	<Msg>	"Verify Fan 1 OK LED RED"
	<Send>	"wr i2c adm 1 28 2"
	<Wait>
	<Send> "sho fan 1 gpios"
	<Wait>
	#<Sleep>	1
	<GetData>
	<Checkdata>	"FAN CARD 1 .on the RIGHT viewed from front. 9501 I/Os = 47"
	<Sendslow> "rd i2c adm 1 28"
	<Wait>
	<GetData>
	<Checkdata>	"02"
	<Getdata> Verify_Chassis_LED_FAN1_OK_RED
	<Send> "wr i2c adm1029 1 60 55"
	<Wait>

</Bypass>


<Bypass> 	$Slot_INST_GBL[22]
	<Msg>	"Verify Fan 2 3.3v LED GREEN"
	<Send>	"wr i2c 9501 fan2 gpio 47"
	<Wait>
	<Send> "sho fan 2 gpios"
	<Wait>
	<GetData>
	<Checkdata>	"FAN CARD 2 .on the LEFT viewed from front. 9501 I/Os = 47"
	#<Sleep>	1
	<Sendslow> "rd i2c 9501 fan2 gpio"
	<Wait>
	<GetData>

	<Getdata> Verify_Chassis_LED_FAN2_3V3_GREEN
</Bypass>

<Bypass> 	$Slot_INST_GBL[22]
	<Msg>	"Verify Fan 2 3.3v LED RED"
	<Send>	"wr i2c 9501 fan2 gpio 43"
	<Wait>
	<Send> "sho fan 2 gpios"
	<Wait>
	#<Sleep>	1
	<GetData>
	<Checkdata>	"FAN CARD 2 .on the LEFT viewed from front. 9501 I/Os = 43"
	<Sendslow> "rd i2c 9501 fan2 gpio"
	<Wait>
	<GetData>

	<Getdata> Verify_Chassis_LED_FAN2_3V3_RED
</Bypass>

<Bypass> 	$Slot_INST_GBL[22]
	<Msg>	"Verify Fan 2 OK LED GREEN"
	<Send>	"wr i2c 9501 fan2 gpio 47"
	<Wait>
	<Send> "sho fan 2 gpios"
	<Wait>
	#<Sleep>	1
	<GetData>
	<Checkdata>	"FAN CARD 2 .on the LEFT viewed from front. 9501 I/Os = 47"
	<Sendslow> "rd i2c 9501 fan2 gpio"
	<Wait>
	<GetData>

	<Getdata> Verify_Chassis_LED_FAN2_OK_GREEN
</Bypass>

<Bypass> 	$Slot_INST_GBL[22]
	<Msg>	"Verify Fan 2 OK LED RED"
	<Send>	"wr i2c adm 2 28 2"
	<Wait>
	<Send> "sho fan 2 gpios"
	<Wait>
	#<Sleep>	1
	<GetData>
	<Sendslow> "rd i2c adm 2 28"
	<Wait>
	<GetData>
	<Checkdata>	"02"
	<Getdata> Verify_Chassis_LED_FAN2_OK_RED
	<Send> "wr i2c adm1029 2 60 55"
	<Wait>

</Bypass>


