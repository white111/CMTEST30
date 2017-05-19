####################################################################
#
# Module:   Init_HA.pm
#
# Author:   Joe White(From PT Init.pm)
#
# Descr:       Subs used to run in HA(Dual IMC) mode (2 console, 2 ethernet)
#
# Version:    (See below) $Id: Init_HA.pm,v 1.3 2008/02/21 00:00:27 joe Exp $
#
# Changes:
#            #$Ver = 'v1.10 2006/07/31'; # fixed partnumber_hash declaration(Thnks PT)
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1993 - 2005 Paul Tindle. All rights reserved.
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
# Notes:
#		Globals Used:
#			 $UUT_IP , 'Serial', $ComPort
#		Globales Created:
#   	Added HA Varialbes(to Init_stoke.pm)
#			our $Tmp_HA             =  "$ENV{HOME}/tmp" ;
#            our $Opening_session = 0;
#            our $HA_Session = 0;
#            our $Comm_Log_HA = ''; # Log file for com app (minicom) HA
#            our ($Comm_HA);     # Handle for Expect HA
#            our ($Comm_Start);  # Our defualt at startup
#            our ($Comm_Current);  # What we are currently pointing too
#            our $HA_Msg = ''; # Msg added to Print2Xlog
#
####################################################################
my $Ver= 'v1.11 1/31/2008'; # Updated versioning
my $CVS_Ver = ' [ CVS: $Id: Init_HA.pm,v 1.3 2008/02/21 00:00:27 joe Exp $ ]';
$Version{'Init_HA'} = $Ver . $CVS_Ver;
#_____________________________________________________________________________


#cmtest
#	Init
#		Initalso
#	Menu1
#		Cmd_Expect
#			Mk_Port
#			Open_port
#
#
#Init_HA
#	Session_HA
#	Cmd_Expect_HA
#		Mk_Port_HA
#		Open_port_HA
#
#Swap_cons
#
#Exsisting Rotines Touched:
#Stats.pm - none, Session_HA created from Session() Init_HA.pm
#Logs.pm - modified print2xlog() to add HA_Msg if defined and not null
#PT.pm - Added &Stats::Session('delete',$HA_Session) if defined and not Zero to Exit_TestExec
#Connect.pm - Added to Cmd_Expect:         # HA Adds
#       $Comm = &Open_Port ($ConType, $ConExec);
#        $Comm_Start = $Comm;    # HA Our starting Port pointer
#        $Comm_Current = $Comm;  # HA Our Current Pointer
#		 May still need to deal with soft close and Tag
#		 Created Cmd_Expect_HA in Init_HA.pm
#		 Open_Port_HA
#Init.pm
#		  Created Open_Port_HA  Init_HA.pm


#package Init_HA;
#use strict qw(vars);
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



#__________________________________________________________________________





sub Cmd_Expect_HA {    #* FROM Connect.pm *
        my ($ConType, $Port) = @_;
        my $Sess_HA = 0;
        my ($ConExec, $ExitCmd);
        $Sess_HA = $Opening_session + 1;
        print ("Opening Session: $Sess_HA $Comm_Log_HA $Comm_Log\n") if $Debug;
        my ($Comm_HA);

        if ($ConType eq 'Serial') {
            &Exit (34, "Serial port not defined for session $Sess_HA")
                  if ! defined $SPort[$Sess_HA];
            if ($SPort[$Sess_HA] =~ /\/dev\/tty/) {
                &Mk_Port_HA;   #Init.pm - just in case!
                $ConExec = "/usr/bin/minicom -C $Comm_Log_HA $Sess_HA";
                print("ConExec: $ConExec \n")  if $Debug;
            } elsif ($SPort[$Sess_HA] =~ s/\:/ /) {
                $ConType = 'TermServer';
                $ConExec = "/usr/bin/telnet $SPort[$Sess_HA]";
            }

        } elsif ($ConType eq 'Telnet') {
                 &Exit (33, "Connect::Cmd_Expect: Port not defined") if !defined $Port;
                $ConExec = "/usr/bin/telnet $Port";
        } elsif ($ConType eq 'ssh') {
                $ConExec = "/usr/bin/ssh $Port -l mfg";
        } else  { &Exit (107, "ConType $ConType ??"); }
         print("ConExec pass: $ConExec \n") if $Debug;

         $Comm_HA = &Open_Port_HA ($ConType, $ConExec);


       # &Tag ($Cached,"Closing spawned connection ...");
       # $Comm_HA -> soft_close();

}
#__________________________________________________________________________

