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
// $Id: RunAction.hh 72972 2013-08-14 15:18:19Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class RunActionMessenger;
class DetectorConstruction;
class PhysicsList;
class PrimaryGeneratorAction;
class G4Run;
class Histo;
class TestSeries;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RunAction : public G4UserRunAction
{
public:
  RunAction(DetectorConstruction*,
	    PrimaryGeneratorAction*);
  virtual ~RunAction();

  void BeginOfRunAction(const G4Run*);
  void   EndOfRunAction(const G4Run*);
    
  void FillTallyEdep(G4int n, G4double e)  {tallyEdep[n] += e;};
  void FillEdep(G4double de, G4double eni) {edeptot += de; eniel += eni;};
  void FillEnIncoming(G4double in) { eintot += in; nmbein++; }
  void FillEnOutgoing(G4double out) { eouttot += out; nmbeout++; }
       
  G4double GetBinLength() {return binLength;};
  G4double GetLength()    {return length;};
  G4double GetOffsetX()   {return offsetX;}
 
  void FillHisto(G4int id, G4double x, G4double weight = 1.0);
    
  void AddProjRange (G4double x) 
  {projRange += x; projRange2 += x*x; nRange++;};
  void AddPrimaryStep() {nPrimarySteps++;};

  void CreateRangeTest(G4double refRange,
                       G4double relError);
  void CreateEnergyLossTest(G4double refLoss,
                            G4double relError);
                   
private:  
  RunActionMessenger*     messenger;
    
  DetectorConstruction*   detector;
  PrimaryGeneratorAction* kinematic;
  G4double*               tallyEdep;   
  G4double                binLength;
  G4double                offsetX;
  G4double                length;
  G4double                projRange, projRange2;
  G4double                edeptot, eniel;
  G4double                eintot, eouttot;
  G4int                   nmbein, nmbeout;
  G4int                   nPrimarySteps;
  G4int                   nRange;

  Histo*                  histo;

  TestSeries*             testRange;
  TestSeries*             testEnergyLoss;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

