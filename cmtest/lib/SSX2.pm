################################################################################
#
# Module:      SSX2.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#			   Joe White ( mailto:joe@stoke.com )
#
# Descr:      Stoke Specific Libray
#
# Version:    (See below) $Id: Stoke2.pm,v 1.31 2012/02/17 17:13:42 joe Exp $
#
# Changes:    modified logging slots
#			 Fixed Check IMC clock in Min < 10
#			Fixed Leading 0 on Part# REvs
#			Added fixed path for parts.cfg
#			Added AX4000 routines
#			Added Check_UUT_Ver and Get_UUT_Varibles
#			Updated for post 4/06 Diags & shasera
#			Addtional Changes for GLC Show mfg
#			Added ORT support, Fixed version check
#			03/19/08 Added Globas for IMC and GLC I2C erase
#			Added OS and QNX clock check functions, changed time from localtime to gmtime
#			Added Get_Port_Counter_Det  8/20/08
#			Mode to Get port counter Detail
#			Adding support for Revions over 9(Convert to Hex) 2/2/09
#			Added Diag Version to Config Output 8/26/09
#			Added Email to Config and Ship test 3/11/10
#			Added Full Config Check and Chassis Test bypass for Full system 4/8/10
#			Added SHOMFG print sub, modified Check_UUT_Last_Status for chassis test
#			XGLC Changes 9/27/11 in progress
#		    our $internal_traffic_test_timeout_GBL = 1100+900;  3/6/12
#			Added Support for Fan2 and PEM2 Chassis test 3/6/13
#		    Check_IMC_0_Standby_Prompt for 6.1/13.1 software
#			Added Support for 4 XGLC, 1gig, Copper,LR SFP per port, SFP power meas
#             #Name Changes to Mavenir  1/29/15

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
my $Ver = '17.4';   #             #Name Changes to Mavenir  1/29/15
my $CVS_Ver = ' [ CVS: $Id: Stoke2.pm,v 1.31 2012/02/17 17:13:42 joe Exp $ ]';
$Version{'SSX2'} = $Ver . $CVS_Ver;
#_____________________________________________________________________________
use Init_HA;
#use MIME::Lite;    # Email capabilites

#_____________________________________________________________________________
sub AssignMac {

    my ( $Match, $Exclude ) = @_;



        my $chassis_serialnumber = "";
        my $chassis_partnumberrev = "";
        my $chassis_5slotpartnum = "00315";
        my $chassis_partnumber = "";
        my $chassis_partnumber_version = "";
        my $chassis_revison = "";
        my $order_number = "";
        my $imc_pcba_temp = "";
        my $Chassis_product_code = "007";

        my $answerok = "N";
        my($answer) = "" ;

        $Cfg_Ptr = '';

        # get imc partnumber
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan Chassis Part number and Revision: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^PN//i;    # remove text
    		$answer =~ s/://g;    # remove text
    		($chassis_partnumber,$chassis_revison) = split(/rev/i,$answer);
    		$chassis_partnumber =~ s/ //g;     # remove spaces
    		$chassis_revison =~ s/ //g;     # remove spaces
    		if (($chassis_partnumber =~ /^[0-9]{5}-[0-9]{2}$/)&&($chassis_revison =~ /^[0-9]{2}$/)) {    # 5-2 digits required
    			if ($chassis_partnumber =~ /^$chassis_5slotpartnum/) {
                    $answerok = "Y";
                    ($imc_pcba_temp,$chassis_partnumber_version) = split("-", $chassis_partnumber);
                     $Cfg_Ptr = 0;
            	} else {
               		print ("Incorect part number entered \n");
            	}
            } else {
            		print ("Incorrect part number length entered\n");
            }

    	}
        &Print2XLog ("Part Number and Revision Entered: $chassis_partnumber Rev $chassis_revison");


        $answerok = "N";
        # get imc Serial number
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan Chassis Serial number: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^SN://;    # remove text
    		$answer =~ s/ //g;     # remove spaces
    		if ($answer =~ /^[0-9]{16}$/) {    # 16 digits required
    			if ($answer =~ /^$Chassis_product_code/) {
                    $answerok = "Y";
                    $chassis_serialnumber = $answer ;
                    $Cfg_Ptr = 0;

            	} else {
               		print ("Incorect product code entered \n");
            	}
            } else {
            		print ("Incorrect Serial number length entered\n");
            }

    	}
         &Print2XLog ("Chassis Serial number entered: $chassis_serialnumber");
         unless ($Cfg_Ptr eq '') {
         	   $SN[$Cfg_Ptr] = $chassis_serialnumber ;
               $PN[$Cfg_Ptr] = "$chassis_partnumber Rev $chassis_revison";
               }

         $Cfg_Ptr = '';
        # get WorkOrder Number
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Enter Stoke Work Order Number: ");
    		chomp($answer = <STDIN>);
       		$order_number = $answer;

       		print("\nOperator: You Entered:  $order_number ");
       		until ($answer =~ /^[YyNn]/) {
       			print("\nIs this Correct? (Y/N): ");
       			chomp($answer = <STDIN>);

      			if ($answer =~ /^[Yy]$/){

                   $answerok = "Y";
                   $Cfg_Ptr = 1;
                   $PN[$Cfg_Ptr] = $order_number;
             	} else {
                   $answerok = "N"
  		   		}
  		   	}

    	}

        &Print2XLog ("Work Order Entered: $order_number ");

                 $Cfg_Ptr = '';
        # get SalesOrder Number
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Enter Customer Sales Order Number: ");
    		chomp($answer = <STDIN>);
       		$order_number = $answer;

       		print("\nOperator: You Entered:  $order_number ");
       		until ($answer =~ /^[YyNn]/) {
       			print("\nIs this Correct? (Y/N): ");
       			chomp($answer = <STDIN>);

      			if ($answer =~ /^[Yy]$/){

                   $answerok = "Y";
                   $Cfg_Ptr = 1;
                   $SN[$Cfg_Ptr] = $order_number;
             	} else {
                   $answerok = "N"
  		   		}
  		   	}

    	}

        &Print2XLog ("Work Order Entered: $order_number ");


        foreach (0..1) {
        	unless ($SN[$_] eq '') {
            &Print_Log (1, "PN[$_] = $PN[$_], SN = $SN[$_]");
        	}
        }
        $Stats{'UUT_ID'} = $chassis_serialnumber;
       	#$Stats{'UUT_ID'} = $imc_fic_sernumber_gbl;
       	#$Stats{'UUT_ID'} = $imz_mmz_sernumber_gbl;
        &Stats::Update_All;


    return ();
}
 #_____________________________________________________________________________
sub AX4000 {

   our $AX4000_avail_GBL = 0;

  my($answer) = "" ;
    until ($answer =~ /^[YyNn]/) {
    		print("\nOperator: Is AX4000 Connected to GLC Slot 1 port 1: Y/N\n");
    		print("Enter Yes or No: ");
    		$answer = <STDIN>;
    		}
	&Print2XLog ("Operator: Is AX4000 Connected to GLC Slot 1 port 1: Y/N: $answer\n");
    if ($answer =~ /^[Nn]/)  {
    	$AX4000_avail_GBL = 0;
    } else {
    	$AX4000_avail_GBL = 1;  # installed
    }
    return ();
}

#__________________________________________________________________________

sub AX4000_Loopback {    #Calls a TCL function to setup the AX4000 in Loopback mode

	if (!($AX4000_avail_GBL)) {return()}; # if AX4000 not used don't do anything

	my $testtype = "LOOPBACK";
    &Print2XLog ("Setting up AX4000 to $testtype traffic");

	#    set axuser [lindex $argv 0]
	# 	set chassis_ip [lindex $argv 1]
	#	set test_duration [lindex $argv 2]
	#	set logfile [lindex $argv 3]
	#	set testtype [lindex $argv 4]
	#	set interface [lindex $argv 5]

    if (system "tclsh $PPath/lib/AX4000.tcl $AX4000_USER $AX4000_IP 60 $Tmp/AX4000.log $testtype 1 > $Tmp/AX4000.txt") {
    print ("Traffic Test Failed\n");
    } else {
    print ("Traffic Test Passed\n");
    };
        print ("Command Line: grep PASSED $Tmp/AX4000.txt \n");
        system "tail" ,"$Tmp/AX4000.txt" ;
       if (system "grep ","PAxSSED" ,"$Tmp/AX4000.txt") {

    	print ("Check Log Traffic Test Passed\n");
    } else {
    	print ("Check Log Traffic Test Failed\n");
    };


}
#__________________________________________________________________________

sub AX4000_Normal {    #Calls a TCL function to setup the AX4000 in Normal mode
	# System must be configured for Snake test
    if (!($AX4000_avail_GBL)) {return()}; # if AX4000 not used don't do anything
	my $testtype = "NORMAL";
	my $testtime = $internal_traffic_test_time_GBL;
    &Print2XLog ("Setting up and running AX4000 with $testtype traffic for $testtime seconds... ");

	#    set axuser [lindex $argv 0]
	# 	set chassis_ip [lindex $argv 1]
	#	set test_duration [lindex $argv 2]
	#	set logfile [lindex $argv 3]
	#	set testtype [lindex $argv 4]
	#	set interface [lindex $argv 5]

    if (system "tclsh $PPath/lib/AX4000.tcl $AX4000_USER $AX4000_IP  $testtime $Tmp/AX4000.log $testtype 1 > $Tmp/AX4000.txt") {
       &Log_Error ("AX4000 Test Not Started/Completed due to System/Traffic failure");
    } else {
    	&Print2XLog  ("Completed AX4000 in $testtype traffic mode\n");

    };
    if (system "grep -q completed $Tmp/AX4000.txt") {
    	&Log_Error ("AX4000 Test did not Complete");
    } else {
    	&Print2XLog  ("AX4000 Test Complete\n");
    };
      if (system "grep -q 'Failed: External' $Tmp/AX4000.txt") {
        &Print2XLog ("AX4000 Traffic Test Passed\n");
    } else {
        &Log_Error ("AX4000 Traffic Test Failed\n");
    };

}
#__________________________________________________________________________
sub AX4000_Monitor {    #Calls a TCL function to setup the AX4000 in Monitor mode,
		#  Routine is started
    if (!($AX4000_avail_GBL)) {return()}; # if AX4000 not used don't do anything
	my $testtype = "MONITOR";
    &Print2XLog ("Setting up AX4000 to $testtype traffic...");
    &Print2XLog ("AX4000 cmd: tclsh $PPath/lib/AX4000.tcl $AX4000_USER $AX4000_IP  5 $Tmp/AX4000.log $testtype 1 > $Tmp/AX4000.tx ",1);

	#    set axuser [lindex $argv 0]
	# 	set chassis_ip [lindex $argv 1]
	#	set test_duration [lindex $argv 2]
	#	set logfile [lindex $argv 3]
	#	set testtype [lindex $argv 4]
	#	set interface [lindex $argv 5]

    if (system "tclsh $PPath/lib/AX4000.tcl $AX4000_USER $AX4000_IP  5 $Tmp/AX4000.log $testtype 1 > $Tmp/AX4000.txt ") {
     &Log_Error ("AX4000 Traffic Monitor Start Failed\n");
    } else {
     &Print2XLog ("AX4000 Traffic Monitor Started\n");
    };

}
#__________________________________________________________________________

sub AX4000_Monitor_Complete {    #Checks the TCL output for Test Complete
    if (!($AX4000_avail_GBL)) {return()}; # if AX4000 not used don't do anything
    &Print2XLog ("Checking AX4000 Monitor Setup Complete");

    if (system "grep -q","Test completed" ,"$Tmp/AX4000.txt") {
    print ("Setup Complete\n");
    } else {
    print ("Setup Not Complete\n");
    };



}
#__________________________________________________________________________
sub Chassis_Program {
      # Still to do 1) Get Slot from CPLD, 2) Cross check Product code to Part number
    	my %chassis = ('');
    	my $File = $PPath . '/uutcfg/' . $Product_gbl . '/parts.cfg';
        #my $File = $PPath . '/uutcfg/parts.cfg'; # Default Development Path
    	my $answer = "";
    	my $answerok = "N";
    	my $pn_answerok = "N";
    	my $sn_answerok = "N";
    	my $partnumber = "";
    	my $partnumber_main = "";
    	my $revision = "";
    	my $version = "";
    	my $product_code = "";
    	my $sernumber = "";
    	#my $Cfg_Ptr = 0;
    	my $Count = 0;
    	my $max_Count = 6; # Max number of part number serial number combinations, 0 will prompt if last #
    	my @Entry_order = ("Chassis","PEM1_RIGHT","PEM2_LEFT","FAN1_RIGHT","FAN2_LEFT","ALARM1_Right");  # For Display
    	my @program_name = ("chassis","pem1","pem2","fan1","fan2","alarm1");  # for setting program name wr i2c tlv xxxx
    	my @PN_temp  = ();
    	my @REV_temp  = ();
    	my @VER_temp  = ();
    	my @SN_temp  = ();
    	my @MAC_temp = ();
    	my @MAC_qty_temp = ();
    	my %seen = ();  # CHECKING FOR DUPLICATES DURING ENTRY
    	my $lastnumber = "x";
    	my $stoke_mac_assign = '00 12 73';
    	my $MAC_Erc  = '';
    	my $MAC_Erc_Msg = '';

           if  (&Read_Data_File ($File)) {
        die "Can\'t read data file $File";
    }

                 # &Check_UUT_Ver();
        print("\nOperator:Scan Serial and Partnumbers starting with Chassis: ");
        # get imc partnumber
       until ($lastnumber =~ /Y/i  or $Count >= $max_Count) {

        $answerok = "N";
        $pn_answerok = "N";
        $sn_answerok = "N";
    		until ($answerok =~ /Y/i) {
    			until ($pn_answerok =~ /Y/i) {
    				print("\nOperator:Scan $Entry_order[$Count] Part number and Revision: ");
    				chomp($answer = <STDIN>);
    				$answer =~ s/^PN//i;    # remove text
    				$answer =~ s/://g;    # remove text
    				($partnumber,$revision) = split(/rev/i,$answer);
    				$revision =~ s/ //g;     # remove spaces
    				$partnumber =~ s/ //g;     # remove spaces
    				if (($partnumber =~ /^[0-9]{5}-[0-9]{2}$/)&&($revision =~ /^[0-9]{2}$/)) {    # 5-2 digits required
    					if ($partnumber =~ /^\d\d\d\d\d-\d\d/) {
    						$PN_temp[$Count] = "$partnumber Rev $revision";
    					    @PN = @PN_temp;

       						&Get_UUT_Variables();

            				if (($PN_temp[$Count] ne '') and (!( $Entry_order[$Count] =~ /$UUT_Variable_ref[$Count]->{I2C_TYPE}/i )) ) {
                     	   		print ("Found $UUT_Variable_ref[$Count]->{I2C_TYPE} where $Entry_order[$Count] should be installed\n");
            				} else {
                       		  $pn_answerok = "Y";
                              $REV_temp[$Count] = sprintf ("00 %02X", $revision);
                              $VER_temp[$Count] = sprintf ("00 %02X", substr($partnumber,6,2));
                            }

            			} else {
               				print ("Incorrect part number entered \n");
            			}
                	} else {
            			print ("Incorrect part number length entered\n");
            		}

              }
              until ($sn_answerok =~ /Y/i) {
    				print("\nOperator:Scan $Entry_order[$Count] Serial Number: ");
    				chomp($answer = <STDIN>);
    				$answer =~ s/^SN//i;    # remove text
    				$answer =~ s/://g;    # remove text
             		$answer =~ s/ //g;     # remove spaces
    				if (($answer =~ /^[0-9]{16}$/) && $partnumber_lookup{substr($answer,0,3)} =~ /^\d\d\d\d\d/ && (! $seen{$answer}) ) { #16 digits required
    					$sn_answerok = "Y";
                    	$sernumber = $answer ;
                    	$SN_temp[$Count] = "$sernumber";  #

                    } else {
               			print ("Incorect/Duplicate Serial number entered $answer \n");
            		}

                 }
                 	#$sernumber =~ /^([0-9]{3})/;
                    $PN_temp[$Count] = "$partnumber Rev $revision";
                   	if ($sn_answerok = "Y" && $pn_answerok = "Y" && ($partnumber_lookup{substr($sernumber,0,3)} eq substr($partnumber,0,5)) ) {
                   	   $answerok = "Y" ;
                   	   $seen{$sernumber}++  # add to hash to check for future duplicates
                   	} else {
                   	  print ("Product Code in SN: $sernumber does not match Part number entered $partnumber \n");
                   	  $sn_answerok = "N" ;    # Ask again
                   	  $pn_answerok = "N" ;
                   	}
    		}
   			foreach (0..25) {
            	unless ($PN_temp[$_] eq '') {
                    	print ("Entered: $Entry_order[$_] $_ PN: $PN_temp[$_]  SN: $SN_temp[$_]\n");
                }
             }
        if ($UUT_Variable_ref[$Count]->{MAC_QTY} ne '') { #Get the MAC address
        	$answerok = "N";
        	$UUT_Variable_ref[$Count]->{MAC_QTY} =~ s/_/ /g;  # replace _ with space
           	until ($answerok =~ /Y/) {
    			print("\nOperator:Scan $Entry_order[$Count] MAC Address: ");
    			chomp($answer = <STDIN>);
    			$answer =~ s/^MAC//i;    # remove text
    			$answer =~ s/ //g;     # remove spaces
    			$answer =~ s/:/ /g;     # sub : for <space>
    			$answer =~ s/\./ /g;     # sub . for <space>
    			$answer =~ s/(.*)/\U$1/;     # Uppercase only
    			if ($answer =~ /^(?:[a-fA-F0-9]{2}\s){5}[a-fA-F0-9]{2}$/) {    # (2 digits 1 space)*5 and (2 digits 1 space) required
    				if ($answer =~ /^$stoke_mac_assign/) {
    					#print ("Checking $SN_temp[$Count],$answer . ' '. $UUT_Variable_ref[$_]->{MAC_QTY}\n");
    				   ($MAC_Erc, $MAC_Erc_Msg) = &Log_MAC ($SN_temp[$Count],$answer . ' '. $UUT_Variable_ref[$_]->{MAC_QTY} . ' ' );
    				   &Log_MAC_Record ($SN_temp[$Count],$answer . ' '. $UUT_Variable_ref[$_]->{MAC_QTY} . ' ' );
    				   	#print (" Found Error code $MAC_Erc , $MAC_Erc_Msg \n");
        				 if ($MAC_Erc > 0) {
        				 	print ("Found $MAC_Erc_Msg\n");
        			   	 } else {
                    		$answerok = "Y";
                    		$MAC_temp[$Count] = $answer;
                    	}
            		} else {
               			print ("Incorect MAC number entered \n");
            		}
            	} else {
            		print ("Incorrect MAC number length entered\n");
            	}
    		}
            print ("Entered:$Entry_order[$Count] $_ PN:$PN_temp[$Count] SN:$SN_temp[$Count] MAC:$MAC_temp[$Count]\n");
          }
        if ($max_Count eq 0) {
    		until ($lastnumber =~ /^[Y,N]/i) {
    			print("\nOperator:Did you enter the last Partnumber Serial number combination?: ");
    			chomp($lastnumber = <STDIN>);
				}
				if ($lastnumber =~ /^[N,n]/) {
           			$Count++;
           			$lastnumber = "x";
           		}
        } else {
        	$Count++;
            print ("Operator: Enter next partnumber/Serial number\n") if ($Count < $max_Count);
           }
        if ($Count eq $max_Count or ($max_Count eq 0 and $lastnumber =~ /y/i)) {
            @PN = @PN_temp;
       		@SN = @SN_temp;

       		&Get_UUT_Variables();
            foreach (0..25) {
            	if (($PN_temp[$_] ne '') and (!( $Entry_order[$_] =~ /$UUT_Variable_ref[$_]->{I2C_TYPE}/i )) ) {
                     print ("Found $UUT_Variable_ref[$_]->{I2C_TYPE} where $Entry_order[$_] should be installed\n");
            		}
       		}
    	}
    }
    		foreach (0..25) {
            	unless ($PN[$_] eq '') {
                    	&Print2XLog ("Entered:$Entry_order[$_] PN: $PN[$_]  SN: $SN[$_]");
                    	$Slot_INST_GBL[$_] = 1;
                }
            }



       @PN = @PN_temp;
       @SN = @SN_temp;
       @MAC =@MAC_temp;
       # Now we can log and build varibles needed for testing
        foreach (0..25) {
        	if (($SN[$_] ne '') && ($MAC eq '')) {
            	&Print_Log (1, "PN[$_] = $PN[$_], SN = $SN[$_]");
        	} elsif (($SN[$_] ne '') && ($MAC ne '')) {
                &Print_Log (1, "PN[$_] = $PN[$_], SN = $SN[$_] MAC = $MAC[$_]");
                ($MAC_Erc, $MAC_Erc_Msg) = &Log_MAC ($SN[$_],$MAC[$_] . ' '. $UUT_Variable_ref[$_]->{MAC_QTY} . ' ' );
                &Log_MAC_Record ($SN[$_],$MAC[$_] . ' '. $UUT_Variable_ref[$_]->{MAC_QTY} . ' ' );
        			&Log_Error ($MAC_Erc_Msg) if ($MAC_Erc > 0);
        	}
        }

        foreach (0..25) {
        	if ($SN_temp[$_] ne '')  {
        	print ("Before SN: $SN_temp[$_] $_\n");

        		# Programming Strings
        		 if (($UUT_Variable_ref[$_]->{LOCAL_TLV_0} ne "NA") && ($UUT_Variable_ref[$_]->{LOCAL_TLV_0} ne "")) {
                	$UUT_Variable[$_]->{LOCAL_TLV_0} = $UUT_Variable_ref[$_]->{LOCAL_TLV_0} . ' ' . $UUT_Variable_ref[$_]->{TLV_MODEL} . ' ' . $VER_temp[$_] . ' ' . $REV_temp[$_];
        			$UUT_Variable[$_]->{LOCAL_TLV_0} =~ s/(\w+\s\w+\s\w+\s)(\w+)(\s\w+\s\w+\s\w+.*)/$1$program_name[$_]$3/;
                 }
                if (($UUT_Variable_ref[$_]->{LOCAL_TLV_7} ne "NA") && ($UUT_Variable_ref[$_]->{LOCAL_TLV_7} ne "")) {
        			$UUT_Variable[$_]->{LOCAL_TLV_7} = $UUT_Variable_ref[$_]->{LOCAL_TLV_7} . ' ' . $SN_temp[$_];
                	$UUT_Variable[$_]->{LOCAL_TLV_7} =~ s/(\w+\s\w+\s\w+\s)(\w+)(\s\w+\s\w+\s\w+.*)/$1$program_name[$_]$3/;
                }
                if (($UUT_Variable_ref[$_]->{LOCAL_TLV_8} ne "NA") && ($MAC_temp[$_] ne '') && ($UUT_Variable_ref[$_]->{LOCAL_TLV_8} ne "")) {
        			$UUT_Variable[$_]->{LOCAL_TLV_8} = $UUT_Variable_ref[$_]->{LOCAL_TLV_8} . ' ' . $MAC_temp[$_]  . ' ' . $UUT_Variable_ref[$_]->{MAC_QTY} . ' ';
                	$UUT_Variable[$_]->{LOCAL_TLV_8} =~ s/(\w+\s\w+\s\w+\s)(\w+)(\s\w+\s\w+\s\w+.*)/$1$program_name[$_]$3/;
                }
                if (($UUT_Variable_ref[$_]->{GLOBAL_TLV_0} ne "NA") && ($UUT_Variable_ref[$_]->{GLOBAL_TLV_0} ne "")) {
        			$UUT_Variable[$_]->{GLOBAL_TLV_0} = $UUT_Variable_ref[$_]->{GLOBAL_TLV_0} . ' ' . $UUT_Variable_ref[$_]->{TLV_MODEL} . ' ' . $VER_temp[$_] . ' ' . $REV_temp[$_];
                	$UUT_Variable[$_]->{GLOBAL_TLV_0} =~ s/(\w+\s\w+\s\w+\s)(\w+)(\s\w+\s\w+\s\w+.*)/$1$program_name[$_]$3/;
                }
                if (($UUT_Variable[$_]->{GLOBAL_TLV_7} ne "NA") && ($UUT_Variable_ref[$_]->{GLOBAL_TLV_7} ne "")) {
        			$UUT_Variable[$_]->{GLOBAL_TLV_7} = $UUT_Variable_ref[$_]->{GLOBAL_TLV_7} . ' ' . $SN_temp[$_];
                	$UUT_Variable[$_]->{GLOBAL_TLV_7} =~ s/(\w+\s\w+\s\w+\s)(\w+)(\s\w+\s\w+\s\w+.*)/$1$program_name[$_]$3/;
                }

                if (($UUT_Variable[$_]->{GLOBAL_TLV_8} ne "NA") && ($MAC_temp[$_] ne '') && ($UUT_Variable_ref[$_]->{GLOBAL_TLV_8} ne "")) {
        			$UUT_Variable[$_]->{GLOBAL_TLV_8} = $UUT_Variable_ref[$_]->{GLOBAL_TLV_8} . ' ' . $MAC_temp[$_]  . ' ' . $UUT_Variable_ref[$_]->{MAC_QTY} . ' ';
                	$UUT_Variable[$_]->{GLOBAL_TLV_8} =~ s/(\w+\s\w+\s\w+\s)(\w+)(\s\w+\s\w+\s\w+.*)/$1$program_name[$_]$3/;
        		}

                #Verify Strings
                $UUT_Variable[$_]->{TLV_0_VERIFY} =  $UUT_Variable_ref[$_]->{TLV_MODEL} . ' '. $VER_temp[$_] . ' ' . $REV_temp[$_]
        			  if (($UUT_Variable_ref[$_]->{TLV_0_VERIFY} ne "") && ($UUT_Variable_ref[$_]->{TLV_0_VERIFY} ne "NA") && ($UUT_Variable_ref[$_]->{TLV_0_VERIFY} eq "CHECK"));

        		$UUT_Variable[$_]->{TLV_7_VERIFY} = $SN_temp[$_]
        			  if (($UUT_Variable_ref[$_]->{TLV_7_VERIFY} ne "") && ($UUT_Variable_ref[$_]->{TLV_7_VERIFY} ne "NA") && ($UUT_Variable_ref[$_]->{TLV_7_VERIFY} eq "CHECK"));

        		$UUT_Variable[$_]->{TLV_8_VERIFY} = $MAC[$_]  . ' ' . $UUT_Variable_ref[$_]->{MAC_QTY}
        			  if (($UUT_Variable_ref[$_]->{TLV_8_VERIFY} ne "") && ($UUT_Variable_ref[$_]->{TLV_8_VERIFY} ne "NA") && ($MAC[$_] ne '') && ($UUT_Variable_ref[$_]->{TLV_8_VERIFY} eq "CHECK"));

        	}
        }



        &Check_UUT_Ver();
        $Stats{'UUT_ID'} = $SN[0];

        &Stats::Update_All;


    return ();
}

#__________________________________________________________________________

