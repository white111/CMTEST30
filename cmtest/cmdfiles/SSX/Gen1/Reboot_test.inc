################################################################################
#
# Module:      Reboot_test.inc
#
# Author:      Joe White
#
# Descr:       Main Execution for IMC Bench test
#
# Version:    1.1 $Id: Reboot_test.inc,v 1.2 2009/09/28 17:21:45 joe Exp $
#
# Changes:    Added 4/1/09 due to unstable Ethernet management ports
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2009 Stoke. All rights reserved.
#
################################################################################

<Msg>		"Test Ethernet Management port"
<Loop>		1500
	<TimeOut>	30
    <Prompt>	"#"
	<Send>		'on -p 3r -f /net/nv-1-0 shutdown'
	<Wait>
	<GetData>
	<Prompt>	"QNX"
	<Send>		'shutdown'
	<Wait>
	<GetData>
	<Power>		OFF
	<Sleep>		5
	<Power>		ON
	<TimeOut>	150
	<Msg>		"Wait for IMC boot ..."
	<Prompt>	"#"
	<Send>
	<Wait>
	<GetData>
	<TimeOut>	10
	<Msg> 'Waiting for Cards to start...'
	<send>	'integer long mytime=`date -t`+(60*3)'
	<Wait>
	<TimeOut>	190
	<Sendslow>	'echo -n Waiting;while  (  ( ! (on -p 3r -f /net/nv-0-0 pidin | grep -q -e "lc_download_server" -e "postDiagReceiver") && ((${mytime} > (`date -t`))) )  && (  if ! (on -p 3r -f /net/nv-0-0 > /dev/null 2>&1) then (echo "*";) fi )  )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT Slot 0) fi ; sleep 2; echo -n .) done; echo'
	<Wait>
	<CheckDataX>	'Wait TIMEOUT Slot 0'
	<GetData>
	<Sendslow>	'echo -n Waiting;while  (  ( ! (on -p 3r -f /net/nv-1-0 pidin | grep -q -e "lc_download_server" -e "postDiagReceiver") && ((${mytime} > (`date -t`))) )  && (  if ! (on -p 3r -f /net/nv-1-0 > /dev/null 2>&1) then (echo "*";) fi )  )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT Slot 1) fi ; sleep 2; echo -n .) done; echo'
	<Wait>
	<CheckDataX>	'Wait TIMEOUT Slot 1'
	<GetData>
	<Sendslow>	'echo -n Waiting;while  (  ( ! (on -p 3r -f /net/nv-2-0 pidin | grep -q -e "lc_download_server" -e "postDiagReceiver") && ((${mytime} > (`date -t`))) )  && (  if ! (on -p 3r -f /net/nv-1-0 > /dev/null 2>&1) then (echo "*";) fi )  )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT Slot 2) fi ; sleep 2; echo -n .) done; echo'
	<Wait>
	<CheckDataX>	'Wait TIMEOUT Slot 2'
	<GetData>
	<TimeOut>	60
	<Sendslow>	'echo -n Waiting;while  (  ( ! (on -p 3r -f /net/nv-3-0 pidin | grep -q -e "lc_download_server" -e "postDiagReceiver") && ((${mytime} > (`date -t`))) )  && (  if ! (on -p 3r -f /net/nv-1-0 > /dev/null 2>&1) then (echo "*";) fi )  )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT Slot 3) fi ; sleep 2; echo -n .) done; echo'
	<Wait>
	<CheckDataX>	'Wait TIMEOUT Slot 3'
	<GetData>
	<Sendslow>	'echo -n Waiting;while  (  ( ! (on -p 3r -f /net/nv-4-0 pidin | grep -q -e "lc_download_server" -e "postDiagReceiver") && ((${mytime} > (`date -t`))) )  && (  if ! (on -p 3r -f /net/nv-1-0 > /dev/null 2>&1) then (echo "*";) fi )  )    do  ( if ((${mytime} <= ((`date -t`)+2))) then (echo Wait TIMEOUT Slot 4) fi ; sleep 2; echo -n .) done; echo'
	<Wait>
	<CheckDataX>	'Wait TIMEOUT Slot 4'
	<GetData>

	<include>		Check_swbase.inc


	<send>	' if (pfeffa show cpld | grep 'F400002B       flash-rdndnt-ctl-stat  05') then (echo "Slot 0 Booted on Primary Flash") else (pfeffa show cpld) fi'
	<wait>
	<Getdata>
	<CheckData> 'Slot 0 Booted on Primary Flash'

	<send>	' if (pfeffa on 1 show cpld | grep 'F400002B       flash-rdndnt-ctl-stat  05') then (echo "Slot 1 Booted on Primary Flash") else (pfeffa on 1 show cpld) fi'
	<wait>
	<Getdata>
	<CheckData> 'Slot 1 Booted on Primary Flash'

	<send>	' if (pfeffa on 2 show cpld | grep 'F400002B       flash-rdndnt-ctl-stat  05') then (echo "Slot 2 Booted on Primary Flash") else (pfeffa on 2 show cpld) fi'
	<wait>
	<Getdata>
	<CheckData> 'Slot 2 Booted on Primary Flash'

	<send>	' if (pfeffa on 3 show cpld | grep 'F400002B       flash-rdndnt-ctl-stat  05') then (echo "Slot 3 Booted on Primary Flash") else (pfeffa on 3 show cpld) fi'
	<wait>
	<Getdata>
	<CheckData> 'Slot 3 Booted on Primary Flash'

	<send>	' if (pfeffa on 4 show cpld | grep 'F400002B       flash-rdndnt-ctl-stat  05') then (echo "Slot 4 Booted on Primary Flash") else (pfeffa on 4 show cpld) fi'
	<wait>
	<Getdata>
	<CheckData> 'Slot 4 Booted on Primary Flash'

#    <Sendslow>  'if    (on -p 3r -f /net/nv-0-0 pidin | grep -q -e "lc_download_server" -e "postDiagReceiver")  then  ( echo "Slot 0 Startup PASSED") else ( echo "Slot 0 Startup FAILED") fi;'
#    <Wait>
#    <Sendslow>  'if    (on -p 3r -f /net/nv-1-0 pidin | grep -q -e "lc_download_server" -e "postDiagReceiver")  then  ( echo "Slot 1 Startup PASSED") else ( echo "Slot 1 Startup FAILED") fi;'
#    <Wait>
#    <Sendslow>  'if    (on -p 3r -f /net/nv-2-0 pidin | grep -q -e "lc_download_server" -e "postDiagReceiver")  then  ( echo "Slot 2 Startup PASSED") else ( echo "Slot 2 Startup FAILED") fi;'
#    <Wait>
#    <Sendslow>  'if    (on -p 3r -f /net/nv-3-0 pidin | grep -q -e "lc_download_server" -e "postDiagReceiver")  then  ( echo "Slot 3 Startup PASSED") else ( echo "Slot 3 Startup FAILED") fi;'
#    <Wait>
#    <Sendslow>  'if    (on -p 3r -f /net/nv-4-0 pidin | grep -q -e "lc_download_server" -e "postDiagReceiver")  then  ( echo "Slot 4 Startup PASSED") else ( echo "Slot 4 Startup FAILED") fi;'
#    <Wait>

</Loop>
