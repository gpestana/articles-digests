# $Id: GNUmakefile 66512 2012-12-19 10:26:52Z gcosmo $
# --------------------------------------------------------------
# GNUmakefile for tests module with AIDA interface
# --------------------------------------------------------------

name := test46
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../..
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/architecture.gmk

include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

