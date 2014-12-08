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
// $Id: Tst33MaterialFactory.cc 66358 2012-12-18 09:07:19Z gcosmo $
// GEANT4 tag 
//
// ----------------------------------------------------------------------
// GEANT 4 class source file
//
// Tst33MaterialFactory.cc
//
// ----------------------------------------------------------------------

#include "Tst33MaterialFactory.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4Material.hh"

Tst33MaterialFactory::Tst33MaterialFactory(){

  G4String name, symbol;

  FillElementMap("Hydrogen", "H", 1, 1.01*g/mole);
  FillElementMap("Carbon", "C", 6, 12.01*g/mole);
  FillElementMap("Oxygen", "O", 8,  16.00*g/mole);
  FillElementMap("Natrium", "Na", 11, 22.99*g/mole);
  //  FillElementMap("Hg", "Hg", 80, 200.59*g/mole);
  FillElementMap("Aluminium", "Al", 14, 26.98*g/mole);
  FillElementMap("Silicon", "Si", 14, 28.09*g/mole);
  FillElementMap("K", "K", 19, 39.1*g/mole);
  FillElementMap("Calzium", "Ca", 31, 69.72*g/mole);
  FillElementMap("Iron", "Fe", 26, 55.85*g/mole);

  fConcreteFractions[fMapSymbolElement["H"]] = 0.01;
  fConcreteFractions[fMapSymbolElement["O"]] = 0.529;
  fConcreteFractions[fMapSymbolElement["Na"]] = 0.016;
  //  fConcreteFractions[fMapSymbolElement["Hg"]] = 0.002 ;
  fConcreteFractions[fMapSymbolElement["Al"]] = 0.034;
  fConcreteFractions[fMapSymbolElement["Si"]] = 0.337 + 0.002;
  fConcreteFractions[fMapSymbolElement["K"]] = 0.013;
  fConcreteFractions[fMapSymbolElement["Ca"]] = 0.044;
  fConcreteFractions[fMapSymbolElement["Fe"]] = 0.014;
  fConcreteFractions[fMapSymbolElement["C"]] = 0.001;

}

Tst33MaterialFactory::~Tst33MaterialFactory(){
}

void Tst33MaterialFactory::FillElementMap(const G4String &name, 
				   const G4String &symbol,
				   G4int Z,
				   G4double A) {
  Tst33MapSymbolElement::iterator it = fMapSymbolElement.find(symbol);
  if (it!=fMapSymbolElement.end()) {
    G4cout << "Tst33MaterialFactory::FillElementMap: symbol: " 
	   << symbol << ", already defined" << G4endl;
  }
  else {
    fMapSymbolElement[symbol] = new G4Element(name, symbol, Z, A);
    if (!fMapSymbolElement[symbol]) {
      G4Exception("Tst33MaterialFactory::FillElementMap()", "TST33-05", 
                   FatalException, " new failed to create G4Element!");
    }
  }
  return;
}

G4Material *Tst33MaterialFactory::CreateConcrete(){
  G4double density = 2.03*g/cm3;
  G4Material* Concrete = 0;
  Concrete = new G4Material("Concrete", density, 
			    fConcreteFractions.size());
  for (Tst33MapElementFraction::iterator it = fConcreteFractions.begin();
       it != fConcreteFractions.end(); ++it) {
    Concrete->AddElement(it->first , it->second);
  }

  return Concrete;

}

G4Material *Tst33MaterialFactory::CreateLightConcrete(){
  G4double density = 0.0203*g/cm3;
  G4Material* LightConcrete = 0;
  LightConcrete = new G4Material("LightConcrete", density, 
				 fConcreteFractions.size());
  for (Tst33MapElementFraction::iterator it = fConcreteFractions.begin();
       it != fConcreteFractions.end(); ++it) {
    LightConcrete->AddElement(it->first , it->second);
  }
  return LightConcrete;
}

G4Material *Tst33MaterialFactory::CreateGalactic(){
  G4double density = universe_mean_density;  //from PhysicalConstants.h
  G4double pressure    = 3.e-18*pascal;
  G4double temperature = 2.73*kelvin;
  return  new G4Material("Galactic", 1., 1.01*g/mole, density,
			 kStateGas,temperature,pressure);
}

