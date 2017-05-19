################################################################################
#
# Module:      Bench_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Main Execution for XGLC test
#
# Version:    1.6 $Id: Bench_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
#
#
# Changes:    Created from Bench_GLC.dat 092711
#			  Added  a margin nominal before going from margin high to low
#			  1.3 minor changes for 5/30 diags
#			  Added Time to diag startup 70-90 sec
#			  Added Background GPP DRAM test
#			  Added more areas of GPP to be tested
#			  Added ECC checks of GPP Dram 9/20/12
#			  Added setup for 1gig sfps enable in Init_Stoke.ini 10/9/12
#			  Moved Fail on error after power supply falgs are cleared 10/23/12
#			  Added Support for 1gig, copper, LR using chassis routines. 10/30/13
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################
#Bench_XGLC.inc
<ETTC>		1800
<Msg>		"Test XGLC"
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

<TimeOut>	10

<Send>		"cpld show"
<Wait>
<GetData>	Check_XGLC_CPLD

<Include>   Check_Voltage_XGLC.inc

<Msg>		"Test memory"
<Timeout>	180
<Send>      "mtest 1000000 10000000 a3d633adba453e8f332a7de39fdae7c66b634f89f116c9a3 1"
<Wait>
<getdata>
<checkdata>  'Tested . iteration... with 0 errors'
<checkdatax>   "FAILURE"

<Include>   i2c_scan_xglc.inc

<TimeOut>	3
<Msg>		"Check Thermal sensors..."
<Send>		"monitor temp"
<Wait>
<GetData>	Check_XGLC_Thermal

#<Msg>       "No Stop On Fail"
# <Msg>    "Check Fail Flags:"
# <Msg>     $Exit_On_Error
# <Msg>     $Exit_On_Timeout

# <Msg>      "Set Stop On Error"

#<Set>       $Exit_On_Error
#<Set>       $Exit_On_Timeout

# <Msg>    "Check Fail Flags:"
# <Msg>     $Exit_On_Error
# <Msg>    $Exit_On_Timeout

<Prompt>	"#"
<timeout>	90
<Msg>		"Start Diags"
#<Send>      "run diag"
<Send>      "cp.b e9000000 40000000 2000000; bootifs 40000000"
<Wait>
<getdata> Check_XGLC_Diag
#<checkdata>  'io-pkt-v4. terminated SIGSEGV'
#<checkdata>  'Disabling local fault on port 1'
#<checkdata>  'Disabling local fault on port 2'
#<checkdata>  'Disabling local fault on port 3'
#<checkdata>  'Disabling local fault on port 4'

<checkdatax>  'fail'
<checkdatax>   "error"
<checkdatax>   "fault"
<checkdatax>   "terminated"
<checkdatax>   "Unable to access"
<checkdatax>	"nvwatchdog"
#Check_XGLC_Diag

<Sleep>		10
#SOCK=/nv xglcdiag
#DIAG>

<Prompt>	"DIAG >"
<timeout>	90
<Msg>		"Start Diags"
<Send>      "SOCK=/nv xglcdiag"
<Wait>
<getdata>
<checkdatax>  'fail'
<checkdatax>   "error"
#Check_XGLC_Diag

<Msg>       "Checking DC voltages ..."
<Send>      "monitor voltage all"
<Wait>
<GetData>   Check_XGLC_voltage

<Sleep>		10

<Msg>		"Check CPLD...."
<Send>		"cpldshow"
<Wait>
#<GetData>	"Check_XGLC_CPLD_Diag"

<Include>   Check_XGLC_thermal.inc

<Msg>       "Check if booted on Primary Flash..."
<TimeOut>   2
<Send>      "cpldacc rd 2B 1"
## 0x20 Fail Count 1 , bank 0
##<WaitFor>  "F400002B   20"  # Failing in 11/15/07 image from don and layne
<Wait>
<CheckData> "Addr .2b. = 04"
<GetData>
<Send>      "cpldacc rd 43 1"
<Wait>
<CheckData> "Addr .43. = 01"
<GetData>
<MSG>		"Boot from Secondary Flash"
#p4080_util cpld read hexadr
#p4080_util cpld write hexadr hexdata
#cpldacc:
    #Syntax: cpldacc <rd> <addr> <count>
            #cpldacc <wr> <addr> <data>