sub Chassis_Program_gen2 {
      # Still to do 1) Get Slot from CPLD, 2) Cross check Product code to Part number
    	my %chassis = ('');
    	my $File = $PPath . '/uutcfg/' . $Product_gbl . '/parts.cfg';
        #my $File = $PPath . '/uutcfg/parts.cfg'; # Default Development Path
    	my $answer = "";
    	my $answerok = "N";
    	my $pn_answerok = "N";
    	my $sn_answerok = "N";
    	my $partnumber = "";
    	my $partnumber_main = "";
    	my $revision = "";
    	my $version = "";
    	my $product_code = "";
    	my $sernumber = "";
    	#my $Cfg_Ptr = 0;
    	my $Count = 0;
    	my $max_Count = 6; # Max number of part number serial number combinations, 0 will prompt if last #
    	my @Entry_order = ("Chassis","PEM1_RIGHT","PEM2_LEFT","FAN1_RIGHT","FAN2_LEFT","ALARM1_Right");  # For Display
    	my @program_name = ("chassis","pem1","pem2","fan1","fan2","alarm1");  # for setting program name wr i2c tlv xxxx
    	my @PN_temp  = ();
    	my @REV_temp  = ();
    	my @VER_temp  = ();
    	my @SN_temp  = ();
    	my @MAC_temp = ();
    	my @MAC_qty_temp = ();
    	my %seen = ();  # CHECKING FOR DUPLICATES DURING ENTRY
    	my $lastnumber = "x";
    	my $stoke_mac_assign = '00 12 73';
    	my $MAC_Erc  = '';
    	my $MAC_Erc_Msg = '';

           if  (&Read_Data_File ($File)) {
        die "Can\'t read data file $File";
    }

                 # &Check_UUT_Ver();
        print("\nOperator:Scan Serial and Partnumbers starting with Chassis: ");
        # get imc partnumber
       until ($lastnumber =~ /Y/i  or $Count >= $max_Count) {

        $answerok = "N";
        $pn_answerok = "N";
        $sn_answerok = "N";
    		until ($answerok =~ /Y/i) {
    			until ($pn_answerok =~ /Y/i) {
    				print("\nOperator:Scan $Entry_order[$Count] Part number and Revision: ");
    				chomp($answer = <STDIN>);
    				$answer =~ s/^PN//i;    # remove text
    				$answer =~ s/://g;    # remove text
    				($partnumber,$revision) = split(/rev/i,$answer);
    				$revision =~ s/ //g;     # remove spaces
    				$partnumber =~ s/ //g;     # remove spaces
    				if (($partnumber =~ /^[0-9]{5}-[0-9]{2}$/)&&($revision =~ /^[0-9]{2}$/)) {    # 5-2 digits required
    					if ($partnumber =~ /^\d\d\d\d\d-\d\d/) {
    						$PN_temp[$Count] = "$partnumber Rev $revision";
    					    @PN = @PN_temp;

       						&Get_UUT_Variables();

            				if (($PN_temp[$Count] ne '') and (!( $Entry_order[$Count] =~ /$UUT_Variable_ref[$Count]->{I2C_TYPE}/i )) ) {
                     	   		print ("Found $UUT_Variable_ref[$Count]->{I2C_TYPE} where $Entry_order[$Count] should be installed\n");
            				} else {
                       		  $pn_answerok = "Y";
                              $REV_temp[$Count] = sprintf ("00 %02X", $revision);
                              $VER_temp[$Count] = sprintf ("00 %02X", substr($partnumber,6,2));
                            }

            			} else {
               				print ("Incorrect part number entered \n");
            			}
                	} else {
            			print ("Incorrect part number length entered\n");
            		}

              }
              until ($sn_answerok =~ /Y/i) {
    				print("\nOperator:Scan $Entry_order[$Count] Serial Number: ");
    				chomp($answer = <STDIN>);
    				$answer =~ s/^SN//i;    # remove text
    				$answer =~ s/://g;    # remove text
             		$answer =~ s/ //g;     # remove spaces
    				if (($answer =~ /^[0-9]{16}$/) && $partnumber_lookup{substr($answer,0,3)} =~ /^\d\d\d\d\d/ && (! $seen{$answer}) ) { #16 digits required
    					$sn_answerok = "Y";
                    	$sernumber = $answer ;
                    	$SN_temp[$Count] = "$sernumber";  #

                    } else {
               			print ("Incorect/Duplicate Serial number entered $answer \n");
            		}

                 }
                 	#$sernumber =~ /^([0-9]{3})/;
                    $PN_temp[$Count] = "$partnumber Rev $revision";
                   	if ($sn_answerok = "Y" && $pn_answerok = "Y" && ($partnumber_lookup{substr($sernumber,0,3)} eq substr($partnumber,0,5)) ) {
                   	   $answerok = "Y" ;
                   	   $seen{$sernumber}++  # add to hash to check for future duplicates
                   	} else {
                   	  print ("Product Code in SN: $sernumber does not match Part number entered $partnumber \n");
                   	  $sn_answerok = "N" ;    # Ask again
                   	  $pn_answerok = "N" ;
                   	}
    		}
   			foreach (0..25) {
            	unless ($PN_temp[$_] eq '') {
                    	print ("Entered: $Entry_order[$_] $_ PN: $PN_temp[$_]  SN: $SN_temp[$_]\n");
                }
             }
        if ($UUT_Variable_ref[$Count]->{MAC_QTY} ne '') { #Get the MAC address
        	$answerok = "N";
        	$UUT_Variable_ref[$Count]->{MAC_QTY} =~ s/_/ /g;  # replace _ with space
           	until ($answerok =~ /Y/) {
    			print("\nOperator:Scan $Entry_order[$Count] MAC Address: ");
    			chomp($answer = <STDIN>);
    			$answer =~ s/^MAC//i;    # remove text
    			$answer =~ s/ //g;     # remove spaces
    			$answer =~ s/:/ /g;     # sub : for <space>
    			$answer =~ s/\./ /g;     # sub . for <space>
    			$answer =~ s/(.*)/\U$1/;     # Uppercase only
    			if ($answer =~ /^(?:[a-fA-F0-9]{2}\s){5}[a-fA-F0-9]{2}$/) {    # (2 digits 1 space)*5 and (2 digits 1 space) required
    				if ($answer =~ /^$stoke_mac_assign/) {
    					#print ("Checking $SN_temp[$Count],$answer . ' '. $UUT_Variable_ref[$_]->{MAC_QTY}\n");
    				   ($MAC_Erc, $MAC_Erc_Msg) = &Log_MAC ($SN_temp[$Count],$answer . ' '. $UUT_Variable_ref[$_]->{MAC_QTY} . ' ' );
    				   &Log_MAC_Record ($SN_temp[$Count],$answer . ' '. $UUT_Variable_ref[$_]->{MAC_QTY} . ' ' );
    				   	#print (" Found Error code $MAC_Erc , $MAC_Erc_Msg \n");
        				 if ($MAC_Erc > 0) {
        				 	print ("Found $MAC_Erc_Msg\n");
        			   	 } else {
                    		$answerok = "Y";
                    		$MAC_temp[$Count] = $answer;
                    	}
            		} else {
               			print ("Incorect MAC number entered \n");
            		}
            	} else {
            		print ("Incorrect MAC number length entered\n");
            	}
    		}
            print ("Entered:$Entry_order[$Count] $_ PN:$PN_temp[$Count] SN:$SN_temp[$Count] MAC:$MAC_temp[$Count]\n");
          }
        if ($max_Count eq 0) {
    		until ($lastnumber =~ /^[Y,N]/i) {
    			print("\nOperator:Did you enter the last Partnumber Serial number combination?: ");
    			chomp($lastnumber = <STDIN>);
				}
				if ($lastnumber =~ /^[N,n]/) {
           			$Count++;
           			$lastnumber = "x";
           		}
        } else {
        	$Count++;
            print ("Operator: Enter next partnumber/Serial number\n") if ($Count < $max_Count);
           }
        if ($Count eq $max_Count or ($max_Count eq 0 and $lastnumber =~ /y/i)) {
            @PN = @PN_temp;
       		@SN = @SN_temp;

       		&Get_UUT_Variables();
            foreach (0..25) {
            	if (($PN_temp[$_] ne '') and (!( $Entry_order[$_] =~ /$UUT_Variable_ref[$_]->{I2C_TYPE}/i )) ) {
                     print ("Found $UUT_Variable_ref[$_]->{I2C_TYPE} where $Entry_order[$_] should be installed\n");
            		}
       		}
    	}
    }
    		foreach (0..25) {
            	unless ($PN[$_] eq '') {
                    	&Print2XLog ("Entered:$Entry_order[$_] PN: $PN[$_]  SN: $SN[$_]");
                    	$Slot_INST_GBL[$_] = 1;
                }
            }



       @PN = @PN_temp;
       @SN = @SN_temp;
       @MAC =@MAC_temp;
       # Now we can log and build varibles needed for testing
        foreach (0..25) {
        	if (($SN[$_] ne '') && ($MAC eq '')) {
            	&Print_Log (1, "PN[$_] = $PN[$_], SN = $SN[$_]");
        	} elsif (($SN[$_] ne '') && ($MAC ne '')) {
                &Print_Log (1, "PN[$_] = $PN[$_], SN = $SN[$_] MAC = $MAC[$_]");
                ($MAC_Erc, $MAC_Erc_Msg) = &Log_MAC ($SN[$_],$MAC[$_] . ' '. $UUT_Variable_ref[$_]->{MAC_QTY} . ' ' );
                &Log_MAC_Record ($SN[$_],$MAC[$_] . ' '. $UUT_Variable_ref[$_]->{MAC_QTY} . ' ' );
        			&Log_Error ($MAC_Erc_Msg) if ($MAC_Erc > 0);
        	}
        }

        foreach (0..25) {
        	if ($SN_temp[$_] ne '')  {
        	print ("Before SN: $SN_temp[$_] $_\n");

        		# Programming Strings
        		 if (($UUT_Variable_ref[$_]->{LOCAL_TLV_0} ne "NA") && ($UUT_Variable_ref[$_]->{LOCAL_TLV_0} ne "")) {
                	$UUT_Variable[$_]->{LOCAL_TLV_0} = $UUT_Variable_ref[$_]->{LOCAL_TLV_0} . ' ' . $UUT_Variable_ref[$_]->{TLV_MODEL} . ' ' . $VER_temp[$_] . ' ' . $REV_temp[$_];
        			$UUT_Variable[$_]->{LOCAL_TLV_0} =~ s/(\w+\s\w+\s\w+\s)(\w+)(\s\w+\s\w+\s\w+.*)/$1$program_name[$_]$3/;
                 }
                if (($UUT_Variable_ref[$_]->{LOCAL_TLV_7} ne "NA") && ($UUT_Variable_ref[$_]->{LOCAL_TLV_7} ne "")) {
        			$UUT_Variable[$_]->{LOCAL_TLV_7} = $UUT_Variable_ref[$_]->{LOCAL_TLV_7} . ' ' . $SN_temp[$_];
                	$UUT_Variable[$_]->{LOCAL_TLV_7} =~ s/(\w+\s\w+\s\w+\s)(\w+)(\s\w+\s\w+\s\w+.*)/$1$program_name[$_]$3/;
                }
                if (($UUT_Variable_ref[$_]->{LOCAL_TLV_8} ne "NA") && ($MAC_temp[$_] ne '') && ($UUT_Variable_ref[$_]->{LOCAL_TLV_8} ne "")) {
        			$UUT_Variable[$_]->{LOCAL_TLV_8} = $UUT_Variable_ref[$_]->{LOCAL_TLV_8} . ' ' . $MAC_temp[$_]  . ' ' . $UUT_Variable_ref[$_]->{MAC_QTY} . ' ';
                	$UUT_Variable[$_]->{LOCAL_TLV_8} =~ s/(\w+\s\w+\s\w+\s)(\w+)(\s\w+\s\w+\s\w+.*)/$1$program_name[$_]$3/;
                }
                if (($UUT_Variable_ref[$_]->{GLOBAL_TLV_0} ne "NA") && ($UUT_Variable_ref[$_]->{GLOBAL_TLV_0} ne "")) {
        			$UUT_Variable[$_]->{GLOBAL_TLV_0} = $UUT_Variable_ref[$_]->{GLOBAL_TLV_0} . ' ' . $UUT_Variable_ref[$_]->{TLV_MODEL} . ' ' . $VER_temp[$_] . ' ' . $REV_temp[$_];
                	$UUT_Variable[$_]->{GLOBAL_TLV_0} =~ s/(\w+\s\w+\s\w+\s)(\w+)(\s\w+\s\w+\s\w+.*)/$1$program_name[$_]$3/;
                }
                if (($UUT_Variable[$_]->{GLOBAL_TLV_7} ne "NA") && ($UUT_Variable_ref[$_]->{GLOBAL_TLV_7} ne "")) {
        			$UUT_Variable[$_]->{GLOBAL_TLV_7} = $UUT_Variable_ref[$_]->{GLOBAL_TLV_7} . ' ' . $SN_temp[$_];
                	$UUT_Variable[$_]->{GLOBAL_TLV_7} =~ s/(\w+\s\w+\s\w+\s)(\w+)(\s\w+\s\w+\s\w+.*)/$1$program_name[$_]$3/;
                }

                if (($UUT_Variable[$_]->{GLOBAL_TLV_8} ne "NA") && ($MAC_temp[$_] ne '') && ($UUT_Variable_ref[$_]->{GLOBAL_TLV_8} ne "")) {
        			$UUT_Variable[$_]->{GLOBAL_TLV_8} = $UUT_Variable_ref[$_]->{GLOBAL_TLV_8} . ' ' . $MAC_temp[$_]  . ' ' . $UUT_Variable_ref[$_]->{MAC_QTY} . ' ';
                	$UUT_Variable[$_]->{GLOBAL_TLV_8} =~ s/(\w+\s\w+\s\w+\s)(\w+)(\s\w+\s\w+\s\w+.*)/$1$program_name[$_]$3/;
        		}

                #Verify Strings
                $UUT_Variable[$_]->{TLV_0_VERIFY} =  $UUT_Variable_ref[$_]->{TLV_MODEL} . ' '. $VER_temp[$_] . ' ' . $REV_temp[$_]
        			  if (($UUT_Variable_ref[$_]->{TLV_0_VERIFY} ne "") && ($UUT_Variable_ref[$_]->{TLV_0_VERIFY} ne "NA") && ($UUT_Variable_ref[$_]->{TLV_0_VERIFY} eq "CHECK"));

        		$UUT_Variable[$_]->{TLV_7_VERIFY} = $SN_temp[$_]
        			  if (($UUT_Variable_ref[$_]->{TLV_7_VERIFY} ne "") && ($UUT_Variable_ref[$_]->{TLV_7_VERIFY} ne "NA") && ($UUT_Variable_ref[$_]->{TLV_7_VERIFY} eq "CHECK"));

        		$UUT_Variable[$_]->{TLV_8_VERIFY} = $MAC[$_]  . ' ' . $UUT_Variable_ref[$_]->{MAC_QTY}
        			  if (($UUT_Variable_ref[$_]->{TLV_8_VERIFY} ne "") && ($UUT_Variable_ref[$_]->{TLV_8_VERIFY} ne "NA") && ($MAC[$_] ne '') && ($UUT_Variable_ref[$_]->{TLV_8_VERIFY} eq "CHECK"));

        	}
        }



        &Check_UUT_Ver();
        $Stats{'UUT_ID'} = $SN[0];

        &Stats::Update_All;


    return ();
}

#__________________________________________________________________________
sub Check_Chassis_FRU_TEST {
                # TLV 99 in IMC U67 EEprom     /P20_NOT_INSTALLED/  ||
  foreach (split /\n/, $Buffer) {
        if (/P20_NOT_INSTALLED/  || /50.32.30.5F.4E.4F.54.5F.49.4E.53.54.41.4C.4C.45/) {
             $P20_NOT_INSTALLED_GBL = 1;
             $P20_INSTALLED_GBL = 0;
              &Print_Log ("Chassis FRU test detected");
              print "Chassis FRU test detected\n";
        }

	}
	 return ();
}
#__________________________________________________________________________
sub Check_Chassis_TACH {
	my ( $command) = @_;

    print "Checking tach\n" if $Debug;
    my $Fan = 0;
    my $FanAB = 0;
    my $tach = 0;
    my $tach_str = '';
    my $i=0;
  foreach (split /\n/, $Buffer) {
        if ( /^\s?([\da-fA-F][\da-fA-F])$/) {
        	$i++;
        	$tach_str = $1;
        	$tach = hex $1;
        	print "Found tach of $1\n" if $Debug;
    		if ($command =~ /Check_Chassis_TACH_FAN_(\d+)_A_FAN_A_OFF_FAN_B_ON_LOW/) {   # ADM 70
    				if ($tach ne hex $UUT_Variable_ref[$1]->{tach_off}) {
               			&Log_Error("Fan $1 Fan A OFF B on LOW, Fan A failed to be off, exp: $UUT_Variable_ref[$1]->{tach_off} actual 0x$tach_str");
               		} else {
                     	&Print2XLog ("Fan $1 Fan A OFF B on LOW, Fan A exp: $UUT_Variable_ref[$1]->{tach_off} actual 0x$tach_str",1);
                    }
               }
    	    elsif ($command =~ /Check_Chassis_TACH_FAN_(\d+)_B_FAN_A_OFF_FAN_B_ON_LOW/) {   # ADM 71
    				if (($tach < hex $UUT_Variable_ref[$1]->{B_only_tach_ls_low_limit}) ||
    					($tach > hex $UUT_Variable_ref[$1]->{B_only_tach_ls_high_limit})) {
    					my $hex_high = hex $UUT_Variable_ref[$1]->{B_only_tach_ls_high_limit};
    					my $hex_low = hex $UUT_Variable_ref[$1]->{B_only_tach_ls_low_limit};
               			&Log_Error("Fan $1 Fan A OFF B on LOW, Fan B failed exp: $UUT_Variable_ref[$1]->{B_only_tach_ls_low_limit} to $UUT_Variable_ref[$1]->{B_only_tach_ls_high_limit} actual 0x$tach_str");
              		} else {
               		    &Print2XLog ("Fan $1 Fan A OFF B on LOW, Fan B exp: $UUT_Variable_ref[$1]->{B_only_tach_ls_low_limit} to $UUT_Variable_ref[$1]->{B_only_tach_ls_high_limit} actual 0x$tach_str",1);
               		}
    		}
    		elsif ($command =~ /Check_Chassis_TACH_FAN_(\d+)_A_FAN_A_OFF_FAN_B_ON_HIGH/) {   # ADM 70
    				if ($tach ne hex $UUT_Variable_ref[$1]->{tach_off}) {
               			&Log_Error("Fan $1 Fan A OFF B on HIGH, Fan A failed to be off exp: $UUT_Variable_ref[$1]->{tach_off} actual 0x$tach_str");
               		}else {
               		    &Print2XLog ("Fan $1 Fan A OFF B on HIGH, Fan A exp: $UUT_Variable_ref[$1]->{tach_off} actual 0x$tach_str",1);
               		}
    		}
    	    elsif ($command =~ /Check_Chassis_TACH_FAN_(\d+)_B_FAN_A_OFF_FAN_B_ON_HIGH/) {   # ADM 71
    				if (($tach < hex $UUT_Variable_ref[$1]->{B_only_tach_hs_low_limit}) ||
    					($tach > hex $UUT_Variable_ref[$1]->{B_only_tach_hs_high_limit})) {
               			&Log_Error("Fan $1 Fan A OFF B on HIGH, Fan B failed, exp: $UUT_Variable_ref[$1]->{B_only_tach_hs_low_limit} to $UUT_Variable_ref[$1]->{B_only_tach_hs_high_limit} actual 0x$tach_str");
					}else {
               		    &Print2XLog ("Fan $1 Fan A OFF B on HIGH, Fan B exp: $UUT_Variable_ref[$1]->{B_only_tach_hs_low_limit} to $UUT_Variable_ref[$1]->{B_only_tach_hs_high_limit} actual 0x$tach_str",1);
               		}

    		}
    	    elsif ($command =~ /Check_Chassis_TACH_FAN_(\d+)_A_FAN_A_ON_FAN_B_ON_LOW/) {   # ADM 71
    				if (($tach < hex $UUT_Variable_ref[$1]->{Fans_A_tach_ls_low_limit}) ||
    					($tach > hex $UUT_Variable_ref[$1]->{Fans_A_tach_ls_high_limit})) {
               			&Log_Error("Fan $1 Both fans on LOW, Fan A failed, exp: $UUT_Variable_ref[$1]->{Fans_A_tach_ls_low_limit} to $UUT_Variable_ref[$1]->{Fans_A_tach_ls_high_limit} actual 0x$tach_str");
					}else {
               		    &Print2XLog ("Fan $1 Both fans on LOW, Fan A exp: $UUT_Variable_ref[$1]->{Fans_A_tach_ls_low_limit} to $UUT_Variable_ref[$1]->{Fans_A_tach_ls_high_limit} actual 0x$tach_str",1);
               		}
    		}
    	    elsif ($command =~ /Check_Chassis_TACH_FAN_(\d+)_B_FAN_A_ON_FAN_B_ON_LOW/) {   # ADM 71
    				if (($tach < hex $UUT_Variable_ref[$1]->{Fans_B_tach_ls_low_limit}) ||
    					($tach > hex $UUT_Variable_ref[$1]->{Fans_B_tach_ls_high_limit})) {
               			&Log_Error("Fan $1 Both fans on LOW, Fan B failed, exp: $UUT_Variable_ref[$1]->{Fans_B_tach_ls_low_limit} to $UUT_Variable_ref[$1]->{Fans_B_tach_ls_high_limit} actual 0x$tach_str");
					}else {
               		    &Print2XLog ("Fan $1 Both fans on LOW, Fan B exp: $UUT_Variable_ref[$1]->{Fans_B_tach_ls_low_limit} to $UUT_Variable_ref[$1]->{Fans_B_tach_ls_high_limit} actual 0x$tach_str",1);
               		}
    		}
    	    elsif ($command =~ /Check_Chassis_TACH_FAN_(\d+)_A_FAN_A_ON_FAN_B_ON_HIGH/) {   # ADM 71
    			    if (($tach < hex $UUT_Variable_ref[$1]->{Fans_A_tach_hs_low_limit}) ||
    					($tach > hex $UUT_Variable_ref[$1]->{Fans_A_tach_hs_high_limit})) {
               			&Log_Error("Fan $1 Both fans on HIGH, Fan A failed, exp: $UUT_Variable_ref[$1]->{Fans_A_tach_hs_low_limit} to $UUT_Variable_ref[$1]->{Fans_A_tach_hs_high_limit} actual 0x$tach_str");
					}else {
               		    &Print2XLog ("Fan $1 Both fans on HIGH, Fan A  exp: $UUT_Variable_ref[$1]->{Fans_A_tach_hs_low_limit} to $UUT_Variable_ref[$1]->{Fans_A_tach_hs_high_limit} actual 0x$tach_str",1);
               		}
    		}
    	    elsif ($command =~ /Check_Chassis_TACH_FAN_(\d+)_B_FAN_A_ON_FAN_B_ON_HIGH/) {   # ADM 71
    				if (($tach < hex $UUT_Variable_ref[$1]->{Fans_B_tach_hs_low_limit}) ||
    					($tach > hex $UUT_Variable_ref[$1]->{Fans_B_tach_hs_high_limit})) {
               			&Log_Error("Fan $1 Both fans on HIGH, Fan B failed, exp: $UUT_Variable_ref[$1]->{Fans_B_tach_hs_low_limit} to $UUT_Variable_ref[$1]->{Fans_B_tach_hs_high_limit} actual 0x$tach_str");
					}else {
               		    &Print2XLog ("Fan $1 Both fans on HIGH, Fan B exp: $UUT_Variable_ref[$1]->{Fans_B_tach_hs_low_limit} to $UUT_Variable_ref[$1]->{Fans_B_tach_hs_high_limit} actual 0x$tach_str",1);
               		}
    		}
   	    	elsif ($command =~ /Check_Chassis_TACH_FAN2_(\d+)_LOW/) {   #Check_Chassis_TACH_FAN2_1_HIGH
    				if (($tach < hex $UUT_Variable_ref[$1]->{Fan_1_tach_ls_low_limit}) ||
    					($tach > hex $UUT_Variable_ref[$1]->{Fan_1_tach_ls_high_limit})) {
               			&Log_Error("Fan $1 Low, failed, exp: $UUT_Variable_ref[$1]->{Fan_1_tach_ls_low_limit} to $UUT_Variable_ref[$1]->{Fan_1_tach_ls_high_limit} actual 0x$tach_str");
					}else {
               		    &Print2XLog ("Fan $1 Low, exp: $UUT_Variable_ref[$1]->{Fan_1_tach_ls_low_limit} to $UUT_Variable_ref[$1]->{Fan_1_tach_ls_high_limit} actual 0x$tach_str");
               		}
    		}
   	    	elsif ($command =~ /Check_Chassis_TACH_FAN2_(\d+)_HIGH/) {   #Check_Chassis_TACH_FAN2_1_HIGH
    				if (($tach < hex $UUT_Variable_ref[$1]->{Fan_1_tach_hs_low_limit}) ||
    					($tach > hex $UUT_Variable_ref[$1]->{Fan_1_tach_hs_high_limit})) {
               			&Log_Error("Fan $1 HIGH, failed, exp: $UUT_Variable_ref[$1]->{Fan_1_tach_hs_low_limit} to $UUT_Variable_ref[$1]->{Fan_1_tach_hs_high_limit} actual 0x$tach_str");
  					}else {
               		    &Print2XLog ("Fan $1 HIGH, exp: $UUT_Variable_ref[$1]->{Fan_1_tach_hs_low_limit} to $UUT_Variable_ref[$1]->{Fan_1_tach_hs_high_limit} actual 0x$tach_str");
               		}
    		}
            else {
            	&Log_Error("Failed to find a matching TACH command in Check_Chassis_TACH($command)");
            }
        }
    }
    &Log_Error("Failed to find a TACH ouput Check_Chassis_TACH($command): @Buffer") if $i eq 0;
    return ();
}

#__________________________________________________________________________

sub Check_IMC_Clock {    # Called by Screen_Data

    &Print2XLog ("Checking Clock after 5 Seconds");
    &Print2XLog ("Check_IMC_Clock: $Buffer",1) if 1;

    my $TimeData = 0;

    # TUE, 12/6/2005, 9:09:05
     foreach ( split /\n/, $Buffer) {
         #THU, 4/3/2008, 22:09:05
        if (/\w+,\s\d+\/\d+\/\d+,\s\d+:\d+:(\d+)/i) {  #Just grab the seconds if (/$sysclock_nosec_padmin_glb:(\w+)/i) {  #Just grab the seconds
            $TimeData = $1;
            &Print2XLog ("Clock after 5 Seconds = $TimeData", 1);
        }
    }
         if ($TimeData < 3 or $TimeData > 6) {# IF clock seconds are not 4 or 5
              &Log_Error ("Time Data Seconds: \"$_\"  = $TimeData  Failed out of range");
        }


}
#__________________________________________________________________________

