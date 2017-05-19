 ################################################################################
#
# Module:      Shell_imc.inc
#
# Author:      Joe White
#
# Descr:       Called by Clean_IMC_drives.inc
#
# Version:    1.1 $Id: Shell_imc.inc,v 1.7 2011/01/21 18:38:55 joe Exp $
#
# Changes:    Added <GetData>  12/05/05
#			  3/13/09 Changed Tiemout to 5 Sec
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################

<Prompt>	'Stoke[local]'
<Msg>		'Drop to QNX Shell...'
<TimeOut>	5
<Exec>		Getmytime
<Send>		'hidden enable 2'
<WaitFor>	'Password:'
#hard coded password
<Send>		$hidden_password_glb
<Wait>
<GetData>
<Prompt>	'#'
<Send>		'start shell'
<Wait>
<GetData>

