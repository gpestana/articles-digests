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
// $Id: G4RayleighTest.cc 66241 2012-12-13 18:34:42Z gunter $
//
// -------------------------------------------------------------------
//      GEANT 4 class file --- Copyright CERN 1998
//      CERN Geneva Switzerland
//
//
//      File name:     G4RayleighTest
//
//      Author:        Maria Grazia Pia
// 
//      Creation date: 2 May 2001
//
//      Modifications: 
//
// -------------------------------------------------------------------

#include "globals.hh"
#include "G4ios.hh"
#include <fstream>
#include <iomanip>

#include "G4Material.hh"
#include "G4VContinuousDiscreteProcess.hh"
#include "G4ProcessManager.hh"
#include "G4LowEnergyBremsstrahlung.hh"
#include "G4eBremsstrahlung.hh"
#include "G4LowEnergyRayleigh.hh"
#include "G4LowEnergyIonisation.hh"
#include "G4eIonisation.hh"
#include "G4VeLowEnergyLoss.hh"
#include "G4EnergyLossTables.hh"
#include "G4VParticleChange.hh"
#include "G4ParticleChange.hh"
#include "G4DynamicParticle.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Gamma.hh"

#include "G4Box.hh"
#include "G4PVPlacement.hh"

#include "G4Step.hh"
#include "G4GRSVolume.hh"

#include "G4UnitsTable.hh"
#include "CLHEP/Hist/TupleManager.h"
#include "CLHEP/Hist/HBookFile.h"
#include "CLHEP/Hist/Histogram.h"
#include "CLHEP/Hist/Tuple.h"

HepTupleManager* hbookManager;

