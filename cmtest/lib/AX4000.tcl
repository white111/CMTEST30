#!/usr/bin/tcl
###############################################################################
#
# Module:      Ax4000.tcl
#
# Author:      Joe White
#
# Description: TCL Script control of the AX4000 Traffic system, Adpated from Spirent Example
#
# Version:    (See below) $Id: AX4000.tcl,v 1.5 2008/02/22 21:00:51 joe Exp $
#
# Changes:	  Initial script 1/17/06
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
# Notes:
#	Setup:
#	Install Dir: /usr/local/AX4000
#	Environment:
#  		Link:	tcl8.4 has a link tcllib8.4.so to tcllib8.3.so
#		.bashrc:	export LD_LIBRARY_PATH=/usr/lib/tcl8.4:$LD_LIBRARY_PATH
#
###############################################################################
#@cvs-id $Id: AX4000.tcl,v 1.5 2008/02/22 21:00:51 joe Exp $
set Version_AX4000 "v1.1 1/31/2008"
#Command line example:
#tclsh ../lib/AX4000.tcl root mfg-adtech 60 ~/tmp/AX4000.log MONITOR 1
############## Global PARAMETERS ###############
### Command line Paramemters
set axuser root
set chassis_ip mfg-adtech
set test_duration 60
set logfile "test_output.txt"
set testtype "monitor"
set interface 1

### Static Globals
 # 0 = pass, all else = fail
set failflag  0
set etype_manufacturing1 "RampFrameSize -initialFrameSize 64 -frameSizeStep 256 -frameSizePeriod 10 -frameNumSteps 10 -fillType PRBS23"
set framesize1 64
set framesize2 512
set framesize3 1514
set bandwidth 50

set interface1 1
set interface2 2
set interface3 3
set interface4 4
## Keyed to installed location
set loaddir "/usr/local/AX4000/tclclib/libax4k.so"
set loadpkg	"ax4kpkg"
set homedir "/usr/local/AX4000"
set biosdir "/usr/local/AX4000/bios"

#########################################
#########################################
#########################################

proc InterfaceSetup_Monitor {} {

global chassis_ip
global axuser
global outfile
global framesize
global bandwidth
global interface1
global outputfile
global homedir
global biosdir
global logfile
global loaddir
global  loadpkg



## Load AX4000 extensions
puts "Loading AX4000 Extensions"
load $loaddir $loadpkg
puts "Loading AX4000 Extensions"
puts "Set home Directory: $homedir"
##cd  $homedir
puts "Set BIOS Location: $biosdir"
ax hwdir $biosdir

set outfile [clock format [clock seconds] -format %m-%d-%y_%H:%M:%S]
set date [clock format [clock seconds] -format %m/%d/%y]
puts "Date: $date"
set timestamp [clock format [clock seconds] -format %H:%M:%S]
puts "Time: $timestamp"
puts ""

append outfile ".txt"
set outputfile $logfile
puts "opening file: $outputfile"
set outfile [open $outputfile "a+"]
puts $outfile "Test Started..."
puts "AX400 Script Vers: $Version_AX4000 "
puts "#######################"
puts "Connecting to AX4000..."
puts "#######################"
puts ""
ax init -remote $chassis_ip -user $axuser -nobios 0

puts ""
puts [ax devlist]
puts ""
puts "Clearing interfaces..."
enet break $chassis_ip $interface1
enet unlock $interface1  $interface1

puts "Locking interfaces..."
enet lock $interface1 $chassis_ip $interface1


puts "Create and configure interfaces..."
interface create int1 $interface1 -ifmode IPoETHER


int1 stop
after 200
int1 reset
after 200
int1 clear
after 200



int1 set -mode MONITOR -autonegotiation 1
#int1 set -mode MONITOR -autonegotiation 1
int1 run
puts " Interface in Monitor Mode"
}


proc AnalyzerSetup_Monitor {} {

global interface1
global framesize
global bandwidth
global etype_manufacturing1


puts "Create generators and analyzers..."
generator create gen1 $interface1
analyzer create ana1 $interface1

puts "Reset generators and analyzers..."
gen1 reset
ana1 reset


puts "Stop and clear generators and analyzers..."
generator stop {gen1}
after 1000
analyzer stop {ana1}
after 500

puts "Defining Traffic..."


ana1 subfilter set ether



}

proc RunAnalyzer_Monitor {} {

 global test_duration

 puts "STARTING Analyzer ..."
 analyzer run {ana1}
 after 4000

 puts "STARTING Analyzer TRAFFIC..."
 gen1 run
 puts "Running Traffic: $test_duration Seconds"

 after [expr $test_duration * 1000]

 puts "STOPPING TRAFFIC..."

 after 5000
 analyzer stop {ana1}

}

