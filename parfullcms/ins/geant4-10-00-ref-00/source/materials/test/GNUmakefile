# $Id: GNUmakefile 66811 2013-01-12 16:04:23Z gcosmo $
# ----------------------------------------------------------------
# Makes test program in environment variable G4TARGET.
# ----------------------------------------------------------------

ifndef G4TARGET
  G4TARGET := $(TESTTARGET)
endif

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

G4EXEC_BUILD = true

include $(G4INSTALL)/config/architecture.gmk

INCFLAGS := \
	    -I$(G4BASE)/global/management/include \
            -I$(G4BASE)/global/HEPRandom/include \
            -I$(G4BASE)/global/HEPGeometry/include \
            -I$(G4BASE)/materials/include \
	    -I$(G4BASE)/intercoms/include
	    
LDLIBS   := \
            -lG4materials \
            -lG4intercoms \
            -lG4globman
	    	    
include $(G4INSTALL)/config/binmake.gmk
