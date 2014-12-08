#
# This file is sourced by setup.csh script.
# 
####################################################
####################################################
### Specific STT member machines configurations  ###
####################################################
####################################################
#
####################################################
# Guy Barrand barrand@lal.in2p3.fr
# Steve O'Neale Birmingham/Cern ( CLHEP dev )
# Steve O'Neale Birmingham/Cern ( Reactivate persistancy)
# Steve O'Neale Birmingham/Cern ( Forgot to commit changes)
####################################################

setenv REF undefined
if ( `pwd | grep /stt/dev1/` != "" ) then
  setenv REF dev1
endif
if ( `pwd | grep /stt/dev2/` != "" ) then
  setenv REF dev2
endif
if ( `pwd | grep /stt/prod/` != "" ) then
  setenv REF prod
endif

if ( $?G4DEBUG ) then
  setenv DEBOPT debug
else
  setenv DEBOPT optim
endif

# Generaal G4 build flags :
setenv G4UI_BUILD_TERMINAL_SESSION 1
setenv G4UI_BUILD_GAG_SESSION      1
setenv G4VIS_BUILD_DAWN_DRIVER     1
setenv G4VIS_BUILD_DAWNFILE_DRIVER 1
setenv G4VIS_BUILD_VRML_DRIVER     1
setenv G4VIS_BUILD_VRMLFILE_DRIVER 1
setenv G4VIS_BUILD_RAYTRACER_DRIVER 1

if ( `uname -n | grep rsplus` != "" ) then
  setenv G4USE_OSPACE 1
  setenv CVSROOT /afs/cern.ch/sw/geant4/cvs
  setenv G4SYSTEM AIX-xlC
  setenv G4INSTALL /afs/cern.ch/sw/geant4/stt/$REF/src/geant4
  setenv G4STTDIR  /afs/cern.ch/sw/geant4/stt/$REF/testtools/geant4/tests/tools
  setenv G4WORKDIR  /afs/cern.ch/sw/geant4/stt/$REF/$G4SYSTEM/$DEBOPT
  setenv G4LIB $G4WORKDIR/lib
  # Other G4 build flags :
  #####setenv G4UI_BUILD_XM_SESSION       1
  #####setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  setenv XKEYSYMDB /usr/lib/X11/XKeysymDB
  setenv OGLHOME /afs/cern.ch/sw/geant4/dev/Mesa/Mesa-1.2.8
  ##### setenv G4VIS_BUILD_OIX_DRIVER      1
endif

if ( `uname -n | grep dxplus` != "" || \
     `uname -n | grep dcosf01` != "" ) then
  if ( $?G4STTNONISO ) then
    setenv DEBOPT ${DEBOPT}_NONISO
    setenv G4USE_OSPACE 1
    setenv CLHEP_BASE_DIR /afs/cern.ch/sw/geant4/dev/CLHEP/DEC-cxx/noiso
  else
    setenv DEBOPT ${DEBOPT}_ISO
    setenv CLHEP_BASE_DIR /afs/cern.ch/sw/geant4/dev/CLHEP/DEC-cxx/pro
  endif
  if ( `uname -n | grep dcosf01` != "" ) then
    setenv CLHEP_LIB CLHEP-cxx62
  endif
  setenv CVSROOT /afs/cern.ch/sw/geant4/cvs
  setenv G4SYSTEM DEC-cxx
  setenv G4INSTALL /afs/cern.ch/sw/geant4/stt/$REF/src/geant4
  setenv G4STTDIR  /afs/cern.ch/sw/geant4/stt/$REF/testtools/geant4/tests/tools
  setenv G4WORKDIR  /afs/cern.ch/sw/geant4/stt/$REF/$G4SYSTEM/$DEBOPT
  setenv G4LIB $G4WORKDIR/lib
  # G4 build flags :
  #####setenv G4UI_BUILD_XM_SESSION       1
  #####setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  setenv XKEYSYMDB /usr/lib/X11/XKeysymDB
  setenv OGLHOME /afs/cern.ch/sw/geant4/dev/Mesa/Mesa-1.2.8
  ##### setenv G4VIS_BUILD_OIX_DRIVER      1
endif

if ( `uname -n | grep pcg4speed` != "" ) then
  setenv DEBOPT ${DEBOPT}_NEWGCC
  setenv CVSROOT /afs/cern.ch/sw/geant4/cvs
  setenv G4SYSTEM Linux-g++
  setenv G4INSTALL /afs/cern.ch/sw/geant4/stt/$REF/src/geant4
  setenv G4STTDIR  /afs/cern.ch/sw/geant4/stt/$REF/testtools/geant4/tests/tools
  setenv G4WORKDIR  /afs/cern.ch/sw/geant4/stt/$REF/$G4SYSTEM/$DEBOPT
  setenv G4LIB $G4WORKDIR/lib
  # G4 build flags :
  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  setenv XKEYSYMDB /usr/lib/X11/XKeysymDB
  setenv OGLHOME /afs/cern.ch/sw/geant4/dev/Mesa/Mesa-1.2.8
  setenv CLHEP_BASE_DIR /afs/cern.ch/sw/geant4/dev/CLHEP/$G4SYSTEM/pro
  # Shareable library
