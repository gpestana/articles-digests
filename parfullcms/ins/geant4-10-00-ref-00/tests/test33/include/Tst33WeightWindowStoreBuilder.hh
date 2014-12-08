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
// $Id: Tst33WeightWindowStoreBuilder.hh 77733 2013-11-27 17:51:42Z gcosmo $
// GEANT4 tag 
//
// ----------------------------------------------------------------------
// Class Tst33WeightWindowStoreBuilder
//
// Class description:
// Creats the importance store and sets the importance
// values. 
// 

// Author: Michael Dressel (Michael.Dressel@cern.ch)
// ----------------------------------------------------------------------

#ifndef Tst33WeightWindowStoreBuilder_hh
#define Tst33WeightWindowStoreBuilder_hh Tst33WeightWindowStoreBuilder_hh

#include "globals.hh"

class G4WeightWindowStore;
class Tst33VGeometry;

class Tst33WeightWindowStoreBuilder {
public:
  Tst33WeightWindowStoreBuilder();
  ~Tst33WeightWindowStoreBuilder();
  G4WeightWindowStore *CreateWeightWindowStore(Tst33VGeometry *samplegeo, G4bool paraFlag);  
};


#endif
