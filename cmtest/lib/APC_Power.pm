################################################################################
#
# Module:     APC_Power.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      SCommon BEGIN block code
#
# Version:    (See below) $Id: APC_Power.pm,v 1.3 2008/02/21 00:00:27 joe Exp $
#
# Changes:   1 09/18/05 Cloned from PT. These are cmtest released functions
#
# Still ToDo:
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1993 - 2005 Paul Tindle. All rights reserved.
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
my $Ver= 'v1.1 1/31/2008'; # Updated versioning
my $CVS_Ver = ' [ CVS: $Id: APC_Power.pm,v 1.3 2008/02/21 00:00:27 joe Exp $ ]';
$Version{'APC_Power'} = $Ver . $CVS_Ver;
#______________________________________________________________________________
package APC_Power;

use strict;
require Exporter;
use Net::SNMP;

my @ISA = qw(Exporter);
my @EXPORT_OK = qw(

        APC_Power
        power
);

sub APC_Power {

    my ($action, $port, $Delay) = @_;

    my $sPDUOutletControlTable_oid = "1.3.6.1.4.1.318.1.1.4.4.2";
    my $sPDUOutletCtl = "$sPDUOutletControlTable_oid.1.3";
    my $sPDUOutletCtlName = "$sPDUOutletControlTable_oid.1.4";

    my (%portNames);
    my (%portStatus);
    my $l;
    my $a;

    my $result;
    our %opts;

    my %portIPs = (
            "machine1"        => "1",
            "machine2"        => "2",
            "machine3"        => "3",
            "machine4"        => "4",
            "machine5"        => "5",
            "machine6"        => "6",
            "machine7"        => "7",
            "machine8"        => "8"
    );

    my @statusArray = ("outletOn",
            "outletOff", "outletReboot", "outletUnknown", "outletOnWithDelay",
            "outletOffWithDelay", "outletRebootWithDelay");


    my ($session, $error) = Net::SNMP->session(
            -hostname => "$hostname",
            -community => "$community"
    );

    if (!defined($session)) {
            printf("ERROR opening SNMP session: %s.\n", $error);
            exit 1;
    }

    # find out what the power switch thinks the host names are.
    # we'll use these to see if anything is obviously wrong.
    getPortNames();
    getOutletStatus();
    checkInternalLists();

#    getopts('Ddv', \%opts);


    if ($action eq "status") {
            printStatus($port);
            return (0);
    }

    for ($l = 0; $l < 7; $l++) {
            if ("$statusArray[$l]" eq "$action") {
                    $a = $l + 1;
                    last;
            }
    }

    my $oid = "$sPDUOutletCtl.$port";
    $result = $session->set_request( -varbindlist => [$oid, INTEGER, $a] );

    if (!defined($result)) {
            print ("Error:  Action NOT successful.\n");
            exit(1);
    }

    return;
}

sub getPortNames {
        my $x;
        for ($x = 1; $x < 9; $x++) {
                my $oid = "$sPDUOutletCtlName.$x";
                my $result = $session->get_request(
                        -varbindlist => [$oid]
                );

                if (!defined($result)) {
                        printf("ERROR getting host names: %s.\n", $session->error);
                        $session->close;
                        exit 1;
                }
                $portNames{$x} = $result->{$oid};
        }
}

sub getOutletStatus {
        my $x;
        for ($x = 1; $x < 9; $x++) {
                my $oid = "$sPDUOutletCtl.$x";
                my $result = $session->get_request(
                        -varbindlist => [$oid]
                );

                if (!defined($result)) {
                        printf("ERROR getting outlet status: %s.\n", $session->error);
                        $session->close;
                        exit 1;
                }
                $portStatus{$x} = $result->{$oid};
        }
}

sub printStatus {
        my $x;
        my ($port) = $_[0];

        if ($port == 0) {
                for ($x = 1; $x < 9; $x++) {
                        printf("Power switch: %d %-10s: %d (%s)\n", $x, $portNames{$x}, $portStatus{$x}, getStatus($portStatus{$x}));
                }
        } else {
                printf("Power switch: %d %-10s: %d (%s)\n", $port, $portNames{$port}, $portStatus{$port}, getStatus($portStatus{$port}));
        }

}

sub getStatus {

        return $statusArray[$_[0] - 1];

}

