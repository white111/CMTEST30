#####################################################################
#
# Perl module: SigmaProbe::SPUnitReport
#
# By Fadil Mesic, fadil.mesic@sigmaquest.net
#
# Copyright (c) 2002 SigmaQuest
# All rights reserved.
#
######################################################################
package SigmaProbe::SPUnitReport;
require Exporter;

@ISA = qw(Exporter);
@EXPORT = qw(xmlDoc Station Operator Product TestRun StartTime EndTime
             StartTimeStamp EndTimeStamp AddProperty setName getName submit);
    
use XML::DOM;
use Time::localtime;

use SigmaProbe::SPTimeStamp;
use SigmaProbe::SPProperty;
use SigmaProbe::SPStation;
use SigmaProbe::SPProduct;
use SigmaProbe::SPOperator;
use SigmaProbe::SPTestRun;
use SigmaProbe::SPQueue;

use strict;

sub new {
  my $class = shift;
  my $self = {};
  bless $self, $class;
  $self->{mName} = "SigmaProbe";  
  $self->_initialize();
  
  return $self;
}

sub DESTROY {
  my $self = shift;
}

#
#   xmlDoc returns XMLDocument
#
sub xmlDoc {
    my $self = shift;
    return $self->{mXMLDOM};
}

#
#   Returns reference to SPStation
#
sub Station {                   
    my $self = shift;
    return $self->{mStation};
}

#
#   Returns reference to SPOperator
#
sub Operator {      
    my $self = shift;
    return $self->{mOperator};
}

#
#   Returns reference to SPProduct
#
sub Product {
    my $self = shift;
    return $self->{mProduct};
}

#
#   Returns reference to SPTestRun
#
sub TestRun {
    my $self = shift;
    return $self->{mTestRun};
}

#
#   Returns first part of the unit report file name
#
sub getName{
    my $self = shift;    
    return $self->{mName};
}  

#
#   Sets first part of the unit report file name
#
sub setName{
  my $self = shift;  
  $self->{mName} = shift;  
}

#
#   Sets unit reports start time attribute
#
sub StartTime {
    my ($self, $value) = @_;
    my $timestamp = new SigmaProbe::SPTimeStamp;
    ($self->{mUnitReport})->setAttribute("start-time", $timestamp->ToStringAsISO($value));
}

#
#   Sets unit reports end time attribute
#
sub EndTime {
    my ($self, $value) = @_;
    my $timestamp = new SigmaProbe::SPTimeStamp;
    ($self->{mUnitReport})->setAttribute("end-time", $timestamp->ToStringAsISO($value));
}

#
#   Sets unit reports start time stamp
#
sub StartTimeStamp {
    my $self = shift;    
    $self->StartTime(localtime);
}

#
#   Sets unit reports end time stamp
#
sub EndTimeStamp {
    my $self = shift;
    $self->EndTime(localtime);
}

#
#   Adds new property to unit report
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

sub CreateName {
    my ($self) = @_;
    my $timestamp = new SigmaProbe::SPTimeStamp;
    my $filename = $self->{mName} . "_" . $timestamp->ToStringAsMilliseconds() . $timestamp->getPID() . ".xml";
    return $filename;	
}

#
#   Submits unit report to queue
#
sub submit {
    my $self = shift;    
    my $queueInit;
    my $queue;
    
    # create new queue
    if ($queueInit == 0) {
        $queue = new SigmaProbe::SPQueue;       
        $queueInit = 1;
    }
    
    # put end time stamp
    $self->EndTimeStamp();  

    # save unit report document to queue
    $queue->Save($self);
}

#
#   Initializes SPUnitReport class
#
sub _initialize {
    my $self = shift;    

    # create new XML document
    $self->{mXMLDOM} = new XML::DOM::Document;
    $self->{mXMLDOM}->createXMLDecl("1.0","UTF-8","");

    # create UnitReport element
    my $unit_report = ($self->{mXMLDOM})->createElement("UnitReport");

    # add UnitReport element to document tree
    $self->{mXMLDOM}->appendChild ($unit_report);
    $self->{mUnitReport} = $unit_report;

    # create new SPStation, pass parent's reference and initialize SPStation
    $self->{mStation} = new SigmaProbe::SPStation;
    $self->{mStation}->UnitReport($unit_report);        
    $self->{mStation}->Initialize();
        
    # create new SPOperator, pass parent's reference and initialize SPOperator    
    $self->{mOperator} = new SigmaProbe::SPOperator;
    $self->{mOperator}->UnitReport($unit_report);        
    $self->{mOperator}->Initialize();

    # create new SPProduct, pass parent's reference and initialize SPProduct    
    $self->{mProduct} = new SigmaProbe::SPProduct;
    $self->{mProduct}->UnitReport($unit_report);        
    $self->{mProduct}->Initialize();
    
    # create new SPSProperty, pass parent's reference and initialize SPProperty
    $self->{mProperty} = new SigmaProbe::SPProperty;
    $self->{mProperty}->Init($self->{mUnitReport});

    # create new SPTestRun, pass parent's reference and initialize SPTestRun    
    $self->{mTestRun} = new SigmaProbe::SPTestRun;
    $self->{mTestRun}->setParent($self->{mUnitReport});
    $self->{mTestRun}->Initialize();
    
    $self->{mName} = $self->CreateName();

    # put start time stamp
    $self->StartTimeStamp();
}

1;
