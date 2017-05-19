#!perl
######################################################################################
#
# Script:    CMTest(-win).cgi ( 2 different versions! )
#
# Author:    Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:     CGI Script to display Mfg Floor Status
#                  - summary form - cloned from status.cgi!
#
# License:   This software is subject to, and may be distributed under, the
#            terms of the Lesser General Public License as described in the
#            file License.html found in this or a parent directory.
#
#######################################################################################

BEGIN { # CGI_Begin_4_Win v3  2005-11-28

    use CGI::Carp qw(carpout fatalsToBrowser warningsToBrowser);

    our $LogFile = '/tmp/cgi.log';

    open(LOG, ">>$LogFile")
        or die "Unable to append to logfile \"$LogFile\"\n";
    carpout(*LOG);
    warningsToBrowser(1);

    unshift @INC, './lib';
    unshift @INC, '.';
    unshift @INC, 'X:/NAS-2/NAS/PT/Master/Dev/lib';
}

use CMTest_CGI;

&CM_Test_Main;
exit(0);
