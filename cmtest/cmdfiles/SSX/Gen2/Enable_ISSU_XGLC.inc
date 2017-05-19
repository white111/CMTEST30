 ################################################################################
#
# Module:      Enable_ISSU.inc
#
# Author:      Joe White
#
# Descr:       Called by Config.dat
#
# Version:    1.8 $Id: Enable_ISSU_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 01/13/09
#			  6/10/09 Modified for ISSUE enable
#			  8/4/09 Formatting change for 4.5
#             020910 Modifications for Bud 14408 4.6 release
#			  060710 addded # Added 4.6B2
#			  Updated for 6.0 1/31/12
#			  Removed <CheckData>	"  Configuration File:   stoke.cfg"  81/12
#			  6/10/13 Prompt changes in 6.1R2/13.1
#			  9/3/14 Corrected IMC ISSU last succesful link setup
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2014 Stoke. All rights reserved.
#
################################################################################


#<Include>	Wait_Card_Stoke.inc
<Msg>		"Waiting for system before applying ISSU package"
<sleep>   180
#<Include>	Show_Card_Stoke_XGLC.inc
<TimeOut>	10
#Added as of 4.6  Bug 14408
<MSG>		"Create Links IMC 0"
 <Include>	Shell_imc.inc
 <send>		 "rm -r /hdp/issu"
 <wait>
 <send>		 "mkdir /hdp/issu"
 <wait>
 <checkdatax>	"No such file or directory"
 <send>		 "ls /hdp/issu"
 <wait>
 <checkdatax>	"No such file or directory"
  <send>		 "rm -r /hdp/images"
 <wait>
  <send>		 "mkdir /hdp/images"
 <wait>
 <checkdatax>	"No such file or directory"
 <sendchr>       "mkdir /hdp/images/"
 <send>       "$StokeOS_release_gbl"
 <wait>
 <checkdatax>	"No such file or directory"
 <send>		 "ls /hdp/images"
 <wait>
 <checkdatax>	"No such file or directory"
 <send>		 "rm -r /hdp/settings"
 <wait>
 <send>		 "mkdir /hdp/settings"
 <wait>
 <checkdatax>	"No such file or directory"
  <send>		 "ls /hdp/settings"
 <wait>
 <checkdatax>	"No such file or directory"
 <Send>     "touch /hdp/issu/issu_mode"
 <wait>
 <checkdatax>	"No such file or directory"
  <send>		 "ls /hdp/issu/issu_mode"
 <wait>
 <checkdatax>	"No such file or directory"
 # Added 4.6B2
# <Send>     "touch /hdp/etc/stos_version.txt"
# <wait>
<Prompt>	"[local]#"
 <send>		exit
 <wait>

 <Bypass>   $HA_Session
    <MSG>       "Create Links IMC 1"
    <Exec>  Swap_cons
    <Include>   Shell_imc.inc
    <send>       "rm -r /hdp/issu"
    <wait>
    <send>       "mkdir /hdp/issu"
    <wait>
    <checkdatax> "No such file or directory"
    <send>       "ls /hdp/issu"
    <wait>
    <checkdatax> "No such file or directory"
    <send>       "rm -r /hdp/images"
    <wait>
    <send>       "mkdir /hdp/images"
    <wait>
    <checkdatax> "No such file or directory"
    <sendchr>       "mkdir /hdp/images/"
    <send>       "$StokeOS_release_gbl"
    <wait>
    <checkdatax> "No such file or directory"
    <send>       "ls /hdp/images"
    <wait>
    <checkdatax> "No such file or directory"
    <send>       "rm -r /hdp/settings"
    <wait>
    <send>       "mkdir /hdp/settings"
    <wait>
    <checkdatax> "No such file or directory"
    <send>       "ls /hdp/settings"
    <wait>
    <checkdatax> "No such file or directory"
    <Send>     "touch /hdp/issu/issu_mode"
    <wait>
    <checkdatax> "No such file or directory"
    <send>       "ls /hdp/issu/issu_mode"
    <wait>
    <checkdatax> "No such file or directory"
    # Added 4.6B2
    # <Send>     "touch /hdp/etc/stos_version.txt"
    # <wait>
    <Prompt>    "[local]#"
    <send>      exit
    <wait>
    <Exec>  Swap_cons
