################################################################################
#
# Module:      tftpcopy_stoke_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Config.dat
#
# Version:    1.4   $Id: tftpcopy_stoke_diag_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 12/2011 from tftpcopy_stoke 12/12/11
#			  Increased blksize to 2048 7/30/12
#			  Added delete of inactive GLC console files 8/1/12
#			  Added BMR_Read_XGLC 7/14/15

#
#
# Still ToDo:
#             Add rm *core* to each dump directory
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################

# TFTP Boot an IMC
#GW_IP_IP		=	92.168.64.254
# unix HOST_IP		=	192.168.64.252
# Windows
#HOST_IP		=	192.168.64.113
#UUT_IP_Base	=	192.168.64.130
#UUT_IP_Range	=	2


<Msg>		"TFTP Copy files..."
<Prompt>	'#'
<Timeout>	10
<Msg>		"Get Chassis MAC ..."
<Sendslow>		"pfeffa rd i2c 9501 chassis tlv 8"
<Wait>
<GetData>	GetMAC

#io-net -dmv64360 mac=001273000e40,deviceindex=0,speed=100,duplex=1 -ptcpip-v4
# Laurel 6.x
#io-pkt-v4 -dmv64360 mac=001273000e40,deviceindex=0,speed=100,duplex=1 -ptcpip-v4

<Msg>		"Config Ethernet"
<SendChr>	"io-pkt-v4 -dmv64360 mac="
<SendChr>	$MAC[0]
<Send>		",deviceindex=0,speed=100,duplex=1 -ptcpip-v4"
<Wait>
<GetData>
#ifconfig en0 172.17.24.12 netmask 255.255.255.0
<SendChr>	"ifconfig en0 "
<SendChr>	$UUT_IP
#<Send>		" netmask 255.255.255.0"
<SendChr>		" netmask "
<Send>		$Netmask
<Wait>
<GetData>
#route add 0.0.0.0 172.17.24.1
<SendChr>	"route add 0.0.0.0 "
<Send>		$GW_IP
<Wait>
<GetData>

<Msg>		'Check port is up..'
<Sleep>		10
<SendChar>	'/usr/bin/ping -c 5 '
<Send>		$HOST_IP
<Wait>
<GetData>
<CheckData>	'5 packets transmitted, 5 packets received, 0% packet loss'

<Send>		"rm /cfint/*"
<Wait>
<GetData>
<Send>		"rm /cfintp/*"
<Wait>
<GetData>
<Send>		"rm -r /hd/mfg"
<Wait>
<GetData>
<Send>		"rm /hd/*"
<Wait>
<GetData>
<Send>		"rm -r /hd/dump/*"
<Wait>
<GetData>
<Send>		"rm /hd/logs/*"
<Wait>
<GetData>
<Send>		"rm /hdp/logs/*"
<Wait>
<GetData>
<Send>		"rm /hdp/*inactive"
<Wait>
<GetData>
#Added 1/13/09 for ISSU 4.3B4
<Send>		"rm -r /hdp/issu/*"
<Wait>
<GetData>
#<Send>		"rm -r /hdp/settings/*"
#<Wait>
#<GetData>
<Send>		"rm -r /hdp/images/*"
<Wait>
<GetData>
<Send>		"ls -l /cfint/stoke.bin"
<Wait>
<GetData>
<CheckData>	"No such file or directory"
#<CheckDataX>	"stoke.bin"
<Bypass>	$Slot_INST_1_IMC_GBL
 	<Send>		"rm /net/nv-1-0/cfint/*"
	<Wait>
	<GetData>
	<Send>		"rm /net/nv-1-0/cfintp/*"
	<Wait>
	<GetData>
	<Send>		"rm -r /hd/mfg"
	<Wait>
	<GetData>
        <Send>		"rm /net/nv-1-0/hd/*"
	<Wait>
	<GetData>
	<Send>		"rm -r /net/nv-1-0/hd/dump/*"
	<Wait>
	<GetData>
	<Send>		"rm /net/nv-1-0/hd/logs/*"
	<Wait>
	<GetData>
	<Send>		"rm /net/nv-1-0/hdp/logs/*"
	<Wait>
	<GetData>
	<Send>		"rm /net/nv-1-0/hdp/*inactive"
	<Wait>
	<GetData>
	#Added 1/13/09 for ISSU 4.3B4
	<Send>		"rm -r /net/nv-1-0/hdp/issu/*"
	<Wait>
	<GetData>
	#<Send>		"rm -r /net/nv-1-0/hdp/settings/*"
	#<Wait>
	#<GetData>
	<Send>		"rm -r /net/nv-1-0/hdp/images/*"
	<Wait>
	<Send>		"ls -l /net/nv-1-0/cfint/stoke.bin"
	<Wait>
	<GetData>
	<CheckData>	"No such file or directory"
