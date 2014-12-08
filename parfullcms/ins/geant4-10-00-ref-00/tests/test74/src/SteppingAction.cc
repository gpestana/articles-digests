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
// -------------------------------------------------------------------
// $Id: SteppingAction.cc 74992 2013-10-25 10:44:55Z gcosmo $
// -------------------------------------------------------------------

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "SteppingAction.hh"
#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4SteppingManager.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

SteppingAction::SteppingAction(RunAction* run) 
{
  	Run= run;
	Detector = (DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
	Primary = (PrimaryGeneratorAction*) G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void SteppingAction::UserSteppingAction(const G4Step* stp)
{
  G4StepPoint* endPoint = stp->GetPostStepPoint();
  G4String procName = endPoint->GetProcessDefinedStep()->GetProcessName();
  Run->CountProcesses(procName);

  G4double edep = stp->GetTotalEnergyDeposit();
  Run->SumeTransf(edep);

  G4Track* track = stp->GetTrack();
  G4double kinEnergy = track->GetKineticEnergy();

  G4ParticleDefinition* particle = track->GetDefinition();
  G4String particleName = particle->GetParticleName(); 
  G4double Mion_c2 = particle->GetPDGMass();
  G4double ekin = kinEnergy*proton_mass_c2/Mion_c2 ;

  if(particleName!="e-" && ekin/keV < 50)
  {
    track->SetTrackStatus(fStopAndKill);
    Run->SumeTransf(kinEnergy);
  }
}    
