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
// $Id: DetectorConstruction.hh 66512 2012-12-19 10:26:52Z gcosmo $
//
//
/////////////////////////////////////////////////////////////////////////
//
// TestEm9: Cryslal calorimetry
//
// Created: 31.01.03 V.Ivanchenko
//
// Modified:
//
////////////////////////////////////////////////////////////////////////
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4VPhysicalVolume.hh"
 
class G4Box;
class G4LogicalVolume;
class G4Material;
class G4UniformMagField;
class DetectorMessenger;
class G4ProductionCuts;
class G4Region;
 
const G4int MaxAbsor = 17;		       

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

  DetectorConstruction();
  virtual ~DetectorConstruction();

  G4VPhysicalVolume* Construct();

  void SetMagField(G4double);

  void UpdateGeometry();

  void SetWorldMaterial(const G4String&);

  //PreShower
  void SetPSMaterial(const G4String&);
  void SetPSLength(G4double val);
  void SetPSGap(G4double val);

  //ECAL
  void SetEcalMaterial(const G4String&);
  void SetEcalLength(G4double val);
  void SetCrystalWidth(G4double val);
  void SetGapWidth  (G4double val);

  //HCAL
  void SetHcalWidth(G4double);          

  void SetBuildAllMatTest(G4bool);

private:

  void ConstructECAL();
  void ConstructHCAL();
  void ConstructAllMatTest();

  DetectorConstruction & operator=(const DetectorConstruction &right);
  DetectorConstruction(const DetectorConstruction&);

  G4UniformMagField* magField;
  DetectorMessenger* detectorMessenger;

  //World
  G4LogicalVolume*   logicWorld;
  G4VPhysicalVolume* physiWorld;

  G4Material* worldMaterial;
  G4double worldZ;
  G4double worldXY;

  //PreShower
  G4Material*      psMaterial;
  G4LogicalVolume* logicPS;
  G4double         psLength;   
  G4double         psgap;   
  G4double         psPosZ;

  //ECAL
  G4LogicalVolume* logicECal;
  G4LogicalVolume* logicCrystal;
  G4Material*      ecalMaterial;

  G4double crystalLength;   // ecalLength
  G4double crystalWidth;
  G4double ecalWidth;       
  G4double gap;
  G4double posCenterEcalZ;

  //HCAL
  G4ProductionCuts* cutsHCAL;
  G4Region*   regionHCAL;

  G4Material* scinMaterial;
  G4Material* absorMaterial[17];

  G4double absorThickness[17];
  G4double scinThickness[17]; 
  G4double posCenterHcalZ;
  G4double angularFactor;

  G4double hcalWidth;
  G4double hcalThickness;

  //PreShower
  G4double posCenterAllMatTestZ;
  G4bool buildAllMatTest;
};

#endif

