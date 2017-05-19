 ################################################################################
#
# Module:      HA_Switchover_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI, Pre_BI,POst_BI, Config, Extended, ORT Dat files
#
# Version:    1.3 $Id: HA_Switchover_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 11/18/11
#				03/03/12 moved 			<Timeout> 180
			<Prompt> "Stoke[local]-STANDBY#"
#			  6/10/13 Prompt changes in 6.1R2/13.1 and IMC in Standby
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2013 Stoke. All rights reserved.
#
################################################################################
<Prompt>	"[local]#"
<Timeout>	15
<Bypass>	$HA_Session
		<Msg>	"Checking Standby IMC"
		<Exec>	Swap_cons
		<Prompt>	"SB[local]#"
		<Send>
		<Wait>
		<GetData>
		<Exec>	Swap_cons
		<Prompt>	"[local]#"
		<Send>
		<Wait>
			<Msg>	"IMC Switchover - Slot 1 Active"
			<Send> "system imc"
			<WaitFor>	'(yes/[no])'
			<Timeout> 180
			<Prompt>	"[local]#"
			<Send>		"yes"
#            <Timeout> 180
#            <Prompt>	"SB[local]#"
			<Wait>
			<GetData>
			<Send>		'terminal length infinite'
			<Wait>
			<Msg>   "Change Console to IMC in Slot 1"
			<Exec>	Swap_cons
			<Prompt>	"[local]#"
			<Timeout> 20
			<Sleep>   2
			<Send>
			<Wait>
			<GetData>
			<Send>		'terminal length infinite'
			<Wait>
			<Msg>		"Waiting for Standby IMC Slot 0 to restart"
			<Sleep>		180
			<Include>	Show_Card_Stoke_XGLC.inc
			#<Include>	Show_Env_Stoke_BI.inc  #Bug intermitt missing info

			<Msg>	"IMC Switchover - Slot 0 Active"
			<Send> "system imc"
			<WaitFor>	'(yes/[no])'
			<Timeout> 180
			<Prompt>	"SB[local]#"
			<Send>		"yes"
#            <Timeout> 180
#            <Prompt>	"SB[local]#"
			<Wait>
			<GetData>
			<Send>		'terminal length infinite'
			<Wait>
			<Msg>   "Change Console to IMC in Slot 0"
			<Exec>	Swap_cons
			<Prompt>	"[local]#"
			<Timeout> 20
			<Sleep>   2
			<Send>
			<Wait>
			<GetData>
			<Send>		'terminal length infinite'
			<Wait>
			<Msg>		"Waiting for Standby IMC Slot 1 to restart"
			<Sleep>		180
			<Include>	Show_Card_Stoke_XGLC.inc


</Bypass>