</Bypass>

#
<TimeOut>	120
<msg>		"Install ISSU packages"
<msg>		$StokeOS_ISSU_Install_gbl
<Prompt>	"[local]#"
<Prompt>	'no'
<Sendchr>		'system install package /hd/'
<Send>       $StokeOS_ISSU_Install_gbl
<Wait>
<Prompt>	"[local]"
<Send>		'y'
<wait>
<CheckData>	"Installation complete"
<checkdatax> "ERROR"
<Getdata>
<Send>      'boot image issu'
<wait>
<GetData>

#Added as of 4.6  Bug 14408
<MSG>		"Create Links part 2 IMC 0"
 <Include>	Shell_imc.inc
 <send>		 "cd /hdp/issu"
 <wait>
 #<Send>     "ln -sf /hdp/images/4.6B1 last_successful_link"
 <Sendchr>     "ln -sf /hdp/images/"
 <Sendchr>		$StokeOS_release_gbl
 <Send>		" last_successful_link"
 <wait>
 <checkdatax>  "No such file or directory"
 <send>		"ls issu_mode"
 <wait>
 <checkdatax>  "No such file or directory .issu_mode"
 <getData>
  <send>		 "cd /hdp/images"
 <wait>
 #<Send>     "ln -sf /hdp/images/4.6B1 current"
 <Sendchr>     "ln -sf /hdp/images/"
 <sendchr>	$StokeOS_release_gbl
 <send>		" current"
 <wait>
 <getData>
  #<Send>     "ln -sf /hdp/images/4.6B1 revert"
  <Sendchr>     "ln -sf /hdp/images/"
  <sendchr>		$StokeOS_release_gbl
  <Send>		" revert"
 <wait>
  #<Send>     "ln -sf /hdp/images/4.6B1 revert_old"
  <Sendchr>     "ln -sf /hdp/images/"
  <Sendchr>	 $StokeOS_release_gbl
  <Send>	 " revert_old"
 <wait>
  <Prompt>	"[local]#"
 <send>		exit
 <wait>

 <Bypass>   $HA_Session
    <MSG>       "Create Links part 2 IMC 1"
    <Exec>  Swap_cons
    <Include>   Shell_imc.inc
    <send>       "cd /hdp/issu"
    <wait>
    #<Send>     "ln -sf /hdp/images/4.6B1 last_successful_link"
    <Sendchr>     "ln -sf /hdp/images/"
    <Sendchr>       $StokeOS_release_gbl
    <Send>      " last_successful_link"
    <wait>
    <checkdatax>  "No such file or directory"
    <send>      "ls issu_mode"
    <wait>
    <checkdatax>  "No such file or directory .issu_mode"
    <getData>
    <send>      "cd /hdp/images"
    <wait>
    #<Send>     "ln -sf /hdp/images/4.6B1 current"
    <Sendchr>     "ln -sf /hdp/images/"
    <sendchr>   $StokeOS_release_gbl
    <send>      " current"
    <wait>
    #<Send>     "ln -sf /hdp/images/4.6B1 revert"
    <Sendchr>     "ln -sf /hdp/images/"
    <sendchr>       $StokeOS_release_gbl
    <Send>      " revert"
    <wait>
    #<Send>     "ln -sf /hdp/images/4.6B1 revert_old"
    <Sendchr>     "ln -sf /hdp/images/"
    <Sendchr>    $StokeOS_release_gbl
    <Send>   " revert_old"
    <wait>
     <Prompt>   "[local]#"
    <send>      exit
    <Exec>  Swap_cons
</Bypass>

#

#testing booting 4.5 and appling 4.6 pkg
#<Send>      'system issu enable'
#<wait>
#<GetData>
#<CheckData> "ISSU mode enabled"



