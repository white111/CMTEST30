################################################################################
#
# Module:      Bench_Prog_XGLC_Flash.inc
#
# Author:      Joe White
#
# Descr:       Program XGLC Flash using Ethernet Debug plugin
#
# Version:    1.1 $Id: Bench_Prog_XGLC_Flash.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
#
#
# Changes:    Created 6/3/11
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################
<ETTC>		700
<Msg>		"Program XGLC Flash"
<Msg>		"Verify at Stoke>.."
<TimeOut>	5
<Send>		""
<WaitFor>	"Stoke>"

<Prompt>	"Stoke>"
<TimeOut>	5

<Send>		"version"
<Wait>
<GetData>

<TimeOut>	10
<Msg>		"Getting Product / Serial info ..."
<Send>		"tlvread local tlv 0"
<Wait>
<GetData>	Board
<Msg>		"Program Flash"

<Msg>    "Check Fail Flags:"
 <Msg>     $Exit_On_Error
 <Msg>     $Exit_On_Timeout

 <Msg>		"Set Stop On Error"

<Set>    	$Exit_On_Error
<Set>		$Exit_On_Timeout

 <Msg>    "Check Fail Flags:"
 <Msg>     $Exit_On_Error
 <Msg>    $Exit_On_Timeout


<Send>		"version"
<Wait>
<GetData>


#
<Msg>       "Configure Ethernet"
# setenv ipaddr 172.17.24.11
<SendChr>      "setenv ipaddr "
<Send>		$UUT_IP
<Wait>
<GetData>

<SendChr>      "setenv serverip "
<Send>		$HOST_IP
<Wait>
<GetData>
<GetData>

<SendChr>      "ping  "
<Send>		$HOST_IP
<Wait>
<GetData>
<CheckData>	"host .* is alive"
<GetData>





###############  RCW  e8000000 ######################
<Timeout>	30
<Msg>	"Check RCW Primary Version"
<Send>	"md.b ffdf0043 1"
<Wait>
<GetData>
#Primary Flash Default power on
<CheckData> "ffdf0043: 01"

# Clear DRAM memory
<Send>	"mw.l 1000000 ffffffff 1000000"
<Wait>
<GetData>
<CheckDatax>  "error"
#TFTP File for DRAM
#tftp 1000000 OS_J/rcw_xglc.bin   #Bytes transferred = 80 (50 hex)
<Msg>	"TFTP RCW Image"
#<Send>	"tftp 1000000 OS_J/rcw_xglc.bin"
<Sendchr>	"tftp 1000000 "
<sendchr>	$tftp_copypath_release_gbl
<send>		"rcw_xglc.bin"
<Wait>
<GetData> Check_tftp_size
<CheckData>  "Bytes transferred = 144"
#Compare  CRC of code im memory to code in Flash    +$filesize
#<Send>  "crc32 01000000 1000000"
<Send>	"crc32 01000000 $filesize"
<Wait>
<GetData> Check_CRC32
<CheckData>  "CRC32 for 01000000.*5953871a"
#<Send>	"crc32 e8000000 1000000"
#<Send>	"crc32 e8000000 $filesize"
<Send>	"cmp.b 01000000 e8000000 $filesize"
<Wait>
<GetData> Check_bytecompare
# $compare_gbl
#<GetData> Check_CRC32
#<CheckData>  "CRC32 for 01000000.*5953871a"
#<bypass> $crc32_match_gbl
<bypass> $compare_gbl
	<Msg>	"Program Primary RCW(2min)..."
	#Remove Flash protection
	#protect off e8000000 e8FFFFFF  #Un-Protected 128 sectors
	#<Send>  "protect off e8000000 e8FFFFFF"
	<Send>  "protect off e8000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Un-Protected"
	<Timeout>   90
	#Erase Flash
	#erase e8000000 e8FFFFFF  #Erased 128 sectors
	#<Send>  "erase e8000000 e8FFFFFF"
	<Send>  "erase e8000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Erased"
	#Copy from memory to flash
	#cp.b 1000000 e8000000 1000000  #.done
	#<Send>  "cp.b 1000000 e8000000 1000000"
	<Send>  "cp.b 1000000 e8000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "done"
	<Checkdatax> 'error'
	#dump0x40 of flash location
	#md.b e8000000 40
	<Send>  "md.b e8000000 40"
	<Wait>
	<GetData>
	<Timeout>   30
	#CRC check Flash Space
	#crc32 e8000000 1000000  #CRC32 for e8000000 ... e8ffffff ==> 9247a644
	#<Send>  "crc32 e8000000 1000000"
	<Send>  "crc32 e8000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "CRC32 for e8000000.*5953871a"
	#Apply flash protection
	#protect on e8000000 e8FFFFFF  #Protected 128 sectors
	#<Send>  "protect on e8000000 e8FFFFFF"
	<Send>  "protect on e8000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Protected"
