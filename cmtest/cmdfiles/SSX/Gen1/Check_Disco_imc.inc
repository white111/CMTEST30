################################################################################
#
# Module:      Bench_IMC.dat
#
# Author:      Joe White
#
# Descr:       Called by Bench_IMC.dat
#
# Version:    1.3 $Id: Check_Disco_imc.inc,v 1.3 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Added <GetData> 12/05/05
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
<TimeOut>	4
<Msg>		'Check Disco Problems...'
<Send>
<Wait>
<Send>		'pfeffa show disco prob'
<Wait>
<CheckData>	'PCI 0 ERROR REPORT'
<CheckData>	'Master generated master abort'
#<CheckData>	'1D44                                 PCI_0_ERROR_ADDR_HIGH  00000000'
#<CheckData>	'1D40                                  PCI_0_ERROR_ADDR_LOW  80000004'
#<CheckData>	'1D48                                 PCI_0_ERROR_ATTRIBUTE  00000000'
#<CheckData>	'1D58                                     PCI_0_ERROR_CAUSE  00000100'
#<CheckData>	'1D50                                   PCI_0_ERROR_COMMAND  00000006'
#<CheckData>	'1D5C                                      PCI_0_ERROR_MASK  00000000'
#<CheckData>	'1D24                                           PCI_0_MMASK  00000000'
#<CheckData>	'0C28                                       PCI_0_SERR_MASK  00F77FF7'

<Send>
<Wait>
# Second time should be clean
<Msg>		"Check Disco Problems...Check for Errors"
<Send>		"pfeffa show disco prob"
<Wait>
<GetData>
<CheckDataX>	'PCI 0 ERROR REPORT'
#There is no PCI 1 on the MC


