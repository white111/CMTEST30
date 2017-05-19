################################################################################
#
# Module:     GUI.pm
#
# Author:      Paul Tindle ( mailto:Paul@Tindle.org )
#			 Joe White( mailto:joe@stoke.com )
#
# Descr:      Subs GUI (not in use)
#
# Version:    (See below) $Id: GUI.pm,v 1.3 2008/02/21 00:00:27 joe Exp $
#
# Changes:
#            7   08/17/05  Pseudo version
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

my $Ver= 'v7.1 1/31/2008'; # Updated versioning
my $CVS_Ver = ' [ CVS: $Id: GUI.pm,v 1.3 2008/02/21 00:00:27 joe Exp $ ]';
$Version{'GUI'} = $Ver . $CVS_Ver;
use PT;
#__________________________________________________________________________
sub Dialog {

    my ($Msg) = @_;

    if ( &YN ($Msg) ) {
        return (0);
    }
    else {
        return (1);
    }
}

#__________________________________________________________________________
sub DialogBox {

    my $RC = &Dialog;
    return ($RC);
}

#__________________________________________________________________________
sub Exec {

    my ($SubName) = @_;

    if ($SubName eq 'exit') { &Exit (0); }
    if ($SubName eq '') { &Message ("Sorry! This function hasn't been released yet!",2,2); return }
    &{$SubName};
}
#__________________________________________________________________________
sub Menu__Create_Main {    # Size may be 1(1/8Xx1/8Y)..8(XxY)

    my ( $Title, $Size ) = @_;

    return ();
}

#__________________________________________________________________________
sub Message {

    my ($Msg) = @_;
    print "$Msg\n";
    return ();
}


#____________________________________________________________________________________

1;
