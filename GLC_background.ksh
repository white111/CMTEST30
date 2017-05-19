################################################################################
#
# Module:      KSH Script Running memory tests
#
# Author:      Joe White
#
# Descr:       Script run on each GLC during BI
#
# Version:    3.4   $Id: GLC.ksh,v 1.1 2008/03/11 18:29:45 joe Exp $
#
# Changes:    Created 12/15/05
#			  Tests removed that interfere with snake test 02/22/06
#			  Removed Bank 3 tests, intermittent fails during snake test
#			  Added traffic and nontraffic tests, fixed testtime bug
#			  Added a Show volts after a test volts failure
#			  Added TCAM and Shasera tests, Shasera tests for cardtype greater than 1
#			  TCAM and Sahasra tests now run via pfeffa as on laynes build 1/3/07
#			  Moved Sahasra to run with out traffic, Sahasra test causes tcam to fail on next test, reboot required to clear
#			  Upadted for 12/1/07 diags
#			  01/29/06 diags 1/29/or later added dram test for avaialble system memory
#			  07/08/08 Add Fith link testing 0x19
#
# Used By:
#				Chassis_BI.dat
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
Ver='v3.5 7/8/2008'; # Added IXP fith link test
CVS_Ver=' [ CVS: $Id: GLC.ksh,v 1.1 2008/03/11 18:29:45 joe Exp $ ]';
Version=$Ver$CVS_Ver;
# Command line
#
# on -f /net/nv-2-0 ksh /net/nv-0-0/hd/dump/slot0/onscript.txt 60  2  1 > /hd/dump/slot0/temp.txt 2>&1 &
# 1 = testtime 2 = slot 3 = non traffic test
#print "$@"
# Fail flag
set -a
integer fail=0
export fail
failfile=onfile.txt
failpath=/net/nv-0-0/hd/dump/slot
integer slot=0
integer sahasra=0


# test time variable
integer testtime=$1
integer testtimeleft=$1
integer loopcount=0
slot=$2
testpath=$failpath$slot/
nontraffic=$3
pfeffapri='on -p6'

failfile=$failpath$slot/onfile.txt
#echo Testtime=$testtime or $1
#echo logpath=$failpath slot $slot
echo Fails logged to $failfile
echo "Started ${0} ${@} Memory Tests at `date` \n ${Version}"
rm ${testpath}*.tmp > /dev/null 2>&1
   #if  ( ! test -f ${testpath}fail.tmp )  then ((fail+=1)) fi