sub Check_IMC_Clock_OS {    # Called by Screen_Data

    #&Print2XLog ("Checking Clock after 5 Seconds");
    &Print2XLog ("Check_IMC_Clock: $Buffer",1) if 1;


      my $month = ('JAN','FEB','MAR','APR','MAY','JUN','JUL','AUG','SEP','OCT','NOV','DEC') [ (gmtime)[4] ];
     my $today = ('SUN','MON','TUE','WED','THU','FRI','SAT')[ (gmtime)[6] ];
     my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = gmtime(time);
     #my $epochtime = time;
     #print $epochtime;
     $mon++;    # Base [0] to month
     $year = 1900 + $year;
#     my $minm1 = $min-1;
#     my $minp1 = $min+1;
#     my $hourm1 = $hour-1;
#     my $hourp1 = $hour+1;

    # TUE, 12/6/2005, 9:09:05
     foreach ( split /\n/, $Buffer) {
        #Wed Apr 02 2008 09:58:00 UTC
        if (/^(\w+)\s(\w+)\s(\d+)\s(\d+)\s(\d+):(\d+):/) {
            &Print2XLog ("Found Clock time = $_");
            my $today_check = $1;
            my $month_check = $2;
            my $mday_check = $3;
            my $year_check = $4;
            my $hour_check = $5;
            my $min_check = $6;
            &Log_Error ("Failed: Day Mismatch: System \"$today_check\" , Expected: $today") if $today_check !~ /$today/i;
            &Log_Error ("Failed: Month Mismatch: System \"$month_check\" , Expected: $month") if $month_check !~ /$month/i;
            &Log_Error ("Failed: Day Mismatch: System \"$mday_check\" , Expected: $mday") if $mday_check !~ /$mday/i;
            &Log_Error ("Failed: Year Mismatch: System \"$year_check\" , Expected: $year") if $year_check  !~ /$year/i;
            #&Log_Error ("Failed: Hour Mismatch: System \"$hour_check\" , Expected: $hour") if $hour_check !~ /$hour/i;
            #&Log_Error ("Failed: Minute Mismatch: System \"$min_check\" , Expected: $min") if $min_check  !~ /$min/i;
        }
    }


}
#__________________________________________________________________________

