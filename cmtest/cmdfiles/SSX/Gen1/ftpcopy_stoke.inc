################################################################################
#
# Module:      ftpcopy_stoke.inc.inc
#
# Author:      Joe White
#
# Descr:       tftpcopy files from Stoke OS
#
# Version:    1.1 $Id: ftpcopy_stoke.inc,v 1.3 2009/05/07 15:50:10 joe Exp $
#
# Changes:     Deprecieated, using tftpcopy from diag image
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
# TFTP Boot an IMC
#GW_IP_IP		=	92.168.64.254
# unix HOST_IP		=	192.168.64.252
# Windows
#HOST_IP		=	192.168.64.113
#UUT_IP_Base	=	192.168.64.130
#UUT_IP_Range	=	2

#context local
# interface mgt management
#  arp arpa
#  ip address 172.17.24.11/24
#  exit
# interface management
#  exit
# exit
#port ethernet 0/0
# enable
# exit


<Msg>		"FTP Copy to Cfint ..."
<Msg>		"Config Management port..."
<TimeOut>	10
<Prompt>	'Stoke[local]#'
<Send>		'config clear'
<Wait>
<Prompt>	'Stoke(cfg)#'
<Send>		'config'
<Wait>
<Prompt>	'Stoke(cfg-ctx)#'
<Send>		'context local'
<Wait>
<Prompt>	'Stoke(cfg-intfv4)#'
<Send>		'interface mgmt'
<Wait>
<Prompt>	'Stoke(cfg-intfv4)#'
<Msg>		'Set management port IP..'
<SendChar>	'ip address '

<SendChar>	$UUT_IP

<Send>		'/24'
<Wait>
<Send>		'arp arpa'
<Wait>
<Prompt>	'Stoke(cfg-ctx)#'
<Send>		'exit'
<Wait>
<Prompt>	'Stoke(cfg)#'
<Send>		'exit'
<Wait>
<Prompt>	'Stoke(cfg-port)#'
<Msg>		'Set Port 0/0..'
<Send>		'port ethernet 0/0'
<Wait>
<Sleep>		5
<Msg>		'Set Enable Port...'
<Send>		'enable'
<Wait>
<Sleep>		10
<Msg>		'Exit Configuration...'
<Prompt>	'cfg-bindv4'
<Send>		'bind interface mgmt local'
<Wait>
<Prompt>	'Stoke(cfg-port)#'
<Send>		'exit'
<Wait>
<Prompt>	'Stoke(cfg)#'
<Send>		'exit'
<Wait>
<Msg>		'Save Configuration to stoke.cfg'
<Prompt>	'Stoke[local]#'
<Send>		'exit'
<Wait>
#delete any old config files
<Send>		'del Stoke.cfg'
<Wait>
<Send>		'config save'
<Wait>
#delete any old Stoke.bin
<Send>		'del Stoke.bin'
<Wait>
<Msg>		'Check port is up..'
<Send>		'show ip int'
<Wait>
<SendChar>	'ping '
<Send>		$HOST_IP
<Wait>
<CheckData>	'0.0% packet loss'
<TimeOut>	60
#<Send>		'copy ftp://anonymous:joe@192.168.64.252/pub/stoke.bin /cfint/stoke.bin'
#<Send>		'copy tftp://192.168.64.252/stoke.bin /cfint/stoke.bin'
<Msg>		'TFTP Copy file...'
<SendChar>	'copy tftp://'
<SendChar>	$HOST_IP
<Send>		'/stoke.bin /cfint/stoke.bin'
<Wait>
<TimeOut>	5
<Send>		'dir /cfint/stoke.bin'
<Wait>
<CheckData>	"stoke.bin"
<CheckDataX>	"         0 stoke.bin"