sub parseOptions {

        my @argv = @_;
        my $wport;
        my $waction;

        if ($#argv < 1 && $argv[0] ne "status") {
                usage();
        }

        my $action = $argv[0];
        my $object = $argv[1];
#
        if ($object =~ /p([1-8])/) {
                $wport = $1;
        } elsif ($object =~ /^[0-9]+\.[0-9]+\.[0-9]+\.([0-9]+)$/) {
                # it's an ip address.  take the last chunk.
                my $twhost;
                $twhost = getPortNameFromIP($1);
                if ($twhost eq "") {
                        print("No host match found for IP address $object\n");
                        exit 1;
                }
                $wport = getPortFromPortName($twhost);
                if ($wport eq "") {
                        print("Power switch doesn't know about this port.\n");
                        exit 1;
                }
        } elsif ($object =~ /^([0-9]{1,3})$/) {
                # it's an ip address.  take the last chunk.
                my $twhost;
                $twhost = getPortNameFromIP($1);
                if ($twhost eq "") {
                        print("No host match found for IP address $object\n");
                        exit 1;
                }
                $wport = getPortFromPortName($twhost);
                if ($wport eq "") {
                        print("Power switch doesn't know about this port.\n");
                        exit 1;
                }
        } else {
                $object =~ s/\..*//g;
                $wport = getPortFromPortName($object);
                if ($wport eq "" && $action ne "status") {
                        print("Power switch doesn't know about this port.\n");
                        exit 1;
                } elsif ($action eq "status") {
                        $wport = 0;
                }
        }

        # now figure out what action to take.

        if ($action eq "on") {
                if (! $Delay) {
                        verboseprint ("Turning port $wport on.\n");
                        $waction = "outletOn";
                } else {
                        verboseprint ("Turning port $wport on with delay.\n");
                        $waction = "outletOnWithDelay";
                }
        } elsif ($action eq "off") {
                if (! $Delay) {
                        verboseprint ("Turning port $wport off.\n");
                        $waction = "outletOff";
                } else {
                        verboseprint ("Turning port $wport off with delay.\n");
                        $waction = "outletOffWithDelay";
                }
        } elsif ($action eq "reboot" | $action eq "cycle") {
                if (! $Delay) {
                        verboseprint ("Rebooting port $wport.\n");
                        $waction = "outletReboot";
                } else {
                        verboseprint ("Rebooting port $wport with delay.\n");
                        $waction = "outletRebootWithDelay";
                }
        } elsif ($action eq "status") {
                $waction = "status";
        } else {
                print "Invalid action.\n";
                exit(1);
        }
        return ($wport, $waction);;

}

sub getPortNameFromIP {

        my $l;
        my $tmp = $_[0];

        foreach $l (keys(%portIPs)) {
                if ($portIPs{$l} == $tmp) {
                        return $l;
                }
        }
        return "";
}
sub getPortFromPortName {

        my $portname = $_[0];
        my $match = 0;
        my $l;
        my $tmp;

        foreach $l (keys(%portNames)) {
                if ($portNames{$l} =~ /^$portname$/i) {
                        return $l;
                }
        }
        return "";
}

sub usage {

print <<EOM;
usage: $0 [-dDv] action object
Options:
        -d        delay
        -D        debug
        -v        verbose

actions:
        on
        off
        delay
        status

objects:
        p<n>                port number n
        <n>                last IP address octet n
        xxx.xxx.xxx.<n>        IP address n
EOM

        exit(1);
}

sub dangerWillRobinson {

print <<EOM;
******************************************************************
* DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER *
******************************************************************
I have an internal list that translates hostnames to physical ports.
I checked the power switches against this list and they don't match.
This implies that you've made some changes and forgot to tell the power
switch about them, or forgot to tell me about them.

The problem is that I use the internal tables of the power switch in
order to figure out what goes where.  Because there is no consistency,
I will have to assume that things are not where I think they are.
Proceeding in these circumstances is dangerous.

Please fix either my internal lists, or the tables in the power
switch.

I'm aborting now.
******************************************************************
* DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER *
******************************************************************
EOM

        exit(1);
}

sub checkInternalLists {

        my $x;
        for ($x = 1; $x < 9; $x++) {
                if (lc($internallist{$x}) ne lc($portNames{$x})) {
                        dangerWillRobinson();
                }
        }
}

sub debugprint {

    print $_[0] if $Debug;

}

sub verboseprint {

    print $_[0] unless $Quiet;
}
1;
