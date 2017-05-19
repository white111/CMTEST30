 ################################################################################
#
# Module:      Reset_all_slots
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI, Pre_BI,POst_BI, Config, Extended, ORT Dat files
#
# Version:    1.4 $Id: Reset_all_slots.inc,v 1.7 2010/03/02 19:09:13 joe Exp $
#
# Changes:    Created 10/12/06
#			  01/11/08  Changed to directly toggle GPIO reset lines in reset,cpu reset and power cycle
#			  Improved detection for Resets 3/1/10
#			  Added Hard reset for Second CPU GPIO "C",     , Reset All Slots using GPIO Hard Reset CPU
#			  Removeing test for resetting CPUs. No longer supported, Causes instability. Chkeck with
#				Software. Feature not supported.
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################
<Prompt>	"#"
<Timeout>	100
<Bypass>	$Slot_INST_1_IMC_GBL
	<Msg>	"Wait for Slot 1 IMC"
	<Send>	'waitfor /net/nv-1-0/stoke/bin/diag/mc.setup.fabsnake 100'
	<Wait>
	<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>		"Reset GLC 1"
	<Send>		"pfeffa on 1 w8 f400002b 11"
	<Wait>
</Bypass>
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>	"Wait for Slot 1 GLC"
	<Send>	'waitfor /net/nv-1-0/stoke/bin/diag/ixtest 100'
	<Wait>
	<send>	"pfeffa rd i2c 9501 1 gpio"
	<wait>
	<Checkdata> "BF"
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>	"Wait for Slot 2"
	<Send>	'waitfor /net/nv-2-0/stoke/bin/diag/ixtest 100'
	<Wait>
	<send>	"pfeffa rd i2c 9501 2 gpio"
	<wait>
	<Checkdata> "BF"
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>	"Wait for Slot 3"
	<Send>	'waitfor /net/nv-3-0/stoke/bin/diag/ixtest 100'
	<Wait>
	<send>	"pfeffa rd i2c 9501 3 gpio"
	<wait>
	<Checkdata> "BF"
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>	"Wait for Slot 4"
	<Send>	'waitfor /net/nv-4-0/stoke/bin/diag/ixtest 100'
	<Wait>
	<Timeout>	20
	<send>	"pfeffa rd i2c 9501 4 gpio"
	<wait>
	<Checkdata> "BF"
</Bypass>

<Timeout>	20
<Msg>		"Reset All Slots using GPIO Reset board"
<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>		"Reset GLC 1"
	<Send>		"pfeffa on 1 w8 f400002b 11"
	<Wait>
	<Send>		"pfeffa wr i2c 9501 1 gpio d"
	<Wait>
	<send>		"ls /net/nv-1-0"
	<wait>
	<checkdata>	"ost.*nv-1-0"
	<send>	"pfeffa rd i2c 9501 1 gpio"
	<wait>
	<Checkdata> "FD"
	<Send>		"pfeffa wr i2c 9501 1 gpio f"
	<Wait>
	#<Send>		"on -f /net/nv-1-0 reset bo &"
	#<Wait>
	<Sleep>		1
	<send>		"ls /net/nv-1-0"
	<wait>
	#<checkdatax>	"No route to host.*nv-1-0"
</Bypass>

<Bypass>	$Slot_INST_GBL[3]
	<Msg>		"Reset GLC 2"
	<Send>		"pfeffa on 2 w8 f400002b 11"
	<Wait>
	<Send>		"pfeffa wr i2c 9501 2 gpio d"
	<Wait>
	<send>		"ls /net/nv-2-0"
	<wait>
	<checkdata>	"ost.*nv-2-0"
	<send>	"pfeffa rd i2c 9501 2 gpio"
	<wait>
	<Checkdata> "FD"
	<Send>		"pfeffa wr i2c 9501 2 gpio f"
	<Wait>
	#<Send>		"on -f /net/nv-2-0 reset bo &"
	#<Wait>
	<Sleep>		1
	<send>		"ls /net/nv-2-0"
	<wait>
	#<checkdatax>	"No route to host.*nv-2-0"
</Bypass>

<Bypass>	$Slot_INST_GBL[4]
	<Msg>		"Reset GLC 3"
	<Send>		"pfeffa on 3 w8 f400002b 11"
	<Wait>
	<Send>		"pfeffa wr i2c 9501 3 gpio d"
	<Wait>
	<send>		"ls /net/nv-3-0"
	<wait>
	<checkdata>	"ost.*nv-3-0"
	<send>	"pfeffa rd i2c 9501 3 gpio"
	<wait>
	<Checkdata> "FD"
	<Send>		"pfeffa wr i2c 9501 3 gpio f"
	<Wait>
	#<Send>		"on -f /net/nv-3-0 reset bo &"
	#<Wait>
	<Sleep>		1
	<send>		"ls /net/nv-3-0"
	<wait>
	#<checkdatax>	"No route to host.*nv-3-0"
</Bypass>

<Bypass>	$Slot_INST_GBL[5]
	<Msg>		"Reset GLC 4"
	<Send>		"pfeffa on 4 w8 f400002b 11"
	<Wait>
	<Send>		"pfeffa wr i2c 9501 4 gpio d"
	<Wait>
	<send>		"ls /net/nv-4-0"
	<wait>
	<checkdata>	"ost.*nv-4-0"
	<send>	"pfeffa rd i2c 9501 4 gpio"
	<wait>
	<Checkdata> "FD"
	<Send>		"pfeffa wr i2c 9501 4 gpio f"
	<Wait>
	#<Send>		"on -f /net/nv-4-0 reset bo &"
	#<Wait>
	<Sleep>		1
	<send>		"ls /net/nv-4-0"
	<wait>
	#<checkdatax>	"No route to host.*nv-4-0"
</Bypass>

<Timeout>  90
<Send>	"wait"
<Wait>

<Timeout>	130
<Bypass>	$Slot_INST_1_IMC_GBL
	<Msg>	"Wait for Slot 1 IMC"
	<Send>	'waitfor /net/nv-1-0/stoke/bin/diag/mc.setup.fabsnake 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>	"Wait for Slot 1 GLC"
	<Send>	'waitfor /net/nv-1-0/stoke/bin/diag/ixtest 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>	"Wait for Slot 2"
	<Send>	'waitfor /net/nv-2-0/stoke/bin/diag/ixtest 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>	"Wait for Slot 3"
	<Send>	'waitfor /net/nv-3-0/stoke/bin/diag/ixtest 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>	"Wait for Slot 4"
	<Send>	'waitfor /net/nv-4-0/stoke/bin/diag/ixtest 100'
	<Wait>
	<Timeout>	20
</Bypass>


#Feature Removed 3/8/9/12 No longer supported, and unstable **********
#<Timeout>   20
#<Msg>       "Bypass - Reset All Slots using GPIO Hard Reset CPUs"
#<Bypass>    $Slot_INST_1_GLC_GBL
#    <Msg>       "Reset GLC 1"
#    <Send>      "pfeffa on 1 w8 f400002b 11"
#    <Wait>
#    <Send>      "pfeffa wr i2c 9501 1 gpio B"
#    <Wait>
#    <Send>      "pfeffa wr i2c 9501 1 gpio C"
#    <Wait>
#    <send>      "ls /net/nv-1-0"
#    <wait>
#    <checkdata> "ost.*nv-1-0"
#    <Send>      "pfeffa wr i2c 9501 1 gpio f"
#    <Wait>
#    #<Send>     "on -f /net/nv-1-0 reset bo &"
#    #<Wait>
#    <Sleep>     1
#    <send>      "ls /net/nv-1-0"
#    <wait>
#    #<checkdatax>   "No route to host.*nv-1-0"
#</Bypass>

