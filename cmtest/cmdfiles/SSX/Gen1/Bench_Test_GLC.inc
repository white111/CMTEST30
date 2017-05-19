################################################################################
#
# Module:      Bench_Test_GLC.inc
#
# Author:      Joe White
#
# Descr:       Include for Bench_GLC.dat
#
# Version:    6.8 $Id: Bench_Test_GLC.inc,v 1.16 2009/05/07 15:50:09 joe Exp $
#
# Changes:    uapdated for R1 release 010306
#			  Updated for IXP2805 052506
#			  Change Xscalup msg for 2805
#			  Updated for 3.0
#			  Added Disable "noreload"
#			  010507 Updated for laynes pfeffa test tcam(bypass qtalk)
#			  fuinit changed to fuinit_diag /fu/snake_load.uof 1 0 0
#			  fuinit now run by test tcam
#			  100108 Added voltage test after Fuinit
#
#			  main: ucode file          = /fu/snake_load.uof
#			  main: start_micro_engines = 1
#	 		  main: hint_value          = 0
#			  main: init_sram_only      = 0
#			 As of 2012 Diags 2/27/12
#				<Send>		"fuinit_diag /fu/snake_load.uof 1 0 0 > /tmp/fuinit_results"  # 2009 Daigs
#				2012 diags. Ubove no longer works
#			<Send>		"pfeffa test fuinitfabsnake"
#
# Used By:
#				BenchGLC.dat
# Includes:
#			 	Bench_Test_GLC.inc
#				Check_PCI_V.inc
#
# Still ToDo:
#              - Fix Intermmittent IXP SRAM Parity Errors
#              - Fix Intermitten PCI errors
#
#
#            Copyright (c) 2006-2008 Stoke. All rights reserved.
#
################################################################################


<Msg>		"Test Disco"
<Prompt>	"> "
<Timeout>	10
<Send>		"pfeffa"
<Wait>
#Take IXF out of reset
<Send>		"w8 f4000010 1"
<Wait>
<Send>		"w8 f4000010 0"
<Wait>
#MAC soft reset control - enable all MACs
<Send>	'pfeffa  wr ixf 505 0'
<Wait>
<Send>		"test ixf access"
<Wait>
<CheckData>	"IXF1110 Access Test PASS"
<Msg>		"Test Disco DX"
<Send>		"test dx access"
<Wait>
<GetData>
#<GetData>	TESTING_PCI_ACCESS_TO_PRESTERA
<CheckData>	'TESTING PCI ACCESS TO PRESTERA 0 ...  PASS'
<CheckData>	'TESTING PCI ACCESS TO PRESTERA 1 ...  PASS'


<Msg>		"Test Disco Link 1"
<Send>		"test link disco 1 biga"
<Wait>
<Sleep>		2
<Send>		"test link disco 1 biga"
<Wait>
<Sleep>		2
<Send>		"test link disco 1 biga"
<Wait>
<Sleep>		2
<Send>		"test link disco 1 biga"
<Wait>
<Sleep>		2
<Send>		"test link disco 1 biga"
<Wait>
<GetData>
<CheckData>	"TESTING LINK DISCO 1 TO BIG-AL ... PASS"


<Msg>		"Test Disco Link 2"
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
<Sleep>		1
<GetData>
<CheckData>	"TESTING LINK DISCO 2 TO BIG-AL ... PASS"

<Msg>		"Test Disco Link 1 to Switch"
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
<GetData>
<CheckData>	"TESTING LINK DISCO 1 TO DXBASE 0 ... PASS"
<Msg>		"Test Disco Link 2 to Switch"
<Send>		"test link disco 2 sw"
<Wait>
<Sleep>		1
<Send>		"test link disco 2 sw"
<Wait>
<GetData>
<CheckData>	"TESTING LINK DISCO 2 TO DX5 0 ... PASS"


<Msg>		"Exiting pfeffa..."
<Prompt>	"#"
<Send>		"exit"
<Wait>
<Msg>		"Restart PCI..."
<Send>		"slay pci-atlantis"
<Wait>
<Send>		"pci-atlantis"
<Wait>

<Include>	Check_PCI_V.inc

