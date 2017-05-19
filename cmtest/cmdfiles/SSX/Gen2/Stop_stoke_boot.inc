################################################################################
#
# Module:      Stop_stoke_boot_q
#
# Author:      Joe White
#
# Descr:       Called by Dat and Inc files
#
# Version:    3.3  $Id: Stop_stoke_boot.inc,v 1.1 2011/12/12 22:54:27 joe Exp $
#
# Changes:    XGLC Changes 5/23/11 from Vers 2.1
#			  Added Supoort for Gen1 IMC/GLC and Gen2 IMC2/XGLCx  02/04/13
#             xx
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2013 Stoke. All rights reserved.
#
################################################################################
<Prompt>	"Stoke>"
<TimeOut>	35

<Msg>		"Stopping Stoke bootup.."
<WaitFor>	"Initializing Network Hardware"
#<WaitFor>	"uboot"
<SendChr>	"uboot"
<Msg> "IMC2/XGLCx POST check..."
<GetData>  POST
<Wait>
<bypass>	$Post_GBL
#  IMC GLC needed here
<Msg> "IMC POST check..."
<GetData>  POST
</bypass>


