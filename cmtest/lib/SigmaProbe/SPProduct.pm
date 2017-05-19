#####################################################################
#
# Perl module: SigmaProbe::SPProduct
#
# By Fadil Mesic, fadil.mesic@sigmaquest.net
#
# Copyright (c) 2002 SigmaQuest
# All rights reserved.
#
######################################################################
package SigmaProbe::SPProduct;
require Exporter;

@ISA = qw(Exporter);
@EXPORT = qw(getName setName getSerialNumber setSerialNumber getPartNumber setPartNumber
             UnitReport AddProperty Initialize);

use SigmaProbe::SPProperty;
use strict;

sub new {
  my $class = shift;
  my $self = {};
  bless($self, $class);

  $self->{Name} = "";
  $self->{SerialNumber} = "";
  $self->{PartNumber} = "";

  return $self;
}

#
#   Returns product's name
#
sub getName{
    my $self = shift;
    return $self->{Name};
}

#
#   Sets product's name
#
sub setName{
  my $self = shift;
  $self->{Name} = shift;
  $self->mProduct->setAttribute("name", $self->{Name});
}

#
#   Returns product's serial number
#
sub getSerialNumber{
    my $self = shift;
    return $self->{SerialNumber};
}

#
#   Sets product's serial number
#
sub setSerialNumber{
  my $self = shift;
  $self->{SerialNumber} = shift;
  $self->{mProduct}->setAttribute("serial-no", $self->{SerialNumber});
}

#
#   Returns product's part number
#
sub getPartNumber{
    my $self = shift;
    return $self->{PartNumber};
}

#
#   Sets product's part number
#
sub setPartNumber{
  my $self = shift;
  $self->{PartNumber} = shift;
  $self->{mProduct}->setAttribute("part-no", $self->{PartNumber});
}

#
#   Sets parent's reference
#
sub UnitReport {
    my ($self, $elm) = @_;
    $self->{mUnitReport} = $elm;
}

#
#   Adds new product's property
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
#   Initializes product
#
sub Initialize {
    my $self = shift;
    my $obj = ($self->{mUnitReport})->getOwnerDocument()->createElement("Product");
    $self->{mProduct} = $obj;
    $self->{mUnitReport}->appendChild ($obj);

    $self->{mProperty} = new SigmaProbe::SPProperty;
    $self->{mProperty}->Init($self->{mProduct});
}

sub DESTROY {
    my $self = shift;
}

1;
