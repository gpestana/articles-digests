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
// $Id: Tst14PositronPenelope.cc 68781 2013-04-05 13:08:56Z gcosmo $
//
// Author: Luciano Pandola (pandola@lngs.infn.it)
//
// History:
// -----------
// 15 Dec 2008 Luciano Pandola     Created
//
// -------------------------------------------------------------------

#include "Tst14PositronPenelope.hh"

#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"
#include "G4eMultipleScattering.hh"
#include "G4GoudsmitSaundersonMscModel.hh"
#include "G4eIonisation.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4eBremsstrahlung.hh"
#include "G4PenelopeBremsstrahlungModel.hh"
#include "G4eplusAnnihilation.hh"
#include "G4PenelopeAnnihilationModel.hh"
#include "G4UniversalFluctuation.hh"

Tst14PositronPenelope::Tst14PositronPenelope(const G4String& name): G4VPhysicsConstructor(name)
{ }

Tst14PositronPenelope::~Tst14PositronPenelope()
{ }

void Tst14PositronPenelope::ConstructProcess()
{
  // Add processes a' la Penelope for electrons
  
  aParticleIterator->reset();

  while( (*aParticleIterator)() )
    {
      G4ParticleDefinition* particle = aParticleIterator->value();
      G4ProcessManager* manager = particle->GetProcessManager();
      G4String particleName = particle->GetParticleName();
     
      G4double PenelopeHighEnergyLimit = 1.0*GeV;

      if (particleName == "e+") 
	{
	  G4eMultipleScattering* msc = new G4eMultipleScattering();
	  //msc->AddEmModel(0, new G4UrbanMscModel93());
	  msc->AddEmModel(0, new G4GoudsmitSaundersonMscModel());
	  msc->SetStepLimitType(fUseDistanceToBoundary);
	  manager->AddProcess(msc,                   -1, 1, 1);
	  
	  //Ionisation
	  G4eIonisation* eIoni = new G4eIonisation();
	  G4PenelopeIonisationModel* theIoniPenelope = 
	    new G4PenelopeIonisationModel();
	  theIoniPenelope->SetHighEnergyLimit(PenelopeHighEnergyLimit);
	  eIoni->AddEmModel(0,theIoniPenelope,new G4UniversalFluctuation());
	  eIoni->SetStepFunction(0.2, 100*um); //     
	  manager->AddProcess(eIoni,                 -1, 2, 2);
	  
	  //Bremsstrahlung
	  G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
	  G4PenelopeBremsstrahlungModel* theBremPenelope = new 
	    G4PenelopeBremsstrahlungModel();
	  theBremPenelope->SetHighEnergyLimit(PenelopeHighEnergyLimit);
	  eBrem->AddEmModel(0,theBremPenelope);
	  manager->AddProcess(eBrem, -1,-3, 3);
	  
	  //Annihilation
	  G4eplusAnnihilation* eAnni = new G4eplusAnnihilation();
	  G4PenelopeAnnihilationModel* theAnnPenelope = new 
	    G4PenelopeAnnihilationModel();
	  theAnnPenelope->SetHighEnergyLimit(PenelopeHighEnergyLimit);
	  eAnni->AddEmModel(0,theAnnPenelope);
	  manager->AddProcess(eAnni,0,-1, 4);	  
	}   
    }
}