#  setenv G4LIB_BUILD_SHARED 1
#  setenv LD_LIBRARY_PATH $G4LIB/$G4SYSTEM
endif

if ( `uname -n | grep pcgeant$`   != "" ) then
  setenv CVSROOT /afs/cern.ch/sw/geant4/cvs
  setenv G4SYSTEM Linux-egcs
  setenv G4INSTALL /afs/cern.ch/sw/geant4/stt/$REF/src/geant4
  setenv G4STTDIR  /afs/cern.ch/sw/geant4/stt/$REF/testtools/geant4/tests/tools
  setenv G4WORKDIR  /afs/cern.ch/sw/geant4/stt/$REF/$G4SYSTEM/$DEBOPT
  setenv G4LIB $G4WORKDIR/lib
  # G4 build flags :
  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  setenv XKEYSYMDB /usr/lib/X11/XKeysymDB
  setenv OGLHOME /afs/cern.ch/sw/geant4/dev/Mesa/Mesa-1.2.8
  setenv CLHEP_BASE_DIR /afs/cern.ch/sw/geant4/dev/CLHEP/$G4SYSTEM/pro
endif

if ( `uname -n | grep pcgeant2` != "" ) then
  setenv CLHEP_VERSION pro                    
  setenv DEBOPT ${DEBOPT}_7.2_2.95.2
  setenv CVSROOT /afs/cern.ch/sw/geant4/cvs
  setenv G4SYSTEM Linux-g++
  setenv G4INSTALL /afs/cern.ch/sw/geant4/stt/$REF/src/geant4
  setenv G4STTDIR  /afs/cern.ch/sw/geant4/stt/$REF/testtools/geant4/tests/tools
  setenv G4WORKDIR  /afs/cern.ch/sw/geant4/stt/$REF/$G4SYSTEM/$DEBOPT
  setenv G4LIB $G4WORKDIR/lib
  setenv CLHEP_BASE_DIR /afs/cern.ch/sw/geant4/dev/CLHEP/Linux-g++/$CLHEP_VERSION

  # Shareable library
  #####################
  setenv G4LIB_BUILD_SHARED 1
  setenv LD_LIBRARY_PATH $G4LIB/$G4SYSTEM:${CLHEP_BASE_DIR}/lib

  # G4 build flags :
endif

if ( `uname -n | grep pcgeant3` != "" ) then
  setenv CLHEP_VERSION pro               
  setenv DEBOPT ${DEBOPT}_7.2_2.95.2
  setenv CVSROOT /afs/cern.ch/sw/geant4/cvs
  setenv G4SYSTEM Linux-g++
  setenv G4INSTALL /afs/cern.ch/sw/geant4/stt/$REF/src/geant4
  setenv G4STTDIR  /afs/cern.ch/sw/geant4/stt/$REF/testtools/geant4/tests/tools
  setenv G4WORKDIR  /afs/cern.ch/sw/geant4/stt/$REF/$G4SYSTEM/$DEBOPT
  setenv G4LIB $G4WORKDIR/lib
  setenv CLHEP_BASE_DIR /afs/cern.ch/sw/geant4/dev/CLHEP/Linux-g++/${CLHEP_VERSION}

  # Shareable library
  #####################
  setenv G4LIB_BUILD_SHARED 1
  setenv LD_LIBRARY_PATH ${G4LIB}/${G4SYSTEM}:${CLHEP_BASE_DIR}/lib:/afs/cern.ch/sw/geant4/dev/XercesC/Linux-g++/RH72
#
#  # G4 build flags :
#######export G4UI_BUILD_XM_SESSION=1
##  export G4VIS_BUILD_OPENGLXM_DRIVER=1
##  export G4VIS_BUILD_OPENGLX_DRIVER=1
##  export G4VIS_BUILD_OIX_DRIVER=1
#
endif

if ( `uname -n | grep pcgeant4` != "" ) then
  setenv DEBOPT ${DEBOPT}_NEWGCC
  setenv CVSROOT /afs/cern.ch/sw/geant4/cvs
  setenv G4SYSTEM Linux-g++
  setenv G4INSTALL /afs/cern.ch/sw/geant4/stt/$REF/src/geant4
  setenv G4STTDIR  /afs/cern.ch/sw/geant4/stt/$REF/testtools/geant4/tests/tools
  setenv G4WORKDIR  /afs/cern.ch/sw/geant4/stt/$REF/$G4SYSTEM/$DEBOPT
  setenv G4LIB $G4WORKDIR/lib
  # G4 build flags :
  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  setenv XKEYSYMDB /usr/lib/X11/XKeysymDB
  setenv OGLHOME /afs/cern.ch/sw/geant4/dev/Mesa/Mesa-1.2.8
  setenv CLHEP_BASE_DIR /afs/cern.ch/sw/geant4/dev/CLHEP/$G4SYSTEM/pro
  # Shareable library
  setenv G4LIB_BUILD_SHARED 1
  setenv LD_LIBRARY_PATH $G4LIB/$G4SYSTEM
