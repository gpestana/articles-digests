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
// $Id: SCSteppingAction.cc 66356 2012-12-18 09:02:32Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SCSteppingAction.hh"
#include "G4SteppingManager.hh"

#include "SCSurfacePoint.hh" 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SCSteppingAction::SCSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SCSteppingAction::UserSteppingAction(const G4Step* aStep)
{ 

  G4Track* aTrack = aStep->GetTrack();

  G4StepPoint*  PreStepPoint= aStep->GetPreStepPoint(); 
  G4StepPoint*  PostStepPoint= aStep->GetPostStepPoint(); 
  G4ThreeVector PostHitPoint = PostStepPoint->GetPosition();
  G4ThreeVector PreHitPoint = PreStepPoint->GetPosition();

  G4cout.precision(16) ;

  G4ThreeVector VertexPosition = aTrack->GetVertexPosition();
  G4ThreeVector m = (PostHitPoint - PreHitPoint).unit() ;

  G4ThreeVector truepoint = spoint.GetSurfacePoint() ;
  G4double delta = (truepoint - PostHitPoint).mag() ;

  G4cout << "Intersection "  
	 << PostHitPoint << " "  
	 << delta  <<  G4endl ;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

