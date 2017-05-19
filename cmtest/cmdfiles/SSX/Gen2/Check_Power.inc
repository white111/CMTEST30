 ################################################################################
#
# Module:      Check_Power.inc
#
# Author:      Joe White
#
# Descr:       Called by Chassis_Post_BI.dat,Config.dat
#
# Version:    1.2  $Id: Check_Power.inc,v 1.1 2011/12/12 22:54:26 joe Exp $
#
# Changes:    Created 11/11/11 from Checkpotentia
#			  Added Support for XGLC in Slot 1 9/3/13
#			  Debug on clearing failult counters. Still not working in chassis 10/30/13
#		      Changed double commands to single commands. 11/18/13
#

#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2013 Stoke. All rights reserved.
#
################################################################################

<Prompt>	'slot 0:>'
<TimeOut>	40
<Send>		"pfeffa"
<wait>

<Bypass>	$UUT_Variable_ref[1]->{Potentia}
	<Msg>		"Check Potentia Slot 0"
	<Send>		"rd potentia 0 nvreg 00 100"
	<Wait>
	<GetData>	Potentia_0_IMC
	<Send>		"rd potentia 1 nvreg 00 100"
	<Wait>
	<GetData>	Potentia_1_IMC
</Bypass>
<Bypass>	$UUT_Variable_ref[1]->{PSOC}
		<Msg>		"Check PSOC Slot 0 Version"
		<Send>		"rd potentia 0 cs 60 10"
		<Wait>
		<Checkdata> $UUT_Variable_ref[1]->{PSOC_VER}
		<GetData>
		<Send>		"rd potentia 0 cs 00 100"
		<Wait>
		<GetData>
		<Send>		"rd potentia 1 cs 00 100"
		<Wait>
		<GetData>
		#Reset Static Counters
		<Send>		"wr potentia 0 csrs 1 5a"
		<Wait>
		<Send>		"rd potentia 0 cs 00 10"
		<Wait>
		<GetData>
</Bypass>

<Bypass>	$Slot_INST_1_IMC_GBL
	<Bypass>	$UUT_Variable_ref[2]->{Potentia}
		<Msg>		"Check Potentia Slot 1 IMC"
		<Send>		"on 1 rd potentia 0 nvreg 00 100"
		<Wait>
		<GetData>	Potentia_0_IMC
		<Send>		"on 1 rd potentia 1 nvreg 00 100"
		<Wait>
		<GetData>	Potentia_1_IMC
	</Bypass>
</Bypass>
<Bypass>	$Slot_INST_1_IMC_GBL
	<Bypass>	$UUT_Variable_ref[2]->{PSOC}
		<Msg>		"Check PSOC IMC Slot 1 Version"
		<Send>		"on 1 rd potentia 0 cs 60 10"
		<Wait>
		<Checkdata> $UUT_Variable_ref[2]->{PSOC_VER}
		<GetData>
		<Send>		"on 1 rd potentia 0 cs 00 100"
		<Wait>
		<GetData>
		<Send>		"on 1 rd potentia 1 cs 00 100"
		<Wait>
		<GetData>
		#Reset Static Counters
		<Send>		"on 1 wr potentia 0 csrs 1 5a"
		<Wait>
		<Send>		"on 1 rd potentia 0 cs 00 10"
		<Wait>
		<GetData>

 	</Bypass>
</Bypass>

<Prompt>	"#"
<Timeout>	15
<Send>		"exit"
<sleep>		1
<send>      "exit"
<Wait>