endif

if ( `uname -n | grep sgmedia` != "" ) then
  setenv G4USE_OSPACE 1
  setenv CVSROOT /afs/cern.ch/sw/geant4/cvs
  setenv G4SYSTEM SGI-CC
  setenv G4INSTALL /afs/cern.ch/sw/geant4/stt/$REF/src/geant4
  setenv G4STTDIR  /afs/cern.ch/sw/geant4/stt/$REF/testtools/geant4/tests/tools
  setenv G4WORKDIR  /afs/cern.ch/sw/geant4/stt/$REF/$G4SYSTEM/$DEBOPT
  setenv G4LIB $G4WORKDIR/lib
  # G4 build flags :
  #######setenv G4UI_BUILD_XM_SESSION       1
  setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  setenv G4VIS_BUILD_OIX_DRIVER      1
endif

if ( `uname -n | grep sun` != "" ) then
  setenv CVSROOT /afs/cern.ch/sw/geant4/cvs
  setenv G4INSTALL /afs/cern.ch/sw/geant4/stt/$REF/src/geant4
  setenv G4STTDIR  /afs/cern.ch/sw/geant4/stt/$REF/testtools/geant4/tests/tools
  if ( $?G4STTNONISO ) then
    setenv G4SYSTEM SUN-CC4
    setenv DEBOPT ${DEBOPT}_NONISO
    setenv G4USE_OSPACE 1
    setenv PATH `echo $PATH | sed s/SUNWspro50/SUNWspro/`
    setenv CLHEP_BASE_DIR /afs/cern.ch/sw/geant4/dev/CLHEP/$G4SYSTEM/pro
    # Persistency...
    if ( $?G4USE_HEPODBMS ) then  # Protect against double calling.
    else
      if ( -f $G4INSTALL/examples/extended/persistency/PersistentEx01/g4odbms_setup.csh ) then
        source $G4INSTALL/examples/extended/persistency/PersistentEx01/g4odbms_setup.csh
        setenv G4EXAMPLE_FDID 207
      else
        echo "G4USE_HEPODBMS undefined as source tree does not contain g4odbms_setup.csh"
        unsetenv G4USE_HEPODBMS
        unsetenv G4EXAMPLE_FDID
      endif
    endif
  else
    setenv G4SYSTEM SUN-CC
    setenv DEBOPT ${DEBOPT}_ISO
    unsetenv G4USE_OSPACE
    setenv PATH `echo $PATH | sed s/SUNWspro/SUNWspro50/`
    setenv PATH `echo $PATH | sed s/SUNWspro50/SUNWspro/`
    # Persistency...
    unsetenv G4USE_HEPODBMS
    setenv CLHEP_BASE_DIR /afs/cern.ch/sw/geant4/dev/CLHEP/$G4SYSTEM/pro
  endif
  setenv G4WORKDIR  /afs/cern.ch/sw/geant4/stt/$REF/$G4SYSTEM/$DEBOPT
  setenv G4LIB $G4WORKDIR/lib
  # G4 build flags :
  #######setenv G4UI_BUILD_XM_SESSION       1
  #######setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
  #######setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  #######setenv G4VIS_BUILD_OIX_DRIVER      1
endif

if ( `uname -n | grep refsol7` != "" ) then
  setenv CVSROOT /afs/cern.ch/sw/geant4/cvs
  setenv G4INSTALL /afs/cern.ch/sw/geant4/stt/$REF/src/geant4
  setenv G4STTDIR  /afs/cern.ch/sw/geant4/stt/$REF/testtools/geant4/tests/tools
  if ( $?G4STTNONISO ) then
    echo "refsol7 only supports the ISO compiler"
    setenv G4SYSTEM SUN-CC4
    setenv DEBOPT ${DEBOPT}_NONISO
    setenv G4USE_OSPACE 1
    setenv PATH `echo $PATH | sed s/SUNWspro50/SUNWspro/`
    setenv CLHEP_BASE_DIR /afs/cern.ch/sw/geant4/dev/CLHEP/$G4SYSTEM/pro
    # Persistency...
    if ( $?G4USE_HEPODBMS ) then  # Protect against double calling.
    else
      source $G4INSTALL/examples/extended/persistency/PersistentEx01/g4odbms_setup.csh
      setenv G4EXAMPLE_FDID 207
    endif
  else
    setenv G4SYSTEM SUN-CC
    setenv DEBOPT ${DEBOPT}_ISO
    unsetenv G4USE_OSPACE
    unsetenv G4STTNONISO