<TimeOut>   5
<Msg>       "Bootup from Secondary flash..."
#<Send>      "cpldacc wr 2B 02"   #  wr ffdf002B
#<Wait>
#<Send>      "Reset board"

<Prompt>	"#"
<Send>		"quit"
<Wait>
#<send>		 "/stoke/bin/util/reload"
<send>		 "nvctl -R"
#<Wait>
<TimeOut>   30

<Include>	Stop_stoke_boot.inc
<Msg>		"Test XGLC"
<Msg>		"Verify at Stoke>.."
<TimeOut>	5
<Send>		""
<WaitFor>	"Stoke>"


<Msg>       "Disable XLP1 overtemp reset"
##52 npu1_reset_control      DEfault is 0x40
#<send>          "xglcdiag cpldacc wr 52 48"
#<wait>
#<GetData>
##52 npu1_reset_control      DEfault is 0x40
#<send>          "xglcdiag cpldacc rd 52"
#<wait>
#<GetData>

<send>          "mw.b ffdf001d 1 ; i2c dev 0 ; i2c mw 70 0 1 1; i2c probe"
<wait>
<GetData>
# RLHN 05h 0101 0101 +85°C Read local (internal) ALERT high limit
<send>          "i2c md 4D 5 1"
<wait>
<GetData>
#WLHO 0Bh N/A — Write local (internal) ALERT high limit
<send>          "i2c mw 4D 0B FF"
<wait>
<GetData>
<send>          "i2c md 4D 5 1"
<wait>
<GetData>

#RRHI 07h 0101 1111 +95°C Read remote (external) ALERT high limit (MAX6646/MAX6647)
<send>          "i2c md 4D 7 1"
<wait>
<GetData>
#WRHA 0Dh N/A — Write remote (external) ALERT high limit
<send>          "i2c mw 4D 0D FF"
<wait>
<GetData>
<send>          "i2c md 4D 7 1"
<wait>
<GetData>

#RWOE 19h 0111 1101 +125°C Read/write remote (external) OVERT limit (MAX6646/MAX6647) Found 0019: 50    P
<send>          "i2c md 4D 19 1"
<wait>
<GetData>
<send>          "i2c mw 4D 19 FF"
<wait>
<GetData>
<send>          "i2c md 4D 19 1"
<wait>
<GetData>
#RWOI 20h 0101 0101 +85°C Read/write local (internal) OVERT limit, Found 0020: 55    U
<send>          "i2c md 4D 20 1"
<wait>
<GetData>
<send>          "i2c mw 4D 20 FF"
<wait>
<GetData>
<send>          "i2c md 4D 20 1"
<wait>
<GetData>



<Prompt>	"#"
<timeout>	90
<Msg>		"Start Diags"
#<Send>      "run diag"
<Send>      "cp.b e9000000 40000000 2000000; bootifs 40000000"
<Wait>
<getdata> Check_XGLC_Diag
<checkdatax>  'fail'
<checkdatax>   "error"
#Check_XGLC_Diag

<Sleep>		10
#SOCK=/nv xglcdiag
#DIAG>

#<Msg>   "Enable SFP I2C, Temporary until Diags enables"

#<Send>      "i2c_util -w bus=3,dev=0x74,off=2,rsize=1,len=2,data=0"
#<Wait>
#<Send>      "i2c_util -r bus=3,dev=0x74,off=2,rsize=1,len=2"
#<Wait>
#<Send>      "i2c_util -w bus=3,dev=0x74,off=3,rsize=1,len=1,data=0"
#<Wait>
#<Send>      "i2c_util -r bus=3,dev=0x74,off=2,rsize=1,len=2"
#<Wait>


<Msg>		"Run CPU Dram test in Background..."