</Bypass>

<Send>
<Wait>

<Msg>		'Create mfg dir...'
<Timeout>  30
<Send>			"mkdir /hd/mfg"
<Wait>
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'Create Slot 1-4 dump directories...'
<Timeout>  30
<Send>			"mkdir /hd/dump/slot1"
<Wait>
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Bypass>    $Slot_INST_1_IMC_GBL
	<Send>			"mkdir /net/nv-1-0/hd/dump/slot1"
	<Wait>
	<CheckDataX>   "No such file or directory"
	<CheckDataX>   "Transfer timed out"
	<CheckDataX>   "Error"
	<CheckDataX>   "Fail"
	<GetData>
</Bypass>

<Send>			"mkdir /hd/dump/slot2"
<Wait>
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Send>			"mkdir /hd/dump/slot3"
<Wait>
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Send>			"mkdir /hd/dump/slot4"
<Wait>
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Send>			"cp -r /hd/dump /net/nv-1-0/hd"
<Wait>
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Send>
<Wait>
#/usr/bin/tftp 172.17.24.10
<Prompt>	'tftp>'
<SendChr>		'/usr/bin/tftp '
<Send>		$HOST_IP
<Wait>
<GetData>

<Send>		"mode binary"
<Wait>
<GetData>

#New for 6.0 Images have gone past the 32meg barrier, default block size of 512 bytes allows only a maximum of just under 32 MB
<Send>		"blksize 2048"
<Wait>
<GetData>


#Get Files
#get diag073106/diag.bin cfint/diag.bin
<Msg>		"TFTP Copy files from:"
<Msg>		$release_name_global
<Msg>		$tftp_copypath_diag_gbl


<Msg>		'Copy Diag Files...."
<Msg>		'TFTP Copy file onscript_GLC.ksh...'
<Timeout>  30
<SendChar>		"get "
<SendChar>		$tftp_copypath_diag_gbl
<SendChar>		$Stoke_onscript_GLC
<SendChar>		" /hd/mfg/"
<Send>			$Stoke_onscript_GLC
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file onscript_MC.ksh...'
<Timeout>  30
<SendChar>		"get "
<SendChar>		$tftp_copypath_diag_gbl
<SendChar>		$Stoke_onscript_MC
<SendChar>		" /hd/mfg/"
<Send>			$Stoke_onscript_MC
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file onscript_XFLC.ksh...'
<Timeout>  30
<SendChar>		"get "
<SendChar>		$tftp_copypath_diag_gbl
<SendChar>		$Stoke_onscript_XGLC
<SendChar>		" /hd/mfg/"
<Send>			$Stoke_onscript_XGLC
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file BMR.ksh...'
<Timeout>  30
<SendChar>		"get "
<SendChar>		$tftp_copypath_diag_gbl
<SendChar>		"BMR.ksh"
<SendChar>		" /hd/mfg/"
<Send>			"BMR.ksh"
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file formatto40gigpartiton.sh...'
<Timeout>  30
<SendChar>		"get "
<SendChar>		$tftp_copypath_diag_gbl
<SendChar>		$Format_40gig_MC
<SendChar>		" /hd/mfg/"
<Send>			$Format_40gig_MC
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file storageprep80.sh...'
<Timeout>  30
<SendChar>		"get "
<SendChar>		$tftp_copypath_diag_gbl
<SendChar>		$Format_MC
<SendChar>		" /tmp/"
<Send>			$Format_MC
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file diag_glc.bin...'
<Timeout>  120
<SendChar>		"get "
<SendChar>		$tftp_copypath_diag_gbl
<SendChar>		$Stoke_diag_glc
<SendChar>		" /hd/mfg/"
<Send>			$Stoke_diag_glc
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file diag_xglc.bin...'
<Timeout>  120
<SendChar>		"get "
<SendChar>		$tftp_copypath_diag_gbl
<SendChar>		$Stoke_diag_xglc
<SendChar>		" /hd/mfg/"
<Send>			$Stoke_diag_xglc
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>