while ((((${testtime} - SECONDS) > 10)  && (${fail}==0))) do
	let testtimeleft=testtime-SECONDS
	let loopcount+=1
	echo		"Started Loop ${loopcount} Time left: ${testtimeleft}..."  > ${testpath}status.tmp
	echo		"Memory Tests Started Loop ${loopcount} Time left: ${testtimeleft}..."
	echo 		"Remove tempfiles from ${testpath}" >> ${testpath}status.tmp
	rm ${failfile} > /dev/null 2>&1
	rm ${testpath}*.tmp > /dev/null 2>&1
	echo		"Memory tests V${Version} started: `date`" >> ${testpath}status.tmp
	echo		"Test Voltage" >> ${testpath}status.tmp
	${pfeffapri} pfeffa test volts > ${testpath}testvolts.tmp  2>&1
	if (grep -q "PASS" ${testpath}testvolts.tmp) then
		echo "Testvolts:passed:$fail" >> ${testpath}status.tmp
	else
		let fail+=1
		echo "Testvolts:Failed:$fail" >> ${testpath}status.tmp
		pfeffa show volts >> ${testpath}status.tmp
	fi
    echo        "Get Thermal Data" >> ${testpath}status.tmp
    ${pfeffapri} pfeffa show thermal > ${testpath}thermal.tmp  2>&1
    if (grep -q "Tppci.*=.*[2-7][0-9].*C" ${testpath}thermal.tmp) then
        echo "Temp_TPPCI:passed:$fail" >> ${testpath}status.tmp
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
        echo "Temp_TppcRem2:passed:$fail" >> ${testpath}status.tmp
    else
        let fail+=1
        echo "Temp_TppcRem2:Failed:$fail" >> ${testpath}status.tmp
    fi
    if (grep -q "TppcRem1.*=.*[2-7][0-9].*C" ${testpath}thermal.tmp) then
        echo "Temp_TppcRem1:passed:$fail" >> ${testpath}status.tmp
    else
        let fail+=1
        echo "Temp_TppcRem1:Failed:$fail"  >> ${testpath}status.tmp
    fi
    if (grep -q "Tixpi.*=.*[2-7][0-9].*C" ${testpath}thermal.tmp) then
        echo "Temp_Tixpi:passed:$fail" >> ${testpath}status.tmp
    else
        let fail+=1
        echo "Temp_Tixpi:Failed:$fail" >> ${testpath}status.tmp
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
		#Emergency shutdown from IMC slot 0
		sleep 1
		on -p3r -f /net/nv-0-0 slay -f devb-mvSata >> /dev/null  2>&1
		#slay -f devb-eide >> /dev/null  2>&1
	   	on -p3r -f /net/nv-0-0 slay -f storaged  >> /dev/null  2>&1
		sleep 1 >> /dev/null   2>&1
		${pfeffapri} pfeffa on 0 w8 f4000042 1 >> /dev/null  2>&1
    fi
    if (grep -q "Toutlet.*=.*[2-5][0-9].*C" ${testpath}thermal.tmp) then
        echo "Temp_Toutlet:passed:$fail" >> ${testpath}status.tmp
    else
        let fail+=1
        echo "Temp_Toutlet:Failed:$fail" >> ${testpath}status.tmp
    fi
