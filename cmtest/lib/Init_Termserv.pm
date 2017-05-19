####################################################################
#
# Module:   Init_Termserv.pm
#
# Author:   Joe White(From PT Init.pm)
#
# Descr:       Subs used to init Termserver dut
#
# Version:    (See below) $Id: Init_HA.pm,v 1.3 2008/02/21 00:00:27 joe Exp $
#
# Changes:
#            #$Ver = 'v1. 2/18/2015'; #Created JSW from Init_HA
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1993 - 2005 Paul Tindle. All rights reserved.
#            Copyright (c) 2005-2015 Mavenir. All rights reserved.
# Notes:
#		Globals Used:

#
####################################################################
my $Ver= 'v1. 2/18/2015'; #Created JSW from Init_HA
my $CVS_Ver = ' [ CVS: $Id: Init_HA.pm,v 1.3 2008/02/21 00:00:27 joe Exp $ ]';
$Version{'Init_HA'} = $Ver . $CVS_Ver;
#_____________________________________________________________________________

use File;
use Logs;
#use PT;
#use DataFile;
use Stats qw( %Stats %TestData %Globals $Stats_Path);
use Cwd qw( abs_path );
use Time::HiRes qw(gettimeofday usleep);
#use SigmaProbe::SPUnitReport;
use SigmaProbe::SPTestRun;
use SigmaProbe::SPTimeStamp;
use SigmaProbe::Local;

#   	our %Default_Termserver_Config = ('');
#     	our %Ship_Config_TermServer = ('');
#our %Term_Slot_Port_Map  = ('');


sub Cmd_Expect_Termserver_dep {    #* FROM Connect.pm *
		foreach $item (@Default_Termserver_Config) {
        my ($ConType, $Port) = @_;

        my ($ConExec, $ExitCmd);
        $Term_Sess = $Opening_session + 1;
        print ("Opening Session: $Term_Sess \n") if $Debug;

        if ($ConType eq 'Serial') {
            &Exit (34, "Serial port not defined for session $Sess_HA")
                  if  defined $SPort[$Sess_HA];
   			die "Attemp to define a tty or device in test device in termserver\n";
                print("ConExec: $ConExec \n")  if $Debug;
        } elsif ($ConType eq 'Telnet') {
                 &Exit (33, "Connect::Cmd_Expect: Port not defined") if !defined $Port;
                $ConExec = "/usr/bin/telnet $Port";
                # script [-a] [-c COMMAND] [-f] [-q] [-t] [file]   #log session(different than ExComm
                $ConExec = "script -c '/usr/bin/telnet $Default_Termserver_Config->[$IP] Term_Slot_Port_Map' -qf '~/tmp/$Sess/portxx'";
        } elsif ($ConType eq 'ssh') {
                $ConExec = "/usr/bin/ssh $Port -l mfg";
        } else  { &Exit (107, "ConType $ConType ??"); }
         print("ConExec pass: $ConExec \n") if $Debug;

         $Comm_HA = &Open_Port_HA ($ConType, $ConExec);
 }

}
#__________________________________________________________________________


sub Cmd_Init_Termserver {    #* FROM Connect.pm *
		my $portname;
		my $Sess = $Stats{'Session'};
		my $Tmp = "$ENV{'HOME'}/tmp";
		my $telnetescape = '';
		#chomp($Default_Termserver_Config{IP});
		foreach $portname (keys %Term_Slot_Port_Map) {
        #my ($ConType, $Port) = @_;
        my ($ConExec, $ExitCmd);
        $ExitCmd = $Default_Termserver_Config{ExitCmd} if defined $Default_Termserver_Config{ExitCmd};
        $telnetescape = "-e \"" . $Default_Termserver_Config{TELNETESCAPE} . "\"" if defined $Default_Termserver_Config{TELNETESCAPE};
        &Print2XLog("Opening Session:$telnetescape: $Default_Termserver_Config{IP} $Term_Slot_Port_Map{$portname} log to $Tmp/s$Sess/$portname.log ",0,1);
        # script [-a] [-c COMMAND] [-f] [-q] [-t] [file]   #log session(different than ExComm
         $ConExec = "script -a -c '/usr/bin/telnet $telnetescape $Default_Termserver_Config{IP} $Term_Slot_Port_Map{$portname}' -f '$Tmp/s$Sess/$portname.log'";

         &Print2XLog("ConExec pass:  $ConExec ") if $Debug;
         $Termserver_port{$portname} = &Open_Port("TermServerPW", $ConExec);

   }
}
#_______________________________________________________________

sub Next_Cons_dep {


# my $MAC_temp = $MAC[0];
# my $IP_temp = $UUT_IP;
# $MAC[0] = $MAC[1];
# $MAC[1] = $MAC_temp;
# $UUT_IP = $UUT_IP_HA;
# $UUT_IP_HA =  $IP_temp;

 if (   $Comm_Current eq $Comm_Start) {
 		$Comm_Current = $Comm_HA;
 		$HA_Msg = ':IMC_HA';
        &Print_Out_XML_Tag("IMC_HA");
 } else {
 		$Comm_Current = $Comm_Start;
 		$HA_Msg = '';
         #&Print_Out ("\<$Tag\>\n");
        &Print_Out_XML_Tag();
 }
        &Print2XLog ("IMC: $Comm_Current Orig: $Comm_Start HA: $Comm_HA  $bootprompt", 1);


}
#_______________________________________________________________

sub Cmd_Set_Cons {
    my ($portname) = @_;
     #Cmd_Set_Cons\("TERM_SLOT0_1"\)
# my $MAC_temp = $MAC[0];
# my $IP_temp = $UUT_IP;
# $MAC[0] = $MAC[1];
# $MAC[1] = $MAC_temp;
# $UUT_IP = $UUT_IP_HA;
# $UUT_IP_HA =  $IP_temp;
 if (   $portname ne '' && $Termserver_port{$portname} ne '' ) {
 		$Comm_Current = $Termserver_port{$portname};
 		$Term_Msg = "$portname:";
        &Print_Out_XML_Tag("$portname");
 } else {
 		$Comm_Current = $Comm_Start;
 		$Term_Msg = '';
         #&Print_Out ("\<$Tag\>\n");
        &Print_Out_XML_Tag();
 }
        &Print2XLog ("Com Current: $Comm_Current Orig: $Comm_Start Term $Termserver_port{$portname}  $bootprompt", 1);


}
#_______________________________________________________________

sub Prev_Cons_dep {


# my $MAC_temp = $MAC[0];
# my $IP_temp = $UUT_IP;
# $MAC[0] = $MAC[1];
# $MAC[1] = $MAC_temp;
# $UUT_IP = $UUT_IP_HA;
# $UUT_IP_HA =  $IP_temp;

 if (   $Comm_Current eq $Comm_Start) {
 		$Comm_Current = $Comm_HA;
 		$HA_Msg = ':IMC_HA';
        &Print_Out_XML_Tag("IMC_HA");
 } else {
 		$Comm_Current = $Comm_Start;
 		$HA_Msg = '';
         #&Print_Out ("\<$Tag\>\n");
        &Print_Out_XML_Tag();
 }
        &Print2XLog ("IMC: $Comm_Current Orig: $Comm_Start HA: $Comm_HA  $bootprompt", 1);


}

##__________________________________________________________________________


1;
