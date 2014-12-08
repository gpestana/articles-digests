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
// -------------------------------------------------------------
//      GEANT 4 class for test35
//
//      History: based on object model of
//      ---------- Test30Physics -------
//                by Vladimir Ivanchenko, 12 March 2002 
// 
//    Modified:
//  11.10.2007 Added INCL cascade and RPG parameterized model (V.Ivanchenko)
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "Test30Physics.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "Test30VSecondaryGenerator.hh"
#include "G4PhysicsTable.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4DecayPhysics.hh"

#include "G4PionPlus.hh"
#include "G4PionMinus.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4GenericIon.hh"
#include "G4Alpha.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"

#include "G4PreCompoundModel.hh"
#include "G4ExcitationHandler.hh"
#include "G4BinaryCascade.hh"
#include "G4BinaryLightIonReaction.hh"
#include "G4CascadeInterface.hh"
#include "HsQGSPInterface.hh"
#include "HsQGSBInterface.hh"
#include "G4INCLXXInterface.hh"

#include "G4HadronElastic.hh"

#include "G4TheoFSGenerator.hh"
#include "G4FTFModel.hh"
#include "G4ExcitedStringDecay.hh"
#include "G4LundStringFragmentation.hh"
#include "G4QuasiElasticChannel.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

Test30Physics::Test30Physics()
{
  Initialise();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

Test30Physics::~Test30Physics()
{
  delete theProcess;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test30Physics::Initialise()
{
  G4DecayPhysics dp;
  dp.ConstructParticle();
  theProcess = 0;
  theDeExcitation = 0;
  thePreCompound = 0;
  hkmod = 0;
  theQuasiElastic = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VProcess* Test30Physics::GetProcess(const G4String& gen_name,
		                      const G4String& part_name,
		                            G4Material* mat)
{
  G4cout <<  "Test30Physics entry" << G4endl;
  if(theProcess) { delete theProcess; }
  theProcess = 0;

  G4ProcessManager* man = 0;

  if(part_name == "proton")   man = new G4ProcessManager(G4Proton::Proton());
  else if(part_name == "pi+") man = new G4ProcessManager(G4PionPlus::PionPlus());
  else if(part_name == "pi-") man = new G4ProcessManager(G4PionMinus::PionMinus());
  else if(part_name == "neutron") man = new G4ProcessManager(G4Neutron::Neutron());
  else if(part_name == "deuteron") man = new G4ProcessManager(G4Deuteron::Deuteron());
  else if(part_name == "alpha") man = new G4ProcessManager(G4Alpha::Alpha());

  if(!man) return 0;

  theProcess = new Test30HadronProduction();
  G4cout <<  "Process is created; gen= " << gen_name << G4endl;

  // Physics list for the given run
  Test30VSecondaryGenerator* sg = 0;

  // Choose generator
  if(gen_name == "binary") {
    G4BinaryCascade* hkm = new G4BinaryCascade();
    hkm->SetMaxEnergy(15.*GeV);
    sg = new Test30VSecondaryGenerator(hkm, mat);
    theProcess->SetSecondaryGenerator(sg);
    man->AddDiscreteProcess(theProcess);

  } else if(gen_name == "binary_ion") {
    G4BinaryLightIonReaction* hkm = new G4BinaryLightIonReaction();
    hkm->SetMaxEnergy(15.*GeV);
    sg = new Test30VSecondaryGenerator(hkm, mat);
    theProcess->SetSecondaryGenerator(sg);
    man->AddDiscreteProcess(theProcess);

  } else if(gen_name == "bertini") {
    G4CascadeInterface* hkm = new G4CascadeInterface();
    hkm->SetMaxEnergy(15.*GeV);
    sg = new Test30VSecondaryGenerator(hkm, mat);
    theProcess->SetSecondaryGenerator(sg);
    man->AddDiscreteProcess(theProcess);

  } else if(gen_name == "incl") {
    G4INCLXXInterface * hkm = new G4INCLXXInterface();
    sg = new Test30VSecondaryGenerator(hkm, mat);
    theProcess->SetSecondaryGenerator(sg);
    man->AddDiscreteProcess(theProcess);

  } else if(gen_name == "incl_ion") {
    G4INCLXXInterface* hkm = new G4INCLXXInterface();
    sg = new Test30VSecondaryGenerator(hkm, mat);
    theProcess->SetSecondaryGenerator(sg);
    man->AddDiscreteProcess(theProcess);

  } else if(gen_name == "qgsp") {
    HsQGSPInterface* qgsp = new HsQGSPInterface();
    qgsp->SetMinEnergy(GeV);
    sg = new Test30VSecondaryGenerator(qgsp, mat);
    theProcess->SetSecondaryGenerator(sg);
    man->AddDiscreteProcess(theProcess);

  } else if(gen_name == "qgsb") {
    HsQGSBInterface* qgsb = new HsQGSBInterface();
    qgsb->SetMinEnergy(GeV);
    sg = new Test30VSecondaryGenerator(qgsb, mat);
    theProcess->SetSecondaryGenerator(sg);
    man->AddDiscreteProcess(theProcess);

  } else if(gen_name == "Elastic") {
    G4HadronElastic* els = new G4HadronElastic();
    sg = new Test30VSecondaryGenerator(els, mat);
    theProcess->SetSecondaryGenerator(sg);
    man->AddDiscreteProcess(theProcess);

  } else if(gen_name == "ftfp") {

    G4TheoFSGenerator* theModel = new G4TheoFSGenerator;
    G4FTFModel* theStringModel = new G4FTFModel();
    G4GeneratorPrecompoundInterface* theCascade = 
      new G4GeneratorPrecompoundInterface;
    theCascade->SetCaptureThreshold(10*MeV);
    G4ExcitedStringDecay* theStringDecay = 
      new G4ExcitedStringDecay(new G4LundStringFragmentation());
    theStringModel->SetFragmentationModel(theStringDecay);

    theModel->SetTransport(theCascade);
    theModel->SetHighEnergyGenerator(theStringModel);
    theModel->SetMinEnergy(GeV);

    sg = new Test30VSecondaryGenerator(theModel, mat);
    theProcess->SetSecondaryGenerator(sg);
    man->AddDiscreteProcess(theProcess);

  } else if(gen_name == "ftfb") {

    G4TheoFSGenerator * model = new G4TheoFSGenerator;
    G4FTFModel * stringmodel= new G4FTFModel;
    G4BinaryCascade* cascade = new G4BinaryCascade();
    G4ExcitedStringDecay * stringDecay = 
      new G4ExcitedStringDecay(new G4LundStringFragmentation());
    stringmodel->SetFragmentationModel(stringDecay);

    model->SetHighEnergyGenerator(stringmodel);
    model->SetTransport(cascade);
    model->SetMinEnergy(GeV);

    sg = new Test30VSecondaryGenerator(model, mat);
    theProcess->SetSecondaryGenerator(sg);
    man->AddDiscreteProcess(theProcess);

  } else {
    G4cout << gen_name
           << " generator is unkown - no hadron production" << G4endl;
  }

  G4cout <<  "Secondary generator <"
         << gen_name << "> is initialized"
         << G4endl;
  return theProcess;

}	

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  






