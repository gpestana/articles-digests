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

// ==============================
// PHYSICS PROCESSES:
// ==============================
//  Electromagnetic processes for: 
//      photons
//     
// 
// ==============================
// COMMENTS:
// ==============================
//  The considered processes are G4LivermorePhotoElectric, G4LivermoreCompton
//  G4LivermoreGammaConversion and G4LivermoreRayleigh (Low Energy Package, 
//  EEDL libraries)
//

#ifndef EMPHOTONEPDL_HH
#define EMPHOTONEPDL_HH 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"


class EMPhotonEPDL : public G4VPhysicsConstructor {

 public: 
   EMPhotonEPDL(const G4String& name = "Photon-EPDL"); 
   virtual ~EMPhotonEPDL();
  
 protected:
   void ConstructParticle() {};
   void ConstructProcess();
};

#endif // EMPHOTONEPDL_HH








