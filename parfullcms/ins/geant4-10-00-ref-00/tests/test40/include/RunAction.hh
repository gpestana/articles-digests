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
// $Id: RunAction.hh 74728 2013-10-21 08:45:03Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// 08.03.01 Hisaya: Adapted MyVector for STL   

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"

#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4DataVector.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction;
class PrimaryGeneratorAction;

class G4Run;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RunAction : public G4UserRunAction
{
public:

  RunAction(DetectorConstruction*, PrimaryGeneratorAction*);
  virtual ~RunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);

  inline void AddWorkerRunAction(RunAction*);

  inline void initializePerEvent();
         void fillPerEvent();
  inline void fillPerTrack(G4double,G4double);
  inline void fillPerStep (G4double,G4int,G4int);
  inline void particleFlux(G4ParticleDefinition*,G4int);

private:

  void Reset();

  DetectorConstruction*   Det;
  PrimaryGeneratorAction* Kin;

  std::vector<RunAction*> runActions;

  G4int NbOfEvents;

  G4int nLbin;
  G4DataVector dEdL;
  G4DataVector sumELongit;
  G4DataVector sumE2Longit;
  G4DataVector sumELongitCumul;
  G4DataVector sumE2LongitCumul;

  G4int nRbin;
  G4DataVector dEdR;
  G4DataVector sumERadial;
  G4DataVector sumE2Radial;
  G4DataVector sumERadialCumul;
  G4DataVector sumE2RadialCumul;

  G4DataVector gammaFlux;
  G4DataVector electronFlux;
  G4DataVector positronFlux;
  
  G4double ChargTrLength;
  G4double sumChargTrLength;
  G4double sum2ChargTrLength;

  G4double NeutrTrLength;
  G4double sumNeutrTrLength;
  G4double sum2NeutrTrLength;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void RunAction::AddWorkerRunAction(RunAction* run)
{
  runActions.push_back(run);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void RunAction::initializePerEvent()
{
  //initialize arrays of energy deposit per bin
  for (G4int i=0; i<nLbin; i++)
     { dEdL[i] = 0.; }
     
  for (G4int j=0; j<nRbin; j++)
     { dEdR[j] = 0.; }     
  
  //initialize tracklength 
  ChargTrLength = NeutrTrLength = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline
void RunAction::fillPerTrack(G4double charge, G4double trkLength)
{
  if (charge != 0.) { ChargTrLength += trkLength; }
  else              { NeutrTrLength += trkLength; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline
void RunAction::fillPerStep(G4double dEstep, G4int Lbin, G4int Rbin)
{
  if(Lbin<nLbin && Lbin>=0) { dEdL[Lbin] += dEstep; }
  if(Rbin<nRbin && Rbin>=0) { dEdR[Rbin] += dEstep; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline
void RunAction::particleFlux(G4ParticleDefinition* particle, G4int Lplan)
{
  if(Lplan<nLbin && Lplan>=0) { 
         if (particle == G4Gamma::Gamma())          gammaFlux[Lplan]+=1.0;
    else if (particle == G4Electron::Electron()) electronFlux[Lplan]+=1.0;
    else if (particle == G4Positron::Positron()) positronFlux[Lplan]+=1.0;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif

