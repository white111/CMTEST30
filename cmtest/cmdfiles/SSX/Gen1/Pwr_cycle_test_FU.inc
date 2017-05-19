################################################################################
#
# Module:      Pwr_cycle_test_FU.inc
#
# Author:      Joe White
#
# Descr:       Adding power cycling
#
# Version:    1.0 $Id: Onscript_Start.inc,v 1.9 2009/05/07 15:50:10 joe Exp $
#
# Changes:    Created 08/30/12, IDT Clock Issues
#
#
# Includes:
#
# Still ToDo:
#              - Add Looping on each test, start a process for each test
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################

    <Msg>		"Power Cycling system"
     <Power>		OFF
     <Sleep>		6
     <Power>		ON
     <TimeOut>	120
     <Prompt>	'#'
 	<Wait>
 	<Msg>		"Waiting for system to boot.."
 	 	<GetData>
 	#<iCheckdata>	"error"
 	#<iCheckdata>	"fail"
 	<Sleep>		20
    <msg>		"Dropping KSH priority to 7f"
	<Send>		'on -p 7f ksh'
	<Wait>
	<GetData>

<Loop>		4000
<Include>   Set_Fan_Speed.inc
<Msg>	"Setting new interpacekt gap"
#1) pfeffa r8 f1002c3c => F
#2) pfeffa w8 f1002c3c E  (Disable port 2)
#3) pfeffa r8 f1002c0c => 6
#4) pfeffa w8 f1002c0c 7  ( max gap 3bits)
#5) pfeffa w8 f1002c3c F (Enable port)
<TimeOut>	20
<Send>		"pfeffa r8 f1002c3c"
<Wait>
<GetData>
<Send>		"pfeffa w8 f1002c3c E"
<Wait>
<Send>		"pfeffa r8 f1002c0c"
<Wait>
<Send>		"pfeffa w8 f1002c0c 7"
<Wait>
<GetData>
<Send>		"pfeffa w8 f1002c3c F"
<Wait>
<Include>   Internal_Snake_setup.inc
<Include>   Clear_Disco.inc
#<Include>  Onscript_Start_BI.inc
#<Include>   BI_loopbacktest.inc
#<Include>  Onscript_Check.inc
#<Include>   Check_Disco.inc
<Include>   Onscript_Start.inc
<Include>   Onscript_Check.inc
<Include>   Check_HDP_Log_Error.inc
<Include>   Check_Disco.inc
#<Include>   Check_5th_link.inc

    <Msg>		"Power Cycling system"
     <Power>		OFF
     <Sleep>		6
     <Power>		ON
     <TimeOut>	120
     <Prompt>	'#'
 	<Wait>
 	<Msg>		"Waiting for system to boot.."
 	 	<GetData>
 	#<iCheckdata>	"error"
 	#<iCheckdata>	"fail"
 	<Sleep>		20
    <msg>		"Dropping KSH priority to 7f"
	<Send>		'on -p 7f ksh'
	<Wait>
	<GetData>
 </Loop>
