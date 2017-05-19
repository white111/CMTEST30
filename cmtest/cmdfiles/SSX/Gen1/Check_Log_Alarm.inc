################################################################################
#
# Module:      Check_Log_Alarm.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_PRE_BI.dat, Chassis_Post_BI.dat,Config.dat
#
# Version:    1.1 $Id: Check_Log_Alarm.inc,v 1.4 2010/03/02 00:37:48 joe Exp $
#
# Changes:    Created 03/10/06
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################

<Prompt>	"Stoke[local]#"
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



