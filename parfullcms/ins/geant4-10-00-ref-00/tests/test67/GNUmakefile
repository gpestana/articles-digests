# $Id: GNUmakefile 66789 2013-01-12 15:21:07Z gcosmo $
# --------------------------------------------------------------
# GNUmakefile for tests module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := test67
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../..
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/architecture.gmk

ifdef ROOTSYS
  CPPFLAGS += `root-config --cflags`
  CPPFLAGS += -DG4_USE_ROOT
  LDFLAGS  += `root-config --libs`
endif

include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*


