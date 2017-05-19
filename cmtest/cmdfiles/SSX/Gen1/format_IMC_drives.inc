################################################################################
#
# Module:      format_IMC_drive.inc
#
# Author:      Joe White
#
# Descr:       Called by Bench_IMC.dat
#
# Version:    1.3 $Id: format_IMC_drives.inc,v 1.7.4.1 2012/02/10 04:48:16 joe Exp $
#
# Changes:    Added <GetData> 12/05/05
#			  Chaged format to Fixed 40gig for HD and 128Meg for CF
#			  cmtest now download stroageprep.sh and copies to /tmp 8/19/09
#             01/25/12 Changes to Cfint formatting Bug 18719
#			  09/01/14 Changes to cfint formatting  QNX to ahve 123 or 124 cy
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
<Msg>		"Format drives..."
<TimeOut>	2
<Prompt>	"#"
<Send>
<Wait>
# Send cp /cfint/storageprep80.sh /tmp
<Sendchr> 		"cp /cfint/"
<sendchr>		$Format_MC
<send>			" /tmp"
<Wait>
<GetData>
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
<TimeOut>	120
#<Send>		'sh /stoke/bin/util/storageprep.sh'
#<Send>		'sh /tmp/storageprep.sh'
<SendChr>	'sh /tmp/'
<Send>		$Format_MC
<Wait>
<GetData>
<CheckData>	'Start SATA driver'
<CheckData>	'Partition hard drive'
<CheckData>	'Start a fresh copy of the SATA driver'
<CheckData>	'Initialize the disk'
<CheckData>	'Mount the file system and create subdirectories'
<CheckData>	'Hard disk is ready'

<CheckData>	'Start pccard controller driver'
<CheckData>	'Start devb-eide driver for internal compact flash'
<CheckData>	'Partition the internal compact flash'
<CheckData>	'Start a fresh copy of the EIDE driver'
<CheckData>	'Initialize the compact flash drive'
<CheckData>	'Mount the file system'
<CheckData>	'Internal CF ready'

<CheckData>	'Start devb-eide driver for external compact flash'
<CheckData>	'Partition and format the external compact flash'

<CheckData>	'Format complete'
#					: FAT32 (4096-byte clusters), 125176 kB available'
<CheckData>	'Start a fresh copy of the EIDE driver'
<CheckData>	'Mount the file system'
<CheckData>	'External CF ready'

<CheckData>	'Slay all drivers'
<CheckData>	'Fire them all up with storaged'
<CheckData>	'storageprep done'

<CheckDataX> 'Memory fault'
<CheckDataX> 'Unable to access /dev/hd0t77'
<CheckDataX> 'Unable to access /dev/hd0t78'


<send>	"fdisk /dev/cfint0 info"
<wait>
<GetData>
<send>	"fdisk /dev/cfint0 show"
<wait>
<Getdata>
#/cfintp
<CheckData> "1. QNX       77          0        .*    1[12][38] MB"
#<CheckData> "1. QNX       77          0        123       12[34]    253920    123 MB"

#/cfint
<CheckData> "2. QNY       78        .*    251904    123 MB   \*"
#<CheckData> "2. QNY       78        124        246       122    251904    123 MB   \*"

<send>	"fdisk /dev/hd0 info"
<wait>
<GetData>
<send>	"fdisk /dev/hd0 show"
<wait>
<Getdata>
<CheckData> "1. QNX       77          0      38159     381[56][09]  78151648  38159 MB"
<CheckData> "2. QNY       78      38160      76318     3815[89]  78149632  38159 MB   \*"

