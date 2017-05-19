################################################################################
#
# Module:      Configure_Ports.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_POST_BI and Config
#
# Version:    2.3 $Id: Configure_Ports.inc,v 1.2.8.1 2011/11/30 19:48:56 joe Exp $
#
# Changes:    Created 081308
#			  Added  ip host 10.2.3.2 00:00:00:00:04:00 binde address 11/21/11
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
# Done at the Noodle level
<Prompt>	"Stoke"
<Send>
<Wait>
<TimeOut>	10
<Send>		"terminal length infinite"
<Wait>
<Msg>		"Configuring Ports..."
######################################
#ping config CONFIGURATION####################
######################################
<Send>	"clear port count"
<Wait>

###########  Slot 1 #################
<Bypass>	$Slot_INST_1_GLC_GBL
<Send> config
<Wait>
<Send> 	context local
<Wait>
<Send>  		interface ssx_1_0
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.1.0.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 1/0
<Wait>
<Send>  		bind interface ssx_1_0 local
<Wait>
<Send>  		ip host 10.1.0.2 00:12:73:FF:10:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>


<Send> 	context local
<Wait>
<Send>  		interface ssx_1_1
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.1.1.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 1/1
<Wait>
<Send>  		bind interface ssx_1_1 local
<Wait>
<Send>  		ip host 10.1.1.2 00:12:73:FF:11:10
<Wait><Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> 	context local
<Wait>
<Send>  		interface ssx_1_2
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.1.2.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 1/2
<Wait>
<Send>  		bind interface ssx_1_2 local
<Wait>
<Send>  		ip host 10.1.2.2 00:12:73:FF:12:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> 	context local
<Wait>
<Send>  		interface ssx_1_3
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.1.3.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 1/3
<Wait>
<Send>  		bind interface ssx_1_3 local
<Wait>
<Send>  		ip host 10.1.3.2 00:12:73:FF:13:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> exit
<Wait>
</Bypass>
###########  Slot 2 #################

<Bypass>	$Slot_INST_2_GBL
<Send> config
<Wait>
<Send> 	context local
<Wait>
<Send>  		interface ssx_2_0
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.2.0.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 2/0
<Wait>
<Send>  		bind interface ssx_2_0 local
<Wait>
<Send>  		ip host 10.2.0.2 00:12:73:FF:20:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> 	context local
<Wait>
<Send>  		interface ssx_2_1
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.2.1.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 2/1
<Wait>
<Send>  		bind interface ssx_2_1 local
<Wait>
<Send>  		ip host 10.2.1.2 00:12:73:FF:21:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> 	context local
<Wait>
<Send>  		interface ssx_2_2
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.2.2.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 2/2
<Wait>
<Send>  		bind interface ssx_2_2 local
<Wait>
<Send>  		ip host 10.2.2.2 00:12:73:FF:22:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> 	context local
<Wait>
<Send>  		interface ssx_2_3
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.2.3.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 2/3
<Wait>
<Send>  		bind interface ssx_2_3 local
<Wait>
<Send>  		ip host 10.2.3.2 00:12:73:FF:23:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> exit
<Wait>
</Bypass>

###########  Slot 3 #################
<Bypass>	$Slot_INST_3_GBL

<Send> config
<Wait>
<Send> 	context local
<Wait>
<Send>  		interface ssx_3_0
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.3.0.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 3/0
<Wait>
<Send>  		bind interface ssx_3_0 local
<Wait>
<Send>  		ip host 10.3.0.2 00:12:73:FF:30:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> 	context local
<Wait>
<Send>  		interface ssx_3_1
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.3.1.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 3/1
<Wait>
<Send>  		bind interface ssx_3_1 local
<Wait>
<Send>  		ip host 10.3.1.2 00:12:73:FF:31:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> 	context local
<Wait>
<Send>  		interface ssx_3_2
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.3.2.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 3/2
<Wait>
<Send>  		bind interface ssx_3_2 local
<Wait>
<Send>  		ip host 10.3.2.2 00:12:73:FF:32:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> 	context local
<Wait>
<Send>  		interface ssx_3_3
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.3.3.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 3/3
<Wait>
<Send>  		bind interface ssx_3_3 local
<Wait>
<Send>  		ip host 10.3.3.2 00:12:73:FF:33:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> exit
<Wait>
</Bypass>

###########  Slot 4 #################
<Bypass>	$Slot_INST_4_GBL

<Send> config
<Wait>
<Send> 	context local
<Wait>
<Send>  		interface ssx_4_0
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.4.0.1/24
<Wait>
<Send>  		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 4/0
<Wait>
<Send>  		bind interface ssx_4_0 local
<Wait>
<Send>  		ip host 10.4.0.2 00:12:73:FF:40:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> 	context local
<Wait>
<Send>  		interface ssx_4_1
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.4.1.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 4/1
<Wait>
<Send>  		bind interface ssx_4_1 local
<Wait>
<Send>  		ip host 10.4.1.2 00:12:73:FF:41:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> 	context local
<Wait>
<Send>  		interface ssx_4_2
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.4.2.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 4/2
<Wait>
<Send>  		bind interface ssx_4_2 local
<Wait>
<Send>  		ip host 10.4.2.2 00:12:73:FF:42:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> 	context local
<Wait>
<Send>  		interface ssx_4_3
<Wait>
<Send>   			arp arpa
<Wait>
<Send>   			ip address 10.4.3.1/24
<Wait>
<Send>   		exit
<Wait>
<Send> 	exit
<Wait>
<Send> 	port ethernet 4/3
<Wait>
<Send>  		bind interface ssx_4_3 local
<Wait>
<Send>  		ip host 10.4.3.2 00:12:73:FF:44:10
<Wait>
<Send>   		exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> exit
<Wait>
</Bypass>







