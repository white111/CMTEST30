################################################################################
#
# Module:      i2c_scan_xglc.inc
#
# Author:      Joe White
#
# Descr:       Called by Bench_GLC.dat
#
# Version:    1.1 $Id: i2c_scan_xglc.inc,v 1.2 2012/02/17 17:13:41 joe Exp $
#
# Changes:    First Release  10/04/11
#			  11/28/07 Output format changed adding 2610-
#			  Updates for diag image 9/19/08
#			  Updates for PSOC replacement of Potentia
#
#
# Still ToDo:
#                U7065 Opto isolated 48vbus Address ?
# 20 M7002(NM)  21 M7004   22 M7005  23 M7006 24 M7008(NM) 25 M7010(NM)
# 26 M7032(NM)  27 M7031(NM)   28 M7016(NM)  29 M7018(NM) 2A M7020(NM)
# 2B M7022(NM)  2C M7024(NM) 2D M7026(NM)   2E M7028
#C0 U7074
#C0 U7076
#C0 U7080
#C0 U7082
#57 U128 Not Installed?
#57 U128 Not Installed?
#6E U6013
#?? U6025 Selectable Address
#44  U257 (Disconnected currentl a master I2C)
## 19 1A  P4080 or DDR3?
#51 SFP ??
#
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################

<prompt>	"Stoke>"
<Timeout>	5

<Msg>	"Check I2C Access"
#<Msg>   Check I2C bus 0 I2C to U68 MFG Local EEPROM
#<Send>  i2c probe
#<Wait>
#<Getdata>
#<Checkdata> "Valid chip addresses: 50"
#<Checkdatax> "Error"

#<msg>   "Check I2C bus 0 local bus"
##enable local i2c bus in cpld
#<Send>  "mw.b ffdf001d 1 ; i2c probe ; mw.b ffdf001d 0"
#<Wait>
#<Getdata>
##70 I2C U98 Switch
#<Checkdata> "Valid chip addresses: 50 70"
#<Checkdatax> "Error"


#<msg>   "Check I2C bus 0 Global bus"
##enable local i2c bus in cpld
#<Send>  "mw.b ffdf001e 1 ; i2c probe ; mw.b ffdf001e 0"
#<Wait>
#<Getdata>
##23 63 I2C U87 changes with slot ID
#<Checkdata> "Valid chip addresses: 23 50 63"
#<Checkdatax> "Error"

#<msg>   "Check I2C bus 0 local bus to Check U98 switch Port 0 U75 U86"
##enable local i2c bus in cpld
#<Send>  "mw.b ffdf001d 1 ; i2c dev 0 ; i2c mw 70 0 1 1; i2c probe ; mw.b ffdf001d 0"
#<Wait>
#<Getdata>
##LOC00_NPU_I2C1_SCL
##4C U75 NPU 0 temp sensor
##4D U86 NPU 1 Temp Senesor
#<Checkdata> "Valid chip addresses: 4C 4D 50 70"
#<Checkdatax> "Error"

#<msg>   "Check I2C bus 0 local bus to Check U98 switch Port 1 U88 U98 U81"
##enable local i2c bus in cpld
#<Send>  "mw.b ffdf001d 1 ; i2c dev 0 ; i2c mw 70 0 2 1; i2c probe ; mw.b ffdf001d 0"
#<Wait>
#<Getdata>
##48  U88 Inlet Temp Sensor
##4A  U98 Outlet Temp sensor
##4C  U81 P4080 Temp Sensor
#<Checkdata> "Valid chip addresses: 48 4A 4C 50 70"
#<Checkdatax> "Error"


#<msg>   "Check I2C bus 0 local bus to Check U98 switch Port 2 U7069"
##enable local i2c bus in cpld
#<Send>  "mw.b ffdf001d 1 ; i2c dev 0 ; i2c mw 70 0 4 1; i2c probe ; mw.b ffdf001d 0"
#<Wait>
#<Getdata>
##U7065 Opto isolated 48vbus Address ?
##7C  U7069 PSOC 0
##7E   U7069 PSOC 0
#<Checkdata> "Valid chip addresses: 50 70 7C 7E"
#<Checkdatax> "Error"

#<msg>   "Check I2C bus 0 local bus to Check U98 switch Port 2 U109"
##enable local i2c bus in cpld
##62 i2c1_enb_control    R/W 4   0011    cs_i2c1_enb_control_l
##en_i2c_pmbus   en_i2c1_vrm en_i2c1_mfg_boot_l  en_i2c1_cpubuf_l

