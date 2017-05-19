################################################################################
#
# Module:      Check_5th_link.inc
#
# Author:      Joe White
#
# Descr:       Check FIC 5th link if enabled
#
# Version:    5.7  $Id: Check_5th_link.inc,v 1.1 2009/05/07 15:50:10 joe Exp $
#
# Changes:    Create 7/14/08
#
#
# Used By:

# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################

<Msg>		"Check Disco Problems..."
<TimeOut>	40


<Bypass>	$SW55thlinkSlot_gbl[1]
          <Msg>		"Slot 1 5th link on FIC..."
          <Send> pfeffa on 1 test pktloopbkn2trunk
          <wait>
          <CheckData> "PASS"
          <GetData>
</Bypass>

<Bypass> $SW55thlinkSlot_gbl[2]
          <Msg>		"Slot 2 5th link on FIC..."
          <Send> pfeffa on 2 test pktloopbkn2trunk
          <wait>
          <CheckData> "PASS"
          <GetData>
</Bypass>

<Bypass> $SW55thlinkSlot_gbl[3]
          <Msg>		"Slot 3 5th link on FIC..."
          <Send> pfeffa on 3 test pktloopbkn2trunk
          <wait>
          <CheckData> "PASS"
          <GetData>
</Bypass>

<Bypass> $SW55thlinkSlot_gbl[4]
          <Msg>		"Slot 4 5th link on FIC..."
          <Send> pfeffa on 4 test pktloopbkn2trunk
          <wait>
          <CheckData> "PASS"
          <GetData>
</Bypass>



#    if (pfeffa on 1 rd i2c fic tlv 03 | grep 01) then
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
