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
// test58.cc
// 
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"
#include "SteppingVerbose.hh"
#include "StackingAction.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv) {

  //choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

  //my Verbose output class
  G4VSteppingVerbose::SetInstance(new SteppingVerbose);

  // Construct the default run manager
  G4RunManager * runManager = new G4RunManager;

  // set mandatory initialization classes
  DetectorConstruction* detector = new DetectorConstruction;
  PhysicsList* physics = new PhysicsList;  



  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(physics);
   
  PrimaryGeneratorAction* primary = new PrimaryGeneratorAction(detector);
  runManager->SetUserAction(primary);


  // set user action classes
  //
  //runAction
  RunAction* runaction = new RunAction(detector,physics,primary);
  runManager->SetUserAction(runaction);

  //eventAction
  EventAction* eventaction = new EventAction(runaction);
  runManager->SetUserAction(eventaction);

//trackAction
  TrackingAction* trackingaction = new TrackingAction(eventaction);
  runManager->SetUserAction(trackingaction);


  //stepAction
  SteppingAction* steppingaction = new SteppingAction(detector,
                                                      eventaction);
  runManager->SetUserAction(steppingaction);
  
  //stackAction
  StackingAction* stackingaction = new StackingAction(runaction, 
                                                      eventaction, detector);
  runManager->SetUserAction(stackingaction);      
   
  // get the pointer to the User Interface manager 
    G4UImanager* UI = G4UImanager::GetUIpointer();  
 
  if (argc!=1)   // batch mode  
    {
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UI->ApplyCommand(command+fileName);
    }
    
  else           //define visualization and UI terminal for interactive mode
    { 
#ifdef G4VIS_USE
   G4VisManager* visManager = new G4VisExecutive;
   visManager->Initialize();
#endif    
     
     G4UIsession * session = 0;
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);      
#else
      session = new G4UIterminal();
#endif     
     session->SessionStart();
     delete session;
     
#ifdef G4VIS_USE
     delete visManager;
#endif     
    }
    
  // job termination
  //  
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