sub Check_IMC_Clock_QNX {    # Called by Screen_Data

    #&Print2XLog ("Checking Clock after 5 Seconds");
    &Print2XLog ("Check_IMC_Clock: $Buffer",1) if 1;
    my $epochtime = time;
    my $timevari=60;

#      my $month = ('JAN','FEB','MAR','APR','MAY','JUN','JUL','AUG','SEP','OCT','NOV','DEC') [ (gmtime)[4] ];
#     my $today = ('SUN','MON','TUE','WED','THU','FRI','SAT')[ (gmtime)[6] ];
#     my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = gmtime(time);
#     #my $epochtime = time;
#     #print $epochtime;
#     $mon++;    # Base [0] to month
#     $year = 1900 + $year;
#     my $minm1 = $min-1;
#     my $minp1 = $min+1;
#     my $hourm1 = $hour-1;
#     my $hourp1 = $hour+1;

    # TUE, 12/6/2005, 9:09:05
     foreach ( split /\n/, $Buffer) {
        #Wed Apr 02 2008 09:58:00 UTC
        if (/^(\d+)/) {
            &Print2XLog ("Found Epoch Clock time = $_ Control time: $epochtime\n");
            if ($epochtime > $_+$timevari || $epochtime < $_-$timevari)  {
            	&Log_Error ("Failed: Epoch Clock time \"$_\" , Expected: $epochtime +-$timevari");
            }

        }
    }


}
#__________________________________________________________________________
sub Check_POST_INFO { # Check the startup output

#Adding Xglc  5/25/11
       my @postinfo_XGLC  = (
#    #".*",
    "CPU0:  P4080E. Version: 2.0. .0x82080020.",
    "Core:  E500MC. Version: 2.0. .0x80230020.",
    "Initializing.....................................................OK",
#    'CPU0:  P4080E, Version: 2.0, (0x82080020)',
#    'Core:  E500MC, Version: 2.0, (0x80230020)',
#    'Initializing....................................................[OK]',
    "I2C:   ready",
    "Validating RAM..................................................",
    "DRAM:  Initializing....using SPD",
    "Detected RDIMM(s)",
    "Detected RDIMM(s)",
    "14 GiB left unmapped",
    "DDR: 16 GiB (DDR3, 64-bit, CL=7, ECC on)[OK]",
    "Testing 0x00000000 - 0x7fffffff",
    "Testing 0x80000000 - 0xffffffff",
    "Testing 0x100000000 - 0x17fffffff",
    "Testing 0x180000000 - 0x1ffffffff",
    "Testing 0x200000000 - 0x27fffffff",
    "Testing 0x280000000 - 0x2ffffffff",
    "Testing 0x300000000 - 0x37fffffff",
    "Testing 0x380000000 - 0x3ffffffff",
    "Remap DDR 14 GiB left unmapped",
    #"      ",
    "read 128 bytes",
    "0: a5a5a5a5",
    "1: 3c3c3c3c",
    "2: a5a5a5a5",
    "3: 3c3c3c3c",
    "4: a5a5a5a5",
    "5: 3c3c3c3c",
    "6: a5a5a5a5",
    "7: 3c3c3c3c",
    "8: a5a5a5a5",
    "9: 3c3c3c3c",
    "10: a5a5a5a5",
    "11: 3c3c3c3c",
    "12: a5a5a5a5",
    "13: 3c3c3c3c",
    "14: a5a5a5a5",
    "15: 3c3c3c3c",
    "16: a5a5a5a5",
    "17: 3c3c3c3c",
    "18: a5a5a5a5",
    "19: 3c3c3c3c",
    "20: a5a5a5a5",
    "21: 3c3c3c3c",
    "22: a5a5a5a5",
    "23: 3c3c3c3c",
    "24: a5a5a5a5",
    "25: 3c3c3c3c",
    "26: a5a5a5a5",
    "27: 3c3c3c3c",
    "28: a5a5a5a5",
    "29: 3c3c3c3c",
    "30: a5a5a5a5",
    "31: 3c3c3c3c",
    "done; relocating now",
    "Now running in RAM - U-Boot at: 7ff70000",
    "Card type XGLC     ",
    "Validating Embedded Images......................................[OK]",
    "Board Reset Reasons: Power Cycle  SW Initiated Hard Reset",
    "CPU 0 Reset Reasons: Power XCycle",     ### Failure test
    "CPU 1 Reset Reasons: Power Cycle",
    "CPU 2 Reset Reasons: Power Cycle",
    "CPU 3 Reset Reasons: Power Cycle",
    "CPU 4 Reset Reasons: Power Cycle",
    "CPU 5 Reset Reasons: Power Cycle",
    "CPU 6 Reset Reasons: Power Cycle",
    "CPU 7 Reset Reasons: Power Cycle",
    "Booting from Primary Flash Bank",
    "POST memory PASSED",
    "128 MiB",
    "L2:    128 KB enabled",
    "Corenet Platform Cache: 2048 KB enabled",
    "Warning - bad CRC, using default environment",
    #"      ",
    "PCIE1 connected to Slot 1 as End Point (base addr fe200000)",
    "PCI Autoconfig: Bus Memory region: [0xe0000000-0xffffffff]",
    "Physical Memory [f80000000-f9fffffffx]",
    "PCI Autoconfig: Bus I/O region: [0x0-0xffff]",
    "Physical Memory: [ff8000000-ff800ffff]",
    "no link, regs @ 0xfe200000",
    "PCIe1: Bus 00 - 00",
    "PCIE2 connected to Slot 3 as Root Complex (base addr fe201000)",
    "PCI Autoconfig: Bus Memory region: [0xe0000000-0xffffffff]",
    "Physical Memory [fa0000000-fbfffffffx]",
    "PCI Autoconfig: Bus I/O region: [0x0-0xffff]",
    "Physical Memory: [ff8010000-ff801ffff]",
    "x2, regs @ 0xfe201000",
    "02:00.0     - 14e4:b842 - Network controller",
    "PCI Autoconfig: BAR 0, Mem, size=0x40000, address=0xe0000000 bus_lower=0xe004000",
    "PCIe2: Bus 01 - 02",
    "PCIE3 connected to Slot 2 as End Point (base addr fe202000)",
    "PCI Autoconfig: Bus Memory region: [0xe0000000-0xffffffff]",
    "Physical Memory [fc0000000-fdfffffffx]",
    "PCI Autoconfig: Bus I/O region: [0x0-0xffff]",
    "Physical Memory: [ff8020000-ff802ffff]",
    "no link, regs @ 0xfe202000",
    "PCIe3: Bus 03 - 03",
    "In:    serial",
    "Out:   serial",
	"Err:   serial"


);
     #Place holder for IMC2 and XGLCP
     my @postinfo_XGLCP=@postinfo_XGLC;
     my @postinfo_IMC2=@postinfo_XGLC;

       my @postinfo_LC  = (
							"PCI 0 bus mode: Conventional PCI",
							"PCI Autoconfig: Memory region: [80000000-bfffffff]",
							"PCI Autoconfig: I/O region: [e0000000-e7ffffff]",
							"PCI Scan: Found Bus 0, Device 13, Function 0",
							"PCI Autoconfig: BAR 0, Mem, size=0x1000, address=0x80000000",
							"PCI Autoconfig: BAR 1, Mem, size=0x4000000, address=0x84000000",
							"PCI Scan: Found Bus 0, Device 15, Function 0",
							"PCI Autoconfig: BAR 0, Mem, size=0x1000, address=0x88000000",
							"PCI Autoconfig: BAR 1, Mem, size=0x4000000, address=0x8c000000",
							"PCI 1 bus mode: Conventional PCI",
							"PCI Autoconfig: Memory region: [c0000000-cfffffff]",
							"PCI Autoconfig: I/O region: [f0000000-f01fffff]",
							"PCI Scan: Found Bus 1, Device 6, Function 0",
							"PCI Autoconfig: BAR 0, Mem, size=0x100000, address=0xc0000000",
							"PCI Autoconfig: BAR 1, Mem, size=0x4000000, address=0xc4000000",
							"PCI Autoconfig: BAR 2, Mem, size=0x10000000, address=0xd0000000",
							"PCI Scan: Found Bus 1, Device 7, Function 0",
							"PCI Autoconfig: BAR 0, I/O, size=0x100, address=0xf0000000",
							"PCI Autoconfig: BAR 1, I/O, size=0x100, address=0xf0000100"

);

my @postinfo_MC  = (
#  "Boot file name is: *",
#"Config file name is: .*",
#"FTP Server IP is: .*",
#"Gateway IP is: .*",
".*",
"PCI 0 bus mode: Conventional PCI",
"PCI Autoconfig: Memory region: [80000000-bfffffff]",
"PCI Autoconfig: I/O region: [e0000000-e7ffffff]",
"PCI Scan: Found Bus 0, Device 3, Function 0",
"PCI Autoconfig: BAR 0, Mem, size=0x1000, address=0x80000000",
"PCI Autoconfig: Found P2CardBus bridge, device 3",
"PCI Scan: Found Bus 0, Device 3, Function 1",
"PCI Autoconfig: BAR 0, Mem, size=0x1000, address=0x80001000",
"PCI Autoconfig: Found P2CardBus bridge, device 3",
"PCI Scan: Found Bus 0, Device 3, Function 2",
"PCI Autoconfig: BAR 0, Mem, size=0x1000, address=0x80002000",
"PCI Autoconfig: Found P2CardBus bridge, device 3",
"PCI Scan: Found Bus 0, Device 3, Function 3",
"PCI Autoconfig: BAR 0, Mem, size=0x1000, address=0x80003000",
"PCI Autoconfig: Found P2CardBus bridge, device 3",
"PCI Scan: Found Bus 0, Device 3, Function 4",
"PCI Autoconfig: BAR 0, Mem, size=0x1000, address=0x80004000",
"PCI Autoconfig: Found P2CardBus bridge, device 3",
"PCI Scan: Found Bus 0, Device 3, Function 5",
"PCI Autoconfig: BAR 0, Mem, size=0x1000, address=0x80005000",
"PCI Autoconfig: Found P2CardBus bridge, device 3",
"PCI Scan: Found Bus 0, Device 3, Function 6",
"PCI Autoconfig: BAR 0, Mem, size=0x1000, address=0x80006000",
"PCI Autoconfig: Found P2CardBus bridge, device 3",
"PCI Scan: Found Bus 0, Device 3, Function 7",
"PCI Autoconfig: BAR 0, Mem, size=0x1000, address=0x80007000",
"PCI Autoconfig: Found P2CardBus bridge, device 3",
"PCI Scan: Found Bus 0, Device 4, Function 0",
"PCI Autoconfig: BAR 0, Mem, size=0x80000, address=0x80080000",
"PCI Scan: Found Bus 0, Device 13, Function 0",
"PCI Autoconfig: BAR 0, Mem, size=0x1000, address=0x80100000",
"PCI Autoconfig: BAR 1, Mem, size=0x4000000, address=0x84000000",
"PCI Scan: Found Bus 0, Device 15, Function 0",
"PCI Autoconfig: BAR 0, Mem, size=0x1000, address=0x88000000",
"PCI Autoconfig: BAR 1, Mem, size=0x4000000, address=0x8c000000"

);
       my $postcount_LC = @postinfo_LC;
       my $postcount_XGLC = @postinfo_XGLC;
       my $postcount_MC = @postinfo_MC;
       my $postcount = 0;
       my @meminfo;
       my $cardtype = "";
       #@postinfo = (split /\n/, $Buffer);
   foreach (split /\n/, $Buffer) {

      #print ("POST Was $_  expected $postinfo_LC[$postcount] Postcount $postcount Postcount_LC $postcount_LC\n");

       if (/Total SDRAM memory is .... MB/) {
       		@meminfo = split (/ +/);
       		#if $meminfo[4]
       };
       #@cardtype = split (/ +/)
       if (/Card type LC/ && $Post_GBL eq 0 ) {
             $cardtype = "GLC";
             $Post_GBL++;
             &Print2XLog("Found Cardtype: $cardtype");
             #print ("Found Cardtype: $cardtype\n");
             next
       } elsif (/Card type MC/ && $Post_GBL eq 0 ) {
             $cardtype = "IMC";
             $Post_GBL++;
             &Print2XLog("Found Cardtype: $cardtype");
             #print ("Found Cardtype: $cardtype\n");
             next
     } elsif (/Card type XGLC/) {
     		 $Post_GBL++;  #We have detected a cardtype
             $cardtype = "XGLC";
             &Print2XLog("Found Cardtype: $cardtype");
             #print ("Found Cardtype: $cardtype\n");
             next
    } elsif (/^Card type IMC2$/) {
    		 $Post_GBL++;  #We have detected a cardtype
             $cardtype = "XGLC";
             &Print2XLog("Found Cardtype: $cardtype");
             #print ("Found Cardtype: $cardtype\n");
             next
    } elsif (/^Card type XGLCP$/) {
    		 $Post_GBL++;  #We have detected a cardtype
             $cardtype = "XGLC";
             &Print2XLog("Found Cardtype: $cardtype");
             #print ("Found Cardtype: $cardtype\n");
             next
       }


		if ($cardtype eq "GLC" && ( $postcount <= $postcount_LC -1 )) {
       		&Log_Error ("Mismatch in POST line count") if ( $postcount > $postcount_LC -1 ) ;
       		#while  ( $postcount <= $postcount_LC -1 ) {
            	#print ("POST: $_  Exp: $postinfo_LC[$postcount] Postcount $postcount Postcount_LC $postcount_LC\n");

        		&Log_Error ("POST Was $_ \n\t    Expected $postinfo_LC[$postcount]") if (! (/$postinfo_LC[$postcount]/));
            	$postcount++;
            #}
		}

		if ($cardtype eq "IMC" && ( $postcount <= $postcount_MC -1 )) {
       		&Log_Error ("Mismatch in POST line count") if ( $postcount > $postcount_MC -1 ) ;
       		#while  ( $postcount <= $postcount_LC -1 ) {
            	#print ("POST: $_  Exp: $postinfo_LC[$postcount] Postcount $postcount Postcount_LC $postcount_LC\n");
                if ((! (/$postinfo_MC[$postcount]/)) && ($postcount<6 )) {   #  Allow search forward without failure
                	#$postcount++;
                	next
                 } else {
        			&Log_Error ("POST Was $_ \n\t    Expected $postinfo_MC[$postcount]") if (! (/$postinfo_MC[$postcount]/));
            		$postcount++;
                }
            #}
		}

   }
     my $postinfo_XGLC_str = "";
     my $postinfo_XGLC_str_found = 0;
     foreach (@postinfo_XGLC) {      #foreach (@Screen_Data)
     	$postinfo_XGLC_str = $_;
        if ($cardtype eq "XGLC" && ( $postcount <= $postcount_XGLC -1 )) {
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


   if ($cardtype eq "GLC") {
        $Bench_card_type_gbl = "Bench_GLC.inc";
        $Bench_Prog_card_type_gbl = "Bench_Prog_GLC.inc";
    } elsif ($cardtype eq "IMC") {
        $Bench_card_type_gbl = "Bench_IMC.inc";
        $Bench_Prog_card_type_gbl = "Bench_Prog_IMC.inc";
    } elsif ($cardtype eq "XGLC") {
        $Bench_card_type_gbl = "Bench_XGLC.inc";
        $Bench_Prog_card_type_gbl = "Bench_Prog_XGLC.inc";
    } elsif ($cardtype eq "XGLCP") {
        $Bench_card_type_gbl = "Bench_XGLCP.inc";
        $Bench_Prog_card_type_gbl = "Bench_Prog_XGLCP.inc";
    } elsif ($cardtype eq "IMC2") {
        $Bench_card_type_gbl = "Bench_IMC2.inc";
        $Bench_Prog_card_type_gbl = "Bench_Prog_IMC2.inc";
    } else {
        &Log_Error ("Unable to determine Card type") if $Post_GBL eq 1;
        &Log_Error ("Unable to determine Card type Gen1 or 2") if $Post_GBL > 2;
        &Print2XLog ("Warn:Unable to determine Card type") if $Post_GBL eq 0;   #$postcount = 0
    }
    #$Post_GBL++;
    #$Post_GBL=0 if $Post_GBL > 2 ;
    $Post_N_GBL=1 if $Post_GBL=0 ;
    $Post_N_GBL=0 if $Post_GBL >= 1 ;

}
#_______________________________________________________________________________

sub Check_Potenita { # Read the data returned by 'pfeffa show mfg'
    my (%potentia) = @_;
   	my $potentia_ver = "";
	my $current_line = "";
	my @currentline_list = ();
	my @potentia_ver = ();
	my $count = 0;
	my $hex_count = sprintf ("%02x", $count);
	my ($potentia_ref) = \%potentia; #Can't put % in print statements

    &Print2XLog("Found Potentia $potentia_ref->{Potentia} Checking Potentia version",1);

   foreach (split /\n/, $Buffer) {
        #$current_line = $_ ;
       if ( /((?:\s[\da-fA-F][\da-fA-F]){16})/) {
       			$PSOC_GLB = 0;  # default for Potentia installed
     			$current_line = $1 ;
     			@currentline_list = split(" ", $current_line);
     			foreach (@currentline_list) {

     				#print ("Checking  $potentia_ref->{$hex_count} $hex_count and $_ \n");
     				if 	(( $count < 207 ) || ($count >  223 )) { # Take out locations that change on powerup 0xcf-0xdf
     					if ($potentia_ref->{$hex_count} =~ /$_/i) {
    						print ("Checking OK  $potentia_ref->{$hex_count} $hex_count and $_ \n") if $Debug;
     	  				} else {
                     		&Log_Error ("$potentia_ver Expected:$potentia_ref->{$hex_count} Loc:0x$hex_count Found $_ ");
     			       	}
     			    }
     				$count++;
     				$hex_count = sprintf ("%02x", $count);

     			}
     			#print ("current_line $current_line\n");
     			#@Buffer_val = ($Buffer_val, @currentline_list);
     			#print ("current line list: @currentline_list\n");
     }
}

}
#__________________________________________________________________________


sub Check_IMC_0_Standby { # Read the data returned by 'pfeffa show mfg'

    #Set the HA session early if IMC slot 0 is not master
    #pfeffa r8 F4000027
    #0xF400:0027	Arbitration
	#Status	Read-only	3 Bit	"	Provides status on other Mgmt Card regarding presence, arbitration request, active mastership
	#"	Hw ensures 1 Mgmt Card of pair is master. If both are present, then default is Hub Slot 0.
	#"	Bit 0: Other Mgmt Card Present; 1 = present, 0 = not present
	#"	Bit 1: Other Mgmt Card Arb Request; 1 = other Mgmt Card is requesting mastership, 0 = no request active
	#"	Bit 2: Other Mgmt Card Master; 1 = other Mgmt Card is active Master; 0 = not master
	#"	Bits [7:3] = don't care.
#    nvctl usage:
#   -d <file>: Return default gateway for GLC management
#              port by reading a file created by the IMC using
#              'route show'
#   -s : Return slot number
#   -P : Return Active IMC slot
#   -n : Return local node number
#   -N : Return local node name
#   -m : Return base channel MAC for this node
#   -M : Return the base MAC address for system management ports
#   -l <file> : Return the slot specific MAC address based on
#               the value written to a file using the '-M' option
#   -c : Return card type name
#   -i : Return node specific base channel IP address
#   -I <file> : Return the GLC management port IP address
#               based on output of 'ifconfig eno0' on the Active
#               IMC.
#   -X <file> : Return the XScale management port IP address.
#               Used in conjunction with the '-I' option to set
#               up the ppp connection between GPP and XScale.
#   -T <sec>  : Set the local processor time to <sec> since Jan 1,
#               1970.
#   -v : Return the version string from the currently accessible
#        SYSINFO_VERSION_FILE.
#   -R : Reset the local board
#   -z : Return the CPU's monotonic clock value
#   -Z : Set the sysinfo monotonic clock values
#   -F : Read local FIC SEEPROM and save information
#Stoke[local]#show card 0
#Slot  Type    State            Serial Number    Model Name       HW Rev
#----- ------- ---------------- ---------------- ---------------- ------
#    0 IMC1    Running(Standby) 0020542070000097 Stoke IMC1       05.05

     our $IMC_0_Standby  = 0;
     #my $hex_val = 0;
   foreach (split /\n/, $Buffer) {
        #if ( /F40000..\s+([\da-fA-F][\da-fA-F])/) {
        if ( /([0|1])/) {
        		#$hex_val = hex $1;
        		&Print2XLog("IMC Active Slot $1");
             if (($1 eq 1)) { # 0x03 inv
            		$IMC_0_Standby = 1;
                  &Print2XLog("Found IMC Slot 0 in Standby");
             }

     }
}

}

#___________________________________________________________________
sub Check_IMC_0_Standby_Prompt {

     our $IMC_0_Standby  = 0;
     #my $hex_val = 0;
   foreach (split /\n/, $Buffer) {
        #if ( /F40000..\s+([\da-fA-F][\da-fA-F])/) {
        if (/IMC-SB/) {
        		$IMC_0_Standby  = 1;
        		&Print2XLog("IMC Active Slot 1");


     }
}

}

#___________________________________________________________________
sub Check_U200 { # Read the data returned by 'pfeffa show mfg'

    #Check the output of the "rd i2c 9501 U200" command
     my $hex_val = 0;
   foreach (split /\n/, $Buffer) {
        if ( /^\s+([\da-fA-F][\da-fA-F])$/ and ! $P20_NOT_INSTALLED_GBL) {
     			$hex_val = hex $1;
                  print ("Found U200 $_ $hex_val\n");

             	if (!($hex_val & 0x03)) { # 0x03 inv
            		&Log_Error ("U200 Alarm Presence Signal failed, U200 IO 0, 1 Value:$_");
            	}
            	if  ($hex_val &  0x04 ) {  #0x04 inv
                    &Log_Error ("U200 Fan A Presence Signal failed, U200 IO 2 Value:$_");
                }
                if  ($hex_val &  0x08) { #0x08 inv
                    &Log_Error ("U200 Fan B Presence Signal failed, U200 IO 3 Value:$_");
                }
                if  ($hex_val &  0x10 ) { # 0x10 inv
                    &Log_Error ("U200 PEM A Presence Signal failed, U200 IO 4 Value:$_");
            	}
            	if  ($hex_val & 0x20) { #0x20 inv
                    &Log_Error ("U200 PEM B Presence Signal failed, U200 IO 5 Value:$_");
                }
                if  ($hex_val &  0x40) { #0x40 inv
                    &Log_Error ("U200 Filter Presence Signal failed, U200 IO 6 Value:$_");
                }
                if  (!($hex_val & 0x80)) { #0x80
                    &Log_Error ("U200 Un-used IO 7 failed Value:$_");
                     			}
     } elsif (/^([\da-fA-F][\da-fA-F])$/ and  $P20_NOT_INSTALLED_GBL) {
             	if  ($hex_val ne 0xff) { #Connector P20 is not installed so we should get all FF
                    &Log_Error ("U200 P20 Not installed should be FF got $_");
                }
     }
}

}
#__________________________________________________________________________


sub Check_UUT_Ver {

   my $File = $PPath . '/uutcfg/' . $Product_gbl . '/parts.cfg'; # Development Path
    #my $File = '/usr/local/cmtest/parts.cfg';
   my $Search = '';
   my $first;
   my $last;
    if  (&Read_Data_File ($File)) {
        die "Can\'t read data file $File";
    }
    while ((($first,$last) = each(%allowed_partnumber_rev)) && $debug) {
    	print ( "Check_UUT-Ver allowed_partnumber_rev Found: $first = $last \n");
    	}

     foreach (0..25) {
     	$PN[$_] =~ /(\w+)-(\w+)\sRev\s(\w+)/;
     	$Search = "$1-$2_Rev_$3";
        unless ($SN[$_] eq '') {
        	if ($allowed_partnumber_rev{$Search}) {

                &Print2XLog("Found correct revision for Part Number $PN[$_] found: $allowed_partnumber_rev{$Search} \n ") if $Debug
        	}   else  {
        		if (($Debug_UUT || $Development) && $UUT_Ver_check)  {
        			&Print2XLog("Warning: Incorrect revision for PN:$PN[$_] SN:$SN[$_]");
                } elsif ($UUT_Ver_check) {
                  &Log_Error ("Incorrect revision for PN:$PN[$_] SN:$SN[$_] \n ");
                }
        		$Search = "$1" ;
        		&Print2XLog("\tAllowed Versions are:\n");
        	   	while (($first,$last) = each(%allowed_partnumber_rev))  {
        	   		&Print2XLog("\t  $first = $last \n") if index($first,$Search) > -1 ;
    				}

        	}
            #&Print_Log (1, "PN[$_] = $PN[$_], SN = $SN[$_]");
                #otherwise 0   $partnumber_lookup{$1};
        }
    }

      $Full_Chassis_str_GBL ="@Slot_INST_GBL";
     #$Full_Chassis_GBL = 1 if @Slot_INST_GBL eq "1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 1 0 0 1 1 0 1 1 0 0";
     $Full_Chassis_GBL = 1 if $Full_Chassis_str_GBL eq "1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 1 0 0 1 1 0 1 1 0 0";
     $Full_Chassis_FRU_GBL = 1 if $Full_Chassis_str_GBL =~ m/1 1 . . . . 0 0 0 0 0 0 0 0 0 1 0 0 1 1 0 1 1 0 0/;

     if (($Debug_UUT || $Development) && $UUT_Ver_check)  {
     	&Print2XLog ("Warn:Full Chassis eq  $Full_Chassis_GBL, ( $Full_Chassis_str_GBL )");
     	&Print2XLog ("Warn:Full Chassis FRU eq  $Full_Chassis_FRU_GBL, ( $Full_Chassis_str_GBL )");
    } else   {
        &Print2XLog ("Full Chassis eq  $Full_Chassis_GBL, ( $Full_Chassis_str_GBL )",1);
     	&Print2XLog ("Full Chassis FRU eq  $Full_Chassis_FRU_GBL, ( $Full_Chassis_str_GBL )",1);
     }
     my $Check_UUT_Start_Time = time;
     &Check_UUT_Last_Status();
     my $Check_UUT_Stop_Time = time;
     my $Check_UUT_time = $Check_UUT_Stop_Time - $Check_UUT_Start_Time;
     &Print2XLog("UUT_Last_Status process time $Check_UUT_time sec $Check_UUT_Start_Time $Check_UUT_Stop_Time"); # if $Check_UUT_time > 5;
}

#__________________________________________________________________________


sub Check_UUT_Last_Status {
     my $TIDcfgfile = "";
     my $slot = 0;
     my $Prev_TID = "";
     my $Timestamp = 0;
     my $TestDate = "";
     my $TestStatus = "";
     my $Test_rec = "";
     my $CFG_Error = "";
     my $CFG_Msg = "";
     my $Event_Error = "";
     my $Event_Msg = "";
     my $TID_found = 0;


             if ($Full_Chassis_GBL == 0 && ! ($TestData{"TID"} eq "SHIP" ||
        	$TestData{"TID"} eq "SO" || $TestData{"TID"} eq "Program"
        	|| $TestData{"TID"} eq "Bench"|| $TestData{"TID"} eq "CHF"
        	|| $TestData{"TID"} eq "CHP" ) ) {
        	print ("Full Chassis eq  $Full_Chassis_GBL, ( $Full_Chassis_str_GBL ) \n");
        	 if (($Debug_UUT || $Development || $TestData{"TID"} eq "DEBUG"))  {
        			 &Print2XLog ("Warning: Test $TestData{\"TID\"} Expects a full chassis, Check for missing modules");
        		   } else {
              			&Log_Error ("Test $TestData{\"TID\"} Expects a full chassis, Check for missing modules");
              			return;
                    }
        };  # if this is full chassis we do not need to check

                   if ($Full_Chassis_FRU_GBL == 0 && ($TestData{"TID"} eq "CHF"
        	|| $TestData{"TID"} eq "CHP" || $TestData{"TID"} eq "SHIP") ) {
        	print ("Full Chassis FRU eq  $Full_Chassis_FRU_GBL, ( $Full_Chassis_str_GBL ) \n");
        	 if (($Debug_UUT || $Development))  {
        			 &Print2XLog ("Warning: Test $TestData{\"TID\"} Expects a full chassis FRU, Check for missing modules");
        		   } else {
              			&Log_Error ("Test $TestData{\"TID\"} Expects a full chassis FRU, Check for missing modules");
              			return;
                    }
        };  # if this is full chassis we do not need to check

     foreach (0..25) {
     	$slot = $_;
     	@TIDs = ("");
     	$PN[$_] =~ /(\w+)-(\w+)\sRev\s(\w+)/;
     	$Search = "$1-$2_Rev_$3";
     	# Bypass Check for previouse tests on Chassis only if a full shassis running Ship test
     	next if ($slot == 0 && $Full_Chassis_GBL == 1 && $TestData{"TID"} eq "SHIP" );  # if this is full chassis we do not need to check
     	# Log an Error if we are not ship test and and not a full chassis


        unless ($SN[$_] eq '') {
        	# NEED to add checks for test cards
        	#Read CFG file for each serial number(We are reading what we have already need to fix)
        	#Get the TIDs and find the previous TID
        	my $TIDcfgfile = $PPath . '/uutcfg/' . $Product_gbl . '/' . $1 . '.cfg';
           	if (-f $TIDcfgfile ) {
           		&Read_Data_File ($TIDcfgfile);
           		if (! @TIDs) {
                   if (($Debug_UUT || $Development))  {
        			  &Print2XLog("Warning: TIDs not found in CFG for PN:$PN[$slot] SN:$SN[$slot]");
        			  return;
        		   } else {
              			&Log_Error ("TIDs not found in CFG for PN:$PN[$slot] SN:$SN[$slot]");
              			return;
              	  }
              	}
           	   #foreach my $TID (@TIDs) {
               #	print "TIDs found for $SN[$_] Slot $slot $TID  \n";
               #	}
            	$Prev_TID = "";
            	$TID_found = 0;
            	foreach my $TID (@TIDs) {
            			#if ($TID eq $TestData{"TID"}) {
                        if ($TestData{"TID"} =~ /$TID/) {
            			#if (/$TestData{"TID"}/) {
            				$TID_found++;
            				last;
            			}
            			$Prev_TID = $TID;
            	}

            	print "My TID to check is $Prev_TID; _ $_\n" if $Debug;
            	if ($Prev_TID && $TID_found++ )  {
           			&Print2XLog("Prev TID $Prev_TID found for PN:$PN[$slot] SN:$SN[$slot]",1);
           		} else {
           			&Print2XLog("No Prev TID found for PN:$PN[$slot] SN:$SN[$slot]",1);
           			next;
           		}
           	} else {
           		if (($Debug_UUT || $Development))  {
        			&Print2XLog("Warning: TIDs not found for PN:$PN[$slot] SN:$SN[$slot]");
        			return;
        		} else {
              		&Log_Error ("TIDs not found for PN:$PN[$slot] SN:$SN[$slot]");
              		return;
              	  }
           	}

            # now get Previous test data ## these routines can work with multiple serial numbers fmt: <SN> | <SN>
            ($CFG_Error, $CFG_Msg) = &Get_Cfg_entry ($SN[$slot]);
            ($Event_Error, $Event_Msg) = &Get_Event_entry ($SN[$slot]);
            if ($CFG_Error || $Event_Error ) {
				($Timestamp, $TestStatus,$Test_rec) = &Get_Test_status ($SN[$slot],$Prev_TID);
				$TestDate = &PT_Date($Timestamp,0);
				$serial = $SN[$slot];
				if ($Timestamp && ($TestStatus eq 'PASS')) {
					&Print2XLog("Previous Test($Prev_TID) for PN:$PN[$slot] SN:$SN[$slot] PASSED on $TestDate \n",1);
				} else {
					if (($Debug_UUT || $Development || $User_Level eq 0 || $User_Level > 8))  {
					   &Print2XLog ("Warning:SN: $SN[$slot] [$slot] $TestStatus $Prev_TID test on $TestDate");
					} else {
    					&Log_Error ( "SN: $SN[$slot] [$slot] $TestStatus $Prev_TID test on $TestDate");
    				}
    				&Print2XLog ("SN: $SN[$slot] [$slot] Previous $Prev_TID Test Result: $Test_rec", 1);
    				if ($Event_rec) {
    					 &Print2XLog ("SN: $SN[$slot] Last Event Record for $SN[$slot]:$Event_rec",1);
    				}
				}
			}

    	}
	}
}

#__________________________________________________________________________
sub Config_Print_depreciated {    #        Print Info from Config test, uses XML log
		my $Out_File = "~/tmp/s2/cmtesta.xml";
        print ("Out_File: $Out_File \n");
        &DataFile_Read($Out_File);

         #my $fh;
         #open ($fh, ">>$Out_File") || &Exit (3, "Can't open $Out_File for cat");
         #print $fh "  \<Test_Tail\> ", '_' x 80, "\n" ;
         #print $fh "		<Runtime Units=\"secs\">$TestData{'TTT'}</Runtime>\n";
         #print $fh "		\<Enddate\>" . &PT_Date(time,2) . "</Enddate>\n";
         #print $fh "		\<TD-TEC>$TestData{'TEC'}</TD-TEC>\n";
         #print $fh "		\<Result\>$Stats{'Result'}</Result>\n";
         #print $fh "  <\/Test_Tail\>\n";


         #close $fh;


}
#__________________________________________________________________________
sub Get_SW55thlink { #Set SW55thlink if tlv 3 = 1
#pfeffa rd i2c fic tlv 3 , or Opt: on -f /net/nv-1-0 pfeffa rd i2c fic tlv 3
#type: 03, len: 03,              FIC TRUNKING BLOCK.
#                              01

       my $tlvinfo ;
       my $tlvinfo_slot =0;

       #print $Buffer;
   foreach (split /\n/, $Buffer) {
        if (/nv-(\d+)-0/) {
       		#&PrintLog ("Found: Slot $1");
       		$tlvinfo_slot = $1;
       	}
        if (/type: 03, len: 03,\s+FIC TRUNKING BLOCK/) {
       		&PrintLog ("Found: FIC 5th link/trunk TLV 3 in slot $tlvinfo_slot ");
       		$SW55thlink_gbl = 1;
       		$SW55thlinkSlot_gbl[$tlvinfo_slot] = 1;
       };
    }

   }


#_____________________________________________________________________________

sub Get_UUT_Variables {
	# This builds a hash array by slot #
		# This is work in progress - JW
   our @UUT_Variable_ref; # array of Hash Pointers

   #my @UUT_Varible_slot();
    my $File = $PPath . '/uutcfg/' . $Product_gbl . '/parts.cfg';
   #my $File = $PPath . '/uutcfg/parts.cfg'; # Default Development Path
   my $File2 = $PPath . '/uutcfg/' . $Product_gbl . '/UUT_default.cfg';
   my $File3 = $Tmp. '/UUT.cfg';
   #my $File = '/usr/local/cmtest/parts.cfg';
   my $Search = '';
   my $first;
   my $last;
   my $count = 0;
   my $count2 = 0;



    if  (&Read_Data_File ($File)) {
        die "Can\'t read data file $File";
    }
    while ((($first,$last) = each(%allowed_partnumber_rev)) && ($debug || $development)) {
    	print ( "Check_UUT-Ver allowed_partnumber_rev Found: $first = $last \n");
    	}
       #&Write_Data_File ($File3, '>','list');
     foreach (0..25) {
     	$count = $_ ;
     	$PN[$_] =~ /(\w+)-(\w+)\sRev\s(\w+)/;
        unless ($PN[$_] eq '') {
        #	if ($allowed_partnumber_rev{$Search}) {
        $File2 = $PPath . '/uutcfg/' . $Product_gbl . '/' . $1 . '.cfg';
        if  (&Read_Data_File ($File2)) {
        	die "Can\'t read data file $File2 on Slot $_";
    	}
    	$partnumber_hash  = "UUT" . "_" . $1 . "_" . $2;
    	$partnumber_hash_out  = "UUT" . "_" . $count . "_" . $1 . "_" . $2;
    	if (each(%{$partnumber_hash})) {
    	   &Print2XLog ("Found partnumber hash: $partnumber_hash\n",1);
    	} else {
          $partnumber_hash  = "UUT" .  "_" . $1;
          $partnumber_hash_out  = "UUT" . "_" . $count . "_" . $1;
          &PrintLog ("Default partnumber hash: $partnumber_hash\n",1);
        }
        #print ("Found Values in $partnumber_hash\n") if (%{$partnumber_hash});
    	while ((($first,$last) = each(%{$partnumber_hash}))  ) {    #  && ($debug || $development && ($debug || $development)
    		&Print2XLog ( "Variables Found in $partnumber_hash: $first = $last \n",1);
    	}
        $partnumber_hash_ref = \%{$partnumber_hash};
        %{$partnumber_hash_out} =  %{$partnumber_hash};
        $UUT_Variable_ref[$count] = \%{$partnumber_hash};
        # For Future use ?
        #&Write_Data_File ($File3, '>>', "%$partnumber_hash_out");
     }
    }
        foreach (0..25 ) {   #&& ($debug || $development)
             unless ($PN[$_] eq '') {
             	$count2 = $_ ;
             	foreach $key ( keys (%{$UUT_Variable_ref[$count2]})) {
             		&Print2XLog ("UUT_Variable_ref[$count2]->{$key}= $UUT_Variable_ref[$count2]->{$key}\n", 1);
             	}
             	 }
        }

}
#__________________________________________________________________________
sub Get_Mesh_slots{ # Run after serial info collected

    #Global variables for Configuratin test
     #if ($TestData{'TID'} eq 'SHIP' or $TestData{'TID'} eq 'DEBUG' ) {
     $Production_GBL = 1 if ($TestData{'TID'} eq 'SHIP' or $TestData{'TID'} eq 'FST'); # Command variable for final configuration test
   #    if ($TestData{'TID'} eq 'SHIP' or $TestData{'TID'} eq 'DEBUG' or $TestData{'TID'} eq 'BI' or $TestData{'TID'} eq 'IST' ) {

     if ($TestData{'TID'} eq 'SHIP' or $TestData{'TID'} eq 'DEBUG'  ) {
     	print ("Configuration Slot1 $Slot_INST_GBL[1] Slot2 $Slot_INST_GBL[2] Slot3 $Slot_INST_GBL[3] Slot4 $Slot_INST_GBL[4] Slot5 $Slot_INST_GBL[5] Slots active\n");
     	# Slots for 5 slot
     	#Globals for checking MESH in partially configured systems
		$Slot_INST_0_1_GBL = $Slot_INST_GBL[1]*$Slot_INST_GBL[2];    #Product of Slot_INST_GBL
    	$Slot_INST_0_2_GBL = $Slot_INST_GBL[1]*$Slot_INST_GBL[3];    #Product of Slot_INST_GBL
    	$Slot_INST_0_3_GBL = $Slot_INST_GBL[1]*$Slot_INST_GBL[4];    #Product of Slot_INST_GBL
    	$Slot_INST_0_4_GBL = $Slot_INST_GBL[1]*$Slot_INST_GBL[5];    #Product of Slot_INST_GBL
    	$Slot_INST_1_2_GBL = $Slot_INST_GBL[2]*$Slot_INST_GBL[3];    #Product of Slot_INST_GBL
    	$Slot_INST_1_3_GBL = $Slot_INST_GBL[2]*$Slot_INST_GBL[4];    #Product of Slot_INST_GBL
    	$Slot_INST_1_4_GBL = $Slot_INST_GBL[2]*$Slot_INST_GBL[5];    #Product of Slot_INST_GBL
    	$Slot_INST_2_3_GBL = $Slot_INST_GBL[3]*$Slot_INST_GBL[4];    #Product of Slot_INST_GBL
    	$Slot_INST_2_4_GBL = $Slot_INST_GBL[3]*$Slot_INST_GBL[5];    #Product of Slot_INST_GBL
    	$Slot_INST_3_4_GBL = $Slot_INST_GBL[4]*$Slot_INST_GBL[5];    #Product of Slot_INST_GBL
   	 	# Can't use global array variable yet
    	$Slot_INST_0_GBL = $Slot_INST_GBL[1];    #Product of Slot_INST_GBL
    	# As of 3.0 Slot 1 can be a glc or IMC
    	$Slot_1_NOT_IMC_GBL = 1 if ($Slot_CARD_TYPE_INST_1_GBL > 1 or $Slot_INST_GBL[2] eq 0);
        $Slot_INST_1_IMC_GBL  = 3 if $Slot_CARD_TYPE_INST_1_GBL eq 1;
        $Slot_INST_1_GLC_GBL  = 1 if $Slot_CARD_TYPE_INST_1_GBL > 1;
        #print ("Slot 1  IMC: $Slot_INST_1_IMC_GBL GLC: $Slot_INST_1_GLC_GBL Card Type: $Slot_CARD_TYPE_INST_1_GBL \n");
    	$Slot_INST_1_GBL = $Slot_INST_GBL[2];    #Product of Slot_INST_GBL
    	$Slot_INST_2_GBL = $Slot_INST_GBL[3];    #Product of Slot_INST_GBL
   		$Slot_INST_3_GBL = $Slot_INST_GBL[4];    #Product of Slot_INST_GBL
    	$Slot_INST_4_GBL = $Slot_INST_GBL[5];    #Product of Slot_INST_GBL
  	 	# Can't use global array variable yet
    	$Slot_SHOWENV_0_GBL = $Slot_INST_GBL[1]*$Slot_CARD_TYPE_INST_0_GBL;    #Product of Slot_INST_GBL
    	$Slot_SHOWENV_1_GBL = 1 if $Slot_CARD_TYPE_INST_1_GBL>3;    # if GLC 4 port or greater
    	$Slot_SHOWENV_2_GBL = 1 if $Slot_CARD_TYPE_INST_2_GBL>3;    # if GLC 4 port or greater
   		$Slot_SHOWENV_3_GBL = 1 if $Slot_CARD_TYPE_INST_3_GBL>3;    # if GLC 4 port or greater
    	$Slot_SHOWENV_4_GBL = 1 if $Slot_CARD_TYPE_INST_4_GBL>3;    # if GLC 4 port or greater

    	#print ("Slot :$Slot_INST_0_GBL $Slot_INST_1_GBL $Slot_INST_0_1_GBL : $Slot_INST_2_3_GBL \n");
    	#Turn up our filters
    	#our $mib_filter_1_gbl = '| grep  -e "gFrames" -e "disco port 0x2" -e "dx-sw5 port 0x0" -e "ixf port"  -e "gBytes" -e "gUcast.." -e "sizeTo127"  -e "Pkts65to127" -e "OctetsTotalOK" -e "bBytes.." -e "UcPckts" -e "..FifoOvrn" -e "ollision" -e "Undersize" -e "Frags" -e "badCRC" -e "Err" -e "late coll" -e "jabber" ';
        #our $mib_filter_2_gbl = '| grep -e "dx-sw5 port 0x0" -e "ixf port" -e "bBytes.." -e "ixf port"  -e  "gBytes..Lo" -e "gUcast.." -e "sizeTo127" -e "..FifoOvrn" -e "ollision" -e "Undersize" -e "Frags" -e "badCRC" -e "Err" -e "late coll" -e "jabber" ';

     } else {
     		print ("All Slots active\n");
     		$Slot_INST_0_1_GBL = 1;    # All slots must be installed
    	$Slot_INST_0_2_GBL = 1;   # All slots must be installed
    	$Slot_INST_0_3_GBL = 1;
    	$Slot_INST_0_4_GBL = 1;
    	$Slot_INST_1_2_GBL = 1;
    	$Slot_INST_1_3_GBL = 1;
    	$Slot_INST_1_4_GBL = 1;
    	$Slot_INST_2_3_GBL = 1;
    	$Slot_INST_2_4_GBL = 1;
    	$Slot_INST_3_4_GBL = 1;
   	 	# Can't use global array variable yet
   	 	$Slot_INST_GBL = (1,1,1,1,1,1);
    	$Slot_INST_0_GBL = 1;
    	$Slot_INST_1_GBL = 1;
    	$Slot_INST_2_GBL = 1;
   		$Slot_INST_3_GBL = 1;
    	$Slot_INST_4_GBL = 1;
    	# As of 3.0 Slot 1 can be a glc or IMC
    	$Slot_1_NOT_IMC_GBL = 1 if ($Slot_CARD_TYPE_INST_1_GBL > 1 or $Slot_INST_GBL[2] eq 0);
        $Slot_INST_1_IMC_GBL  = 3 if $Slot_CARD_TYPE_INST_1_GBL eq 1;
        $Slot_INST_1_GLC_GBL  = 1 if $Slot_CARD_TYPE_INST_1_GBL > 1;
    	$Slot_SHOWENV_0_GBL = 1;    #Product of Slot_INST_GBL
    	$Slot_SHOWENV_1_GBL = 1;    #Product of Slot_INST_GBL
    	$Slot_SHOWENV_2_GBL = 1;    #Product of Slot_INST_GBL
   		$Slot_SHOWENV_3_GBL = 1;    #Product of Slot_INST_GBL
    	$Slot_SHOWENV_4_GBL = 1;    #Product of Slot_INST_GBL

     }
      # Set traffic test time
     if ($TestData{'TID'} eq 'SHIP' or $TestData{'TID'} eq 'FST' or $TestData{'TID'} eq 'IST' or $TestData{'TID'} eq 'Bench' ) {
         our $internal_traffic_test_time_GBL = 60;   # One minute test  x
         our $internal_traffic_test_timeout_GBL = 150+60;
   	  } elsif ($TestData{'TID'} eq 'BI' ) {
	  	our $internal_traffic_test_time_GBL = 900;   # 30 minute test
	  	our $internal_traffic_test_time_background_GBL = 2x$internal_traffic_test_time_GBL;  #XGLC with 1gig and 10gig tests only
	  	our $internal_traffic_test_timeout_GBL = 1100+900;
	  } elsif ( $TestData{'TID'} eq 'EXT' ) {
         our $internal_traffic_test_time_GBL = 14400;   # 4 Hour Test
         our $internal_traffic_test_time_background_GBL = 2x$internal_traffic_test_time_GBL;   # 4 Hour Test
         our $internal_traffic_test_timeout_GBL = 14600+14400;
	  } elsif ( $TestData{'TID'} eq 'ORT' ) {
         our $internal_traffic_test_time_GBL = 43200;   # 12 Hour Test
         our $internal_traffic_test_time_background_GBL = 2x$internal_traffic_test_time_GBL;   # 12 Hour Test
         our $internal_traffic_test_timeout_GBL = 4000+43200;
	  } elsif ( $TestData{'TID'} eq 'CHA' ) {
         our $internal_traffic_test_time_GBL = 60;   # Debug
         our $internal_traffic_test_timeout_GBL = 400+60;
   	  } elsif ( $TestData{'TID'} eq 'DEBUG' ) {
         our $internal_traffic_test_time_GBL = 60;   # Seconds
         our $internal_traffic_test_timeout_GBL = 400+60;   # Seconds
         }
        our $internal_traffic_test_time_msg_GBL = "Send Traffic for $internal_traffic_test_time_GBL Seconds";

      # Get default fan speed, Added to help with noise factor
      if ($DefFanSpeed eq "Low") {
      	our $FanSpeed1_GBL = "wr i2c 9501 fan1 gpio 47"  ;
      	our $FanSpeed2_GBL = "wr i2c 9501 fan2 gpio 47"  ;
      	our $Fan2Speed1_GBL = "pfeffa wr i2c adm1029 1 60 55";
    	our $Fan2Speed2_GBL = "pfeffa wr i2c adm1029 2 60 55";
      	our $FanSpeed_MSG_GBL = "All Fans on Low"  ;
      } else {
        our $FanSpeed1_GBL = "wr i2c 9501 fan1 gpio E7"  ;
      	our $FanSpeed2_GBL = "wr i2c 9501 fan2 gpio E7"  ;
      	our $Fan2Speed1_GBL = "pfeffa wr i2c adm1029 1 60 AA";
    	our $Fan2Speed2_GBL = "pfeffa wr i2c adm1029 2 60 AA";
      	our $FanSpeed_MSG_GBL = "All Fans on High"  ;
      }

      $Slot_CARD_TYPE_INST_1_GBL = 3 if $Slot_CARD_TYPE_INST_1_GBL eq 1;  #Standby IMC card type
       # does the board have shasera installed, from uutcfg files
}
#__________________________________________________________________________
sub Get_Memory_size { # Read the data returned by 'pfeffa show mfg'

       my @meminfo ;


   foreach (split /\n/, $Buffer) {
   		@meminfo = split(/ +/);
       $meminfo[3] =~ s/\,//g;
       my $memtemp = $UUT_Variable_ref[$meminfo[1]+1]->{'SDRAM_RPT'};
       #print (  "Memory info $memtemp slot $meminfo[1] should equal $meminfo[3]\n") if ($meminfo[1] =~ /[0-9]/);
       if (($meminfo[1] =~ /[0-9]/) && ( ($meminfo[3] <  $memtemp ))) {
       		&Log_Error ("Memory in Slot $meminfo[1] was $meminfo[3] Expected: $memtemp  ");
       };
    }

   }


#__________________________________________________________________________
sub Get_Port_Counter_Det { # Read the data returned by 'show port <Slot>/<Port> count det'
       # This is tuned for packets created during configuration(ARP) and pins at
       # 64,512,1024,1528 packet sizes directed at each configured port.
       my %portinfo ;
       #my $portinfo_ref = \%portinfo;
       my $slot = 0;
       my $port = 0;
       my @line;
       # Non Zero Counters


       my $key;
       my $value;
       my $portinfo_line;


   foreach (split /\n/, $Buffer) {
   		next if (/show port.*/);  #ignore the command line
   		next if (/\w+ \w+ \d+ \d+\:\d+\:\d+ \w+ \d+\./); #ignore the date
   		next if (/Port.Input.Output/);
   		next if (/----- -----------------------------------  --------/);
   		if (s/(\d+)\/(\d+)(.*$)/$3/) {
   			$slot = $1 ;
   			$port = $2 ;
          #print ("removed Slot $slot Port $port \n");
   		}
   		s/^\s+//;		# remove white-space, at begiing of line
   		s/(^\w+)\(.*\)(:\s+\d+\s+.*$)/$1$2/;		# remove () and anythin inbetween
        s/(\w+)\(.*\)(:.*$)/$1$2/;		# remove () and anythin inbetween
   		if (/(\w+):\s+(\d+)\s\s(\w+):\s+(\d+)/) {
   			#Buffer Good Packets:                     0  Packets:                          0
   			if ($2 ne $4) {
                  &Log_Error("Slot/port:$slot/$port Input Counter $1:$2 did not match Output Counter $3:$4 ");
                  };
		}
		if (/(.*Err.*):\s+(\d+)\s\s(\w+):\s+(\d+)/) {
   			#Buffer Good Packets:                     0  Packets:                          0
   			if ($2 ne 0) {
                  &Log_Error("Slot/port:$slot/$port Counter $1:$2 Error count non Zero ");
                  };
		}

			if (/(\w+):\s+(\d+)\s\s(.*Err.*):\s+(\d+)/) {
   			#Buffer Good Packets:                     0  Packets:                          0
   			if ($2 ne 0) {
                  &Log_Error("Slot/port:$slot/$port Counter $3:$4 Error count non Zero ");
                  };
		}
    }

   }


#__________________________________________________________________________

sub Get_Port_Counter_Det_dep { # Read the data returned by 'show port <Slot>/<Port> count det'
       # This is tuned for packets created during configuration(ARP) and pins at
       # 64,512,1024,1528 packet sizes directed at each configured port.
       my %portinfo ;
       #my $portinfo_ref = \%portinfo;
       my $slot = 0;
       my $port = 0;
       my @line;
       # Counters that should not change when loopback plug is in place

       my %Counters = qw (
                              IN_Good_Packets                    29
                              IN_Octets                        1856
                              IN_UcastPkts                        9
                              IN_McastPkts                        0
                              IN_BcastPkts                       20
                              IN_ErrorPkts                        0
                              IN_OctetsGood                    1856
                              IN_OctetsBad                        0
                              IN_Pkts64                          29
                              IN_Pkts65to127                      0
                              IN_Pkts128to255                     0
                              IN_Pkts256to511                     0
                              IN_Pkts512to1023                    0
                              IN_Pkts1024to1518                   0
                              IN_Pkts1519toMax                    0
                              IN_TaggedPkts                       0
                              IN_PktRate                          0
                              IN_DataRate                         0
                              IN_BandWidthUtil                    0
                              IN_CRCErrors                        0
                              IN_DataErrors                       0
                              IN_AlignErrs                        0
                              IN_LongPktErrs                      0
                              IN_JabberErrs                       0
                              IN_SymbolErrs                       0
                              IN_PauseFrames                      0
                              IN_UnknownMACCtrl                   0
                              IN_VeryLongPkts                     0
                              IN_RuntErrPkts                      0
                              IN_ShortPkts                        0
                              OUT_CarrierExtend                    0
                              OUT_SequenceErrs                     0
                              OUT_SymbolErrPkts                    0
                              OUT_NoResourceDrop                   0
                              OUT_Packets                         29
                              OUT_Octets                        1856
                              OUT_UcastPkts                        9
                              OUT_McastPkts                        0
                              OUT_BcastPkts                       20
                              OUT_ErrorPkts                        0
                              OUT_OctetsGood                    1856
                              OUT_OctetsBad                        0
                              OUT_Pkts64                          29
                              OUT_Pkts65to127                      0
                              OUT_Pkts128to255                     0
                              OUT_Pkts256to511                     0
                              OUT_Pkts512to1023                    0
                              OUT_Pkts1024to1518                   0
                              OUT_Pkts1519toMax                    0
                              OUT_TaggedPkts                       0
                              OUT_PktRate                          0
                              OUT_DataRate                         0
                              OUT_BandWidthUtil                    0
                              OUT_PktsCRCErrs                      0
                              OUT_TotalColls                       0
                              OUT_SingleColls                      0
                              OUT_MultipleColls                    0
                              OUT_LateCollisions                   0
                              OUT_ExcessiveColls                   0
                              OUT_PauseFrames                      0
                              OUT_FlowCtrlColls                    0
                              OUT_ExcessLenPkts                    0
                              OUT_UnderrunPkts                     0
                              OUT_ExcessDefers                     0
 );

       my $key;
       my $value;
       my $portinfo_line;


   foreach (split /\n/, $Buffer) {
   		next if (/show port.*/);  #ignore the command line
   		next if (/\w+ \w+ \d+ \d+\:\d+\:\d+ \w+ \d+\./); #ignore the date
   		if (s/(\d+)\/(\d+)//) {
   			$slot = $1 ;
   			$port = $2 ;
          #print ("removed Slot $slot Port $port \n");
   		}
   		s/^\s+//;		# remove white-space, at begiing of line
   		s/(^\w+)\(.*\)(:\s+\d+\s+.*$)/$1$2/;		# remove () and anythin inbetween
        s/(\w+)\(.*\)(:.*$)/$1$2/;		# remove () and anythin inbetween

   		if (/:/) {
   			s/^Good Packets(:\s+\d+\s+)/Good_Packets$1/;
   			#@line = /(\w+):\s+(\d+)\s+|$/g;
   			if (/^(.*):\s+(\d+)\s+/) {       # Column 1
   				$portinfo_line = "IN_" . $1;
   				#print ("Col 1 Line: $portinfo_line $2\n");
            	%portinfo = (%portinfo,$portinfo_line,$2);
            }
  			if (/(\w+):\s+(\d+)$/) {       # Column 2
   				$portinfo_line = "OUT_" . $1;
   				#print ("Col 2 Line: $portinfo_line $2\n");
   				#print ("Col 2 Line: $1 $2\n");
				 %portinfo = (%portinfo,$portinfo_line,$2);
            }
		}
    }
    #print "Port info array\n";
    #print %portinfo;
      while( my ($key, $value) = each %Counters ) {
       	if (($value eq 0 && $value ne $portinfo{$key}) || ($portinfo{$key} < ($value * .5) || $portinfo{$key} >($value * 1.2) ) ) {
      	#if (($value eq 0 && $value ne $portinfo{$key}) || ($portinfo{$key} < ($value -1) || $portinfo{$key} > $value ) ) {
        #if ($value ne $portinfo{$key} ) {   #%portinfo{$key}
         &Log_Error ("Slot/port:$slot/$port Counter $key Expected: $value*.5 to $value*1.2 Found: $portinfo{$key}");
        }
        #print "key: $key, value: $value\n";
    }
   }


#__________________________________________________________________________
sub Get_FPD { # Read the data returned by 'show port <Slot>/<Port> count det'
       # This is tuned for packets created during configuration(ARP) and pins at
       # 64,512,1024,1528 packet sizes directed at each configured port.
       my %portinfo ;
       #my $portinfo_ref = \%portinfo;
       my $slot = 0;
       my $port = 0;
       my @line;
       # Non Zero Counters

       my $key;
       my $value;
       my $portinfo_line;


   foreach (split /\n/, $Buffer) {
   		if (/show.fpd.driver.slot\s+(d+)/) {
   			$slot = $1;
   			next;
   			}
   		#Tx Byte:                60,804      Rx Byte:                60,748
   		s/^\s+//;		# remove white-space, at begiing of line
   		s/(^\w+)\(.*\)(:\s+\d+\s+.*$)/$1$2/;		# remove () and anythin inbetween
        s/(\w+)\(.*\)(:.*$)/$1$2/;		# remove () and anythin inbetween
   		if (/^(Tx Pkt):\s+(\d+)\s+(Rx Pkt):\s+(\d+)/) {
   			#Buffer Rx Frame 127-255:            0      Rx Frame 1024-Max:           0
   			if ($2 ne $4) {
                  &Log_Error("Slot:$slot FPD Input Counter $1:$2 did not match Output Counter $3:$4 ");
                  };
		}
    }

   }



#__________________________________________________________________________
sub Get_DOS { # Read the data returned by 'show port <Slot>/<Port> count det'
       # This is tuned for packets created during configuration(ARP) and pins at
       # 64,512,1024,1528 packet sizes directed at each configured port.
       my %portinfo ;
       #my $portinfo_ref = \%portinfo;
       my $slot = 0;
       my $port = 0;
       my @line;
       # Non Zero Counters

       my $key;
       my $value;
       my $portinfo_line;

#       Stoke[local]#show dos slot 2 counters
#Packet Type           Packets in  Packets dropped
#--------------------  ----------  ---------------
#Invalid Encap               0            0
#Nitrox IPv4 IKE             0            0

   foreach (split /\n/, $Buffer) {
   		if (/show.dos.slot\s+(d+)\s+counter/) {
   			$slot = $1;
   			next;
   			}
   		#Tx Byte:                60,804      Rx Byte:                60,748
   		s/^\s+//;		# remove white-space, at begiing of line
   		s/(^\w+)\(.*\)(:\s+\d+\s+.*$)/$1$2/;		# remove () and anythin inbetween
        s/(\w+)\(.*\)(:.*$)/$1$2/;		# remove () and anythin inbetween
   		if (/^(ARP packets)\s+(\d+)\s+(\d+)/) {       #ARP packets               454            0
   			if ($3 ne 0) {
                  &Log_Error("Slot:$slot DOS ARP $1:$2 dropped $3 packets");
                  };
		}elsif ( /^(\w+.*)\s+(\d+)\s+(\d+)/) {       #ARP packets               454            0
   			#Buffer Rx Frame 127-255:            0      Rx Frame 1024-Max:           0
   			if ($3 ne 0) {
                  &Log_Error("Slot:$slot $1:$2 dropped $3 packets");
                  };
        }
    }

   }

 #__________________________________________________________________________


sub Get_show_mfg_serial { # Read the data returned by 'pfeffa show mfg'

    #my $File = '/home/ptindle/cfgfiles/parts.cfg';
    my $File = $PPath . '/uutcfg/' . $Product_gbl . '/parts.cfg';
    #my $File = $PPath . '/uutcfg/' . $Product_gbl . '/parts.cfg'; # Development Path
    #my $File = '/usr/local/cmtest/parts.cfg';
    if  (&Read_Data_File ($File)) {
        die "Can\'t read data file $File";
    }

    my $Trap_Cfg_Errors = 0;
       my @PSS = ( 14,        #[0] = # slots in card cage
                3,        #[1] = # PEMs
                3         #[2] = # Fans
              );
    my %Data = ();
    my @DataSet = ();
#    foreach (@Screen_Data) { # Can't use this - no blank lines!
   foreach (split /\n/, $Buffer) {

         #       CHASSIS 9501   CHASSIS, 5-slot rev 1.1      0070105370100002
        if ((/CHASSIS\s9501\s+(\w+, \w+.\w+) rev (\w+).(\w+)\s+(\w+)/) or
         	(/CHASSIS 9501\s+(\w+,\s+5-slot)\s+rev (\w+).(\w+)\s+(\w+)/)) {
         	 $Data{'Major'}   = $2;
             $Data{'Model'}  = $1;
             $Data{'Minor'} = $3;
             $Data{'Serial'} = $4;
             $Data{'Slot'} = "Chassis" ;
             $Cfg_Ptr = 0 ;
             #print ("Chassis Buffer $Data{'Slot'} $Data{'Model'} $Data{'Major'}. $Data{'Minor'} cfg $Cfg_Ptr Ser $Data{'Serial'} \n");
         }
         #PEM 1   PEM, 5-slot, AC rev 2.1      0090105370100016
         #if (/PEM\s(\w+)\s+(\w+.\w+.\s\w+\s AC)\srev\s(\w+)\.(\w+)\s+(\w+)/) {
         if ((/(PEM \w+)\s+(\w+, \w+.\w+. AC) rev (\w+).(\w+)\s+(\w+)/) or
         	(/(PEM \w+)\s+(\w+,\s+5-slot, DC) rev (\w+).(\w+)\s+(\w+)/) or
         	(/(PEM2 \w+)\s+(\w+,\s+5-slot, DC) rev (\w+).(\w+)\s+(\w+)/) or
         	(/(PEM \w+)\s+(\?) rev (\w+).(\w+)\s+(\w+)/)) {  #PEM2 old diags

             $Data{'Model'}  = $2;
             $Data{'Model'}  = "PEM2 5-slot, DC" if $2 eq "?";  #Old Diags fan2
             $Data{'Major'}   = $3;
             $Data{'Minor'} = $4;
             $Data{'Serial'} = $5;
             $Data{'Slot'} = $1 ;
			if ($Data{'Slot'} =~ /PEM (\w+)/) {
             	$Cfg_Ptr = $1 + $PSS[1]+ $PSS[0];
             }
         }
         # FAN MODULE 1  FAN-MODULE, 5-slot rev 2.1      0100105370100003
         if ( (/(FAN MODULE \w+)\s+(FAN-MODULE. 5-slot) rev (\w+).(\w+)\s+(\w+)/) or
         	  (/(FAN MODULE \w+)\s+(FAN-MODULE,\s+5-slot)\s+rev (\w+).(\w+)\s+(\w+)/) or
         	  (/(FAN2 MODULE \w+)\s+(FAN-MODULE,\s+5-slot)\s+rev (\w+).(\w+)\s+(\w+)/) or
         	  (/(FAN MODULE \w+)\s+(\?)\s+rev (\w+).(\w+)\s+(\w+)/)) {  #Old Diags fan2

             $Data{'Model'}  = $2;
             $Data{'Model'}  = "FAN2-MODULE, 5-slot" if $2 eq "?";  #Old Diags fan2
             $Data{'Major'}   = $3;
             $Data{'Minor'} = $4;
             $Data{'Serial'} = $5;
             $Data{'Slot'} = $1 ;
			if ($Data{'Slot'} =~ /FAN MODULE (\w+)/) {
             	$Cfg_Ptr = $1 + $PSS[2]+ $PSS[1]+ $PSS[0];
             }
         }
         # ALARM CARD 1  ALARM MODULE, 5-slot rev 3.1     0080105370100001
          if ((/(ALARM CARD \w+)\s+(ALARM MODULE, 5-slot) rev (\w+).(\w+)\s+(\w+)/) or
         	(/(ALARM CARD \w+)\s+(ALARM-MODULE,\s+5-slot)\s+rev (\w+).(\w+)\s+(\w+)/) )  {

             $Data{'Model'}  = $2;
             $Data{'Major'}   = $3;
             $Data{'Minor'} = $4;
             $Data{'Serial'} = $5;
             $Data{'Slot'} = $1 ;
             if ($Data{'Slot'} =~ /ALARM CARD (\w+)/) {
             	$Cfg_Ptr = $1 + $PSS[0];
             }
         }
         #slot 1 9501       GLC, 2-port rev 3.1        0010133050000054  or
         #slot 4 9501             GLC, 4-port rev 3.1      0010133050000038
         if ( (/slot (\w+) 9501\s+(GLC.*), (\w+)-port rev (\w+).(\w+)\s+(\w+)/) or
         	(/slot (\w+) 9501\s+(GLC.*),\s+(\w+)-port\s+rev (\w+).(\w+)\s+(\w+)/))  {

             $Data{'Model'}  = "GLC" . " " . $3;
             $Data{'Major'}   = $4;
             $Data{'Minor'} = $5;
             $Data{'Serial'} = $6;
             $Data{'Slot'} = $1 ;
             $Cfg_Ptr = $1+1;

             # I know there is an easier way , but how?
             if ($1 eq 1) {
                 $Slot_CARD_TYPE_INST_1_GBL = $3;
                 #print ("Slot 1  ${Slot_CARD_TYPR_INST_1_GBL} = $2\n");
             }
             if ($1 eq 2) {
                 $Slot_CARD_TYPE_INST_2_GBL = $3;
                 #print ("Slot 2  ${Slot_CARD_TYPR_INST_2_GBL} = $2\n");
             }
             if ($1 eq 3) {
                 $Slot_CARD_TYPE_INST_3_GBL = $3;
                 #print ("Slot 3  ${Slot_CARD_TYPR_INST_3_GBL} = $2\n");
             }
             if ($1 eq 4) {
                 $Slot_CARD_TYPE_INST_4_GBL = $3;
                 #print ("Slot 4  ${Slot_CARD_TYPR_INST_4_GBL} = $2\n");
             }


             #print ("GLC Buffer $Data{'Slot'} $Data{'Model'} $Data{'Major'}. $Data{'Minor'} cfg $Cfg_Ptr Ser $Data{'Serial'} \n");
         }
               #slot 4 9501  GLC2                      rev 02.02           0130133050000011
         if	(/slot (\w+) 9501\s+(GLC2)\s+rev (\w+).(\w+)\s+(\w+)/)  {

             $Data{'Model'}  = "GLC2" ;
             $Data{'Major'}   = $3;
             $Data{'Minor'} = $4;
             $Data{'Serial'} = $5;
             $Data{'Slot'} = $1 ;
             $Cfg_Ptr = $1+1;

             # I know there is an easier way , but how?
             if ($1 eq 1) {
                 $Slot_CARD_TYPE_INST_1_GBL = 4;
                 #print ("Slot 1  ${Slot_CARD_TYPR_INST_1_GBL} = $2\n");
             }
             if ($1 eq 2) {
                 $Slot_CARD_TYPE_INST_2_GBL = 4;
                 #print ("Slot 2  ${Slot_CARD_TYPR_INST_2_GBL} = $2\n");
             }
             if ($1 eq 3) {
                 $Slot_CARD_TYPE_INST_3_GBL = 4;
                 #print ("Slot 3  ${Slot_CARD_TYPR_INST_3_GBL} = $2\n");
             }
             if ($1 eq 4) {
                 $Slot_CARD_TYPE_INST_4_GBL = 4;
                 #print ("Slot 4  ${Slot_CARD_TYPR_INST_4_GBL} = $2\n");
             }


             #print ("GLC Buffer $Data{'Slot'} $Data{'Model'} $Data{'Major'}. $Data{'Minor'} cfg $Cfg_Ptr Ser $Data{'Serial'} \n");
         }
         #slot 2 9501  XGLC           4-port     rev 04.01           0210401311100001
         if	(/slot (\w+) 9501\s+(XGLC)\s+4-port\s+rev (\w+).(\w+)\s+(\w+)/)  {

             $Data{'Model'}  = "XGLC" ;
             $Data{'Major'}   = $3;
             $Data{'Minor'} = $4;
             $Data{'Serial'} = $5;
             $Data{'Slot'} = $1 ;
             $Cfg_Ptr = $1+1;

             # I know there is an easier way , but how?
             if ($1 eq 1) {
                 $Slot_CARD_TYPE_INST_1_GBL = 4;
                 #print ("Slot 1  ${Slot_CARD_TYPR_INST_1_GBL} = $2\n");
             }
             if ($1 eq 2) {
                 $Slot_CARD_TYPE_INST_2_GBL = 4;
                 #print ("Slot 2  ${Slot_CARD_TYPR_INST_2_GBL} = $2\n");
             }
             if ($1 eq 3) {
                 $Slot_CARD_TYPE_INST_3_GBL = 4;
                 #print ("Slot 3  ${Slot_CARD_TYPR_INST_3_GBL} = $2\n");
             }
             if ($1 eq 4) {
                 $Slot_CARD_TYPE_INST_4_GBL = 4;
                 #print ("Slot 4  ${Slot_CARD_TYPR_INST_4_GBL} = $2\n");
             }


             #print ("GLC Buffer $Data{'Slot'} $Data{'Model'} $Data{'Major'}. $Data{'Minor'} cfg $Cfg_Ptr Ser $Data{'Serial'} \n");
         }
         #slot 0 9501                MC rev 3.1        0020133050000022
         #if (/Slot\s(\w+)\s9501\s+MC\s+rev\s(\w+)\.(\w+)\s+(\w+)/) {
         if ( (/slot (\w+) 9501\s+MC rev (\w+).(\w+)\s+(\w+)/) or
         	(/slot (\w+) 9501\s+IMC\s+rev (\w+).(\w+)\s+(\w+)/) ) {
              #print ("SLOT Buffer $1\n");
             $Data{'Model'}  = "MC";
             $Data{'Major'}   = $2;
             $Data{'Minor'} = $3;
             $Data{'Serial'} = $4;
             $Data{'Slot'} = $1 ;
             $Cfg_Ptr = $1+1;
             if ($Cfg_Ptr eq 1) {   # SLot Zero installed
             	$Slot_CARD_TYPE_INST_0_GBL = 1;
             	 #	print ("Slot 0 Card Type: $Slot_CARD_TYPR_INST_0_GBL\n");
             } else {
             	$Slot_CARD_TYPE_INST_1_GBL  = 1;
             	#print ("Slot 1 Card Type: $Slot_CARD_TYPR_INST_1_GBL\n");
             	}
            # print ("MC Buffer $Data{'Slot'} $Data{'Model'} $Data{'Major'}. $Data{'Minor'} cfg $Cfg_Ptr Ser $Data{'Serial'} \n");
         }
         #else {
         #                $Data{'Serial'} = '<none>';
         #                $Data{'PN'}     = '<none>';
         #            }
         unless ($Cfg_Ptr eq '') {
         				if ($Data{'Serial'} =~ /(\w{3})\w{13}/) {
                     			$Data{'PN'} = $partnumber_lookup{$1};

                     	}
                     	 if ($Data{'Minor'} !~ /\d{2}/) {
                         $Data{'Minor'} = "0". $Data{'Minor'}; #Add leading 0
                     	 }
                     	 if ($Data{'Major'} !~ /\d{2}/) {
                         $Data{'Major'} = "0". $Data{'Major'}; #Add leading 0
                     	 }
                         $PN[$Cfg_Ptr] = "$Data{'PN'}-$Data{'Major'} Rev $Data{'Minor'}"
                         unless $Data{'PN'} eq '';  {

                         $SN[$Cfg_Ptr] = $Data{'Serial'};
                         #print (" Found[$Cfg_Ptr]:  $PN[$Cfg_Ptr] Ser: $SN[$Cfg_Ptr]\n");
                         $Cfg_Ptr = '';
                         }
         }


             %Data = ();
        }
   if ($PN[0] =~ /-\sRev\s/)  {
    	print ("Partnumber/serial number not captured aborting\n");
    	&Exit_TestExec();
    	}
    foreach (0..25) {
        unless ($SN[$_] eq '') {
            &Print_Log (1, "PN[$_] = $PN[$_], SN = $SN[$_]");
            $Slot_INST_GBL[$_] = 1;     #otherwise 0
        }
    }
    &Check_UUT_Ver();
    &Get_UUT_Variables();
    $Stats{'UUT_ID'} = $SN[0] unless $Cfg_Ptr;
    &Stats::Update_All;
    Get_Mesh_slots(); #Setup the global varibles needed for cmd file
    }


#_____________________________________________________________________________
sub Get_Board_Info {

    # Extract the Part number and Serial number info
    #  from global @Screen_Data and update @PN & @SN
     # part number lookup
    my $File = $PPath . '/uutcfg/' . $Product_gbl . '/parts.cfg';
    #my $File = $PPath . '/uutcfg/parts.cfg'; #

    if  (&Read_Data_File ($File)) {
        die "Can\'t read data file $File";
    }

    my $major_rev_str = "" ;
    my $minor_rev_str = "" ;
    my $partnumber_str = "";
    # our $glc_type_str_gbl = "";   #defined in INIT

    foreach (@Screen_Data) {

        if ((/.*(\w{16}).*/)  or
        	(/serial number:[ ,](\w{16})/)) {      #diag as of 4/06
           $SN[0] = $1;
           $SN[0] =~ /(\w{3})(\w{2})(\w{4})(\w{1})(\w{1})(\w{5})/;
           $PN[0] = $1;    #!!! Need a lookup

        }

        if ((/hex. (\w+\.\w+\.\w+\.\w+\.\w+\.\w+) -- count (\d+)/) or    #  (hex) 0.12.73.0.a.8 -- count 4
        	(/mac .in hex. : (\w+\.\w+\.\w+\.\w+\.\w+\.\w+) -- count (\d+) / )) {   #diag as of 4/06
           $MAC[0] = $1 . ":" . $2;

           }


    	# parse this line model=000D -- GLC, 2-port -- rev 3.1
        if ((/\s\smodel=....\s--\s\w+.\s([a-zA-Z0-9\-]+)\s--\srev\s(\d+)\.(\d+).*/)  or
        	( /model\/type\s+:.*\/GLC,\s+([a-zA-Z0-9\-]+)\s+, rev: (\d+)\.(\d+).*/  )) { #diag as of 4/06

            $major_rev_str = $2;
        	$minor_rev_str = $3;
        	$glc_type_str_gbl = $1;
        	#print("ScreeData: $_ \n");
        	#print("Type: $1 Major rev $major_rev_str  Minor rev $minor_rev_str \n");
               # add leading 0
        	if ($major_rev_str !~ /\d{2}/)  {
        		$major_rev_str  = '0' . $major_rev_str ;
        	}
        	if ($minor_rev_str !~ /\d{2}/) {
        		$minor_rev_str  = '0' . $minor_rev_str ;
        	}
             #print("Type: $1 Major rev $major_rev_str  Minor rev $minor_rev_str \n");

        }

        	# parse this line model/type   : 12/GLC2                     , rev: 2.2
        if ( /model\/type\s+:.*\/GLC2\s+, rev: (\d+)\.(\d+).*/  ) { #diag as of 4/06

            $major_rev_str = $1;
        	$minor_rev_str = $2;
        	$glc_type_str_gbl = '4-port';   # only 4 ports for GLC2
        	#print("ScreeData: $_ \n");
        	#print("Type: $1 Major rev $major_rev_str  Minor rev $minor_rev_str \n");
               # add leading 0
        	if ($major_rev_str !~ /\d{2}/)  {
        		$major_rev_str  = '0' . $major_rev_str ;
        	}
        	if ($minor_rev_str !~ /\d{2}/) {
        		$minor_rev_str  = '0' . $minor_rev_str ;
        	}
             #print("Type: $1 Major rev $major_rev_str  Minor rev $minor_rev_str \n");

        }
        if ( /model\/type\s+:.*\/XGLC\s+4-port\s+, rev: (\d+)\.(\d+).*/  ) { #XGLC As of 09/27/11

            $major_rev_str = $1;
        	$minor_rev_str = $2;
        	$glc_type_str_gbl = '4-port';   # only 4 ports for GLC2
        	#print("ScreeData: $_ \n");
        	#print("Type: $1 Major rev $major_rev_str  Minor rev $minor_rev_str \n");
               # add leading 0
        	if ($major_rev_str !~ /\d{2}/)  {
        		$major_rev_str  = '0' . $major_rev_str ;
        	}
        	if ($minor_rev_str !~ /\d{2}/) {
        		$minor_rev_str  = '0' . $minor_rev_str ;
        	}
             #print("Type: $1 Major rev $major_rev_str  Minor rev $minor_rev_str \n");

        }
           #parse this line: model=0001 -- MC -- rev 3.1
        if ((/\s\smodel=....\s--\s\w+\s--\srev\s(\d+)\.(\d+).*/)  or
        	( /model\/type.*\/IMC\s+, rev: (\d+)\.(\d+).*/  )){  #diag as of 4/06
            $major_rev_str = $1;
        	$minor_rev_str = $2;
        	$glc_type_str_gbl = 'null';
            # add leading 0
        	if ($major_rev_str !~ /\d{2}/) {
        		$major_rev_str  = '0' . $major_rev_str ;
        	}
        	if ($minor_rev_str !~ /\d{2}/) {
        		$minor_rev_str  = '0' . $minor_rev_str ;
        	}
             #print("Type: $1 Major rev $major_rev_str  Minor rev $minor_rev_str \n");

        }

    }


    $PN[0] =  $partnumber_lookup{$PN[0]} . '-' . $major_rev_str . ' Rev ' . $minor_rev_str ;
    #print("Found PN $PN[0] \n");  # $partnumber{$PN[0]}
    if ($MAC[0]) {
    	&Print2XLog ("PN = \'$PN[0]\',SN = \'$SN[0]\',MAC = \'$MAC[0]\'");
     } else {
         &Print2XLog ("PN = \'$PN[0]\',SN = \'$SN[0]\'");
    	}
    $Stats{'UUT_ID'} = $SN[0];
    &Stats::Update_All;
    if ($PN[0] =~ /-\sRev\s/ )  {
    	if (!($Devlopment)) {
    		print ("Warning: Partnumber/serial number not captured\n");
    	} else {
    		print ("Partnumber/serial number not captured aborting\n");
    		&Exit_TestExec();
    		}
    	}
        &Check_UUT_Ver();
        &Get_UUT_Variables();
    if ($Debug) {
        print "[Get_Serial_Info:] Serial Data->\n$Data{Serial}\n<-\n";
        for $i( 0 .. 2 ) {
            print "$i)\tPN=$PN[$i]\tSN=$SN[$i]\n";
        }
        &PETC('-230');
    }

#!!!    &Create_SigmaQuest_Unit_Report if $First_Time and $PN[0] ne '';
}
#__________________________________________________________________________     sub Get_Board_Info {

    # Extract the Part number and Serial number info
    #  from global @Screen_Data and update @PN & @SN
#__________________________________________________________________________
sub Get_BootPrompt {    # Called by Screen_Data

#  Still In process

    my $bootprompt = '';


     foreach ( split /\n/, $Buffer) {
    		#print("$1 \n");
        if (/(\w+)/i) {
           $bootprompt = $1;
           print ("BootPrompt:  $0 \n");
         }
    }

     &Print2XLog ("BootPrompt:  $bootprompt");
     print ("BootPrompt:  $bootprompt \n");




}
#__________________________________________________________________________
sub Get_FistbootIMC {    # Called by Screen_Data



    my $bootprompt = '';


     foreach ( split /\n/, $Buffer) {
        if (/New IMC in Slot 0/i) {
           $Firstboot_Dual_IMC_GBL = 1;
           &Print2XLog ("First boot of Dual IMC found");
         }
    }



}
#__________________________________________________________________________
sub Get_MAC {


    foreach (@Screen_Data) {
    			#  Cmd: rd i2c 9501 chassis tlv 8
                #  This routines assumes the IMCs will use the first two MACs in the chassis
                my $hex_int = 0;
                my $hex_str = '';
                my $ip_hex_int = 0;
                my $ip_hex_str = '';
                my $ip2_hex_int = 0;
                my $ip2_hex_str = '';
         #print ("Get_MAC Sreen data: $_\n");
        if (  /(\w+)\.(\w+)\.(\w+)\.(\w+)\.(\w+)\.(\w+)/ ) {   #diag as of 4/06
           $MAC[0] = $1 . $2 . $3 . $4 . $5 . $6;
           $MAC[1] = $1 . $2 . $3 . $4 . $5 . $6;

           $hex_int = hex $5 . $6;
           $hex_int++;
           $hex_str = sprintf ("%04X", $hex_int);
           $MAC[1] =  $1 . $2 . $3 . $4 . $hex_str;
           }

         }

    if ($MAC[0]) {
       &Print2XLog ("MAC = \'$MAC[0]\'");
        &Print2XLog ("MAC = \'$MAC[1]\'");
     } else   {
     		# may use this for bench testing IMC that does not have a mac address - TBD
     		# For Now log as a error and try to continue

           $ip_hex_int = $UUT_IP;
           $ip_hex_int =~ s/\.//g;
           $ip2_hex_int = $UUT_IP;
           $ip2_hex_int =~ s/\.//g;
           $ip2_hex_int++ ;
           $ip_hex_str = sprintf ("%08X", $ip_hex_int);
           $ip2_hex_str = sprintf ("%08X", $ip2_hex_int);
           if (! ($TestData{'TID'} eq 'Bench'))  {       # This is only allowed during bench test(no Chassis)
           		&Log_Error ("Failed to get MAC address-Defaulting to IP generated MAC");
           }
           &Print2XLog ("Default IP based MAC: 0012$ip_hex_str\n");

           $MAC[0] = "00" . "12". $ip_hex_str;
           $MAC[1] = "00" . "12". $ip2_hex_str;
           #print ("MAC 1 $MAC[0]\n");

       }


}
#__________________________________________________________________________

sub Getmytime {

#     set clock THU, 10/11/2005,8:30:0
#  		show clock
#		WED, 10/11/2005, 8:30:16


     #my $month = ('JAN','FEB','MAR','APR','MAY','JUN','JUL','AUG','SEP','OCT','NOV','DEC') [ (gmtime)[4] ];
     my $today = ('SUN','MON','TUE','WED','THU','FRI','SAT')[ (gmtime)[6] ];
     my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = gmtime(time);
     # Pad with Zeros where needed
     #my $gmtimenow = time;
     #print ("GMTIME $gmtimenow\n");
     $sec = sprintf "%02d", $sec;
     $min = sprintf "%02d", $min;
     $hour = sprintf "%02d", $hour;
     our $sysclock_glb = "$today, $mon/$mday/$year, $hour:$min:00" ;
     $mday = sprintf "%02d", $mday;
     $mon = sprintf "%02d", $mon;
     $mon++;    # Base [0] to month
     $year = 1900 + $year;
     #our $sysclock_glb = "$today, $mon/$mday/$year, $hour:$min:00" ;
     our $sysclock_OS_set_glb = "clock set $year:$mon:$mday:$hour:$min:$sec" ;
     our $sysclock_QNX_set_glb = "if (date $year$mon$mday$hour$min.$sec) then (echo ClockSet:PASS) fi" ;  #[[[CC]YY]MM]DD]hhmm[.SS]

     our $sysclock_set_glb = "set clock $today, $mon/$mday/$year, $hour:$min:00" ;
     our $sysclock_nosec_glb = "$today, $mon/$mday/$year, $hour:$min" ;
#Depreciated, used for IMC clock test
#      if ($min > 9)  {
#        our $sysclock_5sec_glb = "$today, $mon/$mday/$year, $hour:$min:05" ;
#        our $sysclock_nosec_padmin_glb = "$today, $mon/$mday/$year, $hour:$min";

#     }
#     else {  # Pad min with a 0
#         our $sysclock_5sec_glb = "$today, $mon/$mday/$year, $hour:0$min:05" ;
#         our $sysclock_nosec_padmin_glb = "$today, $mon/$mday/$year, $hour:0$min" ;
#     }
        our $sysclock_5sec_glb = "$today, $mon/$mday/$year, $hour:$min:05" ;
        our $sysclock_nosec_padmin_glb = "$today, $mon/$mday/$year, $hour:$min";

     our $hidden_password_glb = 2*$mon + $year;

    &Print2XLog("Current GM date and Time $sysclock_5sec_glb, $hidden_password_glb,$sysclock_OS_nosec_glb  \n");


}
#__________________________________________________________________________
sub Get_CPLD_data {    # Called by Screen_Data

#  Still In process

    &Print2XLog ("Get Slot Number");
    &Print2XLog ("CPLD_Slot: $Buffer",1) if 1;


    # <Send> f4000003
    # f4000003 xx
    # Items concered with now
	#F4000000                   card-type  00'
	#F4000001                    assy-rev  02'
	#F4000002               cpld-code-rev  8D'
	#F4000003          bp-logical-slot-id  41'
	# Power connection
	#F4000004                bp-system-id  03'
	#5 Slot Chassis
	#F4000004                bp-system-id  00'



     foreach ( split /\n/, $Buffer) {
    		#print("$1 \n");
        if (/(\w+)\s*([a-zA-Z0-9\-]+)\s*(\w+)/i) {
           $Cpld_data{$2} = $3;
           #print("My data $1 Cpld_data{$2} = $3 \n");
           #print("All data $0 : $2 = $3 \n");

        }
    }

       foreach (keys %Cpld_data) {
        if ($Cpld_data{$_} and $UUT_Variable_ref[0]->{$_} ){
                if ($UUT_Variable_ref[0]->{$_} =~ /$Cpld_data{$_}/) {
                   &Print2XLog ("Verified: Cpld_data: $_ = $Cpld_data{$_}", 1);
                } else {
                  &Log_Error ("Cpld_data: $_ = $Cpld_data{$_} Expected: $UUT_Variable_ref[0]->{$_} " );
                  }
        }
    }


   # foreach (keys %Cpld_data) {
   #     if (/card-type|assy-rev|cpld-code-rev|bp-logical-slot-id/){
   #            &Print2XLog ("Cpld_data: $Cpld_data{$_} = $_", 1);
   #            #print ("Cpld_data: $Cpld_data{$_} = $_ \n") ;

   #    }
   # }



   $slot_gbl = $Cpld_data{'bp-logical-slot-id'};
   $slot_gbl =~ s/^4//; # Delete 4
   $slot_gbl =~ s/^7F/1F/; # Delete Highest slot all Ids open
   $slot_gbl--;  #CPLD is 1 based everyone else is 0 based
   $testmemorysize_gbl = $UUT_Variable_ref[0]->{'SDRAM_TEST'}  ;
   &Print2XLog ("Slot Found:  $slot_gbl Test Memory size $testmemorysize_gbl");




}
#__________________________________________________________________________

sub GetOrder {

    my ( $Match, $Exclude ) = @_;



        my $chassis_serialnumber = "";
        my $chassis_partnumberrev = "";
        my $chassis_5slotpartnum = "00315";
        my $chassis_partnumber = "";
        my $chassis_partnumber_version = "";
        my $chassis_revison = "";
        my $order_number = "";
        my $imc_pcba_temp = "";
        my $Chassis_product_code = "007";

        my $answerok = "N";
        my($answer) = "" ;

        $Cfg_Ptr = '';

        # get imc partnumber
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan Chassis Part number and Revision: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^PN//i;    # remove text
    		$answer =~ s/://g;    # remove text
    		($chassis_partnumber,$chassis_revison) = split(/rev/i,$answer);
    		$chassis_partnumber =~ s/ //g;     # remove spaces
    		$chassis_revison =~ s/ //g;     # remove spaces
    		if (($chassis_partnumber =~ /^[0-9]{5}-[0-9]{2}$/)&&($chassis_revison =~ /^[0-9]{2}$/)) {    # 5-2 digits required
    			if ($chassis_partnumber =~ /^$chassis_5slotpartnum/) {
                    $answerok = "Y";
                    ($imc_pcba_temp,$chassis_partnumber_version) = split("-", $chassis_partnumber);
                     $Cfg_Ptr = 0;
            	} else {
               		print ("Incorect part number entered \n");
            	}
            } else {
            		print ("Incorrect part number length entered\n");
            }

    	}
       #	;Print_Out_XML_Tag
        &Print2XLog ("Part Number and Revision Entered: $chassis_partnumber Rev $chassis_revison");


        $answerok = "N";
        # get imc Serial number
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan Chassis Serial number: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^SN://;    # remove text
    		$answer =~ s/ //g;     # remove spaces
    		if ($answer =~ /^[0-9]{16}$/) {    # 16 digits required
    			if ($answer =~ /^$Chassis_product_code/) {
                    $answerok = "Y";
                    $chassis_serialnumber = $answer ;
                    $Cfg_Ptr = 0;

            	} else {
               		print ("Incorect product code entered \n");
            	}
            } else {
            		print ("Incorrect Serial number length entered\n");
            }

    	}
         &Print2XLog ("Chassis Serial number entered: $chassis_serialnumber");
         unless ($Cfg_Ptr eq '') {
         	   $SN[$Cfg_Ptr] = $chassis_serialnumber ;
               $PN[$Cfg_Ptr] = "$chassis_partnumber Rev $chassis_revison";
               }

         $Cfg_Ptr = '';
        # get WorkOrder Number
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Enter Stoke Work Order Number: ");
    		chomp($answer = <STDIN>);
       		$order_number = $answer;

       		print("\nOperator: You Entered:  $order_number ");
       		until ($answer =~ /^[YyNn]/) {
       			print("\nIs this Correct? (Y/N): ");
       			chomp($answer = <STDIN>);

      			if ($answer =~ /^[Yy]$/){

                   $answerok = "Y";
                   $Cfg_Ptr = 1;
                   $PN[$Cfg_Ptr] = $order_number;
             	} else {
                   $answerok = "N"
  		   		}
  		   	}

    	}

        &Print2XLog ("Work Order Entered: $order_number ");

                 $Cfg_Ptr = '';
        # get SalesOrder Number
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Enter Customer Sales Order Number: ");
    		chomp($answer = <STDIN>);
       		$order_number = $answer;

       		print("\nOperator: You Entered:  $order_number ");
       		until ($answer =~ /^[YyNn]/) {
       			print("\nIs this Correct? (Y/N): ");
       			chomp($answer = <STDIN>);

      			if ($answer =~ /^[Yy]$/){

                   $answerok = "Y";
                   $Cfg_Ptr = 1;
                   $SN[$Cfg_Ptr] = $order_number;
             	} else {
                   $answerok = "N"
  		   		}
  		   	}

    	}

        &Print2XLog ("Work Order Entered: $order_number ");


        foreach (0..1) {
        	unless ($SN[$_] eq '') {
            &Print_Log (1, "PN[$_] = $PN[$_], SN = $SN[$_]");
        	}
        }
        $Stats{'UUT_ID'} = $chassis_serialnumber;
       	#$Stats{'UUT_ID'} = $imc_fic_sernumber_gbl;
       	#$Stats{'UUT_ID'} = $imz_mmz_sernumber_gbl;
        &Stats::Update_All;


    return ();
}

