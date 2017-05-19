 ################################################################################
#
# Module:      Clean_IMC_Drives_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Post_BI.dat,Config.dat
#
# Version:    1.4 $Id: Clean_IMC_drives_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 11/18/11
#              01/18/12 Changed for Reduced Size CF(241blcks)Bug 18719
#                2/24/12 Inclreased Copy time mfg ot hdp/mfg
#			  6/10/13 Prompt changes in 6.1R2
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################
<Msg>		"Cleanup Drives...."
<TimeOut>	10
<Prompt>	"[local]#"
<Send>
<Wait>
<Send>		"dir /hd"
<Wait>
<GetData>
<Send>		"dir /cfint"
<Wait>
<GetData>
<Include>	Shell_imc.inc
<TimeOut>	10
<msg>		"Set terminal Column width"
<Send>		'COLUMNS=160'
<Wait>
<GetData>
<msg>		"Checking Drive Size"
<send>		'fdisk /dev/hd0 info;fdisk /dev/hd0 show'
<wait>
<GetData>
<CheckData> "1. QNX       77          0      38159     381[56][09]  78151648  38159 MB"
<CheckData> "2. QNY       78      38160      76318     3815[89]  78149632  38159 MB   \*"

<send>		'fdisk /dev/cfint0 info;fdisk /dev/cfint0 show'
<wait>
<GetData>
<CheckData> "1. QNX       77          0        .*    1[12][38] MB"
#<CheckData> "1. QNX       77          0        123       123    253920    123 MB"

#/cfint
<CheckData> "2. QNY       78        .*    251904    123 MB   \*"
#<CheckData> "2. QNY       78        124        246       122    251904    123 MB   \*"
#<CheckData> "1. QNX       77          0        123       123    253920    123 MB"
#<CheckData> "2. QNY       78        124        246       122    251904    123 MB   \*"

<Msg>		"Moving /hd/mfg to /hdp/mfg"
<Send>		'rm -fr  /hdp/mfg'
<Wait>
<timeout> 90
<Send>		'cp -r  /hd/mfg /hdp'
<Wait>
<Checkdatax>	"error"
<Send>		'rm -fr  /hd/mfg'
<Wait>

<Msg>		'Cleaning cfint Flash ..."
<Send>		'rm  /cfint/*.ksh'
<Wait>
<Send>		'rm  /cfint/nice'
<Wait>
<Send>		'rm  /cfint/*.sh'
<Wait>
<Msg>		'Cleaning cfintp Flash ..."
<Send>		'rm -rf /cfintp/*'
<Wait>
<Msg>		'Cleaning Ext Flash ..."
<Send>		'rm -rf /cfext/*'
<Wait>
<Msg>		'Cleaning HD ..."
<Send>		'rm -rf /hd/logs'
<Wait>
<Send>		'ls /hd/logs'
<Wait>
<GetData>
<CheckdataX>	'File system:'
<Msg>		'Cleaning HDP ..."
<Send>		'rm -rf /hdp/logs'
<Wait>
<Send>		'ls /hdp/logs'
<Wait>
<GetData>
<CheckdataX>	'File system:'

# causes problems on bootup
#<Send>		'rm -rf /hd/dump'
#<Send>		'rm -f /hd/*'
<Send>		'rm  /hd/*.bin'
<Wait>
<Send>		'rm  /hd/*.zip'
<Wait>
<Send>		'rm  /hd/*.tmp'
<Wait>
<Send>		'rm  /hd/tmp*'
<Wait>
<Send>		'rm  /hd/temp*'
<Wait>
#<Send>      'rm -fr /hdp/*'
#<Wait>
<Send>		'rm -f /hd/dump/*'
<Wait>
<GetData>
<Send>		'rm -fr /hd/dump/slot0/*'
<Wait>
<GetData>
<Send>		'rm -fr /hd/dump/slot1/*'
<Wait>
<GetData>
<Send>		'rm -fr /hd/dump/slot2/*'
<Wait>
<GetData>
<Send>		'rm -fr /hd/dump/slot3/*'
<Wait>
<GetData>
<Send>		'rm -fr /hd/dump/slot4/*'
<Wait>
<GetData>

