################################################################################
#
# Module:      SSX3.pm
#
# Author:      Joe White ( mailto:joe@stoke.com )
#
# Descr:      Stoke Specific Libray for Gen2 Changes
#
# Version:    (See below) $Id: Stoke3.pm,v 1.2 2012/02/17 17:13:42 joe Exp $
#
# Changes:    Added 092811
#		["71","NPU_VDD_SRAM","VDD_0V9_NPU_SRAM","1.0","1.0","0.05","0.05"],
		#["72","NPU_1_0V","VDD_1V0_NPU","1.0","1","0.05","0.05"],
#		 Temorary for Hardware bug
#		Added Support for 4 XGLCs
#		Added Support for Copper,1gig, LR SFP perprot Added power measure
#		GE2 GE3 changed NO/YES
#             #Name Changes to Mavenir  1/29/15
#
#
# Still ToDo:
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1995 - 2005 Paul Tindle. All rights reserved.
#            Copyright (c) 2005-2015 Mavenir. All rights reserved.
#
################################################################################
my $Ver = '1.4 012915';   #             #Name Changes to Mavenir  1/29/15
my $CVS_Ver = ' [ CVS: $Id: Stoke3.pm,v 1.2 2012/02/17 17:13:42 joe Exp $ ]';
$Version{'SSX3'} = $Ver . $CVS_Ver;
use Data::Dumper;
#_____________________________________________________________________________
sub Check_CRC32 { #Check CRC32 agaist previous CRC32 for a match
#     our $crc32_match_gbl = 0;
#our $crc32_str_gbl = "na";
#CRC32 for e8000000 ... e8ffffff ==> 9247a644
    #Check the output of the "rd i2c 9501 U200" command
    $crc32_match_gbl = 1;
    &Print2XLog( "CRC32 check of: $crc32_str_gbl $1",1);
   foreach (split /\n/, $Buffer) {
        if ( /^.*==>\s(\w+)$/ ) {
     			if ($crc32_str_gbl eq $1 ) {
                 $crc32_match_gbl = 0 ;
     			 	&Print2XLog( "CRC32 Matched: $1",1);
     			} else {
				$crc32_match_gbl = 1;
     				&Print2XLog( "CRC32 No Match. Setting crc32_str_gbl to $1",1);
     				$crc32_str_gbl = $1;

     			}
   }
}

}
#_____________________________________________________________________________

sub Check_GLC_Redundancy { #Check byte compare
#cmp.b 1000000 e9000000 $filesize
#Total of 18533960 bytes were the same

   #print "varible $xfersizebyte_str_gbl\n";
   foreach (split /\n/, $Buffer) {
   		#print "buf:$_\n";
        if ( /GLC Redundancy Group: 1/ ) {
                 $glcredundant_gbl = 0 ;
                 $noglcredundant_gbl = 1 ;
     			 	&Print2XLog( "Found: GLC Redundancy Group: 1");
     			 	return;
     			} else {
					$glcredundant_gbl = 1;
					$noglcredundant_gbl = 0 ;
     				&Print2XLog( "Not found: GLC Redundancy Group: 1",1);

     			}
   }
}
#_____________________________________________________________________________

sub Check_GLC_Slot4_Enable { #Check byte compare
#cmp.b 1000000 e9000000 $filesize
#Total of 18533960 bytes were the same

   #print "varible $xfersizebyte_str_gbl\n";
   foreach (split /\n/, $Buffer) {
   		#print "buf:$_\n";
        if ( /Four line-card:       Disabled/  && $Slot_INST_1_GLC_GBL ) {
                 $glcslot4enable_gbl = 1 ;
                 $noglcslot4enable_gbl = 0 ;
     			 	&Print2XLog( "Found: Four line-card: Enabled, XGLC in Slot 1");
     			 	return;
     			} elsif (/Four line-card:       Enabled/  && ! $Slot_INST_1_GLC_GBL) {
					$glcslot4enable_gbl = 0;
					$noglcslot4enable_gbl = 1 ;
     				&Print2XLog( "Found: Four line-card: Enabled, No XGLC in Slot 1",1);
                 } else {
                    $glcslot4enable_gbl = 0;
					$noglcslot4enable_gbl = 0 ;
     				&Print2XLog( "No Change needed",1);

     			}
   }
}
#_____________________________________________________________________________

sub Check_bytecompare { #Check byte compare
#cmp.b 1000000 e9000000 $filesize
#Total of 18533960 bytes were the same
    $compare_gbl = 1;
   #print "varible $xfersizebyte_str_gbl\n";
   foreach (split /\n/, $Buffer) {
   		#print "buf:$_\n";
        if ( /$xfersizebyte_str_gbl/ ) {
                 $compare_gbl = 0 ;
     			 	&Print2XLog( "Found: $xfersizebyte_str_gbl");
     			 	return;
     			} else {
					$compare_gbl = 1;
     				&Print2XLog( "Not found: $xfersizebyte_str_gbl",1);

     			}
   }
}
#_____________________________________________________________________________

