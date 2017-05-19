################################################################################
#
# Module:      Check_loopbacktest_Err.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_BI.dat
#
# Version:    1.1 $Id: Check_loopbacktest_Err.inc,v 1.2 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Created 1/30/06
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
