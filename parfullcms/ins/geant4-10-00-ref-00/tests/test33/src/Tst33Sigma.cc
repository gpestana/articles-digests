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
// $Id: Tst33Sigma.cc 66358 2012-12-18 09:07:19Z gcosmo $
//
// ----------------------------------------------------------------------
// GEANT 4 class source file
//
// Tst33Sigma.cc
//
// ----------------------------------------------------------------------

#include "Tst33Sigma.hh"
#include "globals.hh"
#include <cstdio>
#include <cmath>
 
Tst33Sigma::Tst33Sigma()
{
  Init();
}

Tst33Sigma::~Tst33Sigma()
{}

void Tst33Sigma::Init()
{
  fEntries = 0;
  fMean = 0.;
  fSigma = -1.;
  fXsum = 0;
  fXXsum = 0;
  fWsum = 0;
  fWXsum = 0;
  fWXXsum = 0;
  fcalc = 0;
}

G4int Tst33Sigma::Xin(G4double x, G4double w)
{
  if (w<0.) {
    Error("Xin: w < 0");
  }
  fEntries++;
  fXsum+=x;
  fXXsum+=x*x;
  fWsum += w;
  fWXsum += w*x;
  fWXXsum += w*x*x;
  fcalc = 0;
  return fEntries;
}



G4int Tst33Sigma::GetCalc() const
{
  return fcalc;
}

G4int Tst33Sigma::Calculate() const {
  if (fcalc==0) {
    if(fWsum>0) {
      fMean=fWXsum/fWsum;
      fSigma = std::sqrt( fWXXsum / fWsum - fMean * fMean);
      fcalc = 1;
    } else {
      fcalc = -1;
    }
  }
  return fcalc;
}

G4int Tst33Sigma::GetEntries() const
{
  return fEntries;
}

G4double Tst33Sigma::GetMean() const
{
  if (fcalc==0) {
    Calculate();
  }
  return fMean;
}

G4double Tst33Sigma::GetSigma() const
{
  if (fcalc==0) {
    Calculate();
  }
  return fSigma;
}

G4double Tst33Sigma::GetXsum() const {return fXsum;}
G4double Tst33Sigma::GetXXsum() const {return fXXsum;}
G4double Tst33Sigma::GetSumOfWeights() const {return fWsum;}
G4double Tst33Sigma::GetWeightedXsum() const {return fWXsum;}
G4double Tst33Sigma::GetWeightedXXsum() const {return fWXXsum;}

void Tst33Sigma::Error(const G4String &m)
{
  G4cout << "ERROR: Tst33Sigma::" << m << G4endl;
}

std::ostream& operator<<(std::ostream &out, const Tst33Sigma &s)
{
  out << "entries                             : " << s.GetEntries() << "\n";
  out << "Sum(w)                              : " << s.GetSumOfWeights()<<"\n";
  out << "Sum(w*x)                            : " << s.GetWeightedXsum() << "\n";
  out << "Sum(w*x*x)                          : " << s.GetWeightedXXsum() << "\n";
  out << "mean=Sum(w*x) / Sum(w)              : " << s.GetMean() << "\n";
  out << "sigma=std::sqrt(Sum(w*x*x)/Sum(w)-mean^2): " << s.GetSigma() << "\n";
  out << "Sum(x)                              : " << s.GetXsum() << "\n";
  out << "Sum(x^2)                            : " << s.GetXXsum() << "\n";
  
  return out;
}
