################################################################################
#
# Module:      Bench_XGLC_Diag_test.inc
#
# Author:      Joe White
#
# Descr:       Main Execution for XGLC diag tests
#
# Version:    1.3 $Id: Bench_XGLC_Diag_test.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
#
#
# Changes:    Created from Bench_GLC.dat 11/28/11
#			  1.2 Minor changes for 5/30 diags
#			  Move GPP memory test separate from diag runal and use memtest
#			  Change XLP memory test to 60M 8/2/12
#			  Added ECC Check 9/20/12  Add tdnt clear
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################

<Prompt>	"DIAG >"
<Timeout>	10
#<Msg>       "Checking DC voltages ..."
#<Send>      "monitor voltage all"
#<Wait>
#<GetData>   Check_XGLC_voltage

<Sleep>		10

<Msg>		"Show CPLD...."
<Send>		"cpldshow"
<Wait>
#<GetData>	Check_XGLC_CPLD_Diag
<GetData>

<Include>   Check_XGLC_thermal.inc

<Msg>		"Exit Diag"
<Prompt>	"#"
<Send>		"exit"
<Wait>

<Timeout>   30

<msg>       "Testing XLP0 Alive"
<send>          "imcxglctest -t 0 diagtest checkalive"
<wait>
<GetData>
<CheckData>  "XLP is alive"
<Timeout>   75
<msg>       "Testing XLP0 DDR 1 core 16M each"
<send>          "imcxglctest -t 0 diagtest memtest -b -l 16M 1"
<wait>
<GetData>
<CheckData>  "Memory test Passed"

<Timeout>   2000
<msg>       "Testing XLP0 DDR 32 core 60M each"
<send>          "time imcxglctest -t 0 diagtest memtest -b -l -t 32 60M 10"
<wait>
<GetData>
<CheckData>  "Memory test Passed"

<Timeout>   65
<msg>       "Testing XLP0 KBP Register"
<send>          "imcxglctest -t 0 diagtest kbpdiag -regtest"
<wait>
<GetData>
<CheckData>  "KBP Register test Passed"

<msg>       "Testing XLP0 KBP PWR"
<send>          "imcxglctest -t 0 diagtest kbpdiag -pwrtest"
<wait>
<GetData>
<CheckData>  "KBP Power test Passed"

<Timeout>   30
<msg>       "Testing XLP1 Alive"
<send>          "imcxglctest -t 1 diagtest checkalive"
<wait>
<GetData>
<CheckData>  "XLP is alive"

#<Msg>       "Disable XLP1 overtemp reset"
##52 npu1_reset_control      DEfault is 0x40
#<send>          "xglcdiag cpldacc wr 52 48"
#<wait>
#<GetData>
##52 npu1_reset_control      DEfault is 0x40
#<send>          "xglcdiag cpldacc rd 52"
#<wait>
#<GetData>

<Timeout>   75
<msg>       "Testing XLP1 DDR 1 core 16M each"
<send>          "imcxglctest -t 1 diagtest memtest -b -l 16M 1"
<wait>
<GetData>
<CheckData>  "Memory test Passed"

<Timeout>   2000
<msg>       "Testing XLP1 DDR 32 core 60M each"
<send>          "imcxglctest -t 1 diagtest memtest -b -l -t 32 60M 10"
<wait>
<GetData>
<CheckData>  "Memory test Passed"

#<Msg>       "Enable XLP1 overtemp reset"
##52 npu1_reset_control      DEfault is 0x40
#<send>          "xglcdiag cpldacc wr 52 40"
#<wait>
#<GetData>

<Timeout>   65
<msg>       "Testing XLP1 KBP Register"
<send>          "imcxglctest -t 1 diagtest kbpdiag -regtest"
<wait>
<GetData>
<CheckData>  "KBP Register test Passed"

