################################################################################
#
# Module:      Ship_config.inc
#
# Author:      Joe White
#
# Descr:       Creates a default configuration
#
# Version:    1.7 $Id: Ship_config.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Modified to created configuration, without deliting first
#			  May be Causing Event log Warnings
#			  Added final check of clock 4/3/08
#			  Added dir of cfint and hd 8/20/01
#			  1/11/11 Added dir of /hd/dump and /hd/logs , Config Clear response change
#			  Added Check of CF Files size 011812 Bug18719
#			  6/10/13 Prompt changes in 6.1R2/13.1
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2006-2013 Stoke. All rights reserved.
#
################################################################################


<Msg>		"Setup Shipping Config ..."
<Msg>		"Config Management port..."
<TimeOut>	10
<Prompt>	"[local]#"
<Prompt>	'Proceed'
<Send>		'config clear'
<Wait>
<Prompt>	"[local]#"
<Send>		'yes'
<Wait>

# Add this in if we want a defaul IP address for the Management port
#<Prompt>	'Stoke(cfg)#'
#<Send>		'config'
#<Wait>
#<Prompt>	'Stoke(cfg-ctx)#'
#<Send>		'context local'
#<Wait>
#<Send>		'no interface mgmt'
#<Wait>
#<Prompt>	'Stoke(cfg-intfv4)#'
#<Send>		'interface mgmt'
#<Wait>
#<Prompt>	'Stoke(cfg-intfv4)#'
#<Msg>		'Set management port IP..'
#<SendChar>	'ip address '

#<SendChar>	'192.168.1.2'

#<Send>		'/24'
#<Wait>
#<Send>		'arp arpa'
#<Wait>
#<Prompt>	'Stoke(cfg-ctx)#'
#<Send>		'exit'
#<Wait>
#<Prompt>	'Stoke(cfg)#'
#<Send>		'exit'
#<Wait>
#<Prompt>	'Stoke(cfg-port)#'
#<Msg>		'Un-Set Port 0/0..'
#<Send>		'no port ethernet 0/0'
#<Wait>
#<Sleep>		5
#<Msg>		'Disable  Port...'
#<Send>		'no enable'
#<Wait>
#<Sleep>		10
#<Msg>		'Exit Configuration...'
#<Prompt>	'cfg-bindv4'
#<Send>		'no bind interface mgmt local'
#<Wait>
#<Prompt>	'Stoke(cfg-port)#'
#<Send>		'exit'
#<Wait>
#<Prompt>	'Stoke(cfg)#'
#<Send>		'exit'
#<Wait>
#<Msg>		'Save Configuration to stoke.cfg'
#<Prompt>	'Stoke[local]#'
#<Send>		'exit'
#<Wait>
#delete any old config files
#<Send>		'del stoke.cfg'
#<Wait>
<Send>		'del stoke.cfg'
<Wait>
<Send>		'boot configuration file stoke.cfg'
<Waitfor>   ']'
<Send>		"yes"
<wait>
<Send>		'del stoke.cfg'
<Wait>
<Send>		'config save stoke.cfg'
<Waitfor>   ']'
<Send>		"yes"
<Wait>
<Send>		'config load stoke.cfg'
<Wait>

<Exec>		Getmytime
<timeout>   5
#<send>      $sysclock_OS_set_glb
#<waitfor>   yes
#<Send>      yes
#<wait>
<Send>      show clock
<wait>
<Getdata>   IMC_Clock_OS

<Send>		'dir /cfint'
<Wait>
<GetData>
<CheckData>	"File system: size 128,974,848"
<Send>		'dir /hd'
<Wait>
<GetData>
<Send>		'dir /hd/dump'
<Wait>
<GetData>
<Send>		'dir /hd/logs'
<Wait>
<GetData>

