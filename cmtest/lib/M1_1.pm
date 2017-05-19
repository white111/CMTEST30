################################################################################
#
# Module:      Mav.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#			   Joe White ( mailto:joe@stoke.com )
#
# Descr:      Stoke Specific Libray
#
# Version:    (See below) $Id: Stoke.pm,v 1.25 2012/02/17 17:13:42 joe Exp $
#
# Changes:     Added CheckDataX command (check for exclusion of $Arg)
#              Added Check_GLC_Thermal
#			   Enabled exit on Timeout
#			   Modified Temp upper limit
#			   Added ORT test for MTBF validation
#			   Added Chassis Fuctional Full slot test 2/16/10
#			   Added Check for first boot of dual IMC 4/20/10
#			   Added PSOC  1/11/11
#			   XGLC Changes in progress - Menu/Submenu, Buadrate set, added Stoke3.lib
#			Added Support for Fan2 and PEM2 Chassis test 2/6/13
#				&Check_IMC_0_Standby_Prompt  ($Data) if $Key eq 'Check_IMC_0_Standby_Prompt' 6.1/13.1 software
#			   Added Support for 4 XGLCs, 1gig,copper, ler SFP per port, SFP power meas
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
my $Ver = '18.3   012915'; #             #Name Changes to Mavenir  1/29/15
my $CVS_Ver = ' [ CVS: $Id: Stoke.pm,v 1.25 2012/02/17 17:13:42 joe Exp $ ]';
$Version{'Stoke'} = $Ver . $CVS_Ver;
#____________________________________________________________________________

use Init_Termserv;
#use Init_Termserv::Cmd_Init_Termserver;   # M1 Terminal server port config
#use SSX3;   # Gen2 Hardware
#__________________________________________________________________________

sub Get_Data_M1 {       # Called by &Screen_Data to parse the comm buffer

    my ($Key, $Data) = @_;
    $Key = ucfirst $Key;
    #print ("Get_Data $Key, $Data\n");
    &Get_Serial_Info_dep if $Key eq 'Serial'; # No need to pass $Data since we're
                                          # using global @Screen_Data


    #

}
#__________________________________________________________________________

sub Get_Serial_Info_dep {

    # Extract the Part number and Serial number info
    #  from global @Screen_Data and update @PN & @SN, then incr $Cfg_Ptr

    foreach (@Screen_Data) {
        if (/.*(\w{16}).*/) {
           $SN[$Cfg_Ptr] = $1;
           $SN[$Cfg_Ptr] =~ /(\w{3})(\w{2})(\w{4})(\w{1})(\w{1})(\w{5})/;
           $PN[$Cfg_Ptr] = $1;    #!!! Need a lookup
        }
    }
    &Print2XLog ("PN = \'$PN[$Cfg_Ptr]\',SN = \'$SN[$Cfg_Ptr]\'");

    $Stats{'UUT_ID'} = $SN[0] unless $Cfg_Ptr;
    &Stats::Update_All;
    $Cfg_Ptr++;

    if ($Debug) {
        print "[Get_Serial_Info:] Serial Data->\n$Data{Serial}\n<-\n";
        for $i( 0 .. 2 ) {
            print "$i)\tPN=$PN[$i]\tSN=$SN[$i]\n";
        }
        &PETC('-230');
    }

#!!!    &Create_SigmaQuest_Unit_Report if $First_Time and $PN[0] ne '';
}

