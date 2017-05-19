################################################################################
#
# Module:      Check_IMC_Drive.inc
#
# Author:      Joe White
#
# Descr:       Include for Bench_IMC.dat
#
# Version:    1.2   $Id: Check_IMC_drives.inc,v 1.4 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Updated for 08/07/06 Diags
#
# Used By:
#				Bench_IMC.dat
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################s

<Msg>		"Check Internal Drives"
<TimeOut>	5
<Prompt>	"#"
<Send>			'ls -l /cfext'
<Wait>
<CheckData>	'.'
<CheckData>	'..'
<Send>			'ls -l /cfint'
<Wait>
<CheckData>	'.'
<CheckData>	'..'
<CheckData>	'.altboot'
<CheckData>	'.bitmap'
<CheckData>	'..boot'
<CheckData>	'.inodes'
<CheckData>	'.longfilenames'
<Send>			'ls -l /hd'
<Wait>
<CheckData>	'.'
<CheckData>	'..'
<CheckData>	'.altboot'
<CheckData>	'.bitmap'
<CheckData>	'..boot'
<CheckData>	'.inodes'
<CheckData>	'.longfilenames'
<CheckData>	'dump'


#<Msg>		'Tftp Stoke.bin to cfint'
#cp ftp:anonymous:password@192.168.64.113/stoke.bin /cfint/stoke.bin


<Msg>			'Copy Some files /cfint...'
<Send>			'cp /stoke/bin/diag/pfeffa /cfint/temp.tmp'
<Wait>
<CheckDataX>	"Can.t open destination file."
<CheckDataX>	"cp: Can't open source file"
<Send>			'ls /cfint/temp.tmp'
<Wait>
<CheckData>		'temp.tmp'
<Send>			'rm /cfint/temp.tmp'
<Wait>
<Sleep>			1
<Send>			'ls /cfint/temp.tmp'
<Wait>
<CheckData>		'No such file or directory'

<Msg>			'Copy Some files /cfext...'
<Send>			'cp /stoke/bin/diag/pfeffa /cfext/temp.tmp'
<Wait>
<CheckDataX>	'Can't open destination file.  (/cfext/temp.tmp)'
<CheckDataX>	"cp: Can't open source file"
<Send>			'ls /cfext/temp.tmp'
<Wait>
<CheckData>		'temp.tmp'
<Send>			'rm /cfext/temp.tmp'
<Wait>
<Sleep>			1
<Send>			'ls /cfext/temp.tmp'
<Wait>
<CheckData>		'No such file or directory'


<Msg>			'Copy Some files /hd...'
<Send>			'cp /stoke/bin/diag/pfeffa /hd/temp.tmp'
<Wait>
<CheckDataX>	'Can't open destination file.  (/hd/temp.tmp)'
<CheckDataX>	"cp: Can't open source file"
<Send>			'ls /hd/temp.tmp'
<Wait>
<CheckData>		'temp.tmp'
<Send>			'rm /hd/temp.tmp'
<Wait>
<Sleep>			1
<Send>			'ls /hd/temp.tmp'
<Wait>
<CheckData>		'No such file or directory'





