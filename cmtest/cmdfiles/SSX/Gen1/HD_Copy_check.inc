################################################################################
#
# Module:      tftpcopy_stoke_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Config.dat
#
# Version:    1.3   $Id: tftpcopy_stoke_diag_XGLC.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    Created 12/2011 from tftpcopy_stoke 12/12/11
#			  Increased blksize to 2048 7/30/12
#			  Added delete of inactive GLC console files 8/1/12

#
#
# Still ToDo:
#             Add rm *core* to each dump directory
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

<Sleep>		1
<GetData>
<send>
<Wait>

<Msg>		"Copy Speed Check..."
<Sleep>		5
<Prompt>	'#'
    <Msg>	"Copy IMC Slot 0 HD stoke.pkg files..."
	<Timeout>	90
	<Sendchr>      "if (time cp -vp /hd/"
	<sendchr>	$StokeOS_ISSU_Install_gbl
	<send>		" /hd/temp.tmp) then (echo "HD_Copy_PASSED") else (echo "HD_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"HD_Copy_PASSED"
	<GetData>	Check_XGLC_HD_Copytime
    <sleep>		5
    <Msg>	"Copy IMC Slot 0 HD stoke.pkg files...."
	<Timeout>	90
	<Sendchr>      "if (time cp -vp /hd/"
	<sendchr>	$StokeOS_ISSU_Install_gbl
	<send>		" /hd/temp.tmp) then (echo "HD_Copy_PASSED") else (echo "HD_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"HD_Copy_PASSED"
	<GetData>	Check_XGLC_HD_Copytime
    <sleep>		5
    <Msg>	"Copy IMC Slot 0 HD stoke.pkg files....."
	<Timeout>	90
	<Sendchr>      "if (time cp -vp /hd/"
	<sendchr>	$StokeOS_ISSU_Install_gbl
	<send>		" /hd/temp.tmp) then (echo "HD_Copy_PASSED") else (echo "HD_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"HD_Copy_PASSED"
	<GetData>	Check_XGLC_HD_Copytime
    <sleep>		10
    <Msg>	"Copy IMC Slot 0 HD stoke.pkg files......"
	<Timeout>	90
	<Sendchr>      "if (time cp -vp /hd/"
	<sendchr>	$StokeOS_ISSU_Install_gbl
	<send>		" /hd/temp.tmp) then (echo "HD_Copy_PASSED") else (echo "HD_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"HD_Copy_PASSED"
	<GetData>	Check_XGLC_HD_Copytime
    <sleep>		10
    <Msg>	"Copy IMC Slot 0 HD stoke.pkg files......."
	<Timeout>	90
	<Sendchr>      "if (time cp -vp /hd/"
	<sendchr>	$StokeOS_ISSU_Install_gbl
	<send>		" /hd/temp.tmp) then (echo "HD_Copy_PASSED") else (echo "HD_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"HD_Copy_PASSED"
	<GetData>	Check_XGLC_HD_Copytime
<Bypass>	$Slot_INST_1_IMC_GBL
    <Msg>	"Copy IMC Slot 1 HD stoke.pkg files..."
	<Timeout>	90
	<Sendchr>      "if (time on -f /net/nv-1-0 cp -vp /hd/"
	<sendchr>	$StokeOS_ISSU_Install_gbl
	<send>		" /hd/temp.tmp) then (echo "HD_Copy_PASSED") else (echo "HD_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"HD_Copy_PASSED"
	<GetData>	Check_XGLC_HD_Copytime
    <sleep>		5
    <Msg>	"Copy IMC Slot 1 HD stoke.pkg files...."
	<Timeout>	90
	<Sendchr>      "if (time on -f /net/nv-1-0 cp -vp /hd/"
	<sendchr>	$StokeOS_ISSU_Install_gbl
	<send>		" /hd/temp.tmp) then (echo "HD_Copy_PASSED") else (echo "HD_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"HD_Copy_PASSED"
	<GetData>	Check_XGLC_HD_Copytime
    <sleep>		5
    <Msg>	"Copy IMC Slot 1 HD stoke.pkg files....."
	<Timeout>	90
	<Sendchr>      "if (time on -f /net/nv-1-0 cp -vp /hd/"
	<sendchr>	$StokeOS_ISSU_Install_gbl
	<send>		" /hd/temp.tmp) then (echo "HD_Copy_PASSED") else (echo "HD_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"HD_Copy_PASSED"
	<GetData>	Check_XGLC_HD_Copytime
    <sleep>		10
    <Msg>	"Copy IMC Slot 1 HD stoke.pkg files......"
	<Timeout>	90
	<Sendchr>      "if (time on -f /net/nv-1-0 cp -vp /hd/"
	<sendchr>	$StokeOS_ISSU_Install_gbl
	<send>		" /hd/temp.tmp) then (echo "HD_Copy_PASSED") else (echo "HD_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"HD_Copy_PASSED"
	<GetData>	Check_XGLC_HD_Copytime
    <sleep>		10
    <Msg>	"Copy IMC Slot 1 HD stoke.pkg files......."
	<Timeout>	90
	<Sendchr>      "if (time on -f /net/nv-1-0 cp -vp /hd/"
	<sendchr>	$StokeOS_ISSU_Install_gbl
	<send>		" /hd/temp.tmp) then (echo "HD_Copy_PASSED") else (echo "HD_Copy_FAILED")  fi"
	<Wait>
	<CheckData>	"HD_Copy_PASSED"
	<GetData>	Check_XGLC_HD_Copytime
</Bypass>

