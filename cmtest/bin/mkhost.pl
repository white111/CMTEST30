#!/usr/bin/perl
################################################################################
#
# Module:      mkhost.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      cScript to create the necessary directories and copy files to make
#             either a test host or a site test server
#
# Version:    14.5 2006-07-25 $Id: mkhost.pl,v 1.8 2011/12/12 22:53:34 joe Exp $
#
# Changes:    14.1 - 05/11/16 - Mkdir /var/local/cmtest (for nfs), +&Mk_Dirs
#			 14.2 - 06/04/24 - Mkdir uutcfg
#			 14.3 Updated versioning
#			 14.4 Updates for Ubuntu 9.10 Installs
#			 14.5 Changes for Ubuntu privleged userID 8/20/10
#			 14.6 Uncompleted changes for CentOS5
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

use strict;
use Getopt::Std qw(:DEFAULT);

#_______________________________________________________________________________
=item Start of Main
=cut

    our $OS = ( $ENV{'OS'} eq 'Windows_NT' ) ? 'Win32' : 'Unix';
    our $Linux = 'Ubuntu';  # Added 3/4/10 to support Ubuntu install
    if (! system "cat /etc/*release | grep -q 'Ubuntu'" ) {
    	$Linux = 'Ubuntu';
       } elsif (! system "cat /etc/*release | grep -q 'CentOS'" ){
       $Linux = 'CentOS';
       } else {
        $Linux = 'Fedora';
       }
       print "\n\n\tLinux Type: $Linux\n";
       print "\tCurrent UserID: $> \n";
    our ($Usr, $Grp)  = qw( mfg mfg);
    our $Buckets      = 5;
#    our $Release_Pipe  = $ENV{'CmTest_Release_Pipe'};
    our $NFS_Mount    = '/var/local/cmtest/dist';    # Location of distribution master
    our $NFS_Server   = 'mfg-lws1';
    our $NFS_bin      = "$NFS_Mount/bin";
    our $Path         = '';             # Instead of using pwd
    our $NoLF         = 0;              # 1 =  next print on same line

    my $Usage = "
        Usage: mkhost [ -d | -h | -s | -t | -v | -x  ]
        Where:
            -d:        Debug mode
            -h:        Print this message
            -s:        Make target a server, not just a client
            -t:        Test mode, don't do anything for real!
            -v:        Verbose mode, tell all
            -x:        Attempt to eXecute automatically
        \n";

     our ( $opt_d, $opt_h, $opt_s, $opt_t, $opt_v, $opt_x );
     &getopts ('dhqstvx') || exit ( $Usage );

     if ($opt_h) { print "$Usage"; exit; }

     our $Server    = ($opt_s) ? 1 : 0;
     our $Debug     = ($opt_d) ? 1 : 0;
     our $Test_Only = ($opt_t) ? 1 : 0;;
     our $Verbose   = ($opt_v) ? 1 : 0;
     our $Execute   = ($opt_x) ? 1 : 0;

    my $i;
    if ($Debug) {
        print "OS = $OS\n";
        foreach $i (@INC) {

                print "$i\n";
        }
    }

    &Show_Vars qw( PPath VPath ) if ($Debug);

#    print "\nServer = $Server\nTest_Only = $Test_Only\nVerbose = $Verbose\nP1 = $Phase_1\n";

    if (($OS eq 'Win32') and !$Test_Only) {

        print "This can only be run in earnest on a Linux system but since\n" .
                  " you're so curious, we'll continue in (beneigh) test mode ...";

        $Test_Only = 1;
    }

    unless ($Test_Only) {
    	print "\tCurrent UserID: $> \n";
        die "\n\tYou must be \'root\' to run this! Aborting ...\n\n"
            if $> > 1000;
    }

#    print "Production Release Bucket = \'$Release_Pipe\'\n";
    print "Running test mode\n" if $Test_Only;

    if (-d '/usr/local/cmtest/a') {
         &PETC ('Dist path already exists! Overwrite everything [y|n]? [y]:');
    }

#    print "\nServer = $Server\nTest_Only = $Test_Only\nVerbose = $Verbose\nP1 = $Phase_1\n";

=item check the user and group existance
=cut


    my $Erc = system "cd \~$Usr > /dev/null";
    if ($Erc) {
        print "Create a user account for $Usr then rerun...! Aborting\n";
        exit;
    }


=item Mount the tmp partition
=cut
#        This is already done, since this script should be running for there!
#        &Mk_Dir ('server');
#        &Cmd ('mount server:/vol/vol2/cmtest server');