<msg>       "Testing XLP1 KBP PWR"
<send>          "imcxglctest -t 1 diagtest kbpdiag -pwrtest"
<wait>
<GetData>
<CheckData>  "KBP Power test Passed"


#<prompt>        "login"
#<send>      "SOCK=/nv telnet 192.168.204.202"
#<wait>
#<Prompt>    #
#<send>      "root"
#<wait>
#<timeout>   60
#<Timeout>   180
#<msg>       "Testing XLP1 DDR 32 cores 1M each"
##<send>         "time memtest -b -t 32 1M 1 > /tmp/XLP1_1M.txt"
#<send>          "memtest  1M 1 > /tmp/XLP1_1M.txt"
#<wait>
#<GetData>
#<Send>
#<Wait>
#<Sendslow>      "if (grep -in -e "fail" -e "error" /tmp/XLP1_1M.txt) then ( cat /tmp/XLP1_1M.txt; echo "XLP1_DRAM_FAILED:$?") else (echo "XLP1_DRAM_PASSED:$?")  fi"
#<Wait>
#<GetData>
#<CheckData>     "XLP1_DRAM_PASSED"
#<Sendslow>      "if (grep -in -e "Memory test Passed" /tmp/XLP1_1M.txt) then (  echo "XLP1_DRAM_PASSED:$?") else (cat /tmp/XLP1_1M.txt; echo "XLP1_DRAM_FAILED:$?")  fi"
#<Wait>
#<GetData>
#<CheckData>     "XLP1_DRAM_PASSED"

#<Timeout>   240
#<msg>       "Testing XLP1 DDR 1 core 64M each"
#<send>          "memtest 16M 1 > /tmp/XLP1_64M.txt"
#<wait>
#<GetData>
#<Sendslow>      "if (grep -in -e "fail" -e "error" /tmp/XLP1_64M.txt) then ( cat /tmp/XLP1_64M.txt; echo "XLP1_DRAM_FAILED:$?") else (echo "XLP1_DRAM_PASSED:$?")  fi"
#<Wait>
#<GetData>
#<CheckData>     "XLP1_DRAM_PASSED"
#<Sendslow>      "if (grep -in -e "Memory test Passed" /tmp/XLP1_64M.txt ) then ( echo "XLP1_DRAM_PASSED:$?") else (cat /tmp/XLP0_64M.txt; echo "XLP1_DRAM_FAILED:$?")  fi"
#<Wait>
#<GetData>
#<CheckData>     "XLP1_DRAM_PASSED"

##<Timeout>   180
##<msg>       "Testing XLP1 DDR 1 core 256M each.. 14Min ..."
##<send>          "memtest -t 1 256M 1 > /tmp/XLP1_256M.txt"
##<wait>
##<GetData>
##<Sendslow>      "if (grep -in -e "fail" -e "error" /tmp/XLP1_256M.txt) then ( cat /tmp/XLP1_256M.txt; echo "XLP1_DRAM_FAILED:$?") else (echo "XLP1_DRAM_PASSED:$?")  fi"
##<Wait>
##<GetData>
##<CheckData>     "XLP1_DRAM_PASSED"

#<msg>       "Show XLP details"
#<msg>       "Show XLP details"
#<Prompt>    "xlptest"
#<send>      "xlptest -S"
##baseaddr
#<wait>
#<GetData>
#<send>     "baseaddr"
##busnum_read
#<wait>
#<GetData>
#<send>
#<Wait>       "busnum_read"
#<Prompt>    "#"
#<Send>      "q"
#<Wait>
#<Msg>       Test XLP 1 KBP Memory
#<Send>      "kbpdiag  -memtest"
#<wait>
#<GetData>
#<GetData>       "Successful completion of Diag tests"
#<CheckDatax>    "FAIL"
#<CheckDatax>    "FAIL"
#<CheckDatax>    "Fail"
#<CheckDatax>    "Killed"
#<CheckDatax>    "Error"