<Send>		"time on -p6r xglcmemtest -o 0x100000000 -s 128M -b > /tmp/memory0 &"
<Wait>
<GetData>
<Send>		"time on -p6r xglcmemtest -o 0x140000000 -s 128M -b > /tmp/memory1 &"
<Wait>
<GetData>
<Send>		"time on -p6r xglcmemtest -o 0x180000000 -s 128M -b > /tmp/memory2 &"
<Wait>
<GetData>
<Send>		"time on -p6r xglcmemtest -o 0x1C0000000 -s 128M -b > /tmp/memory3 &"
<Wait>
<GetData>
<Send>		"time on -p6r xglcmemtest -o 0x200000000 -s 128M -b > /tmp/memory4 &"
<Wait>
<GetData>
<Send>		"time on -p6r xglcmemtest -o 0x240000000 -s 128M -b > /tmp/memory5 &"
<Wait>
<GetData>
<Send>		"time on -p6r xglcmemtest -o 0x280000000 -s 128M -b > /tmp/memory6 &"
<Wait>
<GetData>
<Send>		"time on -p6r xglcmemtest -o 0x2C0000000 -s 128M -b > /tmp/memory7 &"
<Wait>
<GetData>
<Send>      "time on -p6r xglcmemtest -o 0x40000000 -s 128M -b > /tmp/memory8 &"
<Wait>
<GetData>
<Send>      "time on -p6r xglcmemtest -o 0x80000000 -s 128M -b > /tmp/memory9 &"
<Wait>
<GetData>


<Prompt>	"DIAG >"
<timeout>	90


<Msg>		"Start Diags2"
#Send>      "SOCK=/nv xglcdiag"
<Send>      "xglcdiag"
<Wait>
<getdata>
<checkdatax>  'fail'
<checkdatax>   "error"
#Check_XGLC_Diag
<Msg>       "Check if booted on Secondary Flash..."
<TimeOut>   2
<Send>      "cpldacc rd 2B 1"
## 0x20 Fail Count 1 , bank 0
##<WaitFor>  "F400002B   20"  # Failing in 11/15/07 image from don and layne
<Wait>
<CheckData> "Addr .2b. = 20"
<GetData>
<Send>      "cpldacc rd 43 1"
<Wait>
<CheckData> "Addr .43. = 00"
<GetData>

<timeout>	90

#<Msg>       "Run CPU 1 Core DRAM test..."
#<Send>      "sp mem ddrtest cpu=1 size=10000"
#<Wait>
#<Send>      "sp glob runcount=1"
#<Wait>
#<Send>      "run mem ddrtest"
#<Wait>
#<GetData>

#<Msg>       "Run CPU 8 Core DRAM test..."
#<Send>      "sp mem ddrtest cpu=8 size=10000"
#<Wait>
#<Send>      "sp glob runcount=1"
#<Wait>
#<Send>      "run mem ddrtest"
#<Wait>
#<GetData>
<Prompt>	"#"
<Send>		"exit"
<wait>
<Include>	SFP_POWER_Read.inc
<Include>	Check_1gig_SFP.inc
<Prompt>	"DIAG >"
<timeout>	90


<Msg>		"Start Diags3"
#Send>      "SOCK=/nv xglcdiag"
<Send>      "xglcdiag"
<Wait>
<getdata>
<checkdatax>  'fail'
<checkdatax>   "error"
#<bypass>    $XGLC_1gigSFP_gbl
#<Msg>   "Setup for 1gig SFPs"
#    <send>  "tdnt port xe0 speed=1000"
#    <wait>
#    <send>  "tdnt port xe1 speed=1000"
#    <wait>
#    <send>  "tdnt port xe2 speed=1000"
#    <wait>
#    <send>  "tdnt port xe3 speed=1000"
#    <wait>
#</bypass>
#show xglcsys local10ge
<Msg>       "Get Default xglcsys settings..."
<Send>      "show xglcsys local10ge"
<Wait>
<GetData>
<Msg>       "Run 4 Port test 60 Seconds..."
#Enable Active LED
<Send>      "cpldacc wr 66 f"
<Wait>
<Send>      "sp xglcsys local10ge portmask=0-4"
<Wait>
<GetData>
<timeout>   90
<sleep>     5
<Send>      "run xglcsys local10ge"
<Wait>
<GetData>
<Checkdata>  "Test Completed Successfully"
#Disable Active LED
<Send>      "cpldacc wr 66 0"
<Wait>
<Msg>		"Check Trident Links"
<Send>		"tdnt ps"
<Wait>
<Getdata>	Check_XGLC_Bench_Links
<Sleep>		10

<Msg>       "Checking DC voltages ..."
<Send>      "monitor voltage all"
<Wait>
<GetData>   Check_XGLC_voltage



<Include>   Bench_XGLC_Diag_test.inc

<Msg>       "Checking DC voltages ..."
<Send>      "monitor voltage all"
<Wait>
<GetData>   Check_XGLC_voltage

<Timeout>   10
<Msg>       "Margin Voltages High ..."
<Send>      "monitor margin all high"
<Wait>
<GetData>
<Msg>        "monitor margin group_f nominal"
<Send>      "monitor margin group_f nominal"
<Wait>
<GetData>

