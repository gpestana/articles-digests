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
// $Id: SteppingAction.cc 66892 2013-01-17 10:57:59Z gunter $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4SteppingManager.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(DetectorConstruction* det,RunAction* RuAct)
:detector(det),runAction(RuAct)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  if (edep <= 0.) return;

  // G4cout << "edep= " << edep << "NIEL= " << aStep->GetNonIonizingEnergyDeposit()<<G4endl;

  runAction->FillEdep(edep,aStep->GetNonIonizingEnergyDeposit());

  G4StepPoint* prePoint  = aStep->GetPreStepPoint();
  G4StepPoint* postPoint = aStep->GetPostStepPoint();

  if(aStep->GetTrack()->GetTrackID() == 1) {
     runAction->AddPrimaryStep();  

     G4VPhysicalVolume* preVolume = prePoint -> GetPhysicalVolume();
     G4VPhysicalVolume* postVolume = postPoint -> GetPhysicalVolume();

     if( preVolume != postVolume ) {

       G4VPhysicalVolume* detVolume = detector -> GetAbsorPhysVol();

       if( detVolume == postVolume )
	 runAction->FillEnIncoming( prePoint -> GetKineticEnergy() );
       if( detVolume == preVolume )
	 runAction->FillEnOutgoing( postPoint -> GetKineticEnergy() );
     }
  }

  //Bragg curve
  //	
  G4double x1 = prePoint->GetPosition().x(), x2 = postPoint->GetPosition().x();  
  G4double x = runAction->GetOffsetX() + x1 + G4UniformRand()*(x2-x1);
  runAction->FillHisto(0, x/mm , edep);
  runAction->FillHisto(1, x/mm , edep);

  //fill tallies
  //
  G4TouchableHandle touchable = prePoint->GetTouchableHandle();
  G4LogicalVolume* lVolume = touchable->GetVolume()->GetLogicalVolume();
  if (lVolume == detector->GetLogicalTally())
    runAction->FillTallyEdep(touchable->GetCopyNumber(), edep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