#    if (pfeffa rd i2c fic tlv 03 | grep 01) then
#        echo        "Test 5th IXP link 0x19: `date`"  >> ${testpath}status.tmp
#        ${pfeffapri} pfeffa test discoton2linktrunk > ${testpath}ixplink.tmp  2>&1
#        if (grep -q "PASS" ${testpath}ixplink.tmp) then
#            echo "ixplink:passed:$fail: `date`" >> ${testpath}status.tmp
#        else
#            let fail+=1
#            echo "ixplink:Failed:$fail: `date`" >> ${testpath}fail.tmp
#            echo "ixplink:Failed:$fail: `date`" >> ${testpath}status.tmp
#        fi
#        pfeffa test dram clear_ecc
#    fi
    let testtimeleft=testtime-SECONDS
       #&&  $loopcount > 2
    if ((($testtimeleft > 600  )));  then
        echo        "Test avaialble system memory: `date` : `pidin info`"  >> ${testpath}status.tmp
        ${pfeffapri} pfeffa test dram > ${testpath}dram_full.tmp  2>&1
        if (grep -q "PASS" ${testpath}dram_full.tmp) then
            echo "dram_full:passed:$fail: `date`" >> ${testpath}status.tmp
        else
            let fail+=1
            echo "dram_full:Failed:$fail: `date`" >> ${testpath}fail.tmp
            echo "dram_full:Failed:$fail: `date`" >> ${testpath}status.tmp
        fi
    fi   &
               #||  $loopcount < 2
    if ((($testtimeleft < 600  )));  then
        echo        "Test avaialble system memory random: `date` : `pidin info`"  >> ${testpath}status.tmp
        ${pfeffapri} pfeffa test dram random > ${testpath}dram_full.tmp 2>&1
        if (grep -q "PASS" ${testpath}dram_full.tmp) then
            echo "dram_random:passed:$fail: `date`" >> ${testpath}status.tmp
        else
            let fail+=1
            echo "dram_random:Failed:$fail: `date`" >> ${testpath}fail.tmp
            echo "dram_random:Failed:$fail: `date`" >> ${testpath}status.tmp
        fi
    fi  &
            let testtimeleft=testtime-SECONDS
    #fuinit/ ixp running  needed for these tests
    if (((${nontraffic}==0))) then
        echo        "TCAM TEST..." >> ${testpath}status.tmp
        #qtalk -y -c 3f -m /dev/ser2,'~xstest test|~~~~' -l ${testpath}tcam.tmp > ${testpath}tcam.tmp
        ${pfeffapri} pfeffa test tcam > ${testpath}tcam.tmp
        if (grep -iq -e "FAIL" -e "ERROR" ${testpath}tcam.tmp)then
            let fail+=1
            echo "TCAM:Failed:$fail" >> ${testpath}status.tmp
            echo "TCAM:Failed:$fail" >> ${testpath}fail.tmp
        else
            echo "TCAM:passed:$fail" >> ${testpath}status.tmp

        fi
    fi &
    if (((${nontraffic}==1))) then
        # Shasera test will cause the next Tcam test to fail,  this can only be run one time, reboot needed to clear
        if (pfeffa r8 F4000000 | grep -in -e "F4000000   02" ) then
            let sahsera+=1
            echo        " Sahasra TEST..." >> ${testpath}status.tmp
            #qtalk -y -c 3f -m /dev/ser2,'~diag_ref_app20k -loop 2|~~~~' > ${testpath}sahasra.tmp
            ${pfeffapri} pfeffa test sahasra > ${testpath}sahasra.tmp
            if (grep -iq "Passed" ${testpath}sahasra.tmp) then (echo "SAHASRA:passed:$fail" >> ${testpath}status.tmp) else
                let fail+=1
                echo "SAHASRA:Failed:$fail" >> ${testpath}fail.tmp
                echo "SAHASRA:Failed:$fail" >> ${testpath}status.tmp
            fi
        fi

        echo        "IXP RAM Tests..." >> ${testpath}status.tmp


        #Interfiers with Snake test
        echo        "IXP DDR..." >> ${testpath}status.tmp
        ${pfeffapri} ixtest mt -p4 > ${testpath}ixtest_mt.tmp
        if (grep -q "Passed" ${testpath}ixtest_mt.tmp) then (echo "Ixtest_mt_DRAM:passed:$fail" >> ${testpath}status.tmp) else
            let fail+=1
            echo "IxTest_mt_DRAM:Failed:$fail" >> ${testpath}fail.tmp
            echo "IxTest_mt_DRAM:Failed:$fail" >> ${testpath}status.tmp
        fi