</bypass>


<Msg>   "Check RCW Secondary Version"
#=> secondary bank
<Send>  "mw.b ffdf0043 0"
<Wait>
<Send>  "md.b ffdf0043 1"
<Wait>
<GetData>
#Secondary Flash
<CheckData> "ffdf0043: 00"
#Compare  CRC of code im memory to code in Flash
<Send>	"crc32 01000000 $filesize"
<Wait>
<GetData> Check_CRC32
<CheckData>  "CRC32 for 01000000.*5953871a"
#<Send>	"crc32 e8000000 $filesize"
#<Wait>
#<GetData> Check_CRC32
#<CheckData>  "CRC32 for 01000000.*5953871a"
<Send>	"cmp.b 01000000 e8000000 $filesize"
<Wait>
<GetData> Check_bytecompare
# $compare_gbl

<bypass> $compare_gbl
	<Msg>	"Program Secondary RCW(2min)..."
	<Send>  "protect off e8000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Un-Protected"
	<Timeout>   90
	#Erase Flash
	#erase e8000000 e8FFFFFF  #Erased 128 sectors
	<Send>  "erase e8000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Erased"
	#Copy from memory to flash
	#cp.b 1000000 e8000000 1000000  #.done
	#<Send>  "cp.b 1000000 e8000000 1000000"
	<Send>  "cp.b 1000000 e8000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "done"
	<Checkdatax> 'error'
	#dump0x40 of flash location
	#md.b e8000000 40
	<Send>  "md.b e8000000 40"
	<Wait>
	<GetData>
	<Timeout>   30
	#CRC check Flash Space
	#crc32 e8000000 1000000  #CRC32 for e8000000 ... e8ffffff ==> 5953871a
	<Send>  "crc32 e8000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "CRC32 for e8000000.*5953871a"
	#Apply flash protection
	#protect on e8000000 e8FFFFFF  #Protected 128 sectors
	<Send>  "protect on e8000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Protected"
</bypass>
# Change back to => primary bank
<Send>  "mw.b ffdf0043 1"
<Wait>
<Send>  "md.b ffdf0043 1"
<Wait>
<GetData>
#Secondary Flash
<CheckData> "ffdf0043: 01"
##

################  RCW ######################


###############   Diag Image flash e9000000 ######################
<Timeout>	30
<Msg>	"Check Diag Primary Version"
<Send>	"md.b ffdf0043 1"
<Wait>
<GetData>
#Primary Flash Default power on
<CheckData> "ffdf0043: 01"

# Clear DRAM memory
<Send>	"mw.l 1000000 ffffffff 4000000"
<Wait>
<GetData>
<CheckDatax>  "error"
#TFTP File for DRAM
#tftp 1000000 diag_J/xglcflashdiag.bin   #Bytes transferred = 18765248 (11ace48 hex)
<Msg>	"TFTP Diag Image"
#<Send>	"tftp 1000000 diag_J/xglcflashdiag.bin"
<Sendchr>	"tftp 1000000 "
<Sendchr>	$tftp_copypath_diag_gbl
<Send>	"xglcflashdiag.bin"

