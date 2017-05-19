################################################################################
#
# Module:      Debug_XGLC_DRAM.dat
#
# Author:      Joe White
#
# Descr:       Main Execution for IMC Bench test
#
# Version:    1.1 $Id: Bench.dat,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created from Bench.dat  092811
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2012 Stoke. All rights reserved.
#
################################################################################
<Prompt>	"#"
<timeout>	3
<Msg>		"Starting GPP DRAM test in background"
###########################   Infinit loop with ecc checks b2nk 1 bank 2 mixed test ##############################
<sendslow>	"integer x=0"
<wait>
<sendslow>	"integer fail=0"
<wait>
<sendslow>	"testpath=/tmp/"
<wait>
<sendslow>	"rm /tmp/status.tmp"
<wait>
<sendslow>	"rm /tmp/memtest_results.**"
<wait>
<sendslow>	"rm /tmp/CPU_dram_.*"
<wait>
<sendslow>	"rm ${testpath}fail.tmp"
<wait>

<sendslow>	"set -A cpumem_ecc 8e40 9e40 8e4c 8e50 9e4c 9e50"
<wait>
<sendslow>	"integer y=0"
<wait>
<sendslow>	"integer memorysize=1024"
<wait>
# 1024 -b 5500s (2.6meg/s) , 1024 16500s 0.9meg/s, 512 -b 3000 , 512 5600 , -b 256 610s (5.9meg/s)
			#  256 2346.38, 128 -b 300s
