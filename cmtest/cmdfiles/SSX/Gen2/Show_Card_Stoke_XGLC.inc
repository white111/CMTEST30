################################################################################
#
# Module:      Show_Card_Stoke_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Pre_BI,POST_BI and Config
#
# Version:    1.3 $Id: Show_Card_Stoke_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    11/18/11 Created
#			  01/08/12 Updated with 1 and 10gig. Added Port Switchover
#			  6/10/13 Prompt changes in 6.1R2
#			  Added Support for XGLC in Slot 1 9/3/13
#
#
#
# Still ToDo:
#             Software currently holds Slot 4 and port 3 & 4 off(can not get status)
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"[local]#"
<Send>
<Wait>
<TimeOut>	20
<Send>		"terminal length infinite"
<Wait>
<Msg>		"Show Cards"
<Send>		"show card"
<Waitfor>	"Slot"
<Wait>
<GetData>

<CheckData>	    "0 IMC.*Running.*Stoke IMC"
<Bypass>	$Slot_INST_1_IMC_GBL
	<CheckData>	    "1 IMC.*Running.*Stoke IMC"
</Bypass>
<Bypass>	$Slot_INST_1_GLC_GBL
	<CheckData>	    "1 XGLC1.*Running.*4x10GBase-R"
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<CheckData>	    "2 XGLC1.*Running.*4x10GBase-R"
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<CheckData>	    "3 XGLC1.*Running.*4x10GBase-R"
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<CheckData>	    "4 XGLC1.*Running.*4x10GBase-R"
</Bypass>

<Send>
<Wait>