#__________________________________________________________________________
sub Get_UUT_Variables {
	# This builds a hash array by slot #
		# This is work in progress - JW
   our @UUT_Variable_ref; # array of Hash Pointers

   #my @UUT_Varible_slot();
   my $dir = $PPath . '/uutcfg/' . $Product_gbl ;
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

   opendir DIR, $dir or die "cannot open dir $dir: $!";
	my @file= readdir DIR;
	closedir DIR;

    foreach   $Filefound (@file) {
    	&Print2XLog("Get UUT  Var File $Filefound\n",1);
    if  (&Read_Data_File ("$dir\/$Filefound")) {
        die "Can\'t read data file $Filefound";
    }
   }

#    while ((($first,$last) = each(%allowed_partnumber_rev)) && ($debug || $development)) {
#        print ( "Check_UUT-Ver allowed_partnumber_rev Found: $first = $last \n");
#        }
#       #&Write_Data_File ($File3, '>','list');
#     foreach (0..25) {
#        $count = $_ ;
#        $PN[$_] =~ /(\w+)-(\w+)\sRev\s(\w+)/;
#        unless ($PN[$_] eq '') {
#        #   if ($allowed_partnumber_rev{$Search}) {
#        $File2 = $PPath . '/uutcfg/' . $Product_gbl . '/' . $1 . '.cfg';
#        if  (&Read_Data_File ($File2)) {
#            die "Can\'t read data file $File2 on Slot $_";
#        }
#        $partnumber_hash  = "UUT" . "_" . $1 . "_" . $2;
#        $partnumber_hash_out  = "UUT" . "_" . $count . "_" . $1 . "_" . $2;
#        if (each(%{$partnumber_hash})) {
#           &Print2XLog ("Found partnumber hash: $partnumber_hash\n",1);
#        } else {
#          $partnumber_hash  = "UUT" .  "_" . $1;
#          $partnumber_hash_out  = "UUT" . "_" . $count . "_" . $1;
#          &PrintLog ("Default partnumber hash: $partnumber_hash\n",1);
#        }
#        #print ("Found Values in $partnumber_hash\n") if (%{$partnumber_hash});
#        while ((($first,$last) = each(%{$partnumber_hash}))  ) {    #  && ($debug || $development && ($debug || $development)
#            &Print2XLog ( "Variables Found in $partnumber_hash: $first = $last \n",1);
#        }
#        $partnumber_hash_ref = \%{$partnumber_hash};
#        %{$partnumber_hash_out} =  %{$partnumber_hash};
#        $UUT_Variable_ref[$count] = \%{$partnumber_hash};
#        # For Future use ?
#        #&Write_Data_File ($File3, '>>', "%$partnumber_hash_out");
#     }
#    }
#        foreach (0..25 ) {   #&& ($debug || $development)
#             unless ($PN[$_] eq '') {
#                $count2 = $_ ;
#                foreach $key ( keys (%{$UUT_Variable_ref[$count2]})) {
#                    &Print2XLog ("UUT_Variable_ref[$count2]->{$key}= $UUT_Variable_ref[$count2]->{$key}\n", 1);
#                }
#                 }
#        }

}
#____________________________________________________________________________________________________________________
sub M1_Menu_main {
	&Globals_M1;
    @Menu_List = ();
    @Menu_Desc = ();
    @Menu_Cmd  = ();
    $User_Level = 0 if ($Debug_UUT eq 1 || $Development eq 1);
    our $CmdFilePath = "$GP_Path/cmdfiles/M1";
    &Menu_Add ('Exit', '', 'Menu_Exit');
    &Menu_Add ('Test', 'Test', 'Run_M1Test') if $User_Level > 1  or $User_Level eq 0;

    #&Menu_Add ('Gen 1', 'Test 1 Gig interface product', 'Menu1') if $User_Level > 1  or $User_Level eq 0;
    #&Menu_Add ('Gen 2', 'Test 10 Gig interface product', 'Menu2') if $User_Level > 1  or $User_Level eq 0;


   if ($opt_1 or $opt_M ne '') {
        &Menu_Add ('Test', 'Regression test vehicle', 'Run_Test');
#        &Menu_Add ('Test_ssh', 'Regression test vehicle', 'Run_Test_ssh');
    }

    if ($opt_M eq '') {
        &Menu_Show ( 'Main' );
    } else {
        &Menu_Exec ($opt_M-1);
    }
}
#__________________________________________________________________________

