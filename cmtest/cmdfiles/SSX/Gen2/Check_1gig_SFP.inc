################################################################################
#
# Module:      Check_1gig_SFP.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_POST_BI and Config
#
# Version:    2.2 $Id: Show_Port_Counters_Det.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 081308
#			  Added <Send>		'diag trident slot 2 "show counters xe0" ' 3/16/12
#			  Fixed slot 4 wrong by pass varible
#			  Added Support for XGLC in Slot 1 9/3/13
#			  Added Support for 1gig,copper,LR,per port 10/30/13
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
###############################################################################


<Bypass>	$Slot_INST_1_GLC_GBL
 <Msg>	"Setup Slot 1 for 1gig SFPs"
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[1][0]
	<send>	"on -f /net/nv-1-0 xglcdiag tdnt port xe0 speed=1000"
	<wait>
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[1][1]
	<send>	"on -f /net/nv-1-0 xglcdiag tdnt port xe1 speed=1000"
	<wait>
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[1][2]
	<send>	"on -f /net/nv-1-0 xglcdiag tdnt port xe2 speed=1000"
	<wait>
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[1][3]
	<send>	"on -f /net/nv-1-0 xglcdiag tdnt port xe3 speed=1000"
	<wait>
</Bypass>

<Bypass>	$Slot_INST_2_GBL
<Msg>	"Setup Slot 2 for 1gig SFPs"
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[2][0]
	<send>	"on -f /net/nv-2-0 xglcdiag tdnt port xe0 speed=1000"
	<wait>
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[2][1]
	<send>	"on -f /net/nv-2-0 xglcdiag tdnt port xe1 speed=1000"
	<wait>
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[2][2]
	<send>	"on -f /net/nv-2-0 xglcdiag tdnt port xe2 speed=1000"
	<wait>
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[2][3]
	<send>	"on -f /net/nv-2-0 xglcdiag tdnt port xe3 speed=1000"
	<wait>
</Bypass>

<Bypass>	$Slot_INST_3_GBL
<Msg>	"Setup Slot 3 for 1gig SFPs"
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[3][0]
	<send>	"on -f /net/nv-3-0 xglcdiag tdnt port xe0 speed=1000"
	<wait>
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[3][1]
	<send>	"on -f /net/nv-3-0 xglcdiag tdnt port xe1 speed=1000"
	<wait>
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[3][2]
	<send>	"on -f /net/nv-3-0 xglcdiag tdnt port xe2 speed=1000"
	<wait>
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[3][3]
	<send>	"on -f /net/nv-3-0 xglcdiag tdnt port xe3 speed=1000"
	<wait>
</Bypass>

<Bypass>	$Slot_INST_4_GBL
<Msg>	"Setup Slot 4 for 1gig SFPs"
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[4][0]
	<send>	"on -f /net/nv-4-0 xglcdiag tdnt port xe0 speed=1000"
	<wait>
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[4][1]
	<send>	"on -f /net/nv-4-0 xglcdiag tdnt port xe1 speed=1000"
	<wait>
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[4][2]
	<send>	"on -f /net/nv-4-0 xglcdiag tdnt port xe2 speed=1000"
	<wait>
</bypass>
<bypass>	$XGLC_1gigSFP_gbl[4][3]
	<send>	"on -f /net/nv-4-0 xglcdiag tdnt port xe3 speed=1000"
	<wait>
</Bypass>


<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>	"Setup Slot 1 for Copper SFPs"
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[1][0]
	<send>	"on -f /net/nv-1-0 xglcdiag tdnt port xe0 speed=1000"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=1"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[1][1]
	<send>	"on -f /net/nv-1-0 xglcdiag tdnt port xe1 speed=1000"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=2"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[1][2]
	<send>	"on -f /net/nv-1-0 xglcdiag tdnt port xe2 speed=1000"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=4"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[1][3]
	<send>	"on -f /net/nv-1-0 xglcdiag tdnt port xe3 speed=1000"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=8"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-1-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>


<Bypass>	$Slot_INST_2_GBL
	<Msg>	"Setup Slot 2 for Copper SFPs"
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[2][0]
	<send>	"on -f /net/nv-2-0 xglcdiag tdnt port xe0 speed=1000"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=1"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[2][1]
	<send>	"on -f /net/nv-2-0 xglcdiag tdnt port xe1 speed=1000"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=2"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[2][2]
	<send>	"on -f /net/nv-2-0 xglcdiag tdnt port xe2 speed=1000"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=4"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[2][3]
	<send>	"on -f /net/nv-2-0 xglcdiag tdnt port xe3 speed=1000"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=8"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-2-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>	"Setup Slot 3 for Copper SFPs"
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[3][0]
	<send>	"on -f /net/nv-3-0 xglcdiag tdnt port xe0 speed=1000"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=1"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[3][1]
	<send>	"on -f /net/nv-3-0 xglcdiag tdnt port xe1 speed=1000"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=2"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[3][2]
	<send>	"on -f /net/nv-3-0 xglcdiag tdnt port xe2 speed=1000"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=4"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[3][3]
	<send>	"on -f /net/nv-3-0 xglcdiag tdnt port xe3 speed=1000"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=8"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-3-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<Bypass>	$Slot_INST_4_GBL
	<Msg>	"Setup Slot 4 for Copper SFPs"
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[4][0]
	<send>	"on -f /net/nv-4-0 xglcdiag tdnt port xe0 speed=1000"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=1"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[4][1]
	<send>	"on -f /net/nv-4-0 xglcdiag tdnt port xe1 speed=1000"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=2"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[4][2]
	<send>	"on -f /net/nv-4-0 xglcdiag tdnt port xe2 speed=1000"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=4"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>
<bypass>	$XGLC_1gigCopperSFP_gbl[4][3]
	<send>	"on -f /net/nv-4-0 xglcdiag tdnt port xe3 speed=1000"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x71,off=0,rsize=0,len=1,data=8"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0x16,rsize=1,len=2,data=0x40,01"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x01,00"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x91,0x40"
	<wait>
	<send>	"on -f /net/nv-4-0 i2c_util -w bus=3,dev=0x56,off=0,rsize=1,len=2,data=0x40,00"
	<wait>
</bypass>