<Wait>
<GetData> Check_tftp_size
<CheckData>  "Bytes transferred = 20938276"
#Compare  CRC of code im memory to code in Flash
#<Send>	"crc32 01000000 4000000"
<Send>	"crc32 01000000 $filesize"
<Wait>
<GetData> Check_CRC32
<CheckData>  "CRC32 for 01000000.*4522d8e9"
#<Send>	"crc32 e9000000 4000000"
#<Send>	"crc32 e9000000 $filesize"
#<Wait>
#<GetData> Check_CRC32
##<CheckData>  "CRC32 for e9000000.*4522d8e9"
<Send>	"cmp.b 01000000 e9000000 $filesize"
<Wait>
<GetData> Check_bytecompare
# $compare_gbl
<bypass> $compare_gbl
	<Msg>	"Program Primary Diag(10min)..."
	#Remove Flash protection
	#protect off e9000000 ecffffff  #Un-Protected 512 sectors
	<Send>  "protect off e9000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Un-Protected"
	<Timeout>   600
	#Erase Flash
	#erase e9000000 ecffffff  #Erased 512 sectors
	<Send>  "erase e9000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Erased"
	#Copy from memory to flash
	#cp.b 1000000 e9000000 4000000  #.done
	#<Send>  "cp.b 1000000 e9000000 4000000"
	<Send>  "cp.b 1000000 e9000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "done"
	<Checkdatax> 'error'
	#dump0x40 of flash location
	#md.b e8000000 40
	<Send>  "md.b e9000000 40"
	<Wait>
	<GetData>
	<Timeout>   30
	#CRC check Flash Space
	#crc32 e9000000 4000000  #CRC32 for e9000000 ... ecffffff ==> 6e9bd4ec
	<Send>  "crc32 e9000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "CRC32 for e9000000.*4522d8e9"
	#Apply flash protection
	#protect on e9000000 ecffffff  #Protected 512 sectors
	<Send>  "protect on e9000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Protected"
</bypass>


<Msg>   "Check Diag Secondary Version"
#=> secondary bank
<Send>  "mw.b ffdf0043 0"
<Wait>
<Send>  "md.b ffdf0043 1"
<Wait>
<GetData>
#Secondary Flash
<CheckData> "ffdf0043: 00"
#Compare  CRC of code im memory to code in Flash
<Send>	"crc32 01000000 $filesize"
<Wait>
<GetData> Check_CRC32
<CheckData>  "CRC32 for 01000000.*4522d8e9"
#<Send>  "crc32 e9000000 $filesize"
#<Wait>
#<GetData> Check_CRC32
#<CheckData>  "CRC32 for e9000000.*4522d8e9"
<Send>	"cmp.b 01000000 e9000000 $filesize"
<Wait>
<GetData> Check_bytecompare
# $compare_gbl
<bypass> $compare_gbl
	<Msg>	"Program Secondary Diag(10min)..."
	#Remove Flash protection
	#protect off e9000000 ecffffff  #Un-Protected 512 sectors
	<Send>  "protect off e9000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Un-Protected"
	<Timeout>   600
	#Erase Flash
	#erase e9000000 ecffffff  #Erased 512 sectors
	<Send>  "erase e9000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Erased"
	#Copy from memory to flash
	#cp.b 1000000 e9000000 4000000  #.done
	#<Send>  "cp.b 1000000 e9000000 4000000"
	<Send>  "cp.b 1000000 e9000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "done"
	<Checkdatax> 'error'
	#dump0x40 of flash location
	#md.b e8000000 40
	<Send>  "md.b e9000000 40"
	<Wait>
	<GetData>
	<Timeout>   30
	#CRC check Flash Space
	#crc32 e9000000 4000000  #CRC32 for e9000000 ... ecffffff ==> 6e9bd4ec
	<Send>  "crc32 e9000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "CRC32 for e9000000.*4522d8e9"
	#Apply flash protection
	#protect on e9000000 ecffffff  #Protected 512 sectors
	<Send>  "protect on e9000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Protected"
