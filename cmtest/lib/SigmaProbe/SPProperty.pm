#####################################################################
#
# Perl module: SigmaProbe::SPProperty
#
# By Fadil Mesic, fadil.mesic@sigmaquest.net
#
# Copyright (c) 2002 SigmaQuest
# All rights reserved.
#
######################################################################
package SigmaProbe::SPProperty;
require Exporter;

@ISA = qw(Exporter);
@EXPORT = qw(MakeValue setProperty Init);

use strict;

sub new {
  my $class = shift;
  my $self = {};
  bless $self, $class;

  return $self;
}

#
#   Initializes property and returns initialized property element
#
#   Parameters:
#       mParent - reference to property's parent
#
sub Init {
  my $self = shift;
  $self->{mParent} = shift;
  my $child = ($self->{mParent})->getOwnerDocument()->createElement("Property");
  $self->{mParent}->appendChild($child);
  $self->{mProperty} = $child;

  return $child;
}

#
#   Sets new property
#
#   Parameters:
#       $name - property name
#       $value - property value
#       $type - property type
#
sub setProperty {
    my ($self, $name, $value, $type) = @_;
    my $elm = $self->MakeValue($name, $value, $type);

    $self->{mProperty}->appendChild($elm);
}

#
#   Makes new property value
#
#   Parameters:
#       $name - value name
#       $value - value
#       $type - value type
#
sub MakeValue {
    my ($self, $name, $value, $type) = @_;
    my $elm;

    if ($type == 'd') {
        $elm = ($self->{mParent})->getOwnerDocument()->createElement("ValueDouble")
    }
    elsif ($type == 'i') {
        $elm = ($self->{mParent})->getOwnerDocument()->createElement("ValueInteger");
    }
    elsif ($type == 's') {
        $elm = ($self->{mParent})->getOwnerDocument()->createElement("ValueString");
    }
    elsif ($type == 't') {
        $elm = ($self->{mParent})->getOwnerDocument()->createElement("ValueTimestamp");
    }
    else {
        printf ("SigmaProbe::SPProperty:MakeValue() - unknown value type\n");
    }

    my $txt = ($self->{mParent})->getOwnerDocument()->createTextNode($value);
    $elm->appendChild ($txt);
    $elm->setAttribute("name", $name);

    return $elm;
}

1;
