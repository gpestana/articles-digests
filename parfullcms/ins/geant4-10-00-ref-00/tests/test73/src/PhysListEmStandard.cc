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
// $Id: PhysListEmStandard.cc 73206 2013-08-22 08:25:59Z gcosmo $
//
//---------------------------------------------------------------------------
//
// ClassName:   PhysListEmStandard
//
// Author:      V.Ivanchenko 29.06.2011
//
// Modified:
//
//----------------------------------------------------------------------------
//

#include "PhysListEmStandard.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4LossTableManager.hh"
#include "G4EmProcessOptions.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"
#include "G4CoulombScattering.hh"
#include "G4WentzelVIModel.hh"
#include "G4UrbanMscModel.hh"
#include "G4eCoulombScatteringModel.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4alphaIonisation.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4PionPlus.hh"
#include "G4PionMinus.hh"
#include "G4KaonPlus.hh"
#include "G4KaonMinus.hh"
#include "G4Proton.hh"
#include "G4AntiProton.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4He3.hh"
#include "G4Alpha.hh"
#include "G4GenericIon.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysListEmStandard::PhysListEmStandard(G4int ver, bool apply, bool newForE )
  : G4VPhysicsConstructor("PhysListEmStandard"), verbose(ver), applyCut(apply), newForElectrons(newForE)
{
  G4LossTableManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysListEmStandard::~PhysListEmStandard()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysListEmStandard::ConstructParticle()
{
// gamma
  G4Gamma::Gamma();

// leptons
  G4Electron::Electron();
  G4Positron::Positron();
  G4MuonPlus::MuonPlus();
  G4MuonMinus::MuonMinus();

// mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();

// barions
  G4Proton::Proton();
  G4AntiProton::AntiProton();

// ions
  G4Deuteron::Deuteron();
  G4Triton::Triton();
  G4He3::He3();
  G4Alpha::Alpha();
  G4GenericIon::GenericIonDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysListEmStandard::ConstructProcess()
{

  std::cout << "Physics List " << GetPhysicsName() 
            << ", apply cut " << applyCut
            << ", new for electrons " << newForElectrons
            << std::endl;

  // Add standard EM Processes
  G4double mscEnergyLimit = 1.05*GeV;

  aParticleIterator->reset();
  while( (*aParticleIterator)() ){
    G4ParticleDefinition* particle = aParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    if(verbose > 1)
      G4cout << "### " << GetPhysicsName() << " instantiates for " 
	     << particleName << G4endl;

    if (particleName == "gamma") {

      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      pmanager->AddDiscreteProcess(new G4ComptonScattering);
      pmanager->AddDiscreteProcess(new G4GammaConversion);

    } else if (particleName == "e-") {

      G4eIonisation* eioni = new G4eIonisation();
      eioni->SetStepFunction(0.8, 1.0*mm);
      G4eMultipleScattering* msc = new G4eMultipleScattering;
      msc->SetStepLimitType(fMinimal);
      if (newForElectrons) {
        std::cout << "new model for electrons" << std::endl;
      G4UrbanMscModel* mscModel = new G4UrbanMscModel();
          mscModel->SetSkin(10);//<<<<<<<<<<<<<<<<<<<<<<
      G4WentzelVIModel* wvi = new G4WentzelVIModel();
      mscModel->SetHighEnergyLimit(mscEnergyLimit);
      wvi->SetLowEnergyLimit(mscEnergyLimit);
      msc->AddEmModel(0, mscModel);
      msc->AddEmModel(0, wvi);
      pmanager->AddProcess(msc,                   -1, 1, 1);
      pmanager->AddProcess(eioni,                 -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung, -1,-3, 3);
      G4CoulombScattering* sc = new G4CoulombScattering();
      G4eCoulombScatteringModel* mod = new G4eCoulombScatteringModel();
      mod->SetActivationLowEnergyLimit(mscEnergyLimit);
      sc->AddEmModel(0, mod);
      pmanager->AddDiscreteProcess(sc);
      } else {
        std::cout << "simple model for electrons" << std::endl;
      pmanager->AddProcess(msc,                   -1, 1, 1);
      pmanager->AddProcess(eioni,                 -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung, -1,-3, 3);
      }

    } else if (particleName == "e+") {

      G4eIonisation* eioni = new G4eIonisation();
      eioni->SetStepFunction(0.8, 1.0*mm);
      G4eMultipleScattering* msc = new G4eMultipleScattering;
      msc->SetStepLimitType(fMinimal);
      if (newForElectrons ) {
        std::cout << "new model for positrons" << std::endl;
      G4UrbanMscModel* mscModel = new G4UrbanMscModel();
      G4WentzelVIModel* wvi = new G4WentzelVIModel();
      mscModel->SetHighEnergyLimit(mscEnergyLimit);
      wvi->SetLowEnergyLimit(mscEnergyLimit);
      msc->AddEmModel(0, mscModel);
      msc->AddEmModel(0, wvi);
      pmanager->AddProcess(msc,                     -1, 1, 1);
      pmanager->AddProcess(eioni,                   -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1,-3, 3);
      pmanager->AddProcess(new G4eplusAnnihilation,  0,-1, 4);
      G4CoulombScattering* sc = new G4CoulombScattering();
      G4eCoulombScatteringModel* mod = new G4eCoulombScatteringModel();
      mod->SetActivationLowEnergyLimit(mscEnergyLimit);
      sc->AddEmModel(0, mod);
      pmanager->AddDiscreteProcess(sc);
      }
      else {
        std::cout << "simple model for electrons" << std::endl;
      pmanager->AddProcess(msc,                     -1, 1, 1);
      pmanager->AddProcess(eioni,                   -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1,-3, 3);
      pmanager->AddProcess(new G4eplusAnnihilation,  0,-1, 4);
      }

    } else if (particleName == "mu+" ||
               particleName == "mu-"    ) {

      G4MuMultipleScattering* msc = new G4MuMultipleScattering();
      msc->AddEmModel(0, new G4WentzelVIModel());
      pmanager->AddProcess(msc,                     -1, 1, 1);
      pmanager->AddProcess(new G4MuIonisation,      -1, 2, 2);
      pmanager->AddProcess(new G4MuBremsstrahlung,  -1,-3, 3);
      pmanager->AddProcess(new G4MuPairProduction,  -1,-4, 4);
      pmanager->AddDiscreteProcess(new G4CoulombScattering());

    } else if (particleName == "alpha" ||
               particleName == "He3") {

      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);

    } else if (particleName == "GenericIon") {

      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);

    } else if (particleName == "pi+" ||
               particleName == "pi-" ||
	       particleName == "kaon+" ||
               particleName == "kaon-" ||
               particleName == "proton" ) {

      G4MuMultipleScattering* msc = new G4MuMultipleScattering();
      msc->AddEmModel(0, new G4WentzelVIModel());
      pmanager->AddProcess(msc, -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
      pmanager->AddProcess(new G4hBremsstrahlung,     -1,-3, 3);
      pmanager->AddProcess(new G4hPairProduction,     -1,-4, 4);

    } else if (particleName == "B+" ||
	       particleName == "B-" ||
	       particleName == "D+" ||
	       particleName == "D-" ||
	       particleName == "Ds+" ||
	       particleName == "Ds-" ||
               particleName == "anti_He3" ||
               particleName == "anti_alpha" ||
               particleName == "anti_deuteron" ||
               particleName == "anti_lambda_c+" ||
               particleName == "anti_omega-" ||
               particleName == "anti_proton" ||
               particleName == "anti_sigma_c+" ||
               particleName == "anti_sigma_c++" ||
               particleName == "anti_sigma+" ||
               particleName == "anti_sigma-" ||
               particleName == "anti_triton" ||
               particleName == "anti_xi_c+" ||
               particleName == "anti_xi-" ||
               particleName == "deuteron" ||
	       particleName == "lambda_c+" ||
               particleName == "omega-" ||
               particleName == "sigma_c+" ||
               particleName == "sigma_c++" ||
               particleName == "sigma+" ||
               particleName == "sigma-" ||
               particleName == "tau+" ||
               particleName == "tau-" ||
               particleName == "triton" ||
               particleName == "xi_c+" ||
               particleName == "xi-" ) {

      G4MuMultipleScattering* msc = new G4MuMultipleScattering();
      msc->AddEmModel(0, new G4WentzelVIModel());
      pmanager->AddProcess(msc, -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
    }
  }
  G4EmProcessOptions opt;
  opt.SetVerbose(verbose);
  opt.SetPolarAngleLimit(CLHEP::pi);
  if (applyCut) {  
    opt.SetApplyCuts(true);
    std::cout << GetPhysicsName() << " applying cut" << std::endl;
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
