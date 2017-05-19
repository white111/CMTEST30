################################################################################
#
# Module:      Show_Mem_Stoke.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_POST_BI and Config
#
# Version:    2.1 $Id: Show_Mem_Stoke.inc,v 1.6 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Created 011006
#			  Updated memory sizes for 2.0  030106
#			  Updated memory sizes for 2.0  030906
#			  Modified to lookup minimum memory size  10/12/06
#
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
<Msg>		"Show Memory"
<Send>		"show mem"
<Wait>
<GetData>	Memory_size

<Send>		"show mem"
<Wait>
<GetData>