proc GetStats_Monitor {} {
	  # Test Counters

      set local_fail = 0

    set numstreams 0
    global outfile

    after 5000
    ana1 refreshList

    after 2000
    puts "RECEIVING and DISPLAYING ANALYZER STATS..."
    puts ""
    #puts [gen1 stats]
    #array set genStatsOne [gen1 stats]
    set tsCountA1 $genStatsOne(-pktCount1)
    set tsCountA2 $genStatsOne(-pktCount2)
    set tsCountA3 $genStatsOne(-pktCount3)
    set tsCountA4 $genStatsOne(-pktCount4)
    set tsCountA5 $genStatsOne(-pktCount5)
    set tsCountA6 $genStatsOne(-pktCount6)
    set tsCountA7 $genStatsOne(-pktCount7)
    set tsCountA8 $genStatsOne(-pktCount8)

    set date [clock format [clock seconds] -format %m/%d/%y]
    set timestamp [clock format [clock seconds] -format %H:%M:%S]
    puts $outfile "Date: $date"
    puts $outfile "Time: $timestamp"
    puts $outfile ""
    puts $outfile "Substream #, Tx Packets, Rx Packets, Lost Packets, IPchksum Errors, CRC Errors, PRBS Errors"

    # obtain stream statistics
    for {set numa 0} {$numa <= $numstreams} {incr numa} {

      array set ana1$numa [ana1 stats -line $numa]

      puts "TransmittedPackets(substream$numa): [subst $[subst tsCountA[expr $numa + 1]]]"
      puts "TotalPackets(substream$numa): [subst $[subst ana1$numa\(-totalPackets)]]"
      if { [ [subst $[subst ana1$numa\(-test_lostPackets)]] != 0]} {
             local_fail++
             puts "Failed with [subst $[subst ana1$numa\(-test_lostPackets)]] LostPackets(substream$numa)"
             puts $outfile "Failed with [subst $[subst ana1$numa\(-test_lostPackets)]] LostPackets(substream$numa)"
      } else {
      			puts "LostPackets(substream$numa): [subst $[subst ana1$numa\(-test_lostPackets)]]"
      }
      puts "ipChecksumErrors(substream$numa): [subst $[subst ana1$numa\(-ipChecksumErrors)]]"
      puts "CRCerrors(substream$numa): [subst $[subst ana1$numa\(-phyCrcErrors)]]"
      puts "PRBSBitErrors(substream$numa): [subst $[subst ana1$numa\(-test_prbsBitErrors)]]"
      puts ""
      puts  $outfile "INT1_TSRC_substream$numa:, [subst $[subst tsCountA[expr $numa + 1]]], [subst $[subst ana1$numa\(-totalPackets)]], [subst $[subst ana1$numa\(-test_lostPackets)]], [subst $[subst ana1$numa\(-ipChecksumErrors)]],[subst $[subst ana1$numa\(-phyCrcErrors)]],[subst $[subst ana1$numa\(-test_prbsBitErrors)]]"
      puts ""

    }
    puts ""
    puts $outfile ""
    return $local_fail
}

proc StopTest_Monitor {} {

 global interface1
 global outfile
 global timestamp


 puts "STOPPING TEST..."
 generator stop {gen1}
 analyzer stop {ana1}
 int1 stop

 #gen1 destroy
 #ana1 destroy
 #int1 destroy


 puts "Unlocking ports..."
 enet unlock $interface1

 puts "Test completed..."
 puts $outfile "Test completed..."
 set date [clock format [clock seconds] -format %m/%d/%y]
 set timestamp [clock format [clock seconds] -format %H:%M:%S]
 puts $outfile "Date: $date"
 puts $outfile "Time: $timestamp"

 exit

}


