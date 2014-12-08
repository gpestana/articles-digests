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
// $Id: PrimaryGeneratorAction.cc 70887 2013-06-07 08:28:50Z gcosmo $
// -------------------------------------------------------------------

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fpParticleGun  = new G4ParticleGun(n_particle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fpParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fPrimaryParticleName = fpParticleGun->GetParticleDefinition()->GetParticleName() ;

  G4double x0,y0,z0,theta,phi,xMom0,yMom0,zMom0;

  x0 = 0;
  y0 = 0;
  z0 = 0*micrometer;
  theta = 0;
  phi = 0;

  xMom0 = std::sin(theta);
  yMom0 = std::sin(phi);
  zMom0 = std::sqrt(1.-xMom0*xMom0-yMom0*yMom0);  

  fpParticleGun->SetParticleMomentumDirection(G4ThreeVector(xMom0,yMom0,zMom0));

  fpParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  
  fpParticleGun->GeneratePrimaryVertex(anEvent);

}
