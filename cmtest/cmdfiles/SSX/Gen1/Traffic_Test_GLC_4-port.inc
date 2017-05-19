################################################################################
#
# Module:      Traffic_Test_GLC_4-port.inc
#
# Author:      Joe White
#
# Descr:       Include for Bench_GLC.dat
#
# Version:    5.7  $Id: Traffic_Test_GLC_4-port.inc,v 1.7 2009/05/07 15:50:10 joe Exp $
#
# Changes:    Added <CheckData>  12/05/05
#			  Backward compatabe to 12/13/06 Image 10/18/07
#			  Updated with Laynes new tests. Old tests obsoleted
#
# Used By:
#				Bench_GLC.dat
#				Bench_Test_GLC.inc
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
<Msg>		"Setup 4 Port Traffic Test..."
<Prompt>	"#"
<Timeout>	20

<Msg>		"Clear Counters"
<Send>		"pfeffa sho mib"
<Wait>

<Prompt>	"#"
<TimeOut>	120

<Msg>	'Test SW5 to IXF to N2 Loopback'
<Send>	'pfeffa test pktloopbkn2links4'
<Wait>
<CheckData> "Packet Loop Test: Disco to SW5 to IXF to N2 and back: PASSED"
<GetData>
<TimeOut>	30

<Bypass>	$SW55thlink_gbl
 		<Msg>	'Test SW5 to IXF to N2 Loopback Trunking mode'
		<Send>	'pfeffa test pktloopbkn2trunk'
		<Wait>
		<CheckData> "Disco to Cavium Nitrox Link Trunk Test: PASSED"
		<GetData>
</Bypass>

<Msg>	'Test SW5 to IXF to N2 to SFP Loopback'
<Send>	'pfeffa test pktloopbksfpn2'
<Wait>
<CheckData> "Packet Loop Test: Disco to SW5 to IXF to SFP via N2: PASSED"
<GetData>

<Msg>	'Test SW5 to IXF to N2 to IXP Loopback'
<Send>	'pfeffa test pktloopbkixpfic'
<Wait>
<CheckData> "Disco to IXP Link Test: PASSED"
<GetData>

<Msg>	'Test SW5 to IXF to N2 to IXP to SFP Loopback'
<Send>	'pfeffa test pktloopbksfpixp'
<Wait>
<CheckData> "Disco to SFP Link Test: PASSED"
<GetData>