<sendslow>	"integer memorytest=0"
<wait>
<sendslow>	"let memorytest=$memorysize"
<wait>
#basic=-b
<sendslow>	"basic="
<wait>
<sendslow>	"set -A memteststr 80000000 180000000 1C0000000 280000000 2C0000000 300000000 380000000 3C0000000 100000000 340000000 200000000 140000000 40000000 200000000 240000000"
<wait>
<Prompt>	"^>"
#<sendslow>	"while ((${fail}==0)) do"
#<wait>
<sendslow>	"("
<wait>
#Background started
<sendslow>	"	y=0"
<wait>
<sendslow>	"	x=0"
<wait>
<sendslow>	"	let testtimecount+=SECONDS"
<wait>
<sendslow>	"	let loopcount+=1"
<wait>
<sendslow>	"	echo		"${fail} Started Loop ${loopcount} Time count: ${testtimecount}...`date`""
<wait>
<sendslow>	"      while [ $x -lt 14 ]"
<wait>
<sendslow>	"		do"
<wait>
<sendslow>	"       	if (on -p6r xglcmemtest -o 0x${memteststr[$x]} -s ${memorysize}M ${basic} -l ${testpath}CPU_dram${memteststr[$x]}.tmp 2>&1 ) then"
<wait>
<sendslow>	"            	echo "CPU_dram_${memteststr[$x]}:passed:$fail: `date`" >> ${testpath}status.tmp"
<wait>
<sendslow>	"        	else"
<wait>
<sendslow>	"            	let fail+=1"
<wait>
<sendslow>	"            	echo "CPU_dram_${memteststr[$x]}:Failed:$fail: `date`" >> ${testpath}status.tmp"
<wait>
<sendslow>	"            	cat /dev/shmem/memtest_results_${memteststr[$x]}_${memorysize}M  > ${testpath}CPU_dram${memteststr[$x]}.tmp 2>&1"
<wait>
<sendslow>	"		echo "CPU_dram_${memteststr[$x]}:Failed:$fail: `date`" >> ${testpath}fail.tmp"
<wait>
<sendslow>	"        fi  &"
<wait>
<sendslow>	"		if ( (($memorytest > 4000))) then"
<wait>
<sendslow>	"			echo "memory Size ${memorytest}. Waiting for CPU_dram_${memteststr[$x]} to finish : `date`" >> ${testpath}status.tmp"
<wait>
<sendslow>	"			time wait"
<wait>
<sendslow>	"			let memorytest=$memorysize"
<wait>
<sendslow>	"		fi"
<wait>
<sendslow>	"		let memorytest+=$memorysize"
<wait>
<sendslow>	"		if ((($x == 13))) then"
<wait>
<sendslow>	"			echo waiting... >> ${testpath}status.tmp"
<wait>
<sendslow>	"			 wait"
<wait>
<sendslow>	"		else"
<wait>
<sendslow>	"			echo loop ${x} >> ${testpath}status.tmp"
<wait>
<sendslow>	"	 	fi"
<wait>
<sendslow>	"		(( x=x+1 ))"
<wait>
<sendslow>	"		sleep 1"
<wait>
<sendslow>	"	 done  &"
<wait>
<sendslow>	"	echo waiting.... >> ${testpath}status.tmp"
<wait>
<sendslow>	"	wait"
<wait>
<sendslow>	"	if    (test -f ${testpath}fail.tmp )  then"
<wait>
<sendslow>	"		   echo        "Fail.tmp exist setting fail flag: `date`" >> ${testpath}status.tmp"
<wait>
<sendslow>	"		   let fail+=1"
<wait>
<sendslow>	"	 fi"
<wait>
<sendslow>	"	y=0"
<wait>
<sendslow>	" 	while [ $y -lt 6 ]"
<wait>
<sendslow>	"		do"
<wait>
<sendslow>	"		on -p6r xglcdiag ccsracc rd ${cpumem_ecc[$y]} 1  > ${testpath}CPU_dram_ECC_${cpumem_ecc[$y]}.tmp"
<wait>
<sendslow>	"       		if ( grep -q "Addr.* = 0" ${testpath}CPU_dram_ECC_${cpumem_ecc[$y]}.tmp  > ${testpath}status_ECC 2>&1) then"
<wait>
<sendslow>	"            		echo "CPU_dram_ECC${cpumem_ecc_[$y]}:passed:$fail: `date`" >> ${testpath}status.tmp"
<wait>
<sendslow>	"        		else"
<wait>
<sendslow>	"            		let fail+=1"
<wait>
<sendslow>	"            		echo "CPU_dram_ECC${cpumem_ecc_[$y]}:Failed:$fail: `date`" >> ${testpath}status.tmp"
<wait>
<sendslow>	"			cat  ${testpath}CPU_dram_ECC_${cpumem_ecc[$y]}.tmp"
<wait>
<sendslow>	"        	fi"
<wait>
<sendslow>	"		(( y=y+1 ))"
<wait>
<sendslow>	"	done"
<wait>
<sendslow>	"	on -p6r xglcdiag ccsracc rd 130008 1 > ${testpath}XLP_dram_ECC.tmp"
<wait>
<sendslow>	"      		if ( grep -iq "Addr.* = c30000f0" ${testpath}XLP_dram_ECC.tmp  > ${testpath}status_ECC 2>&1) then"
<wait>
<sendslow>	"            	echo "XLP_dram_ECC:passed:$fail: `date`" >> ${testpath}status.tmp"
<wait>
<sendslow>	"        	else"
<wait>
<sendslow>	"            	let fail+=1"
<wait>
<sendslow>	"            	echo "XLP_dram_ECC:Failed:$fail: `date`" >> ${testpath}status.tmp"
<wait>
<sendslow>	"		cat  ${testpath}XLP_dram_ECC.tmp"
<wait>
<sendslow>	"           	echo "CPU_dram_ECC_${cpumem_ecc_[$y]}:Failed:$fail: `date`" >> ${testpath}status.tmp"
<wait>
<sendslow>	"            	echo "CPU_dram_ECC_${cpumem_ecc_[$y]}:Failed:$fail: `date`" >> ${testpath}CPU_dram_ECC_${cpumem_ecc[$y]}.tmp"
<wait>
<sendslow>	"		xglcdiag ccsracc rd 8e20 40 >>  ${testpath}CPU_dram_ECC_${cpumem_ecc[$y]}.tmp"
<wait>
<sendslow>	"		xglcdiag ccsracc rd 9e20 40 >>  ${testpath}CPU_dram_ECC_${cpumem_ecc[$y]}.tmp"
<wait>
<sendslow>	"        fi"
<wait>
#<sendslow>	"done &"
#<wait>
<Prompt>	"#"
<sendslow>	") &"
<wait>
#Background end
<sendslow>	"jobs"
<wait>
<Getdata>


