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

use Init_SSX;
use Init_M1;
use SSX1;   # SSX hardware
use M1_1;   # M1 hardware

#__________________________________________________________________________
sub Check_Data {    # Called by Screen_Data

    my ( $Match, $Exclude ) = @_;
    my $PassFail = 'PASS';   # Used only by Sigmaprobe

    &Print2XLog ("Check_Data (X=$Exclude) [$Match]: $Buffer",1) if $Debug;

    if ($Buffer =~ /$Match/) {
        $Buffer = $';     # Leave only post-match data in $Buffer
        if ($Exclude) {

            $PassFail = 'FAIL';
            $Erc = 501;
            &Log_Error ("Check_DataX:  \"$Match\"");
        }

    } else {
        return if $Exclude;
        $PassFail = 'FAIL';
        $Erc = 501;
        &Log_Error ("Check_Data: no \"$Match\"");
    }

#!!!    &Create_SigmaQuest_SubTest( "POST", $PassFail );

    return ();
}

#__________________________________________________________________________
sub Check_Datai {    # Called by Screen_Data  , Ignore case

    my ( $Match, $Exclude ) = @_;
    my $PassFail = 'PASS';   # Used only by Sigmaprobe

    &Print2XLog ("Check_Data (X=$Exclude) [$Match]: $Buffer",1) if $Debug;

    if ($Buffer =~ /$Match/i) {
        $Buffer = $';     # Leave only post-match data in $Buffer
        if ($Exclude) {

            $PassFail = 'FAIL';
            $Erc = 501;
            &Log_Error ("Check_DataXi:  \"$Match\"");
        }

    } else {
        return if $Exclude;
        $PassFail = 'FAIL';
        $Erc = 501;
        &Log_Error ("Check_Datai: no \"$Match\"");
    }

#!!!    &Create_SigmaQuest_SubTest( "POST", $PassFail );

    return ();
}

#__________________________________________________________________________
sub Get_Data {       # Called by &Screen_Data to parse the comm buffer
    &Print2XLog ("Found Product set to $Product_gbl",1);
	if ($Product_gbl ne "" || $Product_gbl eq undef ) {
	 	&{"Get_Data_" . $Product_gbl};
	} else {
		die "Product Not found $Product_gbl\n";
	}
    my ($Key, $Data) = @_;
    $Key = ucfirst $Key;
    #print ("Get_Data $Key, $Data\n");
#    &Get_Serial_Info if $Key eq 'Serial'; # No need to pass $Data since we're
#                                          # using global @Screen_Data
#    &Get_show_mfg_serial if $Key eq 'ShowMFG' ;
#    &Get_Board_Info if $Key eq 'Board'; # No need to pass $Data since we're
#    &Get_Chassis_Info if $Key eq 'Chassis';
#    &Get_SW55thlink  if $Key eq 'SW55thlink';
#    &Get_Volts if $Key eq 'Volts';

    #

}
#__________________________________________________________________________

sub Get_SW_Version {

    &Stats::Update_All;
}

#__________________________________________________________________________

