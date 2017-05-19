################################################################################
#
# Module:      Check Disco.txt
#
# Author:      Joe White
#
# Descr:       Check Disco for memory and PCI errors
#
# Version:    1.1 $Id: Check_Disco.inc,v 1.1 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Created 01/23/08
#
# Includes:
#
# Still ToDo:
#              - Add Looping on each test, start a process for each test
#
#
#            Copyright (c) 2008 Stoke. All rights reserved.
#
################################################################################

<Msg>	"Check Disco for Errors"

<Prompt>	"#"
<Timeout>	10

<Send>	"pfeffa show disco prob"
<Wait>
<GetData>
<CheckDatax>	"DEVICE INTERFACE ERROR REPORT"
<CheckDatax>	"show_disco_sdram_ecc_errorreport: error detected"
<CheckDatax>	"Double bit ECC error detected"
<CheckDatax>	"PCI 0 ERROR REPORT"
<CheckDatax>	"PCI 1 ERROR REPORT"
<Sleep>	1

<Bypass>	$Slot_INST_1_IMC_GBL
	<Msg>	"Check Slot 1 Disco"
	<Send>	"pfeffa on 1 show disco prob"
	<Wait>
	<GetData>
	<CheckDatax>	"DEVICE INTERFACE ERROR REPORT"
	<CheckDatax>	"show_disco_sdram_ecc_errorreport: error detected"
	<CheckDatax>	"Double bit ECC error detected"
	<CheckDatax>	"PCI 0 ERROR REPORT"
	<CheckDatax>	"PCI 1 ERROR REPORT"
   <Sleep> 1
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>	"Check Slot 1 Disco"
	<Send>	"pfeffa on 1 show disco prob"
	<Wait>
	<GetData>
	<CheckDatax>	"DEVICE INTERFACE ERROR REPORT"
	<CheckDatax>	"show_disco_sdram_ecc_errorreport: error detected"
	<CheckDatax>	"Double bit ECC error detected"
	<CheckDatax>	"PCI 0 ERROR REPORT"
	<CheckDatax>	"PCI 1 ERROR REPORT"
   <Sleep> 1
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>	"Check Slot 2 Disco"
	<Send>	"pfeffa on 2 show disco prob"
	<Wait>
	<GetData>
	<CheckDatax>	"DEVICE INTERFACE ERROR REPORT"
	<CheckDatax>	"show_disco_sdram_ecc_errorreport: error detected"
	<CheckDatax>	"Double bit ECC error detected"
	<CheckDatax>	"PCI 0 ERROR REPORT"
	<CheckDatax>	"PCI 1 ERROR REPORT"
   <Sleep> 1
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>	"Check Slot 3 Disco"
	<Send>	"pfeffa on 3 show disco prob"
	<Wait>
	<GetData>
	<CheckDatax>	"DEVICE INTERFACE ERROR REPORT"
	<CheckDatax>	"show_disco_sdram_ecc_errorreport: error detected"
	<CheckDatax>	"Double bit ECC error detected"
	<CheckDatax>	"PCI 0 ERROR REPORT"
	<CheckDatax>	"PCI 1 ERROR REPORT"
   <Sleep> 1
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>	"Check Slot 4 Disco"
	<Send>	"pfeffa on 4 show disco prob"
	<Wait>
	<GetData>
	<CheckDatax>	"DEVICE INTERFACE ERROR REPORT"
	<CheckDatax>	"show_disco_sdram_ecc_errorreport: error detected"
	<CheckDatax>	"Double bit ECC error detected"
	<CheckDatax>	"PCI 0 ERROR REPORT"
	<CheckDatax>	"PCI 1 ERROR REPORT"
   <Sleep> 1
</Bypass>




