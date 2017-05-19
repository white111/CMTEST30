################################################################################
#
# Module:      Traffic_Test_GLC_2-port.inc
#
# Author:      Joe White
#
# Descr:       Include for Bench_GLC.dat
#
# Version:    6.1   $Id: Traffic_Test_GLC_2-port.inc,v 1.6 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Added <checkData> 12/05/05
#			  Upadeted for R1 release 010906
#             Backward compatabe to 12/13/06 Image 10/18/07
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
<Msg>		"Setup 2 Port Traffic Test..."
<Prompt>	"#"
<Timeout>	20

<Msg>		"Clear Counters"
<Send>		"pfeffa sho mib"
<Wait>

<Prompt>	"#"
<TimeOut>	5
<Msg>	'Enable ports and Leds'
<Send>	'pfeffa test link dis 2 sw5'
<Wait>
<CheckData>	'PASS'
#Disable ports 8 and 9 change 3ff to ff
<Send>	'pfeffa  wr ixf 500 ff'
<Wait>
#Enable LEDs - Link LED enable
<Send>		"pfeffa wr ixf 502 3ff"
<Wait>
#Enable LEDs - LED Control
<Send>		"pfeffa wr ixf 50A 3ff"
<Wait>
#Enable LEDs - LED Control
<Send>		"pfeffa wr ixf 509 3"
<Wait>
#Enable LEDs - LED Fault Disable
<Send>		"pfeffa wr ixf 50A 3ff"
<Wait>
#Enable LEDs - CPLD Enable
<Send>		"pfeffa w8 f4000041 f"
<Wait>
<Msg>	'Test link from SW5 port 23 to N2 port 36 and back'
<Send>	'pfeffa  set n2 loopback'
<Wait>
<Send>	'pfeffa  set sw5 0 pve 0 17'
<Wait>
<Send>	'pfeffa  set sw5 17 pve 0 0'
<Wait>
<Send>	'pfeffa  test link dis 2 as-is'
<Wait>
<GetData>
<CheckData>	'PASS'
<Send>	'pfeffa  clear sw5 17 pve'
<Wait>
<Msg>	'Test link from SW5 port 23 to N2 port 37 and back'
<Send>	'pfeffa  set sw5 0 pve 0 16'
<Wait>
<Send>	'pfeffa  set sw5 16 pve 0 0'
<Wait>
<Send>	'pfeffa  test link dis 2 as-is'
<Wait>
<GetData>
<CheckData>	'PASS'
<Send>	'pfeffa  clear sw5 16 pve'
<Wait>
<Msg>	'Test link from SW5 port 23 to SFP port 0 and back'
<Send>	'pfeffa  set sw5 0 pve 0 17'
<Wait>
<Send>	'pfeffa  set sw5 17 pve 0 0'
<Wait>
<Send>	'pfeffa  set n2 cut 0 36 32'
<Wait>
<Send>	'pfeffa  set n2 cut 1 32 36'
<Wait>
<Send>	'pfeffa  test link dis 2 as-is'
<Wait>
<GetData>
<CheckData>	'PASS'
<Send>	'pfeffa  clear sw5 17 pve'
<Wait>
<Msg>	'Test link from SW5 port 22 to SFP port 1 and back'
<Send>	'pfeffa  set sw5 0 pve 0 16'
<Wait>
<Send>	'pfeffa  set sw5 16 pve 0 0'
<Wait>
<Send>	'pfeffa  set n2 cut 0 37 33'
<Wait>
<Send>	'pfeffa  set n2 cut 1 33 37'
<Wait>
<Send>	'pfeffa  test link dis 2 as-is'
<Wait>
<GetData>
<CheckData>	'PASS'
<Send>	'pfeffa  clear sw5 16 pve'
<Wait>
# extensions for 4-port board
#<Msg>	'Test link from SW5 port 21 to N2 port 38 and back'
#<Send>	'pfeffa  set n2 loopback'
#<Wait>
#<Send>	'pfeffa  set sw5 0 pve 0 15'
#<Wait>
#<Send>	'pfeffa  set sw5 15 pve 0 0'
#<Wait>
#<Send>	'pfeffa  test link dis 2 as-is'
#<Wait>
#<CheckData>	'PASS'
#<Send>	'pfeffa  clear sw5 15 pve'
#<Wait>
#<Msg>	'Test link from SW5 port 20 to N2 port 39 and back'
#<Send>	'pfeffa  set sw5 0 pve 0 14'
#<Wait>
#<Send>	'pfeffa  set sw5 14 pve 0 0'
#<Wait>
#<Send>	'pfeffa  test link dis 2 as-is'
#<Wait>
#<CheckData>	'PASS'
#<Send>	'pfeffa  clear sw5 14 pve'
#<Wait>
#! DON'T DO THESE ON 2-PORT BOARD
#<Msg>	'test link from SW5 port 21 to SFP port 3 and back'
#<Send>	'pfeffa  set sw5 0 pve 0 15'
#<Wait>
#<Send>	'pfeffa  set sw5 15 pve 0 0'
#<Wait>
#<Send>	'pfeffa  set n2 cut 0 38 34'
#<Wait>
#<Send>	'pfeffa  set n2 cut 1 34 38'
#<Wait>
#<Send>	'pfeffa  test link dis 2 as-is'
#<Wait>
#<CheckData>	'FAILED'
#<Send>	'pfeffa  clear sw5 15 pve'
#<Wait>
#<Msg>	'Test link from SW5 port 20 to SFP port 4 and back'
#<Send>	'pfeffa  set sw5 0 pve 0 14'
#<Wait>
#<Send>	'pfeffa  set sw5 14 pve 0 0'
#<Wait>
#<Send>	'pfeffa  set n2 cut 0 39 35'
#<Wait>
#<Send>	'pfeffa  set n2 cut 1 35 39'
#<Wait>
#<Send>	'pfeffa  test link dis 2 as-is'
#<Wait>
#<CheckData>	'FAILED'
#<Send>	'pfeffa  clear sw5 14 pve'
#<Wait>
<timeout>	10
<Send>	'pfeffa sho mib'
<Wait>
<GetData>
<Msg>	'Check: disco port 0x2'
<CheckData>	'disco port 0x2'
<CheckData>	'              4415000              .*gBytesRx'
<CheckData>	'                 5000              .*gFramesRx'
<CheckData>	'                 2500              .*sizeTo127'
<CheckData>	'                 5000              .*sizeToMax'
<CheckData>	'              4415000              .*gBytesTx'
<CheckData>	'                 5000              .*gFramesTx'
# varies <CheckData>	'                   62                       gFcRx'
<Msg>	'Check: dx-sw5 port 0x0'
<CheckData>	'dx-sw5 port 0x0'
<CheckData>	'              4415000              .*gBytesRxLo'
<CheckData>	'                 5000              .*gUcastRx'
<CheckData>	'                 2500              .*sizeTo127'
<CheckData>	'                 5000              .*sizeToMax'
<CheckData>	'              4415000              .*gBytesTxLo'
<CheckData>	'                 5000              .*gUcastTx'
#varies <CheckData>	'                   65                      FCSent'
<CheckDatax>	'RxFifoOvrn'
#<Msg>	'Check: dx-sw5 port 0x14'
#<CheckData>	'dx-sw5 port 0x14'
#<CheckData>	'               903840                  gBytesRxLo'
#<CheckData>	'                 1000                    gUcastRx'
#<CheckData>	'                  668                   sizeTo127'
#<CheckData>	'                 1332                   sizeToMax'
#<CheckData>	'               903840                  gBytesTxLo'
#<CheckData>	'                 1000                    gUcastTx'
#varies <CheckData>	'                 9945                       gFcRx'
#<Msg>	'Check: dx-sw5 port 0x15'
#<CheckData>	'dx-sw5 port 0x15'
#<CheckData>	'               903840                  gBytesRxLo'
#<CheckData>	'                 1000                    gUcastRx'
#<CheckData>	'                  668                   sizeTo127'
#<CheckData>	'                 1332                   sizeToMax'
#<CheckData>	'               903840                  gBytesTxLo'
#<CheckData>	'                 1000                    gUcastTx'
#varies <CheckData>	'                94142                       gFcRx'
<Msg>	'Check: dx-sw5 port 0x16'
<CheckData>	"dx-sw5 port 0x16"
<CheckData>	'              1766000               .*gBytesRxLo'
<CheckData>	'                 2000               .*gUcastRx'
<CheckData>	'                 1000               .*sizeTo127'
<CheckData>	'                 2000               .*sizeToMax'
<CheckData>	'              1766000               .*gBytesTxLo'
<CheckData>	'                 2000               .*gUcastTx'
<Msg>	'Check: dx-sw5 port 0x17'
<CheckData>	"dx-sw5 port 0x17"
<CheckData>	'              1766000               .*gBytesRxLo'
<CheckData>	'                 2000               .*gUcastRx'
<CheckData>	'                 1000               .*sizeTo127'
<CheckData>	'                 2000               .*sizeToMax'
<CheckData>	'              1766000               .*gBytesTxLo'
<CheckData>	'                 2000               .*gUcastTx'
<Msg>	'Check: ixf port 0x0'
<CheckData>	'ixf port 0x0'
<CheckData>	'               883000             RxOctetsTotalOK'
<CheckData>	'                 1000                   RxUcPckts'
<CheckData>	'                  250               RxPkts65to127'
<CheckData>	'                  500            RxPkts1024to1518'
<CheckData>	'               883000             TxOctetsTotalOK'
<CheckData>	'                 1000                   TxUcPckts'
<CheckData>	'                  250               TxPkts65to127'
<CheckData>	'                  500            TxPkts1024to1518'
<Msg>	'Check: ixf port 0x1'
<CheckData>	'ixf port 0x1'
<CheckData>	'               883000             RxOctetsTotalOK'
<CheckData>	'                 1000                   RxUcPckts'
<CheckData>	'                  250               RxPkts65to127'
<CheckData>	'                  500            RxPkts1024to1518'
<CheckData>	'               883000             TxOctetsTotalOK'
<CheckData>	'                 1000                   TxUcPckts'
<CheckData>	'                  250               TxPkts65to127'
<CheckData>	'                  500            TxPkts1024to1518'
<Msg>	'Check: ixf port 0x4'
<CheckData>	'ixf port 0x4'
<CheckData>	'              1766000             RxOctetsTotalOK'
<CheckData>	'                 2000                   RxUcPckts'
<CheckData>	'                  500               RxPkts65to127'
<CheckData>	'                 1000            RxPkts1024to1518'
<CheckData>	'              1766000             TxOctetsTotalOK'
<CheckData>	'                 2000                   TxUcPckts'
<CheckData>	'                  500               TxPkts65to127'
<CheckData>	'                 1000            TxPkts1024to1518'
<Msg>	'Check: ixf port 0x5'
<CheckData>	'ixf port 0x5'
<CheckData>	'              1766000             RxOctetsTotalOK'
<CheckData>	'                 2000                   RxUcPckts'
<CheckData>	'                  500               RxPkts65to127'
<CheckData>	'                 1000            RxPkts1024to1518'
<CheckData>	'              1766000             TxOctetsTotalOK'
<CheckData>	'                 2000                   TxUcPckts'
<CheckData>	'                  500               TxPkts65to127'
<CheckData>	'                 1000            TxPkts1024to1518'
<CheckDatax>	'RxFifoOvrn'
# Don't check on 2 port
#<Msg>	'Check: ixf port 0x6'
#<CheckData>	'ixf port 0x6'
#<CheckData>	'               966340             RxOctetsTotalOK'
#<CheckData>	'                 1070                   RxUcPckts'
#<CheckData>	'                  358               RxPkts65to127'
#<CheckData>	'                  712            RxPkts1024to1518'
#<CheckData>	'              7648224             TxOctetsTotalOK'
#<CheckData>	'                 1000                   TxUcPckts'
#<CheckData>	'               105382                    TxMcPkts'
#<CheckData>	'               105383                    TxPkts64'
#<CheckData>	'                  334               TxPkts65to127'
#<CheckData>	'                  666            TxPkts1024to1518'
#<CheckData>	'               105385               TxPauseFrames'
#<Msg>	'Check: ixf port 0x7'
#<CheckData>	'ixf port 0x7'
#<CheckData>	'               966340             RxOctetsTotalOK'
#<CheckData>	'                 1070                   RxUcPckts'
#<CheckData>	'                  358               RxPkts65to127'
#<CheckData>	'                  712            RxPkts1024to1518'
#<CheckData>	'              2260512             TxOctetsTotalOK'
#<CheckData>	'                 1000                   TxUcPckts'
#<CheckData>	'                21199                    TxMcPkts'
#<CheckData>	'                21200                    TxPkts64'
#<CheckData>	'                  334               TxPkts65to127'
#<CheckData>	'                  666            TxPkts1024to1518'
#<CheckData>	'                21202               TxPauseFrames'