#__________________________________________________________________________
sub GetSerial {
         #Used for Debu cases where unable to collect serial number from board
    my ( $Match, $Exclude ) = @_;

        my $chassis_serial = "";
        my $partnumberrev = "";
        my $partnumber = "";
        my $partnumber_version = "";
        my $revison = "";
        my $order_number = "";
        my $imc_pcba_temp = "";

        my $answerok = "N";
        my($answer) = "" ;

        $Cfg_Ptr = '';

        # get imc partnumber
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan Part number and Revision: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^PN//i;    # remove text
    		$answer =~ s/://g;    # remove text
    		($partnumber,$revison) = split(/rev/i,$answer);
    		$partnumber =~ s/ //g;     # remove spaces
    		$revison =~ s/ //g;     # remove spaces
    		if (($partnumber =~ /^[0-9]{5}-[0-9]{2}$/)&&($revison =~ /^[0-9]{2}$/)) {    # 5-2 digits required
               $answerok = "Y";
               ($imc_pcba_temp,$partnumber_version) = split("-", $partnumber);
               $Cfg_Ptr = 0;
            } else {
            		print ("Incorrect part number length entered\n");
            }

    	}
       #	;Print_Out_XML_Tag
        &Print2XLog ("Part Number and Revision Entered: $partnumber Rev $revison");


        $answerok = "N";
        # get imc Serial number
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan Serial number: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^SN://;    # remove text
    		$answer =~ s/ //g;     # remove spaces
    		if ($answer =~ /^[0-9]{16}$/) {    # 16 digits required
               $answerok = "Y";
               $serialnumber = $answer ;
               $Cfg_Ptr = 0;

            } else {
            		print ("Incorrect Serial number length entered\n");
            }

    	}
         &Print2XLog ("Serial number entered: $serialnumber");
         unless ($Cfg_Ptr eq '') {
         	   $SN[$Cfg_Ptr] = $serialnumber ;
               $PN[$Cfg_Ptr] = "$partnumber Rev $revison";
               }

         $Cfg_Ptr = '';


        foreach (0..1) {
        	unless ($SN[$_] eq '') {
            &Print_Log (1, "PN[$_] = $PN[$_], SN = $SN[$_]");
        	}
        }
        $Stats{'UUT_ID'} = $serialnumber;
       	#$Stats{'UUT_ID'} = $imc_fic_sernumber_gbl;
       	#$Stats{'UUT_ID'} = $imz_mmz_sernumber_gbl;
        &Stats::Update_All;


    return ();
}