int main()
{

  // Setup

  G4int nIterations = 100000;
  G4int materialId = 3;
  G4int test = 0;

  G4cout.setf( ios::scientific, ios::floatfield );

  // -------------------------------------------------------------------

  // ---- HBOOK initialization


  hbookManager = new HBookFile("rayleightest.hbook", 58);
  assert (hbookManager != 0);
  
  // ---- Book a histogram and ntuples
  G4cout<<"Hbook file name: "<<((HBookFile*) hbookManager)->filename()<<endl;
  
  // ---- primary ntuple ------
  HepTuple* ntuple1 = hbookManager->ntuple("Primary Ntuple");
  assert (ntuple1 != 0);
  
  // ---- secondary ntuple ------
  HepTuple* ntuple2 = hbookManager->ntuple("Secondary Ntuple");
  assert (ntuple2 != 0);
   
  // ---- secondaries histos ----
  HepHistogram* hEKin;
  hEKin = hbookManager->histogram("Kinetic Energy", 100,0.,200.);
  assert (hEKin != 0);  
  
  HepHistogram* hP;
  hP = hbookManager->histogram("Momentum", 100,0.,1000.);
  assert (hP != 0);  
  
  HepHistogram* hNSec;
  hNSec = hbookManager->histogram("Number of secondaries", 40,0.,40.);
  assert (hNSec != 0);  
  
  HepHistogram* hDebug;
  hDebug = hbookManager->histogram("Debug", 100,0.,200.);
  assert (hDebug != 0);  
  

  //--------- Materials definition ---------

  G4Material* Be = new G4Material("Beryllium",    4.,  9.01*g/mole, 1.848*g/cm3);
  G4Material* Graphite = new G4Material("Graphite",6., 12.00*g/mole, 2.265*g/cm3 );
  G4Material* Al  = new G4Material("Aluminium", 13., 26.98*g/mole, 2.7 *g/cm3);
  G4Material* Si  = new G4Material("Silicon",   14., 28.055*g/mole, 2.33*g/cm3);
  G4Material* LAr = new G4Material("LArgon",   18., 39.95*g/mole, 1.393*g/cm3);
  G4Material* Fe  = new G4Material("Iron",      26., 55.85*g/mole, 7.87*g/cm3);
  G4Material* Cu  = new G4Material("Copper",    29., 63.55*g/mole, 8.96*g/cm3);
  G4Material*  W  = new G4Material("Tungsten", 74., 183.85*g/mole, 19.30*g/cm3);
  G4Material* Pb  = new G4Material("Lead",      82., 207.19*g/mole, 11.35*g/cm3);
  G4Material*  U  = new G4Material("Uranium", 92., 238.03*g/mole, 18.95*g/cm3);

  G4Element*   H  = new G4Element ("Hydrogen", "H", 1. ,  1.01*g/mole);
  G4Element*   O  = new G4Element ("Oxygen"  , "O", 8. , 16.00*g/mole);
  G4Element*   C  = new G4Element ("Carbon"  , "C", 6. , 12.00*g/mole);
  G4Element*  Cs  = new G4Element ("Cesium"  , "Cs", 55. , 132.905*g/mole);
  G4Element*   I  = new G4Element ("Iodide"  , "I", 53. , 126.9044*g/mole);

  G4Material*  maO = new G4Material("Oxygen", 8., 16.00*g/mole, 1.1*g/cm3);

  G4Material* water = new G4Material ("Water" , 1.*g/cm3, 2);
  water->AddElement(H,2);
  water->AddElement(O,1);

  G4Material* ethane = new G4Material ("Ethane" , 0.4241*g/cm3, 2);
  ethane->AddElement(H,6);
  ethane->AddElement(C,2);
  
  G4Material* csi = new G4Material ("CsI" , 4.53*g/cm3, 2);
  csi->AddElement(Cs,1);
  csi->AddElement(I,1);


  // Interactive set-up

  G4cout << "How many interactions? " << G4endl;
  G4cin >> nIterations;

  if (nIterations <= 0) G4Exception("Wrong input");

  G4double initEnergy = 1*MeV; 
  G4double initX = 0.; 
  G4double initY = 0.; 
  G4double initZ = 1.;

  G4cout << "Enter the initial particle energy E (MeV)" << G4endl; 
  G4cin >> initEnergy ;

  initEnergy = initEnergy * MeV;

  if (initEnergy  <= 0.) G4Exception("Wrong input");

  static const G4MaterialTable* theMaterialTable = G4Material::GetMaterialTable();

 G4int nMaterials = G4Material::GetNumberOfMaterials();

  G4cout << "Available materials are: " << G4endl;
  for (G4int mat = 0; mat < nMaterials; mat++)
    {
      G4cout << mat << ") "
	     << (*theMaterialTable)[mat]->GetName()
	     << G4endl;
    }

  G4cout << "Which material? " << G4endl;
  G4cin >> materialId;

  G4Material* material = (*theMaterialTable)[materialId] ;

  G4cout << "The selected material is: "
	 << material->GetName()
	 << G4endl;

  G4double dimX = 1*mm;
  G4double dimY = 1*mm;
  G4double dimZ = 1*mm;
  
  // Geometry 

  G4Box* theFrame = new G4Box ("Frame",dimX, dimY, dimZ);
  
  G4LogicalVolume* logicalFrame = new G4LogicalVolume(theFrame,
						      (*theMaterialTable)[materialId],
						      "LFrame", 0, 0, 0);
  logicalFrame->SetMaterial(material); 
  
  G4PVPlacement* physicalFrame = new G4PVPlacement(0,G4ThreeVector(),
						   "PFrame",logicalFrame,0,false,0);
  
  // Particle definitions

  G4ParticleDefinition* gamma = G4Gamma::GammaDefinition();
  G4ParticleDefinition* electron = G4Electron::ElectronDefinition();
  G4ParticleDefinition* positron = G4Positron::PositronDefinition();
  
  gamma->SetCuts(1e-3*mm);
  electron->SetCuts(1e-3*mm);
  positron->SetCuts(1e-3*mm);
  
  // Processes 

  G4VContinuousDiscreteProcess* bremProcess = new G4LowEnergyBremsstrahlung;
  G4VContinuousDiscreteProcess* ioniProcess = new G4LowEnergyIonisation;

  G4ProcessManager* eProcessManager = new G4ProcessManager(electron);
  electron->SetProcessManager(eProcessManager);
  eProcessManager->AddProcess(bremProcess);
    
  G4ProcessManager* positronProcessManager = new G4ProcessManager(positron);
  positron->SetProcessManager(positronProcessManager);
  positronProcessManager->AddProcess(bremProcess);
  
  // Initialize the physics tables 
  bremProcess->BuildPhysicsTable(*electron);
  ioniProcess->BuildPhysicsTable(*electron);

  // Photon process 
  G4VDiscreteProcess* photonProcess = new G4LowEnergyRayleigh;

  G4ProcessManager* gProcessManager = new G4ProcessManager(gamma);
  gamma->SetProcessManager(gProcessManager);
  gProcessManager->AddProcess(photonProcess);
  photonProcess->BuildPhysicsTable(*gamma);

  // Create a DynamicParticle  
  
  G4double gEnergy = initEnergy*MeV;
  G4ParticleMomentum gDirection(initX,initY,initZ);
  G4DynamicParticle dynamicPhoton(G4Gamma::Gamma(),gDirection,gEnergy);

  // Track 

  G4ThreeVector aPosition(0.,0.,0.);
  G4ThreeVector newPosition(0.,0.,1.*mm);
  G4double aTime = 0. ;

  G4Track* gTrack = new G4Track(&dynamicPhoton,aTime,aPosition);

  // do I really need this?

  G4GRSVolume* touche = new G4GRSVolume(physicalFrame, 0, aPosition);   
  gTrack->SetTouchable(touche);
 
 // Step 

  G4Step* step = new G4Step();  
  step->SetTrack(gTrack);

  G4StepPoint* aPoint = new G4StepPoint();
  aPoint->SetPosition(aPosition);
  aPoint->SetMaterial(material);
  G4double safety = 10000.*cm;
  aPoint->SetSafety(safety);
  step->SetPreStepPoint(aPoint);
  G4StepPoint* newPoint = new G4StepPoint();
  newPoint->SetPosition(newPosition);
  newPoint->SetMaterial(material);
  step->SetPostStepPoint(newPoint);

  // Check applicability
  
  if (! (photonProcess->IsApplicable(*gamma)))
    {
      G4Exception("Not Applicable");
    }

  // --------- Test the DoIt 

  G4cout << "DoIt in material " << material->GetName() << G4endl;

  G4int iteration = 0;   
 

  for (G4int iter=0; iter<nIterations; iter++)
    {
      step->SetStepLength(1*micrometer);

      gTrack->SetStep(step); 
 
      G4cout  <<  "Iteration = "  <<  iter 
	      << "  -  Step Length = " 
	      << step->GetStepLength()/mm << " mm "
	      << G4endl;

      G4VParticleChange* dummy;
      dummy = photonProcess->PostStepDoIt(*gTrack, *step);

      G4ParticleChange* particleChange = (G4ParticleChange*) dummy;
      
      // Primary physical quantities 

      G4double energyChange = particleChange->GetEnergyChange();
      G4double dedx = initEnergy - energyChange ;
      G4double dedxNow = dedx / (step->GetStepLength());
      
      G4ThreeVector eChange = particleChange->CalcMomentum(energyChange,
							   (*particleChange->GetMomentumChange()),
							   particleChange->GetMassChange());

      G4double pxChange  = eChange.x();
      G4double pyChange  = eChange.y();
      G4double pzChange  = eChange.z();
      G4double pChange   = std::sqrt(pxChange*pxChange + pyChange*pyChange + pzChange*pzChange);
      
      G4double xChange = particleChange->GetPositionChange()->x();
      G4double yChange = particleChange->GetPositionChange()->y();
      G4double zChange = particleChange->GetPositionChange()->z();
      G4double thetaChange = particleChange->GetPositionChange()->theta();

      G4cout << "---- Primary after the step ---- " << G4endl;
 
      //      G4cout << "Position (x,y,z) = " 
      //	     << xChange << "  " 
      //	     << yChange << "   " 
      //	     << zChange << "   " 
      //	     << G4endl;

      G4cout << "---- Energy: " << energyChange/MeV << " MeV,  " 
	     << "(px,py,pz): ("
	     << pxChange/MeV << ","
	     << pyChange/MeV << "," 
	     << pzChange/MeV << ") MeV"
	     << G4endl;

      G4cout << "---- Energy loss (dE) = " << dedx/keV << " keV" << G4endl;
      //      G4cout << "Stopping power (dE/dx)=" << dedxNow << G4endl;
      
      // Secondaries 

      ntuple1->column("eprimary", initEnergy);
      ntuple1->column("energyf", energyChange);
      ntuple1->column("de", dedx);
      ntuple1->column("dedx", dedxNow);
      ntuple1->column("pxch", xChange);
      ntuple1->column("pych", pyChange);
      ntuple1->column("pzch", pzChange);
      ntuple1->column("pch", zChange);  
      ntuple1->column("thetach", thetaChange);  
      
      // Secondaries physical quantities 
      
      hNSec->accumulate(particleChange->GetNumberOfSecondaries());
      hDebug->accumulate(particleChange->GetLocalEnergyDeposit());
      
      G4int nElectrons = 0;
      G4int nPositrons = 0;
      G4int nPhotons = 0;

      for (G4int i = 0; i < (particleChange->GetNumberOfSecondaries()); i++) 
	{
	  // The following two items should be filled per event, not
	  // per secondary; filled here just for convenience, to avoid
	  // complicated logic to dump ntuple when there are no secondaries
	  
	  G4Track* finalParticle = particleChange->GetSecondary(i) ;
	  
	  G4double e    = finalParticle->GetTotalEnergy();
	  G4double eKin = finalParticle->GetKineticEnergy();
	  G4double px   = (finalParticle->GetMomentum()).x();
	  G4double py   = (finalParticle->GetMomentum()).y();
	  G4double pz   = (finalParticle->GetMomentum()).z();
	  G4double theta   = (finalParticle->GetMomentum()).theta();
	  G4double p   = std::sqrt(px*px+py*py+pz*pz);

	  if (e > initEnergy)
	    {
	      G4cout << "WARNING: eFinal > eInit " << G4endl;
		//	     << e
    		//		     << " > " initEnergy 
		 
	    }

	  G4String particleName = finalParticle->GetDefinition()->GetParticleName();
	  G4cout  << "==== Final " 
		  <<  particleName  <<  " "  
		  << "energy: " <<  e/MeV  <<  " MeV,  " 
		  << "eKin: " <<  eKin/MeV  <<  " MeV, " 
		  << "(px,py,pz): ("
		  <<  px/MeV  <<  "," 
		  <<  py/MeV  <<  ","
		  <<  pz/MeV  << ") MeV "
		  <<  G4endl;   
	  
	  hEKin->accumulate(eKin);
	  hP->accumulate(p);
	  
	  G4int partType = 0;
	  if (particleName == "e-") 
	    {
	      partType = 1;
	      nElectrons++;
	    }
	  else if (particleName == "e+") 
	    {
	      partType = 2;
	      nPositrons++;
	    }
	  else if (particleName == "gamma") 
	    {
	      partType = 3;
	      nPhotons++;
	    }
	  // Fill the secondaries ntuple
          ntuple2->column("eprimary",initEnergy);
	  ntuple2->column("px", px);
	  ntuple2->column("py", py);
	  ntuple2->column("pz", pz);
	  ntuple2->column("p", p);
	  ntuple2->column("e", e);
	  ntuple2->column("theta", theta);
	  ntuple2->column("ekin", eKin);
	  ntuple2->column("type", partType);
	  
	  ntuple2->dumpData(); 
	  
	  delete particleChange->GetSecondary(i);
	}

      ntuple1->column("nelectrons",nElectrons);
      ntuple1->column("npositrons",nPositrons);
      ntuple1->column("nphotons",nPhotons);
      ntuple1->dumpData(); 
	          
      particleChange->Clear();
      
    } 
  
  
  cout  << "Iteration number: "  <<  G4endl;
  hbookManager->write();
  delete hbookManager;
  
  // delete materials and elements
  //  delete Be;
  //  delete Graphite;
  //  delete Al;
  //  delete Si;
  //  delete LAr;
  //  delete Fe;
  //  delete Cu;
  //  delete W;
  //  delete Pb;
  //  delete U;
  //  delete H;
  //  delete maO;
  //  delete C;
  //  delete Cs;
  //  delete I;
  //  delete O;
  //  delete water;
  //  delete ethane;
  //  delete csi;
  //  delete step;
  //  delete touche;
  //  delete Be;
  //  delete Graphite;
  //  delete Al;
  //  delete Si;
  //  delete LAr;
  //  delete Fe;
  //  delete Cu;
  //  delete W;
  //  delete Pb;
  //  delete U;
  //  delete H;
  //  delete maO;
  //  delete C;
  //  delete Cs;
  //  delete I;
  //  delete O;
  //  delete water;
  //  delete ethane;
  //  delete csi;
  delete step;
  //  delete touche;

  cout << "END OF THE MAIN PROGRAM" << G4endl;
}












