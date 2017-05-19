 ################################################################################
#
# Module:      Check-Diag_Jumper.inc
#
# Author:      Joe White
#
# Descr:       Checks software versions on a full 5 slot chassis
#
# Version:    1.1 $Id: Check_Diag_Jumper.inc,v 1.5 2010/03/02 19:09:13 joe Exp $
#
# Changes:    Created 12/08/05
#             Added Check for Boot on Primary, bug with corupted Flash  10/7/09
#
# Includes:
#
#
#
# Still ToDo:
#            Make flexable for different configurations
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"Stoke[local]#"
<TimeOut>	5
<Msg>		"Check For Diag Jumper"
<Send>		'terminal length infinite'
<Wait>
<GetData>

<Msg>		"Show Software Versions Slot 0"
<Send>		"show ver slot 0"
<Wait>
<GetData>
<CheckData> "\*Booted Primary:"

# Debug only <Msg>			"Bypassed checking for diag jumper"
<CheckDataX>	"SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"

<Bypass>	$Slot_INST_1_GBL
	<Msg>		"Show Software Versions Slot 1"
	<Send>		"show ver slot 1"
	<Wait>
	<GetData>
	<CheckData> "\*Booted Primary:"
 	# Debug only <Msg>			"Bypassed checking for diag jumper"
	<CheckDataX>	"SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>		"Show Software Versions Slot 2"
	<Send>		"show ver slot 2"
	<Wait>
	<GetData>
	<CheckData> "\*Booted Primary:"
 	<CheckDataX>	"SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>		"Show Software Versions Slot 3"
	<Send>		"show ver slot 3"
	<Wait>
	<GetData>
	<CheckData> "\*Booted Primary:"
	<CheckDataX>	"SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>		"Show Software Versions Slot 4"
	<Send>		"show ver slot 4"
	<Wait>
	<GetData>
	<CheckData> "\*Booted Primary:"
 	<CheckDataX>	"SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"
</Bypass>

<Send>
<Wait>





