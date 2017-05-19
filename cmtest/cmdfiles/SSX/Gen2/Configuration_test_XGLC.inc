################################################################################
#
# Module:      Configuration_Test.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_POST_BI and Config
#
# Version:    2.3 $Id: Configuration_test_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 081308 in response to componet layer 3 failures not caught
#			  by Layer 2 Snake tests
#			  Removed Show Port counters Det. Failing at Creation only, not at Stoke
#			  6/10/13 Prompt changes in 6.1R2
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"[local]#"
<Send>
<Wait>
<TimeOut>	10
<Send>		"terminal length infinite"
<Wait>
<Msg>		"Configuration Test"
<Include>	Ship_config.inc
<Include>	Configure_Ports.inc
<Sleep>		10
<Include>	Configured_Ports_Ping.inc
<Include>	Show_Port_Counters_Det.inc
#<Include> 	Show_Port_FPD.inc
<Include>   Show_Card_Stoke_XGLC.inc
<Include>	Ship_config.inc

