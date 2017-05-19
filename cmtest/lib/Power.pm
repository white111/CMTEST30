################################################################################
#
# Module:      Power.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      subs from PT.pl
#
# Version:    (See below) $Id: Power.pm,v 1.5 2008/02/21 00:00:27 joe Exp $
#
# Changes:
#    		#$Version{'Power'} = 'v3.3 2005-11-03'; # Create log file even if $SN[0] eq ''
#			3.4 Added Power_Switch2_IP for second APC control
#
# Still ToDo:
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1993 - 2005 Paul Tindle. All rights reserved.
#            Copyright (c) 2005-2012 Stoke. All rights reserved.
#
################################################################################
my $Ver= 'v3.4 5/04/2012'; #Added Power_Switch2_IP for second APC control
my $CVS_Ver = ' [ CVS: $Id: Power.pm,v 1.5 2008/02/21 00:00:27 joe Exp $ ]';
$Version{'Power'} = $Ver . $CVS_Ver;
#______________________________________________________________________________


#use strict;
#use APC_Power;           # Only for snmp
#use Sys::PortIO;         # Only for LPT_Power1 (debug)
use Device::ParallelPort;
use Device::ParallelPort::drv::parport;


#require Exporter;

#@ISA = qw(Exporter);
#@EXPORT_OK = qw(

#        Power_type
#);


    our $Power_type;      # APC | LPT | [manual]
    our $Power_Switch_IP; # 192.168.x.y

    our (%Globals, %Stats);
    $Globals{'Power_type'} = 1;




#_______________________________________________________________________________
sub LPT_Power {

    my ($Session, $Action) = @_;
    $Action = uc $Action;
    my $Bit  = (defined $Power_Port[$Session])
             ? $Power_Port[$Session]
             : ($Session) ? ($Session -1)
                          : 0;
    $Action = 'SHOW_ALL' if ($Action eq 'STATUS')
                         and !$Session;

    die "No port assigned to On/Off Action"
        if ($Action eq 'ON' or
            $Action eq 'OFF') and
            !$Session;

    my $port = Device::ParallelPort->new();

    if ($Action eq 'OFF') {
        &LPT_Power_Write ($port, $Bit, 0);
    } elsif ($Action eq 'ON') {
        &LPT_Power_Write ($port, $Bit, 1);
    } elsif ($Action eq 'SHOW') {
        my $State = $port->get_bit($Bit);
        $State = ($State) ? 'ON' : 'OFF';
        print "Power bit $Bit is $State\n" unless $Quiet;
    } elsif ($Action eq 'SHOW_ALL') {
        my @States  = (time);    # ( <updated>, St1, St2, ...)
        my $Str_ON  ='';
        my $Str_OFF ='';
        foreach (0..7) {
            my $State = $port->get_bit($_);
            $States[$_+1] = $State;
        }
        &Print_Status (@States);
        return (@States);
    } elsif ($Action eq 'STATUS') {
        &Print_Status ($port->get_bit($Session-1));
    } else {

        die "you passed something weird ($Action) to LPT_Power!";
    }

    return ($State);

#    print ord($port->get_byte(0)) . "\n";
#    $port->set_byte(0, chr(255));


}
#_______________________________________________________________________________
sub LPT_Power_Write {

    my ($port, $Bit, $Data) = @_;

    $port->set_bit($Bit,$Data);
    my $PBit = $port->get_bit($Bit);

    die "Power bit not sticky!" unless $PBit == $Data;

    return;
}
#_______________________________________________________________________________
sub LPT_Power1 { # This is the first one tried - still broken!

    use Sys::PortIO;

    my ($Session, $Action) = @_;
    $Action = uc $Action;

    #0x3bc for /dev/lp0

#    my $Port = '0x3bc';
    my $Port = '/dev/lp0';
#    my $Port = 'lp0';
#    my $Port = 'parport0';
    print "\n\tPort = $Port\n\n";
    port_open($Port);

    my $Data = read_byte($Port);

    &PETC ("Read \'$Data  \' from LPT");
    my $Value = ($Action eq 'ON') ? 'FF' : 0; # Bit OR $Data and $Session

    write_byte($Port, $Value);

    port_close($Port);

}

#_______________________________________________________________________________
sub Power {    # This is called by Connect.pm following a <POWER>   ON|OFF

    my ($Action) = @_;
    my $Session  = $Stats{'Session'};
    my $Session2 = $Stats{'Session'} - 8;
    my $Delay    = 0;                  # Future
    my @States   = ();
    my $Cmd = "";

    &Print_Log (1, "Power $Action Session $Session");
    &Print_Log (11, "$Power_type Power $Action");

    if ($Power_type eq 'manual') {
        &Alert ('Please turn UUT Power ' . uc $Action . '!');
    } elsif ($Power_type eq 'APC') {
        if ($Session < 9)  {
         	$Cmd = "powerswitch.pl $Power_Switch_IP " . lc $Action;
        	$Cmd .= ' p' . $Session if $Action =~ /[off|on]/i;
       		&Print_Log (1, "Power Cmd: $Cmd");
        } elsif ($Session > 8 && $Session < 17 && $Power_Switch2_IP != "") {
            $Cmd = "powerswitch.pl $Power_Switch2_IP " . lc $Action;
        	$Cmd .= ' p' . $Session2 if $Action =~ /[off|on]/i;
        	&Print_Log (1, "Power Cmd: $Cmd");
        } else {
              &Alert ('Please turn UUT Power ' . uc $Action . '!');
          } ;
        &Print_Log (11, "Exec'ing $Cmd");
#        print "Exec'ing $Cmd\n";
        &Exit (999, "No Power_Switch_IP") if $Power_Switch_IP eq '';
        open APC, "$Cmd|" ||
            &Exit (999, "Can\'t start snmp session to APC switch $Power_Switch_IP");
        if ($Action eq 'status') {
            while (<APC>) {
                chomp;
                if (/^P(\d+): (.*)/) {
                    $States[$1] = ($2 eq 'ON ') ? 1
                               : ($2 eq 'Off') ? 0
                               : "";
                } else {
                    die "Can't read APC power status";
                }
            }
            &Print_Status (@States);
        }
        close APC;

    } elsif ($Power_type eq 'LPT') {
        &LPT_Power ($Session, $Action);
    } else {
        die "Invalid entry in testctrl.cfg file Power_type = $Power_type";
    }
    $Stats {'Power'}++ if $Action eq 'ON';  #Count the number of power ups per test
    $TestData {'Power'}=$Power_type . "_" . $Action;
    return ($Erc);
# ? Is this what stats power is for
#    $Stats {'Power'} = $Action if $Action =~ /ON|OFF/;
}


#_______________________________________________________________________________
sub Print_Status {

    my (@States) = @_;
    return if $Quiet;

    my $Str_ON  ='';
    my $Str_OFF ='';
    foreach (1..8) {

        if ($States[$_]) {
            $Str_ON  .= ' ON ';
            $Str_OFF .= '    ';
        } else {
            $Str_ON  .= '    ';
            $Str_OFF .= 'Off ';
        }
    }
    print "\n$Power_type switch:\n\n\tBit:\t 1   2   3   4   5   6   7   8\n";
    print "\t\t$Str_ON\n\t\t$Str_OFF\n";

}
#_______________________________________________________________________________

1;
