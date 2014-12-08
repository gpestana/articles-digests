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
// This example is provided by the Geant4-DNA collaboration
// Any report or published results obtained using the Geant4-DNA software 
// shall cite the following Geant4-DNA collaboration publication:
// Med. Phys. 37 (2010) 4692-4708
// The Geant4-DNA web site is available at http://geant4-dna.org
//

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "TrackingAction.hh"
#include "G4RunManager.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "TrackingAction.hh"
#include "StackingAction.hh"
#include "ReactionAction.hh"
#include "G4AllITManager.hh"
#include "G4ITStepManager.hh"
#include "G4DNAChemistryManager.hh"
#include "ITTrackingInteractivity.hh"
#include "ITSteppingAction.hh"
#include "ITTrackingAction.hh"

#include "G4DNAMolecularStepByStepModel.hh"
#include "G4DNASmoluchowskiReactionModel.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4Threading.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization()
: G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
	// In MT mode, to be clearer, the RunAction class for the master thread might be
	// different than the one used for the workers.
	// This RunAction will be called before and after starting the
	// workers.
	// For more details, please refer to :
	// https://twiki.cern.ch/twiki/bin/view/Geant4/Geant4MTForApplicationDevelopers
	//
	// RunAction* runAction= new RunAction();
	// SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
	// G4cout << "Build for = "<< G4RunManager::GetRunManager()->GetRunManagerType() << G4endl;

	PrimaryGeneratorAction* primGenAction = new PrimaryGeneratorAction;
	SetUserAction(primGenAction);

    //------------------------------------------------------------------
    // Set optional user action classes

	bool chemistryFlag = G4DNAChemistryManager::Instance()->IsChemistryActived();

    SetUserAction(new RunAction());
    SetUserAction(new TrackingAction());
    SetUserAction(new SteppingAction(primGenAction));
    SetUserAction(new StackingAction());
    if(chemistryFlag)
    {
//    	G4cout << "OK" << G4Threading::G4GetThreadId()<< G4endl;
//    	G4Exception("","",FatalException,"");
        G4ITStepManager::Instance()->SetUserAction(new ReactionAction());
        G4ITStepManager::Instance()->SetVerbose(1);

        ITTrackingInteractivity* itInteractivity = new ITTrackingInteractivity();
        itInteractivity ->SetUserAction(new ITSteppingAction);
        itInteractivity ->SetUserAction(new ITTrackingAction);
        G4ITStepManager::Instance()->SetInteractivity(itInteractivity);

    	//__________________________________________________________________
    	std::map<double,double>* steps = new std::map<double, double> ;

    	/**
    	 * Give to G4ITStepManager the user defined time steps
    	 * eg : from 1 picosecond to 10 picosecond, the minimum time
    	 * step that the TimeStepper can returned is 0.1 picosecond.
    	 * Those time steps are used for the chemistry of G4DNA
    	 */

    	(*steps)[1*picosecond] = 0.1*picosecond;
    	(*steps)[10*picosecond] = 1*picosecond;
    	(*steps)[100*picosecond] = 3*picosecond;
    	(*steps)[1000*picosecond] = 10*picosecond;
    	(*steps)[10000*picosecond] = 100*picosecond;

    	G4ITStepManager::Instance()-> SetTimeSteps(steps);
    	G4ITStepManager::Instance()->Initialize();
    }

    G4String fileName ("output");

    if(G4RunManager::GetRunManager()->GetRunManagerType() == G4RunManager::sequentialRM)
    {
    	// write initial situation at 1 picosecond
    	G4DNAChemistryManager::Instance()->WriteInto(fileName + ".txt");
    }
    else
    {
    	G4int id = G4Threading::G4GetThreadId();

    	G4String fileName_mt = fileName;
    	fileName_mt += G4UIcommand::ConvertToString(id);
    	fileName_mt += ".txt";

    	G4cout << "chosen file name : " << fileName_mt << G4endl;
    	// G4Exception("","",FatalException,"");

    	G4DNAChemistryManager::Instance()->WriteInto(fileName_mt);
    }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
