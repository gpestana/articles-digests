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
// $Id: Tst18PrimaryGeneratorAction.hh 73122 2013-08-19 07:50:52Z gcosmo $
//
//  File:        Tst18PrimaryGeneratorAction.hh
//  Description: Generator action for radioactive decay system test 
//  Author:      F. Lei (DERA UK)
//                  updated by Dennis Wright (SLAC)
//  Date:        14 August 2013
//

#ifndef Tst18PrimaryGeneratorAction_h
#define Tst18PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4IonTable.hh"
#include "RadioactiveDecayGun.hh"

class G4Event;

class Tst18PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    Tst18PrimaryGeneratorAction();
    ~Tst18PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);

  protected:

    RadioactiveDecayGun* theParticleGun;
};

#endif


