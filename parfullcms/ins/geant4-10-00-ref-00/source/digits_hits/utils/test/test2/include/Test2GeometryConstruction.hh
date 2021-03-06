//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: Test2GeometryConstruction.hh 67992 2013-03-13 10:59:57Z gcosmo $
//
// 

#ifndef Test2GeometryConstruction_h
#define Test2GeometryConstruction_h 1

#include "globals.hh"

class G4VPhysicalVolume;
class G4Material;
class G4LogicalVolume;

class Test2GeometryConstruction 
{
  public:
    Test2GeometryConstruction(G4double boxsize[3],
			      G4Material* material,
			      G4int segment[3]);

    virtual ~Test2GeometryConstruction();

  public:
    G4VPhysicalVolume* ConstructGeometry(G4VPhysicalVolume* worldPhys);

    G4LogicalVolume* GetSensitiveLogical()
    { return fLayerLogical[2]; }
     
  private:
    G4Material* fMaterial;
    G4VPhysicalVolume* fPhantomPhys;
    G4LogicalVolume * fLayerLogical[3];
    G4double phantomSize[3];
    G4int nSegment[3];
};

#endif

