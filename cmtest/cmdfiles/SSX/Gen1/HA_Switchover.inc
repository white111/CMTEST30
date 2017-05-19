 ################################################################################
#
# Module:      HA_Switchover.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI, Pre_BI,POst_BI, Config, Extended, ORT Dat files
#
# Version:    1.2 $Id: HA_Switchover.inc,v 1.6 2009/09/28 17:21:45 joe Exp $
#
# Changes:    Created 10/12/06
#			  Removing Show Env on IMC slot 0, Intermittnt missing information
#             Bug filed
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################
<Prompt>	"Stoke[local]#"
<Timeout>	10
<Bypass>	$HA_Session
		<Msg>	"Checking Standby IMC"
		<Exec>	Swap_cons
		<Prompt> "Stoke[local]-STANDBY#"
		<Send>
		<Wait>
		<GetData>
		<Exec>	Swap_cons
		<Prompt> "Stoke[local]#"
		<Send>
		<Wait>
			<Msg>	"IMC Switchover - Slot 1 Active"
			<Send> "system imc"
			<WaitFor>	'(yes/[no])'
			<Send>		"yes"
			<Timeout> 180
			<Prompt> "Stoke[local]-STANDBY#"
			<Wait>
			<GetData>
			<Send>		'terminal length infinite'
			<Wait>
			<Msg>   "Change Console to IMC in Slot 1"
			<Exec>	Swap_cons
			<Prompt> "Stoke[local]#"
			<Timeout> 20
			<Sleep>   2
			<Send>
			<Wait>
			<GetData>
			<Send>		'terminal length infinite'
			<Wait>
			<Msg>		"Waiting for Standby IMC Slot 0 to restart"
			<Sleep>		180
			<Include>	Show_Card_Stoke.inc
			#<Include>	Show_Env_Stoke_BI.inc  #Bug intermitt missing info

			<Msg>	"IMC Switchover - Slot 0 Active"
			<Send> "system imc"
			<WaitFor>	'(yes/[no])'
			<Send>		"yes"
			<Timeout> 180
			<Prompt> "Stoke[local]-STANDBY#"
			<Wait>
			<GetData>
			<Send>		'terminal length infinite'
			<Wait>
			<Msg>   "Change Console to IMC in Slot 0"
			<Exec>	Swap_cons
			<Prompt> "Stoke[local]#"
			<Timeout> 20
			<Sleep>   2
			<Send>
			<Wait>
			<GetData>
			<Send>		'terminal length infinite'
			<Wait>
			<Msg>		"Waiting for Standby IMC Slot 1 to restart"
			<Sleep>		180
			<Include>	Show_Card_Stoke.inc


</Bypass>