#<Send>  "mw.b ffdf001d 1 ; mw.b ffdf0062 b; i2c dev 0 ; i2c mw 70 0 4 1; i2c probe ;mw.b ffdf0062 3; mw.b ffdf001d 0"
#<Wait>
#<Getdata>
## 20 M7002(NM)  21 M7004   22 M7005  23 M7006 24 M7008(NM) 25 M7010(NM)
## 26 M7032(NM)  27 M7031(NM)   28 M7016(NM)  29 M7018(NM) 2A M7020(NM)
## 2B M7022(NM)  2C M7024(NM) 2D M7026(NM)   2E M7028
##18 M7001
##2F  M7029
#<Checkdata> "Valid chip addresses: 18 2F 50 70 7C 7E"
#<Checkdatax> "Error"


#<msg>   "Check I2C bus 0 local to Check U98 switch Port 2 U104 Switch Port 0 U7074"
##enable local i2c bus in cpld
##62 i2c1_enb_control    R/W 4   0011    cs_i2c1_enb_control_l
##en_i2c_pmbus   en_i2c1_vrm en_i2c1_mfg_boot_l  en_i2c1_cpubuf_l

#<Send>  "mw.b ffdf001d 1 ; mw.b ffdf0062 7; i2c dev 0 ; i2c mw 70 0 4 1; i2c mw 72 0 1 1; i2c probe ;mw.b ffdf0062 3; mw.b ffdf001d 0"
#<Wait>
#<Getdata>
##C0 U7074    Needs control of NPU_VRM_VDD_CTLR_EN from U7069 Cypress PSOC power control
#<Checkdata> "Valid chip addresses: 50 60 70 72 7C 7E"
#<Checkdatax> "Error"

#<msg>   "Check I2C bus 0 local to Check U98 switch Port 2 U104 Switch Port 1 U7076"
##enable local i2c bus in cpld
##62 i2c1_enb_control    R/W 4   0011    cs_i2c1_enb_control_l
##en_i2c_pmbus   en_i2c1_vrm en_i2c1_mfg_boot_l  en_i2c1_cpubuf_l

#<Send>  "mw.b ffdf001d 1 ; mw.b ffdf0062 7; i2c dev 0 ; i2c mw 70 0 4 1; i2c mw 72 0 2 1; i2c probe ;mw.b ffdf0062 3; mw.b ffdf001d 0"
#<Wait>
#<Getdata>
##C0 U7076
#<Checkdata> "Valid chip addresses: 50 60 70 72 7C 7E"
#<Checkdatax> "Error"


#<msg>   "Check I2C bus 0 local to Check U98 switch Port 2 U104 Switch Port 2 U7080"
##enable local i2c bus in cpld
##62 i2c1_enb_control    R/W 4   0011    cs_i2c1_enb_control_l
##en_i2c_pmbus   en_i2c1_vrm en_i2c1_mfg_boot_l  en_i2c1_cpubuf_l

#<Send>  "mw.b ffdf001d 1 ; mw.b ffdf0062 7; i2c dev 0 ; i2c mw 70 0 4 1; i2c mw 72 0 4 1; i2c probe ;mw.b ffdf0062 3; mw.b ffdf001d 0"
#<Wait>
#<Getdata>
##C0 U7080
#<Checkdata> "Valid chip addresses: 50 60 70 72 7C 7E"
#<Checkdatax> "Error"

#<msg>   "Check I2C bus 0 local to Check U98 switch Port 2 U104 Switch Port 3 U7082"
##enable local i2c bus in cpld
##62 i2c1_enb_control    R/W 4   0011    cs_i2c1_enb_control_l
##en_i2c_pmbus   en_i2c1_vrm en_i2c1_mfg_boot_l  en_i2c1_cpubuf_l

#<Send>  "mw.b ffdf001d 1 ; mw.b ffdf0062 7; i2c dev 0 ; i2c mw 70 0 4 1; i2c mw 72 0 8 1; i2c probe ;mw.b ffdf0062 3; mw.b ffdf001d 0"
#<Wait>
#<Getdata>
##C0 U7082
#<Checkdata> "Valid chip addresses: 50 60 70 72 7C 7E"
#<Checkdatax> "Error"