#<Msg>		"****** PSOC check to XGLC slots bypassed *********"
<Bypass>    $Slot_INST_1_GLC_GBL
        <Msg>       "Check Power Slot 1"
        <Send>      "on -p 7f -f /net/nv-1-0 xglcdiag cpldacc wr 1d 1 | grep -i data"
        <Wait>
        <GetData>
        <Send>      "on -p 7f -f /net/nv-1-0 i2c_util -w bus=0,dev=0x70,len=1,data=4,off=0x0"
        <Wait>
        <Sendslow>      "on -p 7f -f /net/nv-1-0 i2c_util -r bus=0,dev=0x7c,rsize=1,len=100,data=0,off=0x0"
        <Wait>
        <GetData>
        <Msg>       "Get PSOC Power Retry Count..."
		 #Retry_Count	1	R	0xF0	Number of Retries (re-sequenced) from Power on
		 # i2c md 7c F0 1"
		<CheckData>	"Data.240. = 0x0"
        <Sendslow>      "on -p 7f -f /net/nv-1-0 i2c_util -r bus=0,dev=0x7e,rsize=1,len=100,data=0,off=0x0"
        <Wait>
		<Msg>       "Check PSOC Voltage Fault Count..."
		<GetData>
		<CheckData>	"Data.32. = 0x0"
		<CheckData>	"Data.33. = 0x0"
		<CheckData>	"Data.34. = 0x0"
		<CheckData>	"Data.35. = 0x0"
		<CheckData>	"Data.36. = 0x0"
		<CheckData>	"Data.37. = 0x0"
		<CheckData>	"Data.38. = 0x0"
		<CheckData>	"Data.39. = 0x0"
		<CheckData>	"Data.40. = 0x0"
		<CheckData>	"Data.41. = 0x0"
		<CheckData>	"Data.42. = 0x0"
		<CheckData>	"Data.43. = 0x0"
		<CheckData>	"Data.44. = 0x0"
		<CheckData>	"Data.45. = 0x0"
		<CheckData>	"Data.46. = 0x0"
		<CheckData>	"Data.47. = 0x0"
		<CheckData>	"Data.48. = 0x0"
		<CheckData>	"Data.49. = 0x0"
		<CheckData>	"Data.50. = 0x0"
		<CheckData>	"Data.51. = 0x0"
		<CheckData>	"Data.52. = 0x0"
		<CheckData>	"Data.53. = 0x0"
		<CheckData>	"Data.54. = 0x0"
		<CheckData>	"Data.55. = 0x0"
		<CheckData>	"Data.56. = 0x0"
		<CheckData>	"Data.57. = 0x0"
		<CheckData>	"Data.58. = 0x0"
		<CheckData>	"Data.59. = 0x0"
		<CheckData>	"Data.60. = 0x0"
		<CheckData>	"Data.61. = 0x0"
		<CheckData>	"Data.62. = 0x0"
		<Msg>       "Get PSOC Debug Fault Count..."
		<CheckData>	"Data.64. = 0x0"
		<CheckData>	"Data.65. = 0x0"
		<CheckData>	"Data.66. = 0x0"
		<CheckData>	"Data.67. = 0x0"
		<CheckData>	"Data.68. = 0x0"
		<CheckData>	"Data.69. = 0x0"
		<CheckData>	"Data.70. = 0x0"
		<CheckData>	"Data.71. = 0x0"
		<CheckData>	"Data.72. = 0x0"
		<CheckData>	"Data.73. = 0x0"
		<CheckData>	"Data.74. = 0x0"
		<CheckData>	"Data.75. = 0x0"
		<CheckData>	"Data.76. = 0x0"
		<CheckData>	"Data.77. = 0x0"
		<CheckData>	"Data.78. = 0x0"
		<CheckData>	"Data.79. = 0x0"
		<CheckData>	"Data.80. = 0x0"
		<CheckData>	"Data.81. = 0x0"
		<CheckData>	"Data.82. = 0x0"
		<CheckData>	"Data.83. = 0x0"
		<CheckData>	"Data.84. = 0x0"
		<CheckData>	"Data.85. = 0x0"
		<CheckData>	"Data.86. = 0x0"
		<CheckData>	"Data.87. = 0x0"
		<CheckData>	"Data.88. = 0x0"
		<CheckData>	"Data.89. = 0x0"
		<CheckData>	"Data.90. = 0x0"
		<CheckData>	"Data.91. = 0x0"
		<CheckData>	"Data.92. = 0x0"
		<CheckData>	"Data.93. = 0x0"
		<CheckData>	"Data.94. = 0x0"
		<CheckData>	"Data.95. = 0x0"
		<Msg>       "Get PSOC Debug Max Fault Count..."
	#Debug_Max_Flt_Cnt	32	R/EEPROM	0x60-0x7F	Max Fault Counter for each Monitored Voltage
	#and the two VRM power good signals (causes retry)
		<CheckData>	"Data.96. = 0x0"
		<CheckData>	"Data.97. = 0x0"
		<CheckData>	"Data.98. = 0x0"
		<CheckData>	"Data.99. = 0x0"
		<CheckData>	"Data.100. = 0x0"
		<CheckData>	"Data.101. = 0x0"
		<CheckData>	"Data.102. = 0x0"
		<CheckData>	"Data.103. = 0x0"
		<CheckData>	"Data.104. = 0x0"
		<CheckData>	"Data.105. = 0x0"
		<CheckData>	"Data.106. = 0x0"
		<CheckData>	"Data.107. = 0x0"
		<CheckData>	"Data.108. = 0x0"
		<CheckData>	"Data.109. = 0x0"
		<CheckData>	"Data.110. = 0x0"
		<CheckData>	"Data.111. = 0x0"
		<CheckData>	"Data.112. = 0x0"
		<CheckData>	"Data.113. = 0x0"
		<CheckData>	"Data.114. = 0x0"
		<CheckData>	"Data.115. = 0x0"
		<CheckData>	"Data.116. = 0x0"
		<CheckData>	"Data.117. = 0x0"
		<CheckData>	"Data.118. = 0x0"
		<CheckData>	"Data.119. = 0x0"
		<CheckData>	"Data.120. = 0x0"
		<CheckData>	"Data.121. = 0x0"
		<CheckData>	"Data.122. = 0x0"
		<CheckData>	"Data.123. = 0x0"
		<CheckData>	"Data.124. = 0x0"
		<CheckData>	"Data.125. = 0x0"
		<CheckData>	"Data.126. = 0x0"
		<CheckData>	"Data.127. = 0x0"
		<Msg>       "Get PSOC Debug PON Fault Count..."
		#Debug_PON_Fail_Cnt	32	R/EEPROM	0x80-0x9F	Initial voltage low Counter for each Sequenced Group (causes retry)
		<CheckData>	"Data.128. = 0x0"
		<CheckData>	"Data.129. = 0x0"
		<CheckData>	"Data.130. = 0x0"
		<CheckData>	"Data.131. = 0x0"
		<CheckData>	"Data.132. = 0x0"
		<CheckData>	"Data.133. = 0x0"
		<CheckData>	"Data.134. = 0x0"
		<CheckData>	"Data.135. = 0x0"
		<CheckData>	"Data.136. = 0x0"
		<CheckData>	"Data.137. = 0x0"
		<CheckData>	"Data.138. = 0x0"
		<CheckData>	"Data.139. = 0x0"
		<CheckData>	"Data.140. = 0x0"
		<CheckData>	"Data.141. = 0x0"
		<CheckData>	"Data.142. = 0x0"
		<CheckData>	"Data.143. = 0x0"
		<CheckData>	"Data.144. = 0x0"
		<CheckData>	"Data.145. = 0x0"
		<CheckData>	"Data.146. = 0x0"
		<CheckData>	"Data.147. = 0x0"
		<CheckData>	"Data.148. = 0x0"
		<CheckData>	"Data.149. = 0x0"
		<CheckData>	"Data.150. = 0x0"
		<CheckData>	"Data.151. = 0x0"
		<CheckData>	"Data.152. = 0x0"
		<CheckData>	"Data.153. = 0x0"
		<CheckData>	"Data.154. = 0x0"
		<CheckData>	"Data.155. = 0x0"
		<CheckData>	"Data.156. = 0x0"
		<CheckData>	"Data.157. = 0x0"
		<CheckData>	"Data.158. = 0x0"
		<CheckData>	"Data.159. = 0x0"
		#Debug_Lost_Volt_Cnt	32	R/EEPROM	0xA0-0xBF	 Initial voltage met minimum high but
		#then went out of range  before PON sequencing completed
		<CheckData>	"Data.160. = 0x0"
		<CheckData>	"Data.161. = 0x0"
		<CheckData>	"Data.162. = 0x0"
		<CheckData>	"Data.163. = 0x0"
		<CheckData>	"Data.164. = 0x0"
		<CheckData>	"Data.165. = 0x0"
		<CheckData>	"Data.166. = 0x0"
		<CheckData>	"Data.167. = 0x0"
		<CheckData>	"Data.168. = 0x0"
		<CheckData>	"Data.169. = 0x0"
		<CheckData>	"Data.170. = 0x0"
		<CheckData>	"Data.171. = 0x0"
		<CheckData>	"Data.172. = 0x0"
		<CheckData>	"Data.173. = 0x0"
		<CheckData>	"Data.174. = 0x0"
		<CheckData>	"Data.175. = 0x0"
		<CheckData>	"Data.176. = 0x0"
		<CheckData>	"Data.177. = 0x0"
		<CheckData>	"Data.178. = 0x0"
		<CheckData>	"Data.179. = 0x0"
		<CheckData>	"Data.180. = 0x0"
		<CheckData>	"Data.181. = 0x0"
		<CheckData>	"Data.182. = 0x0"
		<CheckData>	"Data.183. = 0x0"
		<CheckData>	"Data.184. = 0x0"
		<CheckData>	"Data.185. = 0x0"
		<CheckData>	"Data.186. = 0x0"
		<CheckData>	"Data.187. = 0x0"
		<CheckData>	"Data.188. = 0x0"
		<CheckData>	"Data.189. = 0x0"
		<CheckData>	"Data.190. = 0x0"
		<CheckData>	"Data.191. = 0x0"
		<Msg>       "Get PSOC Retry Reason..."
		#Retry_Reason	1	R	0xF0	Retry power supply number and type of failure
		<CheckData>	"Data.240. = 0x0"
		<Msg>       "Get PSOC Unknown Retry Reason..."
		<Msg>       "Get PSOC EEPROM Error Count..."
		#EEPROM_Error_Cnt	1	R	0xF1	EEPROM write error counter
         <CheckData>	"Data.241. = 0x0"
		#Unknown_Retry_Reason_Cnt	1	R	0xF6	Debug - halt routine entered with invalid retry code counter
		<CheckData>	"Data.246. = 0x0"
		<Msg>       "Clear PSOC Error Registers..."
		#Clear EEPROM Error Registers	0x01   i2c mw add offest data
		# 		            Command  ;    Command Available
		#<Send>      "i2c mw 7c 1 1; i2c mw 7c 0 5a;"
		<Sendslow>      "on -p 7f -f /net/nv-1-0 i2c_util -w bus=0,dev=0x7c,len=1,data=1,off=0x1"
		<Wait>
		<Sendslow>      "on -p 7f -f /net/nv-1-0 i2c_util -w bus=0,dev=0x7c,len=1,data=5a,off=0x0"
		<Wait>
		<GetData>
		<Sleep> 2
		# Check if command completed OK
		#<Send>      "i2c md 7c 00 1"
		<Send>      "on -p 7f -f /net/nv-1-0 i2c_util -r bus=0,dev=0x7c,rsize=1,len=1,data=0,off=0x0"
		<Wait>
		<GetData>
		#<CheckData>	"Data.0. = 0x0"
		<Msg>       "Clear PSOC Retry Registers..."
		#Clear Retry Register	0x02   i2c mw add offest data
		# 		            Command  ;    Command Available
		#<Send>      "i2c mw 7c 1 2; i2c mw 7c 0 5a;"
		<Sendslow>      "on -p 7f -f /net/nv-1-0 i2c_util -w bus=0,dev=0x7c,len=1,data=2,off=0x1"
		<Wait>
		<Sendslow>      "on -p 7f -f /net/nv-1-0 i2c_util -w bus=0,dev=0x7c,len=1,data=5a,off=0x0"
		<Wait>
		<GetData>
		<Sleep> 2
		# Check if command completed OK
		<Sleep> 2
		#<Send>      "i2c md 7c 00 1"
		<Sendslow>      "on -p 7f -f /net/nv-1-0 i2c_util -r bus=0,dev=0x7c,rsize=1,len=1,data=0,off=0x0"
		<Wait>
		<GetData>
		#<CheckData>	"Data.0. = 0x0"

