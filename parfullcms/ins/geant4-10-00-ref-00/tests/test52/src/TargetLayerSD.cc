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

#include "TargetLayerSD.hh"
#include "TargetLayerHit.hh"
#include "AnalysisManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "CLHEP/Random/Randomize.h"

G4Allocator<TargetLayerHit> TargetLayerHitAllocator;


TargetLayerSD::TargetLayerSD(G4String SDuniqueName) :
    G4VSensitiveDetector(SDuniqueName),
    hitsCollectionID(-1) {

  G4String hitsCollectionName = SensitiveDetectorName + "HitsColl";

  collectionName.insert(hitsCollectionName);
}


TargetLayerSD::~TargetLayerSD() {

}


void TargetLayerSD::Initialize(G4HCofThisEvent* hitsCollEvent) {
  
  hitsCollection = 
     new TargetLayerHitsCollection(SensitiveDetectorName, collectionName[0]);
 
  if(hitsCollectionID < 0) {
     hitsCollectionID =
         G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
  }

  hitsCollEvent -> AddHitsCollection(hitsCollectionID, hitsCollection);
}


G4bool TargetLayerSD::ProcessHits(G4Step* step, G4TouchableHistory*) {

  if(step == 0) return false;

  TargetLayerHit* hit = new TargetLayerHit; 

  hit -> StoreEnergyDeposit(step -> GetTotalEnergyDeposit());
  hit -> StorePositionPre(step -> GetPreStepPoint() -> GetPosition());
  hit -> StorePositionPost(step -> GetPostStepPoint() -> GetPosition());
  hit -> StoreParticleType(
                 step -> GetTrack() -> GetDefinition() -> GetParticleName());
  hit -> StoreTrackID(step -> GetTrack() -> GetTrackID());  

  hitsCollection -> insert(hit);

  return true;
}


void TargetLayerSD::EndOfEvent(G4HCofThisEvent*) {

  AnalysisManager* analysisManager = AnalysisManager::Instance();

  G4int nmbHits = hitsCollection -> entries();

  for(G4int i=0;i < nmbHits; i++) {

     G4double frac = CLHEP::RandFlat::shoot();

     G4double x = (*hitsCollection)[i] -> GetXCoordPre();
     G4double y = (*hitsCollection)[i] -> GetYCoordPre();
     G4double z = (*hitsCollection)[i] -> GetZCoordPre();

     x = x + frac * ((*hitsCollection)[i] -> GetXCoordPost() - x);
     y = y + frac * ((*hitsCollection)[i] -> GetYCoordPost() - y);
     z = z + frac * ((*hitsCollection)[i] -> GetZCoordPost() - z);

     analysisManager -> ScoreEnergyDeposit(
                             (*hitsCollection)[i] -> GetEnergyDeposit(), 
                             x, 
                             y, 
                             z, 
                             (*hitsCollection)[i] -> GetParticleType()); 
  }
}
