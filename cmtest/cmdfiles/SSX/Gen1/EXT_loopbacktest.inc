################################################################################
#
# Module:      EXT_BI_loopbacktest.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Extended.dat
#
# Version:    1.2  $Id: EXT_loopbacktest.inc,v 1.5 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Created 10/13/06
#			  Updated for 4.0 diags
#
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################
<Msg>		"Setup Fabric ..."
<Prompt>	"#"

<Timeout>	10
<Prompt>	"> "

<Send>		"pfeffa"
<Wait>


<Timeout>	180
<Msg>		"Traffic source Any Port, All other slots/ports in loopback"
##<Send>     "set fab sna 34444"
#<SendChr>       "pfeffa set fab sna "
#<SendChr>       3
#<Bypass>    $Slot_INST_1_IMC_GBL
#        <SendChr>       3
#</Bypass>
#<Bypass>    $Slot_INST_1_GLC_GBL
#        <SendChr>       $Slot_CARD_TYPE_INST_1_GBL
#</Bypass>

#<SendChr>       $Slot_CARD_TYPE_INST_2_GBL
#<SendChr>       $Slot_CARD_TYPE_INST_3_GBL
#<SendChr>       $Slot_CARD_TYPE_INST_4_GBL
<Send>           "test snakeext"
<Wait>
<GetData>
<CheckData>	"Test Status:"
<Bypass>	$Slot_INST_4_GBL
	<CheckData>	"Slot 4: PASSED"
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<CheckData>	"Slot 3: PASSED"
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<CheckData>	"Slot 2: PASSED"
</Bypass>
<Bypass>	$Slot_INST_1_GBL
	<CheckData>	"Slot 1: PASSED"
</Bypass>

<CheckData>	"Slot 0: PASSED"

<Sleep>		2

<Timeout>	30

<Msg>		"Clear Counts"
<Send>		'clear mibs *'
<wait>
#Clear ixtest/N2 errors
<Bypass>	$Slot_INST_1_GLC_GBL
	<Sendslow>		"sys on -f /net/nv-1-0 ixtest errors > /dev/null"
	<Wait>
	<GetData>
	<Sendslow>		"on 1 show n2 count > /dev/null"
	<Wait>
	<GetData>
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<Sendslow>		"sys on -f /net/nv-2-0 ixtest errors > /dev/null"
	<Wait>
	<GetData>
	<Sendslow>		"on 2 show n2 count > /dev/null"
	<Wait>
	<GetData>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<Sendslow>		"sys on -f /net/nv-3-0 ixtest errors > /dev/null"
	<Wait>
	<GetData>
	<Sendslow>		"on 3 show n2 count > /dev/null"
	<Wait>
	<GetData>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
	<Sendslow>		"sys on -f /net/nv-4-0 ixtest errors > /dev/null"
	<Wait>
	<GetData>
	<Sendslow>		"on 4 show n2 count > /dev/null"
	<Wait>
	<GetData>
</Bypass>

<Msg>		"Starting External loopback test"
<Exec> AX4000_Normal

# use grep to suppress output

<Include> Check_EXT_loopbacktest.inc
#<Include> Check_BI_loopbacktest.inc