#__________________________________________________________________________

sub GLC_Program {
		# Subrotine Get_CPLD_data must be used prior to load $slot_gbl
      # Still to do 1) Get Slot from CPLD, 2) Cross check Product code to Part number
    my ( $Match, $Exclude ) = @_;
    my $PassFail = 'PASS';   # Used only by Sigmaprobe
        my $glc_pcba_temp = "";
        my $fic_pcba_temp = "";
    	my $glc2pt_type_str = '00 00 00 0D ';
        my $glc4pt_type_str = '00 00 00 02 ' ;
        my $glc2_4pt_type_str = '00 00 00 12 ' ;
        my $glc_fic_type_str = '00 00 00 0B ';

        my $stoke_mac_assign = '00 12 73';
        my $glc2pt_mac_quan = ' 00 04 ';
        my $glc4pt_mac_quan = ' 00 08 ';

        my $glc_fic_boardpartnumber_str = '';
        my $glc_fic_boardversion_str = '00 03 ';
        my $glc_fic_boardrevision_str = '00 01 ';

        my $glc_boardpartnumber_str = '';
        my $glc_boardversion_str = '00 03 ';
        my $glc_boardrevision_str = '00 01 ';

        my $glc2pt_pcba_partnumber = "00002";  # does not include the "-0x"
        my $glc4pt_pcba_partnumber = "00648";  # does not include the "-0x"
        my $glc2_4pt_pcba_partnumber = "00722";
        my $glc_fic_pcba_partnumber = "00293";  # does not include the "-0x"


        my $glc2pt_product_code = "001";  # these are the first three dig of the serial num
        my $glc4pt_product_code = "011";   # these are the first three dig of the serial num
        my $glc2_4pt_product_code = "013";   # these are the first three dig of the serial num
        my $glc_fic_product_code = "004";    # these are the first three dig of the serial num

        # basic programming strings
        my $glc_U67_tlv_0 = "wr i2c u67 tlv 0 h ";
        my $glc_9501_tlv_0 = "wr i2c 9501 $slot_gbl tlv 0 h ";   # Fixed Slot number right now(Can get this from CPLD)
        my $glc_U67_tlv_7 = "wr i2c U67 tlv 7 s ";
        my $glc_9501_tlv_7 = "wr i2c 9501 $slot_gbl tlv 7 s ";  # Fixed Slot number right now(Can get this from CPLD)
        my $glc_U67_tlv_8 = "wr i2c u67 tlv 8 h ";
        my $glc_9501_tlv_8 = "wr i2c 9501 $slot_gbl tlv 8 h ";

        my $glc_fic_tlv_0 = "wr i2c fic tlv 0 h ";
        my $glc_fic_tlv_7 = "wr i2c fic tlv 7 s ";

        # Globals to pass back to DAT
        # added to support I2C erase
        our $glc_U67_erase_gbl = "wr i2c u67 2 00";
        our $glc_9501_erase_gbl = "wr i2c 9501 " . $slot_gbl . " 2 00";
        our $glc_fic_erase_gbl = "wr i2c fic 2 00";

        our $glc_U67_tlv_0_gbl = "";
        our $glc_9501_tlv_0_gbl = "";
        our $glc_U67_tlv_7_gbl = "";
        our $glc_9501_tlv_7_gbl = "";
        our $glc_U67_tlv_8_gbl = "";
        our $glc_9501_tlv_8_gbl = "";

        our $glc_fic_tlv_0_gbl = "";
        our $glc_fic_tlv_7_gbl = "";

        our $glc_sernumber_gbl = "";
        our $glc_partnumber_gbl = "";
        our $glc_revision_gbl = "";
        our $glc_tlv_0_verify_gbl = "";
        our $glc_fic_tlv_0_verify_gbl = "";
        our $glc_mac_gbl = "";
        our $glc_MAC_tlv_8_verify_gbl = "";
        our $glc_fic_sernumber_gbl = "";

        my $answerok = "N";
        my($answer) = "" ;
        my(@fields) = "";

         $Cfg_Ptr = '';

        # get GLC partnumber
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan GLC Part number and Revision: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^PN//i;    # remove text
    		$answer =~ s/://g;    # remove text
    		($glc_partnumber_gbl,$glc_revision_gbl) = split(/rev/i,$answer);
    		$glc_revision_gbl =~ s/ //g;     # remove spaces
    		$glc_partnumber_gbl =~ s/ //g;     # remove spaces
    		if (($glc_partnumber_gbl =~ /^[0-9]{5}-[0-9]{2}$/)&&($glc_revision_gbl =~ /^[0-9]{2}$/)) {    # 5-2 digits required
    			if ($glc_partnumber_gbl =~ /^$glc2pt_pcba_partnumber|^$glc4pt_pcba_partnumber|^$glc2_4pt_pcba_partnumber/) {
                    $answerok = "Y";
                    ($glc_pcba_temp,$glc_boardversion_str) = split("-", $glc_partnumber_gbl);

            	} else {
               		print ("Incorect part number entered \n");
            	}
            } else {
            		print ("Incorrect part number length entered\n");
            }

    	}
        $glc_boardversion_str = "00 " . sprintf("%02X",$glc_boardversion_str);
        $glc_boardrevision_str = " 00 " . sprintf ("%02X",$glc_revision_gbl) ;
        &Print2XLog ("Part Number and Revision Entered: $glc_partnumber_gbl Rev $glc_revision_gbl");


        $answerok = "N";
        # get GLC Serial number
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan GLC Serial number: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^SN://;    # remove text
    		$answer =~ s/ //g;     # remove spaces
    		if ($answer =~ /^[0-9]{16}$/) {    # 16 digits required
    			if ($answer =~ /^$glc2pt_product_code|^$glc4pt_product_code|^$glc2_4pt_product_code/) {
                    $answerok = "Y";
                    $glc_sernumber_gbl = $answer ;
                    if ($answer =~ /^$glc2pt_product_code/) {
                    	$glc_U67_tlv_0_gbl = $glc_U67_tlv_0 . $glc2pt_type_str . $glc_boardversion_str .  $glc_boardrevision_str ;
                    	$glc_9501_tlv_0_gbl = $glc_9501_tlv_0 . $glc2pt_type_str . $glc_boardversion_str .  $glc_boardrevision_str ;
                    	$glc_tlv_0_verify_gbl =  $glc2pt_type_str . $glc_boardversion_str .  $glc_boardrevision_str ;
                    	$Cfg_Ptr = 0;
                    } elsif ($answer =~ /^$glc2_4pt_product_code/) {
                    	$glc_U67_tlv_0_gbl = $glc_U67_tlv_0 . $glc2_4pt_type_str . $glc_boardversion_str .  $glc_boardrevision_str ;
                    	$glc_9501_tlv_0_gbl = $glc_9501_tlv_0 . $glc2_4pt_type_str . $glc_boardversion_str .  $glc_boardrevision_str ;
                    	$glc_tlv_0_verify_gbl =  $glc2_4pt_type_str . $glc_boardversion_str .  $glc_boardrevision_str ;
                    	$Cfg_Ptr = 0;
                    } else  {
                    	$glc_U67_tlv_0_gbl = $glc_U67_tlv_0 . $glc4pt_type_str . $glc_boardversion_str .  $glc_boardrevision_str ;
                    	$glc_9501_tlv_0_gbl = $glc_9501_tlv_0 . $glc4pt_type_str . $glc_boardversion_str .  $glc_boardrevision_str ;
                    	$glc_tlv_0_verify_gbl =  $glc4pt_type_str . $glc_boardversion_str .  $glc_boardrevision_str ;
                    	$Cfg_Ptr = 0;
                    }
            	} else {
               		print ("Incorect product code entered \n");
            	}
            } else {
            		print ("Incorrect Serial number length entered\n");
            }

    	}
    	$glc_U67_tlv_7_gbl = $glc_U67_tlv_7 . $glc_sernumber_gbl ;
        $glc_9501_tlv_7_gbl = $glc_9501_tlv_7 . $glc_sernumber_gbl ;
        &Print2XLog ("GLC Serial number entered: $glc_sernumber_gbl");
        unless ($Cfg_Ptr eq '') {
               $SN[$Cfg_Ptr] = $glc_sernumber_gbl  ;
               $PN[$Cfg_Ptr] = "$glc_partnumber_gbl Rev $glc_revision_gbl";
               }
         $Cfg_Ptr = '';
        # get MAC
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan GLC MAC Address: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^MAC//i;    # remove text
    		$answer =~ s/ //g;     # remove spaces
    		$answer =~ s/:/ /g;     # sub : for <space>
    		$answer =~ s/\./ /g;     # sub . for <space>
    		$answer =~ s/([a-zA-Z0-9 ]{2})([a-zA-Z0-9 ]{2})([a-zA-Z0-9 ]{2})([a-zA-Z0-9 ]{2})([a-zA-Z0-9 ]{2})([a-zA-Z0-9 ]{2})/$1 $2 $3 $4 $5 $6/ if $answer =~ /^[a-zA-Z0-9]{12}$/;
       		if ($answer =~ /^[a-zA-Z0-9 ]{17}$/) {    # 5-2 digits required
    			if ($answer =~ /^$stoke_mac_assign/) {
                    $answerok = "Y";
                    $glc_mac_gbl = $answer;
                    if ($glc_sernumber_gbl =~ /^$glc2pt_product_code/) {
         				$glc_U67_tlv_8_gbl = $glc_U67_tlv_8 . $glc_mac_gbl . $glc2pt_mac_quan ;     # global
        				$glc_9501_tlv_8_gbl = $glc_9501_tlv_8 . $glc_mac_gbl . $glc2pt_mac_quan ;
        				$glc_MAC_tlv_8_verify_gbl = $glc_mac_gbl . $glc2pt_mac_quan ;
                    } else  { # 4 port
         				$glc_U67_tlv_8_gbl = $glc_U67_tlv_8 . $glc_mac_gbl . $glc4pt_mac_quan ;     # global
        				$glc_9501_tlv_8_gbl = $glc_9501_tlv_8 . $glc_mac_gbl . $glc4pt_mac_quan ;
        				$glc_MAC_tlv_8_verify_gbl = $glc_mac_gbl . $glc4pt_mac_quan ;
                    }

            	} else {
               		print ("Incorect MAC number entered($answer) \n");
            	}
            } else {
            		print ("Incorrect MAC number length entered($answer)\n");
            }

    	}

	   	&Print2XLog ("GLC MAC number entered: $glc_MAC_tlv_8_verify_gbl");

        my ($MAC_Erc, $MAC_Erc_Msg) = &Log_MAC ($SN[0],$glc_MAC_tlv_8_verify_gbl);
        &Log_MAC_Record ($SN[0],$glc_MAC_tlv_8_verify_gbl);
        &Log_Error ($MAC_Erc_Msg) if ($MAC_Erc > 0);

        # get FIC partnumber
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan FIC Part number and Revision: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^PN//i;    # remove text
    		$answer =~ s/://g;    # remove text
    		($glc_fic_partnumber_gbl,$glc_fic_revision_gbl) = split(/rev/i,$answer);
    		$glc_fic_revision_gbl =~ s/ //g;     # remove spaces
    		$glc_fic_partnumber_gbl =~ s/ //g;     # remove spaces
    		if (($glc_fic_partnumber_gbl =~ /^[0-9]{5}-[0-9]{2}$/) &&($glc_fic_revision_gbl =~ /^[0-9]{2}$/)) {    # 5-2 digits required
    			if ($glc_fic_partnumber_gbl =~ /^$glc_fic_pcba_partnumber/) {
                    $answerok = "Y";
                    ($fic_pcba_temp,$glc_fic_boardversion_str) = split("-", $glc_fic_partnumber_gbl);

            	} else {
               		print ("Incorect part number entered \n");
            	}
            } else {
            		print ("Incorrect part number length entered\n");
            }

    	}
        $glc_fic_boardversion_str = "00 " . sprintf ("%02X",$glc_fic_boardversion_str);
        $glc_fic_boardrevision_str = " 00 " . sprintf ("%02X",$glc_fic_revision_gbl) ;
        &Print2XLog ("Part Number and Revision Entered: $glc_fic_partnumber_gbl Rev $glc_fic_revision_gbl");


        $answerok = "N";
        $answer = "" ;
        # get FIC Serial number
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan FIC Serial number: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^SN://;    # remove text
    		$answer =~ s/ //g;     # remove spaces
    		if ($answer =~ /^[0-9]{16}$/) {    # 16 digits required
    			if ($answer =~ /^$glc_fic_product_code/) {
                    $answerok = "Y";
                    $glc_fic_sernumber_gbl = $answer ;
                    $glc_fic_tlv_0_gbl = $glc_fic_tlv_0 . $glc_fic_type_str . $glc_fic_boardversion_str . $glc_fic_boardrevision_str ;
                    $glc_fic_tlv_0_verify_gbl =  $glc_fic_type_str . $glc_fic_boardversion_str . $glc_fic_boardrevision_str ;
                    $Cfg_Ptr = 1;
                    } else {
               		print ("Incorect product code entered \n");
            	}
            } else {
            		print ("Incorrect Serial number length entered\n");
            }

    	}
        $glc_fic_tlv_7_gbl = $glc_fic_tlv_7 . $glc_fic_sernumber_gbl ;
        &Print2XLog ("GLC FIC Serial number entered: $glc_fic_sernumber_gbl");
        unless ($Cfg_Ptr eq '') {
               $SN[$Cfg_Ptr] = $glc_fic_sernumber_gbl  ;
               $PN[$Cfg_Ptr] = "$glc_fic_partnumber_gbl Rev $glc_fic_revision_gbl";
               }

        foreach (0..1) {
        	unless ($SN[$_] eq '') {
            &Print_Log (1, "PN[$_] = $PN[$_], SN = $SN[$_]");
        	}
        }
        &Check_UUT_Ver();
        &Get_UUT_Variables();
        $Stats{'UUT_ID'} = $glc_sernumber_gbl;
       	#$Stats{'UUT_ID'} = $glc_fic_sernumber_gbl;
        &Stats::Update_All;




    return ();
}