proc InterfaceSetup {} {

global chassis_ip
global testtype
global axuser
global outfile
global framesize
global bandwidth
global interface1
global outputfile
global homedir
global biosdir
global logfile
#global interface2
#global interface3
#global interface4

global loaddir
global  loadpkg
set local_fail  0


## Load AX4000 extensions
load $loaddir $loadpkg

puts "Set home Directory: $homedir"
#cd  $homedir
puts "Set BIOS Location: $biosdir"
ax hwdir $biosdir


set outfile [clock format [clock seconds] -format %m-%d-%y_%H:%M:%S]
set date [clock format [clock seconds] -format %m/%d/%y]
puts "Date: $date"
set timestamp [clock format [clock seconds] -format %H:%M:%S]
puts "Time: $timestamp"
puts ""

append outfile ".txt"
set outputfile $logfile
puts "opening file: $outputfile"
set outfile [open $outputfile "a+"]
puts $outfile "Test Started..."

puts "#######################"
puts "Connecting to AX4000..."
puts "#######################"
puts ""
ax init -remote $chassis_ip -user $axuser -nobios 0

puts ""
puts [ax devlist]
puts ""
puts "Clearing interfaces..."
enet break $chassis_ip $interface1
enet unlock $interface1  $interface1

puts "Locking interfaces..."
enet lock $interface1 $chassis_ip $interface1
###enet lock $interface2 $chassis_ip $interface2
###enet lock $interface3 $chassis_ip $interface3
###enet lock $interface4 $chassis_ip $interface4

puts "Create and configure interfaces..."
interface create int1 $interface1 -ifmode IPoETHER
###interface create int2 $interface2 -ifmode IPoETHER
###interface create int3 $interface3 -ifmode IPoETHER
###interface create int4 $interface4 -ifmode IPoETHER

int1 stop
after 200
int1 reset
after 200
int1 clear
after 200
###int2 stop
###after 200
###int2 reset
###after 200
###int2 clear
###after 200
###int3 stop
###after 200
###int3 reset
###after 200
###int3 clear
###after 200
###
###int4 stop
###after 200
###int4 reset
###after 200
###int4 clear
###after 200


int1 set -mode $testtype -autonegotiation 1
#int1 set -mode LOOPBACK -autonegotiation 0
int1 run
###int2 set -mode NORMAL -autonegotiation 0
###int2 run
###int3 set -mode NORMAL -autonegotiation 0
###int3 run
###int4 set -mode NORMAL -autonegotiation 0
###int4 run

}


proc GeneratorAnalyzerSetup {} {

global interface1
global framesize
global bandwidth
###global interface2
#global interface3
#global interface4

puts "Create generators and analyzers..."
generator create gen1 $interface1
analyzer create ana1 $interface1
###generator create gen2 $interface2
###analyzer create ana2 $interface2
###generator create gen3 $interface3
###analyzer create ana13 $interface3
###generator create gen4 $interface4
###analyzer create ana4 $interface4

puts "Reset generators and analyzers..."
gen1 reset
ana1 reset
###gen2 reset
###ana2 reset
###gen3 reset
###ana3 reset
###gen4 reset
###ana4 reset

puts "Stop and clear generators and analyzers..."
generator stop {gen1}
after 1000
analyzer stop {ana1}
after 500

puts "Defining Traffic..."
puts "	Stream 1"

#gen1 seqdefine 1 ipoetherIPTestPkt ipEthBlk \
# -headerType EII -srcAddr FIXED -fixedAddr 00.10.94.02.14.22  \
# -dstAddr FIXED -fixedAddr 00.00.01.00.00.01 \
# -VLANID 1 \
# ipBlk


##-src FIXED -fixedAddr 10.1.1.2 -dst FIXED -fixedAddr 10.1.1.3
#gen1 dgramlen 1 fixed -len $framesize
#gen1 dist 1 periodic -bw $bandwidth
#gen1 seqsend 1



gen1 seqdefine 1 IPoEtherIPTestPkt \
   -aggregate 0 \
   ipEthBlk -headerType EII -userPriority 0 -userPriority 0 -srcAddr \
      FIXED -fixedAddr 00.10.94.02.17.b6 -dstAddr FIXED -fixedAddr \
      00.00.00.00.00.00 \
   ipBlk -ver 4 -serviceType 0 -id 0 -bitFlags 0 -fragOffset 0 -TTL \
      0x40 -protocol 0xad -src FIXED 0.0.0.0 -dst FIXED 0.0.0.0 \
   ipTstBlk -fillType RAND

gen1 seqdefine 1 IPoEtherIPTestPkt \
   -aggregate 0 \
   ipEthBlk -headerType EII -userPriority 0 -userPriority 0 -srcAddr \
      FIXED -fixedAddr 00.10.94.02.17.b6 -dstAddr FIXED -fixedAddr \
      00.00.00.00.00.00 \
   ipBlk -ver 4 -serviceType 0 -id 0 -bitFlags 0 -fragOffset 0 -TTL \
      0x40 -protocol 0xad -src FIXED 0.0.0.0 -dst FIXED 0.0.0.0 \
   ipTstBlk -fillType RAND

gen1 seqdefine 1 IPoEtherIPTestPkt \
   -aggregate 0 \
   ipEthBlk -headerType EII -userPriority 0 -userPriority 0 -srcAddr \
      FIXED -fixedAddr 00.10.94.02.17.b6 -dstAddr FIXED -fixedAddr \
      00.00.00.00.00.00 \
   ipBlk -ver 4 -serviceType 0 -id 0 -bitFlags 0 -fragOffset 0 -TTL \
      0x40 -protocol 0xad -src FIXED 0.0.0.0 -dst FIXED 0.0.0.0 \
   ipTstBlk -fillType RAND

gen1 dist 1 periodic -bw $bandwidth

gen1 dgramlen 1 \
   fixed 46

#gen1 localshaper 1 disabled

gen1 seqsend 1





ana1 subfilter set ether
###ana2 subfilter set ether
###ana3 subfilter set ether
###ana4 subfilter set ether


}


