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
// $Id: Tst50RunAction.hh 66892 2013-01-17 10:57:59Z gunter $
// 
//
//
// $Id: Tst50RunAction.hh 66892 2013-01-17 10:57:59Z gunter $
//
// Author: Susanna Guatelli (guatelli@ge.infn.it)
//
// History:
// -----------
// 17 May  2003   S. Guatelli   1st implementation
//
// -------------------------------------------------------------------

#ifndef Tst50RunAction_h
#define Tst50RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class Tst50RunMessenger;
class Tst50AnalysisManager;
class Tst50PrimaryGeneratorAction;
class Tst50DetectorConstruction;
class Tst50RunAction : public G4UserRunAction
{
  public:
    Tst50RunAction();
   ~Tst50RunAction();

  public:
  void BeginOfRunAction(const G4Run*);
  G4int GetRunID ();
  G4bool GetFlag();//returns the choice of test: transmission or 
                   //SP and CSDA range test 
  void EndOfRunAction(const G4Run*);
  void SetTransmissionTest(G4String);
  void EnergyDepositTest(G4String);
  void TransmittedGammaNumber();
  void TransmittedParticleNumber();
  void BackscatteredParticleNumber();
  void BackscatteredEnergy(G4double);

private: 
  Tst50RunMessenger* messenger;
  G4bool flag; // if true transmission test, if false SP and CSDA range
               // valid for massive particles

  G4int runID;
  G4double gammaTransmitted; //number of transmitted gamma 
  G4int numberEvents;// number of events in the BeamOn
  G4double particleTransmitted;// number of transmitted massive particles  
  G4double particleBackscattered;// number of backscattered massive particles 
  Tst50PrimaryGeneratorAction* primary;
  Tst50DetectorConstruction* detector;
  G4double backscatteredEnergy;
  
};
#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
