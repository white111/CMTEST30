#************************************************************************************************##
#
# Module:      Get_Card_Data.inc
#
# Author:      Joe White
#
# Descr:       Call to collect debug data stored on the HD
#
# Version:    1.7 $Id: Wait_Card_Stoke.inc,v 1.1 2011/12/12 22:54:27 joe Exp $
#
# Changes:    Added <GetData>   11/02/12/05/05
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
#************************************************************************************************##
# Done at the QNX level
<Msg>		"Getting Debug Data"
<prompt>	"^#"
<timeout>	30
# IMC  Slot 0
			 <send>	"echo "***************  IMC Slot 0 ******************" > /hd/dump/slot0/carddata.txt"
			 <wait>
             <Send> "on -f /net/nv-0-0 pfeffa show volts >> /hd/dump/slot0/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-0-0 pfeffa show therm >> /hd/dump/slot0/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-0-0 pfeffa show cpld >> /hd/dump/slot0/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-0-0 pfeffa fabd -l >> /hd/dump/slot0/carddata.txt"
             <Wait>
             <Send> "ls /net >> /hd/dump/slot0/carddata.txt"
             <Wait>
             <Send> "ls -al hdp >> /hd/dump/slot0/carddata.txt"
             <Wait>
             <Send> "cat /hd/dump/slot0/Onscript_slot0.txt | tail >> /hd/dump/slot0/carddata.txt"
             <Wait>
             <Send> "sloginfo >> /hd/dump/slot0/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-0-0 pidin >> /hd/dump/slot0/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-0-0 nicinfo >> /hd/dump/slot0/carddata.txt"
             <Wait>
#IMC Slot 0

<Bypass>    $Slot_INST_1_IMC_GBL
			 <send>	"echo "***************  IMC Slot 1 ******************" > /hd/dump/slot1/carddata.txt"
			 <wait>
             <Send> "on -f /net/nv-1-0 pfeffa show volts >> /hd/dump/slot1/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-1-0 pfeffa show therm >> /hd/dump/slot1/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-1-0 pfeffa show cpld >> /hd/dump/slot1/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-1-0 pfeffa fabd -l >> /hd/dump/slot1/carddata.txt"
             <Wait>
             <Send> "cat /hd/dump/slot0/Onscript_slot1.txt | tail >> /hd/dump/slot1/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-1-0 sloginfo >> /hd/dump/slot1/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-1-0 pidin >> /hd/dump/slot1/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-1-0 nicinfo >> /hd/dump/slot1/carddata.txt"
             <Wait>
         </Bypass>

#</Bypass>

<Bypass>	$Slot_INST_2_GBL
 			 <send>	"echo "***************  GLC Slot 2 ******************" > /hd/dump/slot2/carddata.txt"
			 <wait>
             <Send> "on -f /net/nv-2-0 pfeffa show volts >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pfeffa show therm >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pfeffa show cpld >> /hd/dump/slot2/carddata.txt"
             <Wait>
  			 <send>	"echo "***************  GLC Slot 2 Logs ******************" >> /hd/dump/slot2/carddata.txt"
			 <wait>
             <Send> "cat /hd/dump/slot0/Onscript_slot2.txt | tail >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-2 | tail >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-2-inactive | tail >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-xs-2 | tail >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-xs-2-inactive | tail >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 sloginfo >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pidin >> /hd/dump/slot2/carddata.txt"
             <Wait>
			 <send>	"echo "***************  GLC Slot 2 fast path ******************" >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 nicinfo >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 fabd -l >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pfeffa show ixf mib >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pfeffa show sw5 mib-cntrs >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pfeffa show n2 count >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pfeffa show n2 prob >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pfeffa show n2 spi >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pfeffa show n2 bmi >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pfeffa read n2 win 5800 >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pfeffa read n2 win 5808 >> /hd/dump/slot2/carddata.txt"
             <Wait>
			 <send>	"echo "***************  GLC Disco ******************" >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pfeffa show disco prob >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pfeffa show disco inter >> /hd/dump/slot2/carddata.txt"
             <Wait>

</Bypass>
<Bypass>	$Slot_INST_3_GBL
 			 <send>	"echo "***************  GLC Slot 3 ******************" > /hd/dump/slot3/carddata.txt"
			 <wait>
             <Send> "on -f /net/nv-3-0 pfeffa show volts >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pfeffa show therm >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pfeffa show cpld >> /hd/dump/slot3/carddata.txt"
             <Wait>
  			 <send>	"echo "***************  GLC Slot 3 Logs ******************" >> /hd/dump/slot3/carddata.txt"
			 <wait>
             <Send> "cat /hd/dump/slot0/Onscript_slot3.txt | tail >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-3 | tail >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-3-inactive | tail >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-xs-3 | tail >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-xs-3-inactive | tail >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 sloginfo >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pidin >> /hd/dump/slot3/carddata.txt"
             <Wait>
			 <send>	"echo "***************  GLC Slot 3 fast path ******************" >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 nicinfo >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 fabd -l >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pfeffa show ixf mib >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pfeffa show sw5 mib-cntrs >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pfeffa show n2 count >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pfeffa show n2 prob >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pfeffa show n2 spi >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pfeffa show n2 bmi >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pfeffa read n2 win 5800 >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pfeffa read n2 win 5808 >> /hd/dump/slot3/carddata.txt"
             <Wait>
			 <send>	"echo "***************  GLC Disco ******************" >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pfeffa show disco prob >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pfeffa show disco inter >> /hd/dump/slot3/carddata.txt"
             <Wait>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
  			 <send>	"echo "***************  GLC Slot 4 ******************" > /hd/dump/slot4/carddata.txt"
			 <wait>
             <Send> "on -f /net/nv-4-0 pfeffa show volts >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pfeffa show therm >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pfeffa show cpld >> /hd/dump/slot4/carddata.txt"
             <Wait>
  			 <send>	"echo "***************  GLC Slot 4 Logs ******************" >> /hd/dump/slot4/carddata.txt"
			 <wait>
             <Send> "cat /hd/dump/slot0/Onscript_slot4.txt | tail >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-4 | tail >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-4-inactive | tail >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-xs-4 | tail >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-xs-4-inactive | tail >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 sloginfo >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pidin >> /hd/dump/slot4/carddata.txt"
             <Wait>
			 <send>	"echo "***************  GLC Slot 4 fast path ******************" >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 nicinfo >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 fabd -l >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pfeffa show ixf mib >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pfeffa show sw5 mib-cntrs >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pfeffa show n2 count >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pfeffa show n2 prob >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pfeffa show n2 spi >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pfeffa show n2 bmi >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pfeffa read n2 win 5800 >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pfeffa read n2 win 5808 >> /hd/dump/slot4/carddata.txt"
             <Wait>
			 <send>	"echo "***************  GLC Disco ******************" >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pfeffa show disco prob >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pfeffa show disco inter >> /hd/dump/slot4/carddata.txt"
             <Wait>
</Bypass>


