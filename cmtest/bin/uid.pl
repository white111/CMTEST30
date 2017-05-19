#!/usr/bin/perl
################################################################################
#
# Module:      uid.pl
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#
# Descr:       Utility for appending encrypted user_ids to a current
#                 data file, typically maintained in ../cfgfiles/users.cfg and
#                 distributed to /usr/local/cmtest/users.cfg
#
# Version:    See Below
#
# Changes:       $Ver = 'v0.1 - 2005-12-02';
#   			$Ver = 'v0.2 - 2006-02-23'; #  Uses encryption key (Init::Gobals-> $Key)
#   			$Ver = 'v1.1 - 2006-03-02'; #  Cleaner UI ->CVS
#   			$Ver = 'v1.2b - 2006-03-02'; #  CVS Id, use new short Write_Data_File calls
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
my $Ver= 'v1.3 1/31/2008'; # Updated versioning
my $CVS_Ver = ' [ CVS: $Id: uid.pl,v 1.3 2008/02/20 23:05:33 joe Exp $ ]';
$Version{'uid'} = $Ver . $CVS_Ver;

=item  To Do:
#           1) [Securely] Save a master user_id | user Name | current euid
#              to allow for regeneration of all keys should the master key
#              need to change
#
#           2) Add getopts to include CLSs:
#               -b batch create from master (above)
#               -c create new users.cfg file
#               -m multiple adds (current mode) default: 1 add only
#                See below BEGIN block
#
=cut
$| = 1;

BEGIN { # 2005-09-12 v2

    our $OS = ($ENV {'OS'} eq 'Windows_NT') ? 'Win32' : 'Linux';

    my (@Check_Path) = split (/\/|\\/, $0);
    pop @Check_Path;  pop @Check_Path;      # $FN, then 'bin'
    our $PPath = join '/', @Check_Path;   # Now contains our root directory
        $PPath = '..' if $PPath eq '';      # for a $0 of ./
    our $Cfg_File;
    our $Tmp;

    if ($OS eq 'Win32') {
         $Cfg_File = "$PPath/cfgfiles/testctrl.defaults.cfg";
         $Tmp = $ENV{'TMP'};
    } else {
         $Cfg_File = '/usr/local/cmtest/testctrl.cfg';
         $Tmp = "$ENV{'HOME'}/tmp";
    }

    pop @INC;
    unshift @INC, "$PPath/lib";
#    unshift @INC, "$ENV{'LIB'}/lib";
    unshift @INC, '.';

    our $CmdFilePath = "$PPath/cmdfiles";
}

our %Version = (
    'main(uid.pl)' => $Ver . $CVS_Ver
);

print "\n\t\$PPath=$PPath\n\n";

#use Cwd qw( abs_path );
use Getopt::Std qw(:DEFAULT);
#use Time::HiRes qw(gettimeofday usleep);


################################################################################

use Init;
use Logs;
use PT;
use DataFile;
use Stats;

print "Starting $0 version $Ver\n\n";

#&Init_All (1);
#&Whos_Running;

our %User_ID   = ();
our %User_Level = ();

&Globals;

$Debug = 1;

my $File   = "$PPath/cfgfiles/users.cfg";
my $Exists = (-f $File) ? 1 : 0;
my $Create = (!$Exists and &YN ("Can\'t find existing encrypted userid file $File! Create?"))
           ? 1 : 0 ;

#&Init_Also (1); # or just "
our $XLOG  =  $ENV{'HOME'} . '/tmp/uid.log';

exit unless $Create or $Exists;

unless ($Create) {
    my $Erc = &Read_Data_File ($File);
    &PrintLog ("Read_Data returned a $Erc");
}

my $Count = &Print_Debug;
&PrintLog ("Read eUIDs for $Count existing users");

my $Done  = 0;
my $Added = 0;
while (!$Done) {
    my ($Name, $UID, $Level) = &Add_User;
    if ($Name eq '') {
        #$Done = &YN ('Finished');
        $Done = 1;
    } elsif (defined $User_ID{$UID} and
             $User_ID{$UID} ne $Name) {
        print "\n";
        &PrintLog ("Key already defined for user $User_ID{$UID}!");
        sleep 1;
    } else {
        $User_ID{$UID}    = $Name;
        $User_Level{$UID} = $Level unless $Level eq '';
        $Added++;
    }
}

unless ($Added) {
#    print "Added $Added new users\n";
#} else {
    &PrintLog ('No new users added...!');
    exit;
}

&Print_Debug;

print "\n\nUpdating $File with $Added new users\n";
&PETC();

#my $Erc = &Write_Data_File ($File, 'new', 'hash', 'User_ID');
#print "Write_Data_File failed with Erc=$Erc" if $Erc;

#$Erc = &Write_Data_File ($File, 'cat', 'hash', 'User_Level');
#print "Write_Data_File failed with Erc=$Erc" if $Erc;

my $Erc = &Write_Data_File ($File, '>', '%User_ID');
print "Write_Data_File failed with Erc=$Erc" if $Erc;

$Erc = &Write_Data_File ($File, '%User_Level');
print "Write_Data_File failed with Erc=$Erc" if $Erc;

exit;

sub Exit     {
    my ( $erc, $Msg ) = @_;
    &PrintLog ($Msg,0,0,1) if $erc;
    exit;
}

sub PrintLog { &main::Print2XLog (@_)}

sub Print_Debug {

    my $Count = '?';
    if ($Debug) {
        $Count = 0;
        my @Level = qw( - admin supervisor user);
        print "\nUsers:\n";
        foreach  ( keys %User_ID ) {
            $Count++;
            print "\t$User_ID{$_} \t: $_ \($Level[$User_Level{$_}]\)\n";
        }
        print "\n";
    }
    return ($Count);
}

sub Add_User {

    print "\n\n\tLeave \'Name\' field blank to Finish\n\n";

    my $Name = &Get_User_Data(' Name', 0);
    return () if $Name eq '';

    my $ID = &Get_User_Data('   ID', 1);

    my $Level = &Get_User_Data('Level', 1);

    return ($Name, crypt ($ID, $Key), $Level);
}

sub Get_User_Data {  #Kiss version of PT:Ask_User

    my ($Prompt, $Required) = @_;
    my $Data;
    while (1) {
        printf  "$Prompt: ";
        chop( $Data = <STDIN> );
        if ( $Data eq "\[" ) { return (); }
        if ( lc $Data eq 'q' ) { return (); }
        return ($Data) if length ($Data)
                       or !$Required;
    }


}
