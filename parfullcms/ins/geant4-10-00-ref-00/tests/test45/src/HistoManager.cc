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
// $Id: HistoManager.cc 72976 2013-08-14 15:27:29Z gcosmo $
//
//---------------------------------------------------------------------------
//
// ClassName:   HistoManager
//
//
// Author:      V.Ivanchenko 30/01/01
//
// Modified:
//
//----------------------------------------------------------------------------
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "HistoManager.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Neutron.hh"
#include "G4Proton.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "Histo.hh"
#include "G4Track.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HistoManager* HistoManager::fManager = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HistoManager* HistoManager::GetPointer()
{
  if(!fManager) {
    static HistoManager manager;
    fManager = &manager;
  }
  return fManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HistoManager::HistoManager()
{
  verbose   =  0;
  nHisto    = 12; 
  length    = 10.*mm;
  histo     = new Histo();
  neutron   = G4Neutron::Neutron();
  dangle    = 2.5*degree; 
  angle[0]  = 0.0*degree;
  angle[1]  = 15.0*degree;
  angle[2]  = 30.0*degree;
  angle[3]  = 45.0*degree;
  angle[4]  = 60.0*degree;
  angle[5]  = 90.0*degree;
  //pn-cu, pn-fe
  /*
  angle[0]  = 0.0*degree;
  angle[1]  = 30.0*degree;
  angle[2]  = 45.0*degree;
  angle[3]  = 60.0*degree;
  angle[4]  = 90.0*degree;
  angle[5]  = 110.0*degree;
  */

  // pn_al, pn_c, ta, w: 050MeV
  emin1     = -.05*MeV;
  emax1     = 5.05*MeV;
  emin2     = 5.5*MeV;
  emax2     = 50.5*MeV;
  de1       =  0.1*MeV;
  de2       =  1.0*MeV;
  nbins1    =  51;
  nbins2    =  45;
  
  // pn_cu, pn_fe 35-70 MeV + dn_be,li,other
  /*
  emin1     = 0*MeV;
  emax1     = 80*MeV;
  emin2     = 0*MeV;
  emax2     = 80*MeV;
  de1       =  1.0*MeV;
  de2       =  1.0*MeV;
  nbins1    =  80;
  nbins2    =  80;
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

HistoManager::~HistoManager()
{
  delete histo;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::bookHisto()
{
  for(G4int i=0; i<6; i++) {
    G4String sss;
    G4String I;
    std::ostringstream ss;
    std::ostringstream II;
    ss << angle[i];
    II << (i+1);
    sss = ss.str();
    I = II.str();
    angle[i]=angle[i]*degree;
    G4String S = " neutron yield at " + sss + " degree in the target ";
    histo->Add1D(I,S,nbins1,emin1,emax1,1.0);
  }
  for(G4int i=0; i<6; i++) {
    G4String sss;
    G4String I;
    std::ostringstream ss;
    std::ostringstream II;
    ss << angle[i];
    II << (i+7);
    sss = ss.str();
    I = II.str();
    angle[i]=angle[i]*degree;
    G4String S = " neutron yield at " + sss + " degree in the target ";
    histo->Add1D(I,S,nbins2,emin2,emax2,1.0);
  }
  // pn_al
 
  histo->Add1D("1"," low-energy neutron yield at 0 degree in the target",
	       nbins1,emin1,emax1,1.0);
  histo->Add1D("2"," low-energy neutron yield at 15 degree in the target",
	       nbins1,emin1,emax1,1.0);
  histo->Add1D("3"," low-energy neutron yield at 30 degree in the target",
	       nbins1,emin1,emax1,1.0);
  histo->Add1D("4"," low-energy neutron yield at 45 degree in the target",
	       nbins1,emin1,emax1,1.0);
  histo->Add1D("5"," low-energy neutron yield at 60 degree in the target",
	       nbins1,emin1,emax1,1.0);
  histo->Add1D("6"," low-energy neutron yield at 90 degree in the target",
	       nbins1,emin1,emax1,1.0);

  histo->Add1D("7"," neutron yield at 0 degree in the target",
	       nbins2,emin2,emax2,1.0);
  histo->Add1D("8"," neutron yield at 15 degree in the target",
	       nbins2,emin2,emax2,1.0);
  histo->Add1D("9"," neutron yield at 30 degree in the target",
	       nbins2,emin2,emax2,1.0);
  histo->Add1D("10"," neutron yield at 45 degree in the target",
	       nbins2,emin2,emax2,1.0);
  histo->Add1D("11"," neutron yield at 60 degree in the target",
	       nbins2,emin2,emax2,1.0);
  histo->Add1D("12"," neutron yield at 90 degree in the target",
	       nbins2,emin2,emax2,1.0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::BeginOfRun()
{
  n_evt       = 0;

  histo->SetVerbose(verbose);
  bookHisto();
  histo->Book();

  if(verbose > 0) 
    G4cout << "HistoManager: Histograms are booked and run has been started"
           <<G4endl<<"  BeginOfRun (After histo->book)"<< G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::EndOfRun()
{

  G4cout << "HistoManager: End of run actions are started" << G4endl;

  // Average values
  G4cout<<"========================================================"<<G4endl;

  G4double x = (G4double)n_evt;
  if(n_evt > 0) x = 1.0/x;

  G4cout                         << "Beam particle                        "
				 << primaryDef->GetParticleName() <<G4endl;
  G4cout                         << "Beam Energy(MeV)                     " 
				 << primaryKineticEnergy/MeV <<G4endl;
  G4cout                         << "Number of events                     " << n_evt <<G4endl;
  G4cout<<"========================================================"<<G4endl;
  G4cout<<G4endl;

  // normalise histograms
  G4double fac = 1.0e-6*coulomb*MeV*x/twopi; //### factor= 99336659
  //G4double fac = 1.0e+13*MeV*x/twopi;

  G4cout << "### factor= " << fac << G4endl;

  for(G4int i=0; i<6; i++) {
    G4double a1 = angle[i] - dangle; 
    G4double a2 = angle[i] + dangle;
    if(a1 < 0.0) a1 = 0.0; 
    G4double fact = fac/(std::cos(a1) - std::cos(a2));
    histo->ScaleH1(i,fact/de1);
    histo->ScaleH1(i+6,fact/de2);
  }

  histo->Save();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::BeginOfEvent()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::EndOfEvent()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::ScoreNewTrack(const G4Track* track)
{
  const G4ParticleDefinition* pd = track->GetDefinition();
  G4double e = track->GetKineticEnergy();

  // Primary track
  if(0 == track->GetParentID()) {

    n_evt++;
    primaryKineticEnergy = e;
    primaryDef = pd;
    
  } else if(pd == neutron) {
    G4ThreeVector dir = track->GetMomentumDirection();
    G4int idx = IndexTheta(dir.theta());
    if(idx >= 0) {
      if(e <= emax1) histo->Fill(idx, e, 1.0);
      if(e >= emin2) histo->Fill(idx+6, e, 1.0);
    }
    
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::AddLeakingParticle(const G4Track* track)
{
  const G4ParticleDefinition* pd = track->GetDefinition();

  if(pd == neutron) {
    /*
    G4double e = track->GetKineticEnergy();
    G4ThreeVector dir = track->GetMomentumDirection();
    G4int idx = IndexTheta(dir.theta());
    if(idx >= 0) {
      if(e <= emax1) histo->Fill(idx, e, 1.0);
      if(e >= emin2) histo->Fill(idx+6, e, 1.0);
    }
    */
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::SetVerbose(G4int val)        
{
  verbose = val; 
  histo->SetVerbose(val);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void HistoManager::Fill(G4int id, G4double x, G4double w)
{
  histo->Fill(id, x, w);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4int HistoManager::IndexTheta(G4double theta)
{
  G4int idx = 0;
  for(; idx<6; idx++) {
    if(std::abs(theta - angle[idx]) <= dangle) return idx;
  }
  return -1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

  //G4double fac = 1./1.602176487e-07; //### factor= 6241509.6
  //G4double fac = 1./1.602176487e-13; //### factor= 6.2415096e+12
  //G4double fac = (1.0e-6)*coulomb; //### factor= 6.2415064e+15
  //G4double fac = 1.0e+6/coulomb; //### factor= 1.6021773e-13
  //G4double fac = 1.0e+13*MeV*x/twopi; //### factor= 1.5915494e+08
