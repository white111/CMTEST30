################################################################################
#
# Module:      Disable_Overtemp_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Pe,BI,POST.dat
#
# Version:    1.2   $Id: Internal_Snake_setup_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 03/04/12
#			  Added Support for XGLC in Slot 1 10/30/13
#
# Still ToDo:
#
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################
#
# Version 5a1	11/12/05
#

<Prompt>	"#"
<Timeout>	20




<Msg> "Disable overtemp on XLP1"

<Bypass>    $Slot_INST_1_GLC_GBL
    <Msg>   "Disable Overtemp XLP1 Slot 1"
    <send>  'on -p 7f -f /net/nv-1-0 xglcdiag cpldacc wr 1d 1'
    <Wait>
    <Getdata>
#    Do not use feed back NPU alert output to NPU input alert 4/13/12
#    #Disable Overtemp return to XLP1, 5F    cpld_npu_temp_alarm_control R/W 8   11111111    cs_cpld_npu_temp_alarm_control_l            cpld NPU1 Overtemp alarm out set    cpld NPU1 TEMP ALERT alarm out set  NPU0 Overtemp alarm out set cpld NPU10TEMP ALERT alarm  out set     CPLD NPU1 Overtemp alarm out pass/block CPLD NPU1 TEMP ALERT alarm out  pass/block  CPLD NPU0 Overtemp alarm out pass/block CPLD_NPU10TEMP ALERT alarm  out pass/block
#    <send>  'on -p 7f -f /net/nv-1-0 xglcdiag cpldacc wr 5F F3'
#    <Wait>
#    <Getdata>
    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -w bus=0,dev=0x70,off=0,rsize=1,len=1,data=1'
    <Wait>
    <Getdata>
    # RLHN 05h 0101 0101 +85°C Read local (internal) ALERT high limit
    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -r bus=0,dev=0x4D,off=5,rsize=1,len=1,data=0'
    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -w bus=0,dev=0x4d,off=B,rsize=1,len=1,data=7d'
#    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -r bus=0,dev=0x4D,off=5,rsize=1,len=1,data=0'
#    <Wait>
#    <Getdata>
    #RRHI 07h 0101 1111 +95°C Read remote (external) ALERT high limit (MAX6646/MAX6647)
    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -r bus=0,dev=0x4D,off=7,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -w bus=0,dev=0x4d,off=d,rsize=1,len=1,data=7d'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -r bus=0,dev=0x4D,off=7,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
    #RWOE 19h 0111 1101 +125°C Read/write remote (external) OVERT limit (MAX6646/MAX6647) Found 0019: 50    P
    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -r bus=0,dev=0x4D,off=19,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -w bus=0,dev=0x4d,off=19,rsize=1,len=1,data=ff'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -r bus=0,dev=0x4D,off=19,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
##RWOI 20h 0101 0101 +85°C Read/write local (internal) OVERT limit, Found 0020: 55    U
#    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -r bus=0,dev=0x4D,off=20,rsize=1,len=1,data=0'
#    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -w bus=0,dev=0x4d,off=20,rsize=1,len=1,data=7d'
#    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-1-0 i2c_util -r bus=0,dev=0x4D,off=20,rsize=1,len=1,data=0'
#    <Wait>
#    <Getdata>

</Bypass>

<Bypass>    $Slot_INST_2_GBL
    <Msg>   "Disable Overtemp XLP1 Slot 2"
    <send>  'on -p 7f -f /net/nv-2-0 xglcdiag cpldacc wr 1d 1'
    <Wait>
    <Getdata>