</Bypass>

<Bypass>    $Slot_INST_2_GBL
        <Msg>       "Check Power Slot 2"
        <Send>      "on -p 7f -f /net/nv-2-0 xglcdiag cpldacc wr 1d 1 | grep -i data"
        <Wait>
        <GetData>
        <Send>      "on -p 7f -f /net/nv-2-0 i2c_util -w bus=0,dev=0x70,len=1,data=4,off=0x0"
        <Wait>
        <Sendslow>      "on -p 7f -f /net/nv-2-0 i2c_util -r bus=0,dev=0x7c,rsize=1,len=100,data=0,off=0x0"
        <Wait>
        <GetData>
        <Msg>       "Get PSOC Power Retry Count..."
		 #Retry_Count	1	R	0xF0	Number of Retries (re-sequenced) from Power on
		 # i2c md 7c F0 1"
		<CheckData>	"Data.240. = 0x0"
        <Sendslow>      "on -p 7f -f /net/nv-2-0 i2c_util -r bus=0,dev=0x7e,rsize=1,len=100,data=0,off=0x0"
        <Wait>
		<Msg>       "Check PSOC Voltage Fault Count..."
		<GetData>
		<CheckData>	"Data.32. = 0x0"
		<CheckData>	"Data.33. = 0x0"
		<CheckData>	"Data.34. = 0x0"
		<CheckData>	"Data.35. = 0x0"
		<CheckData>	"Data.36. = 0x0"
		<CheckData>	"Data.37. = 0x0"
		<CheckData>	"Data.38. = 0x0"
		<CheckData>	"Data.39. = 0x0"
		<CheckData>	"Data.40. = 0x0"
		<CheckData>	"Data.41. = 0x0"
		<CheckData>	"Data.42. = 0x0"
		<CheckData>	"Data.43. = 0x0"
		<CheckData>	"Data.44. = 0x0"
		<CheckData>	"Data.45. = 0x0"
		<CheckData>	"Data.46. = 0x0"
		<CheckData>	"Data.47. = 0x0"
		<CheckData>	"Data.48. = 0x0"
		<CheckData>	"Data.49. = 0x0"
		<CheckData>	"Data.50. = 0x0"
		<CheckData>	"Data.51. = 0x0"
		<CheckData>	"Data.52. = 0x0"
		<CheckData>	"Data.53. = 0x0"
		<CheckData>	"Data.54. = 0x0"
		<CheckData>	"Data.55. = 0x0"
		<CheckData>	"Data.56. = 0x0"
		<CheckData>	"Data.57. = 0x0"
		<CheckData>	"Data.58. = 0x0"
		<CheckData>	"Data.59. = 0x0"
		<CheckData>	"Data.60. = 0x0"
		<CheckData>	"Data.61. = 0x0"
		<CheckData>	"Data.62. = 0x0"
		<Msg>       "Get PSOC Debug Fault Count..."
		<CheckData>	"Data.64. = 0x0"
		<CheckData>	"Data.65. = 0x0"
		<CheckData>	"Data.66. = 0x0"
		<CheckData>	"Data.67. = 0x0"
		<CheckData>	"Data.68. = 0x0"
		<CheckData>	"Data.69. = 0x0"
		<CheckData>	"Data.70. = 0x0"
		<CheckData>	"Data.71. = 0x0"
		<CheckData>	"Data.72. = 0x0"
		<CheckData>	"Data.73. = 0x0"
		<CheckData>	"Data.74. = 0x0"
		<CheckData>	"Data.75. = 0x0"
		<CheckData>	"Data.76. = 0x0"
		<CheckData>	"Data.77. = 0x0"
		<CheckData>	"Data.78. = 0x0"
		<CheckData>	"Data.79. = 0x0"
		<CheckData>	"Data.80. = 0x0"
		<CheckData>	"Data.81. = 0x0"
		<CheckData>	"Data.82. = 0x0"
		<CheckData>	"Data.83. = 0x0"
		<CheckData>	"Data.84. = 0x0"
		<CheckData>	"Data.85. = 0x0"
		<CheckData>	"Data.86. = 0x0"
		<CheckData>	"Data.87. = 0x0"
		<CheckData>	"Data.88. = 0x0"
		<CheckData>	"Data.89. = 0x0"
		<CheckData>	"Data.90. = 0x0"
		<CheckData>	"Data.91. = 0x0"
		<CheckData>	"Data.92. = 0x0"
		<CheckData>	"Data.93. = 0x0"
		<CheckData>	"Data.94. = 0x0"
		<CheckData>	"Data.95. = 0x0"
		<Msg>       "Get PSOC Debug Max Fault Count..."
	#Debug_Max_Flt_Cnt	32	R/EEPROM	0x60-0x7F	Max Fault Counter for each Monitored Voltage
	#and the two VRM power good signals (causes retry)
		<CheckData>	"Data.96. = 0x0"
		<CheckData>	"Data.97. = 0x0"
		<CheckData>	"Data.98. = 0x0"
		<CheckData>	"Data.99. = 0x0"
		<CheckData>	"Data.100. = 0x0"
		<CheckData>	"Data.101. = 0x0"
		<CheckData>	"Data.102. = 0x0"
		<CheckData>	"Data.103. = 0x0"
		<CheckData>	"Data.104. = 0x0"
		<CheckData>	"Data.105. = 0x0"
		<CheckData>	"Data.106. = 0x0"
		<CheckData>	"Data.107. = 0x0"
		<CheckData>	"Data.108. = 0x0"
		<CheckData>	"Data.109. = 0x0"
		<CheckData>	"Data.110. = 0x0"
		<CheckData>	"Data.111. = 0x0"
		<CheckData>	"Data.112. = 0x0"
		<CheckData>	"Data.113. = 0x0"
		<CheckData>	"Data.114. = 0x0"
		<CheckData>	"Data.115. = 0x0"
		<CheckData>	"Data.116. = 0x0"
		<CheckData>	"Data.117. = 0x0"
		<CheckData>	"Data.118. = 0x0"
		<CheckData>	"Data.119. = 0x0"
		<CheckData>	"Data.120. = 0x0"
		<CheckData>	"Data.121. = 0x0"
		<CheckData>	"Data.122. = 0x0"
		<CheckData>	"Data.123. = 0x0"
		<CheckData>	"Data.124. = 0x0"
		<CheckData>	"Data.125. = 0x0"
		<CheckData>	"Data.126. = 0x0"
		<CheckData>	"Data.127. = 0x0"
		<Msg>       "Get PSOC Debug PON Fault Count..."
		#Debug_PON_Fail_Cnt	32	R/EEPROM	0x80-0x9F	Initial voltage low Counter for each Sequenced Group (causes retry)
		<CheckData>	"Data.128. = 0x0"
		<CheckData>	"Data.129. = 0x0"
		<CheckData>	"Data.130. = 0x0"
		<CheckData>	"Data.131. = 0x0"
		<CheckData>	"Data.132. = 0x0"
		<CheckData>	"Data.133. = 0x0"
		<CheckData>	"Data.134. = 0x0"
		<CheckData>	"Data.135. = 0x0"
		<CheckData>	"Data.136. = 0x0"
		<CheckData>	"Data.137. = 0x0"
		<CheckData>	"Data.138. = 0x0"
		<CheckData>	"Data.139. = 0x0"
		<CheckData>	"Data.140. = 0x0"
		<CheckData>	"Data.141. = 0x0"
		<CheckData>	"Data.142. = 0x0"
		<CheckData>	"Data.143. = 0x0"
		<CheckData>	"Data.144. = 0x0"
		<CheckData>	"Data.145. = 0x0"
		<CheckData>	"Data.146. = 0x0"
		<CheckData>	"Data.147. = 0x0"
		<CheckData>	"Data.148. = 0x0"
		<CheckData>	"Data.149. = 0x0"
		<CheckData>	"Data.150. = 0x0"
		<CheckData>	"Data.151. = 0x0"
		<CheckData>	"Data.152. = 0x0"
		<CheckData>	"Data.153. = 0x0"
		<CheckData>	"Data.154. = 0x0"
		<CheckData>	"Data.155. = 0x0"
		<CheckData>	"Data.156. = 0x0"
		<CheckData>	"Data.157. = 0x0"
		<CheckData>	"Data.158. = 0x0"
		<CheckData>	"Data.159. = 0x0"
		#Debug_Lost_Volt_Cnt	32	R/EEPROM	0xA0-0xBF	 Initial voltage met minimum high but
		#then went out of range  before PON sequencing completed
		<CheckData>	"Data.160. = 0x0"
		<CheckData>	"Data.161. = 0x0"
		<CheckData>	"Data.162. = 0x0"
		<CheckData>	"Data.163. = 0x0"
		<CheckData>	"Data.164. = 0x0"
		<CheckData>	"Data.165. = 0x0"
		<CheckData>	"Data.166. = 0x0"
		<CheckData>	"Data.167. = 0x0"
		<CheckData>	"Data.168. = 0x0"
		<CheckData>	"Data.169. = 0x0"
		<CheckData>	"Data.170. = 0x0"
		<CheckData>	"Data.171. = 0x0"
		<CheckData>	"Data.172. = 0x0"
		<CheckData>	"Data.173. = 0x0"
		<CheckData>	"Data.174. = 0x0"
		<CheckData>	"Data.175. = 0x0"
		<CheckData>	"Data.176. = 0x0"
		<CheckData>	"Data.177. = 0x0"
		<CheckData>	"Data.178. = 0x0"
		<CheckData>	"Data.179. = 0x0"
		<CheckData>	"Data.180. = 0x0"
		<CheckData>	"Data.181. = 0x0"
		<CheckData>	"Data.182. = 0x0"
		<CheckData>	"Data.183. = 0x0"
		<CheckData>	"Data.184. = 0x0"
		<CheckData>	"Data.185. = 0x0"
		<CheckData>	"Data.186. = 0x0"
		<CheckData>	"Data.187. = 0x0"
		<CheckData>	"Data.188. = 0x0"
		<CheckData>	"Data.189. = 0x0"
		<CheckData>	"Data.190. = 0x0"
		<CheckData>	"Data.191. = 0x0"
		<Msg>       "Get PSOC Retry Reason..."
		#Retry_Reason	1	R	0xF0	Retry power supply number and type of failure
		<CheckData>	"Data.240. = 0x0"
		<Msg>       "Get PSOC Unknown Retry Reason..."
		<Msg>       "Get PSOC EEPROM Error Count..."
		#EEPROM_Error_Cnt	1	R	0xF1	EEPROM write error counter
         <CheckData>	"Data.241. = 0x0"
		#Unknown_Retry_Reason_Cnt	1	R	0xF6	Debug - halt routine entered with invalid retry code counter
		<CheckData>	"Data.246. = 0x0"
		<Msg>       "Clear PSOC Error Registers..."
		#Clear EEPROM Error Registers	0x01   i2c mw add offest data
		# 		            Command  ;    Command Available
		#<Send>      "i2c mw 7c 1 1; i2c mw 7c 0 5a;"
		<Sendslow>      "on -p 7f -f /net/nv-2-0 i2c_util -w bus=0,dev=0x7c,len=1,data=1,off=0x1"
		<Wait>
		<Sendslow>      "on -p 7f -f /net/nv-2-0 i2c_util -w bus=0,dev=0x7c,len=1,data=5a,off=0x0"
		<Wait>
		<GetData>
		<Sleep> 2
		# Check if command completed OK
		#<Send>      "i2c md 7c 00 1"
		<Send>      "on -p 7f -f /net/nv-2-0 i2c_util -r bus=0,dev=0x7c,rsize=1,len=1,data=0,off=0x0"
		<Wait>
		<GetData>
		#<CheckData>	"Data.0. = 0x0"
		<Msg>       "Clear PSOC Retry Registers..."
		#Clear Retry Register	0x02   i2c mw add offest data
		# 		            Command  ;    Command Available
		#<Send>      "i2c mw 7c 1 2; i2c mw 7c 0 5a;"
		<Sendslow>      "on -p 7f -f /net/nv-2-0 i2c_util -w bus=0,dev=0x7c,len=1,data=2,off=0x1"
		<Wait>
		<Sendslow>      "on -p 7f -f /net/nv-2-0 i2c_util -w bus=0,dev=0x7c,len=1,data=5a,off=0x0"
		<Wait>
		<GetData>
		<Sleep> 2
		# Check if command completed OK
		<Sleep> 2
		#<Send>      "i2c md 7c 00 1"
		<Sendslow>      "on -p 7f -f /net/nv-2-0 i2c_util -r bus=0,dev=0x7c,rsize=1,len=1,data=0,off=0x0"
		<Wait>
		<GetData>
		#<CheckData>	"Data.0. = 0x0"