<Prompt>	"[local]#"
<Send>		'exit'
<Wait>
<GetData>
<Msg>		"Checking HD Slot 0..."
<Send>		'dir /hd/dump/slot0'
<Wait>
<GetData>
<CheckdataX>	'File system:'
<Msg>		"Checking HD Slot 1..."
<Send>		'dir /hd/dump/slot1'
<Wait>
<GetData>
<Bypass>	$Slot_INST_1_GBL
	<CheckdataX>	'File system:'
</Bypass>
<Msg>		"Checking HD Slot 2..."
<Send>		'dir /hd/dump/slot2'
<Wait>
<GetData>
<Bypass>	$Slot_INST_2_GBL
	<CheckdataX>	'File system:'
</Bypass>
<Msg>		"Checking HD Slot 3..."
<Send>		'dir /hd/dump/slot3'
<Wait>
<GetData>
<Bypass>	$Slot_INST_3_GBL
   <CheckdataX>	'File system:'
</Bypass>
<Msg>		"Checking HD Slot 4..."
<Send>		'dir /hd/dump/slot4'
<Wait>
<GetData>
<Bypass>	$Slot_INST_4_GBL
	<CheckdataX>	'File system:'
</Bypass>


<Msg>		"Checking Cfext..."
<Send>		'dir /cfext'
<Wait>
<GetData>
<CheckdataX>	'File system:'
<CheckdataX>	'ERROR'

<Msg>		"Checking Cfint..."
<Send>		'del diag.bin'
<Wait>
<GetData>
<Send>		'del u-boot.bin'
<Wait>
<Send>		'del stokeboot.bin'
<Wait>
<Send>		'del stokeboot'
<Wait>
<GetData>
<Send>		'del bootloader'
<Wait>
<Send>		'del bootloader.bin'
<Wait>
<Send>		'del noodle.bin'
<Wait>
<Send>		'del nice'
<Wait>
<Send>		'del gunzip'
<Wait>
<Send>		'del onscriptR1.ksh'
<Wait>
<Send>		'del onscript_GLC_R2.ksh'
<Wait>
<Send>		'del onscript_GLC_R3.ksh'
<Wait>
<Send>		'del GLC.ksh'
<Wait>
<Send>		'del onscript_MC_R1.ksh'
<Wait>
<Send>		'del IMC.ksh'
<Wait>
<Sleep>		1
<Send>		'dir /cfint'
<Wait>
<GetData>
<Checkdata>	'stoke.cfg'
<Checkdata>	'File system:'
<Checkdatax>	'stoke.bin'
<CheckDataX>	'u-boot.bin'
<CheckDataX>	'stoke.conf'
<CheckDataX>	'stokeboot'
<CheckDataX>	'bootloader.bin'
<CheckDataX>	'bootloader'
<CheckDataX>	'diag.bin'
<CheckDataX>	'noodle.bin'
<CheckDataX>	'onscriptR1.ksh'
<CheckdataX>	'ERROR'

#<Msg>       "Checking Cfintp..."
#<Send>      'dir /cfintp'
#<Wait>
#<GetData>
#<CheckdataX>    'File system:'
#<CheckdataX>    'ERROR'

<Send>		"dir /hd"
<Wait>
<GetData>
<Checkdata>		$StokeOS_ISSU_Install_gbl
<CheckdataX>	'stoke.bin'
<Checkdata>	'File system:'
<CheckDataX>	'u-boot.bin'
<CheckDataX>	'stoke.conf'
<CheckDataX>	'stokeboot'
<CheckDataX>	'bootloader.bin'
<CheckDataX>	'bootloader'
<CheckDataX>	'diag.bin'
<CheckDataX>	'noodle.bin'
<CheckDataX>	'onscriptR1.ksh'
<CheckdataX>	'ERROR'
<Send>		"dir /hd/dump"
<Wait>
<GetData>
	<Checkdata>	'4096 slot0'
	<checkdatax> 'pax'
<Bypass>	$Slot_INST_1_GBL
	<Checkdata>	'4096 slot1'
</Bypass>
<Msg>		"Bypassed Slot 2-4 not showing"
#<Bypass>    $Slot_INST_2_GBL
#    <Checkdata> '4096 slot2'
#</Bypass>
#<Bypass>    $Slot_INST_3_GBL
#    <Checkdata> '4096 slot3'
#</Bypass>
#<Bypass>    $Slot_INST_4_GBL
#    <Checkdata> '4096 slot4'
#</Bypass>
#<Send>      "dir /hd/logs"
#<Wait>
#<GetData>