#   setenv PATH `echo $PATH | sed s/SUNWspro50/SUNWspro/`
#   setenv PATH `echo $PATH | sed s/SUNWspro/SUNWspro50/`
    # Persistency...
    unsetenv G4USE_HEPODBMS
    setenv CLHEP_BASE_DIR /afs/cern.ch/sw/geant4/dev/CLHEP/$G4SYSTEM/pro
  endif
  setenv G4WORKDIR  /afs/cern.ch/sw/geant4/stt/$REF/$G4SYSTEM/$DEBOPT
  setenv G4LIB $G4WORKDIR/lib
  # G4 build flags :
  #######setenv G4UI_BUILD_XM_SESSION       1
  #######setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
  #######setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  #######setenv G4VIS_BUILD_OIX_DRIVER      1
endif

if ( `uname -n | grep hp` != "" ) then
  setenv G4USE_OSPACE 1
  setenv CVSROOT /afs/cern.ch/sw/geant4/cvs
  setenv G4SYSTEM HP-aCC
  setenv G4INSTALL /afs/cern.ch/sw/geant4/stt/$REF/src/geant4
  setenv G4STTDIR  /afs/cern.ch/sw/geant4/stt/$REF/testtools/geant4/tests/tools
  setenv G4WORKDIR  /afs/cern.ch/sw/geant4/stt/$REF/$G4SYSTEM/$DEBOPT
  setenv G4LIB $G4WORKDIR/lib
  setenv CLHEP_BASE_DIR /afs/cern.ch/sw/geant4/dev/CLHEP/$G4SYSTEM/pro
  # G4 build flags :
  ######setenv G4UI_BUILD_XM_SESSION       1
  setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  setenv G4VIS_BUILD_OIX_DRIVER      1
endif

####################################################
### LAL Orsay machines                           ###
####################################################
if ( `uname -n` == aleph ) then
  setenv CVSROOT :pserver:barrand@g4cvs.cern.ch:/afs/cern.ch/sw/geant4/cvs
  setenv G4INSTALL /geant4/geant4-01-00-ref-02
  setenv G4WORKDIR $G4INSTALL
  setenv G4STTDIR  $G4WORKDIR/stt
  setenv G4LIB     $G4WORKDIR/lib
  setenv G4SYSTEM  HP-aCC
  setenv G4DEBUG   1
  #setenv G4MAKESHLIB                 $G4INSTALL/config/makeshlib.sh
  # G4 build flags :
  setenv G4UI_BUILD_XM_SESSION       1
  setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  setenv G4VIS_BUILD_OIX_DRIVER      1
  setenv G4VIS_BUILD_DAWN_DRIVER     1
  setenv G4VIS_BUILD_DAWNFILE_DRIVER 1
  setenv G4VIS_BUILD_VRML_DRIVER     1
  setenv G4VIS_BUILD_VRMLFILE_DRIVER 1
  # G4 use flags :
  setenv G4UI_USE_XM                 1
  setenv G4VIS_USE_OPENGLXM          1
  setenv G4VIS_USE_OPENGLX           1
  setenv G4VIS_USE_OIX               1
  setenv G4VIS_USE_DAWN              1
  setenv G4VIS_USE_DAWNFILE          1
  setenv G4VIS_USE_VRML              1
  setenv G4VIS_USE_VRMLFILE          1
  # Specific :
  setenv CLHEP_BASE_DIR /lal/CLHEP/1.4/HP-UX-aCC
  setenv OGLHOME        /lal/Mesa/3.1/HP-UX
  setenv OGLLIBS        "-L$OGLHOME/lib -lGLU -lGL"
  setenv OIVHOME        /lal/SoFree/v2r9
  setenv HEPVISHOME     /lal/HEPVis/v5r1-05-LAL
  setenv OIVFLAGS       "-I$OIVHOME/include -I$HEPVISHOME/include"
  setenv OIVLIBS        "-L$HEPVISHOME/HP-UX-aCC-SF -lHEPVis -L$OIVHOME/HP-UX-aCC -lSoFree"
  setenv SOFREEUSER     $OIVHOME/user/
  # OPACS :
  setenv G4UI_BUILD_WO_SESSION       1
  setenv G4VIS_BUILD_OPACS_DRIVER    1
  setenv G4UI_USE_WO                 1
  setenv G4VIS_USE_OPACS             1
  setenv OCONFIG HP-UX
  source /lal/OPACS/v3/setup.csh
  # Else :
  #setenv XENVIRONMENT   $G4INSTALL/tests/test201/test201.xrm
  setenv XENVIRONMENT   g4.xrm
  setenv PATH "${PATH}:/lal/DAWN/3.72b/HP-UX-aCC"
  setenv CPPVERBOSE 1
  set prompt='g4-aleph> ' 