#__________________________________________________________________________

sub XGLC_Program {
		# Subrotine Get_CPLD_data must be used prior to load $slot_gbl
      # Still to do 1) Get Slot from CPLD, 2) Cross check Product code to Part number
    my ( $Match, $Exclude ) = @_;
    my $PassFail = 'PASS';   # Used only by Sigmaprobe
        my $xglc_pcba_temp = "";
        my $xglc_type_str = '00 00 00 14 ' ;

        my $stoke_mac_assign = '00 12 73';
        my $xglc_mac_quan = ' 00 08 ';

        my $xglc_boardpartnumber_str = '';
        my $xglc_boardversion_str = '00 03 ';
        my $xglc_boardrevision_str = '00 01 ';

        my $xglc_pcba_partnumber = "01321|02041";
        #my $xglc_pcba_partnumber = "01321";

        my $xglc_product_code = "02[123]";   # these are the first three dig of the serial num

        # basic programming strings
        my $xglc_local_tlv_0 = "tlvwrite local 0 h ";
        my $xglc_global_tlv_0 = "tlvwrite global-slot2 0 h ";   # Fixed Slot number right now(Can get this from CPLD)
        my $xglc_local_tlv_7 = "tlvwrite local 7 s ";
        my $xglc_global_tlv_7 = "tlvwrite global-slot2 7 s ";  # Fixed Slot number right now(Can get this from CPLD)
        my $xglc_local_tlv_8 = "tlvwrite local 8 h ";
        my $xglc_global_tlv_8 = "tlvwrite global-slot2 8 h ";
        my $xglc_local_tlv_16 = "tlvwrite local 22 s ";
        my $xglc_global_tlv_16 = "tlvwrite global-slot2 22 s ";
        my $xglc_global_tlv_17 = "tlvwrite global-slot2 23 h 11 ";   #NPU1 = C0 (old), NPU0 = C0(Old)
        my $xglc_local_tlv_17 = "tlvwrite local 23 h 11 ";   #NPU1 = C0 (old), NPU0 = C0(Old)
        my $xglc_global_read_tlv_17 = "tlvread global-slot2 23 tlv ";   #NPU1 = C0 (old), NPU0 = C0(Old)
        my $xglc_local_read_tlv_17 = "tlvread local 23 tlv";   #NPU1 = C0 (old), NPU0 = C0(Old)




        # Globals to pass back to DAT
        # added to support I2C erase
        our $xglc_local_erase_gbl = "tlverase local";
        #our $xglc_global_erase_gbl = "tlvwrite global " . $slot_gbl . " 0 00";
        #our $xglc_global_erase_gbl = "tlverase global-slot2";
        our $xglc_global_erase_gbl = "tlverase global-slot2";

        our $xglc_local_tlv_0_gbl = "";
        our $xglc_global_tlv_0_gbl = "";
        our $xglc_local_tlv_7_gbl = "";
        our $xglc_global_tlv_7_gbl = "";
        our $xglc_local_tlv_8_gbl = "";
        our $xglc_global_tlv_8_gbl = "";
        our $xglc_global_tlv_16_gbl = ""; #Deviation
        our $xglc_local_tlv_16_gbl = ""; #Deviation

        our $xglc_sernumber_gbl = "";
        our $xglc_partnumber_gbl = "";
        our $xglc_revision_gbl = "";
        our $xglc_mac_gbl = "";
        our $xglc_MAC_tlv_8_verify_gbl = "";
        our $xglc_global_tlv_16_verify_gbl = ""; #Deviation

        my $answerok = "N";
        my($answer) = "" ;
        my(@fields) = "";

         $Cfg_Ptr = '';

        # get xglc partnumber
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan xglc Part number and Revision: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^PN//i;    # remove text
    		$answer =~ s/://g;    # remove text
    		($xglc_partnumber_gbl,$xglc_revision_gbl) = split(/rev/i,$answer);
    		$xglc_revision_gbl =~ s/ //g;     # remove spaces
    		$xglc_partnumber_gbl =~ s/ //g;     # remove spaces
    		if (($xglc_partnumber_gbl =~ /^[0-9]{5}-[0-9]{2}$/)&&($xglc_revision_gbl =~ /^[0-9]{2}$/)) {    # 5-2 digits required
    			if ($xglc_partnumber_gbl =~ /^$xglc_pcba_partnumber/) {
                    $answerok = "Y";
                    ($xglc_pcba_temp,$xglc_boardversion_str) = split("-", $xglc_partnumber_gbl);

            	} else {
               		print ("Incorect part number entered \n");
            	}
            } else {
            		print ("Incorrect part number length entered\n");
            }

    	}
        $xglc_boardversion_str = "00 " . sprintf("%02X",$xglc_boardversion_str);
        $xglc_boardrevision_str = " 00 " . sprintf ("%02X",$xglc_revision_gbl) ;
        &Print2XLog ("Part Number and Revision Entered: $xglc_partnumber_gbl Rev $xglc_revision_gbl");


        $answerok = "N";
        # get xglc Serial number
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan xglc Serial number: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^SN://;    # remove text
    		$answer =~ s/ //g;     # remove spaces
    		if ($answer =~ /^[0-9]{16}$/) {    # 16 digits required
    			if ($answer =~ /^$xglc_product_code/) {
                    $answerok = "Y";
                    $xglc_sernumber_gbl = $answer ;
                    	$xglc_local_tlv_0_gbl = $xglc_local_tlv_0 . $xglc_type_str . $xglc_boardversion_str .  $xglc_boardrevision_str ;
                    	$xglc_global_tlv_0_gbl = $xglc_global_tlv_0 . $xglc_type_str . $xglc_boardversion_str .  $xglc_boardrevision_str ;
                    	$xglc_tlv_0_verify_gbl =  $xglc_type_str . $xglc_boardversion_str .  $xglc_boardrevision_str ;
                    	$Cfg_Ptr = 0;
            	} else {
               		print ("Incorect product code entered \n");
            	}
            } else {
            		print ("Incorrect Serial number length entered\n");
            }

    	}
    	$xglc_local_tlv_7_gbl = $xglc_local_tlv_7 . $xglc_sernumber_gbl ;
        $xglc_global_tlv_7_gbl = $xglc_global_tlv_7 . $xglc_sernumber_gbl ;
        &Print2XLog ("xglc Serial number entered: $xglc_sernumber_gbl");
        unless ($Cfg_Ptr eq '') {
               $SN[$Cfg_Ptr] = $xglc_sernumber_gbl  ;
               $PN[$Cfg_Ptr] = "$xglc_partnumber_gbl Rev $xglc_revision_gbl";
               }
         $Cfg_Ptr = '';
        # get MAC
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan xglc MAC Address: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^MAC//i;    # remove text
    		$answer =~ s/ //g;     # remove spaces
    		$answer =~ s/:/ /g;     # sub : for <space>
    		$answer =~ s/\./ /g;     # sub . for <space>
    		$answer =~ s/([a-zA-Z0-9 ]{2})([a-zA-Z0-9 ]{2})([a-zA-Z0-9 ]{2})([a-zA-Z0-9 ]{2})([a-zA-Z0-9 ]{2})([a-zA-Z0-9 ]{2})/$1 $2 $3 $4 $5 $6/ if $answer =~ /^[a-zA-Z0-9]{12}$/;
       		if ($answer =~ /^[a-zA-Z0-9 ]{17}$/) {    # 5-2 digits required
    			if ($answer =~ /^$stoke_mac_assign/) {
                    $answerok = "Y";
                    $xglc_mac_gbl = $answer;
         				$xglc_local_tlv_8_gbl = $xglc_local_tlv_8 . $xglc_mac_gbl . $xglc_mac_quan ;     # global
        				$xglc_global_tlv_8_gbl = $xglc_global_tlv_8 . $xglc_mac_gbl . $xglc_mac_quan ;
        				$xglc_MAC_tlv_8_verify_gbl = $xglc_mac_gbl . $xglc_mac_quan ;

            	} else {
               		print ("Incorect MAC number entered($answer) \n");
            	}
            } else {
            		print ("Incorrect MAC number length entered($answer)\n");
            }

    	}

	   	&Print2XLog ("xglc MAC number entered: $xglc_MAC_tlv_8_verify_gbl");

        my ($MAC_Erc, $MAC_Erc_Msg) = &Log_MAC ($SN[0],$xglc_MAC_tlv_8_verify_gbl);
        &Log_MAC_Record ($SN[0],$xglc_MAC_tlv_8_verify_gbl);
        &Log_Error ($MAC_Erc_Msg) if ($MAC_Erc > 0);

         #$xglc_global_tlv_16_gbl = ""; #Deviation
#       $answerok = "Y";
#        print("\nOperator: Are there Deviations Applied?{y/N}\n");
#        $answerok = <STDIN>;
		print("\nOperator:Scan Deviations(press return to continue): ");
		chomp($answer = <STDIN>);

        until ($answer eq "") {

            $answer =~ s/^PN//i;    # remove text
            $answer =~ s/://g;    # remove text
            $answer =~ s/ //g;     # remove spaces
            $answer =~ s/ //g;     # remove spaces
            $xglc_global_tlv_16_verify_gbl = $xglc_global_tlv_16_verify_gbl . "," if $xglc_global_tlv_16_verify_gbl ne "";
            $xglc_global_tlv_16_verify_gbl  = $xglc_global_tlv_16_verify_gbl . $answer;
            &Print2XLog ("Deviations Entered: $xglc_global_tlv_16_verify_gbl");
            print("\nOperator:Scan Deviations(press return to continue): ");
            chomp($answer = <STDIN>);

#            print("\nOperator: Are there Deviations Applied?{Y/N<Return>}\n");
#            $answer = <STDIN>;
        }
        &Print2XLog ("Deviations Entered: $xglc_global_tlv_16_gbl");
        $xglc_local_tlv_16_gbl  = $xglc_local_tlv_16 . $xglc_global_tlv_16_verify_gbl;
        $xglc_global_tlv_16_gbl  = $xglc_global_tlv_16 . $xglc_global_tlv_16_verify_gbl;
        $xglc_global_tlv_16_verify_gbl = 0 if $xglc_global_tlv_16_verify_gbl eq "";
        foreach (0..1) {
        	unless ($SN[$_] eq '') {
            &Print_Log (1, "PN[$_] = $PN[$_], SN = $SN[$_]");
        	}
        }
        &Check_UUT_Ver();
        &Get_UUT_Variables();
        $Stats{'UUT_ID'} = $xglc_sernumber_gbl;
       	#$Stats{'UUT_ID'} = $xglc_fic_sernumber_gbl;
        &Stats::Update_All;




    return ();
}

#__________________________________________________________________________
sub IMC_Program {
      # Still to do 1) Get Slot from CPLD, 2) Cross check Product code to Part number
    my ( $Match, $Exclude ) = @_;

        # globals comming from cpld
       $imc_slot_address_gbl = "1";  # in Chassis

    	my $PassFail = 'PASS';   # Used only by Sigmaprobe
        my $imc_pcba_temp = "";
        my $fic_pcba_temp = "";
    	my $imc_type_str = '00 00 00 01 ';
        my $imc_fic_type_str = '00 00 00 09 ';
        my $imc_mmz_type_str = '00 00 00 0F ';

        $imc_slot_address_gbl = "0";  # in Chassis

        my $stoke_mac_assign = '00 12 73';


        my $imc_fic_boardpartnumber_str = '';
        my $imc_fic_boardversion_str = '00 03 ';
        my $imc_fic_boardrevision_str = '00 01 ';

        my $imc_mmz_boardpartnumber_str = '';
        my $imc_mmz_boardversion_str = '00 03 ';
        my $imc_mmz_boardrevision_str = '00 01 ';

        my $imc_boardpartnumber_str = '';
        my $imc_boardversion_str = '00 03 ';
        my $imc_boardrevision_str = '00 01 ';

        my $imc_pcba_partnumber = "00292";  # does not include the "-0x"
        my $imc_fic_pcba_partnumber = "00295";  # does not include the "-0x"
        my $imc_mmz_pcba_partnumber = "00375";  # does not include the "-0x"


        my $imc_product_code = "002";  # these are the first three dig of the serial num
        my $imc_fic_product_code = "003";    # these are the first three dig of the serial num
        my $imc_mmz_product_code = "006";    # these are the first three dig of the serial num

        # basic programming strings
        my $imc_U67_tlv_0 = "wr i2c u67 tlv 0 h ";
        my $imc_9501_tlv_0 = "wr i2c 9501 " . $imc_slot_address_gbl ." tlv 0 h ";   # Fixed Slot number right now(Can get this from CPLD)
        my $imc_U67_tlv_7 = "wr i2c U67 tlv 7 s ";
        my $imc_9501_tlv_7 = "wr i2c 9501 " . $imc_slot_address_gbl . " tlv 7 s ";  # Fixed Slot number right now(Can get this from CPLD)


        my $imc_fic_tlv_0 = "wr i2c fic tlv 0 h ";
        my $imc_fic_tlv_7 = "wr i2c fic tlv 7 s ";

        my $imc_mmz_tlv_0 = "wr mmz i2c tlv 0 h ";
        my $imc_mmz_tlv_7 = "wr mmz i2c tlv 7 s ";

        # Globals to pass back to DAT
        # added to support I2C erase
        our $imc_U67_erase_gbl = "wr i2c u67 1 00";
        our $imc_9501_erase_gbl = "wr i2c 9501 " . $imc_slot_address_gbl . " 1 00";
        our $imc_fic_erase_gbl = "wr i2c fic 1 00";
        our $imc_mmz_erase_gbl = "wr mmz i2c 1 00";

        our $imc_U67_tlv_0_gbl = "";
        our $imc_9501_tlv_0_gbl = "";
        our $imc_U67_tlv_7_gbl = "";
        our $imc_9501_tlv_7_gbl = "";

        our $imc_fic_tlv_0_gbl = "";
        our $imc_fic_tlv_7_gbl = "";
        our $imc_9501_tlv_0_rd_gbl = "rd i2c 9501 " . $imc_slot_address_gbl ." tlv 0";   # Fixed Slot number right now(Can get this from CPLD)
        our $imc_9501_tlv_7_rd_gbl = "rd i2c 9501 " . $imc_slot_address_gbl . " tlv 7";  # Fixed Slot number right now(Can get this from CPLD)


        our $imc_mmz_tlv_0_gbl = "";
        our $imc_mmz_tlv_7_gbl = "";


        our $imc_sernumber_gbl = "";
        our $imc_partnumber_gbl = "";
        our $imc_revision_gbl = "";
        our $imc_tlv_0_verify_gbl = "";
        our $imc_fic_tlv_0_verify_gbl = "";
        our $imc_mmz_tlv_0_verify_gbl = "";


        our $imc_fic_sernumber_gbl = "";
        our $imc_mmz_sernumber_gbl = "";

        my $answerok = "N";
        my($answer) = "" ;

        $Cfg_Ptr = '';

        # get imc partnumber
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan IMC Part number and Revision: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^PN//i;    # remove text
    		$answer =~ s/://g;    # remove text
    		($imc_partnumber_gbl,$imc_revision_gbl) = split(/rev/i,$answer);
    		$imc_revision_gbl =~ s/ //g;     # remove spaces

    		$imc_partnumber_gbl =~ s/ //g;     # remove spaces
    		if (($imc_partnumber_gbl =~ /^[0-9]{5}-[0-9]{2}$/)&&($imc_revision_gbl =~ /^[0-9]{2}$/)) {    # 5-2 digits required
    			if ($imc_partnumber_gbl =~ /^$imc2pt_pcba_partnumber|^$imc4pt_pcba_partnumber/) {
                    $answerok = "Y";
                    ($imc_pcba_temp,$imc_boardversion_str) = split("-", $imc_partnumber_gbl);

            	} else {
               		print ("Incorect part number entered \n");
            	}
            } else {
            		print ("Incorrect part number length entered\n");
            }

    	}
        $imc_boardversion_str = "00 " . sprintf ("%02X",$imc_boardversion_str);
        $imc_boardrevision_str = " 00 " . sprintf ("%02X",$imc_revision_gbl );
        &Print2XLog ("Part Number and Revision Entered: $imc_partnumber_gbl Rev $imc_revision_gbl");


        $answerok = "N";
        # get imc Serial number
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan IMC Serial number: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^SN://;    # remove text
    		$answer =~ s/ //g;     # remove spaces
    		if ($answer =~ /^[0-9]{16}$/) {    # 16 digits required
    			if ($answer =~ /^$imc_product_code/) {
                    $answerok = "Y";
                    $imc_sernumber_gbl = $answer ;

                    	$imc_U67_tlv_0_gbl = $imc_U67_tlv_0 . $imc_type_str . $imc_boardversion_str .  $imc_boardrevision_str ;
                    	$imc_9501_tlv_0_gbl = $imc_9501_tlv_0 . $imc_type_str . $imc_boardversion_str .  $imc_boardrevision_str ;
                    	$imc_tlv_0_verify_gbl =  $imc_type_str . $imc_boardversion_str .  $imc_boardrevision_str ;
                    	$Cfg_Ptr = 0;

            	} else {
               		print ("Incorect product code entered \n");
            	}
            } else {
            		print ("Incorrect Serial number length entered\n");
            }

    	}
    	$imc_U67_tlv_7_gbl = $imc_U67_tlv_7 . $imc_sernumber_gbl ;
        $imc_9501_tlv_7_gbl = $imc_9501_tlv_7 . $imc_sernumber_gbl ;
        &Print2XLog ("IMC Serial number entered: $imc_sernumber_gbl");
         unless ($Cfg_Ptr eq '') {
         	   $SN[$Cfg_Ptr] = $imc_sernumber_gbl ;
               $PN[$Cfg_Ptr] = "$imc_partnumber_gbl Rev $imc_revision_gbl";
               }

         $Cfg_Ptr = '';
        # get FIC partnumber
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan FIC Part number and Revision: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^PN//i;    # remove text
    		$answer =~ s/://g;    # remove text
    		($imc_fic_partnumber_gbl,$imc_fic_revision_gbl) = split(/rev/i,$answer);
    		$imc_fic_revision_gbl =~ s/ //g;     # remove spaces
    		$imc_fic_partnumber_gbl =~ s/ //g;     # remove spaces
    		if (($imc_fic_partnumber_gbl =~ /^[0-9]{5}-[0-9]{2}$/) &&($imc_fic_revision_gbl =~ /^[0-9]{2}$/)) {    # 5-2 digits required
    			if ($imc_fic_partnumber_gbl =~ /^$imc_fic_pcba_partnumber/) {
                    $answerok = "Y";
                    ($fic_pcba_temp,$imc_fic_boardversion_str) = split("-", $imc_fic_partnumber_gbl);

            	} else {
               		print ("Incorect part number entered \n");
            	}
            } else {
            		print ("Incorrect part number length entered\n");
            }

    	}
        $imc_fic_boardversion_str = "00 " . sprintf ("%02X",$imc_fic_boardversion_str);
        $imc_fic_boardrevision_str = " 00 " . sprintf ("%02X",$imc_fic_revision_gbl) ;
        &Print2XLog ("Part Number and Revision Entered: $imc_fic_partnumber_gbl Rev $imc_fic_revision_gbl");


        $answerok = "N";
        $answer = "" ;
        # get FIC Serial number
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan FIC Serial number: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^SN://;    # remove text
    		$answer =~ s/ //g;     # remove spaces
    		if ($answer =~ /^[0-9]{16}$/) {    # 16 digits required
    			if ($answer =~ /^$imc_fic_product_code/) {
                    $answerok = "Y";
                    $imc_fic_sernumber_gbl = $answer ;
                    $imc_fic_tlv_0_gbl = $imc_fic_tlv_0 . $imc_fic_type_str . $imc_fic_boardversion_str . $imc_fic_boardrevision_str ;
                    $imc_fic_tlv_0_verify_gbl =  $imc_fic_type_str . $imc_fic_boardversion_str . $imc_fic_boardrevision_str ;
                    $Cfg_Ptr = 1;
                    } else {
               		print ("Incorect product code entered \n");
            	}
            } else {
            		print ("Incorrect Serial number length entered\n");
            }

    	}
        $imc_fic_tlv_7_gbl = $imc_fic_tlv_7 . $imc_fic_sernumber_gbl ;
        &Print2XLog ("IMC FIC Serial number entered: $imc_fic_sernumber_gbl");
        unless ($Cfg_Ptr eq '') {
                 $SN[$Cfg_Ptr] = $imc_fic_sernumber_gbl ;
               $PN[$Cfg_Ptr] = "$imc_fic_partnumber_gbl Rev $imc_fic_revision_gbl";
               }

         $Cfg_Ptr = '';
        # get mmz partnumber
        $answerok = "N";
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan MicMezz Part number and Revision: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^PN//i;    # remove text
    		$answer =~ s/://g;    # remove text
    		($imc_mmz_partnumber_gbl,$imc_mmz_revision_gbl) = split(/rev/i,$answer);
    		$imc_mmz_revision_gbl =~ s/ //g;     # remove spaces
    		$imc_mmz_partnumber_gbl =~ s/ //g;     # remove spaces
    		if (($imc_mmz_partnumber_gbl =~ /^[0-9]{5}-[0-9]{2}$/) &&($imc_mmz_revision_gbl =~ /^[0-9]{2}$/)) {    # 5-2 digits required
    			if ($imc_mmz_partnumber_gbl =~ /^$imc_mmz_pcba_partnumber/) {
                    $answerok = "Y";
                    ($mmz_pcba_temp,$imc_mmz_boardversion_str) = split("-", $imc_mmz_partnumber_gbl);

            	} else {
               		print ("Incorect part number entered \n");
            	}
            } else {
            		print ("Incorrect part number length entered\n");
            }

    	}
        $imc_mmz_boardversion_str = "00 " . sprintf ("%02X",$imc_mmz_boardversion_str);
        $imc_mmz_boardrevision_str = " 00 " . sprintf ("%02X",$imc_mmz_revision_gbl );
        &Print2XLog ("Part Number and Revision Entered: $imc_mmz_partnumber_gbl Rev $imc_mmz_revision_gbl");


        $answerok = "N";
        $answer = "" ;
        # get mmz Serial number
    	until ($answerok =~ /Y/) {
    		print("\nOperator:Scan MicMezz Serial number: ");
    		chomp($answer = <STDIN>);
    		$answer =~ s/^SN://;    # remove text
    		$answer =~ s/ //g;     # remove spaces
    		if ($answer =~ /^[0-9]{16}$/) {    # 16 digits required
    			if ($answer =~ /^$imc_mmz_product_code/) {
                    $answerok = "Y";
                    $imc_mmz_sernumber_gbl = $answer ;
                    $imc_mmz_tlv_0_gbl = $imc_mmz_tlv_0 . $imc_mmz_type_str . $imc_mmz_boardversion_str . $imc_mmz_boardrevision_str ;
                    $imc_mmz_tlv_0_verify_gbl =  $imc_mmz_type_str . $imc_mmz_boardversion_str . $imc_mmz_boardrevision_str ;
                    $Cfg_Ptr = 2;
                    } else {
               		print ("Incorect product code entered \n");
            	}
            } else {
            		print ("Incorrect Serial number length entered\n");
            }

    	}
        $imc_mmz_tlv_7_gbl = $imc_mmz_tlv_7 . $imc_mmz_sernumber_gbl ;
        &Print2XLog ("IMC mmz Serial number entered: $imc_mmz_sernumber_gbl");
        unless ($Cfg_Ptr eq '') {

               $SN[$Cfg_Ptr] = $imc_mmz_sernumber_gbl ;
               $PN[$Cfg_Ptr] = "$imc_mmz_partnumber_gbl Rev $imc_mmz_revision_gbl";
               }

        foreach (0..2) {
        	unless ($SN[$_] eq '') {
            &Print_Log (1, "PN[$_] = $PN[$_], SN = $SN[$_]");
        	}
        }
        &Check_UUT_Ver();
        &Get_UUT_Variables();
        $Stats{'UUT_ID'} = $imc_sernumber_gbl;
       	#$Stats{'UUT_ID'} = $imc_fic_sernumber_gbl;
       	#$Stats{'UUT_ID'} = $imz_mmz_sernumber_gbl;
        &Stats::Update_All;


    return ();
}

#_____________________________________________________________________________
sub Get_Event_entry {    #in development # # look the pass fail for the last test entry by serial
      my ($serial_search) = @_;
      my $return_logfile = 'none' ;
      my $LastRecord = 'none';
      my @CFG_timestamp = ();
      my @CFG_timestamp_uniq = ();
      my @CFG_timestamp_uniq_sort = ();
      my @Event_Entry_Not_Sorted = ();
      my $Event_Record = "";
        #Evet.log     # 0 1    2        3      4    5       6         7      8      9    10
        # 1;Date;Location;HostID;OpID;Part_No;Serial_No;TestID;Result;Data;LogFilePtr;
      my ($RecType, $TimeStamp, $Location, $HostID, $OpID, $Part, $Parent_SN, $TestID, $Result, $Data, $LogFileP) = "";
       my %seen = ();
    foreach (@CFG_Entrys) {
      	/^2;(\d{10});.*;.*;.*;.*;.*;.*;.*/;
      	push (@CFG_timestamp, $1);  #push only uniq time stamps
       }

	@CFG_timestamp_uniq = grep { ! $seen{$_} ++ } @CFG_timestamp; #uniq entrirys only
	@CFG_timestamp_uniq_sort = sort {$a cmp $b } @CFG_timestamp_uniq;   # keep same order as Event log

	warn "LogPath = >$LogPath<" if $Debug;
    open (FH, "<$LogPath/Event.log") or die "Can\'t open Event log";

    $TimeStampRet = 0; $Parent_SN = 0;
    while (<FH>) {
        #next if $_ !~ /1;\d{10};\w+;\w+-\w+;\w+;\d{5}-\d{2}\sRev\s\d{2};\w{16};\w+;\w+;\w+;.*;/;
        next if $_ !~ /^1;\d{10};\w+;.*;\w+;\d{5}-\d{2}\sRev\s\d{2};\w{16};\w+;\w+;.*/;
        $Event_Record = $_;
        #print (" $Event_Record \n");
        ($RecType, $TimeStamp, $Location, $HostID, $OpID, $Part, $Parent_SN, $TestID, $Result, $Data, $LogFileP) = split (/\;/);
        my $itemfound = 0;
        foreach (@CFG_timestamp_uniq_sort) {
        	if ( /$TimeStamp/) {
        	   push (@Event_Entry_Not_Sorted,$Event_Record);
        	   delete $CFG_timestamp_uniq_sort[$i]; #Remove a found record
        	   $TimeStampRet = $TimeStamp;
        	   $itemfound++;
         	}
       	}
    	if ( ($Parent_SN =~ $serial_search) and ($itemfound == 0)) {
        	 push (@Event_Entry_Not_Sorted,$Event_Record);
        	 #print ("Found $serial_search Serial number $Serial at line $. for Parent SN $Parent_SN \n");
        	 $TimeStampRet = $TimeStamp;
        }
     }
    @Event_Entrys = reverse sort {$a cmp $b } @Event_Entry_Not_Sorted;   # put newest records at the top
    #print ("@Event_Entry\n");
       if ($TimeStampRet eq 0) {
		if (($Debug_UUT || $Development))  {
       		&Print2XLog("Warning: No Event Entry found for : $serial_search\n");
    	} else {
      		&Log_Error ("No Event Entry found for : $serial_search\n");
    	}
    }
    close FH;
    return ($TimeStampRet);
}

