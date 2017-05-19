 ################################################################################
#
# Module:      Show Ship Config_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Config.dat
#
# Version:    1.2 $Id: Show_Ship_config_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 11/17/11
#			  6/10/13 Prompt changes in 6.1R2 
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################


<TimeOut>	20
<Prompt>	"[local]#"
<Send>		'show config'
<Wait>
<Send>		'terminal length infinite'
<Wait>
<Send>		'show port det'
<Wait>
<GetData>
<Send>		'show hardware'
<Wait>
<GetData>
<Send>		'show sys'
<wait>
<CheckData>	'System Hostname: Stoke'
<CheckData>	'System Location:'
<CheckData>	'System Contact:'

<CheckData>	'Console Port Baud Rate: 9600 Baud'

<CheckData>	'Current Boot:'
#<CheckData>	'  Boot Type:          Local'
#<CheckData>	'  Image File:         stoke.bin'
<CheckData>	'  Configuration File:   stoke.cfg'
<CheckData>	'  Classes per Session:  8'
<CheckData>	'  Sessions per GLC:     22500'
<CheckData>	'Next Boot:'
#<CheckData>	'  Boot Type:          Local'
#<CheckData>	'  Image File:         stoke.bin'
<CheckData>	'  Configuration File:   stoke.cfg'
<CheckData>	'  Classes per Session:  8'
<CheckData>	'  Sessions per GLC:     22500'
<GetData>
<Include>	Shell_imc.inc
<timeout>	20
#<Msg>       'Get DRAM SPD info"
#<Msg>   "Slot 0 IMC"
#<Send>  'pfeffa on 1 rd i2c spd 0 100'
#<Wait>
#<GetData>
#<Bypass>    $Slot_INST_1_GLC_GBL
#    <Msg>   "Slot 1 GLC"
#    <Send>  'pfeffa on 1 rd i2c spd 0 100'
#    <Wait>
#    <GetData>
#</Bypass>

#<Bypass>    $Slot_INST_1_IMC_GBL
#    <Msg>   "Slot 1 IMC"
#    <Send>  'pfeffa on 1 rd i2c spd 0 100'
#    <Wait>
#    <GetData>
#</Bypass>

<Msg>		"Bypass Show SPD on XGLC dram"
#<Bypass>    $Slot_INST_2_GBL
#    <Msg>   "Slot 2 GLC"
#    <Send>  'pfeffa on 2 rd i2c spd 0 100'
#    <Wait>
#    <GetData>
#</Bypass>

#<Bypass>    $Slot_INST_3_GBL
#    <Msg>   "Slot 3 GLC"
#    <Send>  'pfeffa on 3 rd i2c spd 0 100'
#    <Wait>
#    <GetData>
#</Bypass>

#<Bypass>    $Slot_INST_4_GBL
#    <Msg>   "Slot 4 GLC"
#    <Send>  'pfeffa on 4 rd i2c spd 0 100'
#    <Wait>
#    <GetData>
#</Bypass>
<Prompt>	"[local]#"
<Send>		'exit'
<Wait>


