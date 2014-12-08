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
#ifndef HsQGSBInterface_h
#define HsQGSBInterface_h

//----------------------------------------------------------------------------
//
//  Package   : Simulation 
//
// Description: Algorithm for QGS_BIC
//
// Author:      V.Ivanchenko 05.11.07
//
// Modifications: 
//
//----------------------------------------------------------------------------
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "G4VIntraNuclearTransportModel.hh"
#include "G4TheoFSGenerator.hh"
#include "G4BinaryCascade.hh"
#include "G4QGSModel.hh"
#include "G4QGSParticipants.hh"
#include "G4QGSMFragmentation.hh"
#include "G4ExcitedStringDecay.hh"

class HsQGSBInterface : public G4VIntraNuclearTransportModel
{
public:
  HsQGSBInterface();

  virtual ~HsQGSBInterface();

  virtual G4HadFinalState* ApplyYourself(const G4HadProjectile& aTrack, 
                                                 G4Nucleus& theNucleus);

  virtual G4ReactionProductVector* Propagate(G4KineticTrackVector*,
                                               G4V3DNucleus*) {return 0;}; 
private:
  
  G4TheoFSGenerator * theModel;
  G4BinaryCascade* theCascade;
  G4QGSModel< G4QGSParticipants > theStringModel;
  G4QGSMFragmentation theFragmentation;
  G4ExcitedStringDecay * theStringDecay;
};
#endif
