//               FTF test: P+P interactions; Inclusive
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
//
// -------------------------------------------------------------------
//      GEANT 4 class file --- Copyright CERN 1998
//      CERN Geneva Switzerland
//
//
//      File name:     Test30
//
//      Author:        V.Ivanchenko
//
//      Creation date: 12 March 2002
//
//      Modifications:
//      14.11.03 Renamed to cascade
//      09.05.06 Return back to test30
// -------------------------------------------------------------------
#include "globals.hh"
#include "G4Version.hh"
#include "G4ios.hh"
#include <fstream>
#include <iomanip>

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "FTFtest1.icc"
#include "G4ChipsComponentXS.hh"                  // Uzhi 29.01.13

#include "UZHI_diffraction.hh"

int main(int argc, char** argv)
{
  CLHEP::RanluxEngine defaultEngine( 1234567, 4 );
  CLHEP::HepRandom::setTheEngine( &defaultEngine );

  G4cout << "========================================================" << G4endl;
  G4cout << "======              FTF Test Start              ========" << G4endl;
  G4cout << "========================================================" << G4endl;

  // -------------------------------------------------------------------
  // Control on input

  if(argc < 2) {
    G4cout << "Input file is not specified! Exit" << G4endl;
    exit(1);
  }

  std::ifstream* fin = new std::ifstream();

  G4String fname = argv[1];
  fin->open(fname.c_str());
  if( !fin->is_open()) {
    G4cout << "Input file <" << fname << "> does not exist! Exit" << G4endl;
    exit(1);
  }

//-----------------------------------------------------------------------
  #include "FTFtest2.icc"   // Initialization
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
//G4double sigTot = 0; 
//G4double sigEl  = 0;
G4double sigIn  = 0;

//-------------------------- Global histograms  -------------------------
std::ofstream PbDNeRest("PbDNe_Rest.dat",std::ios::out);

//G4double SqrtS;
//G4double Ycms;

G4double EnerUzhi[110][2];                 // 0 / 1200 MeV/c momentum
for(G4int ii=0; ii<110; ii++){for(G4int j=0;j<2;j++) EnerUzhi[ii][j]=0.;}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // -------- Loop over run

  G4String line, line1;
  G4bool end = true;

  for(G4int run=0; run<100; run++) {
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-------------------------- Current histograms -------------------------

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
  do {
    #include "FTFtest3.icc"  // -------- Read input file
    #include "FTFtest4.icc"  // -------- Start run processing  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

    G4cout << "cross(mb)in= " << cross_sec*1000./barn << G4endl
           << "cross(mb)el= " << cross_secel*1000./barn<<G4endl<<G4endl;

    cross_inel=cross_sec-cross_secel; // +++++++++++++++++++++++++

    cross_sec/=millibarn;   // Inel Cross section in mb
    cross_secel/=millibarn; // Elas Cross section in mb
    cross_inel/=millibarn;  // Inel Cross section in mb

    G4cout<<"Element A Z N: "<<A<<" "<<Z<<" "<<A-Z<<G4endl;
    G4cout<<"Proposed Xs (mb): Tot El In: "
          <<cross_sec<<" "<<cross_secel<<" "<<cross_inel<<G4endl;

//---------------------------------------------------------------------------
// Kossov cross sections      ---------------------------
    G4double chipsTot, chipsEl, chipsIn;

    static G4ChipsComponentXS* _instance = new G4ChipsComponentXS();
    G4ChipsComponentXS* CHIPSxsManager = _instance;

    G4bool CHIPapplic=true;                          //false;   Uzhi 29.01.13
    if(CHIPapplic)
    {
     chipsTot=CHIPSxsManager->GetTotalElementCrossSection(part,energy,Z,A-Z);
     chipsEl =CHIPSxsManager->GetElasticElementCrossSection(part,energy,Z,A-Z);
     chipsIn =CHIPSxsManager->GetInelasticElementCrossSection(part,energy,Z,A-Z);
     chipsTot/=millibarn; chipsEl/=millibarn; chipsIn/=millibarn;

     G4cout<<"CHIPS cross sections are used:----------------------"<<G4endl<<
             "Plab          Total        Elastic      Inelastic"   <<G4endl;
     G4cout<<" "<<Plab/GeV<<" "<< chipsTot<<" "<<chipsEl<<" "<<chipsIn <<G4endl<<G4endl;

     /* sigTot=chipsTot; sigEl=chipsEl; */ sigIn=chipsIn;
    } else
    {
     //sigTot = cross_sec; 
     //sigEl  = cross_secel;
     sigIn  = cross_inel;

     G4cout<<"Proposed Xs (mb) are used: Tot El In: "
           <<cross_sec<<" "<<cross_secel<<" "<<cross_inel<<G4endl;
    }

//+++++++++++++++++++++++++++++++++ For each energy +++++++++++++++++++++
   //G4double E=energy+part->GetPDGMass();
   //SqrtS=std::sqrt(sqr(part->GetPDGMass())+sqr(938.)+2.*938.*E);
   //SqrtS=SqrtS;       
// Ycms=0.5*std::log((E+Plab)/(E-Plab));

//  G4int Ntotal=nevt;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++       
//-------------------------------------------------------

    const G4DynamicParticle* sec = 0;
    G4ParticleDefinition* pd;
    G4ThreeVector  mom;
    G4LorentzVector labv, fm;
    G4double e; // px, py, pz, pt, pt2, theta;

    G4VParticleChange* aChange = 0;

//  G4double E=energy+part->GetPDGMass();                                  // Elab Proj
//  G4double SqrtS=std::sqrt(sqr(part->GetPDGMass())+sqr(938.)+2.*938.*E); // per  Proj+N
//  G4double Ycms=0.5*std::log((E+Plab)/(E-Plab));                         //      Proj+N

    // -------- Event loop
    G4cout<<"Events start "<<nevt<<G4endl;
    G4int Ninelast=nevt;                              // Uzhi
//=================================================================
    for (G4int iter=0; iter<nevt; ++iter) {
//=================================================================
      if(verbose > 0) G4cout<<"Start events loop***********************"<<G4endl;

      if(verbose>=1 || iter == modu*(iter/modu)) { 
        G4cout << "### " << iter << "-th event start " <<Plab/GeV<<G4endl;
      }

      if(saverand) {defaultEngine.saveStatus("initial.conf");}

      G4double e0 = energy;
      do {
        if(sigmae > 0.0) e0 = G4RandGauss::shoot(energy,sigmae);
      } while (e0 < 0.0);

      dParticle.SetKineticEnergy(e0);

      gTrack->SetStep(step);
      gTrack->SetKineticEnergy(e0);
      G4double amass = phys->GetNucleusMass();
      // note: check of 4-momentum balance for CHIPS is not guranteed due to
      // unknown isotope      
      aChange = proc->PostStepDoIt(*gTrack,*step); 

      G4double mass = part->GetPDGMass();

      if ( ionParticle ) 
      {
       e0/=ionA; G4double mass_N=938.*MeV;                              // Init 4-mom
       labv = G4LorentzVector(0.0, 0.0, std::sqrt(e0*(e0 + 2.*mass_N)), //   NN
	 		      e0 + mass_N +  mass_N); 
      } else
      {                                             
       labv = G4LorentzVector(0.0, 0.0, std::sqrt(e0*(e0 + 2.*mass)),   //   hA
  		              e0 + mass + amass); 
      }

      G4ThreeVector bst = labv.boostVector();          // To CMS NN in AA or hA
//------------
      G4LorentzVector labNN(0.0, 0.0, std::sqrt(e0*(e0 + 2.*mass)),e0 + mass + amass);
      G4ThreeVector boostNN = labNN.boostVector();
//------------

      // take into account local energy deposit
      G4double de = aChange->GetLocalEnergyDeposit();
      G4LorentzVector dee = G4LorentzVector(0.0, 0.0, 0.0, de); 
      labv -= dee;

      G4int n = aChange->GetNumberOfSecondaries();     // Multiplicity of prod. part.

      if(verbose>=1) G4cout<<" Uzhi ------------ N prod. part "<<n<<G4endl;
//++++++++++++++++ Variables for each event +++++++++++++++++++++++++++++
      if((verbose > 0) && (n < 2)) {G4cout<<"Multiplicity of produced < 2!!!"<<G4endl;}

//    G4int Ncharged=0;                          // Uzhi
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      for(G4int i=0; i<n; ++i)              // Loop over produced particles
      {
        sec = aChange->GetSecondary(i)->GetDynamicParticle();
        pd  = sec->GetDefinition();
        G4String pname=pd->GetParticleName();

        if(verbose>=1) G4cout<<" Part  "<<i<<" "<<pname
                             <<" "<<sec->Get4Momentum()/GeV
                             <<sec->Get4Momentum().mag()/GeV<<G4endl;

        fm  = sec->Get4Momentum();
        mom = fm.vect();
/*
        G4double m = pd->GetPDGMass();
        e  = fm.e() - m;
*/
        e  = fm.e();

        labv -= fm;   // For checking energy-momentum conservation

	// electron can come only from internal conversion
	// its mass should be added to initial state
        if(pd == electron) { 

	  labv += G4LorentzVector(0.0,0.0,0.0,electron_mass_c2); 
	}
/*
        px = mom.x();
        py = mom.y();
        pz = mom.z(); pz=pz;
        pt = std::sqrt(px*px +py*py); pt2=sqr(pt/GeV);
        theta = mom.theta();

//        G4double CosTheta=std::cos(theta);

        theta=theta*180./pi;

//        G4double costcm = std::cos(fm.theta());
*/
        G4double Pmod=mom.mag();

        G4double Weight=0.;
        if(Pmod > 0.) Weight=e/sqr(Pmod);

        G4int ImomUz=int(e/12.); 
        if(ImomUz < 0) ImomUz=0; if(ImomUz > 109) ImomUz=109;

//+++++++++++++++++ For each particle in the event ++++++++++++++++++++++

	 if  (pname == "proton")     
         {
            EnerUzhi[ImomUz][0]+=Weight;
         };
/*
	 if ( pname == "neutron" )  
         {
            EnerUzhi[ImomUz][1]++;
         };
*/

	 if ( pname == "pi+" ) 
         {
            EnerUzhi[ImomUz][1]+=Weight; 
         };  

	 if ( pname == "pi-" ) 
         {
            EnerUzhi[ImomUz][1]+=Weight; 
         };  
/*
	 if ( pname == "kaon+" ) 
         {
            XfUzhi[NxUzhi][4]+=PartWeight; 
            YUzhi[NyUzhi][4]+=1; 
            Pt2Uzhi[NPt2Uzhi][4]+=1;
         };

	 if ( pname == "kaon-" ) 
         {
            XfUzhi[NxUzhi][5]+=PartWeight; 
            YUzhi[NyUzhi][5]+=1; 
            Pt2Uzhi[NPt2Uzhi][5]+=1;
         };

	 if ( pname == "anti_proton" )  
         {
            XfUzhi[NxUzhi][6]+=PartWeight; 
            YUzhi[NyUzhi][6]+=1; 
            Pt2Uzhi[NPt2Uzhi][6]+=1;
         };
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	de += e;

	//	delete sec;       	 
        delete aChange->GetSecondary(i);

      } //     end of the loop on particles
//+++++++++++++++++ Store after each event ++++++++++++++++++++++++++++++

      if(n == 2) Ninelast--;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      if(verbose > 0) 
        G4cout << "Energy/Momentum balance= " << labv << G4endl;

      aChange->Clear();

      if(verbose > 0) 
      { 
       G4cout << "End event =====================================" <<Plab<< G4endl; // Uzhi
       G4int Uzhi_i;                                                        // Uzhi
       G4cin >> Uzhi_i;                                                     // Uzhi
      }
//

    }   // End of the event loop ------------------------------------

    timer->Stop();
    G4cout << "  "  << *timer << G4endl;
    delete timer;

//++++++++++++++++++++++ After each energy run ++++++++++++++++++++++++++
G4cout<< "***********************************************************"<< G4endl;

G4cout<<"nevt Ninel "<<nevt<<" "<<Ninelast<<G4endl;
G4cout<<"Plab "<<Plab/GeV<<" SigIn "<<sigIn<<G4endl;
//-------------------------------------------------------------------


    if(verbose > 0) {
      G4cout << "###### End of run # " << run << "     ######" << G4endl;
    }
//++++++++++++++++++++++ After each energy run ++++++++++++++++++++++++++ Uzhi 

//sigTot=sigTot; sigEl=sigEl;

// ----------------------------- Momentum distributions----------------------
    G4cout<< "******** Energy distr ******* at Plab "<<Plab<<" Xin " << sigIn<< G4endl;
    PbDNeRest<<G4Version<<G4endl;
    PbDNeRest<<" Energy     Prot     Pion "<< G4endl;

    for(G4int ii=0; ii <110; ii++)
    {for(G4int jj=0;jj < 2; jj++){EnerUzhi[ii][jj]*=1./Ninelast/12.;}} //sigIn/12.     
                                                                           
    G4double Tkin=-6;                                                     
    for(G4int ii=0; ii <110; ii++)
    { 
     Tkin+=12.; 
     PbDNeRest<<Tkin<<"     "; 
     for(G4int jj=0;jj < 2; jj++){PbDNeRest << EnerUzhi[ii][jj]<<"     ";}
     PbDNeRest<<G4endl;
    }  


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Uzhi 
//    G4cerr << "###### End of run # " << run << "     ######" << G4endl;

  } while(end);
  }  // End of job ----------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  delete pFrame;
//  delete lFrame;
//  delete sFrame;
  delete mate;
  delete fin;
  delete phys;
  partTable->DeleteAllParticles();

  G4cout << "###### End of test #####" << G4endl;
}
