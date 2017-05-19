 ################################################################################
#
# Module:      tftp_boot_imc_stoke.inc
#
# Author:      Joe White
#
# Descr:       TFTP boots system from STOKE>> prompt to released Diag image
#
# Version:    1.0 $Id: tftp_boot_imc_stoke.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    12/2011 for 6.0 release

#
# Includes:
#
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################
# TFTP Boot an IMC
#GW_IP_IP		=	92.168.64.254
# unix HOST_IP		=	192.168.64.252
# Windows
#HOST_IP		=	192.168.64.113
#UUT_IP_Base	=	192.168.64.130
#UUT_IP_Range	=	2
<Msg>		"TFTP Booting Stoke Image..."
<TimeOut>	2
<Prompt>	"Stoke-BootLoader#"
#<Send>		'setenv ethaddr 00:12:73:FF:2:10'
#<Wait>
<Sleep>		5
<SendChar>		'boot image tftp '
<SendChar>		$tftp_copypath_release_gbl
<SendChar>		$Stoke_image
<SendChar>		' server '
<SendChar>		$HOST_IP
<SendChar>		' host-primary '
<SendChar>		$UUT_IP
#<Bypass>        $UUT_IP_HA
	<SendChar>		' host-secondary '
	<SendChar>		$UUT_IP_SEC
#</Bypass>
<SendChar>		' gateway '
<SendChar>		$GW_IP
<SendChar>		' '
<Send>			$Netmask
#<Send>			' /24'
<Wait>
<GetData>
<Sleep>		5
<TimeOut>	180
<Send>		'go'
<Prompt>	'Stoke[local]'

#<WaitFor>    'Stoke HWTEST IMC IFS'
#<WaitFor>    "Card type is MC"
<Wait>
<GetData>
<CheckDataX>  "tftp file transfer error"
<CheckDataX>  "got an old packet so resend ack"

