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
// $Id: EventAction.cc 66512 2012-12-19 10:26:52Z gcosmo $
//
/////////////////////////////////////////////////////////////////////////
//
// EventAction
//
// Created: 31.04.2006 V.Ivanchenko
//
// Modified:
//
////////////////////////////////////////////////////////////////////////
// 

#include "EventAction.hh"
#include "G4Event.hh"
#include "HistoManager.hh"
#include "EventActionMessenger.hh"

#include "G4UImanager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

EventAction::EventAction():
  printModulo(100),
  nSelected(0),
  drawFlag("all"),
  debugStarted(false)
{
  eventMessenger = new EventActionMessenger(this);
  UI = G4UImanager::GetUIpointer();
  selectedEvents.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

EventAction::~EventAction()
{
  delete eventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void EventAction::BeginOfEventAction(const G4Event* evt)
{
  // New event
  G4int nEvt = evt->GetEventID();

  if(nSelected>0) {
    for(G4int i=0; i<nSelected; i++) {
      if(nEvt == selectedEvents[i]) {
        UI->ApplyCommand("/random/saveThisEvent");
        UI->ApplyCommand("/tracking/verbose  2");
        debugStarted = true;
        break;
      }
    }
  }

  // Initialize user actions
  HistoManager* man = HistoManager::GetPointer();
  man->BeginOfEvent(); 
  if(man->GetVerbose() > 0 || G4int(nEvt/printModulo)*printModulo == nEvt) {
    G4cout << "EventAction: Event # "
           << nEvt << " started" << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void EventAction::EndOfEventAction(const G4Event* evt)
{
  if(debugStarted) {
    UI->ApplyCommand("/tracking/verbose  0");
    debugStarted = false;
  }

  HistoManager* man = HistoManager::GetPointer();
  man->EndOfEvent(); 
  if(man->GetVerbose() > 1) {
    G4cout << "EventAction: Event #" << evt->GetEventID()
	   << " ended" << G4endl;
  }

  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

  if(pVVisManager) {
    G4TrajectoryContainer* trjc = evt->GetTrajectoryContainer();
    G4int n_trajectories = 0;
    if (trjc) n_trajectories = trjc->entries();  

    for(G4int i=0; i<n_trajectories; i++) {
      G4Trajectory* t = (G4Trajectory*)((*(evt->GetTrajectoryContainer()))[i]);
      if (drawFlag == "all") t->DrawTrajectory();
      else if ((drawFlag == "charged")&&(t->GetCharge() != 0.))
                             t->DrawTrajectory();
    }
  }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