#        #Interfiers with Snake test
#        echo        "IXP Full DDR..." >> ${testpath}status.tmp
#        ${pfeffapri} ixtest mt -p4 0 10000000 > ${testpath}ixtest_mt.tmp
#        if (grep -q "Passed" ${testpath}ixtest_mt.tmp) then (echo "Ixtest_mt_DRAM:passed:$fail" >> ${testpath}status.tmp) else
#            let fail+=1
#            echo "IxTest_mt_DRAM:Failed:$fail" >> ${testpath}fail.tmp
#            echo "IxTest_mt_DRAM:Failed:$fail" >> ${testpath}status.tmp
#        fi
        #Interfiers with Snake test
        echo        "IXP SRAM Bank 0..."  >> ${testpath}status.tmp
        ${pfeffapri} ixtest mt -s0 -p4 > ${testpath}ixtest_mt_bank_0.tmp
        if (grep -q "Passed" ${testpath}ixtest_mt_bank_0.tmp) then (echo "Ixtest_Bank0:passed:$fail" >> ${testpath}status.tmp) else
            let fail+=1
            echo "Ixtest_Bank0:Failed:$fail" >> ${testpath}fail.tmp
            echo "Ixtest_Bank0:Failed:$fail" >> ${testpath}status.tmp
        #Reinitialize memory after destructive test
        ixtest -I > ${testpath}ixtest_I.tmp
        fi
    fi &
    (
    	echo        "IXP SRAM Bank 1..." >> ${testpath}status_sram.tmp
    	${pfeffapri} ixtest mt -s1 -p4 > ${testpath}ixtest_mt_bank_1.tmp
    	if (grep -q "Passed" ${testpath}ixtest_mt_bank_1.tmp) then (echo "Ixtest_Bank1:passed:$fail" >> ${testpath}status_sram.tmp) else
        	let fail+=1
        	echo "Ixtest_Bank1:Failed:$fail" >> ${testpath}fail.tmp
        	echo "Ixtest_Bank1:Failed:$fail" >> ${testpath}status_sram.tmp
    	fi
    	echo        "IXP SRAM Bank 2 Bottom..." >> ${testpath}status_sram.tmp
    	${pfeffapri} ixtest mt -s2 -p4 0 0x7ffff0 > ${testpath}ixtest_mt_bank_2B.tmp
    	if (grep -q "Passed" ${testpath}ixtest_mt_bank_2B.tmp) then (echo "Ixtest_Bank2B:passed:$fail" >> ${testpath}status_sram.tmp) else
        	let fail+=1
        	echo "Ixtest_Bank2B:Failed:$fail" >> ${testpath}status_sram.tmp
        	echo "Ixtest_Bank2B:Failed:$fail" >> ${testpath}fail.tmp
    	fi
    	echo        "IXP SRAM Bank 2 TOP..."  >> ${testpath}status_sram.tmp
    	${pfeffapri} ixtest mt -s2 -p4 0x800000 0x7ffff0 > ${testpath}ixtest_mt_bank_2T.tmp
    	if (grep -q "Passed" ${testpath}ixtest_mt_bank_2T.tmp) then (echo "Ixtest_Bank2T:passed:$fail" >> ${testpath}status_sram.tmp) else
        	let fail+=1
        	echo "Ixtest_Bank2T:Failed:$fail" >> ${testpath}fail.tmp
        	echo "Ixtest_Bank2T:Failed:$fail" >> ${testpath}status_sram.tmp
    	fi
    	echo        "IXP SRAM Bank 3 Bottom..."  >> ${testpath}status_sram.tmp
    	${pfeffapri} ixtest mt -s3 -p4 0 0x7ffff0 > ${testpath}ixtest_mt_bank_3B.tmp
    	if (grep -q "Passed" ${testpath}ixtest_mt_bank_3B.tmp) then (echo "Ixtest_Bank3B:passed:$fail" >> ${testpath}status_sram.tmp) else
        	let fail+=1
        	echo "Ixtest_Bank3B:Failed:$fail" >> ${testpath}fail.tmp
        	echo "Ixtest_Bank3B:Failed:$fail" >> ${testpath}status_sram.tmp
    	fi
    	echo        "IXP SRAM Bank 3 Top..." >> ${testpath}status_sram.tmp
    	${pfeffapri} ixtest mt -s3 -p4 0x800000 0x7ffff0 > ${testpath}ixtest_mt_bank_3T.tmp
    	if (grep -q "Passed" ${testpath}ixtest_mt_bank_3T.tmp) then (echo "Ixtest_Bank3T:passed:$fail" >> ${testpath}status_sram.tmp) else
        	let fail+=1
        	echo "Ixtest_Bank3T:Failed:$fail" >> ${testpath}fail.tmp
        	echo "Ixtest_Bank3T:Failed:$fail" >> ${testpath}status_sram.tmp
    	fi
    	let testtimeleft=testtime-SECONDS
    ) &
    if (((${nontraffic}==0))) then
    if ((($testtimeleft > 2199)));  then
        echo        "Test Cavium DDR Core 0 Full memory test, about 1 hour: `date`" >> ${testpath}status.tmp
        ${pfeffapri} ddr_test 0 FFFFFFF 0 > ${testpath}Cav_ddr_full.tmp
        if (grep -q "PASS" ${testpath}Cav_ddr_full.tmp) then (echo "FUll_CaviumDDR:passed:$fail" >> ${testpath}status.tmp) else
            let fail+=1
            echo "Full_CaviumDDR:Failed:$fail" >> ${testpath}fail.tmp
            echo "Full_CaviumDDR:Failed:$fail" >> ${testpath}status.tmp
        fi
    fi
    if ((($testtimeleft < 2199  && $testtimeleft > 599))); then
        echo        "Test Cavium DDR Core 0 10 Min memory test" >> ${testpath}status.tmp
        ${pfeffapri} ddr_test 0 1000000 0  > ${testpath}Cav_ddr_10min.tmp
        ${pfeffapri} ddr_test 8000000 9000000 0 >> ${testpath}Cav_ddr_10min.tmp
        ${pfeffapri} ddr_test F000000 FFFFFFF 0 >> ${testpath}Cav_ddr_10min.tmp
        if (grep -q "PASS" ${testpath}Cav_ddr_10min.tmp) then (echo "10min_CaviumDDR:passed:$fail" >> ${testpath}status.tmp) else
            let fail+=1
            echo "10min_CaviumDDR:Failed:$fail" >> ${testpath}fail.tmp
            echo "10min_CaviumDDR:Failed:$fail" >> ${testpath}status.tmp
        fi
    fi

      if ((($testtimeleft < 600 ))); then
        echo        "Test Cavium DDR Core 0 1 Min memory test" >> ${testpath}status.tmp
        ${pfeffapri} ddr_test 0 100000 0 > ${testpath}Cav_ddr_1min.tmp
        ${pfeffapri} ddr_test 8800000 8900000 0 >> ${testpath}Cav_ddr_1min.tmp
        ${pfeffapri} ddr_test FE00000 FFFFFFF 0 >> ${testpath}Cav_ddr_1min.tmp
        if (grep -q "PASS" ${testpath}Cav_ddr_1min.tmp) then (echo "1min_CaviumDDR:passed:$fail" >> ${testpath}status.tmp) else
            let fail+=1
            echo "1min_CaviumDDR:Failed:$fail" >> ${testpath}fail.tmp
            echo "1min_CaviumDDR:Failed:$fail" >> ${testpath}status.tmp
        fi

      fi
    fi &
    echo        "Wait for Memory test to complete: `date`" >> ${testpath}status.tmp
	wait
	if  (  test -f ${testpath}fail.tmp )  then
		   echo        "Fail.tmp exist setting fail flag: `date`" >> ${testpath}status.tmp
		   let fail+=1
	 fi
