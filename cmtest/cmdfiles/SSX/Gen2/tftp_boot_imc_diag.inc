 ################################################################################
#
# Module:      tftp_boot_imc_diag.inc
#
# Author:      Joe White
#
# Descr:       TFTP boots system from STOKE>> prompt to released Diag image
#
# Version:    2.8 $Id: tftp_boot_imc_diag.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Added <GetData> 12/05/05
#			  Updated for R1 release 010506
#             Updated for 12/01/07 Diag
#             Change defual KSH priority 051508
#			  6/16/09 Added check for  got an old packet so resend ack
#			  8/5/09 removed got an old packet so resend ack
#			  1/11/11 Removing /hd/dump directories.  Issue with different sizes
#			  1/31/12 Added set terminal width
##			  8/27/14 Updateds for 13.1 Diags
# Includes:
#
#
#
# Still ToDo:
#                 Check for "got an old packet so resend ack"
#
#            Copyright (c) 2005-2014 Stoke. All rights reserved.
#
################################################################################
# TFTP Boot an IMC
#GW_IP_IP		=	92.168.64.254
# unix HOST_IP		=	192.168.64.252
# Windows
#HOST_IP		=	192.168.64.113
#UUT_IP_Base	=	192.168.64.130
#UUT_IP_Range	=	2
<Msg>		"TFTP Booting Diags..."
<TimeOut>	2
<Prompt>	"Stoke-BootLoader#"
#<Send>		'setenv ethaddr 00:12:73:FF:2:10'
#<Wait>
<Sleep>		5
<SendChar>		'boot image tftp '
<SendChar>		$tftp_bootpath_diag_gbl
<SendChar>		$Stoke_diag_xglc
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
<TimeOut>	90
<Send>		'go'
<Prompt>	'#'
<sleep>  30
#<WaitFor>    'Stoke HWTEST IMC IFS'
#<WaitFor>    "Card type is MC"
<Wait>
<GetData>
<CheckDataX>  "tftp file transfer error"
<CheckDataX>  "got an old packet so resend ack"

<TimeOut>	120
# Make sure this system message does not pop out in the miidle of tests
#<WaitFor>     "System process not started within designated time"
#<WaitFor>     "DiagMgr"
<Sleep> 5
<Send>
<Wait>

<msg>		"Dropping KSH priority to 7f"
<Send>		'on -p 7f ksh'
<Wait>
<GetData>

<msg>		"Set terminal Column width"
<Send>		'COLUMNS=160'
<Wait>
<GetData>


#<Sleep>		10
<TimeOut>	30
#<Include>	Check_HDP_Log_Error.inc
<Bypass>	$HA_Session
		<Msg>	"Check IMC slot 1"
		<Exec>	Swap_cons
 		<Send>
		<Wait>
		#<Include>	Check_HDP_Log_Error.inc
		<Exec>	Swap_cons
        <Send>
		<Wait>
</Bypass>


