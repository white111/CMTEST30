################################################################################
#
# Module:      Stop_stoke_bootloader.inc
#
# Author:      Joe White
#
# Descr:       Called by Dat and Inc files
#
# Version:    1.7 $Id: Stop_stoke_bootloader.inc,v 1.1 2011/12/12 22:54:27 joe Exp $
#
# Changes:    Created for 3.0  09/22/06
#			  12/12/07 Added change for Bootloader Auto stopping due to corrupt/new drive
#			  Added addtional 1 second sleep, for USB based serial ports
#			  Hidden enable bootloader commands
#			  Upped wait time for password prompt to 10sec 6/5/09
#			  Added Sleep 1.  Seeing reboots during stop at bootloader
#			  Added Issue disable 2/3/10
#			  Added extra Send/wait 2/1/11
#		      Added checks for restarting stata
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################
<Msg>		"Stopping Stoke bootup at bootloader.."
<Prompt>	"Stoke-BootLoader#"
<TimeOut>	120
#Type 'stoke' now to invoke boot CLI, or boot will continue in  3
# Will not work for New bootlodaer as on 12/07.  Auto stops if drive is corrupted.
#<WaitFor>	" or boot will continue in  3 seconds"
#message just befor or boot will continue in  3 seconds
<Waitfor> 	"Stoke Bootloader"
<TimeOut>	5
<sleep>				1
<SendSlowChar>		"stoke"
#Need this for some reason
<sleep>				1
<SendSlowChar>		"stoke"
<Send>
<Wait>
<GetData>
<CheckDataX>	"FAIL"
<CheckDataX>	"Restarting"
<CheckDataX>	"restarting"
#<CheckDataX>	"ERROR"

#Clear the extra text
<Send>
<Wait>

# Needed to wait for the drives to be up and running?
<Sleep>		20

#Clear the extra text
<Msg>		'Disable issu...'
<Send> "system issu disable"
<Wait>

<Msg>		'Enable Bootloader commands Shell...'
<TimeOut>	10
<Exec>		Getmytime
<sleep>		5
<send>
<Wait>
<Send>		$hidden_password_glb
<Wait>
<Send>		'hidden enable 2'
<WaitFor>	'Password:'
<Send>		$hidden_password_glb
<Wait>
<GetData>


