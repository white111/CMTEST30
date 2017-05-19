################################################################################
#
# Module:      Check Disco_XGLC.txt
#
# Author:      Joe White
#
# Descr:       Check Disco for memory and PCI errors
#
# Version:    1.1 $Id: Check_Disco_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 11/23/11
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
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

#<Bypass>    $Slot_INST_1_GLC_GBL
#    <Msg>   "Check Slot 1 Disco"
#    <Send>  "pfeffa on 1 show disco prob"
#    <Wait>
#    <GetData>
#    <CheckDatax>    "DEVICE INTERFACE ERROR REPORT"
#    <CheckDatax>    "show_disco_sdram_ecc_errorreport: error detected"
#    <CheckDatax>    "Double bit ECC error detected"
#    <CheckDatax>    "PCI 0 ERROR REPORT"
#    <CheckDatax>    "PCI 1 ERROR REPORT"
#   <Sleep> 1
#</Bypass>

#<Bypass>    $Slot_INST_2_GBL
#    <Msg>   "Check Slot 2 Disco"
#    <Send>  "pfeffa on 2 show disco prob"
#    <Wait>
#    <GetData>
#    <CheckDatax>    "DEVICE INTERFACE ERROR REPORT"
#    <CheckDatax>    "show_disco_sdram_ecc_errorreport: error detected"
#    <CheckDatax>    "Double bit ECC error detected"
#    <CheckDatax>    "PCI 0 ERROR REPORT"
#    <CheckDatax>    "PCI 1 ERROR REPORT"
#   <Sleep> 1
#</Bypass>

#<Bypass>    $Slot_INST_3_GBL
#    <Msg>   "Check Slot 3 Disco"
#    <Send>  "pfeffa on 3 show disco prob"
#    <Wait>
#    <GetData>
#    <CheckDatax>    "DEVICE INTERFACE ERROR REPORT"
#    <CheckDatax>    "show_disco_sdram_ecc_errorreport: error detected"
#    <CheckDatax>    "Double bit ECC error detected"
#    <CheckDatax>    "PCI 0 ERROR REPORT"
#    <CheckDatax>    "PCI 1 ERROR REPORT"
#   <Sleep> 1
#</Bypass>

#<Bypass>    $Slot_INST_4_GBL
#    <Msg>   "Check Slot 4 Disco"
#    <Send>  "pfeffa on 4 show disco prob"
#    <Wait>
#    <GetData>
#    <CheckDatax>    "DEVICE INTERFACE ERROR REPORT"
#    <CheckDatax>    "show_disco_sdram_ecc_errorreport: error detected"
#    <CheckDatax>    "Double bit ECC error detected"
#    <CheckDatax>    "PCI 0 ERROR REPORT"
#    <CheckDatax>    "PCI 1 ERROR REPORT"
#   <Sleep> 1
#</Bypass>




