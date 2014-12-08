#!/usr/local/bin/perl

require 5.000;

use Sys::Hostname;
use Cwd;

$Version = "1.000";

sub InitVars {
    
    $TestScript = 0;

    # PLEASE FILL THIS IN WITH YOUR PROPER EMAIL ADDRESS
    $BuildAdministrator = "$ENV{'USER'}\@$ENV{'HOST'}";

    #Default values of cmdline opts
    $BuildDepend = 1;	#depend or clobber
    $ReportStatus = 1;  # Send results to server or not
    $BuildOnce = 0;     # Build once, don't send results to server
    $BuildClassic = 0;  # Build classic source

    #relative path to binary
    $BinaryName{'x'} = 'mozilla-export';
    $BinaryName{'qt'} = 'qtmozilla-export';
    $BinaryName{'gnome'} = 'gnuzilla-export';
    $BinaryName{'webshell'} = '/webshell/tests/viewer/viewer';
    $BinaryName{'xpfe'} = '/xpfe/xpviewer/src/xpviewer';

    # Set these to what makes sense for your system
    $cpus = 1;
    $Make = 'gmake'; # Must be gnu make
    $mail = '/bin/mail';
    $Autoconf = 'autoconf -l build/autoconf';
    $CVS = 'cvs -z3';
    $CVSCO = 'co -P';

    $AFSDir = "/afs/cern.ch/project/cndoc/wwwasd/cgi-bin/geant4/tinderbox/mail";
    $REF = "$ENV{REF}";
    $G4SYSTEM = "$ENV{G4SYSTEM}";
    $DEBOPT = "$ENV{DEBOPT}";

    print "LN_out=$ENV{G4LARGE_N} \n";
# Large_N
    if ($ENV{G4LARGE_N} ) {
    print "LN_in=$ENV{G4LARGE_N} \n";
	$DOT_G4LARGE_N = ".$ENV{G4LARGE_N}";
    }

    $UNIQ = "$REF.$G4SYSTEM.$DEBOPT.$$";
#################################################################
# Start/End times.
#

# Get tagset number from OnTest

    $OnTest = "$ENV{G4STTDIR}/bin/OnTest";

open(ONTEST,"$OnTest") || die "Failed to open read OnTest $!";

while(<ONTEST>) {
#         1    2                     3              4    5
    (/^(\S+)(\s+)geant4-\d+-\d+-(ref|cand)-\d+\+(tags)(\d+)/) ;
    $tagset = $5;
#    print "tagset=$5\n";
}

close(ONTEST);


# Get number of tests from its list
# to be imlemented
    $tests_number = 45;

# Calculate 'tagset time'
    $BaseTime = ($tagset-1) * ($tests_number) * 5 * 60;

#    # Keep $StartTime in $G4WORKDIR/StartTime
#    if (open(STARTTIME,"$ENV{'G4WORKDIR'}/StartTime")) {
#	while(<STARTTIME>) {
#	    chop;
#	    $StartTime = $_;
#	}
#    } else {
#	$StartTime = time;
#	system("echo $StartTime > $ENV{'G4WORKDIR'}/StartTime");
#    }
#
#    $CurrentTime = time;


###################################################################
    
    $GmakeLog = "$ENV{'G4WORKDIR'}/stt/$ENV{'G4SYSTEM'}/gmake.log";
    $StartLog = "$ENV{'G4WORKDIR'}/start.log";
    $EndLog = "$ENV{'G4WORKDIR'}/end.log";
    
    # Set these proper values for your tinderbox server
#    $Tinderbox_server = 'g4tinder\@pcitapi08';
    $Tinderbox_server = 'g4tinder\@pcitapiww';
    #$Tinderbox_server = 'external-tinderbox-incoming\@tinderbox.seawood.org';

    # These shouldn't really need to be changed
    $BuildSleep = 10; # Minimum wait period from start of build to start
                      # of next build in minutes
#    $BuildTree = &GetTestArea;
#    $BuildTree = "Project_A";
    $BuildTree = $tagset;
    $BuildTag = '';
    $BuildName = &GetBuildName;
    $TopLevel = '.';
    $Topsrcdir = 'mozilla';
    $BuildObjName = '';
    $BuildConfigDir = 'mozilla/config';
    $ClobberStr = 'realclean';
    $ConfigureEnvArgs = 'CFLAGS=-pipe CXXFLAGS=-pipe';
    #$ConfigureEnvArgs = '';
    $ConfigureArgs = "--cache-file=/dev/null";
    $ConfigGuess = './build/autoconf/config.guess';
    $Logfile = '${BuildDir}.log';
} #EndSub-InitVars