#removed as of 4.6  bug 14408
#<Msg>       "Apply ISSU package:"
#<Msg>       $StokeOS_ISSU_Apply_gbl
#<Prompt>    'no'
#<Sendchr>   'system select package '
#<Send>      $StokeOS_ISSU_Apply_gbl
#<Wait>
#<CheckData> "System will be automatically reloaded"
#<checkdatax> "ERROR - Package .* not found"
#<checkdatax> "ERROR - Upgrade pre-sanity checks failed"
#<Getdata>

	<msg>		"Check links on IMC in Slot 0"
	<timeout>	90
##    <Send>      'system issu disable'
##    <wait>
##    <GetData>
##    <Send>      'system issu enable'
##    <wait>
##    <GetData>
##    <CheckData> "ISSU mode enabled"
    <MSG>       "Check IMC slot 1 ISSU"
    <Include>   Shell_imc.inc
    <send>       "cd /hdp/issu"
    <wait>
    <checkdatax>  "No such file or directory"
    <send>      "ls last_successful_link/stoke.bin"
    <wait>
    <checkdatax>  "No such file or directory .last_successful_link.stoke.bin"
    <send>      "ls issu_mode"
    <wait>
    <checkdatax>  "No such file or directory .issu_mode"
    <getData>
    <send>      "cd /hdp/images"
    <wait>
    <send>      "ls current/stoke.bin"
    <wait>
    <checkdatax>  "No such file or directory .current.stoke.bin"
    <getData>
    <send>      "ls revert/stoke.bin"
    <wait>
    <checkdatax>  "No such file or directory .revert.stoke.bin"
    <send>      "ls revert_old/stoke.bin"
    <wait>
    <checkdatax>  "No such file or directory .revert_old.stoke.bin"
     <Prompt>   "[local]#"
    <send>      exit

<Bypass>   $HA_Session
 #	<msg>		"Force IMC in Slot 1 to sync"
	<timeout>	90
##    <Send>      'system issu disable'
##    <wait>
##    <GetData>
##    <Send>      'system issu enable'
##    <wait>
##    <GetData>
##    <CheckData> "ISSU mode enabled"
    <MSG>       "Check IMC slot 1 ISSU"
    <msg>		"Check links on IMC in Slot 1"
    <Exec>  Swap_cons
    <Include>   Shell_imc.inc
    <send>       "cd /hdp/issu"
    <wait>
    <send>      "ls last_successful_link/stoke.bin"
    <wait>
    <checkdatax>  "No such file or directory .last_successful_link.stoke.bin"
    <send>      "ls issu_mode"
    <wait>
    <checkdatax>  "No such file or directory .issu_mode"
    <getData>
    <send>      "cd /hdp/images"
    <wait>
    <send>      "ls current/stoke.bin"
    <wait>
    <checkdatax>  "No such file or directory .current.stoke.bin"
    <getData>
    <send>      "ls revert/stoke.bin"
    <wait>
    <checkdatax>  "No such file or directory .revert.stoke.bin"
    <send>      "ls revert_old/stoke.bin"
    <wait>
    <checkdatax>  "No such file or directory .revert_old.stoke.bin"
     <Prompt>   "[local]#"
    <send>      exit
    <Exec>  Swap_cons
</Bypass>

<include>	Ship_config.inc
<Prompt>	'yes'
<send>		"reload"
<wait>
<Prompt>	"[local]#"
<Send>		'y'
<sleep>		1
<Send>		'y'

<Msg>		"Waiting for system reload after applying ISSU package"
<sleep>		10
<timeout>   360
<Prompt>	'StokeBoot'
<Send>
<wait>
<getdata>
<Prompt>	"[local]#"
<Send>
<wait>
<getdata>
<checkdatax>	"fail"
<icheckdatax>	"ERROR"
<icheckdatax>	"could not open file"


