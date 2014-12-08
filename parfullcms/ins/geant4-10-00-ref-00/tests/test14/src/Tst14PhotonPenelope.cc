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
// $Id: Tst14PhotonPenelope.cc 68781 2013-04-05 13:08:56Z gcosmo $
//
// Author: Maria.Grazia.Pia@cern.ch
//
// History:
// -----------
// 22 Feb 2003 MGP          Designed for modular Physics List
//
// -------------------------------------------------------------------

#include "Tst14PhotonPenelope.hh"

#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4PenelopePhotoElectricModel.hh"
#include "G4ComptonScattering.hh"
#include "G4PenelopeComptonModel.hh"
#include "G4GammaConversion.hh"
#include "G4PenelopeGammaConversionModel.hh"
#include "G4RayleighScattering.hh"
#include "G4PenelopeRayleighModel.hh"


Tst14PhotonPenelope::Tst14PhotonPenelope(const G4String& name): G4VPhysicsConstructor(name)
{;}

Tst14PhotonPenelope::~Tst14PhotonPenelope()
{;}

void Tst14PhotonPenelope::ConstructProcess()
{
  // Add processes a' la Penelope for photons
  
  aParticleIterator->reset();

  while( (*aParticleIterator)() )
    {
      G4ParticleDefinition* particle = aParticleIterator->value();
      G4ProcessManager* manager = particle->GetProcessManager();
      G4String particleName = particle->GetParticleName();

      G4double PenelopeHighEnergyLimit = 1.0*GeV;
     
      if (particleName == "gamma") 
	{
	  //Photo-electric effect
	  G4PhotoElectricEffect* thePhotoElectricEffect = new G4PhotoElectricEffect();
	  G4PenelopePhotoElectricModel* thePEPenelopeModel = new 
	    G4PenelopePhotoElectricModel();
	  thePEPenelopeModel->SetHighEnergyLimit(PenelopeHighEnergyLimit);
	  thePhotoElectricEffect->AddEmModel(0,thePEPenelopeModel);
	  manager->AddDiscreteProcess(thePhotoElectricEffect);

	  //Compton scattering
	  G4ComptonScattering* theComptonScattering = new G4ComptonScattering();
	  G4PenelopeComptonModel* theComptonPenelopeModel = 
	    new G4PenelopeComptonModel();
	  theComptonPenelopeModel->SetHighEnergyLimit(PenelopeHighEnergyLimit);
	  theComptonScattering->AddEmModel(0,theComptonPenelopeModel);
	  manager->AddDiscreteProcess(theComptonScattering);
	  
	  //Gamma conversion
	  G4GammaConversion* theGammaConversion = new G4GammaConversion();
	  G4PenelopeGammaConversionModel* theGCPenelopeModel = 
	    new G4PenelopeGammaConversionModel();
	  theGammaConversion->AddEmModel(0,theGCPenelopeModel);
	  manager->AddDiscreteProcess(theGammaConversion);
	  
	  //Rayleigh scattering
	  G4RayleighScattering* theRayleigh = new G4RayleighScattering();
	  G4PenelopeRayleighModel* theRayleighPenelopeModel = 
	    new G4PenelopeRayleighModel();
	  theRayleighPenelopeModel->SetHighEnergyLimit(PenelopeHighEnergyLimit);
	  theRayleigh->AddEmModel(0,theRayleighPenelopeModel);
	  manager->AddDiscreteProcess(theRayleigh);	  
	}   
    }
}