sub M1_Menu1 {
   @Menu_List = ();
    @Menu_Desc = ();
    @Menu_Cmd  = ();
    $User_Level = 0 if ($Debug_UUT eq 1 || $Development eq 1);
    our $CmdFilePath = "$GP_Path/cmdfiles/M1/gen1";
    &Menu_Add ('Exit', '', 'Menu_main');
#    &Menu_Add ('Bench Program', 'Initial PCB bringup Programming', 'Run_Prog') if $User_Level > 1  or $User_Level eq 0;
#    &Menu_Add ('Debug', 'Debug Sub menu', 'M1_Debug_Menu1') if $User_Level > 1  or $User_Level eq 0;


   if ($opt_1 or $opt_M ne '') {
        &Menu_Add ('Test', 'Regression test vehicle', 'Run_Test');
#        &Menu_Add ('Test_ssh', 'Regression test vehicle', 'Run_Test_ssh');
    }

    if ($opt_M eq '') {
        &Menu_Show ( 'Main' );
    } else {
        &Menu_Exec ($opt_M-1);
    }
}

#__________________________________________________________________________

sub M1_Debug_Menu1 {
   @Menu_List = ();
    @Menu_Desc = ();
    @Menu_Cmd  = ();
    $User_Level = 0 if ($Debug_UUT eq 1 || $Development eq 1);
    our $CmdFilePath = "$GP_Path/cmdfiles/M1/gen1";
    &Menu_Add ('Exit', '', 'Menu_main');
#    &Menu_Add ('Debug', 'Temporary', "Run_Debug")  if $User_Level eq 0; # if ($Debug);
#    &Menu_Add ('Debug', 'Power Cycle GLC on Bench', "Run_Debug_GLC_Bench_Power")  if $User_Level eq 0; # if ($Debug);
#    &Menu_Add ('Debug', 'Power Cycle IMC on Bench', "Run_Debug_IMC_Bench_Power")  if $User_Level eq 0; # if ($Debug);
#    &Menu_Add ('Debug', 'BI Debug', "Run_Debug_Chassis_BI")  if $User_Level eq 0; # if ($Debug);

   if ($opt_1 or $opt_M ne '') {
        &Menu_Add ('Test', 'Regression test vehicle', 'Run_Test');
#        &Menu_Add ('Test_ssh', 'Regression test vehicle', 'Run_Test_ssh');
    }

    if ($opt_M eq '') {
        &Menu_Show ( 'Main' );
    } else {
        &Menu_Exec ($opt_M-1);
    }
}

#__________________________________________________________________________

sub M1_Menu2 {   # Gen 2 boards
    @Menu_List = ();
    @Menu_Desc = ();
    @Menu_Cmd  = ();
    $User_Level = 0 if ($Debug_UUT eq 1 || $Development eq 1);
    our $CmdFilePath = "$GP_Path/cmdfiles/M1/gen2";
    &Menu_Add ('Exit', '', 'Menu_main');
    &Menu_Add ('Debug Gen 2', 'Debug Sub menu', 'M1_Debug_Menu2') if $User_Level > 1  or $User_Level eq 0;

   if ($opt_1 or $opt_M ne '') {
        &Menu_Add ('Test', 'Regression test vehicle', 'Run_Test');
#        &Menu_Add ('Test_ssh', 'Regression test vehicle', 'Run_Test_ssh');
    }

    if ($opt_M eq '') {
        &Menu_Show ( 'Main' );
    } else {
        &Menu_Exec ($opt_M-1);
    }
}

#_______________________________________________________________________________