#<Bypass>    $Slot_INST_GBL[3]
#    <Msg>       "Reset GLC 2"
#    <Send>      "pfeffa on 2 w8 f400002b 11"
#    <Wait>
#    <Send>      "pfeffa wr i2c 9501 2 gpio B"
#    <Wait>
#    <Send>      "pfeffa wr i2c 9501 2 gpio C"
#    <Wait>
#    <send>      "ls /net/nv-2-0"
#    <wait>
#    <checkdata> "ost.*nv-2-0"
#    <Send>      "pfeffa wr i2c 9501 2 gpio f"
#    <Wait>
#    #<Send>     "on -f /net/nv-2-0 reset bo &"
#    #<Wait>
#    <Sleep>     1
#    <send>      "ls /net/nv-2-0"
#    <wait>
#    #<checkdatax>   "No route to host.*nv-2-0"
#</Bypass>

#<Bypass>    $Slot_INST_GBL[4]
#    <Msg>       "Reset GLC 3"
#    <Send>      "pfeffa on 3 w8 f400002b 11"
#    <Wait>
#    <Send>      "pfeffa wr i2c 9501 3 gpio B"
#    <Wait>
#    <Send>      "pfeffa wr i2c 9501 3 gpio C"
#    <Wait>
#    <send>      "ls /net/nv-3-0"
#    <wait>
#    <checkdata> "ost.*nv-3-0"
#    <Send>      "pfeffa wr i2c 9501 3 gpio f"
#    <Wait>
#    #<Send>     "on -f /net/nv-3-0 reset bo &"
#    #<Wait>
#    <Sleep>     1
#    <send>      "ls /net/nv-3-0"
#    <wait>
#    #<checkdatax>   "No route to host.*nv-3-0"
#</Bypass>

#<Bypass>    $Slot_INST_GBL[5]
#    <Msg>       "Reset GLC 4"
#    <Send>      "pfeffa on 4 w8 f400002b 11"
#    <Wait>
#    <Send>      "pfeffa wr i2c 9501 4 gpio B"
#    <Wait>
#    <Send>      "pfeffa wr i2c 9501 4 gpio C"
#    <Wait>
#    <send>      "ls /net/nv-4-0"
#    <wait>
#    <checkdata> "ost.*nv-4-0"
#    <Send>      "pfeffa wr i2c 9501 4 gpio f"
#    <Wait>
#    #<Send>     "on -f /net/nv-4-0 reset bo &"
#    #<Wait>
#    <Sleep>     1
#    <send>      "ls /net/nv-4-0"
#    <wait>
#    #<checkdatax>   "No route to host.*nv-4-0"
#</Bypass>

#<Timeout>  90
#<Send>  "wait"
#<Wait>

#<Timeout>   100
#<Bypass>    $Slot_INST_1_IMC_GBL
#    <Msg>   "Wait for Slot 1 IMC"
#    <Send>  'waitfor /net/nv-1-0/stoke/bin/diag/mc.setup.fabsnake 100'
#    <Wait>
#</Bypass>

#<Bypass>    $Slot_INST_1_GLC_GBL
#    <Msg>   "Wait for Slot 1 GLC"
#    <Send>  'waitfor /net/nv-1-0/stoke/bin/diag/ixtest 100'
#    <Wait>
#</Bypass>

#<Bypass>    $Slot_INST_2_GBL
#    <Msg>   "Wait for Slot 2"
#    <Send>  'waitfor /net/nv-2-0/stoke/bin/diag/ixtest 100'
#    <Wait>
#</Bypass>

#<Bypass>    $Slot_INST_3_GBL
#    <Msg>   "Wait for Slot 3"
#    <Send>  'waitfor /net/nv-3-0/stoke/bin/diag/ixtest 100'
#    <Wait>
#</Bypass>

#<Bypass>    $Slot_INST_4_GBL
#    <Msg>   "Wait for Slot 4"
#    <Send>  'waitfor /net/nv-4-0/stoke/bin/diag/ixtest 100'
#    <Wait>
#    <Timeout>   20
#</Bypass>

