 ################################################################################
#
# Module:      Delete_dump_dir.inc
#
# Author:      Joe White
#
# Descr:       TFTP boots system from STOKE>> prompt to released Diag image
#
# Version:    1.1 $Id: Delete_dump_dir_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 11/18/11
#
# Includes:
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################

<Msg>		'Drop to QNX Shell...'
<TimeOut>	5
<Exec>		Getmytime
<Send>
<Wait>
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
<include>  Check_HDP_Log_Error_XGLC.inc
<msg>       "Removing /hd/dump"
<timeout>	20
<prompt>	'#'
<Send>      'ls /hd/dump'
<Wait>
<GetData>
<Send>      'rm -r /hd/dump/*'
<Wait>
<GetData>
<Send>      'ls /hd/dump'
<Wait>
<GetData>
<Send>      'ls /net/nv-1-0/hd/dump'
<Wait>
<GetData>
<Send>      'rm -r /net/nv-1-0/hd/dump/*'
<Wait>
<GetData>
<Send>      'ls /net/nv-1-0/hd/dump'
<Wait>
<GetData>
<Send>      'rm -r /net/nv-0-0/hdp/images/*'
<Wait>
<GetData>
<Send>      'rm -r /net/nv-1-0/hdp/images/*'
<Wait>
<GetData>
<Send>      'ls -als /net/nv-0-0/hdp/images'
<Wait>
<GetData>
<Send>      'ls -als /net/nv-1-0/hdp/images'
<Wait>
<GetData>
<Prompt>	'Stoke-BootLoader'
<Send>      'exit'
<Wait>