</bypass>
# Change back to => primary bank
<Send>  "mw.b ffdf0043 1"
<Wait>
<Send>  "md.b ffdf0043 1"
<Wait>
<GetData>
#Secondary Flash
<CheckData> "ffdf0043: 01"
##

################  Diag ######################


###############   ed000000 bootloader2 ######################
<Timeout>	30
<Msg>	"Check Bootloader2 Primary Version"
<Send>	"md.b ffdf0043 1"
<Wait>
<GetData>
#Primary Flash Default power on
<CheckData> "ffdf0043: 01"

# Clear DRAM memory
<Send>	"mw.l 1000000 ffffffff 2000000"
<Wait>
<GetData>
<CheckDatax>  "error"
#TFTP File for DRAM
#tftp 1000000 OS_J/bootloader2.bin   #Bytes transferred = 6134380 (5e29b8 hex)
<Msg>	"TFTP Bootloader2 Image"
#<Send>	"tftp 1000000 OS_J/bootloader2.bin"
<Sendchr>	"tftp 1000000 "
<sendchr>	$tftp_copypath_release_gbl
<send>		"bootloader2.bin"
<Wait>
<GetData> Check_tftp_size
<CheckData>  "Bytes transferred = 8199220"
#Compare  CRC of code im memory to code in Flash
<Send>	"crc32 01000000 $filesize"
<Wait>
<GetData> Check_CRC32
<CheckData>  "CRC32 for 01000000.*52e9348"
#<Send>  "crc32 ed000000 $filesize"
#<Wait>
#<GetData> Check_CRC32
#<CheckData>  "CRC32 for ed000000.*35a4f775"
<Send>	"cmp.b 01000000 ed000000 $filesize"
<Wait>
<GetData> Check_bytecompare
# $compare_gbl
<bypass> $compare_gbl
	<Msg>	"Program Primary Bootloader2(5min)..."
	#Remove Flash protection
	#protect off ed000000 eEFFFFFF  #Un-Protected 256 sectors
	<Send>  "protect off ed000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Un-Protected"
	<Timeout>   300
	#Erase Flash
	#erase ed000000 eEFFFFFF  #Erased 256 sectors
	<Send>  "erase ed000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Erased"
	#Copy from memory to flash
	#cp.b 1000000 ed000000 2000000  #.done
	#<Send>  "cp.b 1000000 ed000000 2000000"
	<Send>  "cp.b 1000000 ed000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "done"
	<Checkdatax> 'error'
	#dump0x40 of flash location
	#md.b ed000000 40
	<Send>  "md.b ed000000 40"
	<Wait>
	<GetData>
	<Timeout>   30
	#CRC check Flash Space
	#crc32 ed000000 2000000  #CRC32 for ed000000 ... eeffffff ==> 35a4f775
	<Send>  "crc32 ed000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "CRC32 for ed000000.*52e9348"
	#Apply flash protection
	#protect on ed000000 eEFFFFFF  #Protected 256 sectors
	<Send>  "protect on ed000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Protected"
</bypass>


<Msg>   "Check Bootloader2 Secondary Version"
#=> secondary bank
<Send>  "mw.b ffdf0043 0"
<Wait>
<Send>  "md.b ffdf0043 1"
<Wait>
<GetData>
#Secondary Flash
<CheckData> "ffdf0043: 00"
#Compare  CRC of code im memory to code in Flash
<Send>	"crc32 01000000 $filesize"
<Wait>
<GetData> Check_CRC32
<CheckData>  "CRC32 for 01000000.*52e9348"
#<Send>  "crc32 ed000000 $filesize"
#<Wait>
#<GetData> Check_CRC32
#<CheckData>  "CRC32 for ed000000.*52e9348"
<Send>	"cmp.b 01000000 ed000000 $filesize"
<Wait>
<GetData> Check_bytecompare
# $compare_gbl
<bypass> $compare_gbl
	<Msg>	"Program Secondary Bootloader2(5min)..."
	#Remove Flash protection
	#protect off ed000000 eEFFFFFF  #Un-Protected 256 sectors
	<Send>  "protect off ed000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Un-Protected"
	<Timeout>   300
	#Erase Flash
	#erase ed000000 eEFFFFFF  #Erased 256 sectors
	<Send>  "erase ed000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Erased"
	#Copy from memory to flash
	#cp.b 1000000 ed000000 2000000  #.done
	#<Send>  "cp.b 1000000 ed000000 2000000"
	<Send>  "cp.b 1000000 ed000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "done"
	<Checkdatax> 'error'
	#dump0x40 of flash location
	#md.b ed000000 40
	<Send>  "md.b ed000000 40"
	<Wait>
	<GetData>
	<Timeout>   30
	#CRC check Flash Space
	#crc32 ed000000 2000000  #CRC32 for ed000000 ... eeffffff ==> cc277033
	<Send>  "crc32 ed000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "CRC32 for ed000000.*52e9348"
	#Apply flash protection
	#protect on ed000000 eEFFFFFF  #Protected 256 sectors
	<Send>  "protect on ed000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Protected"