sub Check_tftp_size { #Check CRC32 agaist previous CRC32 for a match
#Bytes transferred = 18533960 (11ace48 hex)

#     our $crc32_match_gbl = 0;
#our $crc32_str_gbl = "na";
##Bytes transferred = 18533960 (11ace48 hex)
    #Check the output of the "rd i2c 9501 U200" command
    &Print2XLog( "Transfer Size check of: $ubootxfersize_str_gbl",1);
   foreach (split /\n/, $Buffer) {
   		#print "Buffer $_\n";
        if ( /Bytes.transferred.=.(\w+).\((\w+).hex/ ) {
     		 	$ubootxfersize_str_gbl = $2;
     			 	&Print2XLog( "Found Transfersize: $1:$2");
     			 	$xfersizebyte_str_gbl = "Total of $1 bytes were the same";
     			}
   }
}
   #Total of 80 bytes were the same
   #Total of 80 bytes were the same

 #_____________________________________________________________________________
 sub Check_tftp_Ping { #Check CRC32 agaist previous CRC32 for a match
our $Check_tftp_Ping_glb = 0;
my($answer) = "" ;
   foreach (split /\n/, $Buffer) {
   		#print "Buffer $_\n";
        if ( /host.*is alive/ ) {

    		until ($answer =~ /^[YyNn]/) {
    			print("\nOperator: TFTP Boot Diags?: Y/N\n");
    			print("Enter Yes or No: ");
    			$answer = <STDIN>;
    			}
			&Print2XLog ("Operator: TFTP Boot Diags: Y/N: $answer\n");
    		if ($answer =~ /^[Nn]/)  {
    		&Print2XLog( "Ping OK, TFTP Boot Diag Not Selected");
     			 	$Check_tftp_Ping_glb = 0;
    		} else {
    			&Print2XLog( "Ping OK, TFTP Boot Diag Selected");
                 	$Check_tftp_Ping_glb = 1;
    		}

     			}
   }
}
   #Total of 80 bytes were the same
   #Total of 80 bytes were the same

 #_____________________________________________________________________________

 sub Check_XGLC_Diag { # Check the startup output   Check_XGLC_Diag

#Adding Xglc  5/25/11
       my @diaginfo_XGLC  = (
"BLoader image is valid - boot proceeding",
"box->boxtype = 1",
"DDR Interleaving = 0",
"smp_init: 8 cpu",
"In xglc_init_hwinfo.",
"xglc_init_hwinfo.. eBLBC config",
"xglc_init_hwinfo.. BMAN/QMAN config",
"xglc_init_hwinfo.. NOR flash config",
"xglc_init_hwinfo.. CPLD config",
"find_law addr = 0000000ff4000000 size 4096",
"law_addr = 0000000ff4000000 size 4096",
"find_law addr = 0000000ff4000000 size 4096",
"xglc_init_hwinfo() PCIe config",
"find_law addr = 0000000fc0000000 size 536870912",
"law_addr = 0000000fc0000000 size 536870912",
"find_law addr = 0000000fc0000000 size 536870912",
"law_addr = 0000000fc0000000 size 536870912",
"find_law addr = 0000000fc0000000 size 536870912",
"find_law addr = 0000000ff8020000 size 65536",
"law_addr = 0000000ff8020000 size 65536",
"find_law addr = 0000000ff8020000 size 65536",
"law_addr = 0000000ff8020000 size 65536",
"find_law addr = 0000000ff8020000 size 65536",
"find_law addr = 0000000fa0000000 size 536870912",
"law_addr = 0000000fa0000000 size 536870912",
"find_law addr = 0000000fa0000000 size 536870912",
"find_law addr = 0000000ff8010000 size 65536",
"law_addr = 0000000ff8010000 size 65536",
"find_law addr = 0000000ff8010000 size 65536",
"find_law addr = 0000000f80000000 size 536870912",
"law_addr = 0000000f80000000 size 536870912",
"find_law addr = 0000000f80000000 size 536870912",
"find_law addr = 0000000ff8000000 size 65536",
"law_addr = 0000000ff8000000 size 65536",
"find_law addr = 0000000ff8000000 size 65536",
"Fixing up any IO overlap",
"Skipping IO region that doesn't shadow SDRAM:     0000000fe0000000-0000000fefff",
"Skipping IO region that doesn't shadow SDRAM:     0000000ff4400000-0000000ff45f",
"Skipping IO region that doesn't shadow SDRAM:     0000000ff4200000-0000000ff43f",
"Skipping IO region that doesn't shadow SDRAM:     0000000ff4000000-0000000ff400",
"Skipping IO region that doesn't shadow SDRAM:     0000000f00000000-0000000f003f",
"Skipping IO region that doesn't shadow SDRAM:     0000000fc0000000-0000000fdfff",
"Skipping IO region that doesn't shadow SDRAM:     0000000ff8020000-0000000ff802",
"Skipping IO region that doesn't shadow SDRAM:     0000000fa0000000-0000000fbfff",
"Skipping IO region that doesn't shadow SDRAM:     0000000ff8010000-0000000ff801",
"Skipping IO region that doesn't shadow SDRAM:     0000000f80000000-0000000f9fff",
"Skipping IO region that doesn't shadow SDRAM:     0000000ff8000000-0000000ff800",
"L3 cache0 already enabled by bootloader, skipping init.",
"L3 cache1 already enabled by bootloader, skipping init.",
"Loading IFS...decompressing...done",
"System page at phys:08008000 user:08008000 kern:08008000",
"Starting next program at v00aeca1c",
"Booting Stoke XGLC Bench Bringup",
"Starting i2c driver..... .OK.",
"Starting pci driver..... .OK.",
"Initializing Trident on slot 2",
"PCI: Found Trident Switch",
"Aperture 0 Base 0xfa0000000 Length 262144 bytes Type MEM",
"Device b842 Revision 1 supported",
"SOC unit 0 went through mmu init",
"In bcm_tr_l2_init 3 unit 0",
"soc_mem_read: invalid index 1162 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1162 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1202 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1202 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1242 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1242 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1282 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1282 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1172 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1172 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1212 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1212 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1252 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1252 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1292 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1292 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1182 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1182 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1222 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1222 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1262 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1262 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1302 for memory MMU_CTR_UC_DROP_MEM",
"soc_mem_read: invalid index 1302 for memory MMU_CTR_UC_DROP_MEM",
"config_var_get name bcm_tx_thread_pri value 0x1",
"config_var_get name bcm_tx_thread_pri value 0x1",
"Setting Enable on port 5",
"Setting Enable on port 6",
"Setting Enable on port 7",
"Setting Enable on port 8",
"Setting Enable on port 9",
"Setting Enable on port 10",
"Setting Enable on port 11",
"Setting Enable on port 12",
"Setting Enable on port 13",
"Setting Enable on port 14",
"Setting Enable on port 15",
"Setting Enable on port 16",
"Setting Enable on port 17",
"Setting Enable on port 18",
"Setting linkscan/stp on port 1",
"Setting linkscan/stp on port 2",
"Setting linkscan/stp on port 3",
"Setting linkscan/stp on port 4",
"Setting linkscan/stp on port 5",
"Setting linkscan/stp on port 6",
"Setting linkscan/stp on port 7",
"Setting linkscan/stp on port 8",
"Setting linkscan/stp on port 9",
"Setting linkscan/stp on port 10",
"Setting linkscan/stp on port 11",
"Setting linkscan/stp on port 12",
"Setting linkscan/stp on port 13",
"Setting linkscan/stp on port 14",
"Setting linkscan/stp on port 15",
"Setting linkscan/stp on port 16",
"Setting linkscan/stp on port 17",
"Setting linkscan/stp on port 18",
"Setting autoneg/linkscan/stp on port 19",
"Setting autoneg/linkscan/stp on port 20",
"Setting autoneg/linkscan/stp on port 21",
"Setting autoneg/linkscan/stp on port 22",
"Setting autoneg/linkscan/stp on port 23",
"Setting autoneg/linkscan/stp on port 24",
"Setting autoneg/linkscan/stp on port 25",
"Setting autoneg/linkscan/stp on port 26",
"Setting autoneg/linkscan/stp on port 27",
"Setting autoneg/linkscan/stp on port 28",
"Setting autoneg/linkscan/stp on port 29",
"Setting autoneg/linkscan/stp on port 30",
"config_var_get name linkscan_thread_pri value 1",
"Broadcom Command Monitor: Copyright .c. 1998-2010 Broadcom Corporation",
"Trident base channel",
"Trident Fabric channel",
"Configuring base channel..... .OK.",
"TODO: dump directory",
"nvctl_kbp_init.. setting KBP flags to 0",
"fuinit: taking XLPs out of reset",
"Releasing KBP from reset. flags = 0x00"
);


       my $postcount_XGLC = @diaginfo_XGLC;
       my $postcount = 0;
       #@postinfo = (split /\n/, $Buffer);
   foreach (split /\n/, $Buffer) {
     foreach (@diaginfo_XGLC) {      #foreach (@Screen_Data)
     	$postinfo_XGLC_str = $_;
        if (( $postcount <= $postcount_XGLC -1 )) {
            &Log_Error ("Mismatch in POST line count") if ( $postcount > $postcount_XGLC -1 ) ;
                foreach (@Screen_Data)  {
                	if (/$postinfo_XGLC_str/ ) {
                		print "Found post info: $postinfo_XGLC_str\n" if $Debug;
                    	$postinfo_XGLC_str_found++
                	}
                }
                &Log_Error ("POST string: $temp not found") if (! $postinfo_XGLC_str_found);
        }
    }
 }



}

#______________________________________________________________________________
 sub Check_XGLC_HD_Copytime { # Check the startup output   Check_XGLC_Diag
                                      ##################################
     foreach (@Screen_Data) {      #foreach (@Screen_Data)
     	#   100.54s real     0.00s user     0.02s system
        if (/(\d+\.\d+)s real/ ) {
           &Log_Error ("Found Copy Time: $1 > 50 Seconds ") if ($1 > 50 )  ;
        } else {
           #&Print2XLog("Found Copy Time: $1",1)
           Print2XLog("Found Copy Time: $1") if ($1 ne '');
              	}
  #
  #
  ####
  ###
  ###
  ###
  ##
	}
 }

#______________________________________________________________________________
 sub Check_XGLC_I2C { # Check the startup output   Check_XGLC_Diag

#Adding Xglc  5/25/11
#Stoke> i2cscan
#Enb control f
#Enabling local bus on bus 0
#Enabling VRM & PMBUS switch on bus 0
#Bus = 0, Switch#0 Port = 0,Valid chip addresses: 4C 4D 50 70
#Bus = 0, Switch#0 Port = 1,Valid chip addresses: 48 4A 4C 50 70
#Bus = 0, Switch#0 Port = 2,Valid chip addresses: 18 2F 50 70 72 7C 7E
#Bus = 0, Switch#0 Port = 2,Switch#1 Port = 0,Valid chip addresses: 50 60 70 72 7C 7E
#Bus = 0, Switch#0 Port = 2,Switch#1 Port = 1,Valid chip addresses: 50 60 70 72 7C 7E
#Bus = 0, Switch#0 Port = 2,Switch#1 Port = 2,Valid chip addresses: 50 60 70 72 7C 7E
#Bus = 0, Switch#0 Port = 2,Switch#1 Port = 3,Valid chip addresses: 50 60 70 72 7C 7E
#Bus = 0, Switch#0 Port = 3,Valid chip addresses: 50 57 6A 6E 70
#Bus = 1,Valid chip addresses: 19 1A 31 32 51 52
#Bus = 3, Switch Port = 0,Valid chip addresses: 50 51 71 74 75
#Bus = 3, Switch Port = 1,Valid chip addresses: 50 51 71 74 75
#Bus = 3, Switch Port = 2,Valid chip addresses: 50 51 71 74 75
#Bus = 3, Switch Port = 3,Valid chip addresses: 50 51 71 74 75

# Added 10/9/12 for 1gig SFP support
my $sfpaddress = "Valid chip addresses: 50 51 71 74 75";
if    ($XGLC_1gigSFP==1) {
   $sfp_address = "Valid chip addresses: 50 51.*71 74 75";
}
       my @diaginfo_XGLC  = (
"Enabling local bus on bus 0",
"Enabling VRM & PMBUS switch on bus 0",
"Bus = 0, Switch#0 Port = 0,Valid chip addresses: 4C 4D 50 70",
"Bus = 0, Switch#0 Port = 1,Valid chip addresses: 48 4A 4C 50 70",
"Bus = 0, Switch#0 Port = 2,Valid chip addresses: 18 2F 50 70 72 7C 7E",
#"Bus = 0, Switch#0 Port = 2,Switch#1 Port = 0,Valid chip addresses: 50 60 70 72 7C 7E",
"Bus = 0, Switch#0 Port = 2,Switch#1 Port = 0,Valid chip addresses: 50 60 70 72",
#"Bus = 0, Switch#0 Port = 2,Switch#1 Port = 1,Valid chip addresses: 50 60 70 72 7C 7E",
"Bus = 0, Switch#0 Port = 2,Switch#1 Port = 1,Valid chip addresses: 50 60 70 72",
#"Bus = 0, Switch#0 Port = 2,Switch#1 Port = 2,Valid chip addresses: 50 60 70 72 7C 7E",
"Bus = 0, Switch#0 Port = 2,Switch#1 Port = 2,Valid chip addresses: 50 60 70 72",
#"Bus = 0, Switch#0 Port = 2,Switch#1 Port = 3,Valid chip addresses: 50 60 70 72 7C 7E",
"Bus = 0, Switch#0 Port = 2,Switch#1 Port = 3,Valid chip addresses: 50 60 70 72",
"Bus = 0, Switch#0 Port = 3,Valid chip addresses: 50 57 6A 6E 70",
"Bus = 1,Valid chip addresses: 19 1A 31 32 51 52",
"Bus = 3, Switch Port = 0,$sfp_address",
"Bus = 3, Switch Port = 1,$sfp_address",
"Bus = 3, Switch Port = 2,$sfp_address",
"Bus = 3, Switch Port = 3,$sfp_address"
);
       my $postinfo_XGLC_str_found = 0;
       my $postinfo_XGLC_str = "";
       my $postcount_XGLC = @diaginfo_XGLC;
       my $postcount = 0;
       #@postinfo = (split /\n/, $Buffer);
 #  foreach (split /\n/, $Buffer) {
     foreach (@diaginfo_XGLC) {      #foreach (@Screen_Data)
     	$postinfo_XGLC_str = $_;
        if (( $postcount <= $postcount_XGLC -1 )) {
            $postinfo_XGLC_str_found = 0;
            &Log_Error ("Mismatch in I2C line count") if ( $postcount > $postcount_XGLC -1 ) ;
                foreach (@Screen_Data)  {
                	if (/$postinfo_XGLC_str/ ) {
                		print "Found I2C info: $postinfo_XGLC_str\n" if $Debug;
                    	$postinfo_XGLC_str_found++ ;
                	}
                }
                &Log_Error ("I2C string: $_ not found") if (! $postinfo_XGLC_str_found);
        }
  #  }
 }



}

#______________________________________________________________________________

sub Check_XGLC_voltage {



#DIAG > monitor voltage all
#Voltage VDD_1V0_CPU_CA value 1020mv
#Voltage VDD_1V0_CPU_CB value 1012mv
#Voltage VDD_1V0_CPU_PL value 988mv
#Voltage VDD_1V5_CPU_DDR3 value 1492mv
#Voltage CPU_SDRAM_VTT value 740mv
#Voltage KBP_0_ANALOG value 892mv
#Voltage KBP_1_ANALOG value 892mv
#Voltage KBP_0_CORE value 900mv
#Voltage KBP_1_CORE value 900mv
#Voltage NPU_1_0V value 1004mv
#Voltage NPU_VDD_SRAM value 1004mv
#Voltage NPU_0_ANALOG value 988mv
#Voltage NPU_1_ANALOG value 980mv
#Voltage NPU_0_AC_AD_VTT value 740mv
#Voltage NPU_0_BD_AD_VTT value 740mv
#Voltage NPU_1_AC_AD_VTT value 740mv
#Voltage NPU_1_BD_AD_VTT value 740mv
#Voltage NPU_0_DDR3 value 1492mv
#Voltage NPU_1_DDR3 value 1492mv
#Voltage VRM_SOC_PGOOD value 1204mv
#Voltage VRM_VDD_PGOOD value 1204mv
#Voltage SWITCH_ANALOG value 988mv
#Voltage SWITCH_CORE value 1004mv
#Voltage VCC_1_2V value 1196mv
#Voltage VCC_1_8V value 1784mv
#3Voltage VCC_2_5V value 2473mv
#Voltage VCC_3_3V value 3296mv
#Voltage VCC_12_0V value 11771mv

my @voltage = (
# reg, Name1, Name2, Nom, Mult, %Hi,%lo
["70","VCC_1_2V","VDD_1V2","1.2","1.0","0.05","0.05"],
["71","NPU_VDD_SRAM","VDD_0V9_NPU_SRAM","1.0","1.0","0.05","0.05"],
["72","NPU_1_0V","VDD_1V0_NPU","1.0","1.0","0.05","0.05"],
["73","NPU_0_ANALOG","VDDA_1V0_NPU0","1.0","1.0","0.05","0.05"],
["74","NPU_1_ANALOG","VDDA_1V0_NPU1","1.0","1.0","0.05","0.05"],
["75","KBP_0_CORE","VDD_0V9_CAM0","0.9","1.0","0.05","0.05"],
["76","KBP_1_CORE","VDD_0V9_CAM1","0.9","1.0","0.05","0.05"],
["77","KBP_0_ANALOG","VDDA_0V9_CAM0","0.9","1.0","0.05","0.05"],
["78","KBP_1_ANALOG","VDDA_0V9_CAM1","0.9","1.0","0.05","0.05"],
["79","VCC_1_8V","VDD_1V8","1.8","2.0","0.05","0.05"],
["7A","NPU_0_DDR3","VDD_1V5_NPU0","1.5","1.0","0.05","0.05"],
["7B","NPU_1_DDR3","VDD_1V5_NPU1","1.5","1.0","0.05","0.05"],
["7C","VCC_3_3V","VCC_3V3","3.3","3.31","0.05","0.05"],
["7D","VCC_2_5V","VDD_2V5","2.5","2.504","0.05","0.05"],
["7E","SWITCH_ANALOG","VDD_1V0_FAB_ANA","1.0","1.0","0.05","0.05"],
["7F","SWITCH_CORE","VDD_AVS_FAB_DIG","1.0","1.0","0.05","0.05"],
["80","VDD_1V0_CPU_CA","VDD_1V0_CPU_CA","1.0","1.0","0.05","0.05"],
["81","VDD_1V0_CPU_CB","VDD_1V0_CPU_CB","1.0","1.0","0.05","0.05"],
["82","VDD_1V0_CPU_PL","VDD_1V0_CPU_PL","1.0","1.0","0.05","0.05"],
["83","VDD_1V5_CPU_DDR3","VDD_1V5_CPU","1.5","1.0","0.05","0.05"],
["84","NPU_1_AC_AD_VTT","NPU0_M_VTTAC","0.75","1.0","0.05","0.05"],
["85","NPU_0_BD_AD_VTT","NPU0_M_VTTBD","0.75","1.0","0.05","0.05"],
["86","NPU_0_AC_AD_VTT","NPU1_M_VTTAC","0.75","1.0","0.05","0.05"],
["87","NPU_1_BD_AD_VTT","NPU1_M_VTTBD","0.75","1.0","0.05","0.05"],
["88","CPU_SDRAM_VTT","CPU_M_VTT","0.75","1.0","0.05","0.05"],
["89","VCC_12_0V","VCC_12V","12.0","12.111","0.05","0.05"],
["8A","VRM_SOC_PGOOD","VRM_SOC_PGOOD","1","1","1","1"],
["8B","VRM_VDD_PGOOD","VRM_VDD_PGOOD","1","1","1","1"],
);
#DIAG >
    my $arrayi = 0;
    print "Checking Voltages\n";
    my $hivoltage = 0;
    my $lowvoltage = 0;
    foreach (@Screen_Data) {
    	 $arryi = 0;
    	 #print "Screen $_\n";
         for ($arrayi = 0; $arrayi < 29; $arrayi++ ) {
         		#print "checking count $arrayi $voltage[$arrayi][1]\n";
         		#Voltage VCC_2_5V value 2473mv
                if (/Voltage.(\w+).value.(\d+)mv/) {
                        #print " Found Voltage 1 $1 and comparing to $voltage[$arrayi][1] \n";
                        if ($voltage[$arrayi][1] eq  $1) {
                            # Test Voltage
                            #print "Found $voltage[$arrayi][1]\n";
                            $hivoltage  = (((1+$voltage[$arrayi][5])*$voltage[$arrayi][3]))*1000 ;
                            $lowvoltage =  (((1-$voltage[$arrayi][6])*$voltage[$arrayi][3]))*1000 ;
                            if ($2 <= $hivoltage && $2 >= $lowvoltage ) {
                            	&Print2XLog("Voltage pass $voltage[$arrayi][1] was $2 mv \nExpected($voltage[$arrayi][3] mv): $lowvoltage mv to $hivoltage mv",1);
                            } else {
                              &Log_Error ("Voltage Fail $voltage[$arrayi][1] was $2 mv \nExpected($voltage[$arrayi][3] v): $lowvoltage mv to $hivoltage mv");
                            }
                       }
                }
            #$arrayi++;
          }
	}


}

#__________________________________________________________________________

sub Check_XGLC_voltage_Margin_low {



#DIAG > monitor voltage all
#Voltage VDD_1V0_CPU_CA value 1020mv
#Voltage VDD_1V0_CPU_CB value 1012mv
#Voltage VDD_1V0_CPU_PL value 988mv
#Voltage VDD_1V5_CPU_DDR3 value 1492mv
#Voltage CPU_SDRAM_VTT value 740mv
#Voltage KBP_0_ANALOG value 892mv
#Voltage KBP_1_ANALOG value 892mv
#Voltage KBP_0_CORE value 900mv
#Voltage KBP_1_CORE value 900mv
#Voltage NPU_1_0V value 1004mv
#Voltage NPU_VDD_SRAM value 1004mv
#Voltage NPU_0_ANALOG value 988mv
#Voltage NPU_1_ANALOG value 980mv
#Voltage NPU_0_AC_AD_VTT value 740mv
#Voltage NPU_0_BD_AD_VTT value 740mv
#Voltage NPU_1_AC_AD_VTT value 740mv
#Voltage NPU_1_BD_AD_VTT value 740mv
#Voltage NPU_0_DDR3 value 1492mv
#Voltage NPU_1_DDR3 value 1492mv
#Voltage VRM_SOC_PGOOD value 1204mv
#Voltage VRM_VDD_PGOOD value 1204mv
#Voltage SWITCH_ANALOG value 988mv
#Voltage SWITCH_CORE value 1004mv
#Voltage VCC_1_2V value 1196mv
#Voltage VCC_1_8V value 1784mv
#3Voltage VCC_2_5V value 2473mv
#Voltage VCC_3_3V value 3296mv
#Voltage VCC_12_0V value 11771mv

my @voltage = (
# reg, Name1, Name2, Nom, Mult, %Hi,%lo
["70","VCC_1_2V","VDD_1V2","1.14","1.0","0.05","0.05"],
["71","NPU_VDD_SRAM","VDD_0V9_NPU_SRAM","0.95","1.0","0.05","0.05"],
["72","NPU_1_0V","VDD_1V0_NPU","0.95","1","0.05","0.05"],
#["71","NPU_VDD_SRAM","VDD_0V9_NPU_SRAM","1.0","1.0","0.05","0.05"], #bypass Group 7 margin
#["72","NPU_1_0V","VDD_1V0_NPU","1.0","1","0.05","0.05"],
["73","NPU_0_ANALOG","VDDA_1V0_NPU0","0.95","1.0","0.05","0.05"],
["74","NPU_1_ANALOG","VDDA_1V0_NPU1","0.95","1.0","0.05","0.05"],
["75","KBP_0_CORE","VDD_0V9_CAM0","0.85","1.0","0.05","0.05"],
["76","KBP_1_CORE","VDD_0V9_CAM1","0.85","1.0","0.05","0.05"],
["77","KBP_0_ANALOG","VDDA_0V9_CAM0","0.85","1.0","0.05","0.05"],
["78","KBP_1_ANALOG","VDDA_0V9_CAM1","0.85","1.0","0.05","0.05"],
["79","VCC_1_8V","VDD_1V8","1.7","2.0","0.05","0.05"],
["7A","NPU_0_DDR3","VDD_1V5_NPU0","1.42","1.0","0.05","0.05"],
["7B","NPU_1_DDR3","VDD_1V5_NPU1","1.42","1.0","0.05","0.05"],
["7C","VCC_3_3V","VCC_3V3","3.1","3.31","0.05","0.05"],
["7D","VCC_2_5V","VDD_2V5","2.4","2.504","0.05","0.05"],
["7E","SWITCH_ANALOG","VDD_1V0_FAB_ANA","0.95","1.0","0.05","0.05"],
["7F","SWITCH_CORE","VDD_AVS_FAB_DIG","1","1.0","0.05","0.05"],
["80","VDD_1V0_CPU_CA","VDD_1V0_CPU_CA","0.95","1.0","0.05","0.05"],
["81","VDD_1V0_CPU_CB","VDD_1V0_CPU_CB","0.95","1.0","0.05","0.05"],
["82","VDD_1V0_CPU_PL","VDD_1V0_CPU_PL","0.95","1.0","0.05","0.05"],
["83","VDD_1V5_CPU_DDR3","VDD_1V5_CPU","1.42","1.0","0.05","0.05"],
["84","NPU_1_AC_AD_VTT","NPU0_M_VTTAC","0.71","1.0","0.05","0.05"],
["85","NPU_0_BD_AD_VTT","NPU0_M_VTTBD","0.71","1.0","0.05","0.05"],
["86","NPU_0_AC_AD_VTT","NPU1_M_VTTAC","0.71","1.0","0.05","0.05"],
["87","NPU_1_BD_AD_VTT","NPU1_M_VTTBD","0.71","1.0","0.05","0.05"],
["88","CPU_SDRAM_VTT","CPU_M_VTT","0.71","1.0","0.05","0.05"],
["89","VCC_12_0V","VCC_12V","12.0","12.111","0.05","0.05"],
["8A","VRM_SOC_PGOOD","VRM_SOC_PGOOD","1","1","1","1"],
["8B","VRM_VDD_PGOOD","VRM_VDD_PGOOD","1","1","1","1"],
);
#DIAG >
    my $arrayi = 0;
    print "Checking Margin Low Voltages\n";
    my $hivoltage = 0;
    my $lowvoltage = 0;
    foreach (@Screen_Data) {
    	 $arryi = 0;
    	 #print "Screen $_\n";
         for ($arrayi = 0; $arrayi < 29; $arrayi++ ) {
         		#print "checking count $arrayi $voltage[$arrayi][1]\n";
         		#Voltage VCC_2_5V value 2473mv
                if (/Voltage.(\w+).value.(\d+)mv/) {
                        #print " Found Voltage 1 $1 and comparing to $voltage[$arrayi][1] \n";
                        if ($voltage[$arrayi][1] eq  $1) {
                            # Test Voltage
                            #print "Found $voltage[$arrayi][1]\n";
                            $hivoltage  = (((1+$voltage[$arrayi][5])*$voltage[$arrayi][3]))*1000 ;
                            $lowvoltage =  (((1-$voltage[$arrayi][6])*$voltage[$arrayi][3]))*1000 ;
                            if ($2 <= $hivoltage && $2 >= $lowvoltage ) {
                            	&Print2XLog("Voltage pass $voltage[$arrayi][1] was $2 mv \nExpected($voltage[$arrayi][3] mv): $lowvoltage mv to $hivoltage mv",1);
                            } else {
                              &Log_Error ("Voltage Fail $voltage[$arrayi][1] was $2 mv \nExpected($voltage[$arrayi][3] v): $lowvoltage mv to $hivoltage mv");
                            }
                       }
                }
            #$arrayi++;
          }
	}


}

#__________________________________________________________________________
sub Check_XGLC_voltage_Margin_high {



#DIAG > monitor voltage all
#Voltage VDD_1V0_CPU_CA value 1020mv
#Voltage VDD_1V0_CPU_CB value 1012mv
#Voltage VDD_1V0_CPU_PL value 988mv
#Voltage VDD_1V5_CPU_DDR3 value 1492mv
#Voltage CPU_SDRAM_VTT value 740mv
#Voltage KBP_0_ANALOG value 892mv
#Voltage KBP_1_ANALOG value 892mv
#Voltage KBP_0_CORE value 900mv
#Voltage KBP_1_CORE value 900mv
#Voltage NPU_1_0V value 1004mv
#Voltage NPU_VDD_SRAM value 1004mv
#Voltage NPU_0_ANALOG value 988mv
#Voltage NPU_1_ANALOG value 980mv
#Voltage NPU_0_AC_AD_VTT value 740mv
#Voltage NPU_0_BD_AD_VTT value 740mv
#Voltage NPU_1_AC_AD_VTT value 740mv
#Voltage NPU_1_BD_AD_VTT value 740mv
#Voltage NPU_0_DDR3 value 1492mv
#Voltage NPU_1_DDR3 value 1492mv
#Voltage VRM_SOC_PGOOD value 1204mv
#Voltage VRM_VDD_PGOOD value 1204mv
#Voltage SWITCH_ANALOG value 988mv
#Voltage SWITCH_CORE value 1004mv
#Voltage VCC_1_2V value 1196mv
#Voltage VCC_1_8V value 1784mv
#3Voltage VCC_2_5V value 2473mv
#Voltage VCC_3_3V value 3296mv
#Voltage VCC_12_0V value 11771mv

my @voltage = (
# reg, Name1, Name2, Nom, Mult, %Hi,%lo         # 5% margin low
["70","VCC_1_2V","VDD_1V2","1.26","1.0","0.05","0.05"],
["71","NPU_VDD_SRAM","VDD_0V9_NPU_SRAM","1.05","1.0","0.05","0.05"],
["72","NPU_1_0V","VDD_1V0_NPU","1.05","1.0","0.05","0.05"],
["73","NPU_0_ANALOG","VDDA_1V0_NPU0","1.05","1.0","0.05","0.05"],
["74","NPU_1_ANALOG","VDDA_1V0_NPU1","1.05","1.0","0.05","0.05"],
["75","KBP_0_CORE","VDD_0V9_CAM0","0.95","1.0","0.05","0.05"],
["76","KBP_1_CORE","VDD_0V9_CAM1","0.95","1.0","0.05","0.05"],
["77","KBP_0_ANALOG","VDDA_0V9_CAM0","0.95","1.0","0.05","0.05"],
["78","KBP_1_ANALOG","VDDA_0V9_CAM1","0.95","1.0","0.05","0.05"],
["79","VCC_1_8V","VDD_1V8","1.89","2.0","0.05","0.05"],
["7A","NPU_0_DDR3","VDD_1V5_NPU0","1.58","1.0","0.05","0.05"],
["7B","NPU_1_DDR3","VDD_1V5_NPU1","1.58","1.0","0.05","0.05"],
["7C","VCC_3_3V","VCC_3V3","3.47","3.31","0.05","0.05"],
["7D","VCC_2_5V","VDD_2V5","2.63","2.504","0.05","0.05"],
["7E","SWITCH_ANALOG","VDD_1V0_FAB_ANA","1.05","1.0","0.05","0.05"],
["7F","SWITCH_CORE","VDD_AVS_FAB_DIG","1","1.0","0.05","0.05"],
["80","VDD_1V0_CPU_CA","VDD_1V0_CPU_CA","1.05","1.0","0.05","0.05"],
["81","VDD_1V0_CPU_CB","VDD_1V0_CPU_CB","1.05","1.0","0.05","0.05"],
["82","VDD_1V0_CPU_PL","VDD_1V0_CPU_PL","1.05","1.0","0.05","0.05"],
["83","VDD_1V5_CPU_DDR3","VDD_1V5_CPU","1.58","1.0","0.05","0.05"],
["84","NPU_1_AC_AD_VTT","NPU0_M_VTTAC","0.79","1.0","0.05","0.05"],
["85","NPU_0_BD_AD_VTT","NPU0_M_VTTBD","0.79","1.0","0.05","0.05"],
["86","NPU_0_AC_AD_VTT","NPU1_M_VTTAC","0.79","1.0","0.05","0.05"],
["87","NPU_1_BD_AD_VTT","NPU1_M_VTTBD","0.79","1.0","0.05","0.05"],
["88","CPU_SDRAM_VTT","CPU_M_VTT","0.79","1.0","0.05","0.05"],
["89","VCC_12_0V","VCC_12V","12.0","12.111","0.05","0.05"],
["8A","VRM_SOC_PGOOD","VRM_SOC_PGOOD","1","1","1","1"],
["8B","VRM_VDD_PGOOD","VRM_VDD_PGOOD","1","1","1","1"],
);
#DIAG >
    my $arrayi = 0;
    print "Checking Margin high Voltages\n";
    my $hivoltage = 0;
    my $lowvoltage = 0;
    foreach (@Screen_Data) {
    	 $arryi = 0;
    	 #print "Screen $_\n";
         for ($arrayi = 0; $arrayi < 29; $arrayi++ ) {
         		#print "checking count $arrayi $voltage[$arrayi][1]\n";
         		#Voltage VCC_2_5V value 2473mv
                if (/Voltage.(\w+).value.(\d+)mv/) {
                        #print " Found Voltage 1 $1 and comparing to $voltage[$arrayi][1] \n";
                        if ($voltage[$arrayi][1] eq  $1) {
                            # Test Voltage
                            #print "Found $voltage[$arrayi][1]\n";
                            $hivoltage  = (((1+$voltage[$arrayi][5])*$voltage[$arrayi][3]))*1000 ;
                            $lowvoltage =  (((1-$voltage[$arrayi][6])*$voltage[$arrayi][3]))*1000 ;
                            if ($2 <= $hivoltage && $2 >= $lowvoltage ) {
                            	&Print2XLog("Voltage pass $voltage[$arrayi][1] was $2 mv \nExpected($voltage[$arrayi][3] mv): $lowvoltage mv to $hivoltage mv",1);
                            } else {
                              &Log_Error ("Voltage Fail $voltage[$arrayi][1] was $2 mv \nExpected($voltage[$arrayi][3] v): $lowvoltage mv to $hivoltage mv");
                            }
                       }
                }
            #$arrayi++;
          }
	}


}

#__________________________________________________________________________

sub Check_XGLC_BMR {



#DIAG > bmrstatus
#BMR453:
#	IOUT: 16.125 (0x02e1)
#	VIN: 52.125 (0xa1e9)
#	VOUT: 12.035 (0x4860)
#	TEMP: 38.000 (0x2600)
#BMR451:
#	IOUT: 17.594 (0x33da)
#	VIN: 11.969 (0xfed2)
#	VOUT: 0.990 (0xb21f)
#	TEMP: 49.563 (0x19e3)

my @voltage = (
# reg, Name1, Name2, Nom, Mult, %Hi,%lo
["XX","BMR453:","48V Converter","0","1.0","0","0"],
["XX","IOUT:","48VDC_CURRENT","16","1.0","17","15"],
["XX","VIN:","48VDC IN","48","1.0","45","55"],
["XX","TEMP:","48-12V Converter Temp","30","1.0","20","45"],
["XX","BMR451:","1V Converter","0","1.0","0","0"],
["XX","IOUT:","1V_Current","17","1.0","16","19"],
["XX","VIN:","1V ConverterIN","12","1.0","11","13"],
["XX","TEMP:","1V Converter Temp","30","1.0","20","50"]

#Checking BMR
#Log_Error: BMR Fail IOUT::48VDC_CURRENT was 16.125
#Expected(16): 17 to 15
#Log_Error: BMR Fail VIN::1V ConverterIN was 48.125
#Expected(12): 11 to 13
#Log_Error: BMR Fail IOUT::48VDC_CURRENT was 18.469
#Expected(16): 17 to 15
#Log_Error: BMR Fail VIN::48VDC IN was 11.953
#Expected(48): 45 to 55
#Log_Error: BMR Fail TEMP::48-12V Converter Temp was 47.063
#Expected(30): 20 to 45

);
#DIAG >
    my $arrayi = 0;
    print "Checking BMR\n";
    foreach (@Screen_Data) {
    	 $arryi = 0;
    	 #print "Screen $_\n";
         for ($arrayi = 0; $arrayi < 8; $arrayi++ ) {
         		#print "checking count $arrayi $voltage[$arrayi][1]\n";
         		#Voltage VCC_2_5V value 2473mv
                if (/(\w+:) (\d+\.\d+) .*/) {
                        #print " Found Voltage 1 $1 and comparing to $voltage[$arrayi][1] \n";
                        if ($voltage[$arrayi][1] eq  $1) {
                            # Test Voltage
                            #print "Found $voltage[$arrayi][1] eq $1\n";
                             if ($2 <= $voltage[$arrayi][6] && $2 >= $voltage[$arrayi][5] ) {
                            	&Print2XLog("BMR pass $voltage[$arrayi][1] was $2 \nExpected($voltage[$arrayi][3]): $voltage[$arrayi][5] to $voltage[$arrayi][6]",1);
                            } else {
                              &Log_Error ("BMR Fail $voltage[$arrayi][1]:$voltage[$arrayi][2] was $2 \nExpected($voltage[$arrayi][3]): $voltage[$arrayi][5] to $voltage[$arrayi][6]");
                            }
                       }

                }
            #$arrayi++;
          }
	}


}

#__________________________________________________________________________
   sub Check_XGLC_CPLD_Diag_dep { # Check the startup output   Check_XGLC_Diag

#Adding Xglc  5/25/11
       my @cpldinfo_XGLC  = (
 "card-type  04",
  "assy-rev  01",
  "cpld-code-rev  ..",    #09
  "bp-logical-slot-id  ..",   #43
  "bp-system-id  03",
  "board-reset-reason  09",
  "cpu0-reset-reason  01",
  "cpu1-reset-reason  F4",
  "board-reset  F4",
  "cpu0->cpu1-reset  F4",
  "cpu0-watchdog-clear  F4",
  "cpu1-watchdog-clear  F4",
  "watchdog-timer_settings  3B",
  "ixp2800-reset  F4",
  "nitrox-reset  F4",
  "ixf1110-reset  F4",
  "tcam-reset  F4",
  "mgmt-phy-reset  00",
  "quad-uart-reset  F4",
  "fic-reset  F4",
  "pci-0-reset  F4",
  "pci-1-reset  F4",
  "cpu0-sys-mgmt-irq-sts  1E",
  "cpu0-sys-mgmt-irq-en  80",
  "cpu1-sys-mgmt-irq-sts  F4",
  "led:power  01",
  #"led:status  00",   #LED is blinking during Diags
  "led:active/standby  00",
  "i2c-local-enable  00",
  "i2c-global-enable  00",
  "IPMI_A/B-enable  01",
  "CPU-boot-state  00",
  "temp-sensor-sts  F4",
  "diag-jumper-present  00",
  "ipx-gpio  F4",
  "tcam-clock-en  F4",
  "ipx-serial-port-mux-sel  F4",
  "fic/pmc-present  06",
  "arbitration-sts  00",
  "arbitration-req  00",
  "cpu0-sys-mgmt-irq-sts2  0C",
  "cpu0-sys-mgmt-irq-en2  04",
  "flash-rdndnt-ctl-stat  04",
  "card-rev-dev-bus-cpld  F4",
  "link-state-led-ctl     00",
  "circuit-breaker-trip   00",
  "flsh-bnk-rdndnt-remap  01",
  "npu-dbg-phy-rst  00",
  "npu0-rst-ctrl  00",
  "npu1-rst-ctrl  40",
  "cpu-dimm-rst-cbt  00",
  "fab-chip-rst  00",
  "spi-mux-ctrl  03",
  "uart-mux-ctrl  02",
  "power-fault-int-sts  0[13]",    #getting 03 after i2c Scan bit 2 not PMBUS_SMBALERT_L
  "power-fault-int-ena  00",
  "cpu0-irq-ena  00",
  "temperr-int-sts  54",
  "temperr-int-ena  00",
  "cpu0-irq-gen-sts  06",
  "dimm-event-int-sts  00",
  "dimm-event-int-ena  00",
  "cpld-npu-temp-alarm  FF",
  "cpu-misc1-ctrl  00",
  "cpu-misc1-sts  1D",
  "i2c-ena-ctrl  03",
  #"i2c-ena-sfp-ctrl  07",
  "i2c-ena-sfp-ctrl  00",  # After I2c Scan
  "cpld-trigg-out-dmux  00",
  "cpu-npu-misc-sts  3.",   #Getting "cpu-npu-misc-sts  36 after I2C Scan", Bits not fully defined
  "sfpp-port-act-set  00",
  "simulate-pwr-temp-dimm-flt  00",
  "simulate-grp-bits-ena  00",
  "simulate-grp-data  00",
  "cpu-npu-misc2-sts  50",

);

 #"cpld-code-rev 09",
 #"bp-logical-slot-id 43",

       my $postcount_XGLC = @cpldinfo_XGLC;
       my $postcount = 0;
       my $postfound = 0;
       my $postinfo_XGLC_str = '';
       #@postinfo = (split /\n/, $Buffer);
   #foreach (split /\n/, $Buffer) {
     foreach (@cpldinfo_XGLC) {      #foreach (@Screen_Data)
     	$postinfo_XGLC_str = $_;
            $postfound = 0;
        if (( $postcount <= $postcount_XGLC -1 )) {
            &Log_Error ("Mismatch in CPLD line count") if ( $postcount > $postcount_XGLC -1 ) ;
                foreach (@Screen_Data)  {
                	   #	print " Checking $_ to $postinfo_XGLC_str\n";
                	if (/($postinfo_XGLC_str)/) {
                		print "Found CPLD info: $1 expected: $postinfo_XGLC_str\n" if $Debug;
                         $postfound++;
                         if (/cpld-code-rev  (\d+)/ ) {    #(\d+)
                		print "Found CPLD Version: $1\n" ; #if $Debug;
                		&Log_Error ("CPLD Version incorrect") if ($1 ne "09");
                		#if ($1 ne $UUT_Variable_ref[1]->{cpld-code-rev});
                        }
                       if (/bp-logical-slot-id  (\d+)/ ) {    #(\d+)
                		print "Found SlotID: $1\n" ; #if $Debug;
                        &Log_Error ("SlotID failed Should be Slot 2 to 4 was $1") if ($1>45 || $1<42);
                        }
                	}
                }
                &Log_Error ("Show CPLD found: $_ exp $postinfo_XGLC_str") if $postfound ==0;
                #&Log_Error ("POST string: $temp not found") if (! $cpldinfo_XGLC_str_found);

        }
    }
# }



}

#__________________________________________________________________________
   sub Check_XGLC_CPLD_dep { # Check the startup output   Check_XGLC_Diag

#Adding Xglc  5/25/11
       my @cpldinfo_XGLC  = (
"Name  Offset  Value",
"card-type    00      04",
"assy-rev    01      01",
"cpld-code-rev    02      ..",
"bp-logical-slot-id    03      4.",
"bp-system-id    04      03",
"board-reset-reason    05      09",
"cpu0-reset-reason    06      01",
"cpu1-reset-reason    07      F4",
"board-reset    08      F4",
"cpu0->cpu1-reset    09      F4",
"cpu0-watchdog-clear    0A      F4",
"cpu1-watchdog-clear    0B      F4",
"watchdog-timer_settings    0C      3B",
"ixp2800-reset    0E      F4",
"nitrox-reset    0F      F4",
"ixf1110-reset    10      F4",
"tcam-reset    11      F4",
"mgmt-phy-reset    12      00",
"quad-uart-reset    13      F4",
"fic-reset    14      F4",
"pci-0-reset    15      F4",
"pci-1-reset    16      F4",
"cpu0-sys-mgmt-irq-sts    17      18",
"cpu0-sys-mgmt-irq-en    18      05",



);

 #"cpld-code-rev 09",
 #"bp-logical-slot-id 43",

       my $postcount_XGLC = @cpldinfo_XGLC;
       my $postcount = 0;
       my $postfound = 0;
       my $postinfo_XGLC_str = '';
       my $Screen_Data_str = '';
       #@postinfo = (split /\n/, $Buffer);
   #foreach (split /\n/, $Buffer) {
     foreach (@cpldinfo_XGLC) {      #foreach (@Screen_Data)
     	$postinfo_XGLC_str = $_;
            $postfound = 0;
        if (( $postcount <= $postcount_XGLC -1 )) {
            &Log_Error ("Mismatch in CPLD line count") if ( $postcount > $postcount_XGLC -1 ) ;
                foreach (@Screen_Data)  {
                		$Screen_Data_str = $_;
                	   #print " Checking $_ to $postinfo_XGLC_str\n";
                	if (/($postinfo_XGLC_str)/) {
                		print "Found CPLD info: $Screen_Data_str expected: $postinfo_XGLC_str\n" if $Debug;
                         $postfound++;
                         if (/cpld-code-rev    02      (\d+)/ ) {    #(\d+)
                		print "Found CPLD Version: $1\n" ; #if $Debug;
                		&Log_Error ("CPLD Version incorrect") if ($1 ne "09");
                		#if ($1 ne $UUT_Variable_ref[1]->{cpld-code-rev});
                        }
                       if (/bp-logical-slot-id    03      (\d+)/ ) {    #(\d+)
                		print "Found SlotID: $1\n" ; #if $Debug;
                        &Log_Error ("SlotID failed Should be Slot 2 to 4 was $1") if ($1>45 || $1<42);
                        }
                	}
                }
                &Log_Error ("Show CPLD found: $Screen_Data_str exp $postinfo_XGLC_str") if $postfound ==0;
                #&Log_Error ("POST string: $temp not found") if (! $cpldinfo_XGLC_str_found);

        }
    }
# }



}

#______________________________________________________________________________
   sub Check_XGLC_CPLD { # Check the startup output   Check_XGLC_Diag

#Adding Xglc  5/25/11
       my @cpldinfo_XGLC  = (
["Name","Offset","Value"],
["card-type","00","04"],
["assy-rev","01","01"],
["cpld-code-rev","02",".."],
["bp-logical-slot-id","03","4."],
["bp-system-id","04","03"],
["board-reset-reason","05","01"],
["cpu0-reset-reason","06","01"],
["cpu1-reset-reason","07","F4"],
["board-reset","08","F4"],
["cpu0->cpu1-reset","09","F4"],
["cpu0-watchdog-clear","0A","F4"],
["cpu1-watchdog-clear","0B","F4"],
["watchdog-timer_settings","0C","3B"],
["ixp2800-reset","0E","F4"],
["nitrox-reset","0F","F4"],
["ixf1110-reset","10","F4"],
["tcam-reset","11","F4"],
["mgmt-phy-reset","12","00"],
["quad-uart-reset","13","F4"],
["fic-reset","14","F4"],
["pci-0-reset","15","F4"],
["pci-1-reset","16","F4"],
["cpu0-sys-mgmt-irq-sts","17","18"],
["cpu0-sys-mgmt-irq-en","18","00"],
["cpu1-sys-mgmt-irq-sts","19","F4"],
[" led:power","1A","01"],
["led:status","1B","03"],
["led:active/standby","1C","00"],
["i2c-local-enable","1D","01"],
[" i2c-global-enable","1E","00"],
[" IPMI_A/B-enable","1F","01"],
["CPU-boot-state","20","01"],
[" temp-sensor-sts","21","F4"],
[" diag-jumper-present","22","00"],
["ipx-gpio","23","F4"],
[" tcam-clock-en","24","F4"],
[" ipx-serial-port-mux-sel","25","F4"],
[" fic/pmc-present","26","06"],
[" arbitration-sts","27","00"],
[" arbitration-req","28","00"],
["cpu0-sys-mgmt-irq-sts2","29","0C"],
[" cpu0-sys-mgmt-irq-en2","2A","00"],
[" flash-rdndnt-ctl-stat","2B","04"],
[" card-rev-dev-bus-cpld","40","F4"],
[" link-state-led-ctl"," 41","00"],
[" circuit-breaker-trip"," 42","00"],
[" flsh-bnk-rdndnt-remap","43","01"],
[" i2c scl control","44","F4"],
[" npu-dbg-phy-rst","50","00"],


);

 #"cpld-code-rev 09",
 #"bp-logical-slot-id 43",

       my $postcount_XGLC = @cpldinfo_XGLC;
       my $postcount = 0;
       my $postfound = 0;
       my $postinfo_XGLC_str = '';
       my $Screen_Data_str = '';
       my $arrayi = 0;
     for ($arrayi = 0; $arrayi < 50; $arrayi++ ) {
     	$postinfo_XGLC_str = $cpldinfo_XGLC[$arrayi][0];
            $postfound = 0;
        if (( $postcount <= $postcount_XGLC -1 )) {
            &Log_Error ("Mismatch in CPLD line count") if ( $postcount > $postcount_XGLC -1 ) ;
                foreach (split /\n/, $Buffer) { #foreach (@Screen_Data)  {
                		s/  / /g;
                		$Screen_Data_str = $_;
                	   #print " Checking $_ to $Screen_Data_str\n";
                	if (/$cpldinfo_XGLC[$arrayi][0] /) {

                        if (/cpld-code-rev\s+(\d+)\s+(\w+)/ ) {    #(\d+)
                			print "Found CPLD Version: $2\n" ; #if $Debug;
                			&Log_Error ("CPLD Version incorrect") if ($2 ne $firmware_ver_xglc_gbl);
                			#if ($1 ne $UUT_Variable_ref[1]->{cpld-code-rev});
                        	}
                       	elsif (/bp-logical-slot-id\s+(\d+)\s+(\d+)/ ) {    #(\d+)
                			print "Found SlotID: $2\n" ; #if $Debug;
                        	&Log_Error ("SlotID failed Should be Slot 2 to 4 was $2") if ($2>45 || $2<42);
                            $Slot_INST_1_GLC_GBL = 1 if ($2 == 42);
                            $Slot_INST_2_GBL = 1 if ($2 == 43);
                            $Slot_INST_3_GBL = 1 if ($2 == 44);
                            $Slot_INST_4_GBL = 1 if ($2 == 45);
                        	}
                        elsif  (/($cpldinfo_XGLC[$arrayi][2])$/) {
                			print "Found CPLD info: $Screen_Data_str expected: $cpldinfo_XGLC[$arrayi][0] $cpldinfo_XGLC[$arrayi][1] $cpldinfo_XGLC[$arrayi][2]\n" if $Debug;
                         	$postfound++;
                         	}
                        else {
                        s/$Screen_Data_str/  /g;
                        &Log_Error ("CPLD: $Screen_Data_str Exp:$cpldinfo_XGLC[$arrayi][0] $cpldinfo_XGLC[$arrayi][1] $cpldinfo_XGLC[$arrayi][2]");
                        }
                	}
                }

                #&Log_Error ("POST string: $temp not found") if (! $cpldinfo_XGLC_str_found);

        }
    }
# }



}

#______________________________________________________________________________
   sub Check_XGLC_CPLD_Diag { # Check the startup output   Check_XGLC_Diag

#Adding Xglc  5/25/11
       my @cpldinfo_XGLC  = (
["Name","Offset","Value"],
["card-type","00","04"],
["assy-rev","01","01"],
["cpld-code-rev","02",".."],
["bp-logical-slot-id","03","4."],
["bp-system-id","04","03"],
["board-reset-reason","05","01"],
["cpu0-reset-reason","06","01"],
["cpu1-reset-reason","07","F4"],
["board-reset","08","F4"],
["cpu0->cpu1-reset","09","F4"],
["cpu0-watchdog-clear","0A","F4"],
["cpu1-watchdog-clear","0B","F4"],
["watchdog-timer_settings","0C","3B"],
["ixp2800-reset","0E","F4"],
["nitrox-reset","0F","F4"],
["ixf1110-reset","10","F4"],
["tcam-reset","11","F4"],
["mgmt-phy-reset","12","00"],
["quad-uart-reset","13","F4"],
["fic-reset","14","F4"],
["pci-0-reset","15","F4"],
["pci-1-reset","16","F4"],
["cpu0-sys-mgmt-irq-sts","17","18"],
["cpu0-sys-mgmt-irq-en","18","00"],
["cpu1-sys-mgmt-irq-sts","19","F4"],
[" led:power","1A","01"],
["led:status","1B","03"],
["led:active/standby","1C","00"],
["i2c-local-enable","1D","01"],
[" i2c-global-enable","1E","00"],
[" IPMI_A/B-enable","1F","01"],
["CPU-boot-state","20","01"],
[" temp-sensor-sts","21","F4"],
[" diag-jumper-present","22","00"],
["ipx-gpio","23","F4"],
[" tcam-clock-en","24","F4"],
[" ipx-serial-port-mux-sel","25","F4"],
[" fic/pmc-present","26","06"],
[" arbitration-sts","27","00"],
[" arbitration-req","28","00"],
["cpu0-sys-mgmt-irq-sts2","29","0C"],
[" cpu0-sys-mgmt-irq-en2","2A","00"],
[" flash-rdndnt-ctl-stat","2B","04"],
[" card-rev-dev-bus-cpld","40","F4"],
[" link-state-led-ctl"," 41","00"],
[" circuit-breaker-trip"," 42","00"],
[" flsh-bnk-rdndnt-remap","43","01"],
[" i2c scl control","44","F4"],
[" npu-dbg-phy-rst","50","00"],


);

 #"cpld-code-rev 09",
 #"bp-logical-slot-id 43",

       my $postcount_XGLC = @cpldinfo_XGLC;
       my $postcount = 0;
       my $postfound = 0;
       my $postinfo_XGLC_str = '';
       my $Screen_Data_str = '';
       my $arrayi = 0;
     for ($arrayi = 0; $arrayi < 50; $arrayi++ ) {
     	$postinfo_XGLC_str = $cpldinfo_XGLC[$arrayi][0];
            $postfound = 0;
        if (( $postcount <= $postcount_XGLC -1 )) {
            &Log_Error ("Mismatch in CPLD line count") if ( $postcount > $postcount_XGLC -1 ) ;
                foreach (split /\n/, $Buffer) { #foreach (@Screen_Data)  {
                		s/  / /g;
                		$Screen_Data_str = $_;
                	   #print " Checking $_ to $Screen_Data_str\n";
                	if (/$cpldinfo_XGLC[$arrayi][0] /) {

                        if (/cpld-code-rev\s+(\d+)\s+(\w+)/ ) {    #(\d+)
                			print "Found CPLD Version: $2\n" ; #if $Debug;
                			&Log_Error ("CPLD Version incorrect") if ($2 ne $firmware_ver_xglc_gbl);
                			#if ($1 ne $UUT_Variable_ref[1]->{cpld-code-rev});
                        	}
                       	elsif (/bp-logical-slot-id\s+(\d+)\s+(\d+)/ ) {    #(\d+)
                			print "Found SlotID: $2\n" ; #if $Debug;
                        	&Log_Error ("SlotID failed Should be Slot 2 to 4 was $2") if ($2>45 || $2<42);
                        	}
                        elsif  (/($cpldinfo_XGLC[$arrayi][2])$/) {
                			print "Found CPLD info: $Screen_Data_str expected: $cpldinfo_XGLC[$arrayi][0] $cpldinfo_XGLC[$arrayi][1] $cpldinfo_XGLC[$arrayi][2]\n" if $Debug;
                         	$postfound++;
                         	}
                        else {
                        s/$Screen_Data_str/  /g;
                        &Log_Error ("CPLD: $Screen_Data_str Exp:$cpldinfo_XGLC[$arrayi][0] $cpldinfo_XGLC[$arrayi][1] $cpldinfo_XGLC[$arrayi][2]");
                        }
                	}
                }

                #&Log_Error ("POST string: $temp not found") if (! $cpldinfo_XGLC_str_found);

        }
    }
# }



}

#______________________________________________________________________________


sub Check_XGLC_Thermal {    # Called by Screen_Data

    &Print2XLog ("Checking Thermal Values");
    &Print2XLog ("Check_XGLC_Thermal: $Buffer",1) if 1;

    #our %TData = ();

#Stoke> monitor temp
#Temperature INLET value 35 C
#Temperature OUTLET value 58 C
#Temperature NPU0_INTERNAL value 34 C
#Temperature NPU0_EXTERNAL value 37 C
#Temperature NPU1_INTERNAL value 60 C
#Temperature NPU1_EXTERNAL value 56 C
#Temperature GPP0_INTERNAL value 57 C
#Temperature GPP1_EXTERNAL value 70 C

#      >


my @Tempurature = (
# Name, Nom, Low, Hi
["INLET","30", "20", "45"],
["OUTLET","30", "22", "55"],
["NPU0_INTERNAL","30", "20", "50"],
["NPU0_EXTERNAL","30", "22", "80"],
["NPU1_INTERNAL","30", "20", "65"],
["NPU1_EXTERNAL","30", "22", "80"],
["GPP0_INTERNAL","40", "20", "65"],
["GPP1_EXTERNAL	","40", "30", "80"],

);
#DIAG >
    my $arrayi = 0;

    #my $hitemp = 0;
    #my $lowtemp = 0;
    foreach (@Screen_Data) {
    	 $arryi = 0;
    	 #print "Screen $_\n";
         for ($arrayi = 0; $arrayi < 7; $arrayi++ ) {
         		#print "checking count $arrayi $Tempurature[$arrayi][1]\n";
         		#Voltage VCC_2_5V value 2473mv
                if (/Temperature.(\w+).value.(\d+).C/) {
                        #print " Found Tempurature 1 $1 and comparing to $Tempurature[$arrayi][0] \n";
                        if ($Tempurature[$arrayi][0] eq  $1) {
                            # Test Voltage
                            #print "Found $voltage[$arrayi][1]\n";
                            if ($2 <= $Tempurature[$arrayi][3] && $2 >= $Tempurature[$arrayi][2] ) {
                            	&Print2XLog("Tempurature pass $Tempurature[$arrayi][0] was $2 C \nExpected($Tempurature[$arrayi][1] C): $Tempurature[$arrayi][2] C to $Tempurature[$arrayi][3] C",1);
                            } else {
                              &Log_Error ("Tempurature Fail $Tempurature[$arrayi][0] was $2 C \nExpected($Tempurature[$arrayi][1] C): $Tempurature[$arrayi][2] C to $Tempurature[$arrayi][3] C");
                            }
                       }
                }
            #$arrayi++;
          }
	}

}
#__________________________________________________________________________

sub Check_Byteswap_dep { #Check CRC32 agaist previous CRC32 for a match
#     our $crc32_match_gbl = 0;
#our $crc32_str_gbl = "na";
#CRC32 for e8000000 ... e8ffffff ==> 9247a644
    #Check the output of the "rd i2c 9501 U200" command
    $crc32_match_gbl = 1;
    &Print2XLog( "Swap check of: $crc32_str_gbl $1",1);
   foreach (split /\n/, $Buffer) {
         #                 ed000000: ff 00 eb 7e 01 00 00 0f 00 01 14 00 a0 00 98 49
        if ( /^\w+:.(\w+.\w+.\w+.\w+.\w+.\w+.\w+.\w+.\w+.\w+.\w+.\w+.\w+.\w+.\w+.\w+)/ ) {
     			if ($crc32_str_gbl eq $1 ) {
                 $crc32_match_gbl = 0 ;
     			 	&Print2XLog( "Swap Matched: $1");
     			} else {
				$crc32_match_gbl = 1;
     				&Print2XLog( "Swap No Match. Setting crc32_str_gbl to $1",1);
     				$crc32_str_gbl = $1;

     			}
   }
}

}
#_____________________________________________________________________________
sub Check_XGLC_Bench_Links { # Check the startup output   Check_XGLC_Diag



       my $xe0 = "xe0  up    10G FD   SW  No   Forward  TX RX   None   FA    SFI 16356";
       my $xe1 = "xe1  up    10G FD   SW  No   Forward  TX RX   None   FA    SFI 16356";
       my $xe2 = "xe2  up    10G FD   SW  No   Forward  TX RX   None   FA    SFI 16356";
       my $xe3 = "xe3  up    10G FD   SW  No   Forward  TX RX   None   FA    SFI 16356";
if    ($XGLC_1gigSFP==1) {
       $xe0 = "xe0  up     1G FD   SW  No   Forward  TX RX   None   FA   GMII  1518";
       $xe1 = "xe1  up     1G FD   SW  No   Forward  TX RX   None   FA   GMII  1518";
       $xe2 = "xe2  up     1G FD   SW  No   Forward  TX RX   None   FA   GMII  1518";
       $xe3 = "xe3  up     1G FD   SW  No   Forward  TX RX   None   FA   GMII  1518";
}

#Adding Xglc  5/25/11
       my @bench_link_info_XGLC  = (
       "$xe0",
       "$xe1",
       "$xe2",
       "$xe3",
       'xe4  up    10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
       'xe5  up    10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
       'xe6  up    10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
       'xe7  up    10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
       'xe8  up    10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
       'xe9  up    10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
      'xe10  up    10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
      'xe11  up    10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
      'xe12  up    10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
      'xe13  up    10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
      'xe14  down  10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
      'xe15  down  10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
      'xe16  down  10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
      'xe17  down  10G FD   SW  No   Forward  TX RX   None   FA  XGMII 16356',
       'ge0  up     1G FD   SW  No   Forward  TX RX   None   FA   GMII  9600',
       'ge1  up     1G FD   SW  No   Forward  TX RX   None   FA   GMII  9600',
       'ge2  down   1G FD   SW  .*  Forward  TX RX   None   FA   GMII  9600',
       'ge3  down   1G FD   SW  .*  Forward  TX RX   None   FA   GMII  9600',
       'ge4  down   1G FD   SW  Yes  Forward  TX RX   None   FA   GMII  9600',
       'ge5  down   1G FD   SW  Yes  Forward  TX RX   None   FA   GMII  9600',
       'ge6  down   1G FD   SW  Yes  Forward  TX RX   None   FA   GMII  9600',
       'ge7  down   1G FD   SW  Yes  Forward  TX RX   None   FA   GMII  9600',
       'ge8  down   1G FD   SW  Yes  Forward  TX RX   None   FA   GMII  9600',
       'ge9  down   1G FD   SW  Yes  Forward  TX RX   None   FA   GMII  9600',
      'ge10  down   1G FD   SW  Yes  Forward  TX RX   None   FA   GMII  9600',
      'ge11  down   1G FD   SW  Yes  Forward  TX RX   None   FA   GMII  9600'
);


       my $postcount_XGLC = @bench_link_info_XGLC;
       my $postcount = 0;
       #@postinfo = (split /\n/, $Buffer);
       &Print2XLog( "Check Links");
#   foreach (split /\n/, $Buffer) {
     foreach (@bench_link_info_XGLC) {      #foreach (@Screen_Data)
     	$postinfo_XGLC_str = $_;
     	$linkinfo_XGLC_str_found = 0;
     		#print    "$postinfo_XGLC_str\n";
        if (( $postcount <= $postcount_XGLC -1 )) {
            &Log_Error ("Mismatch in Link line count") if ( $postcount > $postcount_XGLC -1 ) ;
                foreach (@Screen_Data)  {
                	if (/$postinfo_XGLC_str/ ) {
                		print "Found Link info: $postinfo_XGLC_str\n" if $Debug;
                    	$linkinfo_XGLC_str_found++
                	}
                }
                &Log_Error ("Bench Link string: $postinfo_XGLC_str = $_ not found") if ($linkinfo_XGLC_str_found == 0);
        }
    }
# }



}

#________________________________________________
sub Detect_SFP_1GIG_dep {


   # &Print2XLog( "Device: 0x50 Offset: 0x6 Data:",1);
   foreach (split /\n/, $Buffer) {
   		#print "Buffer $_\n";
        if ( /Device.*Offset.*0x6.*Data: 0x[1-9]/) { # && $XGLC_1gigSFP_detected_gbl eq 0 && $XGLC_10gigSFP_detected_gbl eq 0) {
					#Device: 0x50 Offset: 0x6 Data: 0x1
     			 	&Print2XLog( "Found 1Gig SFP",1);
     			 	$XGLC_1gigSFP_gbl = 1;
                    $XGLC_1gigSFP_detected_gbl = 1;
     			} else {
     				&Print2XLog( "Not Found 1Gig SFP: $_",1);
     				}
     	if   ($XGLC_1gigSFP_detected_gbl eq 1 && $XGLC_10gigSFP_detected_gbl eq 1)  {
                 &Log_Error ("Found Mixed 1Gig and 10gig SFPs");
     				}

   }
}

 #________________________________________________
   sub Detect_SFP_10GIG_dep  {   #Detect_SFP_10GIG


   # &Print2XLog( "Device: 0x50 Offset: 0x6 Data:",1);
   foreach (split /\n/, $Buffer) {
   		#print "Buffer $_\n";
        if ( /Device.*Offset.*0x3.*Data: 0x[1-9]/) { # && $XGLC_1gigSFP_detected_gbl eq 0 && $XGLC_10gigSFP_detected_gbl eq 0) {
#   			  Device: 0x50 Offset: 0x3 Data: 0x10
     			 	&Print2XLog( "Found 10Gig SFP",1);
     			 	$XGLC_10gigSFP_gbl = 1;
                    $XGLC_10gigSFP_detected_gbl = 1;
     					 } else {
     				&Print2XLog( "Not Found 10Gig SFP: $_",1);
     		 	}
     	if   ($XGLC_1gigSFP_detected_gbl eq 1 && $XGLC_10gigSFP_detected_gbl eq 1)  {
                 &Log_Error ("Found Mixed 1Gig and 10gig SFPs");
     	}
   }
}


#________________________________________________
   sub Get_SFP_HextoASCII  {   #Serial Field
      #AA1202AGA5X
      #AA1202A47A558
   my $hexstr='';
   my $hexchr='';
   my $chrstr='';
   my $chrchr='';
   # &Print2XLog( "Device: 0x50 Offset: 0x6 Data:",1);
   foreach (split /\n/, $Buffer) {
   		#print "Buffer $_\n";
        if ( /Data.*=.0x([\da-fA-F-]{2})/) {
        			#print (" hex data $1 \n" );
					next if ($1 eq '20');  # Space null
					$hexstr= $hexstr  . $1  ;
				   s/($1)/pack('H*',$1)/ge;
				   /Data.*=.0x([\w-])/;
				   #print $1;
				   $chrstr= $chrstr  . $1  ;
     		 	}
   }
   #print $hexstr;
    &Log_Error ("Empty String returned") if ($chrstr eq '');
   &Print2XLog( "Hexstr $hexstr converted to $chrstr");
}
#________________________________________________
  sub Get_SFP  {   #Serial Field
      #AA1202AGA5X
      #AA1202A47A558

 my $hexstr='';
   my $hexchr='';
   my $chrstr='';
   my $chrchr='';
   my $port='';
   my $slot='';
   # &Print2XLog( "Device: 0x50 Offset: 0x6 Data:",1);
   foreach (split /\n/, $Buffer) {
   		#print "Buffer $_\n";
        if ( /slot (\d+) port (\d+)/) {
                    $Slot=$1;
                    $Port=$2;
     		 	}
   }
   &Print2XLog( "Slot $Slot Port $Port");

   $hexstr='';
   $hexchr='';
   $chrstr='';
   $chrchr='';
   # &Print2XLog( "Device: 0x50 Offset: 0x6 Data:",1);
   foreach (split /\n/, $Buffer) {
   		#print "Buffer $_\n";
        if ( /Data.0. = 0x([\da-fA-F-]{1,2})/) {
        			#print (" hex data $1 \n" );
					next if ($1 eq '20');  # Space null
					$hexstr= $hexstr  . $1  ;
				   s/($1)/pack('H*',$1)/ge;
				   /Data.*=.0x([\w-])/;
				   $SFPCount_gbl++ ; #SFP is populated
				   $chrstr= $chrstr  . $1  ;
     		 	}
   }
   #$SFPData{'TYPE'} =  $hexstr ;
   $SFPData_slot_ar[$Slot][$Port]->{'TYPE'}=$hexstr;

    $hexstr='';
   $hexchr='';
   $chrstr='';
   $chrchr='';
   # &Print2XLog( "Device: 0x50 Offset: 0x6 Data:",1);
   foreach (split /\n/, $Buffer) {
   		#print "Buffer $_\n";
        if ( /Data\[(\d+)\] = 0x([\da-fA-F-]{1,2})/) {
        			next if ($1 < 3 | $1 > 10 );#print (" hex data $1 \n" );
       			#print (" hex data $1 \n" );
					next if ($1 eq '20');  # Space null
					#$hexstr= $hexstr  . $2  ;
				   s/($2)/pack('H*',$1)/ge;
				   /Data.*=.0x([\w-])/;
				   #print $1;
				   $chrstr= $chrstr  . $1  ;
     		 	}
   }
   #$$SFPData{'Transcvr'} =  $chrstr ;
   $SFPData_slot_ar[$Slot][$Port]->{'Transcvr'}=$chrstr;
   	if ( $chrstr =~ /00012040c/ ) {    #|00012040c1|100000000"
     			 	&Print2XLog( "Found 1Gig SFP",1);
     			 	#$XGLC_1gigSFP_gbl = 0;
                    #$XGLC_1gigSFP_gbl = 0;
                    $XGLC_1gigSFP_gbl[$Slot][$Port]=1;
                    #$XGLC_10gigLRSFP_gbl = 0;
#                   if ($XGLC_1gigSFP_gbl > 0 && $XGLC_1gigSFP_gbl < $SFPCount_gbl) {
#                     &Log_Error ("Found $XGLC_1gigSFP_gbl $SFPCount_gbl Mixed SFPs Check Slot $Slot Port $Port");
#                    }
                     &Print2XLog( "Found SFP TypeXGLC_1gigSFP_gbl[$Slot][$Port] $XGLC_1gigSFP_gbl[$Slot][$Port]",1);
       } elsif (  $chrstr =~ /00080000/) {
   			 	&Print2XLog( "Found 1Gig Copper SFP",1);
     			 	#$XGLC_1gigSFP_gbl++;
                    #$XGLC_1gigSFP_gbl = 0;
                    $XGLC_1gigCopperSFP_gbl[$Slot][$Port]=1;
                    #$XGLC_10gigLRSFP_gbl = 0;
#                   if ($XGLC_1gigCopperSFP_gbl > 0 && $XGLC_1gigCopperSFP_gbl < $SFPCount_gbl) {
#                     &Log_Error ("Found Mixed $XGLC_1gigCopperSFP_gbl $SFPCount_gbl SFPs Check Slot $Slot Port $Port");
#                    }
                     &Print2XLog( "Found SFP Type XGLC_1gigCopperSFP_gbl $XGLC_1gigCopperSFP_gbl[$Slot][$Port]",1);
       } elsif ($chrstr =~ /100000000/) {
   			 	&Print2XLog( "Found 10Gig SFP",1);
     			 	#$XGLC_1gigSFP_gbl = 0;
                    $XGLC_10gigSFP_gbl[$Slot][$Port]=1;
                    #$XGLC_1gigCopperSFP_gbl = 0;
                    #$XGLC_10gigLRSFP_gbl = 0;
#                    if ($XGLC_10gigSFP_gbl > 0 && $XGLC_10gigSFP_gbl < $SFPCount_gbl) {
#                     &Log_Error ("Found Mixed $XGLC_10gigSFP_gbl $SFPCount_gbl SFPs Check Slot $Slot Port $Port");
#                    }
                       &Print2XLog( "Found SFP Type XGLC_10gigSFP_gbl $XGLC_10gigSFP_gbl[$Slot][$Port]",1);
     	 } elsif ($chrstr =~ /100000001/ || $chrstr =~ /200000000/) {
   			 	&Print2XLog( "Found 10Gig LR SFP",1);
     			 	#$XGLC_1gigSFP_gbl = 0;
                    #$XGLC_10gigSFP_gbl = 0;
                    #$XGLC_1gigCopperSFP_gbl = 0;
                    $XGLC_10gigLRSFP_gbl[$Slot][$Port]=1;
                    $XGLC_10gigSFP_gbl[$Slot][$Port]=1;
#                    if ($XGLC_10gigLRSFP_gbl > 0 && $XGLC_10gigLRSFP_gbl < $SFPCount_gbl) {
#                     &Log_Error ("Found Mixed $XGLC_10gigLRSFP_gbl $SFPCount_gbl SFPs Check Slot $Slot Port $Port");
#                    }
                    &Print2XLog( "Found SFP Type XGLC_10gigLRSFP_gbl $XGLC_10gigLRSFP_gbl[$Slot][$Port]",1);
     				}
       	else {
                &Log_Error ("Unknown SFP $chrstr detected Slot $Slot Port $Port");
                       }
       #	if   (($XGLC_1gigSFP_gbl  + $XGLC_10gigSFP_gbl + $XGLC_10gigLRSFP_gbl + $XGLC_1gigCopperSFP_gbl) > 1)  {
        #         &Log_Error ("Found Mixed SFPs");
     	 #			}

      $hexstr='';
   $hexchr='';
   $chrstr='';
   $chrchr='';
   # &Print2XLog( "Device: 0x50 Offset: 0x6 Data:",1);
   foreach (split /\n/, $Buffer) {
   		#print "Buffer $_\n";
        if ( /Data\[(\d\d)\] = 0x([\da-fA-F-]{2})/) {
        			next if ($1 < 20 | $1 > 35 );#print (" hex data $1 \n" );
					next if ($2 eq '20');  # Space null
					#$hexstr= $hexstr  . $2  ;
				   s/($2)/pack('H*',$1)/ge;
				   /Data.*=.0x([\w-])/;
				   #print $1;
				   $chrstr= $chrstr  . $1  ;
     		 	}
   }
   #$SFPData{'Vendor'} =  $chrstr ;
   $SFPData_slot_ar[$Slot][$Port]->{'Vendor'}=$chrstr;
   $hexstr='';
   $hexchr='';
   $chrstr='';
   $chrchr='';
   foreach (split /\n/, $Buffer) {
   		#print "Buffer $_\n";
          if ( /Data\[(\d\d)\] = 0x([\da-fA-F-]{2})/) {
        			next if ($1 < 40 | $1 > 55 );#print (" hex data $1 \n" );
	     			#print (" hex data $1 \n" );
					next if ($2 eq '20');  # Space null
					#$hexstr= $hexstr  . $1  ;
				   s/($2)/pack('H*',$1)/ge;
				   /Data.*=.0x([\w-])/;
				   #print $1;
				   $chrstr= $chrstr  . $1  ;
     		 	}
   }
   #$SFPData{'ModelNo'} =  $chrstr ;
   $SFPData_slot_ar[$Slot][$Port]->{'ModelNo'}=$chrstr;

   $hexstr='';
   $hexchr='';
   $chrstr='';
   $chrchr='';
   foreach (split /\n/, $Buffer) {
   		#print "Buffer $_\n";
         if ( /Data\[(\d\d)\] = 0x([\da-fA-F-]{2})/) {
        			next if ($1 < 68 | $1 > 83 );#print (" hex data $1 \n" );
	       			#print (" hex data $1 \n" );
					next if ($2 eq '20');  # Space null
					#$hexstr= $hexstr  . $1  ;
				   s/($2)/pack('H*',$1)/ge;
				   /Data.*=.0x([\w-])/;
				   #print $1;
				   $chrstr= $chrstr  . $1  ;
     		 	}
   }

   $SFPData_slot_ar[$Slot][$Port]->{'SerialNo'}=$chrstr;
   $SFPData_slot_ar[$Slot][$Port]->{'PowerdBm'}='';
   &Print2XLog( "SFP Slot $Slot Port $Port $SFPData_slot_ar[$Slot][$Port]",1);
#    if (($TestData{'TID'} eq "DEBUG") || ($TestData{'TID'} eq "SHIP")) {
#    print ("(TestData{'TID'} $TestData{'TID'}\n") if $Debug;
#    GetSFPpower();
#    }
#   #print Dumper(\@SFPData_slot_ar);

   return
}
#_______________________________________________________

sub GetSFPpower {

    my ( $Match, $Exclude ) = @_;

    my $powernumber=0;
    my $answerok;
    my $answer;
    my $Port;
    my $Slot;


     foreach (1..25) {        # Updated for 14 Slot Chassis 1/10/07
         $Slot=$_-1;
        if ( $SFPData_slot_ar[($Slot)][0]->{'TYPE'} ne '') {
        	foreach (0..15) {
        		$Port=$_;
        		if ( $XGLC_1gigCopperSFP_gbl[$Slot][$Port] ne 1
        		&& ( $XGLC_10gigLRSFP_gbl[$Slot][$Port]==1
        		||  $XGLC_10gigSFP_gbl[$Slot][$Port]==1
        		||  $XGLC_1gigSFP_gbl[$Slot][$Port]==1) ) {
  # &Print2XLog( "Device: 0x50 Offset: 0x6 Data:",1);
   #foreach (split /\n/, $Buffer) {
   #		#print "Buffer $_\n";
   #     if ( /slot (\d+) port (\d+)/) {
   #                 $Slot=$1;
   #                 $Port=$2;
     		 	#}
  # }

           #$$Cfg_Ptr = '';
        # get WorkOrder Number
        $answer = "";
       		until ($answer =~ /^[YyNn]/ || $checksfppower_gbl>0 ) {
				print("Check SFP power? (Y/N): ");
       			chomp($answer = <STDIN>);
      			if ($answer =~ /^[Yy]$/){
                   $answer = "Y";
                   print("Checking SFP Power\n");
                   #$Cfg_Ptr = 1;
                   #$PN[$Cfg_Ptr] = $order_number;
                   $checksfppower_gbl=2;
             	} else {
                  $answer = "N";
                  $checksfppower_gbl=1;
                  print("Not Checking SFP Power\n");
  		   		}
    		}
         #$$Cfg_Ptr = '';
        # get WorkOrder Number
        $answerok = "";
        #print("checksfppower_gbl $checksfppower_gbl\n");
        $answer = "";
    	until ($answerok =~ /[yY]/  || $checksfppower_gbl<=1) {
    		$answerok = "";
    		#$checksfppower_gbl++;
    		print("\nOperator Enter SFP dBm for Slot $Slot Port $Port :");
    		chomp($powernumber = <STDIN>);
       		print("Operator: You Entered:  $powernumber \n");
       		until ($answerok =~ /^[YyNnr]/) {
                if ($powernumber =~ /\d+\.\d+/) {
					print("Is this Correct? (Y/N): ");
       				chomp($answer = <STDIN>);
      				if ($answer =~ /^[Yy]$/ || $answer =~ /^$/){
                   		$answerok = "Y";
                   		#$Cfg_Ptr = 1;
                   		#$PN[$Cfg_Ptr] = $order_number;
             		} else {
                   		$answerok = "N";
  		   			}
  		   		} else {
  		   			print ("Incorrect format of dd.dd $powernumber\n");
  		   			$answerok = "r";
  		   		}

    		}
    	}
        $SFPData_slot_ar[$Slot][$Port]->{'PowerdBm'}=$powernumber;
        &Print2XLog (" Slot:$Slot:$Port Power number $powernumber ",1);
        }
    	}
    }
    }
    return ();
}

#__________________________________________________________________________
sub Display_SFP {


   &Print2XLog( Dumper(\@SFPData_slot_ar) ,1);
      &Print_Out_XML_Tag("SFPData_slot_ar");
        &Print_Out( Dumper(\@SFPData_slot_ar));
    &Print_Out_XML_Tag();
}

 #________________________________________________

 # _________________

1;
