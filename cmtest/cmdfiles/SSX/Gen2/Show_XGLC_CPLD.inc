################################################################################
#
# Module:      Show_XGLC_CPLD.inc
#
# Author:      Joe White
#
# Descr:       Called by Bench_GLC.dat
#
# Version:    1.1  $Id: Show_XGLC_Cpld.inc.dep,v 1.1 2011/12/12 22:54:27 joe Exp $
#
# Changes:    First Release  04/17/12
#			  Added suporrt for XGLC in slot 1

#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################

# Done at the Noodle level
<TimeOut>	5
#<Msg>       "Check CPLD...."
#<Send>      "cpldshow"
#<Wait>
#<GetData>   "Check_XGLC_CPLD"


<Msg> "Show CPLD contents"

<Bypass>    $Slot_INST_1_GLC_GBL
    <Msg>   "CPLD Slot1"
    <send>  "on -p 7f -f /net/nv-1-0 xglcdiag cpldshow | grep -v -e 'Register' -e 'Adding'"
    <Wait>
    <Getdata>

</Bypass>

<Bypass>    $Slot_INST_2_GBL
    <Msg>   "CPLD Slot2"
    <send>  "on -p 7f -f /net/nv-2-0 xglcdiag cpldshow | grep -v -e 'Register' -e 'Adding'"
    <Wait>
    <Getdata>

</Bypass>

<Bypass>    $Slot_INST_3_GBL
     <Msg>   "CPLD Slot3"
    <send>  "on -p 7f -f /net/nv-3-0 xglcdiag cpldshow | grep -v -e 'Register' -e 'Adding'"
    <Wait>
    <Getdata>
</Bypass>

<Bypass>    $Slot_INST_4_GBL
     <Msg>   "CPLD Slot4"
    <send>  "on -p 7f -f /net/nv-4-0 xglcdiag cpldshow | grep -v -e 'Register' -e 'Adding'"
    <Wait>
    <Getdata>
</Bypass>