sub Init_HA_Port {  #
    my $opt_Z_HA = $opt_Z +1;
    $HA_Msg = ':IMC_HA';
    print "\n\tDebug=1\n\tQuiet=$Quiet\n\tVerbose=$Verbose\n\n" if $Debug;
    &Print_Out_XML_Tag("INIT_HA");
    #&Show_INCs;
          	$Opening_session = $Stats{'Session'}; # Save the original Session

            my $Pid_HA = &Session_HA ('read');        # Returns 0 if available
            if (($Pid_HA and $Pid_HA ne $Stats{'PID'}) or &Is_Running ($Pid_HA, 1)) {
                 # The requested session is already running!
                &Exit (107, "Session $opt_Z_HA declined") unless $Force;
                &Print_Log (11, "Forcing session $opt_Z_HA");
            }
            &Session_HA ('write');
            $HA_Session = $Opening_session +1;
            print("Opening Session: $Opening_session HA: $HA_Session \n") if $Debug;
        $Tmp_HA .= '/s' . $Opening_session;

        $Comm_Log_HA = "$Tmp_HA/Comm_HA.log";

        Cmd_Expect_HA('Serial', $ComPort+1);
        &Print_Out_XML_Tag();
        $HA_Msg = '';
}

#_______________________________________________________________

sub Mk_Port_HA {

    my $Port = $Opening_session + 1;
    my $File = "/etc/minirc.$Port";
    print("Making HA minicom config\n") if $Debug;
    my $UMask = umask; umask 0;
    print("Making HA minicom config Umask: $UMask\n")  if $Debug;
    open OUT, ">$File" or &Exit (35, "Can\'t cpen minicom cfg file $File for port $Port");

    print OUT "# Machine-generated file created " . localtime() . "\n";
    print OUT "pr port             $SPort[$Port]\n";
    print OUT "pu baudrate         $Baud\n";
    print OUT "pu minit\n";
    print OUT "pr rtscts           No\n";
    print OUT "pu histlines        4000\n";

    close OUT;
    umask $UMask;
    system "ls -als /dev/ttyS45"  if $Debug;
    system "ls -als /etc/minirc.4"  if $Debug;
}
#_______________________________________________________________

sub Session_HA {

        my ($Op, $Sess) = @_;                # Normally it would be its own $Session
                                        # But this allows for a partner (+1) check ...

        $Sess = 1 + $main::Stats{'Session'} if ! defined $Sess;
        die "Stats_Path not defined! Did testctrl.cfg get sourced??"
            if !defined $main::Stats_Path;

        my $File = $main::Stats_Path . '/system/' .
                        $main::Stats{'Host_ID'} . '-';
        my $Tag;
        my $FileName = $File . $Sess;

        my $UMask = umask;
        umask 0;

        SWITCH: {
                if ($Op eq 'delete') {
                        system "rm -f $FileName";
                        return (0);
                }
   				if ($Op eq 'HA') {
                        #$main::Stats{'Session'} = 1;
                        #while (-f $File . $main::Stats{'Session'}) { $main::Stats{'Session'}++; }
                        #$FileName = $File . $main::Stats{'Session'};
                        $main::Erc = system "touch $FileName; chmod 777 $FileName";
                        &main::Print_Log (2, "Problem touching $FileName") if $main::Erc;
                        $Tag = '>';
                        last SWITCH;

                }
                if ($Op eq 'read') {
                        return (0) if ! -f $FileName;
                        $Tag = '<';
                        last SWITCH;
                }
                if ($Op eq 'write') {
                        $Tag = '>';
                        last SWITCH;
                }

        }

        open (STATS, "$Tag$FileName") || &main::Exit (8, "Can\'t open Stats File: $File for $Op");

        if ($Op eq 'read') {
                my $PID = <STATS>;
                return ($PID);
        } else {
                print STATS $main::Stats{'PID'};
        }

        close STATS;
        umask $UMask;

        return (0);
}
#__________________________________________________________________________________