endif
#---------------------------------------------------
if ( `uname -n` == asc ) then
  # In CLHEP-default.h : //GB #define HEP_USE_STD 1
  #                      //GB #define HEP_HAVE_BOOL 1
  setenv CVSROOT :pserver:barrand@g4cvs.cern.ch:/afs/cern.ch/rd44/cvs
  setenv G4INSTALL /geant4/geant4-02-00
  setenv G4WORKDIR $G4INSTALL
  setenv G4STTDIR  $G4WORKDIR/stt
  setenv G4LIB     $G4WORKDIR/lib
  setenv G4SYSTEM DEC-cxx
  setenv G4DEBUG 1
  #setenv G4MAKESHLIB $G4INSTALL/config/makeshlib.sh
  # G4 build flags :
  setenv G4UI_BUILD_XM_SESSION       1
  setenv G4UI_BUILD_XAW_SESSION      1
  setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  #TGS out with cxx ansi : 
  #setenv G4VIS_BUILD_OIX_DRIVER      1
  setenv G4VIS_BUILD_DAWN_DRIVER     1
  setenv G4VIS_BUILD_DAWNFILE_DRIVER 1
  # Pb with cxx ansi :
  #setenv G4VIS_BUILD_VRML_DRIVER     1
  #setenv G4VIS_BUILD_VRMLFILE_DRIVER 1
  # G4 use flags :
  setenv G4UI_USE_XM                 1
  setenv G4UI_USE_XAW                1
  setenv G4VIS_USE_OPENGLXM          1
  setenv G4VIS_USE_OPENGLX           1
  #setenv G4VIS_USE_OIX               1
  setenv G4VIS_USE_DAWN              1
  setenv G4VIS_USE_DAWNFILE          1
  # Pb with cxx ansi :
  #setenv G4VIS_USE_VRML              1
  #setenv G4VIS_USE_VRMLFILE          1
  # Specific :
  setenv CLHEP_BASE_DIR /lal/CLHEP/1.5/OSF1-cxx
  setenv OGLHOME        /lal/Mesa/3.2/OSF1
  setenv OIVHOME        /lal/OpenInventor/2.5
  setenv HEPVISHOME     /lal/HEPVis/v5r1-05-LAL
  setenv OIVFLAGS       "-I$OIVHOME/include -I$HEPVISHOME/include"
  setenv OIVLIBS        "-L$HEPVISHOME/OSF1-cxx-TGS -lHEPVis -L$OIVHOME/lib -lInventorXt -lInventor -limage"
  #setenv XENVIRONMENT   $OIVHOME/app-defaults/Inventor
  setenv XENVIRONMENT   g4.xrm
  # OPACS :
  setenv G4UI_BUILD_WO_SESSION       1
  setenv G4VIS_BUILD_OPACS_DRIVER    1
  setenv G4UI_USE_WO                 1
  setenv G4VIS_USE_OPACS             1
  source /lal/OPACS/v3/setup.csh
  set prompt=${G4INSTALL}-${G4SYSTEM}'> '
  # Else :
  setenv LD_LIBRARY_PATH "$OIVHOME/lib:$HEPVISHOME/OSF1-cxx-TGS:${OGLHOME}/lib"
  setenv PATH "${PATH}:/lal/DAWN/3.72b/OSF1-cxx"
  setenv XENVIRONMENT   g4Xt.xrm
  setenv CPPVERBOSE 1
  set prompt='g4-asc> ' 
  # To be able to link :
  limit datasize 500000