# Second time should be clean
<Prompt>	"> "
<Timeout>	10
<Send>		"pfeffa"
<Wait>
<Msg>		"Check for PCI errors"
<Send>		"show disco prob"
<Wait>
<Send>		"show disco prob"
<Wait>
<GetData>
<CheckDataX>	'PCI 0 ERROR REPORT'
<CheckDataX>	'PCI 1 ERROR REPORT'
<Prompt>	"#"
<Send>		"exit"


<Msg>		"IXP RAM Tests..."
<Send>		"ixtest -i"
<Wait>
<GetData>	Ixtest_I

<Send>
<Wait>

<Timeout>	90
<Msg>		"IXP DDR..."
<Sendslow>		"ixtest mt"
<Wait>
<GetData>
#<GetData>	Ixtest_mt
<CheckData>	'Passed'
#<CheckDataX>	'failed'
#<CheckDataX>	'Error'


<Timeout>	60
<Msg>		"IXP SRAM Bank 0..."
<Send>		"ixtest mt -s0 -p4"
<Wait>
<GetData>
<CheckData>	'Passed'
#<CheckDataX>	'failed'
#<CheckDataX>	'Error'

<Msg>		"IXP SRAM Bank 1..."
#<Send>		"ixtest mt -s1 0 0x1000000"
<Send>		"ixtest mt -s1 -p4"
<Wait>
<GetData>
<CheckData>	'Passed'
#<CheckDataX>	'failed'
#<CheckDataX>	'Error'

<Msg>		"IXP SRAM Bank 2 Bottom..."
#<Send>		"ixtest mt -s2 0 0x1000000"
<Send>		"ixtest mt -s2 0 0x7ffff0"
<Wait>
<GetData>
<CheckData>	'Passed'
#<CheckDataX>	'failed'
#<CheckDataX>	'Error'

<Msg>		"IXP SRAM Bank 2 TOP..."
#<Send>		"ixtest mt -s2 0 0x1000000"
<Send>		"ixtest mt -s2 0x800000 0x7ffff0"
<Wait>
<GetData>
<CheckData>	'Passed'
#<CheckDataX>	'failed'
#<CheckDataX>	'Error'

<Msg>		"IXP SRAM Bank 3 Bottom..."
#<Send>		"ixtest mt -s3 0 0x1000000"
<Send>		"ixtest mt -s3 0 0x7ffff0"
<Wait>
<GetData>
<CheckData>	'Passed'
#<CheckDataX>	'failed'
#<CheckDataX>	'Error'

<Msg>		"IXP SRAM Bank 3 Top..."
#<Send>		"ixtest mt -s3 0 0x1000000"
<Send>		"ixtest mt -s3 0x800000 0x7ffff0"
<Wait>
<GetData>
<CheckData>	'Passed'
#<CheckDataX>	'failed'
#<CheckDataX>	'Error'

# Second time should be clean
<Msg>		"Check for PCI errors"
<Send>		"pfeffa show disco prob"
<Wait>
<Send>		"pfeffa show disco prob"
<Wait>
<GetData>
<CheckDataX>	'PCI 0 ERROR REPORT'
<CheckDataX>	'PCI 1 ERROR REPORT'


#<Include>	Check_fuinit.inc
<Sleep>		2
<Prompt>	"#"
<TimeOut>	5
<Msg>		"Start fuinit..."
<Send>		"evlinit"
<Wait>
<TimeOut>	120
#<Send>		"fuinit_diag /fu/snake_load.uof 1 0 0 > /tmp/fuinit_results"  # 2009 Daigs
#2012 diags. Ubove no longer works
<Send>		"pfeffa test fuinitfabsnake"
<Wait>
<GetData>
<Send>		"pfeffa test pktloopbkn2trunk"
<Wait>
<GetData>
<timeout>	30
<Send>		"if (grep -q "Successful init_ixp2800"  /tmp/fuinit_results) then (echo "PASSED:$?"; echo fuinit completed > /tmp/fuinit_completed ) else (echo "FAILED:$?"; rm /tmp/fuinit_completed) fi"
<wait>
<GetData>
<CheckData>	"PASSED"
<Send>		cat /tmp/fuinit_results
<Wait>
<Getdata>
<CheckDataX>	'ERROR: 1 returned from ixp_check_xscale_up'
<CheckDataX>	'Reg Address Error'
#varies <CheckData>	'Shared memory segment created: 90303000'
<CheckData>	'Shared memory segment created successfully, initializing ixp2800 HW'
<CheckData>	'Initializing RDRAM Memory'
<CheckData>	'Bank 0: 256MB'
<CheckData>	'Bank 1: 256MB'
<CheckData>	'Bank 2: 256MB'
<CheckData>	'Test Reads for SRAM at CSR-f9000'
<CheckData>	'Test Reads for SRAM at CSR-f9400'
<CheckData>	'Test Reads for SRAM at CSR-f9800'
<CheckData>	'Test Reads for SRAM at CSR-f9c00'
<CheckData>	'xscale_pci_set_int_bus_priority: Misc Control=3ff0000'
<CheckData>	'Downloading: /proc/boot/redboot.bin to location: 0'
<CheckData>	'Downloading: /proc/boot/QNX_kernel.ixp.ifs to location: 4000000'
<CheckData>	'Waiting for XScale UP..............'

