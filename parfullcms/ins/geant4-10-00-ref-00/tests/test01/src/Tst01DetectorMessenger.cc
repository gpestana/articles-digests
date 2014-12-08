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

#include "Tst01DetectorMessenger.hh"

#include "Tst01DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "globals.hh"

#include "G4ios.hh"

Tst01DetectorMessenger::Tst01DetectorMessenger(Tst01DetectorConstruction * myDC)
:myDetector(myDC)
{
  G4String defParam;

  mydetDir = new G4UIdirectory("/mydet/");
  mydetDir->SetGuidance("Detector setup commands.");

  selDetCmd = new G4UIcmdWithAString("/mydet/SelectDetector",this);
  selDetCmd->SetGuidance("Select Detector Setup.");
  selDetCmd->SetGuidance("  Choice : SimpleBox / Honeycomb / Assembly / Assembly2 / Assembly3");
  selDetCmd->SetParameterName("choice",true);
  selDetCmd->SetDefaultValue("SimpleBox");
  selDetCmd->SetCandidates("SimpleBox Honeycomb Assembly Assembly2 Assembly3");
  selDetCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  switchCmd = new G4UIcmdWithAString("/mydet/SwitchDetector",this);
  switchCmd->SetGuidance("Assign the selected geometry to G4RunManager.");
  switchCmd->SetGuidance("In cese detector name is associated to this command,");
  switchCmd->
  SetGuidance("\"/mydet/SelectDetector\" will be invoked and then switched.");
  switchCmd->SetParameterName("choice",true);
  switchCmd->SetDefaultValue(" ");
  switchCmd->SetCandidates("SimpleBox Honeycomb Assembly Assembly2 Assembly3 \" \"");
  switchCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  selMatCmd = new G4UIcmdWithAString("/mydet/SelectMaterial",this);
  selMatCmd->SetGuidance("Select Material of the SimpleBox.");
  selMatCmd->SetGuidance("  Choice : Air, Al, Pb (default)");
  selMatCmd->SetParameterName("choice",true);
  selMatCmd->SetDefaultValue("Pb");
  selMatCmd->SetCandidates("Air Al Pb");
  selMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // Select/Switch SCG inside Detector

  selCSGcmd = new G4UIcmdWithAString("/mydet/SelectCSG",this);
  selCSGcmd->SetGuidance("Select Detector CSG");
  selCSGcmd->SetGuidance("  Choice : Box Tubs Cons Sphere");
  selCSGcmd->SetParameterName("choice",true);
  selCSGcmd->SetDefaultValue("Box");
  selCSGcmd->SetCandidates("Box Tubs Cons Sphere");
  selCSGcmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  switchCSGcmd = new G4UIcmdWithAString("/mydet/SwitchCSG",this);
  switchCSGcmd->SetGuidance("Assign the selected CSG geometry to G4RunManager.");

  switchCSGcmd->
  SetGuidance("In cese detector name is associated to this command,");

  switchCSGcmd->
  SetGuidance("\"/mydet/SelectCSG\" will be invoked and then switched.");

  switchCSGcmd->SetParameterName("choice",true);
  switchCSGcmd->SetDefaultValue(" ");
  switchCSGcmd->SetCandidates("Box Tubs Cons Sphere \" \"");
  switchCSGcmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // Select/Switch Boolean inside Detector

  selBoolCmd = new G4UIcmdWithAString("/mydet/SelectBool",this);
  selBoolCmd->SetGuidance("Select Detector Boolean");
  selBoolCmd->SetGuidance("  Choice : Intersection Union Subtraction");
  selBoolCmd->SetParameterName("choice",true);
  selBoolCmd->SetDefaultValue("Intersection");
  selBoolCmd->SetCandidates("Intersection Union Subtraction");
  selBoolCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  switchBoolCmd = new G4UIcmdWithAString("/mydet/SwitchBool",this);
  switchBoolCmd->
  SetGuidance("Assign the selected Boolean geometry to G4RunManager.");

  switchBoolCmd->
  SetGuidance("In cese detector name is associated to this command,");

  switchBoolCmd->
  SetGuidance("\"/mydet/SelectBool\" will be invoked and then switched.");

  switchBoolCmd->SetParameterName("choice",true);
  switchBoolCmd->SetDefaultValue(" ");
  switchBoolCmd->SetCandidates("Intersection Union Subtraction \" \"");
  switchBoolCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // Default selections

  myDetector->SelectDetector(defParam="SimpleBox");
  myDetector->SelectMaterial(defParam="Pb");

  myDetector->SelectCSG(defParam="Box");
  myDetector->SelectBoolean(defParam="Intersection");
}

//////////////////////////////////////////////////////////////////////////
//
//

void Tst01DetectorMessenger::SetNewValue( G4UIcommand* command ,
                                          G4String newValues        )
{
  if( command == selDetCmd )
  {
    myDetector->SelectDetector(newValues);
  }
  if( command == switchCmd )
  {
    if(newValues=="SimpleBox" || newValues=="Honeycomb" || 
       newValues=="Assembly" || newValues=="Assembly2" ||
       newValues=="Assembly3" )
    { 
      myDetector->SelectDetector(newValues); 
    }
    myDetector->SwitchDetector();
  }
  if( command == selMatCmd )
  {
    myDetector->SelectMaterial(newValues);
  }

  // Select/Switch CSG

  if( command == selCSGcmd )
  {
    myDetector->SelectCSG(newValues);
  }
  if( command == switchCSGcmd )
  {
    if( newValues=="Box"  || newValues=="Tubs" ||
        newValues=="Cons" || newValues=="Sphere"    )
    { 
      myDetector->SelectCSG(newValues); 
    }
    myDetector->SwitchCSG();
  }

  // Select/Switch Boolean

  if( command == selBoolCmd )
  {
    myDetector->SelectBoolean(newValues);
  }
  if( command == switchBoolCmd )
  {
    if( newValues=="Intersection"  || newValues=="Union"   ||
        newValues=="Subtraction"                                 )
    { 
      myDetector->SelectBoolean(newValues); 
    }
    myDetector->SwitchBoolean();
  }


  return;
}