</bypass>
# Change back to => primary bank
<Send>  "mw.b ffdf0043 1"
<Wait>
<Send>  "md.b ffdf0043 1"
<Wait>
<GetData>
#Secondary Flash
<CheckData> "ffdf0043: 01"
##

################  bootloader2 ######################

###############   ef000000 - ucode ######################
<Timeout>	30
<Msg>	"Check ucode Primary Version"
<Send>	"md.b ffdf0043 1"
<Wait>
<GetData>
#Primary Flash Default power on
<CheckData> "ffdf0043: 01"

# Clear DRAM memory
<Send>	"mw.l 1000000 ffffffff 1000000"
<Wait>
<GetData>
<CheckDatax>  "error"
#TFTP File for DRAM
#tftp 1000000 OS_J/ucode.bin   #Bytes transferred = 7260 (1c5c hex)
<Msg>	"TFTP ucode Image"
#<Send>	"tftp 1000000 OS_J/ucode.bin"
<Sendchr>	"tftp 1000000 "
<sendchr>	$tftp_copypath_release_gbl
<send>		"ucode.bin"
<Wait>
<GetData> Check_tftp_size
<CheckData>  "Bytes transferred = 7260"
#Compare  CRC of code im memory to code in Flash
<Send>	"crc32 01000000 $filesize"
<Wait>
<GetData> Check_CRC32
<CheckData>  "CRC32 for 01000000.*6e7f9197"
#<Send>  "crc32 eF000000 $filesize"
#<Wait>
#<GetData> Check_CRC32
#<CheckData>  "CRC32 for eF000000.*6e7f9197"
<Send>	"cmp.b 01000000 ef000000 $filesize"
<Wait>
<GetData> Check_bytecompare
# $compare_gbl
<bypass> $compare_gbl
	<Msg>	"Program Primary ucode(1min)..."
	#Remove Flash protection
	#protect off ef000000 eFF7FFFF  #Un-Protected 124 sectors
	<Send>  "protect off eF000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Un-Protected"
	<Timeout>   180
	#Erase Flash
	#erase ef000000 eFF7FFFF  #Erased 124 sectors
	<Send>  "erase ef000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Erased"
	#Copy from memory to flash
	#cp.b 1000000 ef000000 F80000  #.done
	#<Send>  "cp.b 1000000 ef000000 F80000"
	<Send>  "cp.b 1000000 ef000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "done"
	<Checkdatax> 'error'
	#dump0x40 of flash location
	#md.b ef000000 40
	<Send>  "md.b ef000000 40"
	<Wait>
	<GetData>
	<Timeout>   30
	#CRC check Flash Space
	#crc32 eF000000 F80000  #CRC32 for 01000000 ... 01f7ffff ==> 6e7f9197
	<Send>  "crc32 eF000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "CRC32 for ef000000.*6e7f9197"
	#Apply flash protection
	#protect on ef000000 eFF7FFFF  #Protected 124 sectors
	<Send>  "protect on ef000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Protected"
</bypass>


