################################################################################
#
# Module:      Configure_Ports.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_POST_BI and Config
#
# Version:    2.3 $Id: Configure_Ports.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 081308
#			  Added  ip host 10.2.3.2 00:00:00:00:04:00 binde address 11/21/11
#			  Enabled port redundancy, added check for SFP speed trpe
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
<Send>  	redundant
<Wait>
<Send>   	exit
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
<Wait>
<Send>   		exit
<Wait>
<Send>  	redundant
<Wait>
<Send>   	exit
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
<Send>  	redundant
<Wait>
<Send>   	exit
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
<Send>  	redundant
<Wait>
<Send>   	exit
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
<Send>  	redundant
<Wait>
<Send>   	exit
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
<Send>  	redundant
<Wait>
<Send>   	exit
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
<Send>  	redundant
<Wait>
<Send>   	exit
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
<Send>  	redundant
<Wait>
<Send>   	exit
<Wait>
<Send>  	enable
<Wait>
<Send> 	exit
<Wait>

<Send> exit
<Wait>
</Bypass>


<Msg>	"Show Port Detail"
<Send>		"show port redundancy"
<Wait>
<GetData>

<Bypass>	$Slot_INST_1_GLC_GBL
	<bypass>	$XGLC_10gigSFP_gbl[1][0]
	<msg>		"Check slot 1 10gig SFP I2C"
	<send>		"show port 1/0 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
	<bypass>	$XGLC_10gigSFP_gbl[1][1]
	<send>		"show port 1/1 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
 	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_1_GLC_GBL
	<bypass>	$XGLC_10gigLRSFP_gbl[1][0]
	<msg>		"Check slot 1 10gig SFP I2C"
	<send>		"show port 1/0 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
	<bypass>	$XGLC_10gigLRSFP_gbl[1][1]
	<send>		"show port 1/1 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
 	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<bypass>	$XGLC_10gigSFP_gbl[2][0]
	<msg>		"Check slot 2 10gig SFP I2C"
	<send>		"show port 2/0 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
	<bypass>	$XGLC_10gigSFP_gbl[2][1]
	<send>		"show port 2/1 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
 	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<bypass>	$XGLC_10gigLRSFP_gbl[2][0]
	<msg>		"Check slot 2 10gig SFP I2C"
	<send>		"show port 2/0 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
	<bypass>	$XGLC_10gigLRSFP_gbl[2][1]
	<send>		"show port 2/1 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
 	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<bypass>	$XGLC_10gigSFP_gbl[3][0]
	<msg>		"Check slot 3 10gig SFP I2C"
	<send>		"show port 3/0 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
	<bypass>	$XGLC_10gigSFP_gbl[3][1]
	<send>		"show port 3/1 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
 	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<bypass>	$XGLC_10gigLRSFP_gbl[3][0]
	<msg>		"Check slot 3 10gig SFP I2C"
	<send>		"show port 3/0 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
	<bypass>	$XGLC_10gigLRSFP_gbl[3][1]
	<send>		"show port 3/1 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
 	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
  <bypass>	$XGLC_10gigSFP_gbl[4][0]
	<msg>		"Check slot 4 10gig SFP I2C"
	<send>		"show port 4/0 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
	<bypass>	$XGLC_10gigSFP_gbl[4][1]
	<send>		"show port 4/1 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"

</Bypass>
<Bypass>	$Slot_INST_4_GBL
  <bypass>	$XGLC_10gigLRSFP_gbl[4][0]
	<msg>		"Check slot 4 10gig SFP I2C"
	<send>		"show port 4/0 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"
	<bypass>	$XGLC_10gigLRSFP_gbl[4][1]
	<send>		"show port 4/1 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "10GBASE-[S,L]R"
    <CheckData>		"Connector-B"
	<CheckData>	    "10GBASE-[S,L]R"

</Bypass>

<Bypass>	$Slot_INST_1_GLC_GBL
	<bypass>	$XGLC_1gigSFP_gbl[1][0]
	<msg>		"Check slot 1 1gig SFP I2C"
	<send>		"show port 1/0 detail redundancy"
	<wait>
	<getdata>
    <CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-SX"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-SX"
	<bypass>	$XGLC_1gigSFP_gbl[1][1]
	<send>		"show port 1/1 detail redundancy"
	<wait>
	<getdata>
   <CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-SX"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-SX"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_1_GLC_GBL
	<bypass>	$XGLC_1gigCopperSFP_gbl[1][0]
	<msg>		"Check slot 1 1gig SFP I2C"
	<send>		"show port 1/0 detail redundancy"
	<wait>
	<getdata>
    <CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-T"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-T"
	<bypass>	$XGLC_1gigCopperSFP_gbl[1][1]
	<send>		"show port 1/1 detail redundancy"
	<wait>
	<getdata>
   <CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-T"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-T"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<bypass>	$XGLC_1gigSFP_gbl[2][0]
	<msg>		"Check slot 2 1gig SFP I2C"
	<send>		"show port 2/0 detail redundancy"
	<wait>
	<getdata>
    <CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-SX"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-SX"
	<bypass>	$XGLC_1gigSFP_gbl[2][1]
	<send>		"show port 2/1 detail redundancy"
	<wait>
	<getdata>
   <CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-SX"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-SX"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_2_GBL
	<bypass>	$XGLC_1gigCopperSFP_gbl[2][0]
	<msg>		"Check slot 2 1gig SFP I2C"
	<send>		"show port 2/0 detail redundancy"
	<wait>
	<getdata>
    <CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-T"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-T"
	<bypass>	$XGLC_1gigCopperSFP_gbl[2][1]
	<send>		"show port 2/1 detail redundancy"
	<wait>
	<getdata>
   <CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-T"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-T"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<bypass>	$XGLC_1gigSFP_gbl[3][0]
	<msg>		"Check slot 3 1gig SFP I2C"
	<send>		"show port 3/0 detail redundancy"
	<wait>
	<getdata>
   <CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-SX"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-SX"
	<bypass>	$XGLC_1gigSFP_gbl[3][1]
	<send>		"show port 3/1 detail redundancy"
	<wait>
	<getdata>
   <CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-SX"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-SX"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_3_GBL
	<bypass>	$XGLC_1gigCopperSFP_gbl[3][0]
	<msg>		"Check slot 3 1gig SFP I2C"
	<send>		"show port 3/0 detail redundancy"
	<wait>
	<getdata>
   <CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-T"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-T"
	<bypass>	$XGLC_1gigCopperSFP_gbl[3][1]
	<send>		"show port 3/1 detail redundancy"
	<wait>
	<getdata>
   <CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-T"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-T"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
  <bypass>	$XGLC_1gigSFP_gbl[4][0]
	<msg>		"Check slot 4 1gig SFP I2C"
	<send>		"show port 4/0 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-SX"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-SX"
	<bypass>	$XGLC_1gigSFP_gbl[4][1]
 	<send>		"show port 4/1 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-SX"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-SX"
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_4_GBL
  <bypass>	$XGLC_1gigCopperSFP_gbl[4][0]
	<msg>		"Check slot 4 1gig SFP I2C"
	<send>		"show port 4/0 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-T"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-T"
	<bypass>	$XGLC_1gigCopperSFP_gbl[4][1]
 	<send>		"show port 4/1 detail redundancy"
	<wait>
	<getdata>
	<CheckData>		"Connector-P"
	<CheckData>	    "1000BASE-T"
    <CheckData>		"Connector-B"
	<CheckData>	    "1000BASE-T"
	</Bypass>
</Bypass>






