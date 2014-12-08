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

#include "AddOnTargetLayer.hh"
#include "TargetGeometryManager.hh"
#include "TargetLayerSD.hh"
#include "Materials.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"


AddOnTargetLayer::AddOnTargetLayer(TargetComponent* component,
                                   TargetGeometryManager* geomManager,
                                   G4String layerName,
                                   G4String material,
                                   G4double thickn) : 
    TargetComponent(geomManager, layerName, thickn, material),
    targetComponent(component) {

  updateManager -> Attach(this);

  addOnTargetLayerSolid = new G4Tubs(Name(),
                                  0.0 * mm, targetComponent -> GetRadius(), 
				  Thickness() * 0.5, 0.0 * deg, 360.0 * deg); 
      
  addOnTargetLayerLogic = new G4LogicalVolume(
                                           addOnTargetLayerSolid,
                                           Material(),
                                           Name());

  addOnTargetLayerPhys = new G4PVPlacement(0, 
                          G4ThreeVector(0.0 * cm, 0.0 * cm, Thickness() * 0.5),
                          Name(), addOnTargetLayerLogic,
                          targetComponent -> GetWorldVolPhys(), false, 0);

  TargetLayerSD* addOnTargetLayerSD = 
                      new TargetLayerSD(Name()); 
  addOnTargetLayerLogic -> SetSensitiveDetector(addOnTargetLayerSD);

  G4SDManager* SDManager = G4SDManager::GetSDMpointer();
  SDManager -> AddNewDetector(addOnTargetLayerSD);

  addOnTargetLayerUserLimits = 
                      new G4UserLimits(targetComponent -> GetMaxStepSize());
  addOnTargetLayerLogic -> SetUserLimits(addOnTargetLayerUserLimits);

  G4VisAttributes* addOnTargetLayerVisAtt = 
                      new G4VisAttributes(G4Colour(1.0, 1.0, 0.0));
  addOnTargetLayerVisAtt -> SetVisibility(true);
  addOnTargetLayerLogic -> SetVisAttributes(addOnTargetLayerVisAtt);
}


AddOnTargetLayer::~AddOnTargetLayer() {

}


void AddOnTargetLayer::GeometryUpdate(TargetGeometryManager* geomManager) {
 
  if(geomManager == updateManager) {

     G4double newRadius = updateManager -> GetRadius();
     if(newRadius > 0.0 * cm) {
        addOnTargetLayerSolid -> SetOuterRadius(newRadius);
     } 

     G4double newMaxStepSize = updateManager -> GetMaxStepSize();
     if(newMaxStepSize > 0.0 * mm) {
        addOnTargetLayerUserLimits -> SetMaxAllowedStep(newMaxStepSize);
     }
 
     Thickness(updateManager -> GetThickness(this));
     addOnTargetLayerSolid -> SetZHalfLength(Thickness() * 0.5);

     Material(updateManager -> GetMaterial(this));
     addOnTargetLayerLogic -> SetMaterial(Material());     

     G4double position = updateManager -> GetPosition(this);
     addOnTargetLayerPhys -> SetTranslation(
        G4ThreeVector(0.0 * cm, 0.0 * cm, position));
  }
}