sub Menu_main {
    @Menu_List = ();
    @Menu_Desc = ();
    @Menu_Cmd  = ();
    $User_Level = 0 if ($Debug_UUT eq 1 || $Development eq 1);
    &Menu_Add ('Exit', '', 'Menu_Exit');
    &Menu_Add ('SSX', 'Test SSX', 'SSX_Menu_main') if $User_Level > 1  or $User_Level eq 0;
    &Menu_Add ('Test', 'Test M1', 'M1_Menu_main') if $User_Level > 1  or $User_Level eq 0;
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

sub Menu_Exec {

    my ($y) = @_;
    print "Exec\'ing $Menu_List[$y]...\n";
    	#  Added for Sub menus,  need to clear the lists
    &Exec ($Menu_Cmd [$y]);     # Find the sub [last arg in Menu_add_...]

    return;
}
#______________________________________________________________________________



sub Menu_Exit {

    my ($y) = @_;

    $Stats{'Status'} = 'Exit';
    &Stats::Update_All ;
    &Exit(0,'');
    #exit;
    return;
}
#________________________________________________________________________

sub Menusub_Exit {

    my ($y) = @_;

    $Stats{'Status'} = 'Exit';
    &Stats::Update_All ;
    Menu_main();
    #exit;
    return;


#________________________________________________________________________
}

sub Menu_Show {    #!!! Move this to

    my ($Menu) = @_;   #!!! currently not used. Only main

    my $i = 0;

    print "\nTest Options:\n";
    foreach (@Menu_List) {
            $i++;
            my $Desc = $Menu_Desc[$i-1];
               $Desc = "[$Desc]" unless $Desc eq '';
            print  "\t$i) " . &Pad ($_, 25) . "$Desc\n";
    }
    print "\n";
    my $y;
    while (! $y or $y > $#Menu_List + 1) {
            $y = &PETC('Select item #?');
    }

    $y--;                # We're base 0, not 1

    $TestData{'SW_Ver'} = $Software_OS_release_gbl;
    $TestData{'Diag_Ver'} = $diag_ver_gbl;
    $Stats{'Status'} = 'Started';
    &Stats::Update_All ;
    print "Exec\'ing $Menu_List[$y]...\n";
    &Exec ($Menu_Cmd [$y]);     # Find the sub [last arg in Menu_add_...]
    return;
}

#__________________________________________________________________________
sub Menu_Add {

    my ($Label, $Desc, $Cmd) = @_;

                            # Can't use a hash because of the ordering!...
    push @Menu_List, $Label;
#    push @Menu_List, &Pad ($Label, 20) . "[$Desc]";
    push @Menu_Desc, $Desc;
    push @Menu_Cmd, $Cmd;
}
#__________________________________________________________________________
sub Pseudo_Cmd {

    my ( $Cmd, $Arg ) = @_;

    #   &Exec_Cmd ($Comm, $CFName, $Line, $KeyWord, $Arg, $Check_Only);

    my ($Tmp_File) = "$Tmp/SData" . $Stats{'Session'} . '.tmp';

    open( $fh, ">>$Tmp_File" ) or &Exit( 1, $Tmp_File );
    print $fh "\<$Cmd\>\t$Arg\n";
    close $fh;

}

#__________________________________________________________________________
sub Run_Demo_Telnet {

    my $Cmd_File = "$CmdFilePath/Demo_Telnet.dat";
    $TestData{'TID'} = 'TelnetDemo';
    $Exit_On_Timeout = 0;

    &Cmd_Expect( 'Telnet', 'localhost', $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Run_Test {

    my $Cmd_File = "$CmdFilePath/Test.dat";
    $TestData{'TID'} = 'Test';
    $Exit_On_Timeout = 0;

    &Cmd_Expect( 'Telnet',  'localhost', $Cmd_File );

    &Final;
}

#__________________________________________________________________________
sub Run_Test_ssh {

    my $Cmd_File = "$CmdFilePath/Test_ssh.dat";
    $TestData{'TID'} = 'Test';
    $Exit_On_Timeout = 0;

    &Cmd_Expect( 'ssh',  'localhost', $Cmd_File );

    &Final;
}
#__________________________________________________________________________
sub Screen_Data {    #        Takes screen data and:
                     #         - Removes any control characters
                     #         - Write label, non blank lines, then summary to the out file
                     #         - Write non blank lines to %Data, using label as key

     my ($Key, $Check_Data, $Exclude) = @_;

                     # Get rid of the weird formatting <esc> sequences ...
     #$Buffer =~ s/\c[\d+;\d+H//g;
#     $Buffer =~ s/\x1B\x5B\d{2}\;*\d*m//g;
     $Buffer =~ s/\c[\[\d+;\d+H//g;

     $Buffer =~ s/\r\n/\n/g;
     $Buffer =~ s/\n\r/\n/g;

     &Print_Log (11, "Screen_Data [$Key]: $Buffer") if $Debug;

     $Buffer =~ s/\<\=/\/\=/g;

     print '_' x 80, "\n", &HexDump ($Buffer), "\n", '_' x 80, "\n"
             if $Debug or 0;

     if ($Check_Data) {
         &Check_Data ($Key, $Exclude); # $Key is actually the match string
     } else {
         my $fh;
         open ($fh, ">>$Out_File") || &Exit (3, "Can't open $Out_File for cat");
         print $fh "  \<$Key\> ", '_' x 80, "\n"  unless $Key eq '';

         @Screen_Data = ();
         foreach $Buf (split (/\n/, $Buffer)) {

             $Buf =~ s/[\000-\031][\127-\255]//g;
             unless ($Buf eq '') {

                 push @Screen_Data, $Buf;
                 print $fh "\t\t$Buf\n";                # Write to the Out File
              }
         }

         unless ($Key eq '' or $Check_Data) {
             my ($RunTime) = time - $Stats{'TimeStamp'};
             print $fh "<Runtime Units=\"secs\">$RunTime</Runtime>\n";
             print $fh "<TD-TEC>$TestData{TEC}</TD-TEC>\n";
             print $fh "  <\/$Key\>\n";
         }

         close $fh;
         &Get_Data ($Key);   # Pass the key + original buffer
     }
}

#__________________________________________________________________________
sub Screen_Datai {    #        Takes screen data and:
                     #         - Removes any control characters
                     #         - Write label, non blank lines, then summary to the out file
                     #         - Write non blank lines to %Data, using label as key
                     #   	   - ignores case during checks

     my ($Key, $Check_Data, $Exclude) = @_;

                     # Get rid of the weird formatting <esc> sequences ...
     #$Buffer =~ s/\c[\d+;\d+H//g;
#     $Buffer =~ s/\x1B\x5B\d{2}\;*\d*m//g;
     $Buffer =~ s/\c[\[\d+;\d+H//g;

     $Buffer =~ s/\r\n/\n/g;
     $Buffer =~ s/\n\r/\n/g;

     &Print_Log (11, "Screen_Data [$Key]: $Buffer") if $Debug;

     $Buffer =~ s/\<\=/\/\=/g;

     print '_' x 80, "\n", &HexDump ($Buffer), "\n", '_' x 80, "\n"
             if $Debug or 0;

     if ($Check_Data) {
         &Check_Datai ($Key, $Exclude); # $Key is actually the match string
     } else {
         my $fh;
         open ($fh, ">>$Out_File") || &Exit (3, "Can't open $Out_File for cat");
         print $fh "  \<$Key\> ", '_' x 80, "\n"  unless $Key eq '';

         @Screen_Data = ();
         foreach $Buf (split (/\n/, $Buffer)) {

             $Buf =~ s/[\000-\031][\127-\255]//g;
             unless ($Buf eq '') {

                 push @Screen_Data, $Buf;
                 print $fh "\t\t$Buf\n";                # Write to the Out File
              }
         }

         unless ($Key eq '' or $Check_Data) {
             my ($RunTime) = time - $Stats{'TimeStamp'};
             print $fh "<Runtime Units=\"secs\">$RunTime</Runtime>\n";
             print $fh "<TD-TEC>$TestData{TEC}</TD-TEC>\n";
             print $fh "  <\/$Key\>\n";
         }

         close $fh;
         &Get_Data ($Key);   # Pass the key + original buffer
     }
}

#__________________________________________________________________________
1;
