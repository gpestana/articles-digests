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
// $Id$
// ------------------------------------------------------------
//	GEANT 4 class header file 
//
//      This is a version for maximum particle set
//	History
//        first version              10  Jan. 1998 by H.Kurashige
//        add decay at rest          26  Feb. 1998 by H.Kurashige
// ------------------------------------------------------------

#include "globals.hh"
#include "Tst01PhysicsList.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4ios.hh"
#include <iomanip>                


Tst01PhysicsList::Tst01PhysicsList():  G4VUserPhysicsList()
{
  SetVerboseLevel(1);
}

Tst01PhysicsList::~Tst01PhysicsList()
{
}

void Tst01PhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  ConstructBosons();
  //  ConstructLeptons();
  //  ConstructMesons();
  //  ConstructBarions();

}

void Tst01PhysicsList::ConstructBosons()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();

  // optical photon
  G4OpticalPhoton::OpticalPhotonDefinition();
}

void Tst01PhysicsList::ConstructLeptons()
{
  // leptons
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  G4TauMinus::TauMinusDefinition();
  G4TauPlus::TauPlusDefinition();
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4NeutrinoTau::NeutrinoTauDefinition();
  G4AntiNeutrinoTau::AntiNeutrinoTauDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
}

void Tst01PhysicsList::ConstructMesons()
{
 //  mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
  G4Eta::EtaDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
  G4KaonZero::KaonZeroDefinition();
  G4AntiKaonZero::AntiKaonZeroDefinition();
  G4KaonZeroLong::KaonZeroLongDefinition();
  G4KaonZeroShort::KaonZeroShortDefinition();

  G4DMesonPlus::DMesonPlusDefinition();
  G4DMesonMinus::DMesonMinusDefinition();
  G4DMesonZero::DMesonZeroDefinition();
  G4AntiDMesonZero::AntiDMesonZeroDefinition();
  G4DsMesonPlus::DsMesonPlusDefinition();
  G4DsMesonMinus::DsMesonMinusDefinition();
  G4JPsi::JPsiDefinition();

  G4BMesonPlus::BMesonPlusDefinition();
  G4BMesonMinus::BMesonMinusDefinition();
  G4BMesonZero::BMesonZeroDefinition();
  G4AntiBMesonZero::AntiBMesonZeroDefinition();
  G4BsMesonZero::BsMesonZeroDefinition();
  G4AntiBsMesonZero::AntiBsMesonZeroDefinition();
}

void Tst01PhysicsList::ConstructBarions()
{
//  barions
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();
  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();
  G4Lambda::LambdaDefinition();
  G4AntiLambda::AntiLambdaDefinition();
  G4SigmaZero::SigmaZeroDefinition();
  G4AntiSigmaZero::AntiSigmaZeroDefinition();
  G4SigmaPlus::SigmaPlusDefinition();
  G4AntiSigmaPlus::AntiSigmaPlusDefinition();
  G4SigmaMinus::SigmaMinusDefinition();
  G4AntiSigmaMinus::AntiSigmaMinusDefinition();
  G4XiZero::XiZeroDefinition();
  G4AntiXiZero::AntiXiZeroDefinition();
  G4XiMinus::XiMinusDefinition();
  G4AntiXiMinus::AntiXiMinusDefinition();
  G4OmegaMinus::OmegaMinusDefinition();
  G4AntiOmegaMinus::AntiOmegaMinusDefinition();

  G4LambdacPlus::LambdacPlusDefinition();
  G4SigmacPlusPlus::SigmacPlusPlusDefinition();
  G4SigmacPlus::SigmacPlusDefinition();
  G4SigmacZero::SigmacZeroDefinition();
  G4XicPlus::XicPlusDefinition();
  G4XicZero::XicZeroDefinition();
  G4OmegacZero::OmegacZeroDefinition();
  G4AntiLambdacPlus::AntiLambdacPlusDefinition();
  G4AntiSigmacPlusPlus::AntiSigmacPlusPlusDefinition();
  G4AntiSigmacPlus::AntiSigmacPlusDefinition();
  G4AntiSigmacZero::AntiSigmacZeroDefinition();
  G4AntiXicPlus::AntiXicPlusDefinition();
  G4AntiXicZero::AntiXicZeroDefinition();
  G4AntiOmegacZero::AntiOmegacZeroDefinition();
}

