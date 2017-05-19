################################################################################
#
# Module:      Chassis_test_Alarm.inc
#
# Author:      Joe White
#
# Descr:       Test Chassis Fan operation
#
# Version:    1.3 $Id: Chassis_test_Alarm.inc,v 1.5 2011/01/21 18:38:55 joe Exp $
#
# Changes:    Created 11/1/06
#			  Added Change for Bug 14781 7/28/10 , Added Second Alarm Card 1/21/11
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################
<Bypass> 	$Slot_INST_GBL[15]
	<SendSlow> "wr i2c 9501 alarm1 gpio a3"
	#; Disable all, Added for Bug 14781 7/28/10
	<Wait>
	<Msg>	"Check Alarm 1"
	<SendSlow> "sho alarm 1"
	<Wait>
	<GetData>
	<CheckData>	"ALARM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = a3"

	<Msg>	"Check Verify Critical Alarm"
	#A3 xor 04, set critical alarm
	<Send> "wr i2c 9501 alarm1 gpio A7"
	<Wait>
	<SendSlow> "sho alarm 1"
	<Wait>
	<CheckData>	"ALARM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = a7"
    <Getdata> Verify_Chassis_LED_ALARM1_CRITICAL_ALARM

	<Msg>	"Check Verify Major Alarm"
	#A3 xor 08 set major alarm
	<Send> "wr i2c 9501 alarm1 gpio AB"
	<Wait>
	<SendSlow> "sho alarm 1"
	<Wait>
	<CheckData>	"ALARM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = ab"
    <Getdata> Verify_Chassis_LED_ALARM1_MAJOR_ALARM

	<Msg>	"Check Verify Minor Alarm"
	#A3 xor 10 ,set minor alarm
	<Send> "wr i2c 9501 alarm1 gpio B3"
	<Wait>
	<SendSlow> "sho alarm 1"
	<Wait>
	<CheckData>	"ALARM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = b3"
    <Getdata> Verify_Chassis_LED_ALARM1_MINOR_ALARM

	<Msg>	"Clear Alarms and Disable ACO Switch"
	#A3 xor 10 ,set minor alarm
	<Send> "wr i2c 9501 alarm1 gpio 83"
	<Wait>
	<SendSlow> "sho alarm 1"
	<Wait>
	<CheckData>	"ALARM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = 83"
    <Getdata> Verify_Chassis_LED_ALARM1_ACO_OFF

	<Msg>	"Clear Alarms and Enable ACO Switch"
	#A3 xor 10 ,set minor alarm
	<Send> "wr i2c 9501 alarm1 gpio A3"
	<Wait>
	<SendSlow> "sho alarm 1"
	<Wait>
	<CheckData>	"ALARM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = a3"
    <Getdata> Verify_Chassis_LED_ALARM1_ACO_ON

    <Msg>	'Check for ACO Button Push"
	<SendSlow> "sho alarm 1"
	<Wait>
	<CheckData>	"ALARM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = e3"
    <Getdata>

	<Msg>	"Clear Alarms"
	#A3 xor 10 ,set minor alarm
	<Send> "wr i2c 9501 alarm1 gpio 83"
	<Wait>
	<SendSlow> "sho alarm 1"
	<Wait>
	<CheckData>	"ALARM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = 83"
    <Getdata> Verify_Chassis_LED_ALARM1_OFF
</Bypass>

<Bypass> 	$Slot_INST_GBL[16]
	<SendSlow> "wr i2c 9501 alarm2 gpio a3"
	#; Disable all, Added for Bug 14781 7/28/10
	<Wait>
	<Msg>	"Check Alarm 2"
	<SendSlow> "sho alarm 2"
	<Wait>
	<GetData>
	<CheckData>	"ALARM CARD 2 .on the LEFT viewed from front. 9501 I/Os = a3"

	<Msg>	"Check Verify Critical Alarm"
	#A3 xor 04, set critical alarm
	<Send> "wr i2c 9501 alarm2 gpio A7"
	<Wait>
	<SendSlow> "sho alarm 2"
	<Wait>
	<CheckData>	"ALARM CARD 2 .on the LEFT viewed from front. 9501 I/Os = a7"
    <Getdata> Verify_Chassis_LED_ALARM2_CRITICAL_ALARM

	<Msg>	"Check Verify Major Alarm"
	#A3 xor 08 set major alarm
	<Send> "wr i2c 9501 alarm2 gpio AB"
	<Wait>
	<SendSlow> "sho alarm 2"
	<Wait>
	<CheckData>	"ALARM CARD 2 .on the LEFT viewed from front. 9501 I/Os = ab"
    <Getdata> Verify_Chassis_LED_ALARM2_MAJOR_ALARM

	<Msg>	"Check Verify Minor Alarm"
	#A3 xor 10 ,set minor alarm
	<Send> "wr i2c 9501 alarm2 gpio B3"
	<Wait>
	<SendSlow> "sho alarm 2"
	<Wait>
	<CheckData>	"ALARM CARD 2 .on the LEFT viewed from front. 9501 I/Os = b3"
    <Getdata> Verify_Chassis_LED_ALARM2_MINOR_ALARM

	<Msg>	"Clear Alarms and Disable ACO Switch"
	#A3 xor 10 ,set minor alarm
	<Send> "wr i2c 9501 alarm2 gpio 83"
	<Wait>
	<SendSlow> "sho alarm 2"
	<Wait>
	<CheckData>	"ALARM CARD 2 .on the LEFT viewed from front. 9501 I/Os = 83"
    <Getdata> Verify_Chassis_LED_ALARM2_ACO_OFF

	<Msg>	"Clear Alarms and Enable ACO Switch"
	#A3 xor 10 ,set minor alarm
	<Send> "wr i2c 9501 alarm2 gpio A3"
	<Wait>
	<SendSlow> "sho alarm 2"
	<Wait>
	<CheckData>	"ALARM CARD 2 .on the LEFT viewed from front. 9501 I/Os = a3"
    <Getdata> Verify_Chassis_LED_ALARM2_ACO_ON

	<Msg>	"Clear Alarms"
	#A3 xor 10 ,set minor alarm
	<Send> "wr i2c 9501 alarm2 gpio 83"
	<Wait>
	<SendSlow> "sho alarm 2"
	<Wait>
	<CheckData>	"ALARM CARD 2 .on the LEFT viewed from front. 9501 I/Os = 83"
    <Getdata> Verify_Chassis_LED_ALARM2_OFF
</Bypass>



