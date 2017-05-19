 ################################################################################
#
# Module:      BMR_Read_XGLC
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI, Pre_BI,POst_BI, Config, Extended, ORT Dat files
#
# Version:    1.3 $Id: Reset_all_slots_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 7/10/14
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2014 Stoke. All rights reserved.
#
################################################################################
#power off and on  and verify to see if NVRAM is written.

## xglcdiag cpldacc wr 1d 1

## xglcdiag cpldacc wr 62 0x0B

## i2c_util -w bus=0,dev=0x70,off=0,rsize=0,len=1,data=4

## i2c_util -r bus=0,dev=0x2f,off=4f,rsize=1,len=2

#should read
## i2c_util -r bus=0,dev=0x2f,off=4f,rsize=1,len=2
#I2C bus set to /dev/i2c0
#Device: 0x2f Offset: 0x4f Data: 0xc0
#Data[0] = 0x98
#Data[1] = 0xeb


<prompt>	"^#"
<Timeout>	60
<Send>
<wait>
<sleep>		1
<Bypass>    $Slot_INST_1_GLC_GBL
	<Msg>	"Read Slot 1 BMR Value"
	<send>	"on -f /net/nv-1-0/ /bin/ksh /net/nv-0-0/hd/mfg/BMR.ksh 1"
	<wait>
	             #BMR programming failed with ${fail} retrys
	<checkdatax> "BMR programming failed with 5 retrys"
	<getData>
</Bypass>
<Bypass>    $Slot_INST_2_GBL
 	<Msg>	"Read Slot 2 BMR Value"
	<send>	"on -f /net/nv-2-0/ /bin/ksh /net/nv-0-0/hd/mfg/BMR.ksh 2"
	<wait>
	<checkdatax> "BMR programming failed with 5 retrys"
	<getData>
</Bypass>
<Bypass>    $Slot_INST_3_GBL
  	<Msg>	"Read Slot 3 BMR Value"
	<send>	"on -f /net/nv-3-0/ /bin/ksh /net/nv-0-0/hd/mfg/BMR.ksh 3"
	<wait>
	<checkdatax> "BMR programming failed with 5 retrys"
	<getData>
</Bypass>
<Bypass>    $Slot_INST_4_GBL
	<Msg>	"Read Slot 4 BMR Value"
	<send>	"on -f /net/nv-4-0/ /bin/ksh /net/nv-0-0/hd/mfg/BMR.ksh 4"
	<wait>
	<checkdatax> "BMR programming failed with 5 retrys"
	<getData>
</Bypass>



