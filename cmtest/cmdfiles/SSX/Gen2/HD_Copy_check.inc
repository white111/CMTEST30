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

<Send>		"pfeffa wr i2c 9501 fan1 gpio E7"
<Wait>
<Sleep>		1
<Send>		"pfeffa wr i2c 9501 fan2 gpio E7"
<Wait>
<Sleep>		1
<Bypass>	$UUT_Variable_ref[22]->{FAN2}
	<Msg>		"Copy Speed Check 33% Fan..."
	<Send>		"pfeffa wr i2c adm1029 1 60 55"
	<Wait>
	<Sleep>		1
	<Send>		"pfeffa wr i2c adm1029 2 60 55"
	<Wait>
	<Include>   HD_Copy_check_2.inc
	<Msg>		"Copy Speed Check 40% Fan..."
	<Send>		"pfeffa wr i2c adm1029 1 60 66"
	<Wait>
	<Sleep>		1
	<Send>		"pfeffa wr i2c adm1029 2 60 66"
	<Wait>
	<Include>   HD_Copy_check_2.inc
	<Msg>		"Copy Speed Check 53% Fan..."
	<Send>		"pfeffa wr i2c adm1029 1 60 88"
	<Wait>
	<Sleep>		1
	<Send>		"pfeffa wr i2c adm1029 2 60 88"
	<Wait>
	<Include>   HD_Copy_check_2.inc
	<Msg>		"Copy Speed Check 73% Fan..."
	<Send>		"pfeffa wr i2c adm1029 1 60 bb"
	<Wait>
	<Sleep>		1
	<Send>		"pfeffa wr i2c adm1029 2 60 bb"
	<Wait>
	<Include>   HD_Copy_check_2.inc
	<Msg>		"Copy Speed Check 100% Fan1..."
	<Send>		"pfeffa wr i2c adm1029 1 60 ff"
	<Wait>
	<Sleep>		1
	<Send>		"pfeffa wr i2c adm1029 2 60 55"
	<Wait>
	<Include>   HD_Copy_check_2.inc
	<Msg>		"Copy Speed Check 100% Fan2..."
	<Send>		"pfeffa wr i2c adm1029 1 60 55"
	<Wait>
	<Sleep>		1
	<Send>		"pfeffa wr i2c adm1029 2 60 FF"
	<Wait>
</bypass>
<Include>   HD_Copy_check_2.inc

<Include>   Set_Fan_Speed.inc
