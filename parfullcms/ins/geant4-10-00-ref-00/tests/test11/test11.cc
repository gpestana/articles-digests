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
// $Id: test11.cc 76252 2013-11-08 11:25:21Z gcosmo $
//

#include "Tst11DetectorConstruction.hh"
#include "Tst11ActionInitialization.hh"
#include "Tst11PhysicsList.hh"
// #include "Tst11SteppingAction.hh"

#include "G4UImanager.hh"
#include "G4UIterminal.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4ios.hh"
#include <stdlib.h>

int main(int argc,char** argv) {

  // Set the default random engine to RanecuEngine
  CLHEP::RanecuEngine defaultEngine;
  G4Random::setTheEngine(&defaultEngine);


  // Run manager
  #ifdef G4MULTITHREADED
    G4cout<<"Warning: forcing G4FORCENUMBEROFTHREADS=4"<<G4endl;
    char env[]="G4FORCENUMBEROFTHREADS=4";
    putenv(env);
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(4);
  #else
    G4RunManager* runManager = new G4RunManager;
  #endif

  // UserInitialization classes
  runManager->SetUserInitialization(new Tst11DetectorConstruction);
  runManager->SetUserInitialization(new Tst11PhysicsList);
  runManager->SetUserInitialization(new Tst11ActionInitialization);

  //Activate prodcuton of fission fragments in neutronHP
  char env_ff[]="G4NEUTRONHP_PRODUCE_FISSION_FRAGMENTS=1";
  putenv(env_ff);

  if(argc==1)
  {
    // G4UIterminal is a (dumb) terminal.
    G4UIsession* session = new G4UIterminal;
    session->SessionStart();
    delete session;
  }
  else
  {
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  G4Random::showEngineStatus();
  delete runManager;
  return 0;
}
