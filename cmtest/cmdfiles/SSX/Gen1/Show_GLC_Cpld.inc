################################################################################
#
# Module:      Bench_GLC.dat
#
# Author:      Joe White
#
# Descr:       Called by Bench_GLC.dat
#
# Version:    1.2  $Id: Show_GLC_Cpld.inc,v 1.5 2008/02/20 22:03:49 joe Exp $
#
# Changes:    First Release  12/05/05
#			  Longer timeout for 9600 baud
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################

# Done at the Noodle level
<Prompt>	"> "
<TimeOut>	5
<Msg>		"Check CPLD...."
<Send>		"show cpld"
<Wait>

# Now checked  by <GetData CPLD>   <CheckData>	'F4000000                   card-type  01'
<CheckData>	'F4000001                    assy-rev  02'
<CheckData>	'F4000002               cpld-code-rev'
<CheckData>	$firmware_ver_gbl
#<CheckData>	'F4000003          bp-logical-slot-id  43'
<CheckData>	'F4000004                bp-system-id  03'
<CheckData>	'F4000005          board-reset-reason  01'
<CheckData>	'F4000006           cpu0-reset-reason  01'
<CheckData>	'F4000007           cpu1-reset-reason  01'
<CheckData>	'F4000008                 board-reset  07'
<CheckData>	'F4000009            cpu0->cpu1-reset  01'
<CheckData>	'F400000A         cpu0-watchdog-clear  07'
<CheckData>	'F400000B         cpu1-watchdog-clear  07'
#<CheckData>	'F400000C      cpu0-watchdog-settings  3E'
#<CheckData>	'F400000D      cpu1-watchdog-settings  07'
<CheckData>	'F400000E               ixp2800-reset  00'
<CheckData>	'F400000F                nitrox-reset  00'
<CheckData>	'F4000010               ixf1110-reset  00'
<CheckData>	'F4000011                  tcam-reset  01'
<CheckData>	'F4000012              mgmt-phy-reset  00'
<CheckData>	'F4000013             quad-uart-reset  00'
<CheckData>	'F4000014                   fic-reset  00'
<CheckData>	'F4000015                 pci-0-reset  00'
<CheckData>	'F4000016                 pci-1-reset  00'
<CheckData>	'F4000017       cpu0-sys-mgmt-irq-sts  18'
<CheckData>	'F4000018        cpu0-sys-mgmt-irq-en  00'
<CheckData>	'F4000019       cpu1-sys-mgmt-irq-sts  0F'
<CheckData>	'F400001A                   led:power  01'
<CheckData>	'F400001B                  led:status  03'
<CheckData>	'F400001C          led:active/standby  00'
<CheckData>	'F400001D            i2c-local-enable  01'
<CheckData>	'F400001E           i2c-global-enable  00'
<CheckData>	'F400001F             IPMI_A/B-enable  09'
<CheckData>	'F4000020              CPU-boot-state  01'
<CheckData>	'F4000021             temp-sensor-sts  13'
<CheckData>	'F4000022         diag-jumper-present  00'
<CheckData>	'F4000023                    ipx-gpio  13'
<CheckData>	'F4000024               tcam-clock-en  00'
<CheckData>	'F4000025     ipx-serial-port-mux-sel  00'
<CheckData>	'F4000026             fic/pmc-present  06'
<CheckData>	'F4000027             arbitration-sts  00'
<CheckData>	'F4000028             arbitration-req  00'

<Msg>		"Get GLC Slot number"
<Send>		"show cpld"
<Wait>
<GetData>	"CPLD"


<Send>		"set ver 0"
<TimeOut>	2
<Wait>
