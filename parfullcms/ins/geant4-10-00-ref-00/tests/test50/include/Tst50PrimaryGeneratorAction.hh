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
// $Id: Tst50PrimaryGeneratorAction.hh 66892 2013-01-17 10:57:59Z gunter $
//
// Author: Susanna Guatelli (guatelli@ge.infn.it)
//
// History:
// -----------
// 17 May  2003   S. Guatelli   1st implementation
//
// -------------------------------------------------------------------
 
#ifndef Tst50PrimaryGeneratorAction_h
#define Tst50PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class G4ParticleGun;
class G4Event;
class Tst50PrimaryGeneratorMessenger; 

class Tst50PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  Tst50PrimaryGeneratorAction();    
  ~Tst50PrimaryGeneratorAction();
  void GeneratePrimaries(G4Event*);

public:
  G4double GetInitialEnergy();
  G4String GetParticle();
  void SetRandomDirection (G4String val) {randomDirection = val;}
  
private:
  G4String randomDirection;
  G4ParticleGun* particleGun;
  Tst50PrimaryGeneratorMessenger* gunMessenger; 
};
#endif