<Msg>   "Check ucode Secondary Version"
#=> secondary bank
<Send>  "mw.b ffdf0043 0"
<Wait>
<Send>  "md.b ffdf0043 1"
<Wait>
<GetData>
#Secondary Flash
<CheckData> "ffdf0043: 00"
#Compare  CRC of code im memory to code in Flash
<Send>	"crc32 01000000 $filesize"
<Wait>
<GetData> Check_CRC32
<CheckData>  "CRC32 for 01000000.*6e7f9197"
#<Send>  "crc32 eF000000 $filesize"
#<Wait>
#<GetData> Check_CRC32
#<CheckData>  "CRC32 for eF000000.*6e7f9197"
<Send>	"cmp.b 01000000 ef000000 $filesize"
<Wait>
<GetData> Check_bytecompare
# $compare_gbl
<bypass> $compare_gbl
	<Msg>	"Program Secondary ucode(1min)..."
	#Remove Flash protection
	#protect off ef000000 eFF7FFFF  #Un-Protected 124 sectors
	<Send>  "protect off eF000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Un-Protected"
	<Timeout>   180
	#Erase Flash
	#erase ef000000 eFF7FFFF  #Erased 124 sectors
	<Send>  "erase ef000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Erased"
	#Copy from memory to flash
	#cp.b 1000000 ef000000 F80000  #.done
	#<Send>  "cp.b 1000000 ef000000 F80000"
	<Send>  "cp.b 1000000 ef000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "done"
	<Checkdatax> 'error'
	#dump0x40 of flash location
	#md.b ef000000 40
	<Send>  "md.b ef000000 40"
	<Wait>
	<GetData>
	<Timeout>   30
	#CRC check Flash Space
	#crc32 eF000000 F80000  #CRC32 for 01000000 ... 01f7ffff ==> 6e7f9197
	<Send>  "crc32 eF000000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "CRC32 for ef000000.*6e7f9197"
	#Apply flash protection
	#protect on ef000000 eFF7FFFF  #Protected 124 sectors
	<Send>  "protect on ef000000 +$filesize"
	<Wait>
	<GetData>
	<CheckData>  "Protected"
</bypass>
# Change back to => primary bank
<Send>  "mw.b ffdf0043 1"
<Wait>
<Send>  "md.b ffdf0043 1"
<Wait>
<GetData>
#Secondary Flash
<CheckData> "ffdf0043: 01"
##

################  ucode ######################


###############   eff80000   => u-boot/stokeboot version ######################
<Timeout>	30
<Msg>	"Check Stokboot Primary Version"
<Send>	"md.b ffdf0043 1"
<Wait>
<GetData>
#Primary Flash Default power on
<CheckData> "ffdf0043: 01"

