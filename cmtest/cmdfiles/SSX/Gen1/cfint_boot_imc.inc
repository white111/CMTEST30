################################################################################
#
# Module:      cfint_boot_imc.inc
#
# Author:      Joe White
#
# Descr:       Called by Bench_IMC.dat, Chassis_Pre,Post,BI.dat
#
# Version:    2.3 $Id: cfint_boot_imc.inc,v 1.7.8.1 2011/11/30 19:48:56 joe Exp $
#
# Changes:    Added <GetData>  12/05/05
#			  Updated to use 3.0 bootloader
#			  12/17/07 Upadted for sometimes missing the passed
#			  CFINT boot time right at 2 min Add adtional 30 sec time for bootup
#			  Added new checks for messages 10/11/11 Case 1313#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
# TFTP Boot an IMC

<Msg>		"Bootloader configure stoke.bin from cfint..."
<TimeOut>	45
<Prompt>	"Stoke-BootLoader#"
<Sendslow>		'boot image file /hd/mfg/stoke.bin'
<Wait>
<GetData>
<CheckData> 'Passed'
<Msg>		'Booting to Stoke Released OS from CFINT....'
<Send>		'go'
<TimeOut>	150
<Prompt>	'Stoke[local]'
<Wait>
<GetData>
<CheckData>	'booting '
<CheckDataX>	"FAIL"
#<CheckDataX>	"ERROR"
<CheckDataX>   "Crash"
<CheckData>	'Welcome to Stoke's Command Line Interface'
<TimeOut>	90
<Send>		'terminal length infinite'
<Wait>
<GetData>

#Check settings


