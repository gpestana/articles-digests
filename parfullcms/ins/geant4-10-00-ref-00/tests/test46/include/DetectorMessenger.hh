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
// $Id: DetectorMessenger.hh 66512 2012-12-19 10:26:52Z gcosmo $
//
/////////////////////////////////////////////////////////////////////////
//
// DetectorMessenger
//
// Created: 31.01.03 V.Ivanchenko
//
// Modified:
//
////////////////////////////////////////////////////////////////////////
//

#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADouble;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorMessenger: public G4UImessenger
{
public:

  DetectorMessenger(DetectorConstruction* );
  virtual ~DetectorMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:

  DetectorConstruction* Detector;

  G4UIdirectory*             testDir;
  G4UIcmdWithAString*        matCmd;
  G4UIcmdWithAString*        mat1Cmd;
  G4UIcmdWithAString*        mat2Cmd;
  G4UIcmdWithADoubleAndUnit* bCmd;
  G4UIcmdWithADoubleAndUnit* rCmd;
  G4UIcmdWithADoubleAndUnit* eCmd;
  G4UIcmdWithADoubleAndUnit* rCmd1;
  G4UIcmdWithADoubleAndUnit* lCmd;
  G4UIcmdWithADoubleAndUnit* gCmd;
  G4UIcmdWithADoubleAndUnit* lpCmd;
  G4UIcmdWithADoubleAndUnit* gpCmd;
  G4UIcmdWithADoubleAndUnit* fCmd;
  G4UIcmdWithADouble*        facCmd1;
  G4UIcmdWithADouble*        facCmd2;
  G4UIcmdWithAnInteger*      verbCmd;
  G4UIcmdWithAnInteger*      binCmd;
  G4UIcmdWithoutParameter*   mCmd;
  G4UIcmdWithoutParameter*   updateCmd;

};
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