<Timeout>	20
<Msg>		"Reset All Slots using GPIO Power cycle"
<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>		"Reset GLC 1"
	<Send>		"pfeffa on 1 w8 f400002b 11"
	<Wait>
	<Send>		"pfeffa wr i2c 9501 1 gpio 7"
	<Wait>
	<send>		"ls /net/nv-1-0"
	<wait>
	#<checkdata>	"ost.*nv-1-0"
	<Send>		"pfeffa wr i2c 9501 1 gpio f"
	<Wait>
	#<Send>		"on -f /net/nv-1-0 reset bo &"
	#<Wait>
	<Sleep>		1
	<send>		"ls /net/nv-1-0"
	<wait>
	#<checkdatax>	"No route to host.*nv-1-0"
</Bypass>

<Bypass>	$Slot_INST_GBL[3]
	<Msg>		"Reset GLC 2"
	<Send>		"pfeffa on 2 w8 f400002b 11"
	<Wait>
	<Send>		"pfeffa wr i2c 9501 2 gpio 7"
	<Wait>
	<send>		"ls /net/nv-2-0"
	<wait>
	#<checkdata>	"ost.*nv-2-0"
	<Send>		"pfeffa wr i2c 9501 2 gpio f"
	<Wait>
	#<Send>		"on -f /net/nv-2-0 reset bo &"
	#<Wait>
	<Sleep>		1
	<send>		"ls /net/nv-2-0"
	<wait>
	#<checkdatax>	"No route to host.*nv-2-0"
</Bypass>

<Bypass>	$Slot_INST_GBL[4]
	<Msg>		"Reset GLC 3"
	<Send>		"pfeffa on 3 w8 f400002b 11"
	<Wait>
	<Send>		"pfeffa wr i2c 9501 3 gpio 7"
	<Wait>
	<send>		"ls /net/nv-3-0"
	<wait>
	#<checkdata>	"ost.*nv-3-0"
	<Send>		"pfeffa wr i2c 9501 3 gpio f"
	<Wait>
	#<Send>		"on -f /net/nv-3-0 reset bo &"
	#<Wait>
	<Sleep>		1
	<send>		"ls /net/nv-3-0"
	<wait>
	#<checkdatax>	"No route to host.*nv-3-0"
</Bypass>

<Bypass>	$Slot_INST_GBL[5]
	<Msg>		"Reset GLC 4"
	<Send>		"pfeffa on 4 w8 f400002b 11"
	<Wait>
	<Send>		"pfeffa wr i2c 9501 4 gpio 7"
	<Wait>
	<send>		"ls /net/nv-4-0"
	<wait>
	#<checkdata>	"ost.*nv-4-0"
	<Send>		"pfeffa wr i2c 9501 4 gpio f"
	<Wait>
	#<Send>		"on -f /net/nv-4-0 reset bo &"
	#<Wait>
	<Sleep>		1
	<send>		"ls /net/nv-4-0"
	<wait>
	<checkdatax>	"No route to host.*nv-4-0"
</Bypass>

<Timeout>  90
<Send>	"wait"
<Wait>

<Timeout>	100
<Bypass>	$Slot_INST_1_IMC_GBL
	<Msg>	"Wait for Slot 1 IMC"
	<Send>	'waitfor /net/nv-1-0/stoke/bin/diag/mc.setup.fabsnake 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>	"Wait for Slot 1 GLC"
	<Send>	'waitfor /net/nv-1-0/stoke/bin/diag/ixtest 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>	"Wait for Slot 2"
	<Send>	'waitfor /net/nv-2-0/stoke/bin/diag/ixtest 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>	"Wait for Slot 3"
	<Send>	'waitfor /net/nv-3-0/stoke/bin/diag/ixtest 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>	"Wait for Slot 4"
	<Send>	'waitfor /net/nv-4-0/stoke/bin/diag/ixtest 100'
	<Wait>
	<Timeout>	20
</Bypass>
