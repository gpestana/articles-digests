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
// $Id:$

// Author: Ivana Hrivnacova, 22/08/2013  (ivana@ipno.in2p3.fr)

#include "G4AnalysisUtilities.hh"
#include "G4BinScheme.hh"
#include "G4UnitsTable.hh"

namespace G4Analysis
{

//_____________________________________________________________________________
G4bool CheckNbins(G4int nbins)
{
  if ( nbins <= 0 ) {
    G4ExceptionDescription description;
    description 
      << "    Illegal value of number of bins: nbins <= 0" << G4endl;
      G4Exception("G4VAnalysisManager::CheckNbins",
                  "Analysis_W013", JustWarning, description);
    return false;
  }
  else
    return true;                   
}  


//_____________________________________________________________________________
G4bool CheckMinMax(G4double xmin, G4double xmax, const G4String& binSchemeName)
{
  G4bool result = true;
  
  if ( xmax <= xmin ) {
    G4ExceptionDescription description;
    description 
      << "    Illegal values of (xmin >= xmax)" << G4endl;
      G4Exception("G4VAnalysisManager::CheckMinMax",
                  "Analysis_W013", JustWarning, description);
                  
    result = false;
  }
  
  if ( ( GetBinScheme(binSchemeName) == kLogBinScheme ) && ( xmin == 0 ) ) {
    G4ExceptionDescription description;
    description 
      << "    Illegal value of (xmin = 0) with logarithmic binning" << G4endl;
      G4Exception("G4VAnalysisManager::CheckMinMax",
                  "Analysis_W013", JustWarning, description);
                  
    result = false;
  }
  
  return result;
}  

//_____________________________________________________________________________
G4bool CheckEdges(const std::vector<G4double>& edges)
{
  if ( edges.size() <= 1 ) {
    G4ExceptionDescription description;
    description 
      << "    Illegal edges vector (size <= 1)" << G4endl;
      G4Exception("G4VAnalysisManager::CheckEdges",
                  "Analysis_W013", JustWarning, description);
    return false;
  }
  else
    return true;                   

}

//_____________________________________________________________________________
G4double GetUnitValue(const G4String& unit)
{
   G4double value = 1.;
   if ( unit != "none" ) {
     value = G4UnitDefinition::GetValueOf(unit);
     if ( value == 0. ) value = 1.; 
   }  
   return value;
}   

//_____________________________________________________________________________
void UpdateTitle(G4String& title, 
                 const G4String& unitName, 
                 const G4String& fcnName)
{
  if ( fcnName != "none" )  { title += " "; title += fcnName; title += "("; }
  if ( unitName != "none" ) { title += " ["; title += unitName; title += "]";}
  if ( fcnName != "none" )  { title += ")"; }
}                                                            

}
