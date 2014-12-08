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
// $Id: test14.cc 68781 2013-04-05 13:08:56Z gcosmo $
//

#include "Tst14DetectorConstruction.hh"
#include "Tst14RunAction.hh"
#include "Tst14PrimaryGeneratorAction.hh"
#include "Tst14PhysicsList.hh"
#include "Tst14SteppingAction.hh"
#include "Tst14TrackingAction.hh"

#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4RunManager.hh"

#include "G4ios.hh"

int main(int argc,char** argv) {

  // Set the default random engine to RanecuEngine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

  // Run manager
  G4RunManager * runManager = new G4RunManager;

  // UserInitialization classes
  Tst14DetectorConstruction* detector;
  detector = new Tst14DetectorConstruction;

  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new Tst14PhysicsList);

  // UserAction classes
  runManager->SetUserAction(new Tst14PrimaryGeneratorAction(detector));
  Tst14RunAction* runaction = new Tst14RunAction;
  runManager->SetUserAction(runaction);

  runManager->SetUserAction(new Tst14SteppingAction);
  //runManager->SetUserAction(new Tst14TrackingAction);

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if(argc==1)
  {
    // G4UIterminal is a (dumb) terminal.
    //   G4UIsession* session = new G4UIterminal;
    //   UImanager->ApplyCommand("/control/execute prerunTst14.mac");
    G4UIsession * session = 0;
    session = new G4UIterminal();
    session->SessionStart();
    delete session;
  }
  else
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  delete runManager;
  return 0;
}
