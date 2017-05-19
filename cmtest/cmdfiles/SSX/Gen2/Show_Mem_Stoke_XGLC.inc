################################################################################
#
# Module:      Show_Mem_Stoke_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_POST_BI and Config
#
# Version:    1.1 $Id: Show_Mem_Stoke_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 011006
#			  6/10/13 Prompt changes in 6.1R2 
#
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
<Msg>		"Show Memory"
<Send>		"show mem"
<Wait>
<GetData>	Memory_size

<Send>		"show mem"
<Wait>
<GetData>






