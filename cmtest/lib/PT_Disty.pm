################################################################################
#
# Module:      PT_Disty.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:      Subs associated with disty (distribution) utilities
#
# Version:    (See below) $Id: PT_Disty.pm,v 1.11 2012/02/17 17:13:42 joe Exp $
#
# Changes:
#				$Version{'PT_Disty'} = 'v9.3  2006/12/06'; #Added &Chown_Files
#               Copy_Files() added support for tftpboot dir
#               Updated for www push/update
#				$Ver= 'v9.3 1/31/2008'; # Updated versioning
#			    V9.5 3/8/10 added use Sys::Hostname    #Added for Ubuntu 9.10 support
#				v9.6 8/30/10 $Cmd =  "scp -pq mfgroot@";  for ubuntu support
#				Changed to conider root to be ID 1000 or less(ubuntu freindly)
#				Added support for tftpboot using push.pl -bH <site> 01/05/12
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
my $Ver= 'v9.8 1/05/2012'; # Added support for tftpboot using push.pl -bH
my $CVS_Ver = ' [ CVS: $Id: PT_Disty.pm,v 1.11 2012/02/17 17:13:42 joe Exp $ ]';
$Version{'PT_Disty'} = $Ver . $CVS_Ver;
#_____________________________________________________________________________


#package PT_Disty;
#use strict;
use Sys::Hostname;    #Added for Ubuntu 9.10 support should work with Fedora
use PT;