=item Check/Install required Linux modules
=cut
    my $Package;
    foreach $Package qw(
                       Expect
                       Time::HiRes
                       Net::SNMP
                       Device::ParallelPort
                       Device::ParallelPort::drv::parport
                       Sys::PortIO
                       ) {

        &CPAN_Install ($Package) if &Check_Perl_Module ($Package);
    }

    &Check_RPM ( 'minicom');
     &Check_RPM ( 'xinetd');
     #&Check_RPM ( 'tftpd');        #### Centos
     &Check_RPM ( 'tftp');
    if ($Linux eq 'Ubuntu') {
    	&Check_RPM ( 'openssh-server');
    }

    our $Erc = &Cmd ('which minicom');
    &PETC('Install the following modules before proceeding: minicom') if $Erc;
      #	&Check_RPM ( 'heirloom-mailx');        #### Centos
		&Check_RPM ( 'sendmail');
#        &Cmd ('umount server');
#        &Cmd ('rmdir server');

=item Create the base directory for the code buckets
=cut

    $Path = &Make_FS ('/usr/local');
#!!!debug    &Mk_Dirs ('/var/local/cmtest/dist/Java');


=item Create each of the code buckets for 'bin', 'lib' and 'cmdfiles'
=cut


    my $Dx = 'a';
    $i = 0;
    while ($i < $Buckets) {

        &Mk_Dir ("$Path/$Dx");
        &Mk_Dir ("$Path/$Dx/bin");
        &Mk_Dir ("$Path/$Dx/lib");
        &Mk_Dir ("$Path/$Dx/lib/SigmaProbe");
        &Mk_Dir ("$Path/$Dx/cmdfiles");
        &Mk_Dir ("$Path/$Dx/Java");
        &Mk_Dir ("$Path/$Dx/uutcfg");

        $i++; $Dx++;
    }

=item Create other dirs
=cut

    &Mk_Dir ("$Path/ipc");
    &Cmd ("chmod 777 $Path/ipc");
    &Mk_Dir ("$Path/SigmaProbe"); # Assuming we want it in the NFS path
    &Mk_Dir ('/var/local/cmtest'); # Needed on all anyway (for the mount)

=item Create server / NFS stuff
=cut
    if ($Server) {

        &Make_FS ('/var/local');
        &Mk_Dir ('/var/local/cmtest/dist');
        &Mk_Dir ('/var/local/cmtest/dist/bin');
        &Mk_Dir ('/var/local/cmtest/dist/lib');
        &Mk_Dir ('/var/local/cmtest/dist/lib/SigmaProbe');
        &Mk_Dir ('/var/local/cmtest/dist/cfgfiles');
        &Mk_Dir ('/var/local/cmtest/dist/cmdfiles');
        &Mk_Dir ('/var/local/cmtest/dist/uutcfg');
        &Mk_Dir ('/var/local/cmtest/dist/www');
        &Mk_Dir ('/var/local/cmtest/dist/www/cgi-bin');
        &Mk_Dir ('/var/local/cmtest/dist/www/cgi-bin/lib');
        &Mk_Dir ('/var/local/cmtest/dist/www/html');
        &Mk_Dir ('/var/local/cmtest/dist/Java');
        &Mk_Dir ('/var/www/html');
        &Mk_Dir ('/tftpboot');
        &Mk_Dir ('/tftpboot/OS_A');
        &Mk_Dir ('/tftpboot/OS_B');
        &Mk_Dir ('/tftpboot/OS_C');
        &Mk_Dir ('/tftpboot/OS_D');
        &Mk_Dir ('/tftpboot/OS_E');
        &Mk_Dir ('/tftpboot/diag_A');
        &Mk_Dir ('/tftpboot/diag_B');
        &Mk_Dir ('/tftpboot/diag_C');
        &Mk_Dir ('/tftpboot/diag_D');
        &Mk_Dir ('/tftpboot/diag_E');
        #touch log files

        if ($Linux eq 'Ubuntu') {
        	&Check_RPM ( 'apache2-mpm-itk');
        } else {
        	&Check_RPM ( 'httpd');
        }
#        &Cmd ('chown 777 /var/log/httpd');     # ubuntu installing apache2  directories are at /var/log/apache2
		&Mk_Dir ('/var/log/httpd') if ($Linux eq 'Ubuntu') ;    # Added for Ubuntu
        &Mk_Dir ('/var/log/httpd/cmtest');
        &Mk_Dir ('/var/www/cgi-bin') if ($Linux eq 'Ubuntu') ;    # Added for Ubuntu
        &Mk_Dir ('/var/www/cgi-bin/lib');

        unless (&Is_Running ('httpd', 0, 'apache')) {
            &PETC('Start Apache daemons in Applications(menu)::System Settings::Server Settings::Services');
        }
        #touch summary.log, ...
        #chown apache
    } else {
        print "\n\n\tMake sure you have an entry in /etc/fstab:\n";
        print "\n\t\t$NFS_Server\:/var/local/cmtest <tab> /var/local/cmtest <tab> nfs <tab> defaults <tab> 0 0\n";
        &PETC();
        system "mount $NFS_Server\:/var/local/cmtest /var/local/cmtest";
   	exit;

# Done
    }



