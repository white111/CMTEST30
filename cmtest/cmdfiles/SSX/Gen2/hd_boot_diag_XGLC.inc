 ################################################################################
#
# Module:      cfint_boot_diag_XGLC.inc
#
# Author:      Joe White
#
# Descr:       TFTP boots system from STOKE>> prompt to released Diag image
#
# Version:    1.2  $Id: hd_boot_diag_XGLC.inc,v 1.1 2011/12/12 22:54:27 joe Exp $
#
# Changes:    Created 11/18/11
#				030412 <Send>		'on -C 0 -p 7f ksh'
#			  Added diag version check 2/7/13
#
#
# Includes:
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2012 Stoke. All rights reserved.
#
################################################################################

<Msg>		"HD/MFG Booting Diags..."
<TimeOut>	2
<Prompt>	"Stoke-BootLoader#"
#<Send>		'setenv ethaddr 00:12:73:FF:2:10'
#<Wait>
<Sleep>		5
<TimeOut>   30
<Sendslow>		$Diag_boot_xglc_gbl
<Wait>
<GetData>
<CheckData>	'Passed'
<Sleep>		7
<TimeOut>	90
<Send>		'go'
<Prompt>	'#'
<sleep>		30

<Wait>
<GetData>

<timeout>	30


<TimeOut>	120
# Make sure this system message does not pop out in the miidle of tests
#<WaitFor>     "System process not started within designated time"
<Send>
<Wait>
<Msg>	"Verify diag version"
<Send>	$Diag_boot_ver_cmd_gbl
<Wait>
<checkdata> $Diag_boot_ver_gbl

<TimeOut>	30
<Include>   Check_HDP_Log_Error_XGLC.inc
<Bypass>    $HA_Session
        <Msg>   "Check IMC slot 1"
        <Exec>  Swap_cons
        <Send>
        <Wait>
        #<Include>  Check_HDP_Log_Error_XGLC.inc
        <Exec>  Swap_cons
        <Send>
        <Wait>
</Bypass>

<msg>		"Dropping KSH priority to 7f"
<Send>		'on -p 7f ksh'
<Wait>
<GetData>

<Send>		'rm -f /hd/dump/slot0/*'
<Wait>
<GetData>
<Send>		'rm -f /hd/dump/slot1/*'
<Wait>
<GetData>
<Send>		'rm -f /hd/dump/slot2/*'
<Wait>
<GetData>
<Send>		'rm -f /hd/dump/slot3/*'
<Wait>
<GetData>
<Send>		'rm -f /hd/dump/slot4/*'
<Wait>
<GetData>


