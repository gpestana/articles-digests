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
// $Id: MyExEventAction.cc 66356 2012-12-18 09:02:32Z gcosmo $
//
//
                                                                                           
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
                                                                                           
#include "ExN01EventAction.hh"
                                                                                           
#include "ExN01RunAction.hh"
                                          
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VTrajectory.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"
                                                                                           
//#include "Randomize.hh"
//#include <iomanip>
                                                                                           
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
                                                                                           
ExN01EventAction::ExN01EventAction(ExN01RunAction* run)
:runAct(run)
{

}
                                                                                           
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ExN01EventAction::~ExN01EventAction()
 {
;
}
                                                                                           
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
                                                                                           
void ExN01EventAction::BeginOfEventAction(const G4Event* evt)
{
  //G4int evtNb = evt->GetEventID();
                                           
}
                                                                                           
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
                                                                                           
void ExN01EventAction::EndOfEventAction(const G4Event* evt)
{
  //accumulates statistic
  //
 
                                                                                           
  //print per event (modulo n)
  //
  //G4int evtNb = evt->GetEventID();

                                                                                           
  }
                                                                                           
 
                                                                                                          
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
                                                                                     
