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
// $Id: Tst11DetectorMessenger.cc 69145 2013-04-19 10:28:11Z gcosmo $
//

#include "Tst11DetectorMessenger.hh"

#include "Tst11DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "globals.hh"

#include "G4ios.hh"

Tst11DetectorMessenger::Tst11DetectorMessenger(Tst11DetectorConstruction * myDC)
:myDetector(myDC)
{
  G4String defParam;

  mydetDir = new G4UIdirectory("/mydet/");
  mydetDir->SetGuidance("Detector setup commands.");

  selMatCmd = new G4UIcmdWithAString("/mydet/SelectMaterial",this);
  selMatCmd->SetGuidance("Select Material of the SimpleBox.");
  selMatCmd->SetGuidance("  Choice : Air, Al, Pb, U (default)");
  selMatCmd->SetParameterName("choice",true);
  selMatCmd->SetDefaultValue("Pb");
//  selMatCmd->SetCandidates("Air Al Pb U");
  selMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  myDetector->SelectMaterial(defParam="Pb");
}

Tst11DetectorMessenger::~Tst11DetectorMessenger()
{
  delete selMatCmd;
  delete mydetDir;
}

void Tst11DetectorMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if( command == selMatCmd )
  {
    myDetector->SelectMaterial(newValues);
  }
  return;
}

