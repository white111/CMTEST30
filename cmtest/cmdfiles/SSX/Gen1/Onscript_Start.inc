################################################################################
#
# Module:      Onscript_Start.txt
#
# Author:      Joe White
#
# Descr:       Starts Background execution of GLC memory tests
#
# Version:    1.6 $Id: Onscript_Start.inc,v 1.9 2009/05/07 15:50:10 joe Exp $
#
# Changes:    Updated to ad MC R1 and GLC R2 script 04/04/06
#			  Added Bypass commands 8/1/06
#			  Added Selection for IMC or GLC in Slot 1
#			  Added command to slay pfeffa on each slot(new diags)
#			  IMC slot one logs to IMC slot 1 4/21/08
#
# Includes:
#
# Still ToDo:
#              - Add Looping on each test, start a process for each test
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################

<Msg>	"Run 60 second test Drive and Memory test, Test all SRAM"
#Wait for GLC to finish loading
#<Sleep>	30
#<send>  "slay -v glc_download_server"
#<wait>
#<sleep> 2
<Msg>	"Start Slot 0 Drive tests"

#<Sendslowchr>	'on -p 3r -f /net/nv-0-0 /bin/ksh /net/nv-0-0/cfint/'
<Sendslowchr>	'/bin/ksh /net/nv-0-0/cfint/'
<Sendslowchr>	$Stoke_onscript_MC
<Sendslow>		' 60 0 > /net/nv-0-0/hd/dump/slot0/Onscript_slot0.txt 2>&1 &'
#<SendChar>	'on -f /net/nv-0-0 /bin/ksh /net/nv-0-0/cfint/onscript_MC./bin/ksh '
#<SendChar>	$internal_traffic_test_time_GBL
#<Send>	' 0 > /hd/dump/slot0/Onscript_slot0.txt 2>&1 &'
<Wait>
<Sleep>	1

<Bypass>	$Slot_INST_1_IMC_GBL
   <Msg>   "Start Slot 1 Drive tests"
   <Sendslowchr>   'on -p 3r -f /net/nv-1-0 /bin/ksh /net/nv-1-0/cfint/'
   <Sendslowchr>   $Stoke_onscript_MC
   <Sendslow>      ' 60 1 > /net/nv-1-0/hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
   #<SendChar> 'on -f /net/nv-1-0 /bin/ksh /net/nv-1-0/cfint/onscript_MC./bin/ksh '
   #<SendChar> $internal_traffic_test_time_GBL
   #<Send> ' 0 > /hd/dump/slot1/Onscript_slot1.txt 2>&1 &'
   <Wait>
   <Sleep> 1
</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<Msg>	"Start Slot 1 Memory tests"
	<Sendslowchr>	'on -p 3r -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/'
	<Sendslowchr>	 $Stoke_onscript_GLC
	<Sendslow>		' 60  1 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
	#<SendChar>	'on -f /net/nv-1-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
	#<SendChar>	$internal_traffic_test_time_GBL
	#<Send>	' 1 0 > /hd/dump/slot0/Onscript_slot1.txt 2>&1 &'
	<Wait>
	<Sleep>	1
</Bypass>

<Bypass>	$Slot_INST_2_GBL
	<Msg>	"Start Slot 2 Memory tests"
	<Sendslowchr>	'on -p 3r -f /net/nv-2-0 /bin/ksh /net/nv-0-0/cfint/'
	<Sendslowchr>	 $Stoke_onscript_GLC
	<Sendslow>		' 60  2 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
	#<SendChar>	'on -f /net/nv-2-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
	#<SendChar>	$internal_traffic_test_time_GBL
	#<Send>	' 2 0 > /hd/dump/slot0/Onscript_slot2.txt 2>&1 &'
	<Wait>
	<Sleep>	1
</Bypass>

<Bypass>	$Slot_INST_3_GBL
	<Msg>	"Start Slot 3 Memory tests"
	<Sendslowchr>	'on -p 3r -f /net/nv-3-0 /bin/ksh /net/nv-0-0/cfint/'
	<Sendslowchr>	 $Stoke_onscript_GLC
	<Sendslow>		' 60  3 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
	#<SendChar>	'on -f /net/nv-3-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
	#<SendChar>	$internal_traffic_test_time_GBL
	#<Send>	' 3 0 > /hd/dump/slot0/Onscript_slot3.txt 2>&1 &'
	<Wait>
	<Sleep>	1
</Bypass>

<Bypass>	$Slot_INST_4_GBL
	<Msg>	"Start Slot 4 Memory tests"
	<Sendslowchr>	'on -p 3r -f /net/nv-4-0 /bin/ksh /net/nv-0-0/cfint/'
	<Sendslowchr>	$Stoke_onscript_GLC
	<Sendslow>		' 60  4 1 > /net/nv-0-0/hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
	#<SendChar>	'on -f /net/nv-4-0 /bin/ksh /net/nv-0-0/cfint/onscriptR2./bin/ksh '
	#<SendChar>	$internal_traffic_test_time_GBL
	#<Send>	' 4 0 > /hd/dump/slot0/Onscript_slot4.txt 2>&1 &'
	<Wait>
	<Sleep>	1
</Bypass>



