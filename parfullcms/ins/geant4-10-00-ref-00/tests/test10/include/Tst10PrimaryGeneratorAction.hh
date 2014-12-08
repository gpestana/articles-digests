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
// $Id: Tst10PrimaryGeneratorAction.hh 66892 2013-01-17 10:57:59Z gunter $
// ------------------------------------------------------------
//	GEANT 4 class header file 
//
//      This class is a class derived from G4VUserPrimaryGeneratorAction
//      for constructing all particles and processes.
//
//	History
//        first version              09 Sept. 1998 by S.Magni
// ------------------------------------------------------------

#ifndef Tst10PrimaryGeneratorAction_h
#define Tst10PrimaryGeneratorAction_h 1

#include "G4ThreeVector.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;
class G4Event;
class Tst10DetectorConstruction;


class Tst10PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    Tst10PrimaryGeneratorAction(Tst10DetectorConstruction*);
    ~Tst10PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);
  private:
    G4ParticleGun* particleGun;
		G4ThreeVector GetRandomPolarization( G4ThreeVector direction );
		G4ThreeVector GetRandomDirection( );
		G4ThreeVector GetRandomPosition( );
  Tst10DetectorConstruction* fDetector;
};

#endif