<CheckData>	'N2 microcode boot image loaded '
<CheckData>	'Ctx memory range\(0x0000000-0x10000000\)'
<CheckData>	'Cleared 262144 1024-byte blocks in 5 requests.'
<CheckData>	'N2 microcode full image loaded \(131048 bytes, 4 images\)'
<CheckData>	'Downloading: /fu/snake_load.uof to location: 3000000'

<CheckData>	'TCAM ayama20k_init...'
<CheckData>	'TCAM ayama20k_init DONE!'
<CheckData>	'Successful init_ixp2800'
<CheckData>	'Successful sram_api_init'

<Msg>		"Test Voltages..."
<Send>		"pfeffa test volt"
<Wait>
<GetData>
<CheckData>	PASS


<Msg>		"Checking DC voltages ..."
<Send>		"pfeffa show volt"
<Wait>
<GetData>	Volts


# Second time should be clean
<Msg>		"Check for PCI errors"
<Send>		"pfeffa show disco prob"
<Wait>
<Send>		"pfeffa show disco prob"
<Wait>
<GetData>
<CheckDataX>	'PCI 0 ERROR REPORT'
<CheckDataX>	'PCI 1 ERROR REPORT'

#Added for 5th link support
<msg>		"Check Local fab links"
<send>		"fabd -l"
<wait>
<GetData>
<CheckData> "Port  0 : Link UP, adjacency: Disco"
<CheckData> "Port  0 : Link UP, adjacency: Disco"
<CheckData> "Port  1 : Link UP, adjacency: Disabled"
<Bypass>	$SW55thlink_gbl
	<Msg>	"Checking for Link 19"
	<CheckData> "Port 19 : Link UP, adjacency: IXP"
</Bypass>
<CheckData> "Port 20 : Link UP, adjacency: IXP"
<CheckData> "Port 21 : Link UP, adjacency: IXP"
<CheckData> "Port 22 : Link UP, adjacency: IXP"
<CheckData> "Port 23 : Link UP, adjacency: IXP"

#Diags 010407
<Msg>       "Testing Tcam..."
<Timeout>   120
<Send>      'pfeffa test tcam'
<Wait>

<CheckData> 'Associated Data    Data Bus Bit Test PASSED'
<CheckData> 'Associated Data Address Bus Bit Test PASSED'
<CheckData> 'Associated Data Mod3 Memory     Test PASSED'
<CheckData> 'TCAM Entry Verify               Test PASSED'
<CheckData> 'TCAM Search                     Test PASSED'
<CheckData> 'TCAM Search Hit/Miss            Test PASSED'
<CheckData> 'Associated Data    Data Bus Bit Test PASSED'
<CheckData> 'Associated Data Address Bus Bit Test PASSED'
<CheckData> 'Associated Data Mod3 Memory     Test PASSED'
<CheckData> 'TCAM Entry Verify               Test PASSED'
<CheckData> 'TCAM Search                     Test PASSED'
<CheckData> 'TCAM Search Hit/Miss            Test PASSED'
<CheckData> 'Test command completed'
<CheckDatax> 'ERROR'
<CheckDatax> 'FAIL'
<GetData>

