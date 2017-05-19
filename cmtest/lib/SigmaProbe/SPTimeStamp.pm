#####################################################################
#
# Perl module: SigmaProbe::SPTimeStamp
#
# By Fadil Mesic, fadil.mesic@sigmaquest.net
#
# Copyright (c) 2002 SigmaQuest
# All rights reserved.
#
######################################################################
package SigmaProbe::SPTimeStamp;
require Exporter;

@ISA = qw(Exporter);
@EXPORT = qw(TimeZoneOffset ToStringAsMilliseconds ToStringAsISO);

use Time::Local;
use Time::HiRes;
use POSIX;
use strict;

sub new {
  my $class = shift;
  my $self = {};
  bless($self, $class);

  return $self;
}

#
#   Finds Time Zone offset between local time and GMT
#   (takes Daylight Saving Time (DST) settings in consideration)
#
sub TimeZoneOffset {

    # Calculate time zone offset    
    my ($l_min, $l_hour, $l_year, $l_yday, $l_isdst) = (localtime $^T)[1,2,5,7,8];
    my ($g_min, $g_hour, $g_year, $g_yday) = (gmtime $^T)[1,2,5,7];
    my $TZOffset = ($l_min - $g_min)/60 + $l_hour - $g_hour + 24 * ($l_year <=> $g_year || $l_yday <=> $g_yday);
    
    # Check for DST
    if ($l_isdst > 0) {
        $TZOffset < 0 ? $TZOffset-- : $TZOffset++;    
    }    

    return $TZOffset;
}

#
#   Returns string representation of current time expressed in milliseconds
#   (used to uniquelly name unit report file).
#
sub ToStringAsMilliseconds {

    my $st;
    my $tzOffset = TimeZoneOffset();
    my $precisetime = Time::HiRes::gettimeofday();
    my $millisec = sprintf("%.3f", $precisetime);
    my @time = split(/\./, $millisec);
    
    my $item;
    my $tostring = "";
    foreach $item(@time) {
        $tostring = $tostring . $item    
    }
    
    return $tostring;    
}

#
#   Returns date-time ISO representation
#
#   Parameters:
#       $datetime - date-time value to format
#
sub ToStringAsISO {

    my ($self, $datetime) = @_;
             
    my $TimeZoneOffset = TimeZoneOffset();
    my $timeZone = sprintf("%03d:00", $TimeZoneOffset);   
    my $dateTimeISO = POSIX::strftime("%Y-%m-%dT%H:%M:%S", $datetime->sec, $datetime->min, $datetime->hour, $datetime->mday, $datetime->mon, $datetime->year, $datetime->wday, $datetime->yday, $datetime->isdst);
    $dateTimeISO = "$dateTimeISO$timeZone"; 

    return $dateTimeISO;
}

#
#   Returns PID of the current running process
#
sub getPID {
    my $pid = sprintf("%d", $$);
    return $pid;	
}

1;
__END__

=head1 NAME

SigmaProbe::SPTimeStamp - Perl class for creating ISO format timestamps and 
unit report naming

=head1 SYNOPSIS

  use SigmaProbe::SPTimeStamp;
  my $TimeStamp = new SigmaProbe::SPTimeStamp;
  $TimeStamp->ToStringAsISO(localtime);

=head1 DESCRIPTION

SigmaProbe::SPTimeStamp is used for creation of start and endn timestamps of
unit report and test runs. In addition, it is used for creation of an unique
unit report file name.

=head1 METHODS

I<ToStringAsMilliseconds> ToStringAsMilliseconds, Returns string 
representation of current time expressed in milliseconds (used to uniquelly 
name unit report file).

I<ToStringAsISO> ToStringAsISO($datetime), Returns date-time ISO representation 
	$datetime - date-time value to format

=head2 EXPORT

None by default.


=head1 AUTHOR

Fadil Mesic, <fadil.mesic@sigmaquest.net>

=head1 LICENSE

(C) SigmaQuest, Inc. 2002, All Rights Reserved. 
This software is property of SigmaQuest, Inc. You may not modify and in any
way alter this software prior obtaining owner's permission.  

=head1 SEE ALSO

SigmaProbe(3), SigmaProbe::SPProperty(3), SigmaProbe::SPOperator(3), 
SigmaProbe::SPProduct(3), SigmaProbe::SPStation(3), SigmaProbe::SPTestRun(3),
SigmaProbe::SPUnitReport(3), SigmaProbe::SPQueue(3).

=cut