endif
#---------------------------------------------------
if ( `uname -n` == "lx1.lal.in2p3.fr" ) then
  setenv CVSROOT :pserver:barrand@g4cvs.cern.ch:/afs/cern.ch/sw/geant4/cvs
  setenv G4INSTALL /geant4/geant4-01-01
  setenv G4WORKDIR $G4INSTALL
  setenv G4STTDIR  $G4WORKDIR/stt
  setenv G4LIB     $G4WORKDIR/lib
  setenv G4SYSTEM  Linux-g++
  setenv G4DEBUG   1
  #setenv G4MAKESHLIB                 $G4INSTALL/config/makeshlib.sh
  # G4 build flags :
  setenv G4UI_BUILD_XM_SESSION       1
  setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  setenv G4VIS_BUILD_OIX_DRIVER      1
  setenv G4VIS_BUILD_DAWN_DRIVER     1
  setenv G4VIS_BUILD_DAWNFILE_DRIVER 1
  setenv G4VIS_BUILD_VRML_DRIVER     1
  setenv G4VIS_BUILD_VRMLFILE_DRIVER 1
  # G4 use flags :
  setenv G4UI_USE_XM                 1
  setenv G4VIS_USE_OPENGLXM          1
  setenv G4VIS_USE_OPENGLX           1
  setenv G4VIS_USE_OIX               1
  setenv G4VIS_USE_DAWN              1
  setenv G4VIS_USE_DAWNFILE          1
  setenv G4VIS_USE_VRML              1
  setenv G4VIS_USE_VRMLFILE          1
  # Specific :
  setenv CLHEP_BASE_DIR /lal/CLHEP/1.4/Linux-gxx
  setenv OGLHOME        /lal/Mesa/3.1/Linux
  setenv OIVHOME        /lal/SoFree/v2r9
  setenv HEPVISHOME     /lal/HEPVis/v5r1-05-LAL
  setenv OIVFLAGS       "-I$OIVHOME/include -I$HEPVISHOME/include"
  setenv OIVLIBS        "-L$HEPVISHOME/Linux-gxx-SF -lHEPVis -L$OIVHOME/Linux-gxx -lSoFree"
  setenv SOFREEUSER     $OIVHOME/user/
  # OPACS :
  setenv G4UI_BUILD_WO_SESSION       1
  setenv G4VIS_BUILD_OPACS_DRIVER    1
  setenv G4UI_USE_WO                 1
  setenv G4VIS_USE_OPACS             1
  source /lal/OPACS/v3/setup.csh
  setenv LD_LIBRARY_PATH "${LD_LIBRARY_PATH}:$OIVHOME/Linux-gxx:$HEPVISHOME/Linux-gxx-SF:${OGLHOME}/lib"
  # Else :
  #setenv XENVIRONMENT   $G4INSTALL/tests/test201/test201.xrm
  setenv XENVIRONMENT   g4.xrm
  setenv PATH "${PATH}:/lal/DAWN/3.72b/Linux-egcs"
  setenv CPPVERBOSE 1
  set prompt='g4-lx1> ' 
endif
#
if ( `uname -n` == "papou1" ) then
  setenv CVSROOT :pserver:barrand@g4cvs.cern.ch:/afs/cern.ch/sw/geant4/cvs
  setenv G4INSTALL /geant4/geant4-01-00-ref-02
  setenv G4WORKDIR $G4INSTALL
  setenv G4STTDIR  $G4WORKDIR/stt
  setenv G4LIB     $G4WORKDIR/lib
  setenv G4SYSTEM  SUN-CC5
  setenv G4DEBUG   1
  #setenv G4MAKESHLIB                 $G4INSTALL/config/makeshlib.sh
  # G4 build flags :
  setenv G4UI_BUILD_XM_SESSION       1
  setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  #setenv G4VIS_BUILD_OIX_DRIVER      1
  setenv G4VIS_BUILD_DAWN_DRIVER     1
  setenv G4VIS_BUILD_DAWNFILE_DRIVER 1
  setenv G4VIS_BUILD_VRML_DRIVER     1
  setenv G4VIS_BUILD_VRMLFILE_DRIVER 1
  # G4 use flags :
  setenv G4UI_USE_XM                 1
  setenv G4VIS_USE_OPENGLXM          1
  setenv G4VIS_USE_OPENGLX           1
  #setenv G4VIS_USE_OIX               1
  # Specific :
  setenv CLHEP_BASE_DIR /lal/CLHEP/1.4/SunOS-CC
  setenv OGLHOME        /lal/Mesa/3.0/SunOS
  setenv OIVHOME        /lal/SoFree/v2r9
  setenv HEPVISHOME     /lal/HEPVis/v5r1-05-LAL
  setenv OIVFLAGS       "-I$OIVHOME/include -I$HEPVISHOME/include"
  setenv OIVLIBS        "-L$HEPVISHOME/SunOS-CC -lHEPVis -L$OIVHOME/SunOS-CC -lSoFree"
  setenv SOFREEUSER     $OIVHOME/user/
  # OPACS :
  #setenv G4UI_BUILD_WO_SESSION       1
  #setenv G4VIS_BUILD_OPACS_DRIVER    1
  #setenv G4UI_USE_WO                 1
  #setenv G4VIS_USE_OPACS             1
  #source /lal/OPACS/v3/setup.csh
  #setenv LD_LIBRARY_PATH "$OIVHOME/Linux-gxx:/lal/HEPVis/v5r0/Linux-gxx"
  # Else :
  setenv CPPVERBOSE 1
  set prompt='g4-papou1> ' 
