################################################################################
#
# Module:      Stop_stoke_boot_q
#
# Author:      Joe White
#
# Descr:       Called by Dat and Inc files
#
# Version:    2.1  $Id: Stop_stoke_boot.inc,v 1.4 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Modified for R1 release 01/03/06
#			  Modified for 3.0
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################
<Prompt>	"Stoke>>"
<TimeOut>	30

<Msg>		"Stopping Stoke bootup.."
<WaitFor>	"Initializing Network Hardware"
<SendChr>		uboot
# For backward compatability to 2.0R2 Only need to keep this until the next release
<Sleep>		1
<SendChr>		"stoke"
<Wait>
<GetData>  POST

