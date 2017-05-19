################################################################################
#
# Module:      Check_Log_Alarm_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_PRE_BI.dat, Chassis_Post_BI.dat,Config.dat
#
# Version:    1.2 $Id: Check_Log_Alarm_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 11/18/11
#			  6/10/13 Prompt changes in 6.1R2 
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################

<Prompt>	"[local]#"
<TimeOut>	10
<Send>
<Wait>
<TimeOut>	10
<Send>		"terminal length infinite"
<Wait>
<Msg>		"Check log for alarms"

<Sendslow>		"show log | grep _ALAR"
<Wait>
<GetData>
<CheckDatax>	"ALARM"



