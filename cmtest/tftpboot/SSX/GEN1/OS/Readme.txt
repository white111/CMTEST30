9:39 AM 9/26/2011

9:43 AM 11/10/2011				Built Name -> cmtest name -> SSX name(if needed)
\\harp\Build\builder\6.0\2011110901\\qnx\cb\mc\boot.nonfs.bin ->-> stoke.bin
\\harp\Build\builder\6.0\2011110901\\qnx\cb\mc\StokeOS-6.0 -> stokepkg.bin -> StokeOS-6.0
\\harp\Build\builder\6.0\2011110901\qnx\cb\lc\boot.bin -> boot_glc.bin
\\harp\Build\builder\6.0\2011110901\xlp\xlp.rootfs.gz -> xlp.rootfs.gz.bin -> xlp.rootfs.gz

\\harp\Build\builder\6.0\2011110901\\qnx\cb\mc\booloader -> bootloader.bin
\\harp\Build\builder\6.0\2011110901\\qnx\cb\mc\bootloader2 -> bootloader2.bin

\\harp\Build\builder\xglc-programmables\latest\rcw_xglc_pcie_100mz_xlprc_04.bin -> rcw_xglc.bin
\\harp\Build\builder\xglc-programmables\latest\stoke_xglc_20110812.img -> stoke_xglc.img
\\harp\Build\builder\xglc-programmables\latest\xlp-r2-boot-spi-20110831.bin -> xlp-r2-boot-spi.bin
\\harp\Build\builder\xglc-programmables\latest\fsl_fman_ucode_P4080_101_6.bin -> fman.bin
\\harp\Build\builder\noodle\noodle.bin.2009082613 -> noodle.bin  (not verified, using original in mfg directories)

#Entire Flash
\\harp\Build\builder\xglc-programmables\p4080\agile\rcw_diag_bloader_fman_uboot_ver5.bin => flashimg.bin


Stoke> setenv ipaddr 172.17.24.12
Stoke> ping 172.17.24.10
Using FM2@DTSEC4 device
host 172.17.24.10 is alive
Stoke> print env
## Error: "env" not defined
Stoke> printenv
baudrate=115200
bootcmd=cp.b ed000000 40000000 800000; bootifs 40000000
consoledev=ttyS0
diag=cp.b e9000000 40000000 1300000;bootifs 40000000
eth1addr=00:12:73:00:0a:01
eth2addr=00:12:73:00:0a:02
eth3addr=00:12:73:00:0a:03
ethact=FM2@DTSEC4
ethaddr=00:12:73:00:0a:00
ethprime=FM2@DTSEC4
gatewayip=172.17.16.1
hwconfig=fsl_ddr:none
ipaddr=172.17.24.12
loadaddr=1000000
netmask=255.255.252.0
nputemp=mw.b ffdf001d 1;i2c dev 0;i2c mw 70 0 1;i2c md 4c 0 1;i2c md 4c 1 1;i2c md 4d 0 1;i2c md 4d 1 1
psocclr=mw.b ffdf001d 1;i2c dev 0;i2c mw 70 0 4;i2c mw 7c 1 1;i2c mw 7c 0 5a
psocdump=mw.b ffdf001d 1;i2c dev 0;i2c mw 70 0 4;echo Address 7c;i2c md 7c 0 100;echo Address 7e;i2c md 7e 0 100
serverip=172.17.3.20
sfpon=i2c bus 3;i2c mw 74 2 0;i2c mw 74 3 0
stderr=serial
stdin=serial
stdout=serial
uboot=u-boot.bin
updateuboot=protect off eff80000 efffffff;erase eff80000 efffffff;cp.b 40000000 eff80000 $filesize

