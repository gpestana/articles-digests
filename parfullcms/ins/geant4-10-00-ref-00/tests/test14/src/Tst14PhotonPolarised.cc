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
// $Id: Tst14PhotonPolarised.cc 68781 2013-04-05 13:08:56Z gcosmo $
//
// Author: Maria.Grazia.Pia@cern.ch
//
// History:
// -----------
// 22 Feb 2003 MGP          Designed for modular Physics List
//
// -------------------------------------------------------------------

#include "Tst14PhotonPolarised.hh"

#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"

#include "G4PhotoElectricEffect.hh"
#include "G4LivermorePolarizedPhotoElectricModel.hh"
#include "G4ComptonScattering.hh"
#include "G4LivermorePolarizedComptonModel.hh"
#include "G4GammaConversion.hh"
#include "G4LivermorePolarizedGammaConversionModel.hh"
#include "G4RayleighScattering.hh"
#include "G4LivermorePolarizedRayleighModel.hh"


Tst14PhotonPolarised::Tst14PhotonPolarised(const G4String& name): G4VPhysicsConstructor(name)
{ }

Tst14PhotonPolarised::~Tst14PhotonPolarised()
{ }

void Tst14PhotonPolarised::ConstructProcess()
{
  // Add polarised processes for photons
  
  aParticleIterator->reset();

  while( (*aParticleIterator)() )
    {
      G4ParticleDefinition* particle = aParticleIterator->value();
      G4ProcessManager* manager = particle->GetProcessManager();
      G4String particleName = particle->GetParticleName();

      G4double LivermoreHighEnergyLimit = GeV;
     
      if (particleName == "gamma") 
	{
	  G4PhotoElectricEffect* thePhotoElectricEffect = new G4PhotoElectricEffect();
	  G4LivermorePolarizedPhotoElectricModel* theLivermorePhotoElectricModel = 
	    new G4LivermorePolarizedPhotoElectricModel();
	  theLivermorePhotoElectricModel->SetHighEnergyLimit(LivermoreHighEnergyLimit);
	  thePhotoElectricEffect->AddEmModel(0, theLivermorePhotoElectricModel);
	  manager->AddDiscreteProcess(thePhotoElectricEffect);

	  G4ComptonScattering* theComptonScattering = new G4ComptonScattering();
	  G4LivermorePolarizedComptonModel* theLivermoreComptonModel = new G4LivermorePolarizedComptonModel();
	  theLivermoreComptonModel->SetHighEnergyLimit(LivermoreHighEnergyLimit);
	  theComptonScattering->AddEmModel(0, theLivermoreComptonModel);
	  manager->AddDiscreteProcess(theComptonScattering);

	  G4GammaConversion* theGammaConversion = new G4GammaConversion();
	  G4LivermorePolarizedGammaConversionModel* theLivermoreGammaConversionModel = 
	    new G4LivermorePolarizedGammaConversionModel();
	  theLivermoreGammaConversionModel->SetHighEnergyLimit(LivermoreHighEnergyLimit);
	  theGammaConversion->AddEmModel(0, theLivermoreGammaConversionModel);
	  manager->AddDiscreteProcess(theGammaConversion);

	  G4RayleighScattering* theRayleigh = new G4RayleighScattering();
	  G4LivermorePolarizedRayleighModel* theRayleighModel = new G4LivermorePolarizedRayleighModel();
	  theRayleighModel->SetHighEnergyLimit(LivermoreHighEnergyLimit);
	  theRayleigh->AddEmModel(0, theRayleighModel);
	  manager->AddDiscreteProcess(theRayleigh);
	}   
    }
}