endif
# Comments :
# --------
#
if ( `uname -n` == "pc-gbp" || `uname -n` == "pc-89026" || `uname -n` == "pc100" || `uname -n` == "pcal26" ) then
  setenv CVSROOT :pserver:barrand@g4cvs.cern.ch:/afs/cern.ch/sw/geant4/cvs
  setenv G4INSTALL /geant4/geant4-03-02-ref-00
  setenv G4WORKDIR $G4INSTALL
  setenv G4STTDIR  $G4WORKDIR/stt
  setenv G4LIB     $G4WORKDIR/lib
  setenv G4SYSTEM  Linux-g++
  setenv G4DEBUG   1
  setenv G4LIB_BUILD_SHARED 1
  # G4 build flags :
  setenv G4UI_BUILD_XM_SESSION       1
  setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
  setenv G4VIS_BUILD_OIX_DRIVER      1
  setenv G4VIS_BUILD_DAWN_DRIVER     1
  setenv G4VIS_BUILD_DAWNFILE_DRIVER 1
  setenv G4VIS_BUILD_VRML_DRIVER     1
  setenv G4VIS_BUILD_VRMLFILE_DRIVER 1
  setenv G4ANALYSIS_BUILD_LAB        1
  setenv G4ANALYSIS_BUILD_JAS        1
#  setenv G4ANALYSIS_BUILD_LIZARD     1
  #setenv G4ANALYSIS_TUPLE 1
  #setenv G4ANALYSIS_CLOUD 1
  setenv G4ANALYSIS_LAB_VISUALIZATION 1
  # G4 use flags :
  setenv G4UI_USE_XM                 1
  setenv G4VIS_USE_OPENGLXM          1
  setenv G4VIS_USE_OPENGLX           1
  setenv G4VIS_USE_OIX               1
  setenv G4VIS_USE_DAWN              1
  setenv G4VIS_USE_DAWNFILE          1
  setenv G4VIS_USE_VRML              1
  setenv G4VIS_USE_VRMLFILE          1
  setenv G4ANALYSIS_USE_LAB          1
  setenv G4ANALYSIS_USE_JAS          1
#  setenv G4ANALYSIS_USE_LIZARD       1
  setenv G4ANALYSIS_SYSTEM           Lab
  # AIDA : 
  setenv G4ANALYSIS_AIDA /lal/AIDA/1.0/AIDA
  # Lab :
  setenv CMTPATH /archos/OSC/v6r1
  source /archos/OSC/v6r1/Lab/v4r1/cmt/setup.csh
  # CLHEP :
  setenv CLHEP_BASE_DIR /lal/CLHEP/1.6.0.0/Linux-gxx
  # Things needed by the Geant4/vis/drivers :
  #setenv OGLHOME        /usr/X11R6
  setenv OGLHOME        /lal/Mesa/3.2/Linux
  setenv TTFLIBS        "-L/lal/freetype/1.3.1/Linux/lib -lttf"
  setenv OIVFLAGS       "-I$HEPVISROOT/include -I$SOFREEROOT/include"
  setenv OIVLIBS        "-L$HEPVISROOT/$HEPVISCONFIG -lHEPVisXm -lHEPVisXt -lHEPVis ${TTFLIBS} -L$SOFREEROOT/$SOFREECONFIG -lSoFreeXt -lSoFree"
  #setenv SOFREEUSER     $OIVHOME/user/
  # OPACS :
  #setenv G4UI_BUILD_WO_SESSION       1
  #setenv G4VIS_BUILD_OPACS_DRIVER    1
  #setenv G4UI_USE_WO                 1
  #setenv G4VIS_USE_OPACS             1
  #source /lal/OPACS/v3/setup.csh
  #
  # java :
  setenv JDKHOME /lal/JDK/1.2.2/Linux
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:$JDKHOME/jre/lib/i386:$JDKHOME/jre/lib/i386/classic:$JDKHOME/jre/lib/i386/native_threads
  # jas :
  set jars=/lal/jas/2.0alpha4/release/lib
  setenv CLASSPATH ${CLASSPATH}:$jars/collections.jar:$jars/hep.jar:$jars/jas.jar
  setenv PATH ${PATH}:/lal/jas/2.0alpha4/release
  # Else :
  #setenv XENVIRONMENT   g4Xt.xrm
  setenv PATH "${PATH}:/lal/DAWN/dawn_3_85a/Linux/bin"
  setenv CPPVERBOSE 1
  alias g4ANA01 "cd $G4INSTALL/examples/extended/analysis/AnaEx01"
  alias ana01   "$G4WORKDIR/bin/$G4SYSTEM/AnaEx01"
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${G4INSTALL}/lib/${G4SYSTEM}
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${G4INSTALL}/tmp/${G4SYSTEM}/AnaEx01
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${G4INSTALL}/tmp/${G4SYSTEM}/dm_example
  set prompt='g4-pc-gbp> ' 
endif
#
#
if ( `uname -n` == "lx-si1.lal.in2p3.fr" ) then
  setenv CVSROOT :pserver:barrand@g4cvs.cern.ch:/afs/cern.ch/sw/geant4/cvs
  setenv G4INSTALL /geant4/geant4-03-02-ref-00
  setenv G4WORKDIR $G4INSTALL
  setenv G4STTDIR  $G4WORKDIR/stt
  setenv G4LIB     $G4WORKDIR/lib
  setenv G4SYSTEM  Linux-g++
  setenv G4DEBUG   1
  setenv G4LIB_BUILD_SHARED 1
  # G4 build flags :