#<msg>   "Check I2C bus 0 local bus to Check U98 switch Port 3 U128"
##enable local i2c bus in cpld
#<Send>  "mw.b ffdf001d 1 ; i2c dev 0 ; i2c mw 70 0 8 1; i2c probe ; mw.b ffdf001d 0"
#<Wait>
#<Getdata>
##57 U128 Not Installed?
##6E U6013
##??6A U6025 Selectable Address
##44  U257 (Disconnected currentl a master I2C)
#<Checkdata> "Valid chip addresses: 50 57 6A 6E 70"
#<Checkdatax> "Error"


# <msg>  "Check I2C bus 1"
##enable local i2c bus in cpld
#<Send>  "i2c dev 1;i2c probe"
#<Wait>
## 52 DDR EEPROM   #32 Temp Senso CN6004 DDR3 Dimm
## 51 DDR EEProm   #32 Temp Sensor CN6005 DDR3 Dimm
## 19 1A  P4080 or DDR3?
#<Getdata>
#<Checkdata> "Valid chip addresses: 19 1A 31 32 51 52"
#<Checkdatax> "Error"

# <msg>  "Check I2C bus 2"
##enable local i2c bus in cpld
#<Send>  "i2c dev 1;i2c probe"
#<Wait>
##No Devices
#<Getdata>
#<Checkdata> "Valid chip addresses:"
#<Checkdatax> "Error"

# <msg>  "Check I2C bus 3"
##enable local i2c bus in cpld
#<Send>  "i2c dev 3;i2c probe"
#<Wait>
##SFPP_SUBSYS_SCL
##75   U261 IO expander SFPs
##74  U260 IO expander to SFPs
##71 U103 Switch
#<Getdata>
#<Checkdata> "Valid chip addresses: 71 74 75"
#<Checkdatax> "Error"

# <msg>  "Check I2C bus 3 to U103 Switch 0"
##enable local i2c bus in cpld
#<Send>  "i2c dev 3;mw.b ffdf0063 4;i2c mw 71 0 1 1; i2c probe;mw.b ffdf0063 0"
#<Wait>
##63 I2C_ENB_SFP_CONTROL R/W 3   000 cs_i2c_enb_sfpp_l
##en_i2c_sfpp0123    en_sfpp_i2c_rsel_expn   en_sfpp_i2c_cntl_expn

##SFPP_SUBSYS_SCL
##50  SFP
##51 SFP ??
#<Getdata>
#<Checkdata> "Valid chip addresses: 50 71"
#<Checkdatax> "Error"

# <msg>  "Check I2C bus 3 to U103 Switch 1"
##enable local i2c bus in cpld
#<Send>  "i2c dev 3;mw.b ffdf0063 4;i2c mw 71 0 2 1; i2c probe;mw.b ffdf0063 0"
#<Wait>
##63 I2C_ENB_SFP_CONTROL R/W 3   000 cs_i2c_enb_sfpp_l
##en_i2c_sfpp0123    en_sfpp_i2c_rsel_expn   en_sfpp_i2c_cntl_expn

##SFPP_SUBSYS_SCL
##50  SFP
##51 SFP ??
#<Getdata>
#<Checkdata> "Valid chip addresses: 50 71"
#<Checkdatax> "Error"

# <msg>  "Check I2C bus 3 to U103 Switch 2"
##enable local i2c bus in cpld
#<Send>  "i2c dev 3;mw.b ffdf0063 4;i2c mw 71 0 2 1; i2c probe;mw.b ffdf0063 0"
#<Wait>
##63 I2C_ENB_SFP_CONTROL R/W 3   000 cs_i2c_enb_sfpp_l
##en_i2c_sfpp0123    en_sfpp_i2c_rsel_expn   en_sfpp_i2c_cntl_expn

##SFPP_SUBSYS_SCL
##50  SFP
##51 SFP ??
#<Getdata>
#<Checkdata> "Valid chip addresses: 50 71"
#<Checkdatax> "Error"

# <msg>  "Check I2C bus 3 to U103 Switch 4"
##enable local i2c bus in cpld
#<Send>  "i2c dev 3;mw.b ffdf0063 4;i2c mw 71 0 4 1; i2c probe;mw.b ffdf0063 0"
#<Wait>
##63 I2C_ENB_SFP_CONTROL R/W 3   000 cs_i2c_enb_sfpp_l
##en_i2c_sfpp0123    en_sfpp_i2c_rsel_expn   en_sfpp_i2c_cntl_expn

