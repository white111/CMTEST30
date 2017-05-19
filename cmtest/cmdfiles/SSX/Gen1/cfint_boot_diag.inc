 ################################################################################
#
# Module:      cfint_boot_diag.inc
#
# Author:      Joe White
#
# Descr:       TFTP boots system from STOKE>> prompt to released Diag image
#
# Version:    1.4  $Id: cfint_boot_diag.inc,v 1.6 2009/09/28 17:21:45 joe Exp $
#
# Changes:    Udated for 3.0  9/29/06
#			  12/17/07 Upadted for sometimes missing the passed
#			  Added cleanup of dump dir to start checking for core files
#			  Added change to defaul KSH priority 5/15/08
#			  Removed waitfor built 6/25/09 intermittent on terminalserver
#
# Includes:
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################

<Msg>		"HD/CFINT Booting Diags..."
<TimeOut>	2
<Prompt>	"Stoke-BootLoader#"
#<Send>		'setenv ethaddr 00:12:73:FF:2:10'
#<Wait>
<Sleep>		5
<TimeOut>   30
<Sendslow>		$Diag_cfint_boot_gbl
<Wait>
<GetData>
<CheckData>	'Passed'
<Sleep>		7
<TimeOut>	90
<Send>		'go'
<Prompt>	'#'

#<WaitFor>    'Stoke HWTEST IMC IFS'
#<WaitFor>    "Card type is MC"
<Wait>
<GetData>

<timeout>	30
#<WaitFor>	"built"

#<MSG>   "Check if IMC Slot 0 in Standby"
#<Send>  "/stoke/bin/util/nvctl -P"
#<Wait>
#<GetData> Check_IMC_0_Standby
#<Bypass>    $IMC_0_Standby
#    <timeout>   5
#    <Msg>   "Make IMC in slot 0 Master"
#    <Send>  "pfeffa on 1 w8 F4000028   01"
#    <Wait>
#    <Send>  "pfeffa w8 F4000028 07"
#    <Wait>
#    <Send>  "pfeffa on 1 r8 F4000028"
#    <Wait>
#    <CheckData> "F4000028   01"
#    <GetData>
#    <Msg>   "Check IMC Slot 0 Master"
#    <Send>
#    <Wait>
#    <Send>  "pfeffa r8 F4000028"
#    <Wait>
#    <CheckData> "F4000028   07"
#    <Include>   Reset_all_slots.inc
#</Bypass>

<TimeOut>	120
# Make sure this system message does not pop out in the miidle of tests
<WaitFor>     "System process not started within designated time"
<Send>
<Wait>
<TimeOut>	30
<Include>   Check_HDP_Log_Error.inc
<Bypass>    $HA_Session
        <Msg>   "Check IMC slot 1"
        <Exec>  Swap_cons
        <Send>
        <Wait>
        #<Include>  Check_HDP_Log_Error.inc
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