sub Swap_cons {


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

sub Open_Port_HA {

    my ($ConType, $ConExec) = @_;
   # my $Comm_HA;
    my $Trap = '';
    #$ConExec = '/usr/bin/minicom -C /home/joe/tmp/s3/Comm_HA.log 4';
    if ($ConType eq 'Serial') {
        $Header = 'Welcome';
        $ExitCmd = "\cA" . "Q\n";
        $Trap = 'lock failed';
    } elsif ($ConType eq 'Telnet') {
        $ExitCmd = 'exit';
        $Header = 'Connected to';
    } elsif ($ConType eq 'TermServer') {
        $ExitCmd = "\c]quit";
        $Header = 'Connected to';
        $Trap = 'is being used by';
    } else {
        die 'What am I doing here??';
    }

    my $Count = 5;
    my $Done = 0;

    &Exit (110, "Call to Exec_Cmd_File on $OS system") if $OS eq 'Win32';
    my $Msg = "Spawning $ConType connection: $ConExec ..";
    &Print_Log (1, $Msg);

    while (! $Done and $Count) {

         $Comm_HA = Expect->spawn($ConExec)
             or &Exit (31, "Couldn't start HA $ConExec: $!\n");

         $Comm_HA->log_file("$Tmp_HA/ExComm_HA.log", "w");

         #if ($Debug) {
             $Expect::Exp_Internal = $Verbose;        # Turn on verbose mode if -v
#                        $Expect::Debug = 1;
#                        $Comm->log_file("$Tmp/expect.log", "w");        # Log all!
         #}
         # Need to do this when we switch
         $Comm_HA->log_stdout(0);                # prevents the program's output from being shown on our STDOUT
         # Already Done ->   $Expect::Log_Stdout = 0;        # but this one does it globally!

         # The acid test to see if we are connected...

         print "." unless $Quiet;
         my (@Ex) = $Comm_HA -> expect(5, $Header, $Trap);
         &Dump_Expect_Data(@Ex);
          print("Expect Return: $Ex[0] Header: $Header Trap: $Trap \n") if $Debug;
         if ($Ex[0] == 1) {      # if ($Comm -> expect(5, $Header)) { 1 if matched, undef if timeout
                         # Got the expected response
              $Done = 1;
         } elsif ($Ex[0] == 2) { # Caught the trap
              &Exit (999, "Trapped Error condition HA: $Trap");
         } else {
              $Count--;
         }

         if ($Done and $Count) {                                        # There were some retries left!
                         print " done HA!\n" unless $Quiet;

         } elsif (! $Done and $Count) {                        # Go round again
                 sleep 4;
         } else {        # We're out of retries!
                 print " Failed HA!\n" unless $Quiet;
                 my $Msg = "$ConExec FAILED to start HA!!\n";
				 &Exit (31, $Msg);
                          }
    }
    unless ($Trap eq '') {
        (@Ex) = $Comm_HA -> expect(2, $Trap);
        &Dump_Expect_Data(@Ex);
        if ($Ex[0]) {      # undef if timeout
                         # Got the trap response
            &Exit (999, "Trapped Error condition HA : $Trap");
        }

    }

    return ($Comm_HA);
}
#__________________________________________________________________________


1;