##<Msg>       Test XLP 1 KBP Cmptest 1
##<Send>      "kbpdiag  -cmptest 1"
##<wait>
##<GetData>
##<GetData>       "Successful completion of Diag tests"
##<CheckDatax>    "FAIL"
##<CheckDatax>    "FAIL"
##<CheckDatax>    "Fail"
##<CheckDatax>    "Killed"
##<CheckDatax>    "Error"

##<Msg>       Test XLP 1 KBP Cmptest 2
##<Send>      "kbpdiag  -cmptest 2"
##<wait>
##<GetData>
##<GetData>       "Successful completion of Diag tests"
##<CheckDatax>    "FAIL"
##<CheckDatax>    "FAIL"
##<CheckDatax>    "Fail"
##<CheckDatax>    "Killed"
##<CheckDatax>    "Error"


##<Msg>       Test XLP 1 SAE test
##<Send>      "saetest -ca"
##<wait>
##<GetData>
##<GetData>       "Successful completion of Diag tests"
##<CheckDatax>    "FAIL"
##<CheckDatax>    "FAIL"
##<CheckDatax>    "Fail"
##<CheckDatax>    "Killed"
##<CheckDatax>    "Error"

#<Msg>       Test XLP 1 regtest test
#<Send>      "kbpdiag –regtest"
#<wait>
#<GetData>
#<GetData>       "Successful completion of Diag tests"
#<CheckDatax>    "FAIL"
#<CheckDatax>    "FAIL"
#<CheckDatax>    "Fail"
#<CheckDatax>    "Killed"
#<CheckDatax>    "Error"

#<Msg>       Test XLP 1 pwrtest test
#<Send>      "kbpdiag -pwrtest"
#<wait>
#<GetData>
#<GetData>       "Successful completion of Diag tests"
#<CheckDatax>    "FAIL"
#<CheckDatax>    "FAIL"
#<CheckDatax>    "Fail"
#<CheckDatax>    "Killed"
#<CheckDatax>    "Error"


#<Msg>       "Exit XLP1"
#<Send>      "exit"
#<wait>



#<timeout>   150
#<Msg>       "Run All Dram 2min..."
#<Send>      "time on -p6r xglcmemtest -s 0x1000000"
#<Wait>
#<GetData>
#<CheckData> "Stuck Address       : ok"
#<CheckData> "Random Value        : ok"
#<CheckData> "Compare XOR         : ok"
#<CheckData> "Compare SUB         : ok"
#<CheckData> "Compare MUL         : ok"
#<CheckData> "Compare DIV         : ok"
#<CheckData> "Compare OR          : ok"
#<CheckData> "Compare AND         : ok"
#<CheckData> "Sequential Increment: ok"
#<CheckData> "Solid Bits          : ok"
#<CheckData> "Block Sequential    : ok"
#<CheckData> "Checkerboard        : ok"
#<CheckData> "Bit Spread          : ok"
#<CheckData> "Bit Flip            : ok"
#<CheckData> "Walking Ones        : ok"


<msg>		"Enter Diags"
<Prompt>	"DIAG >"
<timeout>	30
<Msg>		"Start Diags2"
#Send>      "SOCK=/nv xglcdiag"
<Send>      "xglcdiag"
<Wait>
<getdata>
<checkdatax>  'fail'
<checkdatax>   "error"
#Check_XGLC_Diag

