################################################################################
#
# Module:      hd_boot_imc.inc
#
# Author:      Joe White
#
# Descr:       Called by Bench_IMC.dat, Chassis_Pre,Post,BI.dat
#
# Version:    1.3 $Id: hd_boot_imc.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Added <GetData>  2/5/09
#			  Added Delete dump directories 1/12/11
#			  Added GLC redundancy enable 2/3/12
#		      #Added 6.0 main line creating test config 8/6/12
#		      Stoke Promps change with 6.1 <Prompt>	"^Stoke.*[local]"  for Stoke::LCR[local]
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################
# TFTP Boot an IMC

<Include>	Delete_dump_dir.inc
<Msg>		"Bootloader configure stoke.bin from HD..."
<TimeOut>	45
<Prompt>	"Stoke-BootLoader#"
<Sendslow>		'boot image file /hd/mfg/stoke.bin'
<Wait>
<GetData>
<CheckData> 'Passed'
<Msg>		'Booting to Stoke Released OS from HD....'
<Send>		'go'
<TimeOut>	150
<Prompt>	"[local]#"
<Wait>
<GetData>
<CheckData>	'booting '
<CheckData>	'Welcome to Stoke's Command Line Interface'
<TimeOut>	90
<Send>		'terminal length infinite'
<Wait>
<GetData>

<TimeOut>	360
<msg>		"Install ISSU packages"
<msg>		$StokeOS_ISSU_Install_gbl
<Prompt>	"[local]#"
<Prompt>	'no'
<Sendchr>		'system install package /hd/'
<Send>       $StokeOS_ISSU_Install_gbl
<Wait>
<Prompt>	"[local]#"
<Send>		'y'
<wait>
<CheckData>	"Installation complete"
<checkdatax> "ERROR"
<Getdata>

#Added 6.0 main line creating test config
<Msg>		"Clear and save config"
<TimeOut>	10
<Prompt>	"[local]#"
<Prompt>	'Proceed'
<Send>		'config clear'
<Wait>
<Prompt>	"[local]#"
<Send>		'yes'
<Wait>
<Send>		'del stoke.cfg'
<Wait>
<Send>		'boot configuration file stoke.cfg'
<Waitfor>   ']'
<Send>		"yes"
<wait>
<Send>		'del stoke.cfg'
<Wait>
<Send>		'config save stoke.cfg'
<Waitfor>   ']'
<Send>		"yes"
<Wait>
<Send>		'config load stoke.cfg'
<Wait>


<Prompt>	"[local]#"
<Msg>		"Check if GLC 4 Slot Not enabled"
<Send>		"show system"
<Wait>
<GetData>   Check_GLC_Slot4_Enable
<GetData>   Check_GLC_Redundancy

<bypass>	$noglcslot4enable_gbl
	<msg>		"Disable 4 Slot GLC"
	<Send>       "no system enable-4-lc"
	<Wait>
	<GetData>
	<Prompt>	'yes'
	<send>		"reload"
	<wait>
	<Prompt>	"[local]#"
	<Send>		'y'
	<sleep>		1
	<Send>		'y'

	<Msg>		"Waiting for system reload after disable slot 4 GLC"
	<timeout>   180
	<wait>
	<getdata>

	<Send>		'terminal length infinite'
</Bypass>

#<Msg>       "Check if GLC redundancy Enabled"
#<Send>      "show system"
#<Wait>
##GLC Redundancy Group: 1
<GetData>   Check_GLC_Redundancy
<bypass>	$noglcslot4enable_gbl
 <bypass>	$glcredundant_gbl
	<msg>		"Enable GLC Redundancy"
	<Send>       "system glc-r"
	<Wait>
	<GetData>
	<Prompt>	'yes'
	<send>		"reload"
	<wait>
	<Prompt>	"[local]#"
	<Send>		'y'
	<sleep>		1
	<Send>		'y'

	<Msg>		"Waiting for system reload after applying GLC redundancy"
	<timeout>   180
	<wait>
	<getdata>

	<Send>		'terminal length infinite'
 </Bypass>
</Bypass>


<bypass>	$Slot_INST_1_GLC_GBL
 <Prompt>	"[local]#"
 <Msg>		"Check if GLC Slot4 enabled"
 <Send>		"show system"
 <Wait>
<GetData>   Check_GLC_Slot4_Enable

#<bypass>	$Slot_INST_1_GLC_GBL
 <bypass>	$glcslot4enable_gbl
	<msg>		"Enable 4Slot GLC"
	<Send>       "system enable-4-lc"
	<Wait>
	<GetData>
	<Prompt>	'yes'
	<send>		"reload"
	<wait>
	<Prompt>	"[local]#"
	<Send>		'y'
	<sleep>		1
	<Send>		'y'

	<Msg>		"Waiting for system reload after enable 4 slot GLC"
	<timeout>   180
	<wait>
	<getdata>

	<Send>		'terminal length infinite'
#</Bypass>
</Bypass>




