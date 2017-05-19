 ################################################################################
#
# Module:      Update_all_XGLC.dat
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Post_BI.dat,Config.dat
#
# Version:    1.2 $Id: Update_all_XGLC.inc,v 1.1 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 12/2011
#			  10/17/12 changed to allow 0 and 1 retry booting XGLC
#			  Added Support for XGLC in Slot 1 9/3/13
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################

<Prompt>	'#'
<Timeout>	100

<Bypass>	$Slot_INST_1_IMC_GBL
	<Msg>	"Wait for Slot 1 IMC"
	<Send>	'waitfor /net/nv-1-0/stoke/bin/diag/mc.setup.fabsnake 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>	"Wait for Slot 1"
	<Send>	'waitfor /net/nv-1-0/stoke/bin/diag/xglcdiag 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>	"Wait for Slot 2"
	<Send>	'waitfor /net/nv-2-0/stoke/bin/diag/xglcdiag 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>	"Wait for Slot 3"
	<Send>	'waitfor /net/nv-3-0/stoke/bin/diag/xglcdiag 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>	"Wait for Slot 4"
	<Send>	'waitfor /net/nv-4-0/stoke/bin/diag/xglcdiag 100'
	<Wait>
</Bypass>

<Bypass>	$Slot_INST_1_IMC_GBL
	<Msg>	"Check Slot 1 GLC Flash Status"
	<Send>	'pfeffa on 1 show cpld | grep F400002B'
	<Wait>
	<Send>	'pfeffa on 1 show cpld | grep F400002B'
	<Wait>
	<CheckData>	"F400002B.*flash-rdndnt-ctl-stat  05"
	<GetData>
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>	"Check Slot 1 Flash Status"
	<Send>	'on -f /net/nv-1-0 xglcdiag cpldshow | grep "flash-rdndnt-ctl-stat    2B"'
	<Wait>
	<Send>	'on -f /net/nv-1-0 xglcdiag cpldshow | grep "flash-rdndnt-ctl-stat    2B"'
	<Wait>
	<CheckData>	"flash-rdndnt-ctl-stat    2B      [0,2][0,4]"
	<GetData>
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>	"Check Slot 2 Flash Status"
	<Send>	'on -f /net/nv-2-0 xglcdiag cpldshow | grep "flash-rdndnt-ctl-stat    2B"'
	<Wait>
	<Send>	'on -f /net/nv-2-0 xglcdiag cpldshow | grep "flash-rdndnt-ctl-stat    2B"'
	<Wait>
	<CheckData>	"flash-rdndnt-ctl-stat    2B      [0,2][0,4]"
	<GetData>
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>	"Check Slot 3 Flash Status"
	<Send>	'on -f /net/nv-3-0 xglcdiag cpldshow | grep "flash-rdndnt-ctl-stat    2B"'
	<Wait>
	<Send>	'on -f /net/nv-3-0 xglcdiag cpldshow | grep "flash-rdndnt-ctl-stat    2B"'
	<Wait>
	<CheckData>	"flash-rdndnt-ctl-stat    2B      [0,2][0,4]"
	<GetData>
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>	"Check Slot 4 Flash Status"
	<Send>	'on -f /net/nv-4-0 xglcdiag cpldshow | grep "flash-rdndnt-ctl-stat    2B"'
	<Wait>
	<Send>	'on -f /net/nv-4-0 xglcdiag cpldshow | grep "flash-rdndnt-ctl-stat    2B"'
	<Wait>
	<CheckData>	"flash-rdndnt-ctl-stat    2B      [0,2][0,4]"
	<GetData>
</Bypass>


