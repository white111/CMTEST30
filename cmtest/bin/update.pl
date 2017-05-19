#!/usr/bin/perl -I /usr/local/cmtest
################################################################################
#
# Module:      update.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:       Utility to update Test Automation code locally
#
# Version:    6.5 $Id: update.pl,v 1.6 2011/12/12 22:53:34 joe Exp $
#
# Changes:	  6.3   2005/11/17  Uses &Copy_Files, new BEGINing
#			  6.4	  2006/12/06  # Updated for www push/updateUpdated versioning
#			  Release 2005-11-17
#			  6.5 Updated versioning
#
# Still ToDo:
#
# License:   This software is subject to and may be distributed under the
#            terms of the GNU General Public License as described in the
#            file License.html found in this or a parent directory.
#            Forward any and all validated updates to Paul@Tindle.org
#
#            Copyright (c) 1995 - 2005 Paul Tindle. All rights reserved.
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################

BEGIN { # Disty 2005-11-16 v3
		#Corrected S option and siteserver test

    our $OS = ($ENV {'OS'} eq 'Windows_NT') ? 'Win32' : 'Linux';

    my (@Check_Path) = split (/\/|\\/, $0);
    pop @Check_Path;  pop @Check_Path;      # $FN, then 'bin'
    our $PPath = join '/', @Check_Path;   # Now contains our root directory
        $PPath = '..' if $PPath eq '';      # for a $0 of ./

    our $Tmp;

    if ($OS eq 'Win32') {
        die "Nah!";
        $Tmp = $ENV{'TMP'};
    } else {
        $Tmp = "$ENV{'HOME'}/tmp";
    }

    pop @INC;
    unshift @INC, "$PPath/lib";
    unshift @INC, "$ENV{'LIB'}/lib";
    unshift @INC, '.';

}





#use warnings;
use File;
use Getopt::Std qw(:DEFAULT);
use Logs;
use PT;
use PT_Disty;
use Test;

#_______________________________________________________________
# main:

     &Init_1st;  #PT_Disty::Init_1st
     $Pipe_It = 1;

     my $Usage = "
    Usage: $0 [-dfhqstvx] [-F <Out Path>] [-V 1|2|3]\n
      Where:
         -d:     Debug mode
         -F:     Push to an explicit File system path
         -h:     Print this Help message
         -m:	 Check and create paths as needed with a prompt
         -q:     Quiet mode
         -s:     include site Server files
         -t:     Test only, don't execute
         -V:     Verbosity level
";
#         -v:     Show version
            # Process the command line arguments...
    my $siteserver = 0;
    &getopts ('F:dhmqstvV') || &Invalid ($Usage);

    &Init ($Usage);  #PT_Disty::Init
    &Mains_Init;    # Moved here to init Hosts before checking for site server JSW

    foreach (@Hosts)  {      # Added to get around problem with  if (defined $Hosts{$Host_ID}
    		if ($Host_ID eq $_) {
    			print ("Found Site Server $Host_ID\n") ;
    			$siteserver = 1;
    		}
    	};

    	if ($siteserver && $opt_s) {
    	#if (defined $Hosts{$Host_ID})   # this statemen was returning nothing why ??
    				 				# This system is on push.cfg's [Hosts] list
                                     #  so we're running on a site-server
        $opt_s = 1;
        print("Site Server option Selected\n");
        &Set_Var ('WWW_Path', '/var', '', 1);
        print (" WWW Path set to $WWW_Path \n");
    } elsif ($opt_s) {
    	print("This machine not found in site server list: $Host_ID\n");
    	print("Found the following Hosts:@Hosts\n");
        $WWW_Path = '';
    }  else {
       	$WWW_Path = '';
       }
    $Dest = '/usr/local/cmtest/';
# Now done in Init:    $Target_Host = $Host_ID;            # Force a cp not an scp
    &Proceed;
   	&Show_File_Attrs ($Source, $Dest . $Release_Pipe, @Files);


    my $Str = "Files on the Archive list:\n";
    if (@Files4Archive) {
        # Archive them first
        print "$Str\t$_\n";
        $Str = '';
    }

    if (@Files4Update and !$Test_Only ) {
        if (&YN ('Update needed files')) {
            @Files = @Files4Update;
            &Copy_Files;        # PT_Disty
        }
    }
   # if ($siteserver && $opt_s) { #We need to change owners to apache(Current web server) JSW
   # 	unless ($Quiet) {
   #     	my $Str;
   #     	$Str = "Test only: " if $Test_Only;
   #     	$Str .= "chown'ing $WWW_Path/www... ";
   #     	print $Str . "\n";
   # 	}
	#}

    &Exit (0, "Done!");
#_______________________________________________________________