proc Create_TCL_FROM_IPT  {} {

global interface1
global framesize
global bandwidth
global logfile


puts ("Create from ../lib/AX4000Setup.ipt TCL  $logfile")
axtLoadFile 1 {-inFile ../lib/AX4000Setup.ipt -trafSrc 1} -progopts {-gen gen1 } -outFile $logfile
exit


}

proc RunTraffic {} {

 global test_duration

 puts "STARTING TRAFFIC..."
 analyzer run {ana1}
 after 4000

 gen1 run
 ###gen2 run
 #generator syncrun {gen1 gen2} -delay 1
 puts "Running Traffic: $test_duration Seconds"
 after [expr $test_duration * 1000]

 puts "STOPPING TRAFFIC..."
 generator stop {gen1}
 after 5000
 analyzer stop {ana1}

}

proc GetStats {} {
    set local_fail 0
    set numstreams 0
    global outfile

    after 5000
    ana1 refreshList
    ###ana2 refreshList
    ###ana3 refreshList
    ###ana4 refreshList
    after 2000
    puts "RECEIVING and DISPLAYING ANALYZER STATS..."
    puts ""

    puts [gen1 stats]
    array set genStatsOne [gen1 stats]
    set tsCountA1 $genStatsOne(-pktCount1)
    set tsCountA2 $genStatsOne(-pktCount2)
    set tsCountA3 $genStatsOne(-pktCount3)
    set tsCountA4 $genStatsOne(-pktCount4)
    set tsCountA5 $genStatsOne(-pktCount5)
    set tsCountA6 $genStatsOne(-pktCount6)
    set tsCountA7 $genStatsOne(-pktCount7)
    set tsCountA8 $genStatsOne(-pktCount8)



    set date [clock format [clock seconds] -format %m/%d/%y]
    set timestamp [clock format [clock seconds] -format %H:%M:%S]
    puts $outfile "Start Date: $date"
    puts $outfile "Start Time: $timestamp"
    puts $outfile ""
    puts $outfile "Substream #, Tx Packets, Rx Packets, Lost Packets, IPchksum Errors, CRC Errors, PRBS Errors"

    # obtain stream statistics
    for {set numa 0} {$numa <= $numstreams} {incr numa} {

      array set ana1$numa [ana1 stats -line $numa]


      puts  $outfile "INT1_TSRC_substream$numa:, [subst $[subst tsCountA[expr $numa + 1]]], [subst $[subst ana1$numa\(-totalPackets)]], [subst $[subst ana1$numa\(-test_lostPackets)]], [subst $[subst ana1$numa\(-ipChecksumErrors)]],[subst $[subst ana1$numa\(-phyCrcErrors)]],[subst $[subst ana1$numa\(-test_prbsBitErrors)]]"
      puts ""
      puts "TransmittedPackets(substream$numa): [subst $[subst tsCountA[expr $numa + 1]]]"
      puts "TotalPackets(substream$numa): [subst $[subst ana1$numa\(-totalPackets)]]"
      if {  ![subst $[subst ana1$numa\(-test_lostPackets)]] } {
      	puts "LostPackets(substream$numa): [subst $[subst ana1$numa\(-test_lostPackets)]]"
      } else {
        set local_fail  [expr $local_fail + 1]
        puts "Failed with [subst $[subst ana1$numa\(-test_lostPackets)]] LostPackets(substream$numa)"
        puts $outfile "	Failed with [subst $[subst ana1$numa\(-test_lostPackets)]] LostPackets(substream$numa)"

      }

     if {  ![subst $[subst ana1$numa\(-ipChecksumErrors)]] } {
      	puts "ipChecksumErrors(substream$numa): [subst $[subst ana1$numa\(-ipChecksumErrors)]]"
      } else {
        set local_fail  [expr $local_fail + 1]
        puts "Failed with  [subst $[subst ana1$numa\(-ipChecksumErrors)]] ipChecksumErrors(substream$numa)"
        puts $outfile "	Failed with  [subst $[subst ana1$numa\(-ipChecksumErrors)]] ipChecksumErrors(substream$numa)"

      }

      if {  ![subst $[subst ana1$numa\(-phyCrcErrors)]] } {
      	puts "CRCerrors(substream$numa): [subst $[subst ana1$numa\(-phyCrcErrors)]]"
      } else {
        set local_fail  [expr $local_fail + 1]
        puts "Failed with  [subst $[subst ana1$numa\(-phyCrcErrors)]] CRCerrors(substream$numa)"
        puts $outfile "	Failed with  [subst $[subst ana1$numa\(-phyCrcErrors)]] CRCerrors(substream$numa)"

      }

      if {  ![subst $[subst ana1$numa\(-test_prbsBitErrors)]] } {
      	puts "PRBSBitErrors(substream$numa): [subst $[subst ana1$numa\(-test_prbsBitErrors)]]"
      } else {
        set local_fail  [expr $local_fail + 1]
        puts "Failed with  [subst $[subst ana1$numa\(-test_prbsBitErrors)]] PRBSBitErrors(substream$numa)"
        puts $outfile "	Failed with  [subst $[subst ana1$numa\(-test_prbsBitErrors)]] PRBSBitErrors(substream$numa)"

      }
      puts ""



    }
    puts ""
    puts $outfile ""

    return $local_fail
}

