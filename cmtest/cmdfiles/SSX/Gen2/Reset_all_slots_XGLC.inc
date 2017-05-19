 ################################################################################
#
# Module:      Reset_all_slots_XGLC
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI, Pre_BI,POst_BI, Config, Extended, ORT Dat files
#
# Version:    1.3 $Id: Reset_all_slots_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 12/1/11
#			  Fixed waiting for wron slots 6/7/12
#			  Added Support for XGLC in Slot 1 10/30/13
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2013 Stoke. All rights reserved.
#
################################################################################
#<Prompt>    "#"
#<Timeout>   100
<Msg>   "Bypassed all resets in Reset_all_slots_XGLC"
#<Bypass>    $Slot_INST_1_IMC_GBL
#    <Msg>   "Wait for Slot 1 IMC"
#    <Send>  'waitfor /net/nv-1-0/stoke/bin/diag/mc.setup.fabsnake 100'
#    <Wait>
#    <Bypass>    $Slot_INST_1_GLC_GBL
#    <Msg>       "Reset GLC 1"
#    <Send>      "pfeffa on 1 w8 f400002b 11"
#    <Wait>
#</Bypass>

#<Bypass>    $Slot_INST_1_GLC_GBL
#    <Msg>   "Wait for Slot 1"
#    <Sendslow>  'waitfor /net/nv-1-0/stoke/bin/diag/xglcdiag 100'
#    <Wait>
#    <send>  "pfeffa rd i2c 9501 1 gpio"
#    <wait>
#    <Checkdata> "BF"
#</Bypass>

#<Bypass>    $Slot_INST_2_GBL
#    <Msg>   "Wait for Slot 2"
#    <Sendslow>  'waitfor /net/nv-2-0/stoke/bin/diag/xglcdiag 100'
#    <Wait>
#    <send>  "pfeffa rd i2c 9501 2 gpio"
#    <wait>
#    <Checkdata> "BF"
#</Bypass>

#<Bypass>    $Slot_INST_3_GBL
#    <Msg>   "Wait for Slot 3"
#    <Send>  'waitfor /net/nv-3-0/stoke/bin/diag/xglcdiag 100'
#    <Wait>
#    <sendslow>  "pfeffa rd i2c 9501 3 gpio"
#    <wait>
#    <Checkdata> "BF"
#</Bypass>

#<Bypass>    $Slot_INST_4_GBL
#    <Msg>   "Wait for Slot 4"
#    <Sendslow>  'waitfor /net/nv-4-0/stoke/bin/diag/xglcdiag 100'
#    <Wait>
#    <Timeout>   20
#    <send>  "pfeffa rd i2c 9501 4 gpio"
#    <wait>
#    <Checkdata> "BF"
#</Bypass>

#<Timeout>   20
##<Msg>      "Bypass Reset All Slots using GPIO Reset board"

#<Bypass>    $Slot_INST_1_GLC_GBL
#    <Msg>       "Reset XGLC 1"
#    <Send>      "pfeffa on 1 w8 f400002b 11"
#    <Wait>
#    <Send>      "pfeffa wr i2c 9501 1 gpio d"
#    <Wait>
#    <send>      "ls /net/nv-1-0"
#    <wait>
#    <checkdata> "ost.*nv-1-0"
#    <send>  "pfeffa rd i2c 9501 1 gpio"
#    <wait>
#    <Checkdata> "FD"
#    <Send>      "pfeffa wr i2c 9501 1 gpio f"
#    <Wait>
#    #<Send>     "on -f /net/nv-1-0 reset bo &"
#    #<Wait>
#    <Sleep>     1
#    <send>      "ls /net/nv-1-0"
#    <wait>
#    #<checkdatax>   "No route to host.*nv-1-0"
#</Bypass>

