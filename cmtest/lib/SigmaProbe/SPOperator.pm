#####################################################################
#
# Perl module: SigmaProbe::SPOperator
#
# By Fadil Mesic, fadil.mesic@sigmaquest.net
#
# Copyright (c) 2002 SigmaQuest
# All rights reserved.
#
######################################################################
package SigmaProbe::SPOperator;
use SigmaProbe::SPProperty;

use strict;

sub new {
  my $class = shift;
  my $self = {};
  bless($self, $class);

  $self->{Name} = "";

  return $self;
}

#
#   Gets operator's name
#
sub getName{
    my $self = shift;
    return $self->{Name};
}

#
#   Sets operator's name
#
sub setName{
  my $self = shift;
  $self->{Name} = shift;
  $self->{mOperator}->setAttribute("name", $self->{Name});
}

#
#   Sets parent's reference
#
sub UnitReport {
    my ($self, $elm) = @_;
    $self->{mUnitReport} = $elm;
}

#
#   Adds new operator's property
#
#   Parameters:
#       $name - property name
#       $value - property value
#       $type - property type
#
sub AddProperty {
    my ($self, $name, $value, $type) = @_;
    $self->{mProperty}->AddProperty($name, $value, $type);
}

#
#   Initializes operator
#
sub Initialize {
    my $self = shift;
    my $obj = ($self->{mUnitReport})->getOwnerDocument()->createElement("Operator");
    $self->{mOperator} = $obj;
    $self->{mUnitReport}->appendChild ($obj);

    $self->{mProperty} = new SigmaProbe::SPProperty;
    $self->{mProperty}->Init($self->{mOperator});
}

sub DESTROY {
    my $self = shift;
}

1;
