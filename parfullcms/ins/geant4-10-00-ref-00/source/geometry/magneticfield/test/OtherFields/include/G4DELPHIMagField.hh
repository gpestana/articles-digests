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
// $Id: G4DELPHIMagField.hh 66356 2012-12-18 09:02:32Z gcosmo $
//

// Class describing the DELPHI magnetic field. This axial symmetry
// field mainly directed along Z axis. The function MagneticField(yTrack,B)
// calculates the magnetic induction vector B in point corresponding to
// yTrack according to parametrization given in:
// P.Billoir, Precise tracking in a quasi-honogeneous magnetic field, DELPHI 
// 87-6 PROG 65, 3 February 1987
//
// 3.2.97 V. Grichine 

#ifndef G4DELPHIMAGFIELD_HH
#define G4DELPHIMAGFIELD_HH

#include "globals.hh"
#include "G4MagneticField.hh"
#include "G4Mag_EqRhs.hh"

class G4DELPHIMagField : public G4MagneticField
{
public:
		       
         G4DELPHIMagField() ;	       
           
        ~G4DELPHIMagField() ;
	     
         void  GetFieldValue(const G4double yTrack[3] ,
	                           G4double *MagField  ) const;
			   

protected:

private:
              
} ;

#endif