</Bypass>
<Bypass>    $Slot_INST_3_GBL
        <Msg>       "Check Power Slot 3"
        <Send>      "on -p 7f -f /net/nv-3-0 xglcdiag cpldacc wr 1d 1 | grep -i data"
        <Wait>
        <GetData>
        <Send>      "on -p 7f -f /net/nv-3-0 i2c_util -w bus=0,dev=0x70,len=1,data=4,off=0x0"
        <Wait>
        <Sendslow>      "on -p 7f -f /net/nv-3-0 i2c_util -r bus=0,dev=0x7c,rsize=1,len=100,data=0,off=0x0"
        <Wait>
        <GetData>
        <Msg>       "Get PSOC Power Retry Count..."
		 #Retry_Count	1	R	0xF0	Number of Retries (re-sequenced) from Power on
		 # i2c md 7c F0 1"
		<CheckData>	"Data.240. = 0x0"
        <Sendslow>      "on -p 7f -f /net/nv-3-0 i2c_util -r bus=0,dev=0x7e,rsize=1,len=100,data=0,off=0x0"
        <Wait>
		<Msg>       "Check PSOC Voltage Fault Count..."
		<GetData>
		<CheckData>	"Data.32. = 0x0"
		<CheckData>	"Data.33. = 0x0"
		<CheckData>	"Data.34. = 0x0"
		<CheckData>	"Data.35. = 0x0"
		<CheckData>	"Data.36. = 0x0"
		<CheckData>	"Data.37. = 0x0"
		<CheckData>	"Data.38. = 0x0"
		<CheckData>	"Data.39. = 0x0"
		<CheckData>	"Data.40. = 0x0"
		<CheckData>	"Data.41. = 0x0"
		<CheckData>	"Data.42. = 0x0"
		<CheckData>	"Data.43. = 0x0"
		<CheckData>	"Data.44. = 0x0"
		<CheckData>	"Data.45. = 0x0"
		<CheckData>	"Data.46. = 0x0"
		<CheckData>	"Data.47. = 0x0"
		<CheckData>	"Data.48. = 0x0"
		<CheckData>	"Data.49. = 0x0"
		<CheckData>	"Data.50. = 0x0"
		<CheckData>	"Data.51. = 0x0"
		<CheckData>	"Data.52. = 0x0"
		<CheckData>	"Data.53. = 0x0"
		<CheckData>	"Data.54. = 0x0"
		<CheckData>	"Data.55. = 0x0"
		<CheckData>	"Data.56. = 0x0"
		<CheckData>	"Data.57. = 0x0"
		<CheckData>	"Data.58. = 0x0"
		<CheckData>	"Data.59. = 0x0"
		<CheckData>	"Data.60. = 0x0"
		<CheckData>	"Data.61. = 0x0"
		<CheckData>	"Data.62. = 0x0"
		<Msg>       "Get PSOC Debug Fault Count..."
		<CheckData>	"Data.64. = 0x0"
		<CheckData>	"Data.65. = 0x0"
		<CheckData>	"Data.66. = 0x0"
		<CheckData>	"Data.67. = 0x0"
		<CheckData>	"Data.68. = 0x0"
		<CheckData>	"Data.69. = 0x0"
		<CheckData>	"Data.70. = 0x0"
		<CheckData>	"Data.71. = 0x0"
		<CheckData>	"Data.72. = 0x0"
		<CheckData>	"Data.73. = 0x0"
		<CheckData>	"Data.74. = 0x0"
		<CheckData>	"Data.75. = 0x0"
		<CheckData>	"Data.76. = 0x0"
		<CheckData>	"Data.77. = 0x0"
		<CheckData>	"Data.78. = 0x0"
		<CheckData>	"Data.79. = 0x0"
		<CheckData>	"Data.80. = 0x0"
		<CheckData>	"Data.81. = 0x0"
		<CheckData>	"Data.82. = 0x0"
		<CheckData>	"Data.83. = 0x0"
		<CheckData>	"Data.84. = 0x0"
		<CheckData>	"Data.85. = 0x0"
		<CheckData>	"Data.86. = 0x0"
		<CheckData>	"Data.87. = 0x0"
		<CheckData>	"Data.88. = 0x0"
		<CheckData>	"Data.89. = 0x0"
		<CheckData>	"Data.90. = 0x0"
		<CheckData>	"Data.91. = 0x0"
		<CheckData>	"Data.92. = 0x0"
		<CheckData>	"Data.93. = 0x0"
		<CheckData>	"Data.94. = 0x0"
		<CheckData>	"Data.95. = 0x0"
		<Msg>       "Get PSOC Debug Max Fault Count..."
	#Debug_Max_Flt_Cnt	32	R/EEPROM	0x60-0x7F	Max Fault Counter for each Monitored Voltage
	#and the two VRM power good signals (causes retry)
		<CheckData>	"Data.96. = 0x0"
		<CheckData>	"Data.97. = 0x0"
		<CheckData>	"Data.98. = 0x0"
		<CheckData>	"Data.99. = 0x0"
		<CheckData>	"Data.100. = 0x0"
		<CheckData>	"Data.101. = 0x0"
		<CheckData>	"Data.102. = 0x0"
		<CheckData>	"Data.103. = 0x0"
		<CheckData>	"Data.104. = 0x0"
		<CheckData>	"Data.105. = 0x0"
		<CheckData>	"Data.106. = 0x0"
		<CheckData>	"Data.107. = 0x0"
		<CheckData>	"Data.108. = 0x0"
		<CheckData>	"Data.109. = 0x0"
		<CheckData>	"Data.110. = 0x0"
		<CheckData>	"Data.111. = 0x0"
		<CheckData>	"Data.112. = 0x0"
		<CheckData>	"Data.113. = 0x0"
		<CheckData>	"Data.114. = 0x0"
		<CheckData>	"Data.115. = 0x0"
		<CheckData>	"Data.116. = 0x0"
		<CheckData>	"Data.117. = 0x0"
		<CheckData>	"Data.118. = 0x0"
		<CheckData>	"Data.119. = 0x0"
		<CheckData>	"Data.120. = 0x0"
		<CheckData>	"Data.121. = 0x0"
		<CheckData>	"Data.122. = 0x0"
		<CheckData>	"Data.123. = 0x0"
		<CheckData>	"Data.124. = 0x0"
		<CheckData>	"Data.125. = 0x0"
		<CheckData>	"Data.126. = 0x0"
		<CheckData>	"Data.127. = 0x0"
		<Msg>       "Get PSOC Debug PON Fault Count..."
		#Debug_PON_Fail_Cnt	32	R/EEPROM	0x80-0x9F	Initial voltage low Counter for each Sequenced Group (causes retry)
		<CheckData>	"Data.128. = 0x0"
		<CheckData>	"Data.129. = 0x0"
		<CheckData>	"Data.130. = 0x0"
		<CheckData>	"Data.131. = 0x0"
		<CheckData>	"Data.132. = 0x0"
		<CheckData>	"Data.133. = 0x0"
		<CheckData>	"Data.134. = 0x0"
		<CheckData>	"Data.135. = 0x0"
		<CheckData>	"Data.136. = 0x0"
		<CheckData>	"Data.137. = 0x0"
		<CheckData>	"Data.138. = 0x0"
		<CheckData>	"Data.139. = 0x0"
		<CheckData>	"Data.140. = 0x0"
		<CheckData>	"Data.141. = 0x0"
		<CheckData>	"Data.142. = 0x0"
		<CheckData>	"Data.143. = 0x0"
		<CheckData>	"Data.144. = 0x0"
		<CheckData>	"Data.145. = 0x0"
		<CheckData>	"Data.146. = 0x0"
		<CheckData>	"Data.147. = 0x0"
		<CheckData>	"Data.148. = 0x0"
		<CheckData>	"Data.149. = 0x0"
		<CheckData>	"Data.150. = 0x0"
		<CheckData>	"Data.151. = 0x0"
		<CheckData>	"Data.152. = 0x0"
		<CheckData>	"Data.153. = 0x0"
		<CheckData>	"Data.154. = 0x0"
		<CheckData>	"Data.155. = 0x0"
		<CheckData>	"Data.156. = 0x0"
		<CheckData>	"Data.157. = 0x0"
		<CheckData>	"Data.158. = 0x0"
		<CheckData>	"Data.159. = 0x0"
		#Debug_Lost_Volt_Cnt	32	R/EEPROM	0xA0-0xBF	 Initial voltage met minimum high but
		#then went out of range  before PON sequencing completed
		<CheckData>	"Data.160. = 0x0"
		<CheckData>	"Data.161. = 0x0"
		<CheckData>	"Data.162. = 0x0"
		<CheckData>	"Data.163. = 0x0"
		<CheckData>	"Data.164. = 0x0"
		<CheckData>	"Data.165. = 0x0"
		<CheckData>	"Data.166. = 0x0"
		<CheckData>	"Data.167. = 0x0"
		<CheckData>	"Data.168. = 0x0"
		<CheckData>	"Data.169. = 0x0"
		<CheckData>	"Data.170. = 0x0"
		<CheckData>	"Data.171. = 0x0"
		<CheckData>	"Data.172. = 0x0"
		<CheckData>	"Data.173. = 0x0"
		<CheckData>	"Data.174. = 0x0"
		<CheckData>	"Data.175. = 0x0"
		<CheckData>	"Data.176. = 0x0"
		<CheckData>	"Data.177. = 0x0"
		<CheckData>	"Data.178. = 0x0"
		<CheckData>	"Data.179. = 0x0"
		<CheckData>	"Data.180. = 0x0"
		<CheckData>	"Data.181. = 0x0"
		<CheckData>	"Data.182. = 0x0"
		<CheckData>	"Data.183. = 0x0"
		<CheckData>	"Data.184. = 0x0"
		<CheckData>	"Data.185. = 0x0"
		<CheckData>	"Data.186. = 0x0"
		<CheckData>	"Data.187. = 0x0"
		<CheckData>	"Data.188. = 0x0"
		<CheckData>	"Data.189. = 0x0"
		<CheckData>	"Data.190. = 0x0"
		<CheckData>	"Data.191. = 0x0"
		<Msg>       "Get PSOC Retry Reason..."
		#Retry_Reason	1	R	0xF0	Retry power supply number and type of failure
		<CheckData>	"Data.240. = 0x0"
		<Msg>       "Get PSOC Unknown Retry Reason..."
		<Msg>       "Get PSOC EEPROM Error Count..."
		#EEPROM_Error_Cnt	1	R	0xF1	EEPROM write error counter
         <CheckData>	"Data.241. = 0x0"
		#Unknown_Retry_Reason_Cnt	1	R	0xF6	Debug - halt routine entered with invalid retry code counter
		<CheckData>	"Data.246. = 0x0"
		<Msg>       "Clear PSOC Error Registers..."
		#Clear EEPROM Error Registers	0x01   i2c mw add offest data
		# 		            Command  ;    Command Available
		#<Send>      "i2c mw 7c 1 1; i2c mw 7c 0 5a;"
		<Sendslow>      "on -p 7f -f /net/nv-3-0 i2c_util -w bus=0,dev=0x7c,len=1,data=1,off=0x1"
		<Wait>
		<Sendslow>      "on -p 7f -f /net/nv-3-0 i2c_util -w bus=0,dev=0x7c,len=1,data=5a,off=0x0"
		<Wait>
		<GetData>
		<Sleep> 2
		# Check if command completed OK
		#<Send>      "i2c md 7c 00 1"
		<Send>      "on -p 7f -f /net/nv-3-0 i2c_util -r bus=0,dev=0x7c,rsize=1,len=1,data=0,off=0x0"
		<Wait>
		<GetData>
		#<CheckData>	"Data.0. = 0x0"
		<Msg>       "Clear PSOC Retry Registers..."
		#Clear Retry Register	0x02   i2c mw add offest data
		# 		            Command  ;    Command Available
		#<Send>      "i2c mw 7c 1 2; i2c mw 7c 0 5a;"
		<Sendslow>      "on -p 7f -f /net/nv-3-0 i2c_util -w bus=0,dev=0x7c,len=1,data=2,off=0x1"
		<Wait>
		<Sendslow>      "on -p 7f -f /net/nv-3-0 i2c_util -w bus=0,dev=0x7c,len=1,data=5a,off=0x0"
		<Wait>
		<GetData>
		<Sleep> 2
		# Check if command completed OK
		<Sleep> 2
		#<Send>      "i2c md 7c 00 1"
		<Sendslow>      "on -p 7f -f /net/nv-3-0 i2c_util -r bus=0,dev=0x7c,rsize=1,len=1,data=0,off=0x0"
		<Wait>
		<GetData>
		#<CheckData>	"Data.0. = 0x0"