void Tst01PhysicsList::ConstructIons()
{
  //  nuclei
  G4Alpha::AlphaDefinition();
  G4Deuteron::DeuteronDefinition();
  G4Triton::TritonDefinition();
}

void Tst01PhysicsList::ConstructProcess()
{
  AddTransportation();
  //  ConstructEM();
  //  ConstructLeptHad();
  //  ConstructHad();
  ConstructGeneral();
}

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

//#include "G4eMultipleScattering.hh"
//#include "G4MuMultipleScattering.hh"
//#include "G4hMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"
void Tst01PhysicsList::ConstructEM()
{
  theParticleIterator->reset();

  while( (*theParticleIterator)() )
  {
    G4ParticleDefinition* particle = theParticleIterator->value();
    // G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
     
    if (particleName == "gamma") 
    {
      // gamma
      // Construct processes for gamma

      // pmanager->AddDiscreteProcess(new G4GammaConversion());
      // pmanager->AddDiscreteProcess(new G4ComptonScattering());      
      // pmanager->AddDiscreteProcess(new G4PhotoElectricEffect());

    } 
    else if (particleName == "e-") 
    {
      //electron
      // Construct processes for electron

      // pmanager->AddProcess(new G4eMultipleScattering(),-1,1,1);
      // pmanager->AddProcess(new G4eIonisation(),-1,2,2);
      // pmanager->AddProcess(new G4eBremsstrahlung(),-1,-1,3);
  
    } 
    else if (particleName == "e+") 
    {
      //positron
      // Construct processes for positron
      // pmanager->AddProcess(new G4eMultipleScattering(),-1,1,1);
     
      // pmanager->AddProcess(new G4eIonisation(),-1,2,2);
      // pmanager->AddProcess(new G4eBremsstrahlung(),-1,-1,3);      
      // pmanager->AddProcess(new G4eplusAnnihilation(),0,-1,4);
  
    } 
    else if( particleName == "mu+" || 
               particleName == "mu-"    ) 
    {
      //muon  
      // Construct processes for muon+

      // pmanager->AddProcess(new G4MuMultipleScattering(),-1,1,1);
      // pmanager->AddProcess(new G4MuIonisation(),-1,2,2);
      // pmanager->AddProcess(new G4MuBremsstrahlung(),-1,-1,3);
      // pmanager->AddProcess(new G4MuPairProduction(),-1,-1,4);       
     
    } 
    else 
    { 
      if ((particle->GetPDGCharge() != 0.0) && 
          (particle->GetParticleName() != "chargedgeantino")) 
      {
        // all others charged particles except geantino

	// pmanager->AddProcess(new G4hMultipleScattering(),-1,1,1);
	// pmanager->AddProcess(new G4hIonisation(),-1,2,2);       
     }
    }
  }
}

void Tst01PhysicsList::ConstructHad()
{;}

void Tst01PhysicsList::ConstructLeptHad()
{;}

#include "G4Decay.hh"
void Tst01PhysicsList::ConstructGeneral()
{
  G4Decay* theDecayProcess = new G4Decay();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if (theDecayProcess->IsApplicable(*particle)) { 
      pmanager->AddProcess(theDecayProcess, INT_MAX, -1, INT_MAX); 
   }
  }
}

void Tst01PhysicsList::SetCuts()
{
  if (verboseLevel >0)
  {
    G4cout << "Tst01PhysicsList::SetCuts:";
    // G4cout << "CutLength : " << cut/mm << " (mm)" << G4endl;
  }  

  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma 

  //  SetCutValue(cut, "gamma");
  //  SetCutValue(cut, "e-");
  //  SetCutValue(cut, "e+");
 
  // set cut values for proton and anti_proton before all other hadrons
  // because some processes for hadrons need cut values for proton/anti_proton
 
  //  SetCutValue(cut, "proton");
  //  SetCutValue(cut, "anti_proton");
  
  //  SetCutValueForOthers(cut);

  if (verboseLevel>1) 
  {
    DumpCutValuesTable();
  }
}