#<Msg>	'Enable ports and Leds'
##<Send> 'pfeffa test link dis 2 sw5'
##<Wait>
##<CheckData>    'PASS'
##Disable ports 8 and 9 change 3ff to ff **
#<Send>  'pfeffa  wr ixf 500 ff'
#<Wait>
##Enable LEDs - Link LED enable
#<Send>      "pfeffa wr ixf 502 3ff"
#<Wait>
##Enable LEDs - LED Control
#<Send>      "pfeffa wr ixf 50A 3ff"
#<Wait>
##Enable LEDs - LED Control
#<Send>      "pfeffa wr ixf 509 3"
#<Wait>
##Enable LEDs - LED Fault Disable
#<Send>      "pfeffa wr ixf 50A 3ff"
#<Wait>
##Enable LEDs - CPLD Enable
#<Send>      "pfeffa w8 f4000041 f"
#<Wait>
#<Msg>   'Test link from SW5 port 23 to N2 port 36 and back'
#<Send>  'pfeffa  set n2 loopback'
#<Wait>
#<Send>  'pfeffa  set sw5 0 pve 0 17'
#<Wait>
#<Send>  'pfeffa  set sw5 17 pve 0 0'
#<Wait>
#<Send>  'pfeffa  test link dis 2 as-is'
#<Wait>
#<GetData>
#<CheckData> 'PASS'
#<Send>  'pfeffa  clear sw5 17 pve'
#<Wait>
#<Msg>   'Test link from SW5 port 22 to N2 port 37 and back'
#<Send>  'pfeffa  set sw5 0 pve 0 16'
#<Wait>
#<Send>  'pfeffa  set sw5 16 pve 0 0'
#<Wait>
#<Send>  'pfeffa  test link dis 2 as-is'
#<Wait>
#<GetData>
#<CheckData> 'PASS'
#<Send>  'pfeffa  clear sw5 16 pve'
#<Wait>
#<Msg>   'Test link from SW5 port 23 to SFP port 0 and back'
#<Send>  'pfeffa  set sw5 0 pve 0 17'
#<Wait>
#<Send>  'pfeffa  set sw5 17 pve 0 0'
#<Wait>
#<Send>  'pfeffa  set n2 cut 0 36 32'
#<Wait>
#<Send>  'pfeffa  set n2 cut 1 32 36'
#<Wait>
#<Send>  'pfeffa  test link dis 2 as-is'
#<Wait>
#<GetData>
#<CheckData> 'PASS'
#<Send>  'pfeffa  clear sw5 17 pve'
#<Wait>
#<Msg>   'Test link from SW5 port 22 to SFP port 1 and back'
#<Send>  'pfeffa  set sw5 0 pve 0 16'
#<Wait>
#<Send>  'pfeffa  set sw5 16 pve 0 0'
#<Wait>
#<Send>  'pfeffa  set n2 cut 0 37 33'
#<Wait>
#<Send>  'pfeffa  set n2 cut 1 33 37'
#<Wait>
#<Send>  'pfeffa  test link dis 2 as-is'
#<Wait>
#<GetData>
#<CheckData> 'PASS'
#<Send>  'pfeffa  clear sw5 16 pve'
#<Wait>
## extensions for 4-port board
#<Msg>   'Test link from SW5 port 21 to N2 port 38 and back'
#<Send>  'pfeffa  set n2 loopback'
#<Wait>
#<Send>  'pfeffa  set sw5 0 pve 0 15'
#<Wait>
#<Send>  'pfeffa  set sw5 15 pve 0 0'
#<Wait>
#<Send>  'pfeffa  test link dis 2 as-is'
#<Wait>
#<GetData>
#<CheckData> 'PASS'
#<Send>  'pfeffa  clear sw5 15 pve'
#<Wait>
#<Msg>   'Test link from SW5 port 20 to N2 port 39 and back'
#<Send>  'pfeffa  set sw5 0 pve 0 14'
#<Wait>
#<Send>  'pfeffa  set sw5 14 pve 0 0'
#<Wait>
#<Send>  'pfeffa  test link dis 2 as-is'
#<Wait>
#<GetData>
#<CheckData> 'PASS'
#<Send>  'pfeffa  clear sw5 14 pve'
#<Wait>
##! DON'T DO THESE ON 2-PORT BOARD
#<Msg>   'test link from SW5 port 21 to SFP port 3 and back'
#<Send>  'pfeffa  set sw5 0 pve 0 15'
#<Wait>
#<Send>  'pfeffa  set sw5 15 pve 0 0'
#<Wait>
#<Send>  'pfeffa  set n2 cut 0 38 34'
#<Wait>
#<Send>  'pfeffa  set n2 cut 1 34 38'
#<Wait>
#<Send>  'pfeffa  test link dis 2 as-is'
#<Wait>
#<GetData>
#<CheckData> 'PASS'
#<Send>  'pfeffa  clear sw5 15 pve'
#<Wait>
#<Msg>   'Test link from SW5 port 20 to SFP port 4 and back'
#<Send>  'pfeffa  set sw5 0 pve 0 14'
#<Wait>
#<Send>  'pfeffa  set sw5 14 pve 0 0'
#<Wait>
#<Send>  'pfeffa  set n2 cut 0 39 35'
#<Wait>
#<Send>  'pfeffa  set n2 cut 1 35 39'
#<Wait>
#<Send>  'pfeffa  test link dis 2 as-is'
#<Wait>
#<GetData>
#<CheckData> 'PASS'
#<Send>  'pfeffa  clear sw5 14 pve'
#<Wait>
#<Send>  'pfeffa sho mib'
#<Wait>
#<GetData>
#<Msg>   'Check: disco port 0x2'
#<CheckData> 'disco port 0x2'
#<CheckData> '              7947000              .*gBytesRx'
#<CheckData> '                 9000              .*gFramesRx'
#<CheckData> '                 4500              .*sizeTo127'
#<CheckData> '                 9000              .*sizeToMax'
#<CheckData> '              7947000              .*gBytesTx'
#<CheckData> '                 9000              .*gFramesTx'
## varies <CheckData>    '                   62                       gFcRx'
#<Msg>   'Check: dx-sw5 port 0x0'
#<CheckData> 'dx-sw5 port 0x0'
#<CheckData> '              7947000               .*gBytesRxLo'
#<CheckData> '                 9000               .*gUcastRx'
#<CheckData> '                 4500               .*sizeTo127'
#<CheckData> '                 9000               .*sizeToMax'
#<CheckData> '              7947000               .*gBytesTxLo'
#<CheckData> '                 9000               .*gUcastTx'
#<Msg>   'Check: dx-sw5 port 0x14'
#<CheckData> "dx-sw5 port 0x14"
#<CheckData> '              1766000               .*gBytesRxLo'
#<CheckData> '                 2000               .*gUcastRx'
#<CheckData> '                 1000               .*sizeTo127'
#<CheckData> '                 2000               .*sizeToMax'
#<CheckData> '              1766000               .*gBytesTxLo'
#<CheckData> '                 2000               .*gUcastTx'
#<Msg>   'Check: dx-sw5 port 0x15'
#<CheckData> "dx-sw5 port 0x15"
#<CheckData> '              1766000               .*gBytesRxLo'
#<CheckData> '                 2000               .*gUcastRx'
#<CheckData> '                 1000               .*sizeTo127'
#<CheckData> '                 2000               .*sizeToMax'
#<CheckData> '              1766000               .*gBytesTxLo'
#<CheckData> '                 2000               .*gUcastTx'
#<Msg>   'Check: dx-sw5 port 0x16'
#<CheckData> "dx-sw5 port 0x16"
#<CheckData> '              1766000               .*gBytesRxLo'
#<CheckData> '                 2000               .*gUcastRx'
#<CheckData> '                 1000               .*sizeTo127'
#<CheckData> '                 2000               .*sizeToMax'
#<CheckData> '              1766000               .*gBytesTxLo'
#<CheckData> '                 2000               .*gUcastTx'
#<Msg>   'Check: dx-sw5 port 0x17'
#<CheckData> "dx-sw5 port 0x17"
#<CheckData> '              1766000               .*gBytesRxLo'
#<CheckData> '                 2000               .*gUcastRx'
#<CheckData> '                 1000               .*sizeTo127'
#<CheckData> '                 2000               .*sizeToMax'
#<CheckData> '              1766000               .*gBytesTxLo'
#<CheckData> '                 2000               .*gUcastTx'
#<Msg>   'Check: ixf port 0x0'
#<CheckData> "ixf port 0x0"
#<CheckData> '               883000             RxOctetsTotalOK'
#<CheckData> '                 1000                   RxUcPckts'
#<CheckData> '                  250               RxPkts65to127'
#<CheckData> '                  500            RxPkts1024to1518'
#<CheckData> '               883000             TxOctetsTotalOK'
#<CheckData> '                 1000                   TxUcPckts'
#<CheckData> '                  250               TxPkts65to127'
#<CheckData> '                  500            TxPkts1024to1518'
#<Msg>   'Check: ixf port 0x1'
#<CheckData> "ixf port 0x1"
#<CheckData> '               883000             RxOctetsTotalOK'
#<CheckData> '                 1000                   RxUcPckts'
#<CheckData> '                  250               RxPkts65to127'
#<CheckData> '                  500            RxPkts1024to1518'
#<CheckData> '               883000             TxOctetsTotalOK'
#<CheckData> '                 1000                   TxUcPckts'
#<CheckData> '                  250               TxPkts65to127'
#<CheckData> '                  500            TxPkts1024to1518'
#<Msg>   'Check: ixf port 0x2'
#<CheckData> "ixf port 0x2"
#<CheckData> '               883000             RxOctetsTotalOK'
#<CheckData> '                 1000                   RxUcPckts'
#<CheckData> '                  250               RxPkts65to127'
#<CheckData> '                  500            RxPkts1024to1518'
#<CheckData> '               883000             TxOctetsTotalOK'
#<CheckData> '                 1000                   TxUcPckts'
#<CheckData> '                  250               TxPkts65to127'
#<CheckData> '                  500            TxPkts1024to1518'
#<Msg>   'Check: ixf port 0x3'
#<CheckData> "ixf port 0x3"
#<CheckData> '               883000             RxOctetsTotalOK'
#<CheckData> '                 1000                   RxUcPckts'
#<CheckData> '                  250               RxPkts65to127'
#<CheckData> '                  500            RxPkts1024to1518'
#<CheckData> '               883000             TxOctetsTotalOK'
#<CheckData> '                 1000                   TxUcPckts'
#<CheckData> '                  250               TxPkts65to127'
#<CheckData> '                  500            TxPkts1024to1518'
#<Msg>   'Check: ixf port 0x4'
#<CheckData> "ixf port 0x4"
#<CheckData> '              1766000             RxOctetsTotalOK'
#<CheckData> '                 2000                   RxUcPckts'
#<CheckData> '                  500               RxPkts65to127'
#<CheckData> '                 1000            RxPkts1024to1518'
#<CheckData> '              1766000             TxOctetsTotalOK'
#<CheckData> '                 2000                   TxUcPckts'
#<CheckData> '                  500               TxPkts65to127'
#<CheckData> '                 1000            TxPkts1024to1518'
#<Msg>   'Check: ixf port 0x5'
#<CheckData> "ixf port 0x5"
#<CheckData> '              1766000             RxOctetsTotalOK'
#<CheckData> '                 2000                   RxUcPckts'
#<CheckData> '                  500               RxPkts65to127'
#<CheckData> '                 1000            RxPkts1024to1518'
#<CheckData> '              1766000             TxOctetsTotalOK'
#<CheckData> '                 2000                   TxUcPckts'
#<CheckData> '                  500               TxPkts65to127'
#<CheckData> '                 1000            TxPkts1024to1518'
#<Msg>   'Check: ixf port 0x6'
#<CheckData> "ixf port 0x6"
#<CheckData> '              1766000             RxOctetsTotalOK'
#<CheckData> '                 2000                   RxUcPckts'
#<CheckData> '                  500               RxPkts65to127'
#<CheckData> '                 1000            RxPkts1024to1518'
#<CheckData> '              1766000             TxOctetsTotalOK'
#<CheckData> '                 2000                   TxUcPckts'
#<CheckData> '                  500               TxPkts65to127'
#<CheckData> '                 1000            TxPkts1024to1518'
#<Msg>   'Check: ixf port 0x7'
#<CheckData> "ixf port 0x7"
#<CheckData> '              1766000             RxOctetsTotalOK'
#<CheckData> '                 2000                   RxUcPckts'
#<CheckData> '                  500               RxPkts65to127'
#<CheckData> '                 1000            RxPkts1024to1518'
#<CheckData> '              1766000             TxOctetsTotalOK'
#<CheckData> '                 2000                   TxUcPckts'
#<CheckData> '                  500               TxPkts65to127'
#<CheckData> '                 1000            TxPkts1024to1518'