#<Bypass>    $Slot_INST_GBL[3]
#    <Msg>       "Reset XGLC 2"
#    <Send>      "pfeffa on 2 w8 f400002b 11"
#    <Wait>
#    <Send>      "pfeffa wr i2c 9501 2 gpio d"
#    <Wait>
#    <send>      "ls /net/nv-2-0"
#    <wait>
#    <checkdata> "ost.*nv-2-0"
#    <send>  "pfeffa rd i2c 9501 2 gpio"
#    <wait>
#    <Checkdata> "FD"
#    <Send>      "pfeffa wr i2c 9501 2 gpio f"
#    <Wait>
#    #<Send>     "on -f /net/nv-2-0 reset bo &"
#    #<Wait>
#    <Sleep>     1
#    <send>      "ls /net/nv-2-0"
#    <wait>
#    #<checkdatax>   "No route to host.*nv-2-0"
#</Bypass>

#<Bypass>    $Slot_INST_GBL[4]
#    <Msg>       "Reset XGLC 3"
#    <Send>      "pfeffa on 3 w8 f400002b 11"
#    <Wait>
#    <Send>      "pfeffa wr i2c 9501 3 gpio d"
#    <Wait>
#    <send>      "ls /net/nv-3-0"
#    <wait>
#    <checkdata> "ost.*nv-3-0"
#    <send>  "pfeffa rd i2c 9501 3 gpio"
#    <wait>
#    <Checkdata> "FD"
#    <Send>      "pfeffa wr i2c 9501 3 gpio f"
#    <Wait>
#    #<Send>     "on -f /net/nv-3-0 reset bo &"
#    #<Wait>
#    <Sleep>     1
#    <send>      "ls /net/nv-3-0"
#    <wait>
#    #<checkdatax>   "No route to host.*nv-3-0"
#</Bypass>

#<Bypass>    $Slot_INST_GBL[5]
#    <Msg>       "Reset XGLC 4"
#    <Send>      "pfeffa on 4 w8 f400002b 11"
#    <Wait>
#    <Send>      "pfeffa wr i2c 9501 4 gpio d"
#    <Wait>
#    <send>      "ls /net/nv-4-0"
#    <wait>
#    <checkdata> "ost.*nv-4-0"
#    <send>  "pfeffa rd i2c 9501 4 gpio"
#    <wait>
#    <Checkdata> "FD"
#    <Send>      "pfeffa wr i2c 9501 4 gpio f"
#    <Wait>
#    #<Send>     "on -f /net/nv-4-0 reset bo &"
#    #<Wait>
#    <Sleep>     1
#    <send>      "ls /net/nv-4-0"
#    <wait>
#    #<checkdatax>   "No route to host.*nv-4-0"
#</Bypass>

#<Timeout>  90
#<Send>  "wait"
#<Wait>

#<Timeout>   130
#<Bypass>    $Slot_INST_1_IMC_GBL
#    <Msg>   "Wait for Slot 1 IMC"
#    <Send>  'waitfor /net/nv-1-0/stoke/bin/diag/mc.setup.fabsnake 100'
#    <Wait>
#</Bypass>

#<Bypass>    $Slot_INST_1_GLC_GBL
#    <Msg>   "Wait for Slot 1"
#    <Send>  'waitfor /net/nv-1-0/stoke/bin/diag/xglcdiag 100'
#    <Wait>
#</Bypass>

#<Bypass>    $Slot_INST_2_GBL
#    <Msg>   "Wait for Slot 2"
#    <Send>  'waitfor /net/nv-2-0/stoke/bin/diag/xglcdiag 100'
#    <Wait>
#</Bypass>

#<Bypass>    $Slot_INST_3_GBL
#    <Msg>   "Wait for Slot 3"
#    <Send>  'waitfor /net/nv-3-0/stoke/bin/diag/xglcdiag 100'
#    <Wait>
#</Bypass>

#<Bypass>    $Slot_INST_4_GBL
#    <Msg>   "Wait for Slot 4"
#    <Send>  'waitfor /net/nv-3-0/stoke/bin/diag/xglcdiag 100'
#    <Wait>
#    <Timeout>   20
#</Bypass>

