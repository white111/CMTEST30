################################################################################
#
# Module:      Check_IPMI_Chassis_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_PRE_BI.dat, BI, POST, Config
#
# Version:    1.1  $Id: Check_IPMI_Chassis_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 11/23/11
#				Changed Send to Sendslow due to diag bug
#		        Added a Sleep 5 due to some meessages comming in the middle of a comand output
#				Added Sleep messages due to hangs foud at reboot 8/8/12
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################
<Prompt>	">"
<Timeout>	20
<sendSlow>		"pfeffa"
<Wait>

<sendSlow>		"show ver"
<Wait>

<sendSlow>		"show ver"
<Wait>

<Msg>		"Check Chassis U200"

<Sendslow>		"rd i2c 9501 u200 gpio"
<Wait>
<GetData>   U200
 <Bypass> $P20_INSTALLED_GBL

	<CheckData>		'83'
	<CheckDataX>		'C3'
	<CheckDataX>		'C2'
	#<CheckDataX>	'00'
	<CheckDataX>	'FF'
</Bypass>


<Msg>		"Check Chassis I2C IPMI A comunications.."
#<sendSlow>		'w8 f400001f 01'
#<Wait>
<sendSlow>		'r8 f400001f'
<Wait>
<GetData>
<CheckData>	'F400001F   09'

<Msg>		"Check Chassis IPMI"
<sendSlow>		"rd i2c 9501 chassis tlv"
<Wait>
<GetData>
<CheckData>	'SERIAL NUMBER .*BLOCK'
<Bypass>	$Slot_INST_GBL[21]
	<Msg>		"Check FAN1(RIGHT) IPMI"
	<sendSlow>		"rd i2c 9501 fan1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[22]
	<Msg>		"Check FAN2(LEFT) IPMI"
	<sendSlow>		"rd i2c 9501 fan2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[18]
	<Msg>		"Check PEM1(RIGHT) IPMI"
	<sendSlow>		"rd i2c 9501 pem1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[19]
	<Msg>		"Check PEM2(LEFT) IPMI"
	<sendSlow>		"rd i2c 9501 pem2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[15]
	<Msg>		"Check Alarm1(Right) IPMI"
	<sendSlow>		"rd i2c 9501 alarm1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[16]
	<Msg>		"Check Alarm2(Left) IPMI"
	<sendSlow>		"rd i2c 9501 alarm2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[1]
	<Msg>		"Check Slot 0 IPMI"
	<sendSlow>		"rd i2c 9501 0 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[2]
	<Msg>		"Check Slot 1 IPMI"
	<sendSlow>		"rd i2c 9501 1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[3]
	<Msg>		"Check Slot 2 IPMI"
	<sendSlow>		"rd i2c 9501 2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[4]
	<Msg>		"Check Slot 3 IPMI"
	<sendSlow>		"rd i2c 9501 3 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[5]
	<Msg>		"Check Slot 4 IPMI"
	<sendSlow>		"rd i2c 9501 4 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$HA_Session
    <Msg>	"Disable IMC Slot 1 Master Arbitration"
 	<sendSlow>	'on 1 w8 F4000028 01'
 	<wait>
	<sendSlow>		'on 1 r8 F4000028'
	<Wait>
	<GetData>
	<CheckData>	'F4000028   01'
</Bypass>

<Msg>		"Change Chassis I2C to IPMI B comunications.."
<sendSlow>		'w8 f400001f 07'
<Wait>
<sendSlow>		'r8 f400001f'
<Wait>
<GetData>
<CheckData>	'F400001F   07'
<Sleep>		10
<Msg>		"Check Chassis IPMI"
<Sleep>		5
<sendSlow>		"rd i2c 9501 chassis tlv"
<Wait>
<GetData>
<CheckData>	'SERIAL NUMBER .*BLOCK'
<Bypass>	$Slot_INST_GBL[21]
	<Msg>		"Check FAN1(RIGHT) IPMI"
	<sendSlow>		"rd i2c 9501 fan1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[22]
	<Msg>		"Check FAN2(LEFT) IPMI"
	<sendSlow>		"rd i2c 9501 fan2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[18]
	<Msg>		"Check PEM1(RIGHT) IPMI"
	<sendSlow>		"rd i2c 9501 pem1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[19]
	<Msg>		"Check PEM2(LEFT) IPMI"
	<sendSlow>		"rd i2c 9501 pem2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[15]
	<Msg>		"Check Alarm1(Right) IPMI"
	<sendSlow>		"rd i2c 9501 alarm1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[16]
	<Msg>		"Check Alarm2(Left) IPMI"
	<sendSlow>		"rd i2c 9501 alarm2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[1]
	<Msg>		"Check Slot 0 IPMI"
	<sendSlow>		"rd i2c 9501 0 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[2]
	<Msg>		"Check Slot 1 IPMI"
	<sendSlow>		"rd i2c 9501 1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[3]
	<Msg>		"Check Slot 2 IPMI"
	<sendSlow>		"rd i2c 9501 2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[4]
	<Msg>		"Check Slot 3 IPMI"
	<sendSlow>		"rd i2c 9501 3 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[5]
	<Msg>		"Check Slot 4 IPMI"
	<sendSlow>		"rd i2c 9501 4 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Msg>		"Change Chassis I2C to IPMI A comunications.."