#    Do not use feed back NPU alert output to NPU input alert 4/13/12
#    #Disable Overtemp return to XLP1, 5F    cpld_npu_temp_alarm_control R/W 8   11111111    cs_cpld_npu_temp_alarm_control_l            cpld NPU1 Overtemp alarm out set    cpld NPU1 TEMP ALERT alarm out set  NPU0 Overtemp alarm out set cpld NPU10TEMP ALERT alarm  out set     CPLD NPU1 Overtemp alarm out pass/block CPLD NPU1 TEMP ALERT alarm out  pass/block  CPLD NPU0 Overtemp alarm out pass/block CPLD_NPU10TEMP ALERT alarm  out pass/block
#    <send>  'on -p 7f -f /net/nv-2-0 xglcdiag cpldacc wr 5F F3'
#    <Wait>
#    <Getdata>
    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -w bus=0,dev=0x70,off=0,rsize=1,len=1,data=1'
    <Wait>
    <Getdata>
    # RLHN 05h 0101 0101 +85°C Read local (internal) ALERT high limit
    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -r bus=0,dev=0x4D,off=5,rsize=1,len=1,data=0'
    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -w bus=0,dev=0x4d,off=B,rsize=1,len=1,data=7d'
#    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -r bus=0,dev=0x4D,off=5,rsize=1,len=1,data=0'
#    <Wait>
#    <Getdata>
    #RRHI 07h 0101 1111 +95°C Read remote (external) ALERT high limit (MAX6646/MAX6647)
    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -r bus=0,dev=0x4D,off=7,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -w bus=0,dev=0x4d,off=d,rsize=1,len=1,data=7d'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -r bus=0,dev=0x4D,off=7,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
    #RWOE 19h 0111 1101 +125°C Read/write remote (external) OVERT limit (MAX6646/MAX6647) Found 0019: 50    P
    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -r bus=0,dev=0x4D,off=19,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -w bus=0,dev=0x4d,off=19,rsize=1,len=1,data=ff'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -r bus=0,dev=0x4D,off=19,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
##RWOI 20h 0101 0101 +85°C Read/write local (internal) OVERT limit, Found 0020: 55    U
#    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -r bus=0,dev=0x4D,off=20,rsize=1,len=1,data=0'
#    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -w bus=0,dev=0x4d,off=20,rsize=1,len=1,data=7d'
#    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-2-0 i2c_util -r bus=0,dev=0x4D,off=20,rsize=1,len=1,data=0'
#    <Wait>
#    <Getdata>

</Bypass>


<Bypass>    $Slot_INST_3_GBL
    <Msg>   "Disable Overtemp XLP1 Slot 3"
    <send>  'on -p 7f -f /net/nv-3-0 xglcdiag cpldacc wr 1d 1'
    <Wait>
    <Getdata>
    #Disable Overtemp return to XLP1, 5F	cpld_npu_temp_alarm_control	R/W	8	11111111	cs_cpld_npu_temp_alarm_control_l			cpld NPU1 Overtemp alarm out set	cpld NPU1 TEMP ALERT alarm out set 	NPU0 Overtemp alarm out set	cpld NPU10TEMP ALERT alarm  out set 	CPLD NPU1 Overtemp alarm out pass/block	CPLD NPU1 TEMP ALERT alarm out  pass/block	CPLD NPU0 Overtemp alarm out pass/block	CPLD_NPU10TEMP ALERT alarm  out pass/block
    <send>  'on -p 7f -f /net/nv-3-0 xglcdiag cpldacc wr 5F F3'
    <Wait>
    <Getdata>
    #<sleep> 2
    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -w bus=0,dev=0x70,off=0,rsize=1,len=1,data=1'
    <Wait>
    <Getdata>
    # RLHN 05h 0101 0101 +85°C Read local (internal) ALERT high limit
    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -r bus=0,dev=0x4D,off=5,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