</Bypass>

<Bypass>    $Slot_INST_4_GBL
        <Msg>       "Check Power Slot 4"
        <Send>      "on -p 7f -f /net/nv-4-0 xglcdiag cpldacc wr 1d 1 | grep -i data"
        <Wait>
        <GetData>
        <Send>      "on -p 7f -f /net/nv-4-0 i2c_util -w bus=0,dev=0x70,len=1,data=4,off=0x0"
        <Wait>
        <Sendslow>      "on -p 7f -f /net/nv-4-0 i2c_util -r bus=0,dev=0x7c,rsize=1,len=100,data=0,off=0x0"
        <Wait>
        <GetData>
        <Msg>       "Get PSOC Power Retry Count..."
		 #Retry_Count	1	R	0xF0	Number of Retries (re-sequenced) from Power on
		 # i2c md 7c F0 1"
		<CheckData>	"Data.240. = 0x0"
        <Sendslow>      "on -p 7f -f /net/nv-4-0 i2c_util -r bus=0,dev=0x7e,rsize=1,len=100,data=0,off=0x0"
        <Wait>
		<Msg>       "Check PSOC Voltage Fault Count..."
		<GetData>
		<CheckData>	"Data.32. = 0x0"
		<CheckData>	"Data.33. = 0x0"
		<CheckData>	"Data.34. = 0x0"
		<CheckData>	"Data.35. = 0x0"
		<CheckData>	"Data.36. = 0x0"
		<CheckData>	"Data.37. = 0x0"
		<CheckData>	"Data.38. = 0x0"
		<CheckData>	"Data.39. = 0x0"
		<CheckData>	"Data.40. = 0x0"
		<CheckData>	"Data.41. = 0x0"
		<CheckData>	"Data.42. = 0x0"
		<CheckData>	"Data.43. = 0x0"
		<CheckData>	"Data.44. = 0x0"
		<CheckData>	"Data.45. = 0x0"
		<CheckData>	"Data.46. = 0x0"
		<CheckData>	"Data.47. = 0x0"
		<CheckData>	"Data.48. = 0x0"
		<CheckData>	"Data.49. = 0x0"
		<CheckData>	"Data.50. = 0x0"
		<CheckData>	"Data.51. = 0x0"
		<CheckData>	"Data.52. = 0x0"
		<CheckData>	"Data.53. = 0x0"
		<CheckData>	"Data.54. = 0x0"
		<CheckData>	"Data.55. = 0x0"
		<CheckData>	"Data.56. = 0x0"
		<CheckData>	"Data.57. = 0x0"
		<CheckData>	"Data.58. = 0x0"
		<CheckData>	"Data.59. = 0x0"
		<CheckData>	"Data.60. = 0x0"
		<CheckData>	"Data.61. = 0x0"
		<CheckData>	"Data.62. = 0x0"
		<Msg>       "Get PSOC Debug Fault Count..."
		<CheckData>	"Data.64. = 0x0"
		<CheckData>	"Data.65. = 0x0"
		<CheckData>	"Data.66. = 0x0"
		<CheckData>	"Data.67. = 0x0"
		<CheckData>	"Data.68. = 0x0"
		<CheckData>	"Data.69. = 0x0"
		<CheckData>	"Data.70. = 0x0"
		<CheckData>	"Data.71. = 0x0"
		<CheckData>	"Data.72. = 0x0"
		<CheckData>	"Data.73. = 0x0"
		<CheckData>	"Data.74. = 0x0"
		<CheckData>	"Data.75. = 0x0"
		<CheckData>	"Data.76. = 0x0"
		<CheckData>	"Data.77. = 0x0"
		<CheckData>	"Data.78. = 0x0"
		<CheckData>	"Data.79. = 0x0"
		<CheckData>	"Data.80. = 0x0"
		<CheckData>	"Data.81. = 0x0"
		<CheckData>	"Data.82. = 0x0"
		<CheckData>	"Data.83. = 0x0"
		<CheckData>	"Data.84. = 0x0"
		<CheckData>	"Data.85. = 0x0"
		<CheckData>	"Data.86. = 0x0"
		<CheckData>	"Data.87. = 0x0"
		<CheckData>	"Data.88. = 0x0"
		<CheckData>	"Data.89. = 0x0"
		<CheckData>	"Data.90. = 0x0"
		<CheckData>	"Data.91. = 0x0"
		<CheckData>	"Data.92. = 0x0"
		<CheckData>	"Data.93. = 0x0"
		<CheckData>	"Data.94. = 0x0"
		<CheckData>	"Data.95. = 0x0"
		<Msg>       "Get PSOC Debug Max Fault Count..."
	#Debug_Max_Flt_Cnt	32	R/EEPROM	0x60-0x7F	Max Fault Counter for each Monitored Voltage
	#and the two VRM power good signals (causes retry)
		<CheckData>	"Data.96. = 0x0"
		<CheckData>	"Data.97. = 0x0"
		<CheckData>	"Data.98. = 0x0"
		<CheckData>	"Data.99. = 0x0"
		<CheckData>	"Data.100. = 0x0"
		<CheckData>	"Data.101. = 0x0"
		<CheckData>	"Data.102. = 0x0"
		<CheckData>	"Data.103. = 0x0"
		<CheckData>	"Data.104. = 0x0"
		<CheckData>	"Data.105. = 0x0"
		<CheckData>	"Data.106. = 0x0"
		<CheckData>	"Data.107. = 0x0"
		<CheckData>	"Data.108. = 0x0"
		<CheckData>	"Data.109. = 0x0"
		<CheckData>	"Data.110. = 0x0"
		<CheckData>	"Data.111. = 0x0"
		<CheckData>	"Data.112. = 0x0"
		<CheckData>	"Data.113. = 0x0"
		<CheckData>	"Data.114. = 0x0"
		<CheckData>	"Data.115. = 0x0"
		<CheckData>	"Data.116. = 0x0"
		<CheckData>	"Data.117. = 0x0"
		<CheckData>	"Data.118. = 0x0"
		<CheckData>	"Data.119. = 0x0"
		<CheckData>	"Data.120. = 0x0"
		<CheckData>	"Data.121. = 0x0"
		<CheckData>	"Data.122. = 0x0"
		<CheckData>	"Data.123. = 0x0"
		<CheckData>	"Data.124. = 0x0"
		<CheckData>	"Data.125. = 0x0"
		<CheckData>	"Data.126. = 0x0"
		<CheckData>	"Data.127. = 0x0"
		<Msg>       "Get PSOC Debug PON Fault Count..."
		#Debug_PON_Fail_Cnt	32	R/EEPROM	0x80-0x9F	Initial voltage low Counter for each Sequenced Group (causes retry)
		<CheckData>	"Data.128. = 0x0"
		<CheckData>	"Data.129. = 0x0"
		<CheckData>	"Data.130. = 0x0"
		<CheckData>	"Data.131. = 0x0"
		<CheckData>	"Data.132. = 0x0"
		<CheckData>	"Data.133. = 0x0"
		<CheckData>	"Data.134. = 0x0"
		<CheckData>	"Data.135. = 0x0"
		<CheckData>	"Data.136. = 0x0"
		<CheckData>	"Data.137. = 0x0"
		<CheckData>	"Data.138. = 0x0"
		<CheckData>	"Data.139. = 0x0"
		<CheckData>	"Data.140. = 0x0"
		<CheckData>	"Data.141. = 0x0"
		<CheckData>	"Data.142. = 0x0"
		<CheckData>	"Data.143. = 0x0"
		<CheckData>	"Data.144. = 0x0"
		<CheckData>	"Data.145. = 0x0"
		<CheckData>	"Data.146. = 0x0"
		<CheckData>	"Data.147. = 0x0"
		<CheckData>	"Data.148. = 0x0"
		<CheckData>	"Data.149. = 0x0"
		<CheckData>	"Data.150. = 0x0"
		<CheckData>	"Data.151. = 0x0"
		<CheckData>	"Data.152. = 0x0"
		<CheckData>	"Data.153. = 0x0"
		<CheckData>	"Data.154. = 0x0"
		<CheckData>	"Data.155. = 0x0"
		<CheckData>	"Data.156. = 0x0"
		<CheckData>	"Data.157. = 0x0"
		<CheckData>	"Data.158. = 0x0"
		<CheckData>	"Data.159. = 0x0"
		#Debug_Lost_Volt_Cnt	32	R/EEPROM	0xA0-0xBF	 Initial voltage met minimum high but
		#then went out of range  before PON sequencing completed
		<CheckData>	"Data.160. = 0x0"
		<CheckData>	"Data.161. = 0x0"
		<CheckData>	"Data.162. = 0x0"
		<CheckData>	"Data.163. = 0x0"
		<CheckData>	"Data.164. = 0x0"
		<CheckData>	"Data.165. = 0x0"
		<CheckData>	"Data.166. = 0x0"
		<CheckData>	"Data.167. = 0x0"
		<CheckData>	"Data.168. = 0x0"
		<CheckData>	"Data.169. = 0x0"
		<CheckData>	"Data.170. = 0x0"
		<CheckData>	"Data.171. = 0x0"
		<CheckData>	"Data.172. = 0x0"
		<CheckData>	"Data.173. = 0x0"
		<CheckData>	"Data.174. = 0x0"
		<CheckData>	"Data.175. = 0x0"
		<CheckData>	"Data.176. = 0x0"
		<CheckData>	"Data.177. = 0x0"
		<CheckData>	"Data.178. = 0x0"
		<CheckData>	"Data.179. = 0x0"
		<CheckData>	"Data.180. = 0x0"
		<CheckData>	"Data.181. = 0x0"
		<CheckData>	"Data.182. = 0x0"
		<CheckData>	"Data.183. = 0x0"
		<CheckData>	"Data.184. = 0x0"
		<CheckData>	"Data.185. = 0x0"
		<CheckData>	"Data.186. = 0x0"
		<CheckData>	"Data.187. = 0x0"
		<CheckData>	"Data.188. = 0x0"
		<CheckData>	"Data.189. = 0x0"
		<CheckData>	"Data.190. = 0x0"
		<CheckData>	"Data.191. = 0x0"
		<Msg>       "Get PSOC Retry Reason..."
		#Retry_Reason	1	R	0xF0	Retry power supply number and type of failure
		<CheckData>	"Data.240. = 0x0"
		<Msg>       "Get PSOC Unknown Retry Reason..."
		<Msg>       "Get PSOC EEPROM Error Count..."
		#EEPROM_Error_Cnt	1	R	0xF1	EEPROM write error counter
         <CheckData>	"Data.241. = 0x0"
		#Unknown_Retry_Reason_Cnt	1	R	0xF6	Debug - halt routine entered with invalid retry code counter
		<CheckData>	"Data.246. = 0x0"
		<Msg>       "Clear PSOC Error Registers..."
		#Clear EEPROM Error Registers	0x01   i2c mw add offest data
		# 		            Command  ;    Command Available
		#<Send>      "i2c mw 7c 1 1; i2c mw 7c 0 5a;"
		<Sendslow>      "on -p 7f -f /net/nv-4-0 i2c_util -w bus=0,dev=0x7c,len=1,data=1,off=0x1"
		<Wait>
		<Sendslow>      "on -p 7f -f /net/nv-4-0 i2c_util -w bus=0,dev=0x7c,len=1,data=5a,off=0x0"
		<Wait>
		<GetData>
		<Sleep> 2
		# Check if command completed OK
		#<Send>      "i2c md 7c 00 1"
		<Send>      "on -p 7f -f /net/nv-4-0 i2c_util -r bus=0,dev=0x7c,rsize=1,len=1,data=0,off=0x0"
		<Wait>
		<GetData>
		#<CheckData>	"Data.0. = 0x0"
		<Msg>       "Clear PSOC Retry Registers..."
		#Clear Retry Register	0x02   i2c mw add offest data
		# 		            Command  ;    Command Available
		#<Send>      "i2c mw 7c 1 2; i2c mw 7c 0 5a;"
		<Sendslow>      "on -p 7f -f /net/nv-4-0 i2c_util -w bus=0,dev=0x7c,len=1,data=2,off=0x1"
		<Wait>
		<Sendslow>      "on -p 7f -f /net/nv-4-0 i2c_util -w bus=0,dev=0x7c,len=1,data=5a,off=0x0"
		<Wait>
		<GetData>
		<Sleep> 2
		# Check if command completed OK
		<Sleep> 2
		#<Send>      "i2c md 7c 00 1"
		<Sendslow>      "on -p 7f -f /net/nv-4-0 i2c_util -r bus=0,dev=0x7c,rsize=1,len=1,data=0,off=0x0"
		<Wait>
		<GetData>
		#<CheckData>	"Data.0. = 0x0"

</Bypass>


<Prompt>	"#"
<Timeout>	15
<Send>		"exit"
<sleep>		1
<send>      "exit"
<Wait>
<GetData>
<sleep>		1
<msg>			"Waiting."
<sendslow>      "echo waiting........................................................"
<Wait>
<getdata>

