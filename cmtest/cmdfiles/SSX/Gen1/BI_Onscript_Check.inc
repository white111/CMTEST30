################################################################################
#
# Module:      BI_Onscript_Start.txt
#
# Author:      Joe White
#
# Descr:       Starts Background execution of GLC memory tests
#
# Version:    1.0 $Id: BI_Onscript_Check.inc,v 1.2 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Copied from Onscript_Start 1.4 08/01/06
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
#<Timeout>	20
#<Prompt>	'#'
<TimeOut>	300
# Wait for background jobs to finish
<Send>  "wait"
<Wait>
<Send>
<Wait>
<TimeOut>	60
<Msg>	"Check Slot 0 Drive tests"
<SendSlow>	'cat /hd/dump/slot0/onfile.txt'
<Wait>
<GetData>
<SendSlow>	'cat /hd/dump/slot0/Onscript_slot0.txt'
<Wait>
<GetData>
<CheckData>	"DRIVE_TEST.Passed"
<Msg>	"Check Slot 1 Memory tests"
<SendSlow>	'cat /hd/dump/slot1/onfile.txt'
<Wait>
<GetData>
<SendSlow>	'cat /hd/dump/slot0/Onscript_slot1.txt'
<Wait>
<GetData>
<CheckData>	"Memory.Passed"
<Msg>	"Check Slot 2 Memory tests"
<SendSlow>	'cat /hd/dump/slot2/onfile.txt'
<Wait>
<GetData>
<SendSlow>	'cat /hd/dump/slot0/Onscript_slot2.txt'
<Wait>
<GetData>
<CheckData>	"Memory.Passed"
<Msg>	"Check Slot 3 Memory tests"
<SendSlow>	'cat /hd/dump/slot3/onfile.txt'
<Wait>
<GetData>
<SendSLow>	'cat /hd/dump/slot0/Onscript_slot3.txt'
<Wait>
<GetData>
<CheckData>	"Memory.Passed"
<Msg>	"Check Slot 4 Memory tests"
<SendSlow>	'cat /hd/dump/slot4/onfile.txt'
<Wait>
<GetData>
<SendSlow>	'cat /hd/dump/slot0/Onscript_slot4.txt'
<Wait>
<GetData>
<CheckData>	"Memory.Passed"

