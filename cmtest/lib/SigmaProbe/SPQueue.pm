#####################################################################
#
# Perl module: SigmaProbe::SPQueue
#
# By Fadil Mesic, fadil.mesic@sigmaquest.net
#
# Copyright (c) 2002 SigmaQuest
# All rights reserved.
#
######################################################################
package SigmaProbe::SPQueue;
require Exporter;

@ISA = qw(Exporter);
@EXPORT = qw(setName getName setDirectory getDirectory Save);

use SigmaProbe::SPTimeStamp;
use SigmaProbe::SPUnitReport;
use strict;

sub new {
  my $class = shift;
  my $self = {};
  bless($self, $class);

  $self->{mDirectory} = "";  

  $self->_initialize();
  
  return $self;
}

#
#   Returns queue directory
#
sub getDirectory{
    my $self = shift;    
    return $self->{mDirectory};
}  

#
#   Sets queue directory
#
sub setDirectory{
  my $self = shift;  
  $self->{mDirectory} = shift;  
}

#
#   Initialize queue
#   Note that the prerferred way of finding queue directory is to create SIGMA_QUEUE
#   environment variable with its value as full path to the queue directory. 
#
sub _initialize {
    my $self = shift;    
    $self->setDirectory($ENV{SIGMA_QUEUE});
    
    if ($self->getDirectory() eq "") {
        $self->setDirectory($ENV{TEMP});
    }
    if ($self->getDirectory() eq "") {
        $self->setDirectory($ENV{HOME});
    }
    if ($self->getDirectory() eq "") {
        $self->setDirectory("/");
    }    
}

#
#   Forms unit report name and saves it to queue direrctory
#
sub Save {                   
    my ($self, $UnitReport) = @_;
    ($UnitReport->{mUnitReport})->getOwnerDocument()->printToFile($self->{mDirectory} . "/" . $UnitReport->getName())
}

1;

sub Save {
    my ($self, $UnitReport) = @_;
    my $TimeStamp = new SigmaProbe::SPTimeStamp;
    my $filename = $self->{mName} . "_" . $TimeStamp->ToStringAsMilliseconds() . ".xml";
    $UnitReport->printToFile($self->{mDirectory} . "/" . $filename)
}

1;