proc StopTest {} {

 global interface1
 global outfile
 global timestamp
 global failflag

  ###global interface2
 #global interface3
 #global interface4

 puts "STOPPING TEST..."
 generator stop {gen1}
 analyzer stop {ana1}
 int1 stop
 ###int2 stop
 ###int3 stop
 ###int4 stop

 gen1 destroy
 ana1 destroy
 int1 destroy
 ###gen2 destroy
 ###ana2 destroy
 ###int2 destroy
 ###gen3 destroy
 ###ana3 destroy
 ###int3 destroy
 ###gen4 destroy
 ###ana4 destroy
 ###int4 destroy

 puts "Unlocking ports..."
 enet unlock $interface1
 ###enet unlock $interface2
 ###enet unlock $interface3
 ###enet unlock $interface4

 puts "Test completed..."
 puts $outfile "Test completed..."
 set date [clock format [clock seconds] -format %m/%d/%y]
 set timestamp [clock format [clock seconds] -format %H:%M:%S]
 puts $outfile "Stop Date: $date"
 puts $outfile "Stop Time: $timestamp"

  if $failflag {
		puts "Failed: External Traffic Test $failflag"
		puts $outfile "Failed: External Traffic Test"
	} else {
    	puts "PASSED: External Traffic Test $failflag"
		puts $outfile "PASSED: External Traffic Test"
	}

 exit  $failflag

}


### MAIN ###
if {$argc != 6} {
	puts "Cmd line: $argv0 IP Test_len_(Sec) Test_Type Interface# Log_file"
    puts "Failed to start AX4000"
	exit -1
} else {
    puts "AX4000 Script Vers: $Version_AX4000 "
	set axuser [lindex $argv 0]
	set chassis_ip [lindex $argv 1]
	set test_duration [lindex $argv 2]
	set logfile [lindex $argv 3]
	set testtype [lindex $argv 4]
	set interface [lindex $argv 5]

	puts "Command Line: $axuser $chassis_ip $test_duration $logfile $testtype $interface "
	}
if { [string match "MONITOR" $testtype]} {
	puts "Starting up MONITOR"
	InterfaceSetup
	AnalyzerSetup_Monitor
	RunAnalyzer_Monitor
	#GetStats_Monitor
	StopTest
}  elseif  { [string match "NORMAL" $testtype] || [string match "LOOPBACK" $testtype]} {
	puts "Starting up Trafic test in $testtype mode"
    InterfaceSetup
	GeneratorAnalyzerSetup
	RunTraffic
	if {[GetStats]} {
		set failflag [expr $failflag + 1]
    }
    StopTest
	}  elseif  { [string match "TCLCODE" $testtype] } {
	puts "Creating TCL Code from IPT file code in $logfile"

	Create_TCL_FROM_IPT

}   else {
	puts "Invalid option: $testtype entered"
	puts "Expected: MONITOR, NORMAL or LOOPBACK"
	exit -1
	}