Environment size: 957/8188 bytes
Stoke> tftp 40000000 builder/xglc-programmables/latest/rcw_xglc_pcie_100mz_xlprc_4uart_05.bin
Using FM2@DTSEC4 device
TFTP from server 172.17.3.20; our IP address is 172.17.24.12; sending through gateway 172.17.16.1
Filename 'builder/xglc-programmables/latest/rcw_xglc_pcie_100mz_xlprc_4uart_05.bin'.
Load address: 0x40000000
Loading: #
done
Bytes transferred = 80 (50 hex)
Stoke> crc32 40000000 50
CRC32 for 40000000 ... 4000004f ==> 437572c9
Stoke> crc32 e8000000 50
CRC32 for e8000000 ... e800004f ==> 437572c9
Stoke> <INTERRUPT>
Stoke> setenv serverip 172.17.24.10
Stoke> tftp 1000000 OS_B/rcw_xglc.bin
Using FM2@DTSEC4 device
TFTP from server 172.17.24.10; our IP address is 172.17.24.12
Filename 'OS_B/rcw_xglc.bin'.
Load address: 0x1000000
Loading: #
done
Bytes transferred = 80 (50 hex)
Stoke> crc32 1000000 50
CRC32 for 01000000 ... 0100004f ==> 437572c9
Stoke> setenv serverip=172.17.3.20
## Error: illegal character '=' in variable name "serverip=172.17.3.20"
Stoke> setenv serverip 172.17.3.20
Stoke> tftp 40000000 builder/xglc-programmables/latest/fsl_fman_ucode_P4080_101_6.bin
Using FM2@DTSEC4 device
TFTP from server 172.17.3.20; our IP address is 172.17.24.12; sending through gateway 172.17.16.1
Filename 'builder/xglc-programmables/latest/fsl_fman_ucode_P4080_101_6.bin'.
Load address: 0x40000000
Loading: #
done
Bytes transferred = 7260 (1c5c hex)
Stoke> crc32 40000000 1c5c
CRC32 for 40000000 ... 40001c5b ==> 6e7f9197
Stoke> crc32 eF000000 1c5c
CRC32 for ef000000 ... ef001c5b ==> 6e7f9197
Stoke> md.b ffdf0043 1
ffdf0043: 01    .
Stoke> mw.b ffdf0043 0
Stoke> crc32 eF000000 1c5c
CRC32 for ef000000 ... ef001c5b ==> 6e7f9197
Stoke> setenv serverip 172.17.24.10
Stoke> tftp 1000000 OS_B/ucode.bin
Using FM2@DTSEC4 device
TFTP from server 172.17.24.10; our IP address is 172.17.24.12
Filename 'OS_B/ucode.bin'.
Load address: 0x1000000
Loading: #
done
Bytes transferred = 7260 (1c5c hex)
Stoke> crc32 1000000 1c5c
CRC32 for 01000000 ... 01001c5b ==> 6e7f9197
Stoke> tftp 1000000 OS_B/stokebootxglc.bin
Using FM2@DTSEC4 device
TFTP from server 172.17.24.10; our IP address is 172.17.24.12
Filename 'OS_B/stokebootxglc.bin'.
Load address: 0x1000000
Loading: ####################################
done
Bytes transferred = 524288 (80000 hex)
Stoke> crc32 1000000 8000
CRC32 for 01000000 ... 01007fff ==> 6f2392e1
Stoke> crc32 eff80000 80000
CRC32 for eff80000 ... efffffff ==> 60808e8d
Stoke> mw.b ffdf0043 1
Stoke> crc32 eff80000 80000
CRC32 for eff80000 ... efffffff ==> 60808e8d
Stoke>  setenv serverip 172.17.3.20
Stoke> tftp 40000000 builder/xglc-programmables/latest/stoke_xglc_20110817.img
Using FM2@DTSEC4 device
TFTP from server 172.17.3.20; our IP address is 172.17.24.12; sending through gateway 172.17.16.1
Filename 'builder/xglc-programmables/latest/stoke_xglc_20110817.img'.
Load address: 0x40000000
Loading: ####################################
done
Bytes transferred = 524288 (80000 hex)
Stoke> crc32 40000000 80000
CRC32 for 40000000 ... 4007ffff ==> 60808e8d
Stoke> serverip 172.17.24.10
Unknown command 'serverip' - try 'help'
Stoke> setenv serverip 172.17.24.10
Stoke> tftp 1000000 OS_B/stokebootxglc.bin
Using FM2@DTSEC4 device
TFTP from server 172.17.24.10; our IP address is 172.17.24.12
Filename 'OS_B/stokebootxglc.bin'.
Load address: 0x1000000
Loading: ####################################
done
Bytes transferred = 524288 (80000 hex)
Stoke> crc32 1000000 80000
CRC32 for 01000000 ... 0107ffff ==> 60808e8d
Stoke> tftp 1000000 OS_B/rcw_xglc.bin
Using FM2@DTSEC4 device
TFTP from server 172.17.24.10; our IP address is 172.17.24.12
Filename 'OS_B/rcw_xglc.bin'.
Load address: 0x1000000
Loading: #
done
Bytes transferred = 80 (50 hex)
Stoke> crc32 1000000 50
CRC32 for 01000000 ... 0100004f ==> 437572c9
Stoke> crc32 e8000000 50
CRC32 for e8000000 ... e800004f ==> 437572c9
Stoke>
CRC32 for e8000000 ... e800004f ==> 437572c9
Stoke>
CRC32 for e8000000 ... e800004f ==> 437572c9
Stoke> setenv serverip 172.17.3.20
Stoke> tftp 40000000 builder/xglc-programmables/latest/bootloader2
Using FM2@DTSEC4 device
TFTP from server 172.17.3.20; our IP address is 172.17.24.12; sending through gateway 172.17.16.1
Filename 'builder/xglc-programmables/latest/bootloader2'.
Load address: 0x40000000
Loading: #################################################################
         #################################################################
         #################################################################
         #################################################################
         #################################################################
         #################################################################
         ###############################
done
Bytes transferred = 6171064 (5e29b8 hex)
