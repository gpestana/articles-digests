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
// $Id: StackingAction.hh 66512 2012-12-19 10:26:52Z gcosmo $
//
/////////////////////////////////////////////////////////////////////////
//
// StackingAction
//
// Created: 31.04.2006 V.Ivanchenko
//
// Modified:
// 04.06.2006 Adoptation of hadr01 (V.Ivanchenko)
//
////////////////////////////////////////////////////////////////////////
// 

#ifndef StackingAction_h
#define StackingAction_h 1

#include "G4UserStackingAction.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include <vector>

class HistoManager;
class StackingMessenger;
class G4Track;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class StackingAction : public G4UserStackingAction
{
public:

  StackingAction();
  virtual ~StackingAction();
   
  void ActivateSecondaryBiasing(const G4String& pname, G4double f, G4double e);

  inline void SetKillStatus(G4bool value)    { killSecondary = value; };
  inline void SetKill(const G4String& name)  { pname = name; };
     
  G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);
    
private:

  HistoManager*       histoManager;    
  StackingMessenger*  stackMessenger;

  G4String            pname;
  G4bool              killSecondary;

  G4int               nBiased;
  std::vector<G4ParticleDefinition*> biasedParticle;
  std::vector<G4double> rrProbability;
  std::vector<G4double> biasedEnergy;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

