#!/usr/bin/perl
######################################################################################
#
# Script:    test.cgi
#
# Author:    Paul Tindle ( mailto:Paul@Tindle.org )
#
# Version:    $Id: test.cgi,v 1.2 2010/03/12 18:51:00 joe Exp $
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

our $Version = '1.4 - 03/08/10';

unshift @INC, "/home/ptindle/lib";
unshift @INC, "/usr/home/ptindle/lib";

BEGIN {
#    our $LogFile = "/tmp/cgi.log";
#    our $LogFile = '/var/log/httpd/carp.log';
 #   my $LogFile = '/var/log/httpd/cgi.log';   Fedora only
     #Fedora or Ubuntu install
     my $LogFile        = '/var/log/appache2/cgi.log';
     if (-d '/var/log/appache2' ) {
     	$LogFile        = '/var/log/appache2/cgi.log';
     } else {
     	$LogFile        = '/var/log/httpd/cgi.log';
     };

    use CGI::Carp qw(carpout fatalsToBrowser warningsToBrowser);
    open(LOG, ">>$LogFile")
        or die "Unable to append to cgi.log: $!\n";
    carpout(*LOG);
}

print <<EOF;

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
<HTML>
 <HEAD>
  <TITLE>Test Page</TITLE>
 </HEAD>
<!-- Background white, links blue (unvisited), navy (visited), red (active) -->
 <BODY BACKGROUND="Stoke4.gif">

  <H1 ALIGN="CENTER">Stoke - Automated Manufacturing Test</H1>
  <P><A href="cmtest_main.cgi" CLASS="standard-b-noline"><STRONG>CM Test</A>
         - The production floor test activity / tools</STRONG></P>
 </BODY>
</HTML>

EOF

exit;
#____________________________________________________________________________________

#____________________________________________________________________________________
