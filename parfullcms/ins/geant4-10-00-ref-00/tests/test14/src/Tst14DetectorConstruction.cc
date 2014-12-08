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
// $Id: Tst14DetectorConstruction.cc 68781 2013-04-05 13:08:56Z gcosmo $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "Tst14DetectorConstruction.hh"
#include "Tst14DetectorMessenger.hh"

#include "Tst14CalorimeterSD.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

Tst14DetectorConstruction::Tst14DetectorConstruction()
  :worldchanged(false),AbsorberMaterial(0),WorldMaterial(0),
   solidWorld(0),logicWorld(0),physiWorld(0),
   solidAbsorber(0),logicAbsorber(0),physiAbsorber(0),
   magField(0),calorimeterSD(0)
{
  // default parameter values of the calorimeter
  WorldSizeZ = 2.*m;
  WorldSizeR = 2.*m;
  AbsorberThickness = 10.*m;
  AbsorberRadius   = 10.*m;
  zAbsorber = 0.*cm ;

  // create commands for interactive definition of the calorimeter  
  detectorMessenger = new Tst14DetectorMessenger(this);
  DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

Tst14DetectorConstruction::~Tst14DetectorConstruction()
{ 
  delete detectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* Tst14DetectorConstruction::Construct()
{
  return ConstructCalorimeter();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Tst14DetectorConstruction::DefineMaterials()
{ 
  //This function illustrates the possible ways to define materials
 
  G4String name, symbol;             //a=mass of a mole;
  G4double a, z, density;            //z=mean number of protons;  

  G4int ncomponents, natoms;
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

//
// define simple materials
//
  density = 1.848*g/cm3;
  a = 9.01*g/mole;
  //G4Material* Be = 
  new G4Material(name="Beryllium", z=4., a, density);

  density = 2.700*g/cm3;
  a = 26.98*g/mole;
  //G4Material* Al = 
  new G4Material(name="Aluminium", z=13., a, density);

  density = 2.330*g/cm3;
  a = 28.09*g/mole;
  //G4Material* Si = 
  new G4Material(name="Silicon", z=14., a, density);

  density = 1.390*g/cm3;
  a = 39.95*g/mole;
  //G4Material* lAr = 
  new G4Material(name="liquidArgon", z=18., a, density);

  density = 7.870*g/cm3;
  a = 55.85*g/mole;
  //G4Material* Fe = 
  new G4Material(name="Iron"   , z=26., a, density);

  density = 8.960*g/cm3;
  a = 63.55*g/mole;
  //G4Material* Cu = 
  new G4Material(name="Copper"   , z=29., a, density);

  density = 19.32*g/cm3;
  a =196.97*g/mole;
  //G4Material* Au = 
  new G4Material(name="Gold"   , z=79., a, density);

  density = 11.35*g/cm3;
  a = 207.19*g/mole;
  G4Material* Pb = new G4Material(name="Lead"     , z=82., a, density);

//
// define a material from elements.   case 1: chemical molecule
//

  density = 1.000*g/cm3;
  G4Material* H2O = new G4Material(name="Water", density, ncomponents=2);
  H2O->AddElement(elH, natoms=2);
  H2O->AddElement(elO, natoms=1);

//
// define a material from elements.   case 2: mixture by fractional mass
//

  density = 1.290*mg/cm3;
  G4Material* Air = new G4Material(name="Air"  , density, ncomponents=2);
  Air->AddElement(elN, fractionmass=0.7);
  Air->AddElement(elO, fractionmass=0.3);

  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  //default materials of the calorimeter
  AbsorberMaterial = Pb;
  WorldMaterial  = Air;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  
G4VPhysicalVolume* Tst14DetectorConstruction::ConstructCalorimeter()
{
  // complete the Calor parameters definition and Print 
  ComputeCalorParameters();
  PrintCalorParameters();
  //     
  // World
  //
  worldchanged = CleanGeometry();
		
  solidWorld = new G4Tubs("World",				//its name
			  0.,WorldSizeR,WorldSizeZ/2.,0.,twopi)       ;//its size
                         
  logicWorld = new G4LogicalVolume(solidWorld,		//its solid
                                   WorldMaterial,	//its material
                                   "World");		//its name
                                   
  physiWorld = new G4PVPlacement(0,			//no rotation
  				 G4ThreeVector(),	//at (0,0,0)
                                 "World",		//its name
                                 logicWorld,		//its logical volume
                                 0,			//its mother  volume
                                 false,			//no boolean operation
                                 0);			//copy number
  
  //                               
  // Absorber
  //
  if (AbsorberThickness > 0.) 
    { 
      solidAbsorber = new G4Tubs("Absorber",		//its name
				 0.,AbsorberRadius,AbsorberThickness/2.,0.,twopi); 
                          
      logicAbsorber = new G4LogicalVolume(solidAbsorber,    //its solid
      			                  AbsorberMaterial, //its material
      			                  "Absorber");      //its name
      			                  
      physiAbsorber = new G4PVPlacement(0,		   //no rotation
					G4ThreeVector(0.,0.,zAbsorber),  //its position
                                        "Absorber",        //its name
                                        logicAbsorber,     //its logical volume
                                        physiWorld,        //its mother
                                        false,             //no boulean operat
                                        0);                //copy number
                                        
    }
  
  //                               
  // Sensitive Detectors: Absorber 
  //
  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  if (!calorimeterSD)
    {
      calorimeterSD = new Tst14CalorimeterSD("CalorSD",this);
      SDman->AddNewDetector( calorimeterSD );
    }
  if (logicAbsorber)
    logicAbsorber->SetSensitiveDetector(calorimeterSD);

  //
  //always return the physical World
  //
  worldchanged = false;
	  
  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Tst14DetectorConstruction::PrintCalorParameters()
{
  G4cout << "\n The  WORLD   is made of " 
	 << WorldSizeZ/mm << "mm of " << WorldMaterial->GetName() ;
  G4cout << ", the transverse size (R) of the world is " << WorldSizeR/mm << " mm. " << G4endl;
  G4cout << " The ABSORBER is made of " 
	 << AbsorberThickness/mm << "mm of " << AbsorberMaterial->GetName() ;
  G4cout << ", the transverse size (R) is " << AbsorberRadius/mm << " mm. " << G4endl;
  G4cout << " Z position of the (middle of the) absorber " << zAbsorber/mm << "  mm." << G4endl;
  G4cout << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Tst14DetectorConstruction::SetAbsorberMaterial(G4String materialChoice)
{
  const G4MaterialTable* theMaterialTable = G4Material::GetMaterialTable();
  G4int numOfMaterials = G4Material::GetNumberOfMaterials();

  // search the material by its name   
  G4Material* pttoMaterial;
  for (size_t J=0 ; numOfMaterials ; J++)
    { pttoMaterial = (*theMaterialTable)[J];     
    if (pttoMaterial->GetName() == materialChoice)
      {AbsorberMaterial = pttoMaterial;
      logicAbsorber->SetMaterial(pttoMaterial); 
      PrintCalorParameters();
      return;
      }             
    }
  G4cout<<"Unvalid material"<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Tst14DetectorConstruction::SetWorldMaterial(G4String materialChoice)
{
  // get the pointer to the material table
  const G4MaterialTable* theMaterialTable = G4Material::GetMaterialTable();
  G4int numOfMaterials = G4Material::GetNumberOfMaterials();

  // search the material by its name   
  G4Material* pttoMaterial;
  for (size_t J=0 ; numOfMaterials ; J++)
    { pttoMaterial = (*theMaterialTable)[J];     
    if (pttoMaterial->GetName() == materialChoice)
      {WorldMaterial = pttoMaterial;
      logicWorld->SetMaterial(pttoMaterial); 
      //  PrintCalorParameters();
      return;
      }             
    }
  G4cout<<"Unvalid material"<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Tst14DetectorConstruction::SetAbsorberThickness(G4double val)
{
  // change Absorber thickness and recompute the calorimeter parameters
  AbsorberThickness = val;
  ComputeCalorParameters();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Tst14DetectorConstruction::SetAbsorberRadius(G4double val)
{
  // change the transverse size and recompute the calorimeter parameters
  AbsorberRadius = val;
  ComputeCalorParameters();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Tst14DetectorConstruction::SetWorldSizeZ(G4double val)
{
  worldchanged=true;
  WorldSizeZ = val;
  ComputeCalorParameters();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Tst14DetectorConstruction::SetWorldSizeR(G4double val)
{
  worldchanged=true;
  WorldSizeR = val;
  ComputeCalorParameters();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Tst14DetectorConstruction::SetAbsorberZpos(G4double val)
{
  zAbsorber  = val;
  ComputeCalorParameters();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Tst14DetectorConstruction::SetMagField(G4double fieldValue)
{
  //apply a global uniform magnetic field along X axis
  G4FieldManager* fieldMgr 
    = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    
  if (magField) delete magField;		//delete the existing magn field
  
  if (fieldValue!=0.)			// create a new one if non nul
    { magField = new G4UniformMagField(G4ThreeVector(fieldValue,0.,0.));        
    fieldMgr->SetDetectorField(magField);
    fieldMgr->CreateChordFinder(magField);
    } else {
      magField = 0;
      fieldMgr->SetDetectorField(magField);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  
G4bool Tst14DetectorConstruction::CleanGeometry()
{
  if (physiWorld)
  {
    G4PhysicalVolumeStore::Clean();
    G4LogicalVolumeStore::Clean();
    G4SolidStore::Clean();

    return true;
  }
  else
  {
    return false;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  
void Tst14DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructCalorimeter());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Tst14DetectorConstruction::ComputeCalorParameters()
{
  // Compute derived parameters of the calorimeter
     if( worldchanged )
     {
       WorldSizeR=2.*AbsorberRadius ;
       WorldSizeZ=2.*AbsorberThickness ;
     }
     
     zstartAbs = zAbsorber-0.5*AbsorberThickness; 
     zendAbs   = zAbsorber+0.5*AbsorberThickness; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
