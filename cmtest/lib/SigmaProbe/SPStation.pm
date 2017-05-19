#####################################################################
#
# Perl module: SigmaProbe::SPStation
#
# By Fadil Mesic, fadil.mesic@sigmaquest.net
#
# Copyright (c) 2002 SigmaQuest
# All rights reserved.
#
######################################################################
package SigmaProbe::SPStation;
require Exporter;

@ISA = qw(Exporter);
@EXPORT = qw(getId setId UnitReport AddProperty Initialize);

use SigmaProbe::SPProperty;
use strict;

sub new {
  my $class = shift;
  my $self = {};
  bless($self, $class);

  $self->{ID} = "";

  return $self;
}

#
#   Returns station's GUID
#
sub getId{
    my $self = shift;
    return $self->{ID};
}

#
#   Sets station's GUID
#
sub setId{
  my $self = shift;
  $self->{ID} = shift;
  $self->{mStation}->setAttribute("guid", $self->{ID});
}

#
#   Sets parent's reference
#
sub UnitReport {
    my ($self, $elm) = @_;
    $self->{mUnitReport} = $elm;
}

#
#   Adds new station's property
#
#   Parameters:
#       $name - property name
#       $value - property value
#       $type - property type
#
sub AddProperty {
    my ($self, $name, $value, $type) = @_;
    $self->{mProperty}->setProperty($name, $value, $type);
}

#
#   Initializes station
#
sub Initialize {
    my $self = shift;
    my $obj = ($self->{mUnitReport})->getOwnerDocument()->createElement("Station");
    $self->{mStation} = $obj;
    $self->{mUnitReport}->appendChild ($obj);

    $self->{mProperty} = new SigmaProbe::SPProperty;
    $self->{mProperty}->Init($self->{mStation});
}

sub DESTROY {
    my $self = shift;
}

1;