#_____________________________________________________________________________
sub Get_Cfg_entry { #Search for Serial numbers and add to @CFG_Entry
    my ($serial_search) = @_;
    my $return_logfile = 'none' ;
    my $LastRecord = 'none';
    my @CFG_Entry_Not_Sorted = ();
	warn "LogPath = >$LogPath<" if $Debug;

    open (FH, "<$LogPath/Cfg.log") or die "Can\'t open $LogPath/Cfg log";

         # 0 		1    		2         3       4      5                6         7           8
        # 2;		Date	  ;Location;  HostID; OpID;  Master_Serial_No;Slot#;    Part Number;Serial Number;
    my ($RecType, $TimeStamp, $Location, $HostID, $OpID, $Parent_SN,      $Slot_Num, $Part,     $Serial) = "";
    $TimeStampRet = 0; $Parent_SN = 0;
    while (<FH>) {
    	($RecType, $TimeStamp, $Location, $HostID, $OpID, $Parent_SN, $Slot_Num, $Part, $Serial) = split (/\;/);
        #Only Valid records
        next if $_ !~ /^2;\d{10};\w+;.*;\w+;\w{16};\d{1,2};\d{5}-\d{2}\sRev\s\d{2};\w{16}/;
        if ( $Serial =~ $serial_search) {
        	push (@CFG_Entry_Not_Sorted,$_);
        	$TimeStampRet = $TimeStamp;
         }
     }
    # Sort
    @CFG_Entrys = reverse sort {$a cmp $b } @CFG_Entry_Not_Sorted;   # put newest records at the top
    if ($TimeStampRet eq 0) {
		if (($Debug_UUT || $Development))  {
       		&Print2XLog("Warning: No CFG log entry for SN: $serial_search\n");
    	} else {
      		#&Log_Error ("No log entry for SN: $serial_search\n");
      		&Print2XLog("Warning: No CFG log entry for SN: $serial_search\n");
    	}
    }
    close FH;
    return ($TimeStampRet);
}

#_____________________________________________________________________________
sub Get_Test_status {    # Searches for entrys in the CFG_Entry and Event_Entry lists built by &Get_Event_Entry,&Get_CFG_Entry
      my ($serial_search,$Test_step) = @_;
      my $TestStatus = "null" ;
      my $TimeStampRet = '';
      #CFG
         # 0 		1    		2         3       4      5                6         7           8
        # 2;		Date	  ;Location;  HostID; OpID;  Master_Serial_No;Slot#;    Part Number;Serial Number;
     #Event
      # 0 1    2        3      4    5       6         7      8      9    10
        # 1;Date;Location;HostID;OpID;Part_No;Serial_No;TestID;Result;Data;LogFilePtr;
      my ($RecType, $TimeStamp, $Location, $HostID, $OpID, $Parent_SN,      $Slot_Num, $Part,     $Serial) = "";
      my (  $TestID, $Result, $Data, $LogFileP) = "";
      my $TestDataRet = '';
      my $itemfound = 0;
      foreach (@CFG_Entrys) {
        ($RecType, $TimeStamp, $Location, $HostID, $OpID, $Parent_SN, $Slot_Num, $Part, $Serial) = split (/\;/);
        print ("Get_Test_Status CFG entry $_ for Ser $serial_search to match $Serial\n") if $Debug;
        if ( $Serial =~ /$serial_search/) {
        	print ("Get_Test_Status CFG $serial_search match\n") if $Debug;
           $TimeStampRet = $TimeStamp;
           foreach (@Event_Entrys) {
           	($RecType, $TimeStamp, $Location, $HostID, $OpID, $Part, $Parent_SN, $TestID, $Result, $Data, $LogFileP) = split (/\;/);
        	$TestDataRet = $Parent_SN . ';' . $Location . ';' . $HostID . ';' . $OpID . ';' . $Part . ';' . $TestID;
          	if ( ($TimeStampRet =~ /$TimeStamp/) && ($TestID =~ /$Test_step/)) {
        		$TestStatus = $Result;
        	   	print ("Found $TimeStamp match at Event Record $_ \n") if $Debug;
        	   	$TimeStampRet = $TimeStamp;
        	   	$itemfound++;
        	   	last;
         	}
         	last if $itemfound;   # get out of loop
           }
       	}
       	last if $itemfound; #get out of loop
      }
    	if ( $itemfound == 0) {
    	   print ("Not found in CFG Log, Doing an Event Log Search...\n")  if $Debug;
           # Do a serial number search
           foreach (@Event_Entrys) {
           ($RecType, $TimeStamp, $Location, $HostID, $OpID, $Part, $Parent_SN, $TestID, $Result, $Data, $LogFileP) = split (/\;/);
           $TestDataRet = $Parent_SN . ';' . $Location . ';' . $HostID . ';' . $OpID . ';' . $Part . ';' . $TestID;
           if ( ($Parent_SN =~ $serial_search) && ($TestID =~ /$Test_step/)) {
        	  $TestStatus = $Result;
        	  $TimeStampRet = $TimeStamp;
        	  $itemfound++;
        	  last;
           }
        }
        if ($itemfound == 0) {
           $TimeStampRet = "1";
           $TestStatus = "NotFound"
        }

        }
    return ($TimeStampRet,$TestStatus,$TestDataRet);
}

#_____________________________________________________________________________
sub Verify_Chassis_LED {
	my ( $display) = @_;

    my %prompt = (
    	Verify_Chassis_LED_FAN1_3V3_GREEN, "Verify Fan 1 3.3V is Green",
    	Verify_Chassis_LED_FAN1_3V3_RED, "Verify Fan 1 3.3V is Red",
    	Verify_Chassis_LED_FAN1_OK_GREEN, "Verify Fan 1 OK is Green",
    	Verify_Chassis_LED_FAN1_OK_RED, "Verify Fan 1 OK is Red",
    	Verify_Chassis_LED_FAN2_3V3_GREEN, "Verify Fan 2 3.3V is Green",
    	Verify_Chassis_LED_FAN2_3V3_RED, "Verify Fan 2 3.3V is Red",
    	Verify_Chassis_LED_FAN2_OK_GREEN, "Verify Fan 2 OK is Green",
    	Verify_Chassis_LED_FAN2_OK_RED, "Verify Fan 2 OK is Red",
    	Verify_Chassis_LED_ALARM1_CRITICAL_ALARM, "Verify Alarm 1 Critical LED is RED",
    	Verify_Chassis_LED_ALARM1_MAJOR_ALARM, "Verify Alarm 1 Major LED is RED",
    	Verify_Chassis_LED_ALARM1_MINOR_ALARM, "Verify Alarm 1 Minor LED is Amber",
    	Verify_Chassis_LED_ALARM1_ACO_OFF, "Verify Alarm 1 Blue ACO LED remains off when ACO button pushed",
    	Verify_Chassis_LED_ALARM1_ACO_ON, "Verify Alarm 1 Blue ACO LED on after ACO button pushed",
    	Verify_Chassis_LED_ALARM1_OFF, "Verify Alarm 1 All LEDs off",
    	Verify_Chassis_LED_ALARM2_CRITICAL_ALARM, "Verify Alarm 2 Critical LED is RED",
    	Verify_Chassis_LED_ALARM2_MAJOR_ALARM, "Verify Alarm 2 Major LED is RED",
    	Verify_Chassis_LED_ALARM2_MINOR_ALARM, "Verify Alarm 2 Minor LED is Amber",
    	Verify_Chassis_LED_ALARM2_ACO_OFF, "Verify Alarm 2 Blue ACO LED remains off when ACO button pushed",
    	Verify_Chassis_LED_ALARM2_ACO_ON, "Verify Alarm 2 Blue ACO LED on after ACO button pushed",
    	Verify_Chassis_LED_ALARM2_OFF, "Verify Alarm 2 All LEDs off",
    	Verify_Chassis_LED_PEM1_LED_GREEN, "Verify PEM 1 OK and 3.3V LEDs are GREEN",
    	Verify_Chassis_LED_PEM1_LED_RED, "Verify PEM 1 OK and 3.3V LEDs are RED",
    	Verify_Chassis_LED_PEM2_LED_GREEN, "Verify PEM 2 OK and 3.3V LEDs are GREEN",
    	Verify_Chassis_LED_PEM2_LED_RED, "Verify PEM 2 OK and 3.3V LEDs are RED",
    	Verify_Chassis_LED_All_POWER_OFF, "Verify PEM Breaker(s) are in the OFF state and All Chassis POwer is off"
    );
    if ($prompt{$display} eq '') {
    	&Log_Error("$display returned null in Verify_Chassis_LED()");
    }
    my($answer) = "" ;
    until ($answer =~ /^[YyNn]/) {
    		print("\nOperator:$prompt{$display}: Y/N\n");
    		print("Enter Yes or No: ");
    		$answer = <STDIN>;
    		}
	&Print2XLog ("Operator:$prompt{$display}(Y,N): $answer");
    if ($answer =~ /^[Nn]/)  {
    	&Log_Error ("Failed: $prompt{$display}");
    }
    return ();
}

#__________________________________________________________________________

sub Verify_LED_RED {
	my ( $display) = "RED"; # @_;

    my($answer) = "" ;
    until ($answer =~ /^[YyNn]/) {
    		print("\nOperator:Verify Status LEDs are $display: Y/N\n");
    		print("Enter Yes or No: ");
    		$answer = <STDIN>;
    		}
	&Print2XLog ("Operator:Verify Status LEDs are $display(Y,N): $answer");
    if ($answer =~ /^[Nn]/)  {
    	&Log_Error ("LED Failed to be $display");
    }
    return ();
}

#__________________________________________________________________________
sub Verify_LED_GREEN {
	my ( $display) = "GREEN";  #@_;

    my($answer) = "" ;
    until ($answer =~ /^[YyNn]/) {
    		print("\nOperator:Verify Status LEDs are $display: Y/N\n");
    		print("Enter Yes or No: ");
    		$answer = <STDIN>;
    		}
	&Print2XLog ("Operator:Verify Status LEDs are $display(Y,N): $answer");
    if ($answer =~ /^[Nn]/)  {
    	&Log_Error ("LED Failed to be $display");
    }
    return ();
}

#__________________________________________________________________________
sub Verify_GLCPortLED {
	my ( $display) = "GREEN";  #@_;

    my($answer) = "" ;
    until ($answer =~ /^[YyNn]/) {
    		print("\nOperator:Verify PORT LEDs are $display: Y/N\n");
    		print("Enter Yes or No: ");
    		$answer = <STDIN>;
    		}
	&Print2XLog ("Operator:Verify PORT LEDs are $display(Y,N): $answer");
    if ($answer =~ /^[Nn]/)  {
    	&Log_Error ("LED Failed to be $display");
    }
    return ();
}
#__________________________________________________________________________
sub XML_Header {    #        Header information for XML File
                     #


         my $fh;
         open ($fh, ">>$Out_File") || &Exit (3, "Can't open $Out_File for cat");
         print $fh "  \<Test_Head\> ", '_' x 80, "\n" ;
         print $fh "		\<Startdate\>" . &PT_Date(time,2) . "</Startdate>\n";
         print $fh "		\<UserID>$Stats{'UserID'}</UserID>\n";
         print $fh "		\<Host_ID\>$Stats{'Host_ID'}</Host_ID>\n";
         print $fh "		\<Session\>$Stats{'Session'}</Session>\n";
         print $fh "		\<TID\>$TestData{'TID'}</TID>\n";
         print $fh "  <\/Test_Head\>\n";


         close $fh;


}
#_____________________________________________________________________________

sub XML_Tail {    #        Tail information for XML File
                     #


         my $fh;
         open ($fh, ">>$Out_File") || &Exit (3, "Can't open $Out_File for cat");
         print $fh "  \<Test_Tail\> ", '_' x 80, "\n" ;
         print $fh "		<Runtime Units=\"secs\">$TestData{'TTT'}</Runtime>\n";
         print $fh "		\<Enddate\>" . &PT_Date(time,2) . "</Enddate>\n";
         print $fh "		\<TD-TEC>$TestData{'TEC'}</TD-TEC>\n";
         print $fh "		\<Result\>$Stats{'Result'}</Result>\n";
         print $fh "  <\/Test_Tail\>\n";


         close $fh;


}
#_____________________________________________________________________________
sub Print_Order_Data {
      my ($serial_search) = @_;
      my $return_logfile = 'none' ;
      my $LastRecord = 'none';


	warn "LogPath = >$LogPath<" if $Debug;

    open (FH, "<$LogPath/Event.log") or die "Can\'t open Event log";

        # 0 1    2        3      4    5       6         7      8      9    10
        # 1;Date;Location;HostID;OpID;Part_No;Serial_No;TestID;Result;Data;LogFilePtr;

    my $i = 0;
    while (<FH>) {

        my $Msg = '';

        $i++;
        my ($RecType, $Date, $Location, $HostID, $OpID, $PN, $SN, $TestID, $Result, $Data, $LogFileP) = split (/\;/);

        next if $RecType != 1;
        next if $TestID ne 'SHIP';
        #print ("Found Serial $SN testid $TestID Result $Result Rectype $RecType\n") if $TestID eq 'SHIP';
        #next if $Result ne 'PASS';
        if (  $RecType eq 1 and  $TestID eq 'SHIP' and  $Result eq 'PASS' and $SN eq $serial_search) {
        	$LastRecord =  $Result;
        	$return_logfile = $LogFileP   ;
        	#print ("Found a PASS logfile $LogFileP  \n");
        } elsif (  $RecType eq 1 and  $TestID eq 'SHIP' and  $Result ne 'PASS' and $SN eq $serial_search) {
        	$return_logfile = 'fail';

        }

     }
    &Log_Error("No log entry for SN: $SN[0]\n") if $return_logfile eq 'none';
    &Log_Error("Last test Entry for $SN[0] did not pass\n") if $return_logfile eq 'fail';
    #print ("Found File $return_logfile i = $i for serial number $serial_search\n");
    close FH;
    return ($return_logfile);
}


#________________________________________________________________________________
sub Print_ShowMFG_Data {    #        Get information from XML File
    my @mfg_config = ();
    #my @show_ver = ();
    my $Config_log = "$Tmp/Config.log";
    my $XML_log = 'none';
    my $configrpt;
    my $answerok = "n";
    my $result = "none";

    my $Tag_data_count = @mfg_config;
    #my $Printer = "mfg-prt1";
    if ($TestData{'TEC'} > 0) {
    	print("Test log not printed due to test errors\n");
    	return ;
    }
    return if $Printer eq "none";

  if ($TestData{'TID'} eq 'SO') {
    	$XML_log = "$LogPath/logfiles/" . Print_Order_Data($SN[0]);
    	 #print ("Found XML File $XML_log\n");
   } else {
        $XML_log = $Out_File; # current open XML file
    }

    open ($configrpt,">>$Config_log") || die "Can't find valid $Config_log";
      #Add Header information
    print $configrpt "\n\n\n";
    printf $configrpt "\tStoke Chassis Test Report.  %s \n",&PT_Date(time, 0);

    if ($TestData{'TID'} eq 'SO' and $SN[1] ne '') {
            printf $configrpt  "\tWork Order: $PN[1],  Sales Order: $SN[1]\n\n";
     }

    XML_Get_Data("ShowMFG",\@mfg_config, 1, $XML_log);

    print ("Tag Data Count = $Tag_data_count\n") if $Debug;
   	# flush a file to disk  select((select(OUTPUT_HANDLE), $| = 1)[0]);
    foreach (@mfg_config) {
    	print ("Writing to log $_\n") if $Debug;
           	# Add any formatting here
           	print $configrpt $_ . "\n";
           }

    XML_Get_Data("show_ver_slot_0",\@show_ver, 1, $XML_log);
    foreach (@show_ver) {
          	print ("Writing to log $_\n") if $Debug;
           	# Add any formatting here
           	print $configrpt $_ . "\n";
           }

     &Stats::Update_All;
    # Add Trailer information
    print $configrpt "\n\n";
    printf $configrpt "\tTest System: %s:%s User: %s TID %s\n\n",$Stats{'Host_ID'}, $Stats{'Session'}, $Stats{'UserID'} , $TestData{'TID'};
       if ($TestData{'TID'} eq 'SO' and $SN[1] ne '') {
             printf $configrpt  "\tConfiguration Log File:\n";
            printf $configrpt  "\t $XML_log \n\n";
    }

    if  ($Stats{'Result'} eq "INCOMPLETE") {
    	$result = "PASS"   if $Stats{'Result'} ne 'FAIL'   ;  #  Have to do this if run before the is finished.
    } elsif ($TestData{'TID'} eq 'SO') { #if called during an order only pass records are pulled
       $result = 'PASS';
    } else {
    	$result = $Stats{'Result'}    ;  #  Have to do this if run before the is finished.
    }
    printf $configrpt "\tResult: %s %s  Diag Version: %s\n\n", $result, $Stats{'Status'}, $TestData{'Ver'};

    close $configrpt;



    if ($Printer ne "noprint")  {
    	$answerok = "x";
    	until ($answerok =~ /^[Y,y,N,n]/) {
    		print("\nOperator:Do you want to print a copy of the configuration?: ");
    		chomp($answerok = <STDIN>);
    	}
       if ($answerok =~ /^[Y,y]/) {
       		if (system "lp -o length=75 -o width=100 -o cpi=12 -d $Printer $Config_log"  ) {
          		&Log_Error ("Configuration Report Print Failed: $Printer $Config_log \n");
       		} else {
         		print ("Configuration Report Printed\n");
            }
       }
    } else {
      			print ("No print requested\n");
    }
          #END Print Area - to be moved
          #$xml_get_fail = 0 if $tag_true ;  # Return 0 if no closing tag else return count
          #return ($xml_get_fail);




}

#_______________________________________________________________________________
sub Print_Config_Data {    #        Get information from XML File
    my @mfg_config = ();
    #my @show_ver = ();
    my $Config_log = "$Tmp/Config.log";
    my $XML_log = 'none';
    my $configrpt;
    my $answerok = "n";
    my $result = "none";

    my $Tag_data_count = @mfg_config;
    #my $Printer = "mfg-prt1";
    if ($TestData{'TEC'} > 0) {
    	print("Configuration log not printed due to test errors\n");
    	return ;
    }
    return if $Printer eq "none";

  if ($TestData{'TID'} eq 'SO') {
    	$XML_log = "$LogPath/logfiles/" . Print_Order_Data($SN[0]);
    	 #print ("Found XML File $XML_log\n");
   } else {
        $XML_log = $Out_File; # current open XML file
    }

    open ($configrpt,">>$Config_log") || die "Can't find valid $Config_log";
      #Add Header information
    print $configrpt "\n\n\n";
    printf $configrpt "\tStoke Configuration Report.  %s \n",&PT_Date(time, 0);

    if ($TestData{'TID'} eq 'SO' and $SN[1] ne '') {
            printf $configrpt  "\tWork Order: $PN[1],  Sales Order: $SN[1]\n\n";
     }

    XML_Get_Data("show_hardware",\@mfg_config, 1, $XML_log);

    print ("Tag Data Count = $Tag_data_count\n") if $Debug;
   	# flush a file to disk  select((select(OUTPUT_HANDLE), $| = 1)[0]);
    foreach (@mfg_config) {
    	print ("Writing to log $_\n") if $Debug;
           	# Add any formatting here
           	print $configrpt $_ . "\n";
           }

    XML_Get_Data("show_ver_slot_0",\@show_ver, 1, $XML_log);
    foreach (@show_ver) {
          	print ("Writing to log $_\n") if $Debug;
           	# Add any formatting here
           	print $configrpt $_ . "\n";
           }

     &Stats::Update_All;
    # Add Trailer information
    print $configrpt "\n\n";
    printf $configrpt "\tTest System: %s:%s User: %s TID %s\n\n",$Stats{'Host_ID'}, $Stats{'Session'}, $Stats{'UserID'} , $TestData{'TID'};
       if ($TestData{'TID'} eq 'SO' and $SN[1] ne '') {
             printf $configrpt  "\tConfiguration Log File:\n";
            printf $configrpt  "\t $XML_log \n\n";
    }

    if  ($Stats{'Result'} eq "INCOMPLETE") {
    	$result = "PASS"   if $Stats{'Result'} ne 'FAIL'   ;  #  Have to do this if run before the is finished.
    } elsif ($TestData{'TID'} eq 'SO') { #if called during an order only pass records are pulled
       $result = 'PASS';
    } else {
    	$result = $Stats{'Result'}    ;  #  Have to do this if run before the is finished.
    }
    printf $configrpt "\tResult: %s %s  Diag Version: %s\n\n", $result, $Stats{'Status'}, $TestData{'Ver'};

    close $configrpt;



    if ($Printer ne "noprint")  {
    	$answerok = "x";
    	until ($answerok =~ /^[Y,y,N,n]/) {
    		print("\nOperator:Do you want to print a copy of the configuration?: ");
    		chomp($answerok = <STDIN>);
    	}
       if ($answerok =~ /^[Y,y]/) {
       		if (system "lp -o length=75 -o width=100 -o cpi=12 -d $Printer $Config_log"  ) {
          		&Log_Error ("Configuration Report Print Failed: $Printer $Config_log \n");
       		} else {
         		print ("Configuration Report Printed\n");
            }
       }
    } else {
      			print ("No print requested\n");
    }
          #END Print Area - to be moved
          #$xml_get_fail = 0 if $tag_true ;  # Return 0 if no closing tag else return count
          #return ($xml_get_fail);




}

#_______________________________________________________________________________
sub Send_Email {       # Send Emails for notification
	my $Config_log = "$Tmp/Config.log";
	my $Event_log = "$Tmp/Event.log $Tmp/Cfg.log";
	my $File = $PPath . '/uutcfg/' . $Product_gbl . '/' .$Location.'_email.cfg'; # Development Path g'
    #my $File = $PPath . '/uutcfg/'.$Location.'_email.cfg'; # Development Path
   #my $File = '/usr/local/cmtest/'.$Location.'_email.cfg'; # Development Path
    #my $File = '/usr/local/cmtest/parts.cfg';
    my $msg = '';
       #	;Print_Out_XML_Tag
    if ($Email_Notification == 1 ) {
    	    if  (&Read_Data_File ($File)) {
        		return "Can\'t read data file $File for email configuration";
    		}
    	if   (($TestData{'TID'} eq 'SHIP' or $TestData{'TID'} eq 'SO') and $SN[1] ne '' and $Stats{'Result'} eq 'PASS' ) {
        	if ($TestData{'TID'} eq 'SO' and $SN[1] ne '') {
        		$msg = "cat $Config_log \| Mail -c \"$Email_Config_CC\" -s \"$Location:$Stats{'Host_ID'} MFG System shipped \`date\` \" \"@Email_Config\" ";
        	} else {
        		$msg = "cat $Config_log \| Mail -c \"$Email_Ship_CC\" -s \"$Location:$Stats{'Host_ID'} MFG System shipped \`date\` \" \"@Email_Ship\" ";
        	}
        	print $msg if $Debug;
        	print ("Email Sent: with $Config_log\n");
        	system "$msg";
        	}

    	if   (($TestData{'TID'} eq 'SHIP' or $TestData{'TID'} eq 'SO') and $SN[1] ne '' and $Stats{'Result'} eq 'PASS' ) {
        	if ($TestData{'TID'} eq 'SO' and $SN[1] ne '') {
        		$msg = "cat $Event_log \| Mail -s \"$Location:$Stats{'Host_ID'} MFG System shipped Records \`date\` \" \"@Email_Config_Records\" ";
        	} else {
        		$msg = "cat $Event_log \| Mail -s \"$Location:$Stats{'Host_ID'} MFG System shipped Records \`date\` \" \"@Email_Ship_Records\" ";
        	}
        	print $msg if $Debug;
        	print ("Record Email Sent: with $Event_log\n");
        	system "$msg";
        	}
       }
        # Else
         #add more tests later
  	  	#system (cat $Config_log | Mail -c "" -s "MFG System shipped `date`" "joe@stoke.com,white222@sbcglobal.net );
        #print 'system cat $Config_log | Mail -c "" -s "MFG System shipped `date`" "joe@stoke.com,white222@sbcglobal.net"; ';
#        my $msg = MIME::Lite->new(
#        From    => 'mfg@stoke.com',
#        To      => 'joe@stoke.com',
#        Cc      => '',
#        Subject => 'MFG System Shipped',
#        Type    => 'multipart/mixed',
#        );

#        $msg->attach(
#        Type     => 'TEXT',
#        Data     => "Here's the GIF file you wanted",
#        );

#        $msg->attach(
#        Type     => 'image/gif',
#        Path     => 'aaa000123.gif',
#        Filename => 'logo.gif',
#        );

#        $msg->send;


}
#_____________________________________________________________________________
sub XML_Get_Data {    #        Get information from XML File
          my ($Tag, $Tag_data_ref, $instance,$XML_log) = @_;
         #$Out_File = Defaul XML file for session
         my $tag_true = 0;
         my $Xml_file;
         my $Tag_data_count;
         #my $xml_get_fail = 0;
         my $count = 0;

         $XML_log = $Out_File if ($XML_log eq 'None' or $XML_log eq '');
         if ($XML_log !~/fail$/) {
         	open ($Xml_file, $XML_log) || &Log_Error("Can't open $XML_log for Reading");
         	#flush a file to disk
         	select((select($Xml_file), $| = 1)[0]);
         	while (<$Xml_file>) {
          	$tag_true = 1 if (/<$Tag>/) ;
          	$count++ if (/<$Tag>/) ;
          		if (($tag_true)  && ($count eq $instance or $instance eq 0))  {
          			s/^\t//;  # Remove the tabs added to XML files
          			#print ("Tag $Tag Data $_ \n") if !(/</);
          			$tag_true = 0 if (/<\/$Tag>/) ;
          			push(@{$Tag_data_ref}, $_) if !(/</);  #Push only if  no Tag
           		}
          	 }
           	#@Tag_Data = reverse( @Tag_Data);
           	chomp(@{$Tag_data_ref});
           	$Tag_data_count = @{$Tag_data_ref};
           	close $Xml_file;
           	$Tag_data_count = 0 if $tag_true eq 1 ;  # Return 0 if no closing tag else return count



         }

         #&Log_Error("Failed to get XML Tag data for $SN[0]\n") if $Tag_data_count eq 0;
          return ($Tag_data_count);




}
#_____________________________________________________________________________



1;
