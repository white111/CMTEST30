################################################################################
#
# Module:      Check_IPMI_Chassis.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_PRE_BI.dat, BI, POST, Config
#
# Version:    1.4  $Id: Check_IPMI_Chassis.inc,v 1.7 2008/12/02 01:42:02 joe Exp $
#
# Changes:    Created 02/16/06
#			  Added IMPMI and U200 for Standby  10/12/06
#			  Updated for 4.0 software
#			  11/18/08 Bypass U200 when P20 not Installed(TLV 99 in IMC U67)
#			  Changed <Prompt>	"^#|^slot ..>"  modifed 11/13/12
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
<Prompt>	">"
<Timeout>	20
<Send>		"pfeffa"
<Wait>

<Msg>		"Check Chassis U200"

<Send>		"rd i2c 9501 U200 GPIO"
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
#<Send>		'w8 f400001f 01'
#<Wait>
<Send>		'r8 f400001f'
<Wait>
<GetData>
<CheckData>	'F400001F   09'

<Msg>		"Check Chassis IPMI"
<Send>		"rd i2c 9501 chassis tlv"
<Wait>
<GetData>
<CheckData>	'SERIAL NUMBER .*BLOCK'
<Bypass>	$Slot_INST_GBL[21]
	<Msg>		"Check FAN1(RIGHT) IPMI"
	<Send>		"rd i2c 9501 fan1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[22]
	<Msg>		"Check FAN2(LEFT) IPMI"
	<Send>		"rd i2c 9501 fan2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[18]
	<Msg>		"Check PEM1(RIGHT) IPMI"
	<Send>		"rd i2c 9501 pem1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[19]
	<Msg>		"Check PEM2(LEFT) IPMI"
	<Send>		"rd i2c 9501 pem2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[15]
	<Msg>		"Check Alarm1(Right) IPMI"
	<Send>		"rd i2c 9501 alarm1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[16]
	<Msg>		"Check Alarm2(Left) IPMI"
	<Send>		"rd i2c 9501 alarm2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[1]
	<Msg>		"Check Slot 0 IPMI"
	<Send>		"rd i2c 9501 0 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[2]
	<Msg>		"Check Slot 1 IPMI"
	<Send>		"rd i2c 9501 1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[3]
	<Msg>		"Check Slot 2 IPMI"
	<Send>		"rd i2c 9501 2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[4]
	<Msg>		"Check Slot 3 IPMI"
	<Send>		"rd i2c 9501 3 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[5]
	<Msg>		"Check Slot 4 IPMI"
	<Send>		"rd i2c 9501 4 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$HA_Session
    <Msg>	"Disable IMC Slot 1 Master Arbitration"
 	<Send>	'on 1 w8 F4000028 01'
 	<wait>
	<Send>		'on 1 r8 F4000028'
	<Wait>
	<GetData>
	<CheckData>	'F4000028   01'
</Bypass>

<Msg>		"Change Chassis I2C to IPMI B comunications.."
<Send>		'w8 f400001f 07'
<Wait>
<Send>		'r8 f400001f'
<Wait>
<GetData>
<CheckData>	'F400001F   07'
<Sleep>		10
<Msg>		"Check Chassis IPMI"
<Send>		"rd i2c 9501 chassis tlv"
<Wait>
<GetData>
<CheckData>	'SERIAL NUMBER .*BLOCK'
<Bypass>	$Slot_INST_GBL[21]
	<Msg>		"Check FAN1(RIGHT) IPMI"
	<Send>		"rd i2c 9501 fan1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[22]
	<Msg>		"Check FAN2(LEFT) IPMI"
	<Send>		"rd i2c 9501 fan2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[18]
	<Msg>		"Check PEM1(RIGHT) IPMI"
	<Send>		"rd i2c 9501 pem1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[19]
	<Msg>		"Check PEM2(LEFT) IPMI"
	<Send>		"rd i2c 9501 pem2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[15]
	<Msg>		"Check Alarm1(Right) IPMI"
	<Send>		"rd i2c 9501 alarm1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>