sub M1_Debug_Menu2 {   # Gen 2 boards
    @Menu_List = ();
    @Menu_Desc = ();
    @Menu_Cmd  = ();
    $User_Level = 0 if ($Debug_UUT eq 1 || $Development eq 1);
    our $CmdFilePath = "$GP_Path/cmdfiles/M1/gen2";
    &Menu_Add ('Exit', '', 'Menu_main');
#    &Menu_Add ('Debug Bench Test XGLC', 'Debug', 'Run_Bench_Debug') if $User_Level > 5  or $User_Level eq 0;
#    &Menu_Add ('Bench Flash XGLC', 'Flash Programming', 'Run_Prog_Flash2') if $User_Level > 1  or $User_Level eq 0;
#    &Menu_Add ('StokeOS Reload', 'StokeOS startup Stability', 'Run_Debug_XGLC_StokeOSReload') if $User_Level > 5  or $User_Level eq 0;
#    &Menu_Add ('Debug Temp', 'Debug XGLC', 'Run_Debug_XGLC') if $User_Level > 5  or $User_Level eq 0;
#    &Menu_Add ('Debug', 'Debug Reboot XLP', 'Run_Debug_Reboot_XLP') if $User_Level > 5  or $User_Level eq 0;
#    &Menu_Add ('Debug', 'Debug Power Cycle XGLC', 'Run_Debug_Bench_XGLC_PowerCycle') if $User_Level > 5  or $User_Level eq 0;
#    &Menu_Add ('Debug', 'Debug Power Cycle XGLC Selct margin', 'Run_Debug_Bench_XGLC_PowerCycle_Select_Margin') if $User_Level > 5  or $User_Level eq 0;
#    &Menu_Add ('Debug', 'Debug Power Cycle XGLC GPP DRAM', 'Run_Debug_Bench_XGLC_PowerCycle_GPP_DRAM') if $User_Level > 5  or $User_Level eq 0;
#    &Menu_Add ('Debug', 'Debug Reboot XGLC', 'Run_Debug_Bench_XGLC_Reboot') if $User_Level > 5  or $User_Level eq 0;
#    &Menu_Add ('Debug', 'Debug XGLC Flashimage', 'Run_Debug_Flashimage_XGLC') if $User_Level > 5  or $User_Level eq 0;
#    &Menu_Add ('Debug', 'Debug', 'Run_Debug_Gen2') if $User_Level > 5  or $User_Level eq 0;



   if ($opt_1 or $opt_M ne '') {
        &Menu_Add ('Test', 'Regression test vehicle', 'Run_Test');
#        &Menu_Add ('Test_ssh', 'Regression test vehicle', 'Run_Test_ssh');
    }

    if ($opt_M eq '') {
        &Menu_Show ( 'Main' );
    } else {
        &Menu_Exec ($opt_M-1);
    }
}

#__________________________________________________________________________
sub Run_Debug_GLC_Bench_Power {
            #caller(0))[3];
    my $Cmd_File = "$CmdFilePath/Debug_Bench_GLC_Powercyle.dat";
     print "Debug\n";
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;

    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_M1Test {
            #caller(0))[3];
    my $Cmd_File = "$CmdFilePath/Test.dat";
     print "Debug\n";
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;

    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Debug_IMC_Bench_Power {
            #caller(0))[3];
    my $Cmd_File = "$CmdFilePath/Debug_Bench_IMC_Powercyle.dat";
     print "Debug\n";
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;

    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Debug_Chassis_BI {
            #caller(0))[3];
    my $Cmd_File = "$CmdFilePath/Debug_Chassis_BI.dat";
     print "Debug\n";
    $TestData{'TID'} = 'DEBUG';
    $Exit_On_Timeout = 1;

    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#_______________________________________________________________________
sub Run_Bench_Test {

    my $Cmd_File = "$CmdFilePath/Bench.dat";

    $TestData{'TID'} = 'Bench';
    $Exit_On_Timeout = 1;
    &XML_Header(); # Added JSW - Stoke
    &Cmd_Expect( 'Serial', $ComPort, $Cmd_File );

    &Final;
}
#__________________________________________________________________________
1;
