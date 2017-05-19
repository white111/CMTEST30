################################################################################
#
# Module:      KSH Script MC tests
#
# Author:      Joe White
#
# Descr:       Script run on each MC during BI
#
# Version:    1.8 $Id: IMC.ksh,v 1.1 2008/03/11 18:29:45 joe Exp $
#
# Changes:    Created 03/01/06
#			  Changed tests to processes, added drive tests
#			  fixed testtime bug 03/30/06
#			  Added Quiet to cfint and cfext tests 05/02/06
#			  Updated 12/1/07 Diags
#			  01/29/06 diags 1/29/or later added dram test for avaialble system memory
#			  030408 Added Random back to HD tests
#			  03/07/08 COrrected /hd /cfint /cfext devices, added dcheckpri to lower dcheck priority
#			  04/21/08 Moved all files for IMC in slot 1 to IMC in slot 1
#
# Used By:
#				Chassis_BI.dat, Chassis extended.dat
# Includes:
#
# Setup: Expects to have evlinit and fuinit already run
#
# Still ToDo:
#
#
#            Copyright (c) 2005 Stoke. All rights reserved.
## SOCK=/nv ifconfig en0 inet 192.168.63.130
#SOCK=/nv telnet 192.168.200.201
################################################################################
Ver='1.5 1/31/2008'; # Updated versioning
CVS_Ver=' [ CVS: $Id: IMC.ksh,v 1.1 2008/03/11 18:29:45 joe Exp $ ]';
Version=$Ver$CVS_Ver;
# Command line
#
# if standby MC on -f /net/nv-2-0 ksh /net/nv-0-0/hd/dump/slot0/onscript_MC.txt 60  2 > /hd/dump/slot0/temp.txt 2>&1 &
#if Primary MC ksh onscript_MC.ksh 3700  0 > /hd/dump/slot0/Onscript_MC.txt 2>&1 &
# 1 = testtime 2 = slot
#print "$@"
# Fail flag
set -a
integer fail=0
export fail
failfile=onfile.txt

integer slot=0
dcheckpri='on -p4'
pfeffapri='on -p6'

# test time variable
integer testtime=$1
integer testtimeleft=$1
integer loopcount=0
slot=$2
failpath=/net/nv-$slot-0/hd/dump/slot
testpath=$failpath$slot/

failfile=$failpath$slot/onfile.txt
#echo Testtime=$testtime or $1
#echo logpath=$failpath slot $slot
echo Fails logged to $failfile
echo "Started ${0} ${@} Drive and Memory Tests at `date` \n ${Version}"
rm ${testpath}*.tmp > /dev/null 2>&1


while ((((${testtime} - SECONDS) > 10)  && (${fail}==0))) do
	let testtimeleft=testtime-SECONDS
	let loopcount+=1
	echo		"Started Loop ${loopcount} Time left: ${testtimeleft}..." > ${testpath}status.tmp
	echo		"Started ${0} Drive Tests Loop ${loopcount} Time left: ${testtimeleft}..."
	echo 		"Remove tempfiles from ${testpath}" >> ${testpath}status.tmp
	rm ${failfile}   > /dev/null 2>&1
	rm ${testpath}*.tmp > /dev/null 2>&1
	echo		"Drive tests V${Version} started: `date`"   >> ${testpath}status.tmp
	echo		"Test Voltage"   >> ${testpath}status.tmp
