################################################################################
#
# Module:      Fisrtboot_DualIMC_BI.inc
#
# Author:      Joe White
#
# Descr:       Handels First boot of Dual IMC system when IMC in slot 1 is active
#
# Version:    1.2 $Id: Firstboot_DualIMC_BI.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    04/20/10 Created
#			  01/17/11 Added 240 Second wait due to switchover
#			  12/2/11 Change to hd boot for 6.0
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
    <Include>	hd_boot_imc.inc
	<Msg>	"Checking Standby IMC"
	<Prompt> "Stoke[local]-STANDBY#"
	<Send>
	<Wait>
	<GetData>
    <Prompt> "Proceed"
	<Send>	"system imc"
    <Wait>
    <GetData>
    <Prompt>	"Stoke[local]#"
    <Send>	"y"
    <Wait>
    <GetData>
 #    <Include>	Wait_Card_Stoke.inc
	<Msg>		"Wait 240 Sec for cards to come ready"
	<Sleep>		240
 	<Msg>		"Restart System"
	<Send>		"reload now"
	<WaitFor>	'(yes/[no])'
	<Send>		"yes"
	<Sleep>		1
	<Send>		"yes"
	<TimeOut>	120
	<Include>	Stop_stoke_bootloader.inc
    <Msg>		"Completed:First Boot of Dual IMC system"

</Bypass>