#<Include>	Wait_Card_Stoke.inc
<Msg>		"Waiting 300 Sec for system to complete ISSU soak phase"
<Sleep>		360
<Send>
<Wait>
<GetData>	Check_IMC_0_Standby_Prompt
<Bypass>	$IMC_0_Standby
	<Msg>       "Switch Slot 0 Active"
	<sleep>     10
	<timeout>   200
	<prompt>    "Proceed"

	<Send>      "system imc"
	<wait>
	<Prompt>    "[local]#"
	<Send>      "y"
	<wait>
	<getdata>
	<checkdatax>	"fail"
	<icheckdatax>	"ERROR"
	<icheckdatax>	"could not open file"
	<sleep>		5
	#<Msg>		"Waiting 300 Sec IMC to reload"
	#<Sleep>		360
	<Exec>  Swap_cons
	<Prompt>    "SB[local]#"
	<timeout>   400
	<Send>
	<wait>
	<Getdata>
	<sleep> 5
	<Send>
	<wait>
	<Getdata>
     <Exec>  Swap_cons
</bypass>

<Include>	Show_Card_Stoke_XGLC.inc
<Prompt>	'yes'
<send>		"reload"
<wait>
<Prompt>	'[local]#'
<Send>		'y'
<sleep>		1
<Send>		'y'
<Msg>		"Reload System after ISSU install completed.."
<sleep>		10
<timeout>   360
<wait>
<checkdatax>	"Card . is flashing"
<checkdatax>	"fail"
<icheckdatax>	"ERROR"
<icheckdatax>	"could not open file"
<getdata>
<Msg>		"Waiting for system..."
<sleep>   180
<Send>
<Wait>
<GetData>	Check_IMC_0_Standby_Prompt
<Bypass>	$IMC_0_Standby
	<Msg>       "Switch Slot 0 Active"
	<sleep>     10
	<timeout>   200
	<prompt>    "Proceed"

	<Send>      "system imc"
	<wait>
	<Prompt>    "[local]#"
	<Send>      "y"
	<wait>
	<getdata>
	<checkdatax>    "fail"
	<getdata>
	<checkdatax>	"fail"
	<icheckdatax>	"ERROR"
	<icheckdatax>	"could not open file"
	#<Msg>		"Waiting 300 Sec IMC to reload"
	#<Sleep>		360
	<Exec>  Swap_cons
	<Prompt>    "SB[local]#"
	<timeout>   400
	<Send>
	<wait>
	<Getdata>
	<Sleep> 5
	<Send>
	<wait>
	<Getdata>
     <Exec>  Swap_cons
</bypass>
#<Include>	Wait_Card_Stoke.inc
<Msg>		"Waiting for system..."
<sleep>   180
<Include>	Show_Card_Stoke_XGLC.inc

<Send>		"show upgrade status"
<Wait>
<Getdata>
<CheckData>	   "No ISSU Operation in progress"

<Send>		'terminal length infinite'
<Wait>
#<Send>      'system issu enable'
#<wait>
#<GetData>
#<CheckData> "ISSU mode enabled"

<send>		"show system boot"
<wait>
<CheckData>	"System Hostname: Stoke"
<CheckData>	"System Location:"
<CheckData>	"System Contact:"

<CheckData>	"Console Port Baud Rate: 9600 Baud"

<CheckData>	"Current Boot:"
<CheckData>	"  Boot Type:           Local"
<CheckData>	"  Image File:          ISSU"
#<CheckData>	"  Configuration File:   stoke.cfg"
<CheckData>	"  Classes per Session:  8"
<CheckData>	"  Sessions per GLC:     22500"
<CheckData>	"Next Boot:"
<CheckData>	"  Boot Type:           Local"
<CheckData>	"  Image File:          ISSU"
#<CheckData>	"  Configuration File:   stoke.cfg"
<CheckData>	"  Classes per Session:  8"
<CheckData>	"  Sessions per GLC:     22500"

# removed in 4.6 <CheckData>	"ISSU mode:  enabled"
<CheckData>	"In-Use Packages:"
<CheckData> $show_sys_ISSU_in_use_gbl
#<CheckData> "Other Packages:"
#<CheckData> $show_sys_ISSU_other_gbl
<Getdata>



