################################################################################
#
# Module:      Check_Voltage_XGLC.inc
#
# Author:      Joe White
#
# Descr:       Check Voltages and Contoller in Stokeboot
#
# Version:    1.2 $Id: Check_Voltage_XGLC.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
#
#
# Changes:    Created 11/28/11
#			  Debug on clearing power fail counters.  Still not working.
#
# Includes:
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################


<Msg>       "Checking DC voltages ..."
<Send>      "monitor voltage test"
<Wait>
<CheckData>	"Voltage supply test PASSED"
<CheckData>	"Debug_Fault_Count test PASSED"
<CheckData>	"Debug_Max_Fault_Count test PASSED"
<CheckData>	"Debug_PON_Fail_Count test PASSED"
<CheckData>	"Debug_Lost_Volt_Count test PASSED"
<CheckDataX>	"FAILED"
<GetData>

<Msg>       "Test PSOC version..."
# mw.b ffdf001d 1;  i2c dev 0 ;i2c mw 70 0 4 1 ;i2c probe
<Send>      " mw.b ffdf001d 1"
<Wait>
<Send>      "i2c dev 0"
<Wait>
<Send>      "i2c mw 70 0 4 1 "
<Wait>
<Send>      "i2c probe"
<Wait>
<GetData>
<CheckData> "Valid chip addresses: 50 70 7C 7E"
<Send>      "i2c md 7c 0 100"
<Wait>
<GetData>
<CheckData> "0060: 50 53 4f 43 58 47 4c 43 10 1e 09 e0 69 03 00 00"
<Send>      "i2c md 7e 0 100"
<Wait>
<GetData>

<Msg>       "Get PSOC MAX Voltage..."
#Max_Volt	32	R	0x10-0x2F	Max reading for each voltage
<Send>      "i2c md 7c 10 1F"
<Wait>
<GetData>

<Msg>       "Get PSOC MIN Voltage..."
#32	R	0x30-0x4F	Min reading for each voltage
<Send>      "i2c md 7c 30 1F"
<Wait>
<GetData>

<Msg>       "Get PSOC Power Retry Count..."
#Retry_Count	1	R	0xF0	Number of Retries (re-sequenced) from Power on
<Send>      "i2c md 7c F0 1"
<Wait>
<GetData>
<CheckData>	"00"

<Msg>       "Get PSOC Voltage Fault Count..."
#Volt_Fault_Count	32	R	0x20-0x3F	Fault Counter for each Monitored Voltage zeroed if non-sequential
<Send>      "i2c md 7e 20 1F"
<Wait>
<GetData>
<CheckData>	"0020: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
<CheckData>	"0030: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"

<Msg>       "Get PSOC Debug Fault Count..."
#Debug_Flt_Cnt	32	R	0x40-0x5F	Fault Counter for each Monitored Voltage not zeroed
<Send>      "i2c md 7e 40 1F"
<Wait>
<GetData>
<CheckData>	"0040: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
<CheckData>	"0050: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"

<Msg>       "Get PSOC Debug Max Fault Count..."
#Debug_Max_Flt_Cnt	32	R/EEPROM	0x60-0x7F	Max Fault Counter for each Monitored Voltage
#and the two VRM power good signals (causes retry)
<Send>      "i2c md 7e 60 1F"
<Wait>
<GetData>
<CheckData>	"0060: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
<CheckData>	"0070: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"

<Msg>       "Get PSOC Debug PON Fault Count..."
#Debug_PON_Fail_Cnt	32	R/EEPROM	0x80-0x9F	Initial voltage low Counter for each Sequenced Group (causes retry)
<Send>      "i2c md 7e 80 1F"
<Wait>
<GetData>
<CheckData>	"0080: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
<CheckData>	"0090: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"

<Msg>       "Get PSOC Lost Voltage Fault Count..."
#Debug_Lost_Volt_Cnt	32	R/EEPROM	0xA0-0xBF	 Initial voltage met minimum high but
#then went out of range  before PON sequencing completed
<Send>      "i2c md 7e a0 1F"
<Wait>
<GetData>
<CheckData>	"00a0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"
<CheckData>	"00b0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"

<Msg>       "Get PSOC Retry Reason..."
#Retry_Reason	1	R	0xF0	Retry power supply number and type of failure
<Send>      "i2c md 7e f0 0"
<Wait>
<GetData>
<CheckData>	"00"

<Msg>       "Get PSOC Unknown Retry Reason..."
#Unknown_Retry_Reason_Cnt	1	R	0xF6	Debug - halt routine entered with invalid retry code counter
<Send>      "i2c md 7e f6 1"
<Wait>
<GetData>
<CheckData>	"00"

<Msg>       "Get PSOC EEPROM Error Count..."
#EEPROM_Error_Cnt	1	R	0xF1	EEPROM write error counter
<Send>      "i2c md 7e f1 1"
<Wait>
<GetData>
<CheckData>	"00"

<Msg>       "Clear PSOC Error Registers..."
#Clear EEPROM Error Registers	0x01   i2c mw add offest data
# 		            Command  ;    Command Available
<Send>      "i2c mw 7c 1 1; i2c mw 7c 0 5a;"
<Wait>
<GetData>
<Sleep> 2
# Check if command completed OK
<Send>      "i2c md 7c 00 1"
<Wait>
<GetData>
<CheckData>	"a5"

<Msg>       "Clear PSOC Retry Registers..."
#Clear Retry Register	0x02   i2c mw add offest data
# 		            Command  ;    Command Available
<Send>      "i2c mw 7c 1 2; i2c mw 7c 0 5a;"
<Wait>
<GetData>
# Check if command completed OK
<Sleep> 2
<Send>      "i2c md 7c 00 1"
<Wait>
<GetData>
<CheckData>	"a5"