<Msg>		"Run All Traffic 2min..."
<timeout>	150
<Send>		"skip mem"
<Wait>
<Send>		"tdnt clear counters all"
<Wait>
#Enable Active LED
<Send>      "cpldacc wr 66 f"
<Wait>
<Send>		"run all"
<Wait>
<GetData>
<CheckData>	"Test CPLD Register Access Test Completed Successfully"
#<CheckData>	"Test P4080 Mem Test Completed Successfully"
<CheckData>	"Test SFP EEPROM Access Test Completed Successfully"
<CheckData>	"Voltage supply test PASSED"
<CheckData>	"Test Voltage Supply Test Completed Successfully"
<CheckData>	"Debug_Fault_Count test PASSED"
<CheckData>	"Debug_Max_Fault_Count test PASSED"
<CheckData>	"Debug_PON_Fail_Count test PASSED"
<CheckData>	"Debug_Lost_Volt_Count test PASSED"
<CheckData>	"Voltage Fault Monitoring test PASSED"
<CheckData>	"Test Fault Monitoring Test Completed Successfully"
<CheckData>	"Temperature Sensor test PASSED"
<CheckData>	"Test Temp Sensor Test Completed Successfully"
<CheckData>	"Test BCM56840 Register Access Test Completed Successfully"
<CheckData>	"Test P4080 ... Trident Packet Test Completed Successfully"

<CheckDatax>	"Test Failed with error"

#<Msg>       "Run 14 Port test 60 Seconds..."
#<Send>      "sp xglcsys local10ge portmask=0-14"
#<Wait>
#<GetData>
#<timeout>   90
#<sleep>     5
#<Send>      "run xglcsys local10ge"
#<Wait>
#<GetData>
#<Checkdata>  "Test Completed Successfully"
#tdnt show counters <xe0/xe1>

#Disable Active LED
<Send>      "cpldacc wr 66 0"
<Wait>
<Timeout>	10
<Msg>		"Check Trident Links"
<Send>		"tdnt ps"
<Wait>
<Getdata>	Check_XGLC_Bench_Links
# XE6-9  XLP0, XPL1

<Msg>	"Display error Counters....."

<Msg>		Show Trident nonzero counters
<Send>		"tdnt show counters NZ"
<Wait>
<GetData>

<Msg>		Show Trident Discard counters
<Send>		"tdnt show counter ErDisc"
<Wait>
<GetData>

<Msg>		Show Trident error counters
<Send>		"tdnt show error"
<Wait>
<GetData>

<Msg>		Show Trident Interupts
<Send>		"tdnt show int"
<Wait>
<GetData>

<prompt>	"#"
<send>		"exit"
<wait>
<Msg>	        "Check XLP_ECC..."
<Send>		"	on -p6r xglcdiag ccsracc rd 130008 1 > /tmp/XLP_dram_ECC.tmp "
<Wait>
<Prompt> 	">"
<Send>		"    if ( grep -q "Addr.* = c30000f0" /tmp/XLP_dram_ECC.tmp ) then"
<wait>
<Send>		"         echo "XLP_dram_ECC:passed:$fail: `date`"  "
<Wait>
<Send>		"    else "
<Wait>
<Send>		"        echo "XLP_dram_ECC:Failed:$fail: `date`" >> ${testpath}status.tmp "
<Wait>
<Send>		"        if ( grep -q "Addr.* = c3000030" /tmp/XLP_dram_ECC.tmp )  then "
<Wait>
<Send>		"           echo "XLP0_dram_ECC:Failed:$fail: `date`"  "
<Wait>
<Send>		"        else "
<Wait>
<Send>		"        	echo "XLP1_dram_ECC:Failed:$fail: `date`" "
<Wait>
<Send>		"        fi "
<Wait>
<Send>		"			cat  ${testpath}XLP_dram_ECC.tmp "
<Wait>
<Prompt>	"#"
<Send>		"    fi "
<Wait>
<GetData>
<Checkdata>		"XLP_dram_ECC:passed"
<CheckdataX>	"XLP0_dram_ECC:Failed"
<CheckDataX>	"XLP1_dram_ECC:Failed"

<Msg>		"Start Diags2"
<Prompt>	"DIAG >"
#Send>      "SOCK=/nv xglcdiag"
<Send>      "xglcdiag"
<Wait>
<getdata>
<checkdatax>  'fail'
<checkdatax>   "error"

<Send>
<Wait>