##########################################################################
# NO USER CONFIGURABLE PIECES BEYOND THIS POINT                          #
##########################################################################

sub GetSystemInfo {

    $OS = `uname -s`;
    $OSVer = `uname -r`;
    
    chop($OS, $OSVer);
    
    if ( $OS eq 'AIX' ) {
	$OSVer = `uname -v`;
	chop($OSVer);
	$OSVer = $OSVer . "." . `uname -r`;
	chop($OSVer);
    }
        
    if ( $OS eq 'IRIX64' ) {
	$OS = 'IRIX';
    }
    
    if ( $OS eq 'SCO_SV' ) {
	$OS = 'SCOOS';
	$OSVer = '5.0';
    }
    
    my $host, $myhost = hostname;
    chomp($myhost);
    ($host, $junk) = split(/\./, $myhost);
	
    $BuildName = ""; 
	
    if ( "$host" ne "" ) {
	$BuildName = $host . ' ';
    }
    $BuildName .= $OS . ' ' . $OSVer . ' ' . ($BuildDepend?'Depend':'Clobber');
    $DirName = $OS . '_' . $OSVer . '_' . ($BuildDepend?'depend':'clobber');
    
    $RealOS = $OS;
    $RealOSVer = $OSVer;
    
    if ( $OS eq 'HP-UX' ) {
	$RealOSVer = substr($OSVer,0,4);
    }
    
    if ( $OS eq 'Linux' ) {
	$RealOSVer = substr($OSVer,0,3);
    }

    if ($BuildClassic) {
        $logfile = "${DirName}-classic.log";
    } else {
	$logfile = "${DirName}.log";
    }
} #EndSub-GetSystemInfo

sub CVSTime {
    my($StartTimeArg) = @_;
    my($RetTime, $StartTimeArg, $sec, $minute, $hour, $mday, $mon, $year);
    
    ($sec,$minute,$hour,$mday,$mon,$year) = localtime($StartTimeArg);
    $mon++; # month is 0 based.
    
    sprintf("%02d/%02d/%02d %02d:%02d:00", $mon,$mday,$year,$hour,$minute );
}

sub StartBuild {
    
#    my($fe, @felist);

#    @felist = split(/,/, $FE);

#    die "SERVER: " . $Tinderbox_server . "\n";
###    open( LOG, "|$mail $Tinderbox_server" );
    open( LOG, "|cat >> $StartLog" );
	print LOG "\n";
	# TestArea1|TestArea2|TestArea3
	print LOG "tinderbox: tree: $BuildTree\n";
	# ?
	print LOG "tinderbox: starttime: $StartTime\n";
	print LOG "tinderbox: timenow: $StartTime\n";
	print LOG "tinderbox: status: building\n";
	# SUN-CC/debug
	print LOG "tinderbox: buildname: $BuildName\n"; 
	print LOG "tinderbox: errorparser: unix\n";
	print LOG "tinderbox: END\n";
	print LOG "\n";
    close( LOG );

    if ( $TestScript == 0) {
#	system("$mail $Tinderbox_server < $StartLog");
	system("cp $StartLog $AFSDir/$UNIQ");
	system("rm $StartLog");
    }
}

sub StartTest {
    
#    my($fe, @felist);

#    @felist = split(/,/, $FE);

#    die "SERVER: " . $Tinderbox_server . "\n";
###    open( LOG, "|$mail $Tinderbox_server" );
    open( LOG, "|cat >> $StartLog" );
	print LOG "\n";
	# TestArea1|TestArea2|TestArea3
	print LOG "tinderbox: tree: $BuildTree\n";
	# ?
	print LOG "tinderbox: starttime: $StartTime\n";
	print LOG "tinderbox: timenow: $StartTime\n";
#	print LOG "tinderbox: status: $TestName-running\n";
	print LOG "tinderbox: status: tests-running\n";
	print LOG "tinderbox: testname: $TestName\n";
	# SUN-CC/debug
	print LOG "tinderbox: buildname: $BuildName\n"; 
	print LOG "tinderbox: errorparser: unix\n";
	print LOG "tinderbox: END\n";
	print LOG "\n";
    close( LOG );
    
    if ( $TestScript == 0) {
#	system("$mail $Tinderbox_server < $StartLog");
#	system("cp $StartLog StartLog");
	system("cp $StartLog $AFSDir/$UNIQ");
	system("rm $StartLog");
    }
    
}