<Msg>		"Copy OS Files..."
<Msg>		'TFTP Copy file stoke.cfg...'
<Timeout>  120
<SendChar>		"get "
<SendChar>		$tftp_copypath_release_gbl
<SendChar>		$Stoke_config
<SendChar>		" /cfint/"
<Send>			$Stoke_config
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file stoke.bin...'
<Timeout>  120
<SendChar>		"get "
<SendChar>		$tftp_copypath_release_gbl
<SendChar>		$Stoke_image
<SendChar>		" /hd/mfg/"
<Send>			$Stoke_image
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file stokepkg.bin...'
<Timeout>  230
<SendChar>		"get "
<SendChar>		$tftp_copypath_release_gbl
<SendChar>		$Stoke_pkg
<SendChar>		" /hd/"
<Send>			$StokeOS_ISSU_Install_gbl
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file stokeboot...'
<Timeout>  60
<SendChar>		"get "
<SendChar>		$tftp_copypath_release_gbl
<SendChar>		$Stoke_uboot
<SendChar>		" /hd/mfg/"
<Send>			$Stoke_uboot
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file stokebootxglc...'
<Timeout>  60
<SendChar>		"get "
<SendChar>		$tftp_copypath_release_gbl
<SendChar>		$Stoke_ubootxglc
<SendChar>		" /hd/mfg/"
<Send>			$Stoke_ubootxglc
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file bootloader...'
<Timeout>  90
<SendChar>		"get "
<SendChar>		$tftp_copypath_release_gbl
<SendChar>		$Stoke_bootloader
<SendChar>		" /hd/mfg/"
<Send>			$Stoke_bootloader
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>
<Msg>		'TFTP Copy file bootloader2...'
<Timeout>  90
<SendChar>		"get "
<SendChar>		$tftp_copypath_release_gbl
<SendChar>		$Stoke_bootloader2
<SendChar>		" /hd/mfg/"
<Send>			$Stoke_bootloader2
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>		'TFTP Copy file Noodle...'
<Timeout>  90
<SendChar>		"get "
<SendChar>		$tftp_copypath_release_gbl
<SendChar>		$Stoke_noodle
<SendChar>		" /hd/mfg/"
<Send>			$Stoke_noodle
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>


#<Msg>       'TFTP Copy file xlp.rootfs.gz...'
#<Timeout>  120
#<SendChar>      "get "
#<SendChar>      $tftp_copypath_release_gbl
#<SendChar>      "xlp.rootfs.gz"
#<SendChar>      " /hd/mfg/"
#<Send>          "xlp.rootfs.gz"
#<Wait>
#<CheckData>     "Received"
#<CheckDataX>   "No such file or directory"
#<CheckDataX>   "Transfer timed out"
#<CheckDataX>   "Error"
#<CheckDataX>   "Fail"
#<GetData>

<Msg>		'TFTP Copy file rcw_xglc.bin...'
<Timeout>  120
<SendChar>		"get "
<SendChar>		$tftp_copypath_release_gbl
<SendChar>		"rcw_xglc.bin"
<SendChar>		" /hd/mfg/"
<Send>			"rcw_xglc.bin"
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>


<Msg>		'TFTP Copy file ucode.bin...'
<Timeout>  120
<SendChar>		"get "
<SendChar>		$tftp_copypath_release_gbl
<SendChar>		"ucode.bin"
<SendChar>		" /hd/mfg/"
<Send>			"ucode.bin"
<Wait>
<CheckData>		"Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

<Msg>       'TFTP Copy file stoke.glc.bin...'
<Timeout>  120
<SendChar>      "get "
<SendChar>      $tftp_copypath_release_gbl
<SendChar>      "stoke.glc.bin"
<SendChar>      " /hd/mfg/"
<Send>          "stoke.glc.bin"
<Wait>
<CheckData>     "Received"
<CheckDataX>   "No such file or directory"
<CheckDataX>   "Transfer timed out"
<CheckDataX>   "Error"
<CheckDataX>   "Fail"
<GetData>

#tftpboot/OS_B/flashimg.bin




#Exit tftp
<Prompt>	'#'
<Timeout>	10
<Send>		'quit'
<Wait>
 # Diags check
<Send>		"ls -l /hd/mfg/diag_glc.bin"
<Wait>
<GetData>
<CheckData>	"diag_glc.bin"
<CheckDataX>	"No such file or directory"
<Send>		"ls -l /hd/mfg/diag_xglc.bin"
<Wait>
<GetData>
<CheckData>	"diag_xglc.bin"
<CheckDataX>	"No such file or directory"
<Send>		"ls -l /hd/mfg/noodle.bin"
<Wait>
<GetData>
<CheckData>	"noodle.bin"
<CheckDataX>	"No such file or directory"
<Send>		"ls -l /hd/mfg/GLC*"
<Wait>
<GetData>
<CheckData>	"GLC"
<CheckDataX>	"No such file or directory"
<Send>		"ls -l /hd/mfg/IMC*"
<Wait>
<GetData>
<CheckData>	"IMC"
<CheckDataX>	"No such file or directory"

## OS Check
<Send>		"ls -l /hd/mfg/stoke.bin"
<Wait>
<GetData>
<CheckData>	"stoke.bin"
<CheckDataX>	"No such file or directory"