#    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -w bus=0,dev=0x4d,off=B,rsize=1,len=1,data=7d'
#    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -r bus=0,dev=0x4D,off=5,rsize=1,len=1,data=0'
#    <Wait>
#    <Getdata>
    #RRHI 07h 0101 1111 +95°C Read remote (external) ALERT high limit (MAX6646/MAX6647)
    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -r bus=0,dev=0x4D,off=7,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -w bus=0,dev=0x4d,off=d,rsize=1,len=1,data=7d'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -r bus=0,dev=0x4D,off=7,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
    #RWOE 19h 0111 1101 +125°C Read/write remote (external) OVERT limit (MAX6646/MAX6647) Found 0019: 50    P
    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -r bus=0,dev=0x4D,off=19,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -w bus=0,dev=0x4d,off=19,rsize=1,len=1,data=ff'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -r bus=0,dev=0x4D,off=19,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
##RWOI 20h 0101 0101 +85°C Read/write local (internal) OVERT limit, Found 0020: 55    U
#    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -r bus=0,dev=0x4D,off=20,rsize=1,len=1,data=0'
#    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -w bus=0,dev=0x4d,off=20,rsize=1,len=1,data=7d'
#    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-3-0 i2c_util -r bus=0,dev=0x4D,off=20,rsize=1,len=1,data=0'
#    <Wait>
#    <Getdata>
</Bypass>

<Bypass>    $Slot_INST_4_GBL
    <Msg>   "Disable Overtemp XLP1 Slot 4"
    <send>  'on -p 7f -f /net/nv-4-0 xglcdiag cpldacc wr 1d 1'
    <Wait>
    <Getdata>
    #Disable Overtemp return to XLP1, 5F	cpld_npu_temp_alarm_control	R/W	8	11111111	cs_cpld_npu_temp_alarm_control_l			cpld NPU1 Overtemp alarm out set	cpld NPU1 TEMP ALERT alarm out set 	NPU0 Overtemp alarm out set	cpld NPU10TEMP ALERT alarm  out set 	CPLD NPU1 Overtemp alarm out pass/block	CPLD NPU1 TEMP ALERT alarm out  pass/block	CPLD NPU0 Overtemp alarm out pass/block	CPLD_NPU10TEMP ALERT alarm  out pass/block
    <send>  'on -p 7f -f /net/nv-2-0 xglcdiag cpldacc wr 5F F3'
    <Wait>
    <Getdata>
    #<sleep> 2
    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -w bus=0,dev=0x70,off=0,rsize=1,len=1,data=1'
    <Wait>
    <Getdata>
    # RLHN 05h 0101 0101 +85°C Read local (internal) ALERT high limit
    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -r bus=0,dev=0x4D,off=5,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
#    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -w bus=0,dev=0x4d,off=B,rsize=1,len=1,data=7d'
#    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -r bus=0,dev=0x4D,off=5,rsize=1,len=1,data=0'
#    <Wait>
#    <Getdata>
    #RRHI 07h 0101 1111 +95°C Read remote (external) ALERT high limit (MAX6646/MAX6647)
    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -r bus=0,dev=0x4D,off=7,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -w bus=0,dev=0x4d,off=d,rsize=1,len=1,data=7d'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -r bus=0,dev=0x4D,off=7,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
    #RWOE 19h 0111 1101 +125°C Read/write remote (external) OVERT limit (MAX6646/MAX6647) Found 0019: 50    P
    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -r bus=0,dev=0x4D,off=19,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -w bus=0,dev=0x4d,off=19,rsize=1,len=1,data=7d'
    <Wait>
    <Getdata>
    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -r bus=0,dev=0x4D,off=19,rsize=1,len=1,data=0'
    <Wait>
    <Getdata>
#    #RWOI 20h 0101 0101 +85°C Read/write local (internal) OVERT limit, Found 0020: 55    U
#    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -r bus=0,dev=0x4D,off=20,rsize=1,len=1,data=0'
#    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -w bus=0,dev=0x4d,off=20,rsize=1,len=1,data=7d'
#    <Wait>
#    <Getdata>
#    <send>  'on -p 7f -f /net/nv-4-0 i2c_util -r bus=0,dev=0x4D,off=20,rsize=1,len=1,data=0'
#    <Wait>
#    <Getdata>
</Bypass>