sub EndBuild {
    
    $BuildStatus = &GetBuildStatus;

#    my($fe, @felist);

#    @felist = split(/,/, $FE);

#    die "SERVER: " . $Tinderbox_server . "\n";
###    open( LOG, "|$mail $Tinderbox_server" );
    open( LOG, "|cat >> $EndLog" );
	print LOG "\n";
	# TestArea1|TestArea2|TestArea3
	print LOG "tinderbox: tree: $BuildTree\n";
	# ?
	print LOG "tinderbox: starttime: $StartTime\n";
	print LOG "tinderbox: timenow: $CurrentTime\n";
	print LOG "tinderbox: status: $BuildStatus\n";
	# SUN-CC/debug
	print LOG "tinderbox: buildname: $BuildName\n"; 
	print LOG "tinderbox: errorparser: unix\n";
	print LOG "tinderbox: END\n";
	print LOG "\n";
    close( LOG );
    if ( $TestScript == 0) {
	system("rm $ENV{'G4WORKDIR'}/StartTime");
	
	system("cat $GmakeLog >> $EndLog");
#	system("$mail $Tinderbox_server < $EndLog");
	system("cp $EndLog $AFSDir/$UNIQ");
	system("rm $EndLog");
    }
}

sub EndTest {
    
#    $BuildStatus = &GetBuildStatus;
    $BuildStatus = "success";

#    my($fe, @felist);

#    @felist = split(/,/, $FE);

#
# Get the size of $TestName.err 
#
    $filename = "$ENV{'G4WORKDIR'}/stt/$ENV{'G4SYSTEM'}/$TestName$DOT_G4LARGE_N.err";
    $errsize = (stat($filename))[7];

    open(ERRFILE,"$filename") || die "Failed to open read $filename $!";
    
    while(<ERRFILE>) {
	if ($ENV{'G4SYSTEM'} eq 'Linux-g++') {
	    if (/(\d+)\:(\d+)\.(\d+)elapsed/) {
		
		$sec = $1*60+$2;
		$deltatime = "$sec.$3";
		
#		print "deltatime=$deltatime\n";
	    }
	} else {
	    if (/^real(\s+)(\d+)\.(\d+)/) {
		
		$deltatime = "$2.$3";
		
#		print "deltatime=$deltatime\n";
	    }
	}
    }
    
    close(ERRFILE);
    
    if ($ENV{'G4SYSTEM'} eq "DEC-cxx") {
	$minerr=30;
	$maxerr=45;
    } 

    if ($ENV{'G4SYSTEM'} eq "Linux-g++") {
	$minerr=125;
	$maxerr=140;
    } 

    if ($ENV{'G4SYSTEM'} eq "Linux-egcs") {
	$minerr=125;
	$maxerr=140;
    } 

    if ($ENV{'G4SYSTEM'} eq "SUN-CC") {
	$minerr=45;
	$maxerr=55;
    } 

    if ($ENV{'G4SYSTEM'} eq "HP-aCC") {
	$minerr=45;
	$maxerr=55;
    } 

    if ($errsize < $maxerr && $errsize > $minerr) {
	$BuildStatus = "success";
    } else {
	$BuildStatus = "failed";
    }

#    die "SERVER: " . $Tinderbox_server . "\n";
###    open( LOG, "|$mail $Tinderbox_server" );
    open( LOG, "|cat >> $EndLog" );
	print LOG "\n";
	# TestArea1|TestArea2|TestArea3
	print LOG "tinderbox: tree: $BuildTree\n";
	# ?
	print LOG "tinderbox: starttime: $StartTime\n";
	print LOG "tinderbox: timenow: $CurrentTime\n";
#	print LOG "tinderbox: status: $TestName-$BuildStatus\n";
	print LOG "tinderbox: status: tests-$BuildStatus\n";
	print LOG "tinderbox: testname: $TestName\n";
	print LOG "tinderbox: errsize:  err=$errsize\n";
	print LOG "tinderbox: deltatime:  time=$deltatime\n";
#	print LOG "tinderbox: diffsize: 200\n";
#	print LOG "tinderbox: outsize:  300\n";
	# SUN-CC/debug
	print LOG "tinderbox: buildname: $BuildName\n"; 
	print LOG "tinderbox: errorparser: unix\n";
	print LOG "tinderbox: END\n";
	print LOG "\n";
    close( LOG );
    if ( $TestScript == 0) {
	system("rm $ENV{'G4WORKDIR'}/StartTime");
	
	system("cat $filename >> $EndLog");
#	system("$mail $Tinderbox_server < $EndLog");
	system("cp $EndLog $AFSDir/$UNIQ");
	system("rm $EndLog");
    }
}