<TimeOut>   90
<Msg>       "Update All ..."
<Sleep>     5
<Msg>       "Update Slot 0 stokeboot"
<Msg>       "Commit Current image Slot 0 stokeboot"
#<sendslow>      "if (./stoke/bin/util/flashutil -m 0 ) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
<sendslow>      "if (./stoke/bin/util/flashutil -m 0 ) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
<Wait>
<GetData>
<CheckData>     "PASSED"
<Sleep>     1
<Msg>       "Update Slot 0 Uboot"
#<Sendslow>      "if (./stoke/bin/util/flashutil -p 0 1 /hd/mfg/stokeboot.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
<Sendslow>      "if (./stoke/bin/util/flashutil -p 0 1 /hd/mfg/stokeboot.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
<Wait>
<GetData>
<CheckData>     "PASSED"
<Sleep>     1

<Msg>       "Update Slot 0 Bootloader"
<Sendslow>      "if (./stoke/bin/util/flashutil -p 2 1 /hd/mfg/bootloader.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
<Wait>
<GetData>
<CheckData>     "PASSED"
<Sleep>     1

<Msg>       "Update Slot 0 Noodle"
<Sendslow>      "if (./stoke/bin/util/flashutil -p 1 1 //hd/mfg/noodle.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
<Wait>
<GetData>
#<CheckData>        "PASSED"
<Sleep>     1


<Msg>       "Commit Slot 0"
<sendslow>      "if (./stoke/bin/util/flashutil -m 0 ) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
<Wait>
<GetData>
<CheckData>     "PASSED"

<Bypass>    $Slot_INST_1_IMC_GBL
    <Sleep>     1
    <Msg>       "Commit Current image Slot 1 stokeboot"
    <sendslow>      "if (on -f /net/nv-1-0 /stoke/bin/util/flashutil -m 0) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
    <Wait>
    <GetData>
    <CheckData>     "PASSED"

    <Sleep>     1
    <Msg>       "Update Slot 1 Uboot"
    <sendslow>      "if (on -f /net/nv-1-0 /stoke/bin/util/flashutil -p 0 1 /net/nv-0-0/hd/mfg/stokeboot.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
    <Wait>
    <GetData>
    <CheckData>     "PASSED"
    <Sleep>     1

    <Msg>       "Update Slot 1 Bootloader"
    <sendslow>      "if (on -f /net/nv-1-0 /stoke/bin/util/flashutil -p 2 1 /net/nv-0-0/hd/mfg/bootloader.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
    <Wait>
    <GetData>
    <CheckData>     "PASSED"
    <Sleep>     1

    <Msg>       "Update Slot 1 Noodle"
    <sendslow>      "if (on -f /net/nv-1-0 /stoke/bin/util/flashutil -p 1 1 /net/nv-0-0/hd/mfg/noodle.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
    <Wait>
    <GetData>
#   <CheckData>     "PASSED"
    <Sleep>     1

    <Sleep>     1
    <Msg>       "Commit Current image Slot 1 stokeboot"
    <sendslow>      "if (on -f /net/nv-1-0 /stoke/bin/util/flashutil -m 1) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
    <Wait>
    <GetData>
    <CheckData>     "PASSED"
</Bypass>

#<Bypass>    $Slot_INST_2_GBL
#    <Sleep>     1
#    <Msg>       "Commit Current image Slot 2 stokeboot"
#    <sendslow>      "if (on -f /net/nv-2-0 /stoke/bin/util/flashutil -m 0) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
#    <Wait>
#    <GetData>
#    <CheckData>     "PASSED"

#    <Sleep>     1
#    <Msg>       "Update Slot 2 Uboot"
#    <sendslow>      "if (on -f /net/nv-2-0 /stoke/bin/util/flashutil -p 0 1 /net/nv-0-0/cfint/stokeboot.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
#    <Wait>
#    <GetData>
#    <CheckData>     "PASSED"
#    <Sleep>     1

#    <Msg>       "Update Slot 2 Bootloader"
#    <sendslow>      "if (on -f /net/nv-2-0 /stoke/bin/util/flashutil -p 2 1 /net/nv-0-0/cfint/bootloader.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
#    <Wait>
#    <GetData>
#    <CheckData>     "PASSED"
#    <Sleep>     1

