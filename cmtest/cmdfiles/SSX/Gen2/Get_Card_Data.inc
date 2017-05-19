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
             <Send> "on -f /net/nv-0-0 pfeffa fabd -l >> /hd/dump/slot0/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-0-0 pfeffa show volts >> /hd/dump/slot0/carddata.txt"
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
             <Send> "on -f /net/nv-1-0 pfeffa fabd -l >> /hd/dump/slot1/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-1-0 pfeffa show volts >> /hd/dump/slot1/carddata.txt"
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
             <Send> "on -f /net/nv-2-0 xglcdiag tdnt ps >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag monitor voltage all >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag cpldshow >> /hd/dump/slot2/carddata.txt"
             <Wait>
  			 <send>	"echo "***************  GLC Slot 2 Logs ******************" >> /hd/dump/slot2/carddata.txt"
			 <wait>
             <Send> "cat /hd/dump/slot0/Onscript_slot2.txt | tail >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-2 | tail >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-2-inactive | tail >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-fu0-2 | tail >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-fu1-2 | tail >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-fu0-2-inactive | tail >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-fu1-2-inactive | tail >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 sloginfo >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 pidin >> /hd/dump/slot2/carddata.txt"
             <Send> "on -f /net/nv-2-0 xglcdiag monitor voltage all >> /hd/dump/slot2/carddata.txt"
             <Wait>
 			 <send>	"echo "***************  GLC Slot 2 VRM ******************" >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag npuvrm rb 0 0 >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag npuvrm rb 0 78 >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag npuvrm rw 0 79 >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag npuvrm rb 1 78 >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag npuvrm rw 1 79 >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag npuvrm rb 2 78 >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag npuvrm rw 2 79 >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag npuvrm rb 3 78 >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag npuvrm rw 3 79 >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag pwrstatus | grep -i ":" >> /hd/dump/slot2/carddata.txt"
             <Wait>
			 <send>	"echo "***************  GLC Slot 2 Switch ******************" >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 nicinfo >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag linkstatus >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag tdnt show counters NZ >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag tdnt show counter ErDisc >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag tdnt show error >> /hd/dump/slot2/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-2-0 xglcdiag tdnt show int >> /hd/dump/slot2/carddata.txt"
             <Wait>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
 			 <send>	"echo "***************  GLC Slot 3 ******************" > /hd/dump/slot3/carddata.txt"
			 <wait>
             <Send> "on -f /net/nv-3-0 xglcdiag tdnt ps >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag monitor voltage all >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag cpldshow >> /hd/dump/slot3/carddata.txt"
             <Wait>
			 <send>	"echo "***************  GLC Slot 3 Logs ******************" >> /hd/dump/slot3/carddata.txt"
			 <wait>
             <Send> "cat /hd/dump/slot0/Onscript_slot3.txt | tail >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-3 | tail >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-3-inactive | tail >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-fu0-3 | tail >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-fu1-3 | tail >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-fu0-3-inactive | tail >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-fu1-3-inactive | tail >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 sloginfo >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 pidin >> /hd/dump/slot3/carddata.txt"
             <Send> "on -f /net/nv-3-0 xglcdiag monitor voltage all >> /hd/dump/slot3/carddata.txt"
             <Wait>
 			 <send>	"echo "***************  GLC Slot 3 VRM ******************" >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag npuvrm rb 0 0 >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag npuvrm rb 0 78 >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag npuvrm rw 0 79 >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag npuvrm rb 1 78 >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag npuvrm rw 1 79 >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag npuvrm rb 2 78 >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag npuvrm rw 2 79 >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag npuvrm rb 3 78 >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag npuvrm rw 3 79 >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag pwrstatus | grep -i ":" >> /hd/dump/slot3/carddata.txt"
             <Wait>
			 <send>	"echo "***************  GLC Slot 3 Switch ******************" >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 nicinfo >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag linkstatus >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag tdnt show counters NZ >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag tdnt show counter ErDisc >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag tdnt show error >> /hd/dump/slot3/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-3-0 xglcdiag tdnt show int >> /hd/dump/slot3/carddata.txt"
             <Wait>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
 			 <send>	"echo "***************  GLC Slot 4 ******************" > /hd/dump/slot4/carddata.txt"
			 <wait>
             <Send> "on -f /net/nv-4-0 xglcdiag tdnt ps >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag monitor voltage all >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag cpldshow >> /hd/dump/slot4/carddata.txt"
             <Wait>
  			 <send>	"echo "***************  GLC Slot 4 Logs ******************" >> /hd/dump/slot4/carddata.txt"
			 <wait>
             <Send> "cat /hd/dump/slot0/Onscript_slot4.txt | tail >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-4 | tail >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-4-inactive | tail >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-fu0-4 | tail >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-fu1-4 | tail >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-fu0-4-inactive | tail >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "cat /hdp/glc-console-fu1-4-inactive | tail >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 sloginfo >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 pidin >> /hd/dump/slot4/carddata.txt"
             <Send> "on -f /net/nv-4-0 xglcdiag monitor voltage all >> /hd/dump/slot4/carddata.txt"
             <Wait>
 			 <send>	"echo "***************  GLC Slot 4 VRM ******************" >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag npuvrm rb 0 0 >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag npuvrm rb 0 78 >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag npuvrm rw 0 79 >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag npuvrm rb 1 78 >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag npuvrm rw 1 79 >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag npuvrm rb 2 78 >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag npuvrm rw 2 79 >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag npuvrm rb 3 78 >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag npuvrm rw 3 79 >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag pwrstatus | grep -i ":" >> /hd/dump/slot4/carddata.txt"
             <Wait>
			 <send>	"echo "***************  GLC Slot 4 Switch ******************" >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 nicinfo >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag linkstatus >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag tdnt show counters NZ >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag tdnt show counter ErDisc >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag tdnt show error >> /hd/dump/slot4/carddata.txt"
             <Wait>
             <Send> "on -f /net/nv-4-0 xglcdiag tdnt show int >> /hd/dump/slot4/carddata.txt"
             <Wait>
</Bypass>