#xxxif ($slot != 1) then
	${pfeffapri} pfeffa test volts > ${testpath}testvolts.tmp
	if (grep -q "PASS" ${testpath}testvolts.tmp) then
		echo "Testvolts:passed:$fail"   >> ${testpath}status.tmp
	else
		let fail+=1
		echo "Testvolts:Failed:$fail" >> ${testpath}status.tmp
	fi
	echo		"Get Thermal Data"  >> ${testpath}status.tmp
	${pfeffapri} pfeffa show thermal > ${testpath}thermal.tmp
	if (grep -q "Tppci.*=.*[2-7][0-9].*C" ${testpath}thermal.tmp) then
		echo "Temp_TPPCI:passed:$fail"  >> ${testpath}status.tmp
	else
		let fail+=1
		echo "Temp_TPPCI:Failed:$fail"  >> ${testpath}status.tmp
	fi
	if (grep -q "TppcRem1.*=.*[2-7][0-9].*C" ${testpath}thermal.tmp) then
		echo "Temp_TppcRem1:passed:$fail" >> ${testpath}status.tmp
	else
		let fail+=1
		echo "Temp_TppcRem1:Failed:$fail" >> ${testpath}status.tmp
	fi
	if (grep -q "TppcRem2.*=.*[2-7][0-9].*C" ${testpath}thermal.tmp) then
		echo "Temp_TppcRem2:passed:$fail"  >> ${testpath}status.tmp
	else
		let fail+=1
		echo "Temp_TppcRem2:Failed:$fail" >> ${testpath}status.tmp
	fi
	#There is about a 10DegC delta in measured to actual ambient 50DegC at Sensor =~ 40DegC ambient
	if (grep -q "Tinlet.*=.*[1-5][0-9].*C" ${testpath}thermal.tmp) then
		echo "Temp_Tinlet:passed:$fail" >> ${testpath}status.tmp
	else
		let fail+=1
		echo "Temp_Tinlet:Failed:$fail" >> ${testpath}status.tmp
		echo "Slot:${slot} Tinlet Tempurature out of range:\n `grep Tinlet ${testpath}thermal.tmp`\n Shutting Down..." >> ${testpath}status.tmp
		echo "Slot:${slot} Tinlet Tempurature out of range:\n `grep Tinlet ${testpath}thermal.tmp`\n Shutting Down..." >> ${testpath}status.tmp
		echo "Slot:${slot} Tinlet Tempurature out of range:\n `grep Tinlet ${testpath}thermal.tmp`\n Shutting Down..." >> ${testpath}status.tmp
		#Emergency shutdown
		sleep 1
		slay -f devb-mvSata >> /dev/null  2>&1
		#slay -f devb-eide >> /dev/null  2>&1
		slay -f storaged  >> /dev/null  2>&1
		sleep 1 >> /dev/null   2>&1
		${pfeffapri} pfeffa w8 f4000042 1 >> /dev/null  2>&1
	fi
	if (grep -q "Toutlet.*=.*[2-5][0-9].*C" ${testpath}thermal.tmp) then
		echo "Temp_Toutlet:passed:$fail" >> ${testpath}status.tmp
	else
		let fail+=1
		echo "Temp_Toutlet:Failed:$fail" >> ${testpath}fail.tmp
		echo "Temp_Toutlet:Failed:$fail" >> ${testpath}status.tmp
	fi
        let testtimeleft=testtime-SECONDS

    #$loopcount > 2     &&  $slot != 1
    if ((($testtimeleft > 600 )));  then
        echo        "Test avaialble system memory: `date` : `pidin info`"  >> ${testpath}status.tmp
        ${pfeffapri} pfeffa test dram > ${testpath}dram_full.tmp
        if (grep -q "PASS" ${testpath}dram_full.tmp) then
            echo "dram_full:passed:$fail: `date`" >> ${testpath}status.tmp
        else
            let fail+=1
            echo "dram_full:Failed:$fail: `date`" >> ${testpath}fail.tmp
            echo "dram_full:Failed:$fail: `date`" >> ${testpath}status.tmp
        fi
    fi  &

    #||  $loopcount < 2  &&  $slot != 1
    if ((($testtimeleft < 600  )));  then
        echo        "Test avaialble system memory random: `date` : `pidin info`"  >> ${testpath}status.tmp
        pfeffa test dram random > ${testpath}dram_full.tmp
        if (grep -q "PASS" ${testpath}dram_full.tmp) then
            echo "dram_full:passed:$fail: `date`" >> ${testpath}status.tmp
        else
            let fail+=1
            echo "dram_full:Failed:$fail: `date`" >> ${testpath}fail.tmp
            echo "dram_full:Failed:$fail: `date`" >> ${testpath}status.tmp
        fi
    fi  &


            let testtimeleft=testtime-SECONDS
    echo        "CFEXT TESTs..."   >> ${testpath}status.tmp
    if ((($testtimeleft > 499)));  then
        echo        "Full Drive Tests Ext Flash: `date`"  >> ${testpath}status.tmp
        if (${dcheckpri} dcheck -q /dev/cfext0 > ${testpath}cfext_full.tmp) then (echo "CFEXT_full:passed:$fail: `date`" >> ${testpath}status.tmp) else
            let fail+=1
            echo "CFEXT_full:Failed:$fail: `date`" >> ${testpath}fail.tmp
            echo "CFEXT_full:Failed:$fail: `date`" >> ${testpath}status.tmp
        fi
    fi  &

    if ((($testtimeleft < 498 ))); then
        echo        "Drive Tests Ext Flash 1min: `date`"  >> ${testpath}status.tmp
        if (${dcheckpri} dcheck -q -b 20000 /dev/cfext0  > ${testpath}cfext_1min.tmp) then (echo "CFEXT_1min:passed:$fail: `date`" >> ${testpath}status.tmp) else
            let fail+=1
            echo "CFEXT_1min:Failed:$fail: `date`"  >> ${testpath}fail.tmp
            echo "CFEXT_1min:Failed:$fail: `date`"  >> ${testpath}status.tmp
        fi

    fi  &
    let testtimeleft=testtime-SECONDS
    echo        "CFINT TESTs..."    >> ${testpath}status.tmp
    if ((($testtimeleft > 499)));  then

        echo        "Full Drive Tests INT FLASH: `date`" >> ${testpath}status.tmp
        if (${dcheckpri} dcheck -q /dev/cfint0 > ${testpath}cfint_full.tmp) then (echo "CFINT_full:passed:$fail: `date`" >> ${testpath}status.tmp) else
            let fail+=1
            echo "CFINT_full:Failed:$fail: `date`" >> ${testpath}fail.tmp
            echo "CFINT_full:Failed:$fail: `date`" >> ${testpath}status.tmp
        fi
    fi  &

    if ((($testtimeleft < 498  ))); then
        echo        "Drive Tests INT FLASH 1min: `date`"  >> ${testpath}status.tmp
        if (${dcheckpri} dcheck -q -b 20000 /dev/cfint0  > ${testpath}cfint_1min.tmp) then (echo "CFINT_1min:passed:$fail: `date`" >> ${testpath}status.tmp) else
            let fail+=1
            echo "CFINT_1min:Failed:$fail: `date`" >> ${testpath}fail.tmp
            echo "CFINT_1min:Failed:$fail: `date`" >> ${testpath}status.tmp
        fi

    fi  &
    let testtimeleft=testtime-SECONDS
    echo        "HD TESTs..." >> ${testpath}status.tmp
    if ((($testtimeleft > 2000)));  then

        echo        "Full Drive Tests Tests HD: `date`" >> ${testpath}status.tmp
        if (${dcheckpri} dcheck  -q /dev/hd0 > ${testpath}hd_full.tmp) then (echo "HD_full:passed:$fail: `date`" >> ${testpath}status.tmp) else
            let fail+=1
            echo "HD_full:Failed:$fail: `date`"  >> ${testpath}fail.tmp
            echo "HD_full:Failed:$fail: `date`"  >> ${testpath}status.tmp
        fi
    fi &
    if ((($testtimeleft < 1999  && $testtimeleft > 599))); then
        echo        "Drive Tests Tests HD 30min: `date`" >> ${testpath}status.tmp
        if (${dcheckpri} dcheck -q -r -b 200000  /dev/hd0 > ${testpath}hd_120min.tmp) then (echo "HD_120min:passed:$fail: `date`" >> ${testpath}status.tmp) else
            let fail+=1
            echo "HD_120min:Failed:$fail: `date`" >> ${testpath}fail.tmp
            echo "HD_120min:Failed:$fail: `date`" >> ${testpath}status.tmp
        fi
    fi &

    if ((($testtimeleft < 3599  && $testtime > 599))); then
        echo        "Drive Tests Tests HD 10min: `date`" >> ${testpath}status.tmp
        if (${dcheckpri} dcheck -q -r -b 50000  /dev/hd0 > ${testpath}hd_10min.tmp) then (echo "HD_10min:passed:$fail: `date`" >> ${testpath}status.tmp) else
            let fail+=1
            echo "HD_10min:Failed:$fail: `date`"  >> ${testpath}fail.tmp
            echo "HD_10min:Failed:$fail: `date`"  >> ${testpath}status.tmp
        fi
    fi &
    if ((($testtimeleft < 600 ))); then
        echo        "Drive Tests Tests HD 1min: `date`" >> ${testpath}status.tmp
        if (${dcheckpri} dcheck -q -r -b 20000 /dev/hd0  > ${testpath}hd_1min.tmp) then (echo "HD_1min:passed:$fail: `date`" >> ${testpath}status.tmp) else
            let fail+=1
            echo "HD_1min:Failed:$fail: `date`" >> ${testpath}fail.tmp
            echo "HD_1min:Failed:$fail: `date`" >> ${testpath}status.tmp
        fi

    fi  &
	echo        "Wait for Drive/Memory test to complete: `date`" >> ${testpath}status.tmp
	wait
	if  (  test -f ${testpath}fail.tmp )
	then
		let fail+=1
	 fi
	done
let testtime=SECONDS

if ((($fail > 0))) then
	echo "DRIVE:Failed"
	echo "DRIVE:Failed" > $failfile
	echo "Displaying all tests" >> $failfile
	cat ${testpath}fail.tmp >> $failfile
	cat ${testpath}status.tmp >> $failfile
	cat ${testpath}testvolts.tmp >> $failfile
	cat ${testpath}thermal.tmp >> $failfile
	cat ${testpath}dram_full.tmp >> $failfile
	cat ${testpath}cfext*.tmp >> $failfile
	cat ${testpath}cfint*.tmp >> $failfile
	cat ${testpath}hd*.tmp >> $failfile
	rm ${testpath}*.tmp > /dev/null 2>&1
else
	echo "DRIVE_TEST:Passed"
	echo "DRIVE_TEST:Passed" > $failfile
	rm ${testpath}*.tmp > /dev/null 2>&1
fi
echo	"Drive Tests completed: `date` Total test time: ${testtime}"
