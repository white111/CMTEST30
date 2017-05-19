#!/usr/bin/perl
######################################################################################
#
# Script:    CMTest.cgi
#
# Author:    Paul Tindle ( mailto:Paul@Tindle.org )
#
# Version:    $Id: CMTest.cgi,v 1.3 2010/03/12 18:51:00 joe Exp $
#
# Descr:     CGI Script to display Mfg Floor Status
#                  - summary form - cloned from status.cgi!
#
# Changes:	 3/8/2010 add versioning, add support for Ubuntu 9.10 apache2
#
# License:   This software is subject to, and may be distributed under, the
#            terms of the Lesser General Public License as described in the
#            file License.html found in this or a parent directory.
#
#######################################################################################

BEGIN { # CGI_Begin v3  2005-11-28

    use CGI::Carp qw(carpout fatalsToBrowser warningsToBrowser);

#    our $LogFile = '/var/log/httpd/cgi.log';    Fedora only
     #Fedora or Ubuntu install
     our $LogFile        = '/var/log/appache2/cgi.log';
     if (-d '/var/log/apache2' ) {
     	$LogFile        = '/var/log/apache2/cgi.log';
     } else {
     	$LogFile        = '/var/log/httpd/cgi.log';
     };

        unshift @INC, "$ENV{HOME}/lib";

    open(LOG, ">>$LogFile")
        or die "Unable to append to logfile \"$LogFile\"\n";
    carpout(*LOG);
    warningsToBrowser(1);
   # fatalsToBrowser(1);

    unshift @INC, './lib';
#    unshift @INC, '/home/ptindle/Dev/lib';
    #unshift @INC, './new-lib';
    unshift @INC, '.';
}

use CMTest_CGI;
&CM_Test_Main;
exit(0);