<Bypass>	$UUT_Variable_ref[0]->{Sahasera}
			<TimeOut>	60
			<Msg>	"Testing Sahasra..."
			<Send>	'pfeffa test sahasra'
            <Wait>
            <GetData>
            <CheckData>	"PASSED"
            <CheckData> "Completed tests"
</Bypass>


# Still vailed but depreciated as of 010507
#<Include>	Check_tcam.inc
#<Msg>		"Test Tcam..."
#<Prompt>	"#"
#<TimeOut>	10
#Start Qtalk with ? escape
#<Send>		"qtalk -c 3f -m /dev/ser2"
#<Sleep>		5
#<Send>
#<Wait>
#<Sleep>		5
#<Send>
#<Wait>
#<TimeOut>	40
#<Send>		"xstest tc -i -k -m -s -v"
#<Wait>
#<GetData>
# Diags before 04/06
#<CheckData>	"AD Memory Test.*PASS"
#<CheckData>	"TCAM Entry Verify Test.*PASS"
#<CheckData>	"TCAM Search Test.*PASS"
# Diags After 04/06
#<CheckData>	"Associated Data Mod3 Memory     Test PASS"
#<CheckData>	"TCAM Entry Verify               Test PASS"
#<CheckData>	"TCAM Search                     Test PASS"


#<Bypass>	$UUT_Variable_ref[0]->{Sahasera}
#			<TimeOut>	60
#			<Msg>	"Testing Shasera..."
#            <Send>	'diag_ref_app20k | grep PASSED'
#            <Wait>
#            <GetData>
#            <CheckData>	"PASSED"
#            #<CheckData> "Completed tests"
#</Bypass>

#<SendChr>	'?'
#<Msg>		'Exiting TCAM Test'
#<Sleep>		1
#<SendChr>	'x'
#<Wait>

<Msg>		"Test Cavium DDR Core 0"
<Timeout>	180
<Send>		"ddr_test 0 100000 0"
<Wait>
<GetData>
<CheckData>	"PASS"
<CheckDatax>	"failed"

<Send>		"ddr_test 8800000 8900000 0"
<Wait>
<GetData>
<CheckData>	"PASS"
<CheckDatax>	"failed"

<Send>		"ddr_test FE00000 FFFFFFF 0"
<Wait>
<GetData>
<CheckData>	"PASS"
<CheckDatax>	"failed"


# Second time should be clean
<Msg>		"Check for PCI errors"
<Send>		"pfeffa show disco prob"
<Wait>
<GetData>
<CheckDataX>	'PCI 0 ERROR REPORT'
<CheckDataX>	'PCI 1 ERROR REPORT'

<Msg>		"Reboot Card..."
<TimeOut>	30
<Prompt>	"Stoke>>"
<Msg>		"Bootup from Secondary flash..."
<Send>		"reset board"

<Include>	Stop_stoke_boot.inc
#<Msg>		"Stopping Stoke bootup.."
#<WaitFor>	"now to use STOKE boot monitor:"
#<SendChr>		"stoke"
#<Wait>

<Prompt>	">"
<TimeOut>	5
<Msg>		"Starting Noodle..."
<Send>
<Wait>
<Send>		"go ffe00100"
<Wait>


<Prompt>	"#"
<TimeOut>	60

<Msg>		"Booting IFS flash ..."
<Send>		"boot flash"
<Waitfor>	"application"
<Wait>
#For 3.0
<Msg>		"Disable system reload"
<Send>		"ls > /dev/shmem/system_noreload"
<Wait>
#<Msg>       "Disco to IXP loopback test ..."
#<TimeOut>   120
## ls /stoke/bin/diag/disco-to-ixp-link-test : pfeffa test link disco 2 as-is
#### Old Diags prior to 9/19/08
###<Send>     "disco-to-ixp-link-test"
##<Send>      " pfeffa test discotoixplink"
##<Wait>      Can not wait for # due to GLC script
###<WaitFor>  "TESTING LINK DISCO GIG-PORT 2 ... PASS"
##<GetData>
##<CheckData> "TESTING LINK DISCO GIG-PORT 2 ... PASS"
###<Wait>
###<GetData>
#<Send> "pfeffa test pktloopbkixpfic"
#<Wait>
#<CheckData> "Disco to IXP Link Test: PASSED"