<sendSlow>		'w8 f400001f 01'
<Wait>
#Added getting some XGLC boot messages in the middle of the command below
<Sleep> 6
<sendSlow>		'r8 f400001f'
<Wait>
<GetData>
<CheckData>	'F400001F   09'


<Bypass>	$HA_Session
	<Msg>		"Check IMC Slot 1 IPMI"
	<Msg>	"Make IMC in slot 1 Master"
	<sendSlow>	"w8 F4000028   01"
	<Wait>
	#Arb other card to master
	<sendSlow>	"on 1 w8 F4000028   07"
	<Wait>
	<sendSlow>  "r8 F4000028"
	<Wait>
	<CheckData>	"F4000028   01"
	<GetData>

	<Exec>	Swap_cons

	<sendSlow>
	<sendSlow>	"pfeffa"
	<Wait>

    <Msg>	"Check IMC Slot 1 Master"
    <sendSlow>  "r8 F4000028"
	<Wait>

	<CheckData>	"F4000028   07"

	<Msg>		"Check Chassis U200"


	<sendSlow>		"rd i2c 9501 U200 GPIO"
	<Wait>
	<GetData>   U200
	<CheckData>		'83'
	<CheckDataX>		'C3'
	<CheckDataX>		'C2'
	#<CheckDataX>	'00'
	<CheckDataX>	'FF'


	<Msg>		"Check Chassis I2C IPMI B comunications.."
	#<sendSlow>		'w8 f400001f 01'
	#<Wait>
	<sendSlow>		'r8 f400001f'
	<Wait>
	<GetData>
	# Swap enabled
	<CheckData>	'F400001F   01'

	<Msg>		"Check Chassis IPMI"
	<sendSlow>		"rd i2c 9501 chassis tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'


 	<Msg>		"Change Chassis I2C to IPMI A comunications.."
	<sendSlow>		'w8 f400001f 07'
	<Wait>
	<sendSlow>		'r8 f400001f'
	<Wait>
	<GetData>
	# Swap + buffer swap enabled
	<CheckData>	'F400001F   0F'

	<Msg>		"Check Chassis IPMI"
	<sendSlow>		"rd i2c 9501 chassis tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'

	<Msg>		"Change Chassis I2C to IPMI B comunications.."
	<sendSlow>		'w8 f400001f 01'
	<Wait>
	<sendSlow>		'r8 f400001f'
	<Wait>
	<GetData>
	<CheckData>	'F400001F   01'

	<Msg>	"Make IMC in slot 0 Master"
	<sendSlow>	"w8 F4000028   01"
	<Wait>
	<sendSlow>	"on 0 w8 F4000028 07"
	<Wait>
	<sendSlow>  "r8 F4000028"
	<Wait>
	<CheckData>	"F4000028   01"
	<GetData>

	<Prompt>	"#"
	<Timeout>	20
	<sendSlow>		"exit"
	<Wait>

	<Exec>	Swap_cons
    <Prompt>	">"
    <Msg>	"Check IMC Slot 0 Master"
    <sendSlow>
    <Wait>
    <sendSlow>  "r8 F4000028"
	<Wait>
	<CheckData>	"F4000028   07"
</Bypass>
<Sleep>		5

<Prompt>	"^[#|slot ..>]"
<Timeout>	20
<sendSlow>		"exit"
#<Sleep>		2
<Wait>
