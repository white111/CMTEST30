###############################################################################
#
# Module:    PTML.pm
#
# Author:    Paul Tindle ( mailto:Paul@Tindle.org )
#
# Desc:      P[t-h]TML ! ;^)
#
# License:   This software is subject to, and may be distributed under, the
#            terms of the Lesser General Public License as described in the
#            file License.html found in this or a parent directory.

################################################################################
$Version{'PTML'} = 'v6.1 - 2005-12-04';  # New exports

package PTML;
use strict;

require Exporter;

our ( $Indent, $Paint );

our @ISA = qw(Exporter);
our @EXPORT_OK = qw( Body Comment Debug $Indent Init_CGI
                     $Paint PrintLog Table_Head Table_Row Table_Tail );

#__________________________________________________________________________
sub Body {

    my ($Data) = @_;

    print ' ' x $Indent . "$Data\n";

}
#_____________________________________________________________________________
sub Comment {

    my ($Msg) = @_;

    &Body ("\<\!-- $Msg --\>");

}
#__________________________________________________________________________________
sub Debug {                           # Print debug info to html out

    my ($Msg) = @_;

    chomp $Msg;

    &Body ("<P>Debug: $Msg</P>\n") if $main::Debug;
}#__________________________________________________________________________
sub Head {

        my ($Title) = @_;
        my $Background = (1) ? 'BACKGROUND="Stoke4.gif" ' : '';

        print "Content-type: text/html\n\n";
#        print '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">' . "\n";
        print "<HTML>\n";
        print " <HEAD>\n";
        print "  <TITLE>  $Title  </TITLE>\n";
        print " </HEAD>\n";
        print " <BODY $Background>\n";
#        print "  <STYLE TYPE=\"text/css\"></STYLE>\n";
        print "  <CENTER>\n";

        $PTML::Indent = 3;
}
#_______________________________________________________________
sub Init_CGI {

#        $Main = fnstrip ($0,3);        # Script file name.ext without the path

                # Set up log files...

#        $XLog = "/var/log/httpd/$Main.log";

#        my $Erc = &Print_Log (11, "Starting $Main $Version at " . &PT_Date(time, 2));
#        die "Erc = $Erc: ($XLog)" if $Erc;

        our %TD_Desc = (
                ATT        =>        'Actual Test Time',
                ECT        =>        'Estimated Completion',
                ERC        =>        'Last Error Code',
                Power      =>        'Power Supply',
                TEC        =>        'Total Error Count',
                TOLF       =>        'Time Of Last Failure',
                TSLF       =>        'Time Since Last Failure',
                TTF        =>        'Time To [1st] Failure',
                TTT        =>        'Total Test Time'
        );

        our $BG_Color   = '#E0D0D0' if ! defined $BG_Color;  #It should be done in main!
        our $Fail_Color = 'red' if ! defined $Fail_Color;    #It should be done in main!
        our $Pass_Color = 'green' if ! defined $Fail_Color;  #It should be done in main!


        our %Test_ID = ();
        our %Product_ID = ();
        our %Status = ();
        our %Result = ();

}
#__________________________________________________________________________________
sub PrintLog {     # Print a line to the log file $Log_File
                    # This may get replaced with PT3::Pr2Log2 function

    my ($Msg) = @_;
    chomp $Msg;

    my $Log_File = $main::Log_File;
       $Log_File = '/tmp/' . $main::Main . '.log'
          if $Log_File eq '';

    my @Chunks = split ( /\//, $0 );
    my $Main = pop (@Chunks);

#    my $Time = substr (scalar(localtime), 4, 15);
    my $Time = scalar(localtime);
    $Time = substr ($Time, 4, 15);

    my $fh;
#!!! This needs to return 3 not die. Have the caller die if necessary!
    open ($fh, ">>$Log_File") || die "Can't open log file $Log_File for cat";
    print $fh $Time, "[$Main]\:\t$Msg\n";
    #       print $fh $ETime, "\:\t$Msg\n";
    close $fh;

    return (0);
}
#__________________________________________________________________________
sub xHead {

    my ($Title, $Background) = @_;

    print "Content-type: text/html\n\n";
    print '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">' . "\n";
    print "<HTML>\n";
    print " <HEAD>\n";
    print "  <TITLE>  $Title  </TITLE>\n";
    print " </HEAD>\n";
    print " <BODY background=\"$Background\">\n";
#        print "  <STYLE TYPE=\"text/css\"></STYLE>\n";
    print "  <CENTER>\n";

    $Indent = 3;
}

#__________________________________________________________________________
sub Table_Head {

    my (@Fields) = @_;
    my $Head_Color = '#E0D0FF';

    &Body ("<TABLE ALIGN=center BORDER=1 CELLPADDING=3 CELLSPACING=3>");
    $Indent++;

    &Body ("<TR>");
    $Indent++;

    my $Data;
    foreach $Data (@Fields) {
        &Body ("<TD style=\"color: black; background: $Head_Color\">$Data</TD>");
    }

    $Indent--;
    &Body ("</TR>");
}
#__________________________________________________________________________
sub Table_Row {

    my (@Fields) = @_;
    my ($Data);

    &Body ("<TR>");
    $Indent++;

    foreach $Data (@Fields) {
        my $Style = '"color: black; background: ' . $Paint . '"';
        &Body ("<TD style=$Style>$Data</TD>");
    }

    $Indent--;
    &Body ("</TR>");
}
#__________________________________________________________________________
sub Table_Row_dep {

        my (@Fields) = @_;
        my ($Data);
        my $BG_Color = $main::BG_Color[$main::BG_Color_Ptr];

        &Body ("<TR>");
        $PTML::Indent++;

        foreach $Data (@Fields) {
                &Body ("<TD style=\"color: black; background: $BG_Color\">$Data</TD>");
        }

        $PTML::Indent--;
        &Body ("</TR>");
}
#__________________________________________________________________________
sub Table_Tail {

    $Indent--;
    &Body ("</TABLE>");
}
#__________________________________________________________________________
sub Tail {

        print "  </CENTER>\n";
        print " </BODY>\n";
        print "</HTML>\n";

        $PTML::Indent = 0;

}
#__________________________________________________________________________
sub xTail {

    print "  </CENTER>\n";
    print " </BODY>\n";
    print "</HTML>\n";

    $Indent = 0;

}
#__________________________________________________________________________
sub Colors {

print "
<h2><a name=color>Color</a></h2>
<p>Color attribute values give a color definition. The value can be any hexadecimal number, specified according to the sRGB color space, or one of sixteen color names. Hexadecimal numbers must be prefixed by a \"#\" character.</p>
<p>The case-insensitive color names and their sRGB values are as follows:</p>
<table cellspacing=5 cellpadding=5>
  <tr>
    <th scope=col>Color Name</th>
    <th scope=col>sRGB Value</th>
  </tr>
  <tr>
    <td style=\"color: #000000; background: white\">Black</td>
    <td style=\"color: white; background: #000000\">#000000</td>
  </tr>
  <tr>
    <td style=\"color: #C0C0C0; background: white\">Silver</td>
    <td style=\"color: white; background: #C0C0C0\">#C0C0C0</td>
  </tr>
  <tr>
    <td style=\"color: #808080; background: white\">Gray</td>
    <td style=\"color: white; background: #808080\">#808080</td>
  </tr>
  <tr>
    <td style=\"color: #FFFFFF; background: silver\">White</td>
    <td style=\"color: silver; background: #FFFFFF\">#FFFFFF</td>
  </tr>
  <tr>
    <td style=\"color: #800000; background: white\">Maroon</td>
    <td style=\"color: white; background: #800000\">#800000</td>
  </tr>
  <tr>
    <td style=\"color: #FF0000; background: white\">Red</td>
    <td style=\"color: white; background: #FF0000\">#FF0000</td>
  </tr>
  <tr>
    <td style=\"color: #800080; background: white\">Purple</td>
    <td style=\"color: white; background: #800080\">#800080</td>
  </tr>
  <tr>
    <td style=\"color: #FF00FF; background: white\">Fuchsia</td>
    <td style=\"color: white; background: #FF00FF\">#FF00FF</td>
  </tr>
  <tr>
    <td style=\"color: #008000; background: white\">Green</td>
    <td style=\"color: white; background: #008000\">#008000</td>
  </tr>
  <tr>
    <td style=\"color: #00FF00; background: white\">Lime</td>
    <td style=\"color: white; background: #00FF00\">#00FF00</td>
  </tr>
  <tr>
    <td style=\"color: #808000; background: white\">Olive</td>
    <td style=\"color: white; background: #808000\">#808000</td>
  </tr>
  <tr>
    <td style=\"color: #FFFF00; background: silver\">Yellow</td>
    <td style=\"color: silver; background: #FFFF00\">#FFFF00</td>
  </tr>
  <tr>
    <td style=\"color: #000080; background: white\">Navy</td>
    <td style=\"color: white; background: #000080\">#000080</td>
  </tr>
  <tr>
    <td style=\"color: #0000FF; background: white\">Blue</td>
    <td style=\"color: white; background: #0000FF\">#0000FF</td>
  </tr>
  <tr>
    <td style=\"color: #008080; background: white\">Teal</td>
    <td style=\"color: white; background: #008080\">#008080</td>
  </tr>
  <tr>
    <td style=\"color: #00FFFF; background: silver\">Aqua</td>
    <td style=\"color: silver; background: #00FFFF\">#00FFFF</td>
  </tr>
</table>
";
}

#__________________________________________________________________________
1;
