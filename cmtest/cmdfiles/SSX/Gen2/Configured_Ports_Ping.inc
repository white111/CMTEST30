################################################################################
#
# Module:      Configured_Ports_Ping.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_POST_BI and Config
#
# Version:    3.2 $Id: Configured_Ports_Ping.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 081308
#			  11/18/11 Changed to Flood Pin 100 to test for FCS errors
#			  6/10/13 Prompt changes in 6.1R2 
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"[local]#"
<Send>
<Wait>
<TimeOut>   300
<Send>      "terminal length infinite"
<Wait>
<Msg>       "Ping Ports..."
<Bypass>	$Slot_INST_1_GLC_GBL
#### Slot 1 ######
#Port 1/0
<Send>      "ping 10.1.0.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.1.0.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.1.0.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.1.0.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.1.0.2 flood repeat 1000 size 1528"
<Wait>
#Port 1/1
<Send>      "ping 10.1.1.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.1.1.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.1.1.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.1.1.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.1.1.2 flood repeat 1000 size 1528"
<Wait>
#Port 1/2
<Send>      "ping 10.1.2.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.1.2.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.1.2.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.1.2.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.1.2.2 flood repeat 1000 size 1528"
<Wait>
#Port 1/3
<Send>      "ping 10.1.3.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.1.3.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.1.3.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.1.3.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.1.3.2 flood repeat 1000 size 1528"
<Wait>
</Bypass>
##### Slot 2 ######
#Port 2/0
<Bypass>	$Slot_INST_2_GBL
<Send>      "ping 10.2.0.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.2.0.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.2.0.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.2.0.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.2.0.2 flood repeat 1000 size 1528"
<Wait>
#Port 2/1
<Send>      "ping 10.2.1.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.2.1.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.2.1.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.2.1.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.2.1.2 flood repeat 1000 size 1528"
<Wait>
#Port 2/2
<Send>      "ping 10.2.2.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.2.2.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.2.2.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.2.2.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.2.2.2 flood repeat 1000 size 1528"
<Wait>
#Port 2/3
<Send>      "ping 10.2.3.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.2.3.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.2.3.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.2.3.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.2.3.2 flood repeat 1000 size 1528"
<Wait>
</Bypass>
##### Slot 3 ######
#Port 3/0
<Bypass>	$Slot_INST_3_GBL
<Send>      "ping 10.3.0.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.3.0.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.3.0.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.3.0.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.3.0.2 flood repeat 1000 size 1528"
<Wait>
#Port 3/1
<Send>      "ping 10.3.1.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.3.1.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.3.1.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.3.1.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.3.1.2 flood repeat 1000 size 1528"
<Wait>
#Port 3/2
<Send>      "ping 10.3.2.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.3.2.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.3.2.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.3.2.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.3.2.2 flood repeat 1000 size 1528"
<Wait>
#Port 3/3
<Send>      "ping 10.3.3.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.3.3.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.3.3.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.3.3.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.3.3.2 flood repeat 1000 size 1528"
<Wait>
</Bypass>
##### Slot 4 ######
#Port 4/0
<Bypass>	$Slot_INST_4_GBL
<Send>      "ping 10.4.0.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.4.0.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.4.0.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.4.0.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.4.0.2 flood repeat 1000 size 1528"
<Wait>
#Port 4/1
<Send>      "ping 10.4.1.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.4.1.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.4.1.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.4.1.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.4.1.2 flood repeat 1000 size 1528"
<Wait>
#Port 4/2
<Send>      "ping 10.4.2.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.4.2.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.4.2.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.4.2.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.4.2.2 flood repeat 1000 size 1528"
<Wait>
#Port 4/3
<Send>      "ping 10.4.3.2 flood repeat 1000"
<Wait>
<Send>      "ping 10.4.3.2 flood repeat 1000 size 256"
<Wait>
<Send>      "ping 10.4.3.2 flood repeat 1000 size 512"
<Wait>
<Send>      "ping 10.4.3.2 flood repeat 1000 size 1024"
<Wait>
<Send>      "ping 10.4.3.2 flood repeat 1000 size 1528"
<Wait>
</Bypass>





