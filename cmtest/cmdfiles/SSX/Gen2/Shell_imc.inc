 ################################################################################
#
# Module:      Shell_imc.inc
#
# Author:      Joe White
#
# Descr:       Called by Clean_IMC_drives.inc
#
# Version:    1.3 $Id: Shell_imc.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Added <GetData>  12/05/05
#			  3/13/09 Changed Tiemout to 5 Sec
#			  Added Set terminal width 1/31/12
#			  6/10/13 Prompt changes in 6.1R2 
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################

<Prompt>	"[local]#"
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

<msg>		"Set terminal Column width"
<Send>		'COLUMNS=160'
<Wait>
<GetData>

