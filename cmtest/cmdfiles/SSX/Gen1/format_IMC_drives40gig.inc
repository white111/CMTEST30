################################################################################
#
# Module:      format_IMC_drive.inc
#
# Author:      Joe White
#
# Descr:       Called by Bench_IMC.dat
#
# Version:    1.1 $Id: format_IMC_drives40gig.inc,v 1.1 2009/09/28 17:21:45 joe Exp $
#
# Changes:    Added <GetData> 12/05/05
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################

<Include>	tftpcopy_stoke_diag.inc
<TimeOut>	2
<Prompt>	"#"
<TimeOut>	120
<Msg>		"Format drives IMC Slot 0..."
<Send>		'sh /cfint/formatto40gigpartition.sh'
<Wait>
<GetData>
<CheckData>	'Start SATA driver'
<CheckData>	'Harddrive Drive partitions set to 40gig'
<CheckData>	'Start a fresh copy of the SATA driver'
<CheckData>	'Initialize the disk'
<CheckData>	'Mount the file system and create subdirectories'
<CheckData>	'Hard disk is ready'

<CheckData>	'Fire them all up with storaged'
<CheckData>	'storageprep done'
<CheckData> "1. QNX       77          0      38159     38159  78151648  38159 MB"
<CheckData> "2. QNY       78      38160      76318     38158  78149632  38159 MB   \*"

<CheckDataX> 'Memory fault'
<CheckDataX> 'Unable to access /dev/hd0t77'
<CheckDataX> 'Unable to access /dev/hd0t78'




<Bypass>	$Slot_INST_1_IMC_GBL
	<Exec>	Swap_cons
	<Msg>		"Format drives IMC Slot 1..."
	#<Include>	tftpcopy_stoke_diag.inc
	<TimeOut>	2
	<Prompt>	"#"
	<TimeOut>	120
	<Send>		'sh /cfint/formatto40gigpartition.sh'
	<Wait>
	<GetData>
	<CheckData>	'Start SATA driver'
	<CheckData>	'Harddrive Drive partitions set to 40gig'
	<CheckData>	'Start a fresh copy of the SATA driver'
	<CheckData>	'Initialize the disk'
	<CheckData>	'Mount the file system and create subdirectories'
	<CheckData>	'Hard disk is ready'

	<CheckData>	'Fire them all up with storaged'
	<CheckData>	'storageprep done'
	<CheckData> "1. QNX       77          0      38159     38159  78151648  38159 MB"
	<CheckData> "2. QNY       78      38160      76318     38158  78149632  38159 MB   \*"


	<CheckDataX> 'Memory fault'
	<CheckDataX> 'Unable to access /dev/hd0t77'
	<CheckDataX> 'Unable to access /dev/hd0t78'
	<Exec>	Swap_cons
</Bypass>

<Msg>		"Reset system after drive format"

<Prompt>	"#"
<Send>		"reset board"
<TimeOut>	120
# Make sure this system message does not pop out in the miidle of tests
<WaitFor>     "System process not started within designated time"
<Send>
<Wait>

<Send>
<Wait>

