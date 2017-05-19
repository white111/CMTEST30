###############################################################################
#
# Module:    Local.pm
#
# Author:    Paul Tindle ( mailto:Paul@Tindle.org )
#
# Version:   v4 - 08/14/05
#
# License:   This software is subject to, and may be distributed under, the
#            terms of the Lesser General Public License as described in the
#            file License.html found in this or a parent directory.
#
###############################################################################
#

#package SigmaProbe::Local;

our $UnitReport;

#__________________________________________________________________________
sub Create_SigmaQuest_Unit_Report {

    $Erc = &Print_Log (1, "Creating SigmProbe Unit Report ...");

# From Init.pm...
#       %Stats           = (                     # Used by the Stats mechanism
#            'ECT'        => '',                  # Expected Completion Time
#            'Host_ID'    => $ENV{HOSTNAME},      # HostID for logging purposes
#            'Loop'       => 0,                   # Loop counter (and flag!)
#            'PID'        => $$,                  # PID for this process
#            'PPID'       => getppid,             # PID for shell that launched this
#            'Power'      => '',                  # Which power module to switch
#            'Result'     => 'INCOMPLETE',        # Final Result
#            'Session'    => 0,                   # Session no [1..#Ports on the system]
#            'Started'    => &PT_Date (time,1),   # Ascii version of TimeStamp
#            'Status'     => '',                  # OK|Running|Finished fluff
#            'TimeStamp'  => time,                # Start-time - used for all logging finctions
#            'TTG'        => '',                  # (Test) Time To Go ($Stats{ECT} - time)
#            'Updated'    => time,                # Time stamp of last update
#            'UUT_ID'     => ''                   # Primary Serial no to be used for logging purposes
#        );
#
#        %TestData = (
#            'ATT'        => 0,                   # Actual Test Time (excl. wait time) (secs)
#            'Diag_Ver'   => '',                  # Diag version extracted from header
#            'ERC'        => '',                  # The last $Erc reported
#            'Power'      => '',                  # Which power module (A|B) was in use (last or on 1st error
#            'TID'        => '',                  # Test ID
#            'TOLF'       => '',                  # Time Of Last Failure (time code) [set in &Logs::Log_Error]
#            'TSLF'       => '',                  # Time Since Last Failure (secs)
#            'TEC'        => 0,                   # Total Error Count
#            'TTF'        => '',                  # Time To Failure (secs)
#            'TTT'        => 0,                   # Total Test Time (secs)
#            'Ver'        => ''                   # Code version
#        );


    $UnitReport = new SigmaProbe::SPUnitReport;

    $UnitReport->{mStation}->setId($GUID);
    $UnitReport->{mStation}->setName('Host_ID');
    $UnitReport->{mOperator}->setName("mfg-${Op_ID}");
    $UnitReport->{mProduct}->setPartNumber($PN[0]);
    $UnitReport->{mProduct}->setSerialNumber($SN[0]);
    $UnitReport->{mTestRun}->setName($TestData{'TID'});


}
#__________________________________________________________________________
sub Create_SigmaQuest_SubTest {

    &Exit (999, 'No Test Report initiated') if !defined $UnitReport;

    my ($TestName, $Result) = @_;
    &Print_Log (1, "Running SQ_Sub_Test ($TestName, $Result)");

    my $SubTest = $UnitReport->{mTestRun}->CreateSubTestRun();

    $SubTest->setName($TestName);

    if ($Result eq 'FAIL') {
        $SubTest->Fail();
    } else {
        $SubTest->Pass();
    }

    $UnitReport->submit();
}
#__________________________________________________________________________
sub Submit_SigmaQuest_Unit_Report {

    if ($TestData{'TEC'}) {
        $UnitReport->{mTestRun}->Fail();
    } else {
        $UnitReport->{mTestRun}->Pass();
    }

    $UnitReport->submit();
}
#__________________________________________________________________________
1;
