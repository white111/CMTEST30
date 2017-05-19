 ################################################################################
#
# Module:      Check_Software_version.inc
#
# Author:      Joe White
#
# Descr:       Checks software versions on a full 5 slot chassis
#
# Version:    1.4  $Id: Check_Software_version.inc,v 1.6 2010/03/12 18:50:59 joe Exp $
#
# Changes:    Add <GetData> 12/05/05
#			  Updated for 3.0 bootloader added to all cards
#			  Check Software Versions Slot 1 bypassed bug 14440 3/3/10
#
# Includes:
#
#
#
# Still ToDo:
#            Make flexable for different configurations
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"^Stoke.local.#"
<TimeOut>	10
<Msg>		"Check Software Versions"
<Send>		'terminal length infinite'
<Wait>
<GetData>

<Msg>		"Check Software Versions Slot 0"
<Send>		"show ver slot 0"
#<WaitFor>	"Info"
<Wait>
<GetData>
<CheckData>		$Software_OS_release_gbl
#<CheckData>	    "Boot Image File: stoke\.bin"
#<CheckData>	    "Boot Configuration File: stoke\.cfg"

<CheckData>	    "Firmware Version: v"
<CheckData>	    $firmware_ver_gbl
<CheckData>		"Stoke-Boot Version"
<CheckData>	    "Booted Primary:"
<CheckData>	    $Stoke_boot_ver_gbl
<CheckData>	    "Booted Backup:"
<CheckData>		$Stoke_boot_ver_gbl
<CheckData>		"Stoke-Bloader Version"
<CheckData>	    "Booted Primary:"
<CheckData>	    $Stoke_bootloader_ver_gbl
<CheckData>	    "Booted Backup:"
<CheckData>		$Stoke_bootloader_ver_gbl
# Debug only <Msg>			"Bypassed checking for diag jumper"
<CheckDataX>	"SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"

<Msg>    "Check Software Versions Slot 1 bypassed bug 14440"
#<Bypass>    $Slot_INST_1_GBL
#    <Msg>       "Check Software Versions Slot 1"
#    <Send>      "show ver slot 1"
#    <WaitFor>   "Information"
#    <Wait>
#    <GetData>
#    <CheckData>     "Firmware Version: v"
#    <CheckData>     $firmware_ver_gbl
#    <CheckData>     "Booted Primary:"
#    <CheckData>     $Stoke_boot_ver_gbl
#    <CheckData>     "Booted Backup:"
#    <CheckData>     $Stoke_boot_ver_gbl
#    <CheckData>     "Stoke-Bloader Version"
#    <CheckData>     "Booted Primary:"
#    <CheckData>     $Stoke_bootloader_ver_gbl
#    <CheckData>     "Booted Backup:"
#    <CheckData>     $Stoke_bootloader_ver_gbl
#    # Debug only <Msg>          "Bypassed checking for diag jumper"
#    <CheckDataX>    "SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"
#</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>		"Check Software Versions Slot 2"
	<Send>		"show ver slot 2"
	<WaitFor>	"Information"
	<Wait>
	<GetData>
	<CheckData>	    "Firmware Version: v"
	<CheckData>	    $firmware_ver_gbl
	<CheckData>	    "Booted Primary:"
	<CheckData>	    $Stoke_boot_ver_gbl
	<CheckData>	    "Booted Backup:"
	<CheckData>		$Stoke_boot_ver_gbl
	<CheckData>		"Stoke-Bloader Version"
	<CheckData>	    "Booted Primary:"
	<CheckData>	    $Stoke_bootloader_ver_gbl
	<CheckData>	    "Booted Backup:"
	<CheckData>		$Stoke_bootloader_ver_gbl
	# Debug only <Msg>			"Bypassed checking for diag jumper"
	<CheckDataX>	"SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>		"Check Software Versions Slot 3"
	<Send>		"show ver slot 3"
	<WaitFor>	"Information"
	<Wait>
	<GetData>
	<CheckData>	    "Firmware Version: v"
	<CheckData>	    $firmware_ver_gbl
	<CheckData>	    "Booted Primary:"
	<CheckData>	    $Stoke_boot_ver_gbl
	<CheckData>	    "Booted Backup:"
	<CheckData>		$Stoke_boot_ver_gbl
	<CheckData>		"Stoke-Bloader Version"
	<CheckData>	    "Booted Primary:"
	<CheckData>	    $Stoke_bootloader_ver_gbl
	<CheckData>	    "Booted Backup:"
	<CheckData>		$Stoke_bootloader_ver_gbl
	# Debug only <Msg>			"Bypassed checking for diag jumper"
	<CheckDataX>	"SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>		"Check Software Versions Slot 4"
	<Send>		"show ver slot 4"
	<WaitFor>	"Information"
	<Wait>
	<GetData>
	<CheckData>	    "Firmware Version: v"
	<CheckData>	    $firmware_ver_gbl
	<CheckData>	    "Booted Primary:"
	<CheckData>	    $Stoke_boot_ver_gbl
	<CheckData>	    "Booted Backup:"
	<CheckData>		$Stoke_boot_ver_gbl
	<CheckData>		"Stoke-Bloader Version"
	<CheckData>	    "Booted Primary:"
	<CheckData>	    $Stoke_bootloader_ver_gbl
	<CheckData>	    "Booted Backup:"
	<CheckData>		$Stoke_bootloader_ver_gbl
	# Debug only <Msg>			"Bypassed checking for diag jumper"
	<CheckDataX>	"SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"
</Bypass>

<Send>
<Wait>





