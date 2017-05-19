################################################################################
#
# Module:      Fisrtboot_DualIMC.inc
#
# Author:      Joe White
#
# Descr:       Handels First boot of Dual IMC system when IMC in slot 1 is active
#
# Version:    1.1 $Id: Firstboot_DualIMC.inc,v 1.2 2011/01/21 18:38:55 joe Exp $
#
# Changes:    04/20/10 Created
#			  01/17/11 Added 240 Second wait due to switchover
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2010 Stoke. All rights reserved.
#
################################################################################
<Msg>		"Check if Firstboot of Dual IMC system"
<Timeout>	60
<Prompt>	"#"
<Send>		"start shell"
<Wait>
<GetData>
<include>	Set_Fan_Speed.inc
<prompt>		"Stoke"
<send>		"exit"
<wait>