##    <Msg>       "Update Slot 2 Noodle"
##    <sendslow>      "if (on -f /net/nv-2-0 /stoke/bin/util/flashutil -p 1 1 /net/nv-0-0/cfint/noodle.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
##    <Wait>
##    <GetData>
###   <CheckData>     "PASSED"
##    <Sleep>     1

#    <Sleep>     1
#    <Msg>       "Commit Current image Slot 2 stokeboot"
#    <sendslow>      "if (on -f /net/nv-2-0 /stoke/bin/util/flashutil -m 1) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
#    <Wait>
#    <GetData>
#    <CheckData>     "PASSED"
#</Bypass>

#<Bypass>    $Slot_INST_3_GBL
#    <Sleep>     1
#    <Sleep>     1
#    <Msg>       "Commit Current image Slot 3 stokeboot"
#    <sendslow>      "if (on -f /net/nv-3-0 /stoke/bin/util/flashutil -m 0) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
#    <Wait>
#    <GetData>
#    <CheckData>     "PASSED"

#    <Sleep>     1
#    <Msg>       "Update Slot 3 Uboot"
#    <sendslow>      "if (on -f /net/nv-3-0 /stoke/bin/util/flashutil -p 0 1 /net/nv-0-0/cfint/stokeboot.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
#    <Wait>
#    <GetData>
#    <CheckData>     "PASSED"
#    <Sleep>     1

#    <Msg>       "Update Slot 3 Bootloader"
#    <sendslow>      "if (on -f /net/nv-3-0 /stoke/bin/util/flashutil -p 2 1 /net/nv-0-0/cfint/bootloader.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
#    <Wait>
#    <GetData>
#    <CheckData>     "PASSED"
#    <Sleep>     1

##    <Msg>       "Update Slot 3 Noodle"
##    <sendslow>      "if (on -f /net/nv-3-0 /stoke/bin/util/flashutil -p 1 1 /net/nv-0-0/cfint/noodle.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
##    <Wait>
##    <GetData>
###   <CheckData>     "PASSED"
##    <Sleep>     1

#    <Sleep>     1
#    <Msg>       "Commit Current image Slot 3 stokeboot"
#    <sendslow>      "if (on -f /net/nv-3-0 /stoke/bin/util/flashutil -m 1) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
#    <Wait>
#    <GetData>
#    <CheckData>     "PASSED"
#</Bypass>

#<Bypass>    $Slot_INST_4_GBL
#    <Sleep>     1
#    <Msg>       "Commit Current image Slot 4 stokeboot"
#    <sendslow>      "if (on -f /net/nv-4-0 /stoke/bin/util/flashutil -m 0) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
#    <Wait>
#    <GetData>
#    <CheckData>     "PASSED"

#    <Sleep>     1
#    <Msg>       "Update Slot 4 Uboot"
#    <sendslow>      "if (on -f /net/nv-4-0 /stoke/bin/util/flashutil -p 0 1 /net/nv-0-0/cfint/stokeboot.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
#    <Wait>
#    <GetData>
#    <CheckData>     "PASSED"
#    <Sleep>     1

#    <Msg>       "Update Slot 4 Bootloader"
#    <sendslow>      "if (on -f /net/nv-4-0 /stoke/bin/util/flashutil -p 2 1 /net/nv-0-0/cfint/bootloader.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
#    <Wait>
#    <GetData>
#    <CheckData>     "PASSED"
#    <Sleep>     1

##    <Msg>       "Update Slot 4 Noodle"
##    <sendslow>      "if (on -f /net/nv-4-0 /stoke/bin/util/flashutil -p 1 1 /net/nv-0-0/cfint/noodle.bin) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
##    <Wait>
##    <GetData>
###   <CheckData>     "PASSED"
##    <Sleep>     1

#    <Sleep>     1
#    <Msg>       "Commit Current image Slot 4 stokeboot"
#    <sendslow>      "if (on -f /net/nv-4-0 /stoke/bin/util/flashutil -m 1) then (echo "PASSED:$?") else (echo "FAILED:$?") fi"
#    <Wait>
#    <GetData>
#    <CheckData>     "PASSED"
#</Bypass>