#    $Path = "$Path/$Release_Pipe/bin";

=item Run the push utility on the site server if necessary
=cut


    print "Path=$Path\n" if $Debug;
    if (! -f "$Path/cmtest.pl") {

&PETC('Now run push.pl manually');
exit;
#die "\n\tProduction Release Bucket not declared \(source .cmtestrc and rerun\)! Aborting ...\n\n"
#     if $Release_Pipe eq '';
        print "$Path/cmtest.pl doesn\'t exist!\n" if $Debug;
        if (-d $NFS_bin) {
            print "NFS bin = \'$NFS_bin\' exists!\n" if $Debug;
            print "Starting update utility ...\n";
            &Cmd ("$NFS_bin/update.pl");
        } else {
            print "NFS bin = \'$NFS_bin\' does NOT exists!\n" if $Debug;
            if ($Execute) {
                print "Execute true\n" if $Debug;
                print "Running the push utility on $NFS_Server ...\n";
                &Cmd ("ssh $NFS_Server /home/ptindle/bin/push.pl -H $ENV{HOSTNAME}");
            } else {

                die "Please run push.pl \'-H $ENV{HOSTNAME}\', then run this again (or use -x)";
            }
        }
    } else {

        print "cmtest.pl already exists in $Path - skipping push/update!\n";
    }


    print "Please add \'$ENV{HOSTNAME}\' to the push.cfg file on \'$NFS_Server\'\n";
    print "done\n";

    exit;

=item *** End of main ***
=cut

#_______________________________________________________________
sub Check_Perl_Module {

    my ($Name) = @_;
    &Print_Padded ("Checking perl module $Name", 60);
    my $Erc = system "perl -e \"use $Name\" > /dev/null 2>&1";
    my $Msg = ($Erc) ? 'Missing!' : 'OK';
    print "$Msg\n";

    $Erc = ($Erc) ? 1 : 0;
    return ($Erc);
}
#_______________________________________________________________
sub CPAN_Install {

    my ($Name) = @_;
    &Print_Padded ("Installing perl module $Name", 60);
    my $Cmd = "perl -MCPAN -e \"install $Name\"";

    unless ($Execute) {
        print "Confirm that you have run:\n\t$Cmd\n\n";
        &PETC();
        return;
    }

    my $Erc = &Cmd ( $Cmd, 1);
    $Erc = ($Erc) ? 1 : 0;
    return ($Erc);

}
#_______________________________________________________________
sub Check_RPM {

    my ($Name) = @_;
    my $Buf = 'none';

    if ($Linux eq 'Ubuntu') {
     	&Print_Padded ("Checking apt-get module $Name", 60);
        $Buf = `sudo apt-get install  $Name --assume-yes --install-recommends check` ;
    } elsif ($Linux eq 'CentOS') {
       	&Print_Padded ("Checking YUM module $Name", 60);
    	$Buf = `yum install $Name`;
    } else {
    	&Print_Padded ("Checking RPM module $Name", 60);
    	$Buf = `rpm -qa|grep -i $Name`;
       };

    if ($Buf =~ /$Name/) {
        print "OK\n";
        # &PETC("System returned $Buf for $Name");
    } else {
    	if ($Linux eq 'Ubuntu') {
    	print "FAILED!\n\n\tPlease run $Erc = \"sudo apt-get install $Name\" are restart...!\n\n";
    	} else {
        # Not useful, since it runs in background...: my $Erc = `rpm -i $Name`;
        print "FAILED!\n\n\tPlease run $Erc = \"rpm -i $Name\" are restart...!\n\n";
        }
        exit;
    }
}
#_______________________________________________________________
sub Cmd {

    my ($Cmd, $Verbose) = @_;

    my $Str = "Exec\n" . ($Test_Only) ? 'Test:' : 'Exec\'ing';
    &Print_Padded ("$Str $Cmd", 60);

    $Str = "[Test only]";
    unless ($Test_Only) {

        $Cmd .= "> /dev/null 2>&1" unless $Verbose;
        my $Erc = system $Cmd;

        &PETC ("\nError $Erc after \'$Cmd\'\! Continue?") if $Erc;
            $Str = ($Erc) ? 'FAILED' : 'OK';
         }

    if ($NoLF) {
        print $Str, ' ' x 20-length($Str), "\r";
    } else {
        print "$Str\n";
    }
    return ($Erc);

}
#____________________________________________________________________________
sub Is_Running {        # Copied from PT 11/10 - Copied from PT2 (10/05
                        # Stripped down to Linux only, and look anywhere in the string

return (0); #!!! Broken!

     my ($Grep_Str, $Owner) = @_;
     my $Its_Running = 0;

     my ($Cmd, $pField);

     $Owner = 'root' if $Owner eq '';
     $Cmd = 'ps -u $Owner';

     open PS, "$Cmd|" || &Exit (999, "Error opening pipe to ps");

     while (<PS>) {
         $Its_Running = 1 if /^$Grep_Str/;
         &PETC("Looking for $Grep_Str in $_: = " . $Its_Running)
     }
     close PS;

     return ($Its_Running);
}

