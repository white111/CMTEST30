################################################################################
#
# Module:      Check_BI_loopbacktest_Err_slot.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI.dat
#
# Version:    1.0 $Id: Check_BI_loopbacktest_Err_slot.inc,v 1.2 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Created 12/13/05
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
#
# Version 5a1	11/12/05
#
<GetData>
#<CheckData>	"dx-sw5 port 0x3"
<CheckData>	"gBytesRxLo"
<CheckData>	"gUcastRx"
<CheckData>	"sizeTo127"
<CheckData>	"gBytesTxLo"
<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0x4"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0x5"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0x6"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0x7"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0x8"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0x9"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0xa"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0xb"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0xc"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0xd"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0xe"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0xf"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0x10"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0x11"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"
#<CheckData>	"dx-sw5 port 0x12"
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"


<CheckDataX> "bBytesRx"
<CheckDataX> "txFifoOvrn"
<CheckDataX> "excCollision"
<CheckDataX> "RxFifoOvrn"
<CheckDataX> "rxUndersize"
<CheckDataX> "rxFrags"
<CheckDataX> "rxOversize"
<CheckDataX> "jabber"
<CheckDataX> "rxErrFrame"
<CheckDataX> "badCRC"
<CheckDataX> "collisions"
<CheckDataX> "late coll"
