################################################################################
#
# Module:      format_IMC_drives_bootloader.inc
#
# Author:      Joe White
#
# Descr:       Called by Bench_IMC.dat
#
# Version:    1.2  $Id: format_IMC_drives_bootloader.inc,v 1.3.8.1 2011/11/30 19:48:56 joe Exp $
#
# Changes:    Created 10/19/07, preformat drive at bootloader to get around post
#			  2.0 OS startup issue with unformated drives
#			  10/28/11 Adding time to dinit -hq /dev/hd0t77 ; dinit -hq /dev/hd0t78 for Seagate
#
#
# Still ToDo:
#
#
#            Copyright (c) 2007-2008 Stoke. All rights reserved.
#      fdisk /dev/hd0 delete -a   ;   fdisk /dev/cfint0 delete -a
################################################################################
<Prompt>	'Stoke-BootLoader'
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


<Msg>		"Format drives..."
<TimeOut>	30
<Prompt>	"#"
<Send>
<Wait>
<Sleep>		3
<Send>		'fdisk /dev/hd0 delete -a'
<Wait>
<Send>		'fdisk /dev/cfint0 delete -a'
<Wait>
<Sleep>		3
<Send>		'slay -f devb-mvSata'
<Wait>
<GetData>
<Sleep>		1
<Send>		'slay -f devb-eide'
<Wait>
<GetData>
<Sleep>		2
<Send>		'slay -f devb-eide'
<Wait>
<GetData>
<Sleep>		1
# Used when the full Stoke software is loaded
#	<WaitFor>	'(tty not known) (y/N)?'
#<SendChar>	y
#<Sleep>		1
#	<WaitFor>	'(tty not known) (y/N)?'
#<SendChar>	y
#<Sleep>		3
#<Send>
#<Wait>
<Send>		'pidin | grep devb'
<Wait>
<GetData>
<CheckDataX>	'pid tid name               prio STATE       Blocked'
<CheckDataX>	'devb-eide'
<Msg>		'Format HD ...'
<Send>		'slay devb-mvSata'
<Wait>
<sleep>		 2
<Send>		'devb-mvSata mvSata irq=68'

<Sleep>		5
<Send>
<Wait>

<Send>		'fdisk /dev/hd0 add -t77 -b -p50 ; fdisk /dev/hd0 add -t78 -b -p100'
<Wait>
<Send>		'slay devb-mvSata'
<Wait>
<sleep>		 2
<Send>		'devb-mvSata mvSata irq=68'

<Sleep>		5
<Send>
<Timeout>	90
<Wait>
<Sendslow>		'dinit -hq /dev/hd0t77 ; dinit -hq /dev/hd0t78'
<Wait>
<Timeout>	60
<Send>		'mount -tqnx4 /dev/hd0t77 /hdp ; mount -tqnx4 /dev/hd0t78 /hd'
<Wait>
<Timeout>	30
<Send>		"rm -R /hd/\*"
<Wait>
<Send>		"rm -R /hdp/\*"
<Wait>

<Msg>		'Format Cfint ...'

<Send> 		'devb-eide disk name=cfint eide ioport=0xe0000010:0xe000001c,irq=68,noslave'

<Sleep>		5
<Send>
<Wait>

<Send>		'fdisk /dev/cfint0 add -t77 -b -p50 ; fdisk /dev/cfint0 add -t78 -b -p100'
<Send>
<Wait>
<Send>		'slay -f devb-eide'
<Wait>
<sleep> 2
<Send>		'devb-eide disk name=cfint eide ioport=0xe0000010:0xe000001c,irq=68,noslave'

<Sleep>		5
<Send>
<Wait>
<Send>		'dinit -hq /dev/cfint0t77 ; dinit -hq /dev/cfint0t78'
<Wait>
<Timeout>	30
<Send>		'mount -tqnx4 /dev/cfint0t77 /cfintp ; mount -tqnx4 /dev/cfint0t78 /cfint'
<Wait>
<Timeout>	10
<Send>		'rm -R /cfint/\*'
<Wait>
<Send>		'rm -R /cfintp/\*'
<Wait>

<Prompt>	'Stoke-BootLoader'
<Send>      'exit'
<Wait>


