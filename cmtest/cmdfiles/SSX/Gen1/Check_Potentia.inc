 ################################################################################
#
# Module:      Check_Potentia.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Post_BI.dat,Config.dat
#
# Version:    2.2  $Id: Check_Potentia.inc,v 1.4 2011/05/26 19:31:26 joe Exp $
#
# Changes:    Created 10/24/06
#			  Added Changes for PSOC 11/15/10
#			  Fix for inttermeitten issue 3/11/11

#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################

<Prompt>	'slot 0:>'
<TimeOut>	40
<Send>		"pfeffa"
<wait>

<Bypass>	$UUT_Variable_ref[1]->{Potentia}
	<Msg>		"Check Potentia Slot 0"
	<Send>		"rd potentia 0 nvreg 00 100"
	<Wait>
	<GetData>	Potentia_0_IMC
	<Send>		"rd potentia 1 nvreg 00 100"
	<Wait>
	<GetData>	Potentia_1_IMC
</Bypass>
<Bypass>	$UUT_Variable_ref[1]->{PSOC}
		<Msg>		"Check PSOC Slot 0 Version"
		<Send>		"rd potentia 0 cs 60 10"
		<Wait>
		<Checkdata> $UUT_Variable_ref[1]->{PSOC_VER}
		<GetData>
		<Send>		"rd potentia 0 cs 00 100;rd potentia 1 cs 00 100"
		<Wait>
		<GetData>
		#Reset Static Counters
		<Send>		"wr potentia 0 csrs 1 5a"
		<Wait>
		<Send>		"rd potentia 0 cs 00 10"
		<Wait>
		<GetData>
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Bypass>	$UUT_Variable_ref[2]->{Potentia}
		<Msg>		"Check Potentia Slot 1 GLC"
		<Send>		"on 1 rd potentia 0 nvreg 00 100"
		<Wait>
		<GetData>	Potentia_0_GLC
		<Send>		"on 1 rd potentia 1 nvreg 00 100"
		<Wait>
		<GetData>	Potentia_1_GLC
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_1_GLC_GBL
	<Bypass>	$UUT_Variable_ref[2]->{PSOC}
	    <Msg>		"Check PSOC Slot 1 Version"
		<Send>		"on 1 rd potentia 0 cs 60 10"
		<Wait>
		<Checkdata> $UUT_Variable_ref[2]->{PSOC_VER}
		<GetData>
		<Send>		"on 1 rd potentia 0 cs 00 100;rd potentia 1 cs 00 100"
		<Wait>
		<GetData>
		#Reset Static Counters
		<Send>		"on 1 wr potentia 0 csrs 1 5a"
		<Wait>
		<Send>		"on 1 rd potentia 0 cs 00 10"
		<Wait>
		<GetData>
 	</Bypass>
</Bypass>

<Bypass>	$Slot_INST_1_IMC_GBL
	<Bypass>	$UUT_Variable_ref[2]->{Potentia}
		<Msg>		"Check Potentia Slot 1 IMC"
		<Send>		"on 1 rd potentia 0 nvreg 00 100"
		<Wait>
		<GetData>	Potentia_0_IMC
		<Send>		"on 1 rd potentia 1 nvreg 00 100"
		<Wait>
		<GetData>	Potentia_1_IMC
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_1_IMC_GBL
	<Bypass>	$UUT_Variable_ref[2]->{PSOC}
		<Msg>		"Check PSOC IMC Slot 1 Version"
		<Send>		"on 1 rd potentia 0 cs 60 10"
		<Wait>
		<Checkdata> $UUT_Variable_ref[2]->{PSOC_VER}
		<GetData>
		<Send>		"on 1 rd potentia 0 cs 00 100;rd potentia 1 cs 00 100"
		<Wait>
		<GetData>
		#Reset Static Counters
		<Send>		"on 1 wr potentia 0 csrs 1 5a"
		<Wait>
		<Send>		"on 1 rd potentia 0 cs 00 10"
		<Wait>
		<GetData>

 	</Bypass>
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Bypass>	$UUT_Variable_ref[3]->{Potentia}
		<Msg>		"Check Potentia Slot 2"
		<Send>		"on 2 rd potentia 0 nvreg 00 100"
		<Wait>
		<GetData>	Potentia_0_GLC
		<Send>		"on 2 rd potentia 1 nvreg 00 100"
		<Wait>
		<GetData>	Potentia_1_GLC
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<Bypass>	$UUT_Variable_ref[3]->{PSOC}
		<Msg>		"Check PSOC Slot 2 Version"
		<Send>		"on 2 rd potentia 0 cs 60 10"
		<Wait>
		<Checkdata> $UUT_Variable_ref[3]->{PSOC_VER}
		<GetData>
		<Send>		"on 2 rd potentia 0 cs 00 100;rd potentia 1 cs 00 100"
		<Wait>
		<GetData>
		#Reset Static Counters
		<Send>		"on 2 wr potentia 0 csrs 1 5a"
		<Wait>
		<GetData>
		<Send>		"on 2 rd potentia 0 cs 00 10"
		<Wait>
		<GetData>

	</Bypass>
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Bypass>	$UUT_Variable_ref[4]->{Potentia}

		<Msg>		"Check Potentia Slot 3"
		<Send>		"on 3 rd potentia 0 nvreg 00 100"
		<Wait>
		<GetData>	Potentia_0_GLC
		<Send>		"on 3 rd potentia 1 nvreg 00 100"
		<Wait>
		<GetData>	Potentia_1_GLC
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<Bypass>	$UUT_Variable_ref[4]->{PSOC}
		<Msg>		"Check PSOC Slot 3"
		<Send>		"on 3 rd potentia 0 cs 60 10"
		<Wait>
		<Checkdata> $UUT_Variable_ref[4]->{PSOC_VER}
		<GetData>
		<Send>		"on 3 rd potentia 0 cs 00 100;rd potentia 1 cs 00 100"
		<Wait>
		<GetData>
		#Reset Static Counters
		<Send>		"on 3 wr potentia 0 csrs 1 5a"
		<Wait>
		<Send>		"on 3 rd potentia 0 cs 00 10"
		<Wait>
		<GetData>
	</Bypass>
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Bypass>	$UUT_Variable_ref[5]->{Potentia}
		<Msg>		"Check Potentia Slot 4"
 		<Send>		"on 4 rd potentia 0 nvreg 00 100"
		<Wait>
		<GetData>	Potentia_0_GLC
		<Send>		"on 4 rd potentia 1 nvreg 00 100"
		<Wait>
		<GetData>	Potentia_1_GLC
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<Bypass>	$UUT_Variable_ref[5]->{PSOC}
		<Msg>		"Check PSOC Slot 4"
		<Send>		"on 4 rd potentia 0 cs 60 10"
		<Wait>
		<Checkdata> $UUT_Variable_ref[5]->{PSOC_VER}
		<GetData>
		<Send>		"on 4 rd potentia 0 cs 00 100;rd potentia 1 cs 00 100"
		<Wait>
		<GetData>
		#Reset Static Counters
		<Send>		"on 4 wr potentia 0 csrs 1 5a"
		<Wait>
		<Send>		"on 4 rd potentia 0 cs 00 10"
		<Wait>
		<GetData>
	</Bypass>
</Bypass>


<Prompt>	"#"
<Timeout>	15
<Send>		"exit"
<sleep>		1
<send>      "exit"
<Wait>

