################################################################################
#
# Module:      Fisrtboot_DualIMC.inc
#
# Author:      Joe White
#
# Descr:       Handels First boot of Dual IMC system when IMC in slot 1 is active
#
# Version:    1.1 $Id: Firstboot_DualIMC.inc,v 1.2 2011/01/21 18:38:55 joe Exp $
#
# Changes:    04/20/10 Created
#			  01/17/11 Added 240 Second wait due to switchover
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2010 Stoke. All rights reserved.
#
################################################################################
<Msg>		"Check if Firstboot of Dual IMC system"
<Timeout>	60
<Prompt>	"#"
<Send>		"start shell"
<Wait>
<GetData>
<Send>		" chassis_nv=`pfeffa rd nvram tlv 7 | grep 007`"
<Wait>
<GetData>
<Send>		"chassis_ee=`pfeffa rd i2c 9501 chassis tlv 7 | grep 007` "
<Wait>
<GetData>
<Send>		"echo $chassis_nv  "
<Wait>
<GetData>
<Send>		"echo $chassis_ee   "
<Wait>
<GetData>
<SendSlow>		"if ( (test "$chassis_nv" != "$chassis_ee") && (pfeffa rd i2c 9501 1 tlv | grep IMC) ) then (echo New IMC in Slot 0) else (echo Known IMC in slot 0) fi"
<Wait>
<GetData> Get_FistbootIMC
<TimeOut>	10
<Prompt>	"Stoke-BootLoader#"
<Send>		"exit"
<Wait>
<GetData>
<Bypass>	$Firstboot_Dual_IMC_GBL
	<Msg>		"First Boot of Dual IMC system detected"
    #<include>  tftp_boot_imc_stoke.inc
    <timeout>	180
    <Send> "system issu disable"
    <wait>
    <send>	"boot image file stoke.bin"
    <wait>
    <Msg>	"Configure IMC Slot 1"
    <Exec>		Init_HA_Port
    <Exec>	Swap_cons
    <Send> "system issu disable"
    <wait>
    <send>	"boot image file stoke.bin"
    <wait>
    <Exec>	Swap_cons
    <timeout>	360
	<Msg>	"Waiting Standby IMC slot 0"
	<Prompt> "Stoke[local]-STANDBY#"
	<Send>	"go"
	<Wait>
	<GetData>
	<Exec>	Swap_cons
	<Msg>	"Checking Active IMC slot 1"
	<Prompt> "Stoke[local]#"
	<Send>
	<Wait>
	<GetData>
 	<Msg>		"Restart System"
	<Send>		"reload now"
	<WaitFor>	'(yes/[no])'
	<Send>		"yes"
	<Sleep>		1
	<Send>		"yes"
	<Exec>	Swap_cons
	<TimeOut>	120
	<Include>	Stop_stoke_bootloader.inc
    <Msg>		"Completed:First Boot of Dual IMC system"

</Bypass>