# Clear DRAM memory
<Send>	"mw.l 1000000 ffffffff 1000000"
<Wait>
<GetData>
<CheckDatax>  "error"
#TFTP File for DRAM
#tftp 1000000 OS_J/stokebootxglc.bin   #Bytes transferred = 524288 (80000 hex)
<Msg>	"TFTP Stokeboot Image"
#<Send>	"tftp OS_J/stokebootxglc.bin"
<Sendchr>	"tftp 1000000 "
<sendchr>	$tftp_copypath_release_gbl
<send>		"stokebootxglc.bin"
<Wait>
<GetData> Check_tftp_size
<CheckData>  "Bytes transferred = 524288"
#Compare  CRC of code im memory to code in Flash
<Send>	"crc32 01000000 80000"
<Wait>
<GetData> Check_CRC32
<CheckData>  "CRC32 for 01000000.*fb67795a"
#<Send>  "crc32 eff80000 80000"
#<Wait>
#<GetData> Check_CRC32
#<CheckData>  "CRC32 for eff80000.*fb67795a"
<Send>	"cmp.b 01000000 eff80000 $filesize"
<Wait>
<GetData> Check_bytecompare
# $compare_gbl
<bypass> $compare_gbl
	<Msg>	"Program Primary Stokeboot(1min)..."
	#Remove Flash protection
	#protect off eff80000 efffffff  #Un-Protected 4 sectors
	<Send>  "protect off eff80000 efffffff"
	<Wait>
	<GetData>
	<CheckData>  "Un-Protected 4 sectors"
	<Timeout>   60
	#Erase Flash
	#erase eff80000 efffffff  #Erased 4 sectors
	<Send>  "erase eff80000 efffffff"
	<Wait>
	<GetData>
	<CheckData>  "Erased 4 sectors"
	#Copy from memory to flash
	#cp.b 1000000 eff80000 80000  #.done
	<Send>  "cp.b 1000000 eff80000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "done"
	<Checkdatax> 'error'
	#dump0x40 of flash location
	#md.b eff80000 40
	<Send>  "md.b eff80000 40"
	<Wait>
	<GetData>
	<Timeout>   30
	#CRC check Flash Space
	#crc32 eff80000 80000  #CRC32 for eff80000 ... efffffff ==> fb67795a
	<Send>  "crc32 eff80000 80000"
	<Wait>
	<GetData>
	<CheckData>  "CRC32 for eff80000.*fb67795a"
	#Apply flash protection
	#protect on eff80000 efffffff  #Protected 4 sectors
	<Send>  "protect on eff80000 efffffff"
	<Wait>
	<GetData>
	<CheckData>  "Protected 4 sectors"
</bypass>


<Msg>   "Check Stokboot Secondary Version"
#=> secondary bank
<Send>  "mw.b ffdf0043 0"
<Wait>
<Send>  "md.b ffdf0043 1"
<Wait>
<GetData>
#Secondary Flash
<CheckData> "ffdf0043: 00"
#Compare  CRC of code im memory to code in Flash
<Send>	"crc32 01000000 80000"
<Wait>
<GetData> Check_CRC32
<CheckData>  "CRC32 for 01000000.*fb67795a"
#<Send>  "crc32 eff80000 80000"
#<Wait>
#<GetData> Check_CRC32
#<CheckData>  "CRC32 for eff80000.*fb67795a"
<Send>	"cmp.b 01000000 eff80000 $filesize"
<Wait>
<GetData> Check_bytecompare
# $compare_gbl
<bypass> $compare_gbl
	<Msg>	"Program Secondary Stokeboot(1min)..."
	#Remove Flash protection
	#protect off eff80000 efffffff  #Un-Protected 4 sectors
	<Send>  "protect off eff80000 efffffff"
	<Wait>
	<GetData>
	<CheckData>  "Un-Protected 4 sectors"
	<Timeout>   60
	#Erase Flash
	#erase eff80000 efffffff  #Erased 4 sectors
	<Send>  "erase eff80000 efffffff"
	<Wait>
	<GetData>
	<CheckData>  "Erased 4 sectors"
	#Copy from memory to flash
	#cp.b 1000000 eff80000 80000  #.done
	<Send>  "cp.b 1000000 eff80000 $filesize"
	<Wait>
	<GetData>
	<CheckData>  "done"
	<Checkdatax> 'error'
	#dump0x40 of flash location
	#md.b eff80000 40
	<Send>  "md.b eff80000 40"
	<Wait>
	<GetData>
	<Timeout>   30
	#CRC check Flash Space
	#crc32 eff80000 80000  #CRC32 for eff80000 ... efffffff ==> fb67795a
	<Send>  "crc32 eff80000 80000"
	<Wait>
	<GetData>
	<CheckData>  "CRC32 for eff80000.*fb67795a"
	#Apply flash protection
	#protect on eff80000 efffffff  #Protected 4 sectors
	<Send>  "protect on eff80000 efffffff"
	<Wait>
	<GetData>
	<CheckData>  "Protected 4 sectors"
</bypass>
# Change back to => primary bank
<Send>  "mw.b ffdf0043 1"
<Wait>
<Send>  "md.b ffdf0043 1"
<Wait>
<GetData>
#Secondary Flash
<CheckData> "ffdf0043: 01"
##

################  uboot/stokeboot ######################