<Include>	Bench_XGLC_Diag_test.inc

<Msg>       "Checking DC Margin High voltages ..."
<Send>      "monitor voltage all"
<Wait>
<GetData>   Check_XGLC_voltage_Margin_high

<Send>      "monitor margin all nominal"
<Wait>
<GetData>


<Msg>       "Checking DC Margin nominal voltages ..."
<Send>      "monitor voltage all"
<Wait>
<GetData>   Check_XGLC_voltage

<Timeout>   10
<Msg>       "Margin Voltages low ..."
<Send>      "monitor margin all low"
<Wait>
<Msg>        "monitor margin group_f nominal"
<Send>      "monitor margin group_f nominal"
<Wait>
<GetData>
<GetData>

#<Send>      "monitor margin group_a low"
#<Wait>
#<GetData>

#<Send>      "monitor margin group_b low"
#<Wait>
#<GetData>

#<Send>      "monitor margin group_c low"
#<Wait>
#<GetData>

#<Send>      "monitor margin group_d low"
#<Wait>
#<GetData>

#<Send>      "monitor margin group_e low"
#<Wait>
#<GetData>

##<Send>      "monitor margin group_f low"
##<Wait>
##<GetData>

#<Send>      "monitor margin group_npu low"
#<Wait>
#<GetData>

#<Send>      "monitor margin group_cam low"
#<Wait>
#<GetData>



<Include>	Bench_XGLC_Diag_test.inc

<Msg>       "Checking DC Margin low voltages ..."
<Send>      "monitor voltage all"
<Wait>
<GetData>   Check_XGLC_voltage_Margin_low

<Send>      "monitor margin all nominal"
<Wait>
<GetData>

#<Include>	Bench_XGLC_Diag_test.inc

<Msg>       "Checking DC Margin nominal voltages ..."
<Send>      "monitor voltage all"
<Wait>
<GetData>   Check_XGLC_voltage

#Exit diags
<prompt>	"#"
<send>		"exit"
<wait>
<timeout>	120
<Msg>	Waiting for memory tests to complete
<Send>	"wait"
<wait>
<getdata>
#<Send>  "grep -ie \"error\" -e \"fail\" -e \"parity\"  /tmp/memory*"
#<wait>
<prompt>	">"
<Send>	"	if (grep -ie \"error\" -e \"fail\" -e \"parity\"  /tmp/memory*) then"
<wait>
<Send>	"	   echo \"GPP memory:Failed\""
<wait>
<Send>	"	else"
<wait>
<Send>	"        echo \"GPP Memory:PASS\""
<wait>
<prompt>	"#"
<Send>	"	fi"
<wait>
<CheckData> Memory:PASS
<GetData>
<Send>	"		cat /tmp/memory*"
<wait>
<GetData>

<Msg>	        "Check GPP_ECC..."
<send>	"set -A cpumem_ecc 8e40 9e40 8e4c 8e50 9e4c 9e50"
<wait>
<send>	"integer y=0"
<wait>
<Prompt>	">"
<send>	" while [ $y -lt 6 ]"
<wait>
<send>	"		do"
<wait>
<send>	"	on -p6r xglcdiag ccsracc rd ${cpumem_ecc[$y]} 1  > /tmp/CPU_dram_ECC_${cpumem_ecc[$y]}.tmp"
<wait>
<send>	"       	if ( grep -q "Addr.* = 0" /tmp/CPU_dram_ECC_${cpumem_ecc[$y]}.tmp ) then"
<wait>
<send>	"            	echo "CPU_dram_ECC${cpumem_ecc_[$y]}:passed:$fail: `date`" "
<wait>
<send>	"        	else"
<wait>
<send>	"            	echo "CPU_dram_ECC${cpumem_ecc_[$y]}:Failed:$fail: `date`" "
<wait>
<send>	"		cat  /tmp/CPU_dram_ECC_${cpumem_ecc[$y]}.tmp	 "
<wait>
<send>	"        fi"
<wait>
<send>	"	(( y=y+1 ))"
<wait>
<Prompt>	"#"
<send>	"done"
<wait>
<GetData>
<CheckData>	"CPU_dram_ECC.*:passed:"
<CheckDatax>	"Failed"
#               CPU_dram_ECC:Failed

