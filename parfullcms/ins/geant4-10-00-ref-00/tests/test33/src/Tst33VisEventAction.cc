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
// $Id: Tst33VisEventAction.cc 66358 2012-12-18 09:07:19Z gcosmo $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "Tst33VisEventAction.hh"

#include "Tst33VisEventActionMessenger.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4Polyline.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Tst33VisEventAction::Tst33VisEventAction()
:drawFlag("all"),printModulo(1),
 eventMessenger(0)
{
  eventMessenger = new Tst33VisEventActionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Tst33VisEventAction::~Tst33VisEventAction()
{
  delete eventMessenger;
}

void Tst33VisEventAction::Clear() {
  
}


//Alex 17/12/12 Temporary commit until I can figure it out:
// void Tst33VisEventAction::SpecialCellScorer(const G4CellScorer *){
//   G4cout << "Tst33VisEventAction::SpecialCellScorer: no action taken!" << G4endl;
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Tst33VisEventAction::BeginOfEventAction(const G4Event* )
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Tst33VisEventAction::EndOfEventAction(const G4Event* evt)
{
  
  if (G4VVisManager::GetConcreteInstance()) {
    G4TrajectoryContainer* trajectoryContainer=0;
    trajectoryContainer = evt->GetTrajectoryContainer();
    G4int n_trajectories = 0;
    if (trajectoryContainer) {
      n_trajectories = trajectoryContainer->entries();
    }

    for (G4int i=0; i<n_trajectories; i++)  { 
      G4Trajectory* trj = 0;
      trj = dynamic_cast<G4Trajectory*>((*trajectoryContainer)[i]);
      if (trj) {
	G4bool charged=false;
	charged = std::fabs(trj->GetCharge()) > 0;
	if (drawFlag == "all") {
	  DrawTrajectory(*trj);
	}
	else if ((drawFlag == "charged")&&(charged)) {
	  DrawTrajectory(*trj);
	}
	else if ((drawFlag == "neutral")&&(!charged)) {
	  DrawTrajectory(*trj);
	}
      }
      else {
	G4cerr << " Tst33VisEventAction::EndOfEventAction: failed to dynamic cast to G4Trajectory!" << G4endl;
      }
    }
  }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


///////////////////////////////////////////////
void Tst33VisEventAction::DrawTrajectory(G4Trajectory &trj) const
///////////////////////////////////////////////
{

   G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
   G4ThreeVector pos;

   G4ParticleDefinition* pdf = trj.GetParticleDefinition();
   G4String ParticleName(pdf->GetParticleName());
   G4double PDGCharge=pdf->GetPDGCharge();


   G4Polyline pPolyline;
   for (int i = 0; i < trj.GetPointEntries() ; i++) {
     G4VTrajectoryPoint* trjPoint = trj.GetPoint(i);
       pos = trjPoint->GetPosition();
     pPolyline.push_back( pos );
   }
   
   G4Colour colour;
   if (ParticleName == "proton") {
     colour = G4Colour(1,0,1); // magenta
     }
   else if (ParticleName == "neutron") {
     colour = G4Colour(0,1,1); // cyan
   }
   else if (ParticleName == "gamma") {
     colour = G4Colour(1,1,0); // yellow
   }
   else {
     if(PDGCharge<0.) 
       colour = G4Colour(1.,0.,0.); // red
     else if(PDGCharge>0.) 
       colour = G4Colour(0.,0.,1.); // blue
     else 
       colour = G4Colour(0.,1.,0.); // green
   }
   G4VisAttributes attribs(colour);
   pPolyline.SetVisAttributes(attribs);
   if(pVVisManager) pVVisManager->Draw(pPolyline);


   /*
   if(i_mode!=0)
   {
     for(size_t j=0; j<positionRecord->size(); j++) {
       G4TrajectoryPoint* aTrajectoryPoint = (G4TrajectoryPoint*)((*positionRecord)[j]);
       pos = aTrajectoryPoint->GetPosition();
       G4Circle circle( pos );
       circle.SetScreenSize(0.001*i_mode);
       circle.SetFillStyle(G4Circle::filled);
       G4Colour colSpot(0.,0.,0.);
       G4VisAttributes attSpot(colSpot);
       circle.SetVisAttributes(attSpot);
       if(pVVisManager) pVVisManager->Draw(circle);
     }
   }
   */
}
