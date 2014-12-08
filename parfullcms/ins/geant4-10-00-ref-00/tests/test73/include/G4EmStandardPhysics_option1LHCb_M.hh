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
// $Id: G4EmStandardPhysics_option1LHCb_M.hh 68793 2013-04-05 13:21:59Z gcosmo $
//
//---------------------------------------------------------------------------
//
// ClassName:   G4EmStandardPhysics_option1LHCb_M
//
// Author:      V.Ivanchenko 29.06.2011
//
// Modified:
//
//----------------------------------------------------------------------------
//
// This class provides construction of EM standard physics using set of options
// allowing speed up simulation. Results for simulation of energy deposition 
// in thin layers of materials with different density may be biased.
// WentzelVI model of multiple scattering is used for all particles 
//

#ifndef G4EmStandardPhysics_option1LHCb_M_h
#define G4EmStandardPhysics_option1LHCb_M_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4EmStandardPhysics_option1LHCb_M : public G4VPhysicsConstructor
{
public:

  G4EmStandardPhysics_option1LHCb_M(G4int ver = 1, bool applyCut = true,
                                  bool newForElectrons = true);

  virtual ~G4EmStandardPhysics_option1LHCb_M();

  virtual void ConstructParticle();
  virtual void ConstructProcess();

private:
  G4int  verbose;
  bool   applyCut;
  bool   newForElectrons;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif






