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
// $Id: Tst69DetectorConstruction.hh 75837 2013-11-06 17:24:27Z gcosmo $
//

#ifndef Tst69DetectorConstruction_h
#define Tst69DetectorConstruction_h 1

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class Tst69DetectorMessenger;

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class Tst69DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    Tst69DetectorConstruction();
    ~Tst69DetectorConstruction();

  public:
     G4VPhysicalVolume* Construct();
     void SelectMaterial(G4String val);

  private:
     void SelectMaterialPointer();

     G4LogicalVolume*   simpleBoxLog;
     G4Material* selectedMaterial;
     G4Material* theH;
     G4Material* theLi;
     G4Material* theC;
     G4Material* theSi;
     G4Material* theCu;
     G4Material* thePb;
     G4Material* theU;
     G4Material* theTh;
     G4Material* theMix;
     G4String materialChoice;
     Tst69DetectorMessenger * detectorMessenger;
};

#endif