#_____________________________________________________________________________
sub Check_Path {   # Soon to be obsolete...
                   # use PT3 qw(Build_Path);
                   # Takes a full file-spec, checks and if necessary creates
                   #  each element of it's path

    my ($Path, $Create) = @_;

    $Path =~ s/\/$//;          # Lose any trailing '/'

    my (@Check_Path) = split (/\//, $Path);
    pop @Check_Path;                          # Lose the filename
    $Path = join ('/', @Check_Path);          # Humpty-Dumpty

#    &PETC("Checking the existence of dir $Path") if $Verbose;
    print "\tCurrent UserID: $> \n";
    my $Chunk;
    my $Sub_Path = '';
    foreach $Chunk (split (/\//, $Path)) {
        next if $Chunk eq '';
        $Sub_Path .= "/$Chunk";
        if ($Verbose) {
            print "Test: " if  ! $Create;
            print "\&Check_Path: $Sub_Path ";
        }
        if (! -d $Sub_Path) {
            print "required!\n" if $Verbose;
            &Continue;
            if ($Create) {
            	print "Attempting to create path mkdir $Sub_Path\n" if $Verbose;
                $Erc = system "mkdir $Sub_Path> /dev/null 2>&1";
                &Exit ($Erc, "Unable to create dir \'$Sub_Path\'") if $Erc;
            }
        } else {
            print "OK!\n" if $Verbose;
        }
    }

}
#_______________________________________________________________

sub Check_Path_SSH {   # Added for tftpboot distribution support

    my ($Target, $Path, $Create) = @_;

    $Path =~ s/\/$//;          # Lose any trailing '/'

    my (@Check_Path) = split (/\//, $Path);
    pop @Check_Path;                          # Lose the filename
    $Path = join ('/', @Check_Path);          # Humpty-Dumpty

#    &PETC("Checking the existence of dir $Path") if $Verbose;

    my $Chunk;
    my $Sub_Path = '';
    foreach $Chunk (split (/\//, $Path)) {
        next if $Chunk eq '';
        $Sub_Path .= "/$Chunk";
        if ($Verbose) {
            print "Test: " if ! $Create;
            print "\&SSH $Target Check_Path: $Sub_Path ";
        }
        if ( system "ssh $Target ls -d $Sub_Path> /dev/null 2>&1"  ) {
            print "required!\n" if $Verbose;
            &Continue;
            if ($Create) {
                $Erc = system "ssh $Target mkdir $Sub_Path> /dev/null 2>&1";
                &Exit ($Erc, "Unable to create dir \'$Sub_Path\'") if $Erc;
            }
        } else {
            print "OK!\n" if $Verbose;
        }
    }

}
#_______________________________________________________________
sub Cmd {        # Copied from mkhost #!!! Consolidate when mkhost allows includes

    my ($Cmd) = @_;

    my $Str = ($Test_Only) ? 'Test:' : 'Exec\'ing';
    &Print_Padded ("$Str $Cmd", 60);

    unless ($Test_Only) {
        my $Erc = system $Cmd unless $Test_Only;
        &PETC ("\nError $Erc after \'$Cmd\'\! Continue?") if $Erc;
    }
    print "OK\n";

}
#______________________________________________________________________________
sub Chown_Files {      # Proto!!!

    my ($Path) = @_;
    $Path = $Dest if $Path eq '';

    my $Cmd;

    my @Cmds =  ('chown -R mfg', 'chgrp -R mfg', 'chmod -R 755' );

    if ($Host eq $Host_ID) {
        $Cmd =  "cp -p";
    } else {
        $Dest = "$Host:$Dest";
    }
    $Cmd .= " $Source $Dest > /dev/null 2>&1";

    unless ($Quiet) {
        my $Str;
        $Str = "Test only: " if $Test_Only;
        $Str .= "\nch[mod|own|grp]'ing $Path ... ";
        print $Str . "\n";
    }
    foreach $Cmd (@Cmds) {
        my $Erc = system "$Cmd $Path" unless $Test_Only;
        &Exit ($Erc, "Unable to $Cmd") if $Erc;
    }

}
#_____________________________________________________________________________
sub Continue {

    $Erc = 0;
    unless ($Quiet) {

        print "\nRunning test mode\n\n" if $Test_Only;
        print "\tHost     = $Target_Host\n";
        print "\tSource   = $Source\n";
        print "\tDest     = [<Target_Host(s)>:]$Dest";
        print "$Release_Pipe\/" if $Pipe_It;
        print "\n\n";

        exit unless &YN ('Continue?');
    }
}

#______________________________________________________________________________
sub Copy_Files_dep {  # New for v9, and an alternative to the do anything &Distr_File.
                  # This is the main loop called by either push.pl or update.pl
                  # Uses local Vars $From and $To for &SCopy
                  # Mofified for improved www distribution
    my $Item;

    #print ("Copy to the following Hosts: $Hosts\n") if $opt_a;
    foreach $Item (@Files) {
        my (@Segment) = split (/\//, $Item);
         #print " $Item\n" if $Debug;
        my $No_Clobber = 0;

        my $FN     = pop   @Segment;   # Just the File Name
        my $Path   = shift @Segment;   # Path contains just the first subdir only!
        push @Segment, $FN;                           #  "now just you put that back!"
        my $File   = join ('/', @Segment); # File contains the remaining path +FN

        my $From = &Set_Path ($Source, $Path, $File);

        if ($WWW_Path ne '' and  $opt_s and $Path eq 'www') {
              $Dest = $WWW_Path ;
        }
        my $To = $Dest;
        if ($Path ne 'cfgfiles') {
        	if ($Path eq 'tftpboot') {   # JW, only when updating distribution, Added
        		$To = "/" if ! $Pipe_It;
        		print ("Tftpboot Path: $Path\n") if $Verbose;
        		Check_Path("/". $Path . "/" . $File ,0) if ! $Pipe_It && $Target_Host ne $Host_ID;  # Create path JW
        		next if $Pipe_It; # Skip this entry if doing an update
            } else {                                    #JW
            	#$To .= "$Release_Pipe/" if $Pipe_It;   # Original
            	 $To .= "$Release_Pipe/" if ($Pipe_It && $Path ne 'www');

              }
        } else {
            $Path = '' if $Pipe_It;
            $No_Clobber = 1 if $FN eq '.cmtestrc';
        }
        $To   = &Set_Path ($To, $Path, $File);

        &PETC("No_Clobber: $Item") if $No_Clobber and $Debug;
        # next if $Pipe_It and ($FN =~ /^\./);

        next if (-s $To) and $No_Clobber;

        umask 0;
        if ($opt_a) {
            foreach (@Hosts) {
            	next if $_ eq $Host_ID;  # Skip local host JSW
            	if ($Path eq 'tftpboot') {
            		if ( $opt_b)  {           # JW
                    print ("Copy from: $_  Source: $To Dest: $Dest $To\n") if $Verbose;  # JW
                    Check_Path_SSH($_, $To,0) if ($Target_Host ne $Host_ID);  # Create path JW
            		&SCopy ($_, $To, $To );  # JW
            		}
            	} else {
            		print ("Copy from: $_  Source: $From Dest: $To\n") if $Verbose;
            		Check_Path_SSH($_, $To,0) if ($Target_Host ne $Host_ID);  # Create path JW  # JW
                	&SCopy ($_, $From, $To);
                }

            }
        } else {
        	if ( (!($Path =~ /tftpboot/) && ! $opt_b)  ) {
            	Check_Path_SSH($Target_Host, $To,0) if ($Target_Host ne $Host_ID);  # Create path JW
            	print ("Copy target from: $Target_Host  Source: $From Dest: $To\n") if $Verbose;
            	&SCopy ($Target_Host, $From, $To);
            } elsif ($Path eq 'tftpboot') {
            		if ( $opt_b && $opt_X)  {           # JW
                    	print ("Opt b Copy from: $Path Source: $From Dest: $Dest $To\n") if $Verbose;  # JW
                    	Check_Path_SSH($Target_Host, $To,0) if ($Target_Host ne $Host_ID);  # Create path JW
            			&SCopy ($Target_Host, $From, $To );  # JW     ###  $From for local and $To for remote ????
            			} elsif ( $opt_b && $opt_H)  {           # JW
                    	print ("Opt b Copy from: $Path Source: $From Dest: $Dest $To\n") if $Verbose;  # JW
                    	Check_Path_SSH($Target_Host, $To,0) if ($Target_Host ne $Host_ID);  # Create path JW
            			&SCopy ($Target_Host, $To, $To );  # JW     ###  $From for local and $To for remote ????
            			}

              }
        }

        if ($WWW_Path ne '' and  $opt_s and $Path eq 'www') {
           print (" Bypassed --- WWW files chown Dest: $To\n"); # if $Verbose;
           # Does all in path my $Erc = system "chown -R apache:apache $WWW_Path/www" unless $Test_Only;
           #&Exit ($Erc, "Unable to chown apache:apache") if $Erc;
           #my $Erc = system "chown -R apache:apache $To" unless $Test_Only;
    	   #&Exit ($Erc, "Unable to chown apache:apache $To") if $Erc
        }
    }
}

#_______________________________________________________________
sub Copy_Files {  # New for v9, and an alternative to the do anything &Distr_File.
                  # This is the main loop called by either push.pl or update.pl
                  # Uses local Vars $From and $To for &SCopy
                  # Mofified for improved www distribution
    my $Item;
    #print ("Copy to the following Hosts: $Hosts\n") if $opt_a;
    foreach $Item (@Files) {

        my (@Segment) = split (/\//, $Item);

        my $No_Clobber = 0;

        my $FN     = pop   @Segment;   # Just the File Name
        my $Path   = shift @Segment;   # Path contains just the first subdir only!
        push @Segment, $FN;                           #  "now just you put that back!"
        my $File   = join ('/', @Segment); # File contains the remaining path +FN
        print "File Disty is $File $Pipe_It $Release_Pipe\n";
        my $From = &Set_Path ($Source, $Path, $File);

        if ($WWW_Path ne '' and  $opt_s and $Path eq 'www') {
              $Dest = $WWW_Path ;
        }
        my $To = $Dest;
        if ($Path ne 'cfgfiles') {
        	if ($Path =~ /tftpboot/) {   # JW, only when updating distribution, Added
        		$File =~ s/\{\$Release_Pipe\}/$Release_Pipe/;
        		$To = "/" if ! $Pipe_It;
        		print ("Tftpboot Path: $Path  $File\n") if $Verbose;
        		Check_Path("/". $Path . "/" . $File ,0) if ! $Pipe_It && $Target_Host ne $Host_ID;  # Create path JW
        		next if $Pipe_It; # Skip this entry if doing an update
            } else {                                    #JW
            	#$To .= "$Release_Pipe/" if $Pipe_It;   # Original
            	 $To .= "$Release_Pipe/" if ($Pipe_It && $Path ne 'www');

              }
        } else {
            $Path = '' if $Pipe_It;
            $No_Clobber = 1 if $FN eq '.cmtestrc';
        }
        $To   = &Set_Path ($To, $Path, $File);

        &PETC("No_Clobber: $Item") if $No_Clobber and $Debug;
        # next if $Pipe_It and ($FN =~ /^\./);

        next if (-s $To) and $No_Clobber;

        umask 0;
        if ($opt_a) {
            foreach (@Hosts) {
            	next if $_ eq $Host_ID;  # Skip local host JSW
            	if ($Path eq 'tftpboot') {
            		if ( $opt_b)  {           # JW
                    print ("Copy opt ab tftpboot from: $_  Source: $To Dest: $Dest $To\n") if $Verbose;  # JW
                    Check_Path_SSH($_, $To,0) if ($Target_Host ne $Host_ID);  # Create path JW
            		&SCopy ($_, $To, $To );  # JW
            		}
            	} else {
            		print ("Copy opt a relative from: $_  Source: $From Dest: $To\n") if $Verbose;  # JW
                	&SCopy ($_, $From, $To);
                }

            }
        } else {
        	if ( (!($Path =~ /tftpboot/) && ! $opt_b)  ) {
        		print ("Copy opt b target from: $Target_Host  Source: $From Dest: $To\n") if $Verbose;
            	&SCopy ($Target_Host, $From, $To);
            } elsif ($Path eq 'tftpboot') {
            		if ( $opt_b && $opt_X && ! $opt_H )  {           # JW
            			#$From =&Set_Path ('../', $Path, $File);
            			$File =~ s/_$Release_Pipe//;
                        print ("Opt bX Copy from: $Path Source: $From Dest: $Dest $To\n") if $Verbose;  # JW
                    	Check_Path_SSH($Target_Host, $To,0) if ($Target_Host ne $Host_ID);  # Create path JW
            			&SCopy ($Target_Host, "../". $Path . "/" . $File, $To );  # JW     ###  $From for local and $To for remote ????
            			} elsif ( $opt_b && $opt_H)  {           # JW
                    	print ("Opt bH Copy from: $Path Source: $From Dest: $Dest $To\n") if $Verbose;  # JW
                    	Check_Path_SSH($Target_Host, $To,0) if ($Target_Host ne $Host_ID);  # Create path JW
            			&SCopy ($Target_Host, $To, $To );  # JW     ###  $From for local and $To for remote ????
            			}

              }
        }

        if ($WWW_Path ne '' and  $opt_s and $Path eq 'www') {
           print (" Bypassed --- WWW files chown Dest: $To\n"); # if $Verbose;
           # Does all in path my $Erc = system "chown -R apache:apache $WWW_Path/www" unless $Test_Only;
           #&Exit ($Erc, "Unable to chown apache:apache") if $Erc;
           #my $Erc = system "chown -R apache:apache $To" unless $Test_Only;
    	   #&Exit ($Erc, "Unable to chown apache:apache $To") if $Erc
        }
    }
}

#_______________________________________________________________
#_______________________________________________________________
sub Copy_Files_dep {  # New for V30 2/9/15 to handel multi depth.
                  # This is the main loop called by either push.pl or update.pl
                  # Uses local Vars $From and $To for &SCopy
                  # Mofified for improved www distribution
    my $Item;
    my $Path;
    #print ("Copy to the following Hosts: $Hosts\n") if $opt_a;
    print " Showing Files @Files \n";
    foreach $Item ( @Files ) {
    	print " Item $Item $_ \n";
    	if ( $Item  =~ /\// ) {
    			$Path = $Item;
    			$Item = "";
    			print "Set Path $Path\n";
    			foreach ( $Files[1]  ) {    #$Files[$Path]
            		print "Found $_  in Files $Path  \n";
             }
#        } else  {
#                print "Found new section $Item no path\n"
#                $Path = "";
#                foreach $Item ( $Files ) {
#                    print "Found $_  in Files $Path  \n";
#             }
#        }

            }


#        my (@Segment) = split (/\//, $Item);
#         #print " $Item\n" if $Debug;
#        my $No_Clobber = 0;

#        my $FN     = pop   @Segment;   # Just the File Name
#        my $Path   = shift @Segment;   # Path contains just the first subdir only!
#        push @Segment, $FN;                           #  "now just you put that back!"
#        my $File   = join ('/', @Segment); # File contains the remaining path +FN

        my $From = &Set_Path ($Source, $Path, $File);

        if ($WWW_Path ne '' and  $opt_s and $Path eq 'www') {
              $Dest = $WWW_Path ;
        }
#        my $To = $Dest;
#        if ($Path ne 'cfgfiles') {
#            if ($Path eq 'tftpboot') {   # JW, only when updating distribution, Added
#                $To = "/" if ! $Pipe_It;
#                print ("Tftpboot Path: $Path\n") if $Verbose;
#                Check_Path("/". $Path . "/" . $File ,0) if ! $Pipe_It && $Target_Host ne $Host_ID;  # Create path JW
#                next if $Pipe_It; # Skip this entry if doing an update
#            } else {                                    #JW
#                #$To .= "$Release_Pipe/" if $Pipe_It;   # Original
#                 $To .= "$Release_Pipe/" if ($Pipe_It && $Path ne 'www');

#              }
#        } else {
#            $Path = '' if $Pipe_It;
#            $No_Clobber = 1 if $FN eq '.cmtestrc';
#        }
#        $To   = &Set_Path ($To, $Path, $File);

#        &PETC("No_Clobber: $Item") if $No_Clobber and $Debug;
#        # next if $Pipe_It and ($FN =~ /^\./);

#        next if (-s $To) and $No_Clobber;

#        umask 0;
#        if ($opt_a) {
#            foreach (@Hosts) {
#                next if $_ eq $Host_ID;  # Skip local host JSW
#                if ($Path eq 'tftpboot') {
#                    if ( $opt_b)  {           # JW
#                    print ("Copy from: $_  Source: $To Dest: $Dest $To\n") if $Verbose;  # JW
#                    Check_Path_SSH($_, $To,0) if ($Target_Host ne $Host_ID);  # Create path JW
#                    &SCopy ($_, $To, $To );  # JW
#                    }
#                } else {
#                    print ("Copy from: $_  Source: $From Dest: $To\n") if $Verbose;  # JW
#                    &SCopy ($_, $From, $To);
#                }

#            }
#        } else {
#            if ( (!($Path =~ /tftpboot/) && ! $opt_b)  ) {
#            &SCopy ($Target_Host, $From, $To);
#                print ("Copy target from: $Target_Host  Source: $From Dest: $To\n") if $Verbose;
#            } elsif ($Path eq 'tftpboot') {
#                    if ( $opt_b && $opt_X)  {           # JW
#                        print ("Opt b Copy from: $Path Source: $From Dest: $Dest $To\n") if $Verbose;  # JW
#                        Check_Path_SSH($Target_Host, $To,0) if ($Target_Host ne $Host_ID);  # Create path JW
#                        &SCopy ($Target_Host, $From, $To );  # JW     ###  $From for local and $To for remote ????
#                        } elsif ( $opt_b && $opt_H)  {           # JW
#                        print ("Opt b Copy from: $Path Source: $From Dest: $Dest $To\n") if $Verbose;  # JW
#                        Check_Path_SSH($Target_Host, $To,0) if ($Target_Host ne $Host_ID);  # Create path JW
#                        &SCopy ($Target_Host, $To, $To );  # JW     ###  $From for local and $To for remote ????
#                        }

#              }
#        }

#        if ($WWW_Path ne '' and  $opt_s and $Path eq 'www') {
#           print (" Bypassed --- WWW files chown Dest: $To\n"); # if $Verbose;
#           # Does all in path my $Erc = system "chown -R apache:apache $WWW_Path/www" unless $Test_Only;
#           #&Exit ($Erc, "Unable to chown apache:apache") if $Erc;
#           #my $Erc = system "chown -R apache:apache $To" unless $Test_Only;
#           #&Exit ($Erc, "Unable to chown apache:apache $To") if $Erc
#        }
    }
}

#_______________________________________________________________
sub Exit {

    my ($Erc, $Msg) = @_;

    if ($Erc) {
        print "Failed!: Exiting with Erc=$Erc: $Msg\n";
    } else {
        print "Done!\n" unless $Quiet;
    }
    exit (0);
}
#_____________________________________________________________________________
sub File_Mod_Time {                        # Note the reverse use of return values !!

        my ($File) = @_;

        return (0) if ! -s $File;

        my $Age = (-M $File);
        my $Time = time - ($Age * 24 * 60 * 60);

        return ($Time);
}
#_____________________________________________________________________________
sub Get_Release_Pipe {

    my $File = ($opt_x) ? $SCCS_Path : $Release_Path;

      $File .= "/bin/Release.id";

    print "Determining Release pipe ...\n";
    my $Erc = &Read_Cfg_File ($File);
    if ($Erc) {
        print "Error reading the cfg file $File\n";
        exit;
    } else {
        $Release_Pipe = $Pipe;
        &PETC ("Erc = $Erc, Version=$Version, pipe=$Pipe") if $Debug;
    }
}
#_____________________________________________________________________________
sub Init_1st {

                #Globals:
      print ("Setting Globals\n");
     $Util_only = 1;

     our @Hosts = ();
     our @Paths = ();
     our @Files = ();

     our %From2 = ();        # Key = From path, Value = To path
     our $opt_M = '';
     our ($SCCS_Path, $Release_Path, $Source, $Dest, $WWW_Path, $Pipe_It);


# 'B:F:H:X:dfhiqstvx'


     $Erc = 101;


}
#_____________________________________________________________________________
sub Init {
                        # This must be called after &getopts
                        #updated 2/9/15 to do multidimensional lists/dir

        my ($Usage) = @_;

    our $Quiet     = ($opt_q) ? 1 : 0;
    our $Debug     = 1 if $opt_d;
    our $GUI       = 1 if $opt_g;
    our $Verbose   = ($opt_q) ? 0 : ($opt_v) ? 1 : 0;
    our $ChkSumIt  = 1;

    our $Test_Only = ($opt_t) ? 1 : 0;

    our ($Usr, $Grp)  = qw( mfg mfg);

    our $Home         = $ENV{HOME};
    #our $Host_ID      = $ENV{HOSTNAME};
    our $Host_ID      = hostname;
    our $Target_Host  = ($opt_H ne '') ? $opt_H : $Host_ID;
    our $FH           = '00';

    if ($opt_h) {
            print "$Usage\n";
            exit (0);
    }

    print "\n\t\$PPath = $PPath\n\n" unless $Quiet;

    exit if $opt_f; # Deprecated!

    if ($> > 1000) {
            print "\tCurrent UserID: $> \n";
            print "\n\tYou must be \'root\' to run this! Setting Test mode on ...\n\n"
            unless $Test_Only;
                $Test_Only = 1;
        }

    $opt_x = 1 if $opt_X ne ''; #You're defining the VSS path, you must want them
    &Show_INCs;
    &Set_Var ('SCCS_Path',    '/home/ptindle/Dev',          $opt_X, 0);
    &Set_Var ('Release_Path', '/var/local/cmtest/dist', '',     1);

    if ($opt_x) {   # Only available for push.pl
    	print ("pt_disty option x found\n");
        $Source = $SCCS_Path;
        $Dest   = $Release_Path;
    } else {        # push.pl or update.pl
        $Source = $Release_Path;
        $Dest   = $Release_Path;
    }

    $Cfg_File = $Source . 'cfgfiles/push.cfg';

    return;
}
#_________________________________________________________________________
sub Mains_Init {  #Don't call this, copy it to main and edit

#    &Set_Var ('SCCS_Path',    $ENV{'HOME'},         $opt_X, 0);
    if ($opt_f) {
       &Set_Var ('Dest', '/mnt/floppy',             '',     1);
#    } elsif ($opt_H eq '') {
    } else {
            &Set_Var ('Dest', '/usr/local/cmtest',      $opt_F, 1);
    }


#    $Dest_Path .= '/' unless $Dest_Path =~ /\/$/;   # Ensure '..xyz/'

    &Get_Release_Pipe
        unless ($opt_F ne '') or $opt_f;    # They dont use the bucket scheme

    $Cfg_File    = $opt_C unless $opt_C eq '';
    $Cfg_File    = '/mnt/floppy/push.cfg'  if ! -s $Cfg_File
                                           and  -s '/mnt/floppy/push.cfg';
    &Exit (2,  "No push cfg file \'$Cfg_File\') found") if ! -s $Cfg_File;
    print "\tCfg File = $Cfg_File\n" unless $Quiet;

    $Erc = &Read_Init_File ($Cfg_File);
    &Exit (2,  "(Error reading Push Cfg file \'$Cfg_File\')") if $Erc;
    foreach(@Products) {
        $Cfg_File = $Source . "cfgfiles\/push$_.cfg";
    	$Erc = &Read_Init_File ($Cfg_File);
    	&Exit (2,  "(Error reading Push Cfg file \'$Cfg_File\')") if $Erc;
    }

#   push @Files, @Server-Files if $opt_s;
    if ($opt_s or $opt_a) {
       foreach (@Server_Files) {
           push @Files, $_;
       }
    }
    if ($opt_f) {
        my $Cmd =  "mount /dev/floppy /mnt/floppy > /dev/null 2>&1";
        print 'Mounting floppy ...' unless $Quiet;
        system $Cmd if ! -d '/mnt/floppy';
        print "done\n" unless $Quiet;

        foreach ( 'bin', 'lib', 'lib/SigmaProbe', 'cmdfiles' ) {
            my $Dir1 = '/mnt/floppy/' . $_;
            if (! -d $Dir1) {
                my $Cmd =  "mkdir $Dir1 > /dev/null 2>&1" ;
                print "Test: " if $Test_Only and not $Quiet;
                print "Exec'ing $Cmd ...\n" unless $Quiet;
                system $Cmd unless $Test_Only;
            }
        }
    }
}

#_______________________________________________________________________________
sub Invalid {

        my ($Usage) = @_;
        print "$Bell$Usage";
        exit ($Erc);
}


#_______________________________________________________________________________
sub Parent {

    my (@Check_Path) = split (/\//, $_);
    pop @Check_Path;  pop @Check_Path;
    return (join '/', @Check_Path);
}
#_____________________________________________________________________________
sub Print_Info {

# &Print_Info ($Which, $Item, $Path, $FN, $File, $Source, $Dest, $Msg);

    my ($Which, $Item, $Path, $FN, $File, $Source, $Dest, $Msg) = @_;

    print "\n$Which:\n\tItem\t= $Item\n",
                  "\tPath\t= $Path\n\tFile\t= $File\n",
                  "\tSource\t= $Source\n\tDest\t= $Dest\n$Msg\n\n" if $Verbose;

}
#_______________________________________________________________
sub Print_Padded {  #Obsolete: use PT3 qw (Print_Padded)

    my ($Str, $Len) = @_;
    $Len -= length($Str);
    print "$Str ", '.' x $Len, ' ';
}

#_______________________________________________________________________________
sub Proceed {

    $Erc = 0;
    unless ($Quiet) {

        print "\nRunning test mode\n\n" if $Test_Only;
        print "\tHost     = $Target_Host\n";
        print "\tSource   = $Source\n";
        print "\tDest     = [<Target_Host(s)>:]$Dest";
        print "$Release_Pipe\/" if $Pipe_It;
        print "\n\n";

        exit unless &YN ('Proceed');
    }
}
#_____________________________________________________________________________
sub SCopy {

    my ($Host, $Source, $Dest) = @_;
    &PETC("Calling SCopy ($Host, $Source, $Dest)") if $Debug;
    print "Option m $opt_m $Host\n";
    my $Cmd;
    #Check_Path_SSH {   # Added for tftpboot distribution support
    #Check_Path($Host, $Dest,0); # if ($Host ne $Host_ID);
    Check_Path( $Dest,$opt_m) if ($Host eq $Host_ID);
    Check_Path_SSH($Host, $Dest,$opt_m) if ($Host ne $Host_ID);
   # my ($Target, $Path, $Dont_Create) = @_;
    #  $Cmd = "ping -qc1 $Host";
    #  $Erc = `$Cmd`;
    #  chomp $Erc;
    #  &PETC("Cmd returned $Erc");

    $Cmd =  "scp -pq";
    #$Cmd =  "scp -Bpq";
    if ($Host eq $Host_ID) {
        $Cmd =  "cp -p";
    } else {
        $Dest = "$Host:$Dest";
    }
    $Cmd .= " $Source $Dest > /dev/null 2>&1";

    if ($No_Clobber and -s $Dest) {
        print "Skipping overwrite of $Dest\n" unless $Quiet;
        return (0);
    }

    unless ($Quiet) {
        my $Str;
        $Str = "Test only: " if $Test_Only;
        $Str .= "Exec'ing $Cmd ..." if $Verbose;
        $Str .= "\nCopying\t$Source\nto\t$Dest ... ";
        print $Str . "\n";
    }

    my $Erc = system "$Cmd" unless $Test_Only;
    &Exit ($Erc, "Unable to $Cmd") if $Erc;

    print '(not) ' if $Test_Only and not $Quiet;
    print "done\n" unless $Quiet;

}
#______________________________________________________________________________
sub Set_Path {        # Deals with the potential absense of a $Dir

    my ($Path, $Dir, $File) = @_;
    my $Path1 = $Path; # For the Debug PETC below

    $Path .= "$Dir/" unless $Dir eq '' or $Dir eq '.';

         &PETC ("
                 Path1   = $Path1
                 Path2   = $Path
                 Dir    = $Dir
                 File   = $File
                 Rtrns:  $Path$File
           ")
         if $Debug and 1;

    return ($Path . $File);
}
#__________________________________________________________________________
sub Set_Var {  # Assign a value to a variable using switch 1st, if that's
                      #  not set, use the $ENV{cmtest_...} value instead.
                      # Exit if neither, and $Reqd flag set

    my ($Var, $Def, $Switch_Val, $Reqd) = @_;
    my $Env_Var = $ENV{"CmTest_${$Var}"};

        my $LVar = ${$Var};                                                                  # 3rd pref
    $LVar = $Def        if     $LVar       eq '';          # 4th pref
    $LVar = $Env_Var    unless $Env_Var    eq '';          # 2nd pref
    $LVar = $Switch_Val unless $Switch_Val eq '';          # 1st pref

    &PETC ("
                        Var   = $Var
                        Def   = $Def
                        SwVal = $Switch_Val
                        EnVar = $Env_Var
                        Reqd  = $Reqd
                        Rtrns:  $LVar
                  ")
            if 0;

    &Exit (102, "Missing Envar \'CmTest_${Var}\'")
        if $LVar eq '' and  $Reqd;

#   Note: $LVar .= '/' if -d $LVar and ! $LVar =~ /\/$/;  fails!!
    $LVar .= '/' if -d $LVar and ! ($LVar =~ /\/$/);

    ${$Var} = $LVar;
}
#__________________________________________________________________________
1;
__END__

=head1 NAME

  PT_Disty: Perl module for providing code distribution functions

=head1 SYNOPSIS

  use PT_Disty;


=head1 DESCRIPTION



=head1 METHODS

  none

=head2 EXPORT

  None by default.


=head1 AUTHOR

  Paul Tindle, <Paul@Tindle.org>

=head1 LICENSE

  Copyright(C) 2002 Paul Tindle., All Rights Reserved.
  This software is property of Paul Tindle. You may not modify or in any
  way alter this software without prior written permission from the owner.

=head1 SEE ALSO

  CMTest.

=cut

