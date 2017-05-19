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
#			  Fixed waiting for wrong slots 6/7/12
#			  Updated to detect Copper and 1gig.  10/30/13
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2013 Stoke. All rights reserved.
#
################################################################################
<prompt>	"^#"
<Timeout>	100
<send>      "echo check 1"
<wait>
<sleep>		1
<Bypass>    $Slot_INST_1_GLC_GBL
	<Msg>	"Get Slot 1 SFP Port info"
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x71,off=1,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-1-0 i2c_util -r bus=3,dev=0x71,off=1,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 1 port 0;on -f /net/nv-1-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP

	<Timeout>	100
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x71,off=2,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-1-0 i2c_util -r bus=3,dev=0x71,off=2,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 1 port 1;on -f /net/nv-1-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP

	<Timeout>	100
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x71,off=4,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-1-0 i2c_util -r bus=3,dev=0x71,off=4,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 1 port 2;on -f /net/nv-1-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x71,off=8,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-1-0 i2c_util -r bus=3,dev=0x71,off=8,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 1 port 3;on -f /net/nv-1-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP
</Bypass>
<Bypass>    $Slot_INST_2_GBL
	<Msg>	"Get Slot 2 SFP Port info"
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x71,off=1,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-2-0 i2c_util -r bus=3,dev=0x71,off=1,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 2 port 0;on -f /net/nv-2-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP

	<Timeout>	100
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x71,off=2,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-2-0 i2c_util -r bus=3,dev=0x71,off=2,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 2 port 1;on -f /net/nv-2-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP

	<Timeout>	100
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x71,off=4,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-2-0 i2c_util -r bus=3,dev=0x71,off=4,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 2 port 2;on -f /net/nv-2-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x71,off=8,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-2-0 i2c_util -r bus=3,dev=0x71,off=8,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 2 port 3;on -f /net/nv-2-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP
</Bypass>
<Bypass>    $Slot_INST_3_GBL
	<Msg>	"Get Slot 3 SFP Port info"
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x71,off=1,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-3-0 i2c_util -r bus=3,dev=0x71,off=1,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 3 port 0;on -f /net/nv-3-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP

	<Timeout>	100
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x71,off=2,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-3-0 i2c_util -r bus=3,dev=0x71,off=2,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 3 port 1;on -f /net/nv-3-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP

	<Timeout>	100
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x71,off=4,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-3-0 i2c_util -r bus=3,dev=0x71,off=4,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 3 port 2;on -f /net/nv-3-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x71,off=8,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-3-0 i2c_util -r bus=3,dev=0x71,off=8,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 3 port 3;on -f /net/nv-3-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP
</Bypass>
<Bypass>    $Slot_INST_4_GBL
	<Msg>	"Get Slot 4 SFP Port info"
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x71,off=1,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-4-0 i2c_util -r bus=3,dev=0x71,off=1,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 4 port 0;on -f /net/nv-4-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP

	<Timeout>	100
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x71,off=2,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-4-0 i2c_util -r bus=3,dev=0x71,off=2,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 4 port 1;on -f /net/nv-4-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP

	<Timeout>	100
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x71,off=4,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-4-0 i2c_util -r bus=3,dev=0x71,off=4,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 4 port 2;on -f /net/nv-4-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x71,off=8,rsize=1,len=1,data=1"
	<wait>
    <send>  "on -f /net/nv-4-0 i2c_util -r bus=3,dev=0x71,off=8,rsize=1,len=1,data=0"
    <wait>
	<send>	"echo slot 4 port 3;on -f /net/nv-4-0 i2c_util -r bus=3,dev=0x50,off=0,rsize=1,len=54,data=0"
	<wait>
	<Getdata>  Get_SFP
</Bypass>

<send>      "echo check 4"
<wait>
<sleep>		1
<Exec>		Display_SFP

