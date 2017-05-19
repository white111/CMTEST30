################################################################################
#
# Module:      Configuration_Test.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_POST_BI and Config
#
# Version:    2.2 $Id: Configuration_test.inc,v 1.2.8.1 2011/11/30 19:48:56 joe Exp $
#
# Changes:    Created 081308 in response to componet layer 3 failures not caught
#			  by Layer 2 Snake tests
#			  Removed Show Port counters Det. Failing at Creation only, not at Stoke
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"Stoke[local]#"
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
<Include> 	Show_Port_FPD.inc
<Include>	Ship_config.inc

