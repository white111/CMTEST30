################################################################################
#
# Module:      Show_Mib.inc
#
# Author:      Joe White
#
# Descr:       Show Mib used by GLC bench tests
#
# Version:    1.0 $Id: Show_MIB.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2008 Stoke. All rights reserved.
#
################################################################################
<Msg>		"Check Counters"
<Timeout>	10
<Send>		"pfeffa sho mib"
<Wait>

<CheckData>	'            820000000                  gBytesRxLo'
<CheckData>	'             10000000                    gUcastRx'
<CheckData>	'             20000000                   sizeTo127'
<CheckData>	'            820000000                  gBytesTxLo'
<CheckData>	'             10000000                    gUcastTx'
<CheckData>	'dx-sw5 port 0x17'
<CheckData>	'            820000000                  gBytesRxLo'
<CheckData>	'             10000000                    gUcastRx'
<CheckData>	'             20000000                   sizeTo127'
<CheckData>	'            820000000                  gBytesTxLo'
<CheckData>	'             10000000                    gUcastTx'
<CheckData>	'ixf port 0x0'
<CheckData>	'            820000000             RxOctetsTotalOK'
<CheckData>	'             10000000                   RxUcPckts'
<CheckData>	'             10000000               RxPkts65to127'
<CheckData>	'            820000000             TxOctetsTotalOK'
<CheckData>	'             10000000                   TxUcPckts'
<CheckData>	'             10000000               TxPkts65to127'
<CheckData>	'ixf port 0x1'
<CheckData>	'            820000000             RxOctetsTotalOK'
<CheckData>	'             10000000                   RxUcPckts'
<CheckData>	'             10000000               RxPkts65to127'
<CheckData>	'            820000000             TxOctetsTotalOK'
<CheckData>	'             10000000                   TxUcPckts'
<CheckData>	'             10000000               TxPkts65to127'
<CheckData>	'ixf port 0x4'
<CheckData>	'            820000000             RxOctetsTotalOK'
<CheckData>	'             10000000                   RxUcPckts'
<CheckData>	'             10000000               RxPkts65to127'
<CheckData>	'            820000000             TxOctetsTotalOK'
<CheckData>	'             10000000                   TxUcPckts'
<CheckData>	'             10000000               TxPkts65to127'
<CheckData>	'ixf port 0x5'
<CheckData>	'            820000000             RxOctetsTotalOK'
<CheckData>	'             10000000                   RxUcPckts'
<CheckData>	'             10000000               RxPkts65to127'
<CheckData>	'            820000000             TxOctetsTotalOK'
<CheckData>	'             10000000                   TxUcPckts'
<CheckData>	'             10000000               TxPkts65to127'

