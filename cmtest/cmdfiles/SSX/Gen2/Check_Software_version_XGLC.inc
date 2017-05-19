 ################################################################################
#
# Module:      Check_Software_version_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Checks software versions on a full 5 slot chassis
#
# Version:    1.2  $Id: Check_Software_version_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Create 11/18/11
#			  6/10/13 Prompt changes in 6.1R2
#			  Added Support for XGLC in Slot 1 9/3/13
#
#
#
# Includes:
#
#
#
# Still ToDo:
#            Make flexable for different configurations
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"[local]#"
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

<Bypass>    $Slot_INST_1_IMC_GBL
    <Msg>       "Check Software Versions Slot 1"
    <Send>      "show ver slot 1"
    <WaitFor>   "Information"
    <Wait>
    <GetData>
    <CheckData>     "Firmware Version: v"
    <CheckData>     $firmware_ver_gbl
    <CheckData>     "Booted Primary:"
    <CheckData>     $Stoke_boot_ver_gbl
    <CheckData>     "Booted Backup:"
    <CheckData>     $Stoke_boot_ver_gbl
    <CheckData>     "Stoke-Bloader Version"
    <CheckData>     "Booted Primary:"
    <CheckData>     $Stoke_bootloader_ver_gbl
    <CheckData>     "Booted Backup:"
    <CheckData>     $Stoke_bootloader_ver_gbl
    # Debug only <Msg>          "Bypassed checking for diag jumper"
    <CheckDataX>    "SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>		"Check Software Versions Slot 1"
	<Send>		"show ver slot 1"
	<WaitFor>	"Information"
	<Wait>
	<GetData>
	<CheckData>	    "Firmware Version: v"
	<CheckData>	    $firmware_ver_xglc_gbl
	<CheckData>	    "Booted Primary:"
	<CheckData>	    $Stoke_boot_XGLC_ver_gbl
	<CheckData>	    "Booted Backup:"
	<CheckData>		$Stoke_boot_XGLC_ver_gbl
	<CheckData>		"Stoke-Bloader Version"
	<CheckData>	    "Booted Primary:"
	<CheckData>	    $Stoke_bootloader_ver_gbl
	<CheckData>	    "Booted Backup:"
	<CheckData>		$Stoke_bootloader_ver_gbl
	# Debug only <Msg>			"Bypassed checking for diag jumper"
	<CheckDataX>	"SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>		"Check Software Versions Slot 2"
	<Send>		"show ver slot 2"
	<WaitFor>	"Information"
	<Wait>
	<GetData>
	<CheckData>	    "Firmware Version: v"
	<CheckData>	    $firmware_ver_xglc_gbl
	<CheckData>	    "Booted Primary:"
	<CheckData>	    $Stoke_boot_XGLC_ver_gbl
	<CheckData>	    "Booted Backup:"
	<CheckData>		$Stoke_boot_XGLC_ver_gbl
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
	<CheckData>	    $firmware_ver_xglc_gbl
	<CheckData>	    "Booted Primary:"
	<CheckData>	    $Stoke_boot_XGLC_ver_gbl
	<CheckData>	    "Booted Backup:"
	<CheckData>		$Stoke_boot_XGLC_ver_gbl
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
#	<WaitFor>	"Information"
	<Wait>
	<GetData>
    <CheckData>     "Firmware Version: v"
    <CheckData>     $firmware_ver_xglc_gbl
    <CheckData>     "Booted Primary:"
    <CheckData>     $Stoke_boot_XGLC_ver_gbl
    <CheckData>     "Booted Backup:"
    <CheckData>     $Stoke_boot_XGLC_ver_gbl
    <CheckData>     "Stoke-Bloader Version"
    <CheckData>     "Booted Primary:"
    <CheckData>     $Stoke_bootloader_ver_gbl
    <CheckData>     "Booted Backup:"
    <CheckData>     $Stoke_bootloader_ver_gbl
#    # Debug only <Msg>          "Bypassed checking for diag jumper"
	<CheckDataX>	"SYSTEM RUNNING WITH DIAG JUMPER INSTALLED"
</Bypass>

<Send>
<Wait>





