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
// $Id: F02CalorimeterSD.cc 66356 2012-12-18 09:02:32Z gcosmo $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "F02CalorimeterSD.hh"

#include "F02CalorHit.hh"
#include "F02DetectorConstruction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
  
#include "G4ios.hh"

/////////////////////////////////////////////////////////////////////////////////

F02CalorimeterSD::F02CalorimeterSD(G4String name,
                                   F02DetectorConstruction* det)
:G4VSensitiveDetector(name),Detector(det)
{
  collectionName.insert("CalCollection");
  HitID = new G4int[500];
}

//////////////////////////////////////////////////////////////////////////////////

F02CalorimeterSD::~F02CalorimeterSD()
{
  delete [] HitID;
}

/////////////////////////////////////////////////////////////////////////////

void F02CalorimeterSD::Initialize(G4HCofThisEvent*HCE)
{
  CalCollection = new F02CalorHitsCollection( SensitiveDetectorName,
                                              collectionName[0]      ); 
  for (G4int j=0;j<1; j++) 
  {
    HitID[j] = -1;
  }
}

////////////////////////////////////////////////////////////////////////////////

G4bool F02CalorimeterSD::ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  G4double stepl = 0.;
  // if ( (aStep->GetTrack()->GetDefinition()->GetPDGCharge()) != 0.0 ) 
  {
    stepl = aStep->GetStepLength();
  }
  if ((edep == 0.) && (stepl == 0.) ) return false;      

  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
    
  G4VPhysicalVolume* physVol = theTouchable->GetVolume();
 
  //theTouchable->MoveUpHistory();

  G4int F02Number = 0 ;

  if (HitID[F02Number]==-1)
  { 
    F02CalorHit* calHit = new F02CalorHit();

    if (physVol == Detector->GetAbsorber()) 
    {
      calHit->AddAbs(edep,stepl);
    }
    HitID[F02Number] = CalCollection->insert(calHit) - 1;

    if (verboseLevel>0)
    {  
      G4cout << " New Calorimeter Hit on F02: " << F02Number << G4endl;
    }
  }
  else
  { 
    if (physVol == Detector->GetAbsorber())
    {   
      (*CalCollection)[HitID[F02Number]]->AddAbs(edep,stepl);
    }
    if (verboseLevel>0)
    {    
      G4cout << " Energy added to F02: " << F02Number << G4endl;
    } 
  }    
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void F02CalorimeterSD::EndOfEvent(G4HCofThisEvent* HCE)
{
  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection(HCID,CalCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void F02CalorimeterSD::clear()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


void F02CalorimeterSD::PrintAll()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

