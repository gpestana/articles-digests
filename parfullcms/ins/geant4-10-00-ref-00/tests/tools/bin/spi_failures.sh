#!/bin/sh

# get short html listing for failed tests

addbg()
{
list=$1;
dbg=$2;
opt=$3;
result="";
for sys in $list ; do
result="$result ${sys}${opt} ${sys}$dbg"; 
done
}

setdate()
{
datum="preceeding `date "+%a %d-%b-%Y"`"
}


URLstart=http://lcgapp.cern.ch/spi/aaLibrarian/nightlies/

slc4="slc4_amd64_gcc34 slc4_ia32_gcc34"
slc5="x86_64-slc5-gcc43 i686-slc5-gcc43"
slc5="$slc5 x86_64-slc5-gcc41 i686-slc5-gcc41"
icc="     x86_64-slc5-icc11 i686-slc5-icc11"
icc="$icc x86_64-slc5-icc12 i686-slc5-icc12"
mac5="osx105_ia32_gcc401"
mac6="x86_64-mac106-gcc42"
win="i686-winxp-vc9"

addbg "$slc4" _dbg; slc4=$result;
addbg "$slc5" -dbg -opt; slc5=$result;
addbg "$icc"  -dbg -opt; icc=$result;
addbg "$mac5"  _dbg; mac=$result;
addbg "$mac6"  -dbg -opt; mac="$mac $result";
addbg "$win"  -dbg -opt; win=$result;

day=`date "+%a"`
logfile=`date "+%a.%d%m%y"`
datum=`date "+%d-%b-%Y"`

#slot="geant4"
#tagname="tags_bonsai"
slot="geant4"
tagname="g4tags-dev"

while test $# -gt 0 ; do 
  case $1 in 
  --day) day=$2;
         setdate $day;
	 shift;shift;
	 ;;
  --win) win="";
  	shift;	 
	;;
  --mac) mac="";
  	shift;	 
	;;
  --icc) icc="";
  	shift;	 
	;;
  --tag) slot=geant4_1;
  	  tagname=$2;
          logfile="${logfile}.${tagname}";
	   shift;
	   shift;
	   ;;	   
  default) shift;
         ;;
  esac
done

echo ""
echo "checking for $slot, $tagname on $day, $datum";
echo "-----------------------------"
echo ""
tmpfile=/tmp/spi_tmp.tmp.$$
sedfile=/tmp/sedfile.$$
	 	 
[ -r $logfile ] && rm $logfile
for sys in $slc4 $slc5 $icc $mac $win; do 
  url_build=${URLstart}${sys}/${slot}.${day}_${tagname}-${sys}-log.html
  url_test=${URLstart}${sys}/${slot}.${day}_${tagname}-${sys}-qmtest.log
   #echo '--------------------------------------------------------'
   #echo $sys using $url_build 
  wget -O - $url_build 2>/dev/null  |tr -d '\r' | grep -i Taglist > $tmpfile
  taglist_selected=`awk -F: '/# Taglists with selected tags/ { print $2 }' $tmpfile`
  taglist_accepted=`awk -F: '/# Taglists with accepted tags/ { print $2 }' $tmpfile`
  rm $tmpfile
   #echo "tags: $taglist_selected,  $taglist_accepted"
  [ -z "$taglist_selected"  ] && taglist_selected=`echo $tagname | tr "-" "_"`
  [ -z "$taglist_accepted" ] && taglist_accepted=$slot

  cat > $sedfile << EoI
1i\
SYSTEM: $sys\n\
Taglist selected: $taglist_selected\n\
Taglist accepted: $bonsai_basetag
/--- TESTS THAT DID NOT PASS/q
EoI
  wget -O - $url_test 2>/dev/null | tac | sed -f $sedfile >> $logfile
  rm $sedfile
done

./expected_fail.sh >> $logfile

awkfile=/tmp/awkfile.$$ 
cat > $awkfile << EoI
BEGIN {}

/SYSTEM/ {
# print "1="\$1 "   2="\$2;
  sys=\$2;
  nsys=nsys+1;
  allsys[nsys]=sys "|"; 
}

/Taglist selected:/ {
  num=\$3;
  tag[num]=tag[num] " " sys;
  if (num in tagnums) {;}
  else {tagnums[num]=num;}
}
/Taglist accepted:/ {
  num=\$4
  basetag[num]=basetag[num] " " sys;
  if (num in basetagnums) {;}
  else {basetagnums[num]=num;}   
}  

/: FAIL/ {
  test=\$1;
#  print "failed " test;
  if (test in failed) {;}
  else { failed[test]=test; expected[test]=" ";}
  systems[test]=systems[test] " " sys "|";
}

/: ERROR/ {
  test=\$1;
  if (test in failed) {;}
  else { failed[test]=test; expected[test]=" ";}
  systems[test]=systems[test] " " sys "|";
}

/EXPECTED_FAIL/ {
  test=\$2;
  if (test in failed) {;}
  else { failed[test]=test;
         systems[test]=" ";
       }
  for (elem=3;elem <= NF ; elem++) {
      expected[test]=expected[test] " " \$elem "|";
  }
}

	END {

#find bonsai tag 
n_tags=asorti(tagnums)
if (n_tags == 1) {
   printf("Taglist selected tags: %s\n",tagnums[1]);
} else {
   printf"Different Taglists for selected tags:\n"
   for (el=1;el<=n_tags; el++) {
     printf(" tag: %d used on %s\n",tagnums[el],tag[tagnums[el]]);
   }
}        

spaces=25;
for (msys=1;msys<=nsys;msys++) {
  for (i=0;i<spaces;i++)printf(" ");
  printf("%25s\n",allsys[msys]);
  spaces=spaces+6;
}

for (msys=1;msys<=nsys;msys++) {
#  disentangle system name into os, co(mpiler), arch, opt
   lcg=allsys[msys];
   if ( index("-",lcg) > 0 ) {
   # new convention
#      printf(" new : %s\n",lcg);
   } else {
#      printf(" old : %s\n",lcg);
   }    
}

#match(failed,'test',test_fail);
 
n_elem=asort(failed);

for (elem=1;elem<=n_elem;elem++ ) {
     fail=failed[elem]
     offset=1
     if ( length(fail) > 42 ) {offset=length(fail)-42+1}
     printf("\n%42s |",substr(fail,offset));
     for (msys=1;msys<=nsys;msys++) {
        strg="     |";
        if ( index(systems[fail],allsys[msys]) ) { 
	   strg=" =X= |";
	   if ( index(expected[fail],allsys[msys]) )
	    { strg="  x  |";} 
	} else {
	   if ( index(expected[fail],allsys[msys]) )
	    { strg=" O-K |";}
	}  
        printf("%s",strg);
     }
  }
  printf("\n\n");	
}
EoI

awk -f $awkfile $logfile
rm $awkfile  
exit
#http://lcgapp.cern.ch/spi/aaLibrarian/nightlies/slc4_amd64_gcc34/geant4.Wed_geant4-slc4_amd64_gcc34-qmtest.brief.log