#_______________________________________________________________
sub Make_FS {
                # Create all the dirs either local or on site servers NFS
    my ($Path) = @_;

    $Path .= '/cmtest';  # Either '/var/local/cmtest' or '/usr/local/cmtest'

    &Mk_Dir ($Path);
    &Mk_Dir ("$Path/logs");
    &Mk_Dir ("$Path/logs/logfiles");
    &Mk_Dir ("$Path/stats");
    &Mk_Dir ("$Path/stats/system");

    return ($Path);
}

#_______________________________________________________________
sub Mk_Dir {

    my ($Dir) = @_;

    &Print_Padded ("Checking directory $Dir", 60);

    if (-d $Dir) {
            print "OK\n";
            return;
    }
    print "Required!\n";
    die "Can\'t mkdir $Dir since file of same name exists" if -f $Dir;

#    $NoLF = 1;
    &Cmd ("mkdir $Dir");
    &Cmd ("chmod 775 $Dir");
    &Cmd ("chown $Usr $Dir");
    &Cmd ("chgrp $Grp $Dir");

}

#_______________________________________________________________
sub Mk_Dirs {

    my ($Dir) = @_;

    &Print_Padded ("Checking directory $Dir", 60);

    if (-d $Dir) {
            print "OK\n";
            return;
    }
#!!!debug
# We should really use PT3 qw(Build_Path);
die;
    $NoLF = 1;
    my $Tree;
    my $Chunk;
    my @Chunks = split ( /\//, $Dir );
    foreach $Chunk (@Chunks) {
        $Tree .= "/$Chunk" unless $Chunk eq '';
        &PETC($Tree);
        &Mk_Dir ($Tree, 1);
    }
    print "\n";
    $NoLF = 0;
}
#_______________________________________________________________
sub Move_Link {

        my ($Link_Name, $Target) = @_;
        $Target = $Link_Name . '.pl' if ! defined $Target;

        &Make_Link ($Link_Name, $Target);

}
#_______________________________________________________________
sub Print_Padded {

    my ($Str, $Len) = @_;
    $Len -= length($Str);
    print "$Str ", '.' x $Len, ' ';
}

#__________________________________________________________________________________
#From File.pm:
#_______________________________________________________________
sub fnstrip {

#        Returns specified portions of a filename

#        Invocation: fnstrip (c:/tmp/foo.txt, X)

#        X:        Returns:
#        0        c:/tmp/foo.txt
#        1        c:/tmp/
#        2        c:/tmp/foo
#        3        foo.txt
#        7        foo
#        8        txt

        my (@Ret, @Chunks, @Tmp) = ();
        my ($Full_FN, $Specifier) = @_;
        my ($Foo);

        $Ret[0] = $Full_FN;
        $Full_FN =~ s|\\|/|g;

        @Chunks = split (/\//, $Full_FN);
        $Ret[3] = pop (@Chunks);

        $Ret[1] = substr ($Full_FN, 0, length($Full_FN)-length($Ret[3]));

        @Tmp = split (/\//, $Full_FN);
        $Foo = pop (@Tmp);
        ($Ret[7], $Ret[8]) = split (/\./, $Foo);

        $Ret[2] = $Ret[1] . $Ret[7];

        return ($Ret[$Specifier]);
}
#__________________________________________________________________________________
# From PT.pm 9to make it standalone!:
#_______________________________________________________________
sub Exit {

    exit;
}
#__________________________________________________________________________________
sub PETC {

#   Press
#   _ Enter
#     _ To
#       _ Continue
#         _


        my ($MSG) = @_;
        my ($X);
        our $PETC_Dont_Stop;

        unless (@_) { $MSG = 'Press <CR> to Continue, Q to End, R to Run'; }

        unless ($PETC_Dont_Stop) {

            printf "$MSG: ";
            chop ($X = <STDIN>);
            $X = "\U$X";
            if ($X eq 'Q') { &Exit (198, "PETC Abort"); }
            if ($X eq 'R') { $PETC_Dont_Stop = 1; }
        }


        return $X;
}
#_______________________________________________________________
