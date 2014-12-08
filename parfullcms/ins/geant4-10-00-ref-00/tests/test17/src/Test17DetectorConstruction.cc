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
//      ---------- Test17DetectorConstruction -------
//
//                by Vladimir Ivanchenko, 23 July 1999
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "Test17DetectorConstruction.hh"
#include "Test17DetectorMessenger.hh"

#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

Test17DetectorConstruction::Test17DetectorConstruction():
  AbsorberMaterial(0),
  WorldMaterial(0),
  defaultWorld(true),
  solidWorld(0),
  logicWorld(0),
  physiWorld(0),
  solidAbsorber(0),
  logicAbsorber(0),
  physiAbsorber(0),
  magField(0)
{
  // default parameter values of the calorimeter
  AbsorberThickness = 100.0*mm;
  AbsorberSizeYZ    = 10.*cm;
  XposAbs           = 0.*cm ;
  NumberOfAbsorbers = 1;

  // create commands for interactive definition of the calorimeter
  detectorMessenger = new Test17DetectorMessenger(this);
  DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

Test17DetectorConstruction::~Test17DetectorConstruction()
{
  delete detectorMessenger;
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* Test17DetectorConstruction::Construct()
{
  return ConstructCalorimeter();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test17DetectorConstruction::DefineMaterials()
{
  //This function illustrates the possible ways to define materials

  G4String name, symbol;             //a=mass of a mole;
  G4double a, z, density;            //z=mean number of protons;

  G4int    ncomponents, natoms;
  G4double fractionmass;

  //
  // define Elements
  //

  a = 1.01*g/mole;
  G4Element* elH  = new G4Element(name="Hydrogen",symbol="H" , z= 1., a);

  a = 14.01*g/mole;
  G4Element* elN  = new G4Element(name="Nitrogen",symbol="N" , z= 7., a);

  a = 16.00*g/mole;
  G4Element* elO  = new G4Element(name="Oxygen"  ,symbol="O" , z= 8., a);

  a = 12.00*g/mole;
  G4Element* elC  = new G4Element(name="Carbon"  ,symbol="C" , z= 6., a);

  //
  // define simple materials
  //
  density = 1.848*g/cm3;
  a = 9.01*g/mole;
  G4Material* Be = new G4Material(name="Beryllium", z=4., a, density);
  G4cout << "Material available: " << Be->GetName() << G4endl;

  density = 2.700*g/cm3;
  a = 26.98*g/mole;
  G4Material* Al = new G4Material(name="Aluminum", z=13., a, density);
  G4cout << "Material available: " << Al->GetName() << G4endl;

  density = 2.0*g/cm3;
  a = 12.0107*g/mole;
  G4Material* C = new G4Material(name="Carbon", z=6., a, density);
  G4cout << "Material available: " << C->GetName() << G4endl;

  density = 2.330*g/cm3;
  a = 28.09*g/mole;
  G4Material* Si = new G4Material(name="Silicon", z=14., a, density);
  G4cout << "Material available: " << Si->GetName() << G4endl;

  density = 1.390*g/cm3;
  a = 39.95*g/mole;
  G4Material* lAr = new G4Material(name="liquidArgon", z=18., a, density);
  G4cout << "Material available: " << lAr->GetName() << G4endl;

  density = 3.02*g/cm3;
  a = 131.29*g/mole;
  G4Material* lXe = new G4Material(name="liquidXenon", z=54., a, density);
  G4cout << "Material available: " << lXe->GetName() << G4endl;

  density = 7.870*g/cm3;
  a = 55.85*g/mole;
  G4Material* Fe = new G4Material(name="Iron"   , z=26., a, density);
  G4cout << "Material available: " << Fe->GetName() << G4endl;

  density = 8.960*g/cm3;
  a = 63.55*g/mole;
  G4Material* Cu = new G4Material(name="Copper"   , z=29., a, density);
  G4cout << "Material available: " << Cu->GetName() << G4endl;

  density = 19.32*g/cm3;
  a =196.97*g/mole;
  G4Material* Au = new G4Material(name="Gold"   , z=79., a, density);
  G4cout << "Material available: " << Au->GetName() << G4endl;

  density = 11.35*g/cm3;
  a = 207.19*g/mole;
  G4Material* Pb = new G4Material(name="Lead"     , z=82., a, density);
  G4cout << "Material available: " << Pb->GetName() << G4endl;

  //
  // define a material from elements.   case 1: chemical molecule
  //

  density = 1.000*g/cm3;
  G4Material* H2O = new G4Material("Water", density, ncomponents=2);
  H2O->SetChemicalFormula("H_2O");
  H2O->AddElement(elH, natoms=2);
  H2O->AddElement(elO, natoms=1);
  G4cout << "Material available: " << H2O->GetName() << G4endl;

  density = 0.00066715*g/cm3;
  G4Material* CH4 = new G4Material("Methane", density, ncomponents=2);
  CH4->SetChemicalFormula("CH_4");
  CH4->AddElement(elH, natoms=4);
  CH4->AddElement(elC, natoms=1);
  G4cout << "Material available: " << CH4->GetName() << G4endl;

  G4Material*  Graphite = new G4Material("Graphite", 2.265*g/cm3, ncomponents=1);
  Graphite->SetChemicalFormula("Graphite");
  Graphite->AddElement( elC, 1 );
  G4cout << "Material available: " << Graphite->GetName() << G4endl;

  //
  // define a material from elements.   case 2: mixture by fractional mass
  //

  density = 1.290*mg/cm3;
  G4Material* Air = new G4Material(name="Air"  , density, ncomponents=2);
  Air->AddElement(elN, fractionmass=0.7);
  Air->AddElement(elO, fractionmass=0.3);

  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  //default materials of the calorimeter
  AbsorberMaterial = H2O;
  WorldMaterial    = Air;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* Test17DetectorConstruction::ConstructCalorimeter()
{
  // complete the Calor parameters definition and Print
  ComputeCalorParameters();

  //
  // World
  //
  solidWorld = new G4Box("World",				//its name
			 WorldSizeX/2.0,                        //its size X
                         WorldSizeYZ/2.0,WorldSizeYZ/2.0);      //its size YZ

  logicWorld = new G4LogicalVolume(solidWorld,		//its solid
                                   WorldMaterial,	//its material
                                   "World");		//its name

  physiWorld = new G4PVPlacement(0,			//no rotation
  				 G4ThreeVector(),	//no moving
                                 "World",		//its name
                                 logicWorld,		//its logical volume
                                 0,			//its mother  volume
                                 false,			//no boolean operation
                                 0);			//copy number
  
  //                               
  // Absorber
  // 
  solidAbsorber = new G4Box("Absorber",	
                      AbsorberThickness/2,AbsorberSizeYZ/2,AbsorberSizeYZ/2); 
                          
  logicAbsorber = new G4LogicalVolume(solidAbsorber,    //its solid
    	                  AbsorberMaterial,             //its material
   	                 "Absorber");                   //its name
      			                  
  G4int copyNo=0;
  G4double x ;

  for (G4int j=0; j<NumberOfAbsorbers; j++)
  {
    x = XposAbs + AbsorberThickness * (G4double(j) + 0.5) ; 
    physiAbsorber = new G4PVPlacement(0,	   //no rotation
      		  G4ThreeVector(x,0.0,0.0),        //its position
                                "Absorber",        //its name
                                logicAbsorber,     //its logical volume
                                physiWorld,        //its mother
                                false,             //no boulean operat
                                copyNo);           //copy number
  }
  
  //                               
  // Sensitive Detectors: Absorber 
  //
  /*
  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  calorimeterSD = new Test17CalorimeterSD("CalorSD",this);
  SDman->AddNewDetector( calorimeterSD );
  logicAbsorber->SetSensitiveDetector(calorimeterSD);
  */  
  
  //
  //always return the physical World
  //
  PrintCalorParameters();  
  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test17DetectorConstruction::PrintCalorParameters()
{
  G4cout << "\n The  WORLD   is made of "
         << G4BestUnit(WorldSizeX,"Length") << " of " << WorldMaterial->GetName();
  G4cout << ". The transverse size (YZ) of the world is "
         << G4BestUnit(WorldSizeYZ,"Length") << G4endl;
  G4cout << " The ABSORBER is made of " << NumberOfAbsorbers << " items of "
         <<G4BestUnit(AbsorberThickness,"Length")<< " of " << AbsorberMaterial->GetName();
  G4cout << ". The transverse size (YZ) is "
         << G4BestUnit(AbsorberSizeYZ,"Length") << G4endl;
  G4cout << " X position of the middle of the absorber " << G4BestUnit(XposAbs,"Length");
  G4cout << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test17DetectorConstruction::SetAbsorberMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
  if (pttoMaterial)
     {AbsorberMaterial = pttoMaterial;
      if(logicAbsorber) logicAbsorber->SetMaterial(pttoMaterial);
      PrintCalorParameters();
     }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test17DetectorConstruction::SetWorldMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
  if (pttoMaterial)
     {WorldMaterial = pttoMaterial;
      if(logicWorld) logicWorld->SetMaterial(pttoMaterial);
      PrintCalorParameters();
     }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test17DetectorConstruction::SetNumberOfAbsorbers(G4int val)
{
  // change Absorber thickness and recompute the calorimeter parameters
  NumberOfAbsorbers = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test17DetectorConstruction::SetAbsorberThickness(G4double val)
{
  // change Absorber thickness and recompute the calorimeter parameters
  AbsorberThickness = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test17DetectorConstruction::SetAbsorberSizeYZ(G4double val)
{
  // change the transverse size and recompute the calorimeter parameters
  AbsorberSizeYZ = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test17DetectorConstruction::SetWorldSizeX(G4double val)
{
  WorldSizeX = val;
  defaultWorld = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test17DetectorConstruction::SetWorldSizeYZ(G4double val)
{
  WorldSizeYZ = val;
  defaultWorld = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test17DetectorConstruction::SetAbsorberXpos(G4double val)
{
  XposAbs  = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test17DetectorConstruction::SetMagField(G4double fieldValue)
{
  //apply a global uniform magnetic field along Z axis
  G4FieldManager* fieldMgr
   = G4TransportationManager::GetTransportationManager()->GetFieldManager();

  if(magField) delete magField;		//delete the existing magn field

  if(fieldValue!=0.)			// create a new one if non nul
  { magField = new G4UniformMagField(G4ThreeVector(0.,0.,fieldValue));
    fieldMgr->SetDetectorField(magField);
    fieldMgr->CreateChordFinder(magField);
  } else {
    magField = 0;
    fieldMgr->SetDetectorField(magField);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Test17DetectorConstruction::UpdateGeometry()
{
    G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