##SFPP_SUBSYS_SCL
##50  SFP
##51 SFP ??
#<Getdata>
#<Checkdata> "Valid chip addresses: 50 71"
#<Checkdatax> "Error"

#<msg>   "Check I2C bus 0 "
##enable local i2c bus in cpld
#<Send>  "i2c dev 0"
#<Wait>


<msg>	"Check I2C "
#enable local i2c bus in cpld
<Send>  "i2cscan"
<Wait>
<GetData>	Check_XGLC_I2C
#<CheckData> ".*Bus . 0, Switch.0 Port . 0,Valid chip addresses: 4C 4D 50 70.*"
#<CheckData> ".*Bus . 0, Switch.0 Port . 1,Valid chip addresses: 48 4A 4C 50 70.*"
#<CheckData> ".*Bus . 0, Switch.0 Port . 2,Valid chip addresses: 18 2F 50 70 72 7C 7E.*"
#<CheckData> ".*Bus . 0. Switch.0 Port . 2.Switch.1 Port . 0.Valid chip addresses: 50 60 70 72 7C 7E.*"
#<CheckData> ".*Bus . 0. Switch.0 Port . 2.Switch.1 Port . 1.Valid chip addresses: 50 60 70 72 7C 7E.*"
#<CheckData> ".*Bus . 0. Switch.0 Port . 2,Switch.1 Port . 2.Valid chip addresses: 50 60 70 72 7C 7E.*"
#<CheckData> ".*Bus . 0, Switch.0 Port . 2.Switch.1 Port . 3.Valid chip addresses: 50 60 70 72 7C 7E.*"
#<CheckData> ".*Bus . 0, Switch.0 Port . 3,Valid chip addresses: 50 57 6A 6E 70.*"
#<CheckData> ".*Bus . 1,Valid chip addresses: 19 1A 31 32 51 52.*"
#<CheckData> ".*Bus . 3, Switch Port . 0,Valid chip addresses: 50 71 74 75.*"
#<CheckData> ".*Bus . 3, Switch Port . 1,Valid chip addresses: 50 71 74 75.*"
#<CheckData> ".*Bus . 3, Switch Port . 2,Valid chip addresses: 50 71 74 75.*"
#<CheckData> ".*Bus . 3, Switch Port . 3,Valid chip addresses: 50 71 74 75.*"

#November 2011 builds of Stokeboot
#<CheckData> "Setting bus to 0"
#<CheckData> "Enabling local bus on bus 0"
#<CheckData> "Bus = 0. Switch #0 Port = 0"
#<CheckData> "Valid chip addresses: 4C 4D 50 70"
#<CheckData> "Bus = 0. Switch #0 Port = 1"
#<CheckData> "Valid chip addresses: 48 4A 4C 50 70"
#<CheckData> "Bus = 0. Switch #0 Port = 2"
#<CheckData> "VRM & PMBUS switch are enabled on bus 0"
#<CheckData> "Switch \#1 Port = 0"
#<CheckData> "Valid chip addresses: 18 2F 50 70 72 7C 7E"
#<CheckData> "Switch \#1 Port = 1"
#<CheckData> "Valid chip addresses: 0C 18 2F 50 70 72 7C 7E"
#<CheckData> "Switch \#1 Port = 2"
#<CheckData> "Valid chip addresses: 18 2F 50 70 72 7C 7E"
#<CheckData> "Switch \#1 Port = 3"
#<CheckData> "Valid chip addresses: 18 2F 50 70 72 7C 7E"
#<CheckData> "Bus = 0. Switch #0 Port = 3"
#<CheckData> "Valid chip addresses: 50 57 6A 6E 70"
#<CheckData> "Setting bus to 1"
#<CheckData> "Valid chip addresses: 19 1A 31 32 51 52"
#<CheckData> "Setting bus to 3"
#<CheckData> "Bus = 3. Switch Port = 0"
#<CheckData> "Valid chip addresses: 50 71 74 75"
#<CheckData> "Bus = 3. Switch Port = 1"
#<CheckData> "Valid chip addresses: 50 71 74 75"
#<CheckData> "Bus = 3. Switch Port = 2"
#<CheckData> "Valid chip addresses: 50 71 74 75"
#<CheckData> "Bus = 3. Switch Port = 3"
#<CheckData> "Valid chip addresses: 50 71 74 75"
