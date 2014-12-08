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
// $Id: SteppingAction.cc 72968 2013-08-14 14:59:05Z gcosmo $
// -------------------------------------------------------------------

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "SteppingAction.hh"
#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4SteppingManager.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Electron.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

SteppingAction::SteppingAction(PrimaryGeneratorAction* p)
{
    Edeposit = 0;
    Primary = p ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
    if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition() == G4Electron::Definition())
    {
        Edeposit += aStep -> GetTotalEnergyDeposit();

        if( aStep -> GetTrack() -> GetTrackID() == 1)
        {
            if(Primary->GetIncidentEnergy() - aStep->GetPostStepPoint()->GetKineticEnergy() > 2.*keV )
            {
                G4cout<<"!!!" <<  aStep -> GetTrack() -> GetDynamicParticle() -> GetDefinition() -> GetParticleName()
                     <<" finished tracking track 1 "<<G4endl;
                G4cout<<"!!! Penetration : "
                     << G4BestUnit((aStep->GetTrack() ->GetPosition() - aStep->GetTrack()->GetVertexPosition()).mag(),"Length")
                     <<G4endl;
                aStep-> GetTrack() -> SetTrackStatus(fStopAndKill);
            }
        }
    }
}
