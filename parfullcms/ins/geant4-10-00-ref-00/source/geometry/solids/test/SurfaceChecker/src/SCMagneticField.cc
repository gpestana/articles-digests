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
// $Id: SCMagneticField.cc 66356 2012-12-18 09:02:32Z gcosmo $
//  
//   User Field class implementation.
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SCMagneticField.hh"
#include "G4FieldManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCMagneticField::SCMagneticField()
  : G4UniformMagField(G4ThreeVector())
{
  GetGlobalFieldManager()->SetDetectorField(this);
  GetGlobalFieldManager()->CreateChordFinder(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCMagneticField::SCMagneticField(G4ThreeVector fieldVector)
  : G4UniformMagField(fieldVector)
{
  GetGlobalFieldManager()->SetDetectorField(this);    
  GetGlobalFieldManager()->CreateChordFinder(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Set the value of the Global Field to fieldValue along X
//
void SCMagneticField::SetFieldValue(G4double fieldValue)
{
   G4UniformMagField::SetFieldValue(G4ThreeVector(fieldValue,0,0));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Set the value of the Global Field
//
void SCMagneticField::SetFieldValue(G4ThreeVector fieldVector)
{
  // Find the Field Manager for the global field
  G4FieldManager* fieldMgr= GetGlobalFieldManager();
    
  if(fieldVector!=G4ThreeVector(0.,0.,0.))
  { 
    G4UniformMagField::SetFieldValue(fieldVector);
    fieldMgr->SetDetectorField(this);
  } else {
    // If the new field's value is Zero, then it is best to
    //  insure that it is not used for propagation.
    G4MagneticField* magField = NULL;
    fieldMgr->SetDetectorField(magField);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCMagneticField::~SCMagneticField()
{
  // GetGlobalFieldManager()->SetDetectorField(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4TransportationManager.hh"

G4FieldManager*  SCMagneticField::GetGlobalFieldManager()
{
  return G4TransportationManager::GetTransportationManager()->GetFieldManager();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
