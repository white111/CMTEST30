#####################################################################
#
# Perl module: SigmaProbe::SPTestRun
#
# By Fadil Mesic, fadil.mesic@sigmaquest.net
#
# Copyright (c) 2002 SigmaQuest
# All rights reserved.
#
######################################################################
package SigmaProbe::SPTestRun;
require Exporter;

@ISA = qw(Exporter);
@EXPORT = qw(setParent setVersion getVersion setName getName StartTime EndTime
             StartTimeStamp EndTimeStamp CreateSubTestRun AddSetup AddResult AddProperty
             Pass Fail Initialize);

use SigmaProbe::SPTimeStamp;
use SigmaProbe::SPProperty;
use Time::localtime;
use strict;

sub new {
    my $class = shift;
    my $self = {};
    bless $self, $class;
  
    return $self;
}

#
#   Sets  parent's reference
#
sub setParent {
    my ($self, $e) = @_;    
    $self->{mParent} = $e;
}

#
#   Sets test run version
#
sub setVersion {
    my ($self, $value) = @_;    
    $self->{mTestRun}->setAttribute("version", $value)
}

#
#  Retuns test run version
#
sub getVersion {
    my $self = shift;
    return $self->{mTestRun}->getAttribute("version");
}

#
#   Sets test run name
#
sub setName {
    my ($self, $value) = @_;    
    $self->{mTestRun}->setAttribute("name", $value)
}

#
#   Returns test run name
#
sub getName {
    my $self = shift;
    return $self->{mTestRun}->getAttribute("name");
}

#
#   Sets test run start time attribute
#
sub StartTime {
    my ($self, $value) = @_;
    my $time = new SigmaProbe::SPTimeStamp;
    my $strtm = $time->ToStringAsISO($value);
    $self->{mTestRun}->setAttribute("start-time", $strtm);
}

#
#   Sets test run end time attribute
#
sub EndTime {
    my ($self, $value) = @_;
    my $time = new SigmaProbe::SPTimeStamp;
    $self->{mTestRun}->setAttribute("end-time", $time->ToStringAsISO($value));
}

#
#   Sets test run start time stamp
#
sub StartTimeStamp {
    my $self = shift;
    $self->StartTime(localtime);
}

#
#   Sets test run end time stamp
#
sub EndTimeStamp {
    my $self = shift;    
    $self->EndTime(localtime);
}

#
#   Creates sub test run and initializes it
#
sub CreateSubTestRun {
    my $self = shift;    
    my $TestRun = new SigmaProbe::SPTestRun;        # create recursive reference
    $TestRun->setParent($self->{mTestRun});
    $TestRun->Initialize();
    return $TestRun;
}

#
#   Adds new setup attribute (using SPProperty)
#
#   Parameters:
#       $name - property name
#       $value - property value
#       $type - property type
#
sub AddSetUp {
    my ($self, $name, $value, $type) = @_;
    ($self->{mStimuli})->setProperty($name, $value, $type);
}

#
#   Adds new result attribute (using SPProperty)
#
#   Parameters:
#       $name - property name
#       $value - property value
#       $type - property type
#
sub AddResult  {
    my ($self, $name, $value, $type) = @_;
    ($self->{mResult})->setProperty($name, $value, $type);
}

#
#   Adds new property to test run
#
#   Parameters:
#       $name - property name
#       $value - property value
#       $type - property type
#
sub AddProperty {
    my ($self, $name, $value, $type) = @_;
    ($self->{mProperty})->setProperty($name, $value, $type);
}

#
#   Sets test run's INCOMPLETE grade
#
sub Incomplete {
    my $self = shift;
    ($self->{mTestRun})->setAttribute("grade", "INCOMPLETE");
    # put end time stamp
    $self->EndTimeStamp();      
}

#
#   Sets test run's passing grade
#
sub Pass {
    my $self = shift;
    ($self->{mTestRun})->setAttribute("grade", "PASS");
    # put end time stamp
    $self->EndTimeStamp();      
}

#
#   Sets test run's failing grade
#
sub Fail {
    my $self = shift;
    ($self->{mTestRun})->setAttribute("grade", "FAIL");
    # put end time stamp
    $self->EndTimeStamp();      
}

#
#   Initializes test run
#
sub Initialize {
    
    my $self = shift;
    my $elm = ($self->{mParent})->getOwnerDocument()->createElement("TestRun");
    $self->{mParent}->appendChild ($elm);
    $self->{mTestRun} = $elm;

    $elm = ($self->{mParent})->getOwnerDocument()->createElement("SetUp");
    $self->{mTestRun}->appendChild ($elm);
    $self->{mStimuliElm} = $elm;
    $self->{mStimuli} = new SigmaProbe::SPProperty;
    $self->{mStimuli}->Init($self->{mStimuliElm});

    $elm = ($self->{mParent})->getOwnerDocument()->createElement("Result");
    $self->{mTestRun}->appendChild($elm);
    $self->{mResultElm} = $elm;
    $self->{mResult} = new SigmaProbe::SPProperty;
    $self->{mResult}->Init($self->{mResultElm});
    
    $self->{mProperty} = new SigmaProbe::SPProperty;
    $self->{mProperty}->Init($self->{mTestRun});
    
    $self->Incomplete();
    
    $self->StartTimeStamp();
}

1;