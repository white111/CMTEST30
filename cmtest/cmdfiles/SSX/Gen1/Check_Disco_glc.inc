################################################################################
#
# Module:      Check_Disco_glc.inc
#
# Author:      Joe White
#
# Descr:       Include for Bench_GLC.dat
#
# Version:    5.7  $Id: Check_Disco_glc.inc,v 1.4 2008/02/20 22:03:49 joe Exp $
#
# Changes:    Added <CheckData> 12/05/05
#			  Updated for R1 release 010706
#
# Used By:
#				BenchGLC.dat
#				Bench_Test_GLC.inc
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
<Send>		"show disco prob"
<Wait>

<CheckData>	'PCI 0 ERROR REPORT'
<CheckData>	'Master generated master abort'
<CheckData>	'1D44                                 PCI_0_ERROR_ADDR_HIGH  00000000'
<CheckData>	'1D40                                  PCI_0_ERROR_ADDR_LOW  00000000'
<CheckData>	'1D48                                 PCI_0_ERROR_ATTRIBUTE  00000000'
<CheckData>	'1D58                                     PCI_0_ERROR_CAUSE  00000100'
<CheckData>	'1D50                                   PCI_0_ERROR_COMMAND  0000000A'
<CheckData>	'1D5C                                      PCI_0_ERROR_MASK  00000000'
<CheckData>	'PCI 1 ERROR REPORT:'
<CheckData>	'Master generated master abort'
<CheckData>	'1DC4                                 PCI_1_ERROR_ADDR_HIGH  00000000'
<CheckData>	'1DC0                                  PCI_1_ERROR_ADDR_LOW  00000000'
<CheckData>	'1DC8                                 PCI_1_ERROR_ATTRIBUTE  00000000'
<CheckData>	'1DD8                                     PCI_1_ERROR_CAUSE  00000100'
<CheckData>	'1DD0                                   PCI_1_ERROR_COMMAND  0000000A'
<CheckData>	'1DDC                                      PCI_1_ERROR_MASK  00000000'
<CheckData>	'1DA4                                           PCI_1_MMASK  00000000'
<CheckData>	'0CA8                                       PCI_1_SERR_MASK  00F77FF7'

# Second time should be clean
<Send>		"show disco prob"
<Wait>
<GetData>
<CheckDataX>	'PCI 0 ERROR REPORT'
<CheckDataX>	'PCI 1 ERROR REPORT'

