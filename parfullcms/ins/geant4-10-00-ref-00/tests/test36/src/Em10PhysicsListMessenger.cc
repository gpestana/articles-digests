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
// $Id: Em10PhysicsListMessenger.cc 68061 2013-03-13 14:51:28Z gcosmo $
//
// 
//
///////////////////////////////////////////////////////////////////////



#include "Em10PhysicsListMessenger.hh"

#include "Em10PhysicsList.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"


//////////////////////////////////////////////////////////////////////////////
//
//

Em10PhysicsListMessenger::Em10PhysicsListMessenger(Em10PhysicsList* List)
:Em10List(List)
{
  cutGCmd = new G4UIcmdWithADoubleAndUnit("/calor/cutG",this);
  cutGCmd->SetGuidance("Set cut values by RANGE for Gamma.");
  cutGCmd->SetParameterName("range",true);
  cutGCmd->SetDefaultValue(1.);
  cutGCmd->SetDefaultUnit("mm");
  cutGCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  cutECmd = new G4UIcmdWithADoubleAndUnit("/calor/cutE",this);
  cutECmd->SetGuidance("Set cut values by RANGE for e- e+.");
  cutECmd->SetParameterName("range",true);
  cutECmd->SetDefaultValue(1.);
  cutECmd->SetDefaultUnit("mm");
  cutECmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  eMinEnergyCmd = new G4UIcmdWithADoubleAndUnit("/emphyslist/eMinEnergy",this);
  eMinEnergyCmd->SetGuidance("Set cut values by energy in Photo-Comp for e-");
  eMinEnergyCmd->SetParameterName("range",true);
  eMinEnergyCmd->SetDefaultValue(1.);
  eMinEnergyCmd->SetDefaultUnit("keV");
  eMinEnergyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  gMinEnergyCmd = new G4UIcmdWithADoubleAndUnit("/emphyslist/gMinEnergy",this);
  gMinEnergyCmd->SetGuidance("Set cut values by energy in Compton for gamma");
  gMinEnergyCmd->SetParameterName("range",true);
  gMinEnergyCmd->SetDefaultValue(1.);
  gMinEnergyCmd->SetDefaultUnit("keV");
  gMinEnergyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  setMaxStepCmd = new G4UIcmdWithADoubleAndUnit("/step/setMaxStep",this);
  setMaxStepCmd->SetGuidance("Set max. step length in the detector");
  setMaxStepCmd->SetParameterName("mxStep",true);
  setMaxStepCmd->SetDefaultUnit("mm");


  ElectronCutCmd = new G4UIcmdWithADoubleAndUnit("/emphyslist/setElectronCut",this);
  ElectronCutCmd->SetGuidance("Set electron cut in mm for vertex region");
  ElectronCutCmd->SetParameterName("ElectronCut",false,false);
  ElectronCutCmd->SetDefaultUnit("mm");
  ElectronCutCmd->SetRange("ElectronCut>0.");
  ElectronCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  PositronCutCmd = new G4UIcmdWithADoubleAndUnit("/emphyslist/setPositronCut",this);
  PositronCutCmd->SetGuidance("Set positron cut in mm for vertex region");
  PositronCutCmd->SetParameterName("PositronCut",false,false);
  PositronCutCmd->SetDefaultUnit("mm");
  PositronCutCmd->SetRange("PositronCut>0.");
  PositronCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  GammaCutCmd = new G4UIcmdWithADoubleAndUnit("/emphyslist/setGammaCut",this);
  GammaCutCmd->SetGuidance("Set gamma cut in mm for vertex region");
  GammaCutCmd->SetParameterName("GammaCut",false,false);
  GammaCutCmd->SetDefaultUnit("mm");
  GammaCutCmd->SetRange("GammaCut>0.");
  GammaCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  RadiatorCutCmd = new G4UIcmdWithADoubleAndUnit("/emphyslist/setRadiatorCuts",this);
  RadiatorCutCmd->SetGuidance("Set radiator cut in mm for vertex region");
  RadiatorCutCmd->SetParameterName("RadiatorCuts",false,false);
  RadiatorCutCmd->SetDefaultUnit("mm");
  RadiatorCutCmd->SetRange("RadiatorCuts > 0.");
  RadiatorCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  DetectorCutCmd = new G4UIcmdWithADoubleAndUnit("/emphyslist/setDetectorCuts",this);
  DetectorCutCmd->SetGuidance("Set radiator cut in mm for vertex region");
  DetectorCutCmd->SetParameterName("DetectorCuts",false,false);
  DetectorCutCmd->SetDefaultUnit("mm");
  DetectorCutCmd->SetRange("DetectorCuts > 0.");
  DetectorCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  XTRModelCmd = new G4UIcmdWithAString("/emphyslist/setXTRModel",this);
  XTRModelCmd->SetGuidance("Set XTR model");
  XTRModelCmd->SetParameterName("XTRModel",false);
  XTRModelCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

/////////////////////////////////////////////////////////////////////////////

Em10PhysicsListMessenger::~Em10PhysicsListMessenger()
{
  delete cutGCmd;
  delete cutECmd;

  delete eMinEnergyCmd;
  delete gMinEnergyCmd;

  delete setMaxStepCmd;

  delete ElectronCutCmd;
  delete PositronCutCmd;
  delete GammaCutCmd;
  delete XTRModelCmd;
}

////////////////////////////////////////////////////////////////////////////////

void Em10PhysicsListMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if(command == cutGCmd)
    { Em10List->SetGammaCut(cutGCmd->GetNewDoubleValue(newValue));}
  if(command == cutECmd)
    { Em10List->SetElectronCut(eCmd->GetNewDoubleValue(newValue));}
  if(command == setMaxStepCmd)
    { Em10List->SetMaxStep(setMaxStepCmd->GetNewDoubleValue(newValue));}
  if(command == eMinEnergyCmd)
    { Em10List->SetMinElectronEnergy(eMinEnergyCmd->GetNewDoubleValue(newValue));}
  if(command == gMinEnergyCmd)
    { Em10List->SetMinGammaEnergy(gMinEnergyCmd->GetNewDoubleValue(newValue));}

  if( command == ElectronCutCmd )
  {
    Em10List->SetRegElectronCut(ElectronCutCmd->GetNewDoubleValue(newValue));
  }
  if( command == PositronCutCmd )
  {
    Em10List->SetRegPositronCut(PositronCutCmd->GetNewDoubleValue(newValue));
  }
  if( command == GammaCutCmd )
  {
    Em10List->SetRegGammaCut(GammaCutCmd->GetNewDoubleValue(newValue));
  }
  if( command == RadiatorCutCmd )
  {
    Em10List->SetRadiatorCuts();
  }
  if( command == DetectorCutCmd )
  {
    Em10List->SetDetectorCuts();
  }
  if( command == XTRModelCmd )
  { 
    Em10List->SetXTRModel(newValue);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
