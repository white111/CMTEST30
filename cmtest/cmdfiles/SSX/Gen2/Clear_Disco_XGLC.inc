################################################################################
#
# Module:      Clear Disco_XGLC.txt
#
# Author:      Joe White
#
# Descr:       Clear Disco errors after startup
#
# Version:    1.2 $Id: Clear_Disco_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 11/22/11
#			  Added Clear of XGLC ECC reg 9/24/12
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################

<Msg>	"Clear Disco Errors"

<Prompt>	"#"
<Timeout>	10

<Send>	"pfeffa show disco prob > /dev/null"
<Wait>
<Sleep>	1

<Bypass>	$Slot_INST_1_IMC_GBL
	#<Msg>	"Clear Disco Errors IMC Slot 1"
	<Send>	"pfeffa on 1 show disco prob  > /dev/null"
	<Wait>
   <Sleep> 1
</Bypass>

<Bypass>    $Slot_INST_1_GLC_GBL
	<Send>  "on -p6r -f /net/nv-1-0/ xglcdiag ccsracc wr 8e48 0x19c"
	<Wait>
	<Send>  "on -p6r -f /net/nv-1-0/ xglcdiag ccsracc wr 8e58 0x10000"
	<Wait>
	<Send>  "on -p6r -f /net/nv-1-0/ xglcdiag ccsracc wr 9e48 0x19c"
	<Wait>
	<Send>  "on -p6r -f /net/nv-1-0/ xglcdiag ccsracc wr 9e58 0x10000"
	<Wait>
	#clear err
	<Send>  "on -p6r -f /net/nv-1-0/ xglcdiag ccsracc wr 8e40 0x8000000c"
	<Wait>
	<Send>  "on -p6r -f /net/nv-1-0/ xglcdiag ccsracc wr 9e40 0x8000000c"
	<Wait>
	#For clear memselect error adr
	<Send>  "on -p6r -f /net/nv-1-0/ xglcdiag ccsracc wr 8e40 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-1-0/ xglcdiag ccsracc wr 8e4c 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-1-0/ xglcdiag ccsracc wr 8e50 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-1-0/ xglcdiag ccsracc wr 9e40 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-1-0/ xglcdiag ccsracc wr 9e4c 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-1-0/ xglcdiag ccsracc wr 9e50 0x0"
	<Wait>
   <Sleep> 1
</Bypass>

<Bypass>    $Slot_INST_2_GBL
	<Send>  "on -p6r -f /net/nv-2-0/ xglcdiag ccsracc wr 8e48 0x19c"
	<Wait>
	<Send>  "on -p6r -f /net/nv-2-0/ xglcdiag ccsracc wr 8e58 0x10000"
	<Wait>
	<Send>  "on -p6r -f /net/nv-2-0/ xglcdiag ccsracc wr 9e48 0x19c"
	<Wait>
	<Send>  "on -p6r -f /net/nv-2-0/ xglcdiag ccsracc wr 9e58 0x10000"
	<Wait>
	#clear err
	<Send>  "on -p6r -f /net/nv-2-0/ xglcdiag ccsracc wr 8e40 0x8000000c"
	<Wait>
	<Send>  "on -p6r -f /net/nv-2-0/ xglcdiag ccsracc wr 9e40 0x8000000c"
	<Wait>
	#For clear memselect error adr
	<Send>  "on -p6r -f /net/nv-2-0/ xglcdiag ccsracc wr 8e40 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-2-0/ xglcdiag ccsracc wr 8e4c 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-2-0/ xglcdiag ccsracc wr 8e50 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-2-0/ xglcdiag ccsracc wr 9e40 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-2-0/ xglcdiag ccsracc wr 9e4c 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-2-0/ xglcdiag ccsracc wr 9e50 0x0"
	<Wait>
   <Sleep> 1
</Bypass>

<Bypass>    $Slot_INST_3_GBL
	<Send>  "on -p6r -f /net/nv-3-0/ xglcdiag ccsracc wr 8e48 0x19c"
	<Wait>
	<Send>  "on -p6r -f /net/nv-3-0/ xglcdiag ccsracc wr 8e58 0x10000"
	<Wait>
	<Send>  "on -p6r -f /net/nv-3-0/ xglcdiag ccsracc wr 9e48 0x19c"
	<Wait>
	<Send>  "on -p6r -f /net/nv-3-0/ xglcdiag ccsracc wr 9e58 0x10000"
	<Wait>
	#clear err
	<Send>  "on -p6r -f /net/nv-3-0/ xglcdiag ccsracc wr 8e40 0x8000000c"
	<Wait>
	<Send>  "on -p6r -f /net/nv-3-0/ xglcdiag ccsracc wr 9e40 0x8000000c"
	<Wait>
	#For clear memselect error adr
	<Send>  "on -p6r -f /net/nv-3-0/ xglcdiag ccsracc wr 8e40 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-3-0/ xglcdiag ccsracc wr 8e4c 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-3-0/ xglcdiag ccsracc wr 8e50 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-3-0/ xglcdiag ccsracc wr 9e40 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-3-0/ xglcdiag ccsracc wr 9e4c 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-3-0/ xglcdiag ccsracc wr 9e50 0x0"
	<Wait>
   <Sleep> 1
</Bypass>

<Bypass>    $Slot_INST_4_GBL
	<Send>  "on -p6r -f /net/nv-4-0/ xglcdiag ccsracc wr 8e48 0x19c"
	<Wait>
	<Send>  "on -p6r -f /net/nv-4-0/ xglcdiag ccsracc wr 8e58 0x10000"
	<Wait>
	<Send>  "on -p6r -f /net/nv-4-0/ xglcdiag ccsracc wr 9e48 0x19c"
	<Wait>
	<Send>  "on -p6r -f /net/nv-4-0/ xglcdiag ccsracc wr 9e58 0x10000"
	<Wait>
	#clear err
	<Send>  "on -p6r -f /net/nv-4-0/ xglcdiag ccsracc wr 8e40 0x8000000c"
	<Wait>
	<Send>  "on -p6r -f /net/nv-4-0/ xglcdiag ccsracc wr 9e40 0x8000000c"
	<Wait>
	#For clear memselect error adr
	<Send>  "on -p6r -f /net/nv-4-0/ xglcdiag ccsracc wr 8e40 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-4-0/ xglcdiag ccsracc wr 8e4c 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-4-0/ xglcdiag ccsracc wr 8e50 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-4-0/ xglcdiag ccsracc wr 9e40 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-4-0/ xglcdiag ccsracc wr 9e4c 0x0"
	<Wait>
	<Send>  "on -p6r -f /net/nv-4-0/ xglcdiag ccsracc wr 9e50 0x0"
	<Wait>
   <Sleep> 1
</Bypass>




