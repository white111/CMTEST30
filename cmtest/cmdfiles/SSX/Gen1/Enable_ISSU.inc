 ################################################################################
#
# Module:      Enable_ISSU.inc
#
# Author:      Joe White
#
# Descr:       Called by Config.dat
#
# Version:    1.7 $Id: Enable_ISSU_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 01/13/09
#			  6/10/09 Modified for ISSUE enable
#			  8/4/09 Formatting change for 4.5
#             020910 Modifications for Bud 14408 4.6 release
#			  060710 addded # Added 4.6B2
#			  Updated for 6.0 1/31/12
#			  Removed <CheckData>	"  Configuration File:   stoke.cfg"  81/12
#			  6/10/13 Prompt changes in 6.1R2/13.1
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################


#<Include>	Wait_Card_Stoke.inc
<Msg>		"Waiting for system before applying ISSU package"
<sleep>   180
#<Include>	Show_Card_Stoke.inc
<TimeOut>	10
#Added as of 4.6  Bug 14408
<MSG>		"Create Links"
 <Include>	Shell_imc.inc
 <send>		 "mkdir /hdp/issu"
 <wait>
 <send>		 "ls /hdp/issu"
 <wait>
  <send>		 "mkdir /hdp/images"
 <wait>
 <send>		 "ls /hdp/images"
 <wait>

 <Send>     "touch /hdp/issu/issu_mode"
 <wait>
# # Added 4.6B2
# <Send>     "touch /hdp/etc/stos_version.txt"
# <wait>

 <Bypass>	$HA_Session
 	<send>		 "mkdir /net/nv-1-0/hdp/issu"
 	<wait>
 	<send>		 "ls /net/nv-1-0/hdp/issu"
 	<wait>
 	<Send>     "touch /net/nv-1-0/hdp/issu/issu_mode"
 	<wait>
#    # Added 4.6B2
#    <Send>     "touch /hdp/etc/stos_version.txt"
#    <wait>

	<send>		 "mkdir /net/nv-1-0/hdp/images"
 	<wait>
 	<send>		 "ls /net/nv-1-0/hdp/images"
 	<wait>
</Bypass>
<Prompt>	"[local]#"
 <send>		exit
 <wait>
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
#<Prompt>    'no'
#<Send>      'system install package /hd/stokeS1.pkg'
#<Wait>
#<Prompt>    'Stoke[local]#'
#<Send>      'y'
#<wait>
#<CheckData> "Installation complete"
#<checkdatax> "ERROR"
#<Getdata>
#<Prompt>    'Stoke[local]#'
<Send>      'boot image issu'
<wait>
<GetData>

#Added as of 4.6  Bug 14408
<MSG>		"Create Links part 2"
 <Include>	Shell_imc.inc
 <send>		 "cd /hdp/issu"
 <wait>
 #<Send>     "ln -sf /hdp/images/4.6B1 last_successful_link"
 <Sendchr>     "ln -sf /hdp/images/"
 <Sendchr>		$StokeOS_release_gbl
 <Send>		" last_successful_link"
 <wait>
  <send>		 "cd /hdp/images"
 <wait>
 #<Send>     "ln -sf /hdp/images/4.6B1 current"
 <Sendchr>     "ln -sf /hdp/images/"
 <sendchr>	$StokeOS_release_gbl
 <send>		" current"
 <wait>
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
 <Bypass>	$HA_Session
	<send>		 "cd /net/nv-1-0/hdp/issu"
 	<wait>
 	#<Send>     "ln -sf /net/nv-1-0/hdp/images/4.6B1 last_successful_link"
 	<Sendchr>     "ln -sf /net/nv-1-0/hdp/images/"
 	<Sendchr>	$StokeOS_release_gbl
 	<Send>		" /net/nv-1-0/hdp/images/last_successful_link"
 	<wait>
  	<send>		 "cd /net/nv-1-0/hdp/images"
 	<wait>
 	#<Send>     "ln -sf /net/nv-1-0/hdp/images/4.6B1 current"
 	<Sendchr>     "ln -sf /net/nv-1-0/hdp/images/"
 	<sendchr>	$StokeOS_release_gbl
 	<Send>		" /net/nv-1-0/hdp/images/current"
 	<wait>
  	#<Send>     "ln -sf /net/nv-1-0/hdp/images/4.6B1 revert"
  	<Sendchr>     "ln -sf /net/nv-1-0/hdp/images/"
  	<SendChr>	$StokeOS_release_gbl
  	<Send>		" /net/nv-1-0/hdp/images/revert"
 	<wait>
  	#<Send>     "ln -sf /net/nv-1-0/hdp/images/4.6B1 revert_old"
  	<Sendchr>     "ln -sf /net/nv-1-0/hdp/images/"
  	<sendchr>  $StokeOS_release_gbl
  	<Send>		" /net/nv-1-0/hdp/images/revert_old"
 	<wait>
</Bypass>
 <Prompt>	"[local]#"
 <send>		exit
 <wait>
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


#<Include>	Wait_Card_Stoke.inc
<Msg>		"Waiting 300 Sec for system to complete ISSU soak phase"
<Sleep>		360
<Send>
<Wait>
<GetData>	Check_IMC_0_Standby_Prompt
<Bypass>	$IMC_0_Standby
	<Msg>       "Switch Slot 0 Active"
	<sleep>     10
	<timeout>   60
	<prompt>    "Proceed"

	<Send>      "system imc"
	<wait>
	<Prompt>    "[local]#"
	<Send>      "y"
	<wait>
	<getdata>
	<checkdatax>    "fail"
	<sleep>		5
	<Msg>		"Waiting 300 Sec IMC to reload"
	<Sleep>		360
</bypass>

<Include>	Show_Card_Stoke.inc
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
<getdata>
<Msg>		"Waiting for system..."
<sleep>   180
<Send>
<Wait>
<GetData>	Check_IMC_0_Standby_Prompt
<Bypass>	$IMC_0_Standby
	<Msg>       "Switch Slot 0 Active"
	<sleep>     10
	<timeout>   60
	<prompt>    "Proceed"

	<Send>      "system imc"
	<wait>
	<Prompt>    "[local]#"
	<Send>      "y"
	<wait>
	<getdata>
	<checkdatax>    "fail"
	<Msg>		"Waiting 300 Sec IMC to reload"
	<Sleep>		360
</bypass>
#<Include>	Wait_Card_Stoke.inc
<Msg>		"Waiting for system..."
<sleep>   180
<Include>	Show_Card_Stoke.inc

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