<Bypass>	$Slot_INST_GBL[16]
	<Msg>		"Check Alarm2(Left) IPMI"
	<Send>		"rd i2c 9501 alarm2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[1]
	<Msg>		"Check Slot 0 IPMI"
	<Send>		"rd i2c 9501 0 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[2]
	<Msg>		"Check Slot 1 IPMI"
	<Send>		"rd i2c 9501 1 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[3]
	<Msg>		"Check Slot 2 IPMI"
	<Send>		"rd i2c 9501 2 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[4]
	<Msg>		"Check Slot 3 IPMI"
	<Send>		"rd i2c 9501 3 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Bypass>	$Slot_INST_GBL[5]
	<Msg>		"Check Slot 4 IPMI"
	<Send>		"rd i2c 9501 4 tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'
</Bypass>

<Msg>		"Change Chassis I2C to IPMI A comunications.."
<Send>		'w8 f400001f 01'
<Wait>
<Send>		'r8 f400001f'
<Wait>
<GetData>
<CheckData>	'F400001F   09'


<Bypass>	$HA_Session
	<Msg>		"Check IMC Slot 1 IPMI"
	<Msg>	"Make IMC in slot 1 Master"
	<Send>	"w8 F4000028   01"
	<Wait>
	#Arb other card to master
	<Send>	"on 1 w8 F4000028   07"
	<Wait>
	<Send>  "r8 F4000028"
	<Wait>
	<CheckData>	"F4000028   01"
	<GetData>

	<Exec>	Swap_cons

	<Send>
	<Send>	"pfeffa"
	<Wait>

    <Msg>	"Check IMC Slot 1 Master"
    <Send>  "r8 F4000028"
	<Wait>

	<CheckData>	"F4000028   07"

	<Msg>		"Check Chassis U200"


	<Send>		"rd i2c 9501 U200 GPIO"
	<Wait>
	<GetData>   U200
	<CheckData>		'83'
	<CheckDataX>		'C3'
	<CheckDataX>		'C2'
	#<CheckDataX>	'00'
	<CheckDataX>	'FF'


	<Msg>		"Check Chassis I2C IPMI B comunications.."
	#<Send>		'w8 f400001f 01'
	#<Wait>
	<Send>		'r8 f400001f'
	<Wait>
	<GetData>
	# Swap enabled
	<CheckData>	'F400001F   01'

	<Msg>		"Check Chassis IPMI"
	<Send>		"rd i2c 9501 chassis tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'


 	<Msg>		"Change Chassis I2C to IPMI A comunications.."
	<Send>		'w8 f400001f 07'
	<Wait>
	<Send>		'r8 f400001f'
	<Wait>
	<GetData>
	# Swap + buffer swap enabled
	<CheckData>	'F400001F   0F'

	<Msg>		"Check Chassis IPMI"
	<Send>		"rd i2c 9501 chassis tlv"
	<Wait>
	<GetData>
	<CheckData>	'SERIAL NUMBER .*BLOCK'

	<Msg>		"Change Chassis I2C to IPMI B comunications.."
	<Send>		'w8 f400001f 01'
	<Wait>
	<Send>		'r8 f400001f'
	<Wait>
	<GetData>
	<CheckData>	'F400001F   01'

	<Msg>	"Make IMC in slot 0 Master"
	<Send>	"w8 F4000028   01"
	<Wait>
	<Send>	"on 0 w8 F4000028 07"
	<Wait>
	<Send>  "r8 F4000028"
	<Wait>
	<CheckData>	"F4000028   01"
	<GetData>

	<Prompt>	"#"
	<Timeout>	20
	<Send>		"exit"
	<Wait>

	<Exec>	Swap_cons
    <Prompt>	">"
    <Msg>	"Check IMC Slot 0 Master"
    <Send>
    <Wait>
    <Send>  "r8 F4000028"
	<Wait>
	<CheckData>	"F4000028   07"
</Bypass>


<Prompt>	"^#|^slot ..>"
<Timeout>	20
<Send>		"exit"
#<Sleep>		2
<Wait>