done

let testtime=SECONDS
if ((($fail > 0))) then
	echo "Memory:Failed"
	echo "Memory:Failed" > $failfile
	echo "Displaying all tests" >> $failfile
	cat ${testpath}fail.tmp >> $failfile
	cat ${testpath}status*.tmp >> $failfile
	cat ${testpath}testvolts.tmp >> $failfile
	cat ${testpath}thermal.tmp >> $failfile
	cat ${testpath}ixplink.tmp >> $failfile
	cat ${testpath}dram_full.tmp >> $failfile
	cat ${testpath}tcam.tmp >> $failfile
	cat ${testpath}sahasra.tmp  >> $failfile
	cat ${testpath}ixtest_mt.tmp >> $failfile
	cat ${testpath}ixtest_mt_bank_0.tmp >> $failfile
	cat ${testpath}ixtest_mt_bank_1.tmp >> $failfile
	cat ${testpath}ixtest_mt_bank_2B.tmp >> $failfile
	cat ${testpath}ixtest_mt_bank_2T.tmp >> $failfile
	cat ${testpath}ixtest_mt_bank_3B.tmp >> $failfile
	cat ${testpath}ixtest_mt_bank_3T.tmp >> $failfile
	cat ${testpath}Cav_ddr_*.tmp >> $failfile
	#rm ${testpath}*.tmp  > /dev/null 2>&1
else
	echo "Memory:Passed"
	echo "Memory:Passed" > $failfile
	#rm ${testpath}*.tmp > /dev/null 2>&1
fi
echo	"Memory Tests completed: `date` Total test time: ${testtime}"

