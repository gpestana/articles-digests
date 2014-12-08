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
// $Id: Tst12RunAction.cc 71210 2013-06-12 10:08:29Z gcosmo $
//

#include "Tst12RunAction.hh"

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"

Tst12RunAction::Tst12RunAction()
{
   runTimer = new G4Timer;
}

Tst12RunAction::~Tst12RunAction()
{
   delete runTimer;
}

void Tst12RunAction::BeginOfRunAction(const G4Run* )
{
   runTimer->Start();
}

void Tst12RunAction::EndOfRunAction(const G4Run*)
{
   runTimer->Stop();
   G4double userTime(0.0) , wallTime(0.0);
   G4cout << "   time(s) spent "; 
   if ( runTimer->IsValid() ) {
      userTime = runTimer->GetUserElapsed();
      wallTime = runTimer->GetRealElapsed();
      G4cout << "user  time: " << userTime << "s"
             << ", wall time: "<< wallTime << "s"
	     << G4endl;
  } else {
      G4cout << "UNDEFINED" << G4endl;;
  }

}