<Sendchr>		"ls -l /hd/"
<Send>		"$StokeOS_ISSU_Install_gbl"
<Wait>
<GetData>
<CheckData>	"StokeOS"
<CheckDataX>	"No such file or directory"
<Send>		"ls -l /hd/mfg/stokeboot.bin"
<Wait>
<GetData>
<CheckData>	"stokeboot"
<CheckDataX>	"No such file or directory"
<Send>
<Wait>
<Send>		"ls -l /hd/mfg/bootloader2.bin"
<Wait>
<GetData>
<CheckData>	"bootloader2"
<CheckDataX>	"No such file or directory"
<Send>
<Wait>
<Send>		"ls -l /hd/mfg/xlp.rootfs.gz"
<Wait>
<GetData>
#<CheckData> "xlp.rootfs.gz"
#<CheckDataX>    "No such file or directory"
#<Send>
#<Wait>

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
#<Send>      'rm -fr /hdp/*'
#<Wait>
<Send>		'rm -f /hd/dump/slot0/*'
<Wait>
<GetData>
<Send>		'rm -f /hd/dump/slot1/*'
<Wait>
<GetData>
<Send>		'rm -f /hd/dump/slot2/*'
<Wait>
<GetData>
<Send>		'rm -f /hd/dump/slot3/*'
<Wait>
<GetData>
<Send>		'rm -f /hd/dump/slot4/*'
<Wait>
<GetData>
<Send>		"ls -l /hd/mfg/stoke.bin"
<Wait>
<GetData>
<CheckDataX>	"No such file or directory"
<Bypass>	$Slot_INST_1_IMC_GBL
	<Msg>		'Create mfg dir...'
	<Timeout>  30
	<Send>			"mkdir /net/nv-1-0/hd/mfg"
	<Wait>
	<CheckDataX>   "No such file or directory"
	<CheckDataX>   "Transfer timed out"
	<CheckDataX>   "Error"
	<CheckDataX>   "Fail"
	<GetData>
	<Msg>	"Copy IMC Slot 0 Cfint files to IMC Slot 1 Cfint..."
	<Timeout>	90
	<Send>      "if (cp -vp /cfint/* /net/nv-1-0/cfint) then (echo "CFint_Copy_PASSED") else (echo "CFint_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"CFint_Copy_PASSED"
	<GetData>
    <Msg>	"Copy IMC Slot 0 HD files to IMC Slot 1 HD..."
	<Timeout>	90
	<Send>      "if (cp -vp /hd/* /net/nv-1-0/hd) then (echo "HD_Copy_PASSED") else (echo "HD_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"HD_Copy_PASSED"
	<GetData>
	<Timeout>	90
	<Send>      "if (cp -vp /hd/mfg/* /net/nv-1-0/hd/mfg) then (echo "HD_Copy_PASSED") else (echo "HD_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"HD_Copy_PASSED"
	<GetData>


    <Msg>		'Cleaning Ext Flash ..."
	<Send>		'rm -rf /net/nv-1-0/cfext/*'
	<Wait>
	<Msg>		'Cleaning HD ..."
	<Send>		'rm -rf /net/nv-1-0/hd/logs'
	<Wait>
	<Send>		'ls /net/nv-1-0/hd/logs'
	<Wait>
	<GetData>
	<CheckdataX>	'File system:'
	<Msg>		'Cleaning HDP ..."
	<Send>		'rm -rf /net/nv-1-0/hdp/logs'
	<Wait>
	<Send>		'ls /net/nv-1-0/hdp/logs'
	<Wait>
	<GetData>
	<CheckdataX>	'File system:'

	# causes problems on bootup
	#<Send>		'rm -rf /net/nv-1-0/hd/dump'
	#<Send>      'rm -fr /net/nv-1-0/hdp/*'
	#<Wait>
	<Send>		'rm -f /net/nv-1-0/hd/dump/slot0/*'
	<Wait>
	<GetData>
	<Send>		'rm -f /net/nv-1-0/hd/dump/slot1/*'
	<Wait>
	<GetData>
	<Send>		'rm -f /net/nv-1-0/hd/dump/slot2/*'
	<Wait>
	<GetData>
	<Send>		'rm -f /net/nv-1-0/hd/dump/slot3/*'
	<Wait>
	<GetData>
	<Send>		'rm -f /net/nv-1-0/hd/dump/slot4/*'
	<Wait>
	<GetData>
	#picking up failure before images have been loaded to drive or tftp
	<Send>		"rm /hdp/*inactive"
	<Wait>
	<GetData>
	<GetData>
	<Send>		"rm /net/nv-1-0/hdp/*inactive"
	<Wait>
	<GetData>


</Bypass>



