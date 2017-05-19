################################################################################
#
# Module:      Bench_Test_IMC.inc
#
# Author:      Joe White
#
# Descr:       Main Execution for IMC Bench test
#
# Version:    1.2 $Id: Bench_Test_IMC.inc,v 1.7 2011/01/21 18:38:55 joe Exp $
#
# Changes:    Version 1	10/09/05 JSW
#			  Added Set FIC type for PR 4320
#			  11/6/08 Added Get Data statements
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################

<Msg>		"Test Disco"
<Prompt>	"> "
<Timeout>	10
<Send>		"pfeffa"
<Wait>
<Send>		"set hw dx auto"
<Wait>

<Send>		"test dx access"
<Wait>
<GetData>
<CheckData>	'TESTING PCI ACCESS TO PRESTERA 0 ...  PASS'
<CheckData>	'TESTING PCI ACCESS TO PRESTERA 1 ...  PASS'
<CheckData> 'TESTING PCI ACCESS INDEPENDENCE TO PRESTERAS ...  PASS'

<Msg>		"Check Disco Link 0"
<Send>		"test link disco 0 biga"
<Wait>
<Sleep>		3
<Send>		"test link disco 0 biga"
<Wait>
<Sleep>		3
<Send>		"test link disco 0 biga"
<Wait>
<Sleep>		3
<Send>		"test link disco 0 biga"
<Wait>
<Sleep>		3
<Send>		"test link disco 0 biga"
<Wait>
<Sleep>		3
<GetData>
<CheckData>	'TESTING LINK DISCO 0 TO BIG-AL ... PASS'

<Msg>		"Check Disco Link 1"
<Send>		"test link disco 1 biga"
<Wait>
<Sleep>		1
<Send>		"test link disco 1 biga"
<Wait>
<Sleep>		1
<Send>		"test link disco 1 biga"
<Wait>
<Sleep>		1
<Send>		"test link disco 1 biga"
<Wait>
<Sleep>		1
<Send>		"test link disco 1 biga"
<Wait>
<GetData>
<Sleep>		1

<Timeout>	15
<CheckData>	"TESTING LINK DISCO 1 TO BIG-AL ... PASS"
<Msg>		"Check Disco Link 2"
<Send>		"test link disco 2 biga"
<Wait>
<Sleep>		1
<Send>		"test link disco 2 biga"
<Wait>
<Sleep>		1
<Send>		"test link disco 2 biga"
<Wait>
<Sleep>		1
<Send>		"test link disco 2 biga"
<Wait>
<Sleep>		1
<Send>		"test link disco 2 biga"
<Wait>
<GetData>
<Sleep>		1
<CheckData>	'TESTING LINK DISCO 2 TO BIG-AL ... PASS'

<Msg>		"Check Disco Link 1 to Switch"
<Send>		"test link disco 1 sw"
<Wait>
<Sleep>		1
<Send>		"test link disco 1 sw"
<Wait>
<Sleep>		1
<Send>		"test link disco 1 sw"
<Wait>
<Sleep>		1
<Send>		"test link disco 1 sw"
<Wait>
<Sleep>		1
<Send>		"test link disco 1 sw"
<Wait>
<GetData>
<Sleep>		1
<CheckData>	"TESTING LINK DISCO 1 TO DXBASE 0 ... PASS"

#<Msg>		"Bypassed Check Disco Link 2 to Switch  Debug ??"
#<Msg>		"Check Disco Link 2 to Switch"
#<Send>		"test link disco 2 sw"
#<Wait>
#<Sleep>		1
#<Msg>		"Check Disco Link 2 to Switch"
#<Send>		"test link disco 2 sw"
#<Wait>
#<Sleep>		1
#<Msg>		"Check Disco Link 2 to Switch"
#<Send>		"test link disco 2 sw"
#<Wait>
#<Sleep>		1
#<CheckData>	'TESTING LINK DISCO 2 TO DX5 0 ... PASS'

# <Msg>		"Exiting pfeffa..."
#<Prompt>	"#"
#<Send>		"exit"
#<Wait>


