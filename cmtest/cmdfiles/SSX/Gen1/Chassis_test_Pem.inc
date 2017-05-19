################################################################################
#
# Module:      Chassis_test_Pem.inc
#
# Author:      Joe White
#
# Descr:       Test Chassis Fan operation
#
# Version:    1.1 $Id: Chassis_test_Pem.inc,v 1.3 2008/02/20 22:03:49 joe Exp $
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
<Bypass> 	$Slot_INST_GBL[18]
	<Msg>	'Check PEM 1'
	<Msg>	'Check PEM 1'
	<Send> 'sho pem 1'
	<Wait>
	<CheckData>	'PEM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = ef'
    <GetData>   Verify_Chassis_LED_PEM1_LED_GREEN

	<Msg>	'Check PEM 1'
	#ef xor A0
	<Send> 'wr i2c 9501 pem1 gpio 4F'
	<Wait>
	<Send> 'sho pem 1'
	<Wait>
	<CheckData>	'PEM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = 4f'
    <Getdata> Verify_Chassis_LED_PEM1_LED_RED

	<Msg>	'Check PEM 1'
	#ef xor A0
	<Send> 'wr i2c 9501 pem1 gpio EF'
	<Wait>
	<Send> 'sho pem 1'
	<Wait>
	<CheckData>	'PEM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = ef'
    <Getdata>
    <Send> 'wr i2c 9501 pem1 gpio EF'
	<Wait>
    # Dummy read, first read is incorrect
	<Send> 'r8 F4000029'
	<Wait>

	<Alert>	'Operator: Power off PEM 1 on the RIGHT viewed from front of chassis'
	<Send> 'sho pem 1'
	<Wait>
	<CheckData>	'PEM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = cf'
    <Getdata>
    <Bypass>   $P20_INSTALLED_GBL
    	<Msg>	'Check PEM trip status
    	<SendSlow> 'r8 F4000029'
		<Wait>
		<GetData>
		<CheckData> 'F4000029   04'
	</Bypass>

	<Alert>	Operator: Power on PEM 1 on the RIGHT viewed from front of chassis"
	<Send> "sho pem 1"
	<Wait>
	<CheckData>	"PEM CARD 1 .on the RIGHT viewed from front. 9501 I/Os = ef"
    <Getdata>
	<Bypass>   $P20_INSTALLED_GBL
    	<Msg>	"Check PEM trip status
    	<SendSlow> "r8 F4000029"
		<Wait>
		<GetData>
		<CheckData> "F4000029   00"
    </Bypass>

 </Bypass>

 <Bypass> 	$Slot_INST_GBL[19]
	<Msg>	"Check PEM 2"
	<Msg>	"Check PEM 2"
	<Send> "sho pem 2"
	<Wait>
	<CheckData>	"PEM CARD 2 .on the LEFT viewed from front. 9501 I/Os = ef"
    <GetData>   Verify_Chassis_LED_PEM2_LED_GREEN

	<Msg>	"Check PEM 2"
	#ef xor A0
	<Send> "wr i2c 9501 pem2 gpio 4F"
	<Wait>
	<Send> "sho pem 2"
	<Wait>
	<CheckData>	"PEM CARD 2 .on the LEFT viewed from front. 9501 I/Os = 4f"
    <Getdata> Verify_Chassis_LED_PEM2_LED_RED

	<Msg>	"Check PEM 2"
	#ef xor A0
	<Send> "wr i2c 9501 pem2 gpio EF"
	<Wait>
	<Send> "sho pem 2"
	<Wait>
	<CheckData>	"PEM CARD 2 .on the LEFT viewed from front. 9501 I/Os = ef"
    <Getdata>
    <Send> "wr i2c 9501 pem2 gpio EF"
	<Wait>
    # Dummy read, first read is incorrect
	<Send> "r8 F4000029"
	<Wait>

	<Alert>	"Operator: Power off PEM 2 on the LEFT viewed from front of chassis"
	<Send> "sho pem 2"
	<Wait>
	<CheckData>	"PEM CARD 2 .on the LEFT viewed from front. 9501 I/Os = cf"
    <Getdata>
    <Bypass>   $P20_INSTALLED_GBL
    	<Msg>	"Check PEM trip status
    	<SendSlow> "r8 F4000029"
		<Wait>
		<GetData>
		<CheckData> "F4000029   08"
	</Bypass>

	<Alert>	"Operator: Power on PEM 2 on the LEFT viewed from front of chassis"
	<Send> "sho pem 2"
	<Wait>
	<CheckData>	"PEM CARD 2 .on the LEFT viewed from front. 9501 I/Os = ef"
    <Getdata>
    <Bypass>   $P20_INSTALLED_GBL
    	<Msg>	"Check PEM trip status
    	<SendSlow> "r8 F4000029"
		<Wait>
		<GetData>
		<CheckData> "F4000029   00"
	</Bypass>

 </Bypass>
