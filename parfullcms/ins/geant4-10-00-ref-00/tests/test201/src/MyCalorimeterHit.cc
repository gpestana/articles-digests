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
// $Id: MyCalorimeterHit.cc 73437 2013-08-27 11:11:21Z gcosmo $
//

#include "MyCalorimeterHit.hh"
#include "G4ios.hh"

#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"

G4Allocator<MyCalorimeterHit> MyCalorimeterHitAllocator;

MyCalorimeterHit::MyCalorimeterHit()
{pPhys=0;}

MyCalorimeterHit::MyCalorimeterHit(G4VPhysicalVolume* physVol)
:pPhys(physVol)
{;}

MyCalorimeterHit::~MyCalorimeterHit()
{;}

MyCalorimeterHit::MyCalorimeterHit(const MyCalorimeterHit &right)
  : G4VHit()
{
  edep = right.edep;
  pos = right.pos;
  rot = right.rot;
  pPhys = right.pPhys;
}

const MyCalorimeterHit& MyCalorimeterHit::operator=(const MyCalorimeterHit &right)
{
  edep = right.edep;
  pos = right.pos;
  rot = right.rot;
  pPhys = right.pPhys;
  return *this;
}

int MyCalorimeterHit::operator==(const MyCalorimeterHit &) const
{
  return 0;
}

void MyCalorimeterHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    /* In 1.0 drawing physical volumes with the below
       crashe most of the vis drivers (at least the Inventor one)
    G4Transform3D trans(rot,pos);
    G4VisAttributes attribs;
    G4LogicalVolume* logVol = pPhys->GetLogicalVolume();
    const G4VisAttributes* pVA = logVol->GetVisAttributes();
    if(pVA) attribs = *pVA;
    G4Colour colour(1.,0.,0.);
    attribs.SetColour(colour);
    attribs.SetForceSolid(true);
    pVVisManager->Draw(*pPhys,attribs,trans);
    */
    G4Circle circle(pos);
    circle.SetScreenSize(0.1);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,1.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

void MyCalorimeterHit::Print()
{
}


