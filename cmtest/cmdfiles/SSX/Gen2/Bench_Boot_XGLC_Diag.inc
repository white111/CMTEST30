################################################################################
#
# Module:      Bench_Prog_XGLC_Flash.inc
#
# Author:      Joe White
#
# Descr:       Program XGLC Flash using Ethernet Debug plugin
#
# Version:    1.1 $Id: Bench_Boot_XGLC_Diag.inc,v 1.1 2012/02/17 17:13:41 joe Exp $
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
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
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
<GetData>	Check_tftp_Ping






<bypass> $Check_tftp_Ping_gbl
	<Msg>	"Boot Flash"
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
#tftp 1000000 diag_B/xglcflashdiag.bin   #Bytes transferred = 18765248 (11ace48 hex)
	<Msg>	"TFTP Diag Image"
	<Send>	"tftp 1000000 diag_B/xglcflashdiag.bin"
	<Wait>
	<GetData> Check_tftp_size
	<CheckData>  "Bytes transferred = 18867260"
	#Compare  CRC of code im memory to code in Flash
	#<Send>	"crc32 01000000 4000000"
	<Send>	"crc32 01000000 $filesize"
	<Wait>
	<GetData> Check_CRC32
	<CheckData>  "CRC32 for 01000000.*f70734ff"
	#<Send>	"crc32 e9000000 4000000"
	#<Send>	"crc32 e9000000 $filesize"
	#<Wait>
	#<GetData> Check_CRC32
	##<CheckData>  "CRC32 for e9000000.*f70734ff"
	<Send>	"cmp.b 01000000 e9000000 $filesize"
	<Wait>
	<GetData> Check_bytecompare
# $compare_gbl

	<Msg>	"Bench Boot XGLC Diag..."
	#Remove Flash protection
	#protect off e9000000 ecffffff  #Un-Protected 512 sectors
	<Send>  "go 01000000"
	<Wait>
	<GetData>

</bypass>




