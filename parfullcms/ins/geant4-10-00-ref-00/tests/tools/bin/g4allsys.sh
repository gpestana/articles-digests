#!/usr/local/bin/bash
######################################
# Submit remote build&run 
######################################

account=stesting
 
while read host devprod debopt tag action actarg1 actarg2 actarg3 nonincremental
do

    g4sbr=/afs/cern.ch/sw/geant4/stt/$devprod/testtools/geant4/tests/tools/bin/g4sbr.sh

#    command="rsh -l $account $host $g4sbr $devprod $debopt $tag $action $actarg1 $actarg2 $actarg3 $nonincremental"
    command="ssh -l $account $host $g4sbr $devprod $debopt $tag $action $actarg1 $actarg2 $actarg3 $nonincremental"
    if [ X$host = X ]
    then
        exit # end of requests on command line
    fi
    if [ X$host = X\# ]
    then
	echo "String is comment: $host $devprod $debopt $tag $action $actarg1 $actarg2 $actarg3 $nonincremental"
    elif [ X$host = X\% ]
    then
	echo "String is local command (intended for sleep): $devprod $debopt $tag $action $actarg1 $actarg2 $actarg3 $nonincremental"
	$devprod $debopt $tag $action $actarg1 $actarg2 $actarg3 $nonincremental
    else
        echo $command
	echo $PATH >>  $host.$devprod.$debopt.log 2>&1 
	echo "______________________" >>  $host.$devprod.$debopt.log 2>&1 
	echo $command >>  $host.$devprod.$debopt.log 2>&1 
# Sequential run!
	$command >> $host.$devprod.$debopt.log 2>&1 &
#	$command >> $host.$devprod.$debopt.log 2>&1 
    fi	
done