# check for the existence of the binary
sub BinaryExists {
    my($fe) = @_;
    my($Binname);
    $fe = 'x' if (!defined($fe)); 

    if ($BuildClassic) {
	$BinName = $BuildDir . '/' . $TopLevel . '/' . $Topsrcdir . '/'. $BuildObjName . "/cmd/${fe}fe/" . $BinaryName{"$fe"};
    } else {
	$BinName = $BuildDir . '/' . $TopLevel . '/' . $Topsrcdir . '/' . $BuildObjName . $BinaryName{"$fe"};
    }
    print LOG $BinName . "\n"; 
    if ((-e $BinName) && (-x $BinName) && (-s $BinName)) {
	1;
    }
    else {
	0;
    }
}

sub DeleteBinary {
    my($fe) = @_;
    my($BinName);
    $fe = 'x' if (!defined($fe)); 

    if ($BuildClassic) {
	$BinName = $BuildDir . '/' . $TopLevel . '/' . $Topsrcdir . '/' . $BuildObjName . "/cmd/${fe}fe/" . $BinaryName{"$fe"};
    } else {
	$BinName = $BuildDir . '/' . $TopLevel . '/' . $Topsrcdir . '/' . $BuildObjName . $BinaryName{"$fe"};
    }
    print LOG "unlinking $BinName\n";
    unlink ($BinName) || print LOG "unlinking $BinName failed\n";
}


sub PrintEnv {
    my ($key);
    foreach $key (keys %ENV) {
	print LOG "$key = $ENV{$key}\n";
	print "$key = $ENV{$key}\n";
    }
} #EndSub-PrintEnv

sub GetTestArea {
    return "$ENV{'REF'}";
}

sub GetBuildName {
    return "$ENV{'G4SYSTEM'}-$ENV{'DEBOPT'}";
}

sub PrintUsage {
    die "usage: $0 [--start | --end] [--start-test | --end-test] TestName\n";
}

sub ParseArgs {
    my($i, $manArg);

    if( @ARGV == 0 ) {
	&PrintUsage;
    }
    $i = 0;
    $manArg = 0;
    while( $i < @ARGV ) {
	if ($ARGV[$i] eq '--start') {
	    $i++;
	    $TinderboxMessage = "StartBuild";
	    $TestName = "Build";
	    $TestNumber = $ARGV[$i];
 	    $manArg++;
	}
	elsif ($ARGV[$i] eq '--end') {
	    $i++;
	    $TinderboxMessage = "EndBuild";
	    $TestName = "Build";
	    $TestNumber = $ARGV[$i];
	    $manArg++;
	} elsif ($ARGV[$i] eq '--start-test') {
	    $i++;
	    $TinderboxMessage = "StartTest";
	    $TestName = $ARGV[$i];
	    $i++;
	    $TestNumber = $ARGV[$i];
	    $manArg++;
	} elsif ($ARGV[$i] eq '--end-test') {
	    $i++;
	    $TinderboxMessage = "EndTest";
	    $TestName = $ARGV[$i];
	    $i++;
	    $TestNumber = $ARGV[$i];
	    $manArg++;
    } else {
	&PrintUsage;
    }
    
	$i++;
    } #EndWhile

    if ( $BuildTree =~ /^\s+$/i ) {
	&PrintUsage;
    }

    if ($BuildDepend eq undef) {
	&PrintUsage;
    }

    &PrintUsage if (! $manArg );

} #EndSub-ParseArgs

sub GetBuildStatus {
    
    open(GMAKELOG, $GmakeLog);

    while($line = <GMAKELOG>) {
	chomp($line);
	if($line =~ m#gmake\[\d+]\: \*\*\* \[\S+\] Error \d+#) {
#	   print "$line\n";
	   return "build_failed";
       }
    }
    close(GMAKELOG);
    return "success";
}

# Main function
&InitVars;
&ParseArgs;
#&ConditionalArgs;
####&GetSystemInfo;
#&SetupEnv;
#&SetupPath;
#&BuildIt;

print "TestNumber=$TestNumber\n";
    $StartTime = $BaseTime + ($TestNumber-1)*5*60;
    $CurrentTime = $BaseTime + ($TestNumber)*5*60-1;

if ($TinderboxMessage eq "StartBuild") {
    &StartBuild;
} elsif ($TinderboxMessage eq "EndBuild") {
#    print "EndBuild\n";
    &EndBuild;
} elsif ($TinderboxMessage eq "StartTest") {
#    print "StartTest\n";
    &StartTest;
} elsif ($TinderboxMessage eq "EndTest") {
#    print "EndTest\n";
    &EndTest;
}

1;