#  setenv G4UI_BUILD_XM_SESSION       1
#  setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
#  setenv G4VIS_BUILD_OPENGLX_DRIVER  1
#  setenv G4VIS_BUILD_OIX_DRIVER      1
  setenv G4VIS_BUILD_DAWN_DRIVER     1
  setenv G4VIS_BUILD_DAWNFILE_DRIVER 1
  setenv G4VIS_BUILD_VRML_DRIVER     1
  setenv G4VIS_BUILD_VRMLFILE_DRIVER 1
#  setenv G4ANALYSIS_BUILD_LAB        1
#  setenv G4ANALYSIS_BUILD_JAS        1
#  setenv G4ANALYSIS_BUILD_LIZARD     1
  #setenv G4ANALYSIS_TUPLE 1
  #setenv G4ANALYSIS_CLOUD 1
#  setenv G4ANALYSIS_LAB_VISUALIZATION 1
  # G4 use flags :
#  setenv G4UI_USE_XM                 1
#  setenv G4VIS_USE_OPENGLXM          1
#  setenv G4VIS_USE_OPENGLX           1
#  setenv G4VIS_USE_OIX               1
  setenv G4VIS_USE_DAWN              1
  setenv G4VIS_USE_DAWNFILE          1
  setenv G4VIS_USE_VRML              1
  setenv G4VIS_USE_VRMLFILE          1
#  setenv G4ANALYSIS_USE_LAB          1
#  setenv G4ANALYSIS_USE_JAS          1
#  setenv G4ANALYSIS_USE_LIZARD       1
#  setenv G4ANALYSIS_SYSTEM           Lab
  # CLHEP :
  setenv CLHEP_BASE_DIR /lal/CLHEP/1.6.0.0/Linux-gxx
endif
#
if ( `uname -n | grep lxplus` != "" ) then
if ( `whoami` == "gbarrand" ) then
  setenv CVSROOT   /afs/cern.ch/sw/geant4/cvs
  setenv G4INSTALL /afs/cern.ch/sw/contrib/geant4/dev
  setenv G4WORKDIR $G4INSTALL
  setenv G4STTDIR  $G4WORKDIR/stt
  setenv G4LIB     $G4WORKDIR/lib
  setenv G4SYSTEM  Linux-g++
  setenv G4DEBUG   1
  setenv CPPVERBOSE 1
  #setenv G4MAKESHLIB                 $G4INSTALL/config/makeshlib.sh
  # G4 build flags :
  setenv G4ANALYSIS_BUILD_LAB    1
  setenv G4ANALYSIS_BUILD_JAS    1
  setenv G4ANALYSIS_BUILD_LIZARD 1
  # G4 use flags :
  setenv G4UI_USE_XM             1
  setenv G4UI_USE_XAW            1
  setenv G4ANALYSIS_USE_LAB      1
  setenv G4ANALYSIS_USE_JAS      1
  setenv G4ANALYSIS_USE_LIZARD   1
  # AIDA : 
  setenv G4ANALYSIS_AIDA /afs/cern.ch/sw/contrib/AIDA/1.0/AIDA
  # Lab :
  setenv CMTSITE CERN
  source /afs/cern.ch/sw/contrib/Lab/v4r0/cmt/setup.csh
  # Lizard :
  setenv LIZARDROOT /afs/cern.ch/project/asddat/lhcxx/3.2.0/Gecko
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${LIZARDROOT}/lib
  # CLHEP :
  setenv CLHEP_BASE_DIR /afs/cern.ch/sw/lhcxx/specific/@sys/CLHEP/1.5.0.0
  #
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${G4LIB}/${G4SYSTEM}
  # java :
  #setenv JDKHOME /asis.local/i386_redhat61/usr.local/libexec/jdk/1.2.2
  #setenv JDKHOME /usr/local/libexec/jdk/1.2.2
  setenv JDKHOME /afs/cern.ch/sw/java/i386_redhat61/jdk/blackdown-1.2.2
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${JDKHOME}/jre/lib/i386:${JDKHOME}/jre/lib/i386/classic:${JDKHOME}/jre/lib/i386/native_threads
  # jas :
  set jars=/afs/cern.ch/sw/contrib/jas/2.0alpha4/release/lib
  setenv CLASSPATH ${CLASSPATH}:$jars/collections.jar:$jars/hep.jar:$jars/jas.jar
  # Else :
  alias g4ANA01 "cd $G4INSTALL/examples/extended/analysis/AnaEx01"
  alias ana01   "$G4WORKDIR/bin/$G4SYSTEM/AnaEx01"
  set prompt='g4-lxplus> ' 
endif
endif
#
####################################################
####################################################
