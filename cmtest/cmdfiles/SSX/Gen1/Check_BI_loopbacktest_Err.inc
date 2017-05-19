################################################################################
#
# Module:      Check_BI_loopbacktest_Err.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI.dat
#
# Version:    1.3 $Id: Check_BI_loopbacktest_Err.inc,v 1.4 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Added <GetData> 12/05/05
#			  removed Check dx-sw5
#			  removed all checks except errors 03/30/06
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
#<CheckData>	"gBytesRxLo"
#<CheckData>	"gUcastRx"
#<CheckData>	"sizeTo127"
#<CheckData>	"gBytesTxLo"
#<CheckData>	"gUcastTx"

<CheckDataX>	"grep: cannot open file ./nv-0-0/hd/dump/slot./traffic.log. .No such file or directory."
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
