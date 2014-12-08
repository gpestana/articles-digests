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
// INCL++ intra-nuclear cascade model
// Pekka Kaitaniemi, CEA and Helsinki Institute of Physics
// Davide Mancusi, CEA
// Alain Boudard, CEA
// Sylvie Leray, CEA
// Joseph Cugnon, University of Liege
//
#define INCLXX_IN_GEANT4_MODE 1

#include "globals.hh"

/** \file G4INCLXXInterfaceStore.hh
 * \brief Header file for the G4INCLXXInterfaceStore class
 *
 * \date 24 May 2012
 * \author Davide Mancusi
 */

#ifndef G4INCLXXINTERFACESTORE_HH_
#define G4INCLXXINTERFACESTORE_HH_

#include "G4INCLXXInterface.hh"
#include "G4INCLCascade.hh"
#include "G4INCLVersion.hh"
#include "G4INCLConfig.hh"
#include <list>
#include <sstream>

class G4INCLXXInterfaceMessenger;

/** \class G4INCLXXInterfaceStore
 * \brief Singleton class for configuring the INCL++ Geant4 interface.
 *
 * This class also contains a single cached instance of the INCL model
 * (\see{G4INCL::INCL}).
 */
class G4INCLXXInterfaceStore {
  public:

    /// \brief Get the singleton instance
    static G4INCLXXInterfaceStore *GetInstance();

    /// \brief Delete the singleton instance
    static void DeleteInstance();

    /// \brief Get the cached INCL model engine
    G4INCL::INCL *GetINCLModel();

    void constructINCLXXVersionName();

    const std::string &getINCLXXVersionName();



    /// \brief Setter for accurateProjectile
    void SetAccurateProjectile(const G4bool b);

    /// \brief Setter for theMaxClusterMass
    void SetMaxClusterMass(const G4int aMass);

    /// \brief Setter for cascadeMinEnergyPerNucleon
    void SetCascadeMinEnergyPerNucleon(const G4double anEnergy);

    /// \brief Setter for conservationTolerance
    void SetConservationTolerance(const G4double aTolerance);




    /** \brief Getter for accurateProjectile
     *
     * The \see{G4INCLXXInterfaceMessenger} class provides a UI command to set
     * this parameter.
     */
    G4bool GetAccurateProjectile() const;

    /** \brief Getter for cascadeMinEnergyPerNucleon
     *
     * The \see{G4INCLXXInterfaceMessenger} class provides a UI command to set
     * this parameter.
     */
    G4double GetCascadeMinEnergyPerNucleon() const;

    /** \brief Getter for ClusterMaxMass
     *
     * The \see{G4INCLXXInterfaceMessenger} class provides a UI command to set
     * this parameter.
     */
    G4int GetMaxClusterMass() const;




    /// \brief Getter for theMaxProjMassINCL
    G4int GetMaxProjMassINCL() const;




    /// \brief Getter for conservationTolerance
    G4double GetConservationTolerance() const;




    /** \brief Emit a warning to G4cout
     *
     * The InterfaceStore will not emit more than maxWarnings warnings.
     */
    void EmitWarning(const G4String &message);

    /** \brief Emit a BIG warning to G4cout
     *
     * There is no limit on the number of BIG warnings emitted.
     */
    void EmitBigWarning(const G4String &message) const;

  private:

    /** \brief Private constructor
     *
     * This class is a singleton. It must be instantiated using the GetInstance
     * static method.
     */
    G4INCLXXInterfaceStore();

    /** \brief Private destructor
     *
     * This class is a singleton. Its instance must be deleted using the
     * DeleteInstance static method.
     */
    ~G4INCLXXInterfaceStore();

    /// \brief Delete the INCL model engine
    void DeleteModel() { delete theINCLModel; theINCLModel=NULL; }

    /// \brief Create a new Config object from the current options

    static G4ThreadLocal G4INCLXXInterfaceStore *theInstance;

    G4bool accurateProjectile;
    const G4int theMaxClusterMassDefault;
    G4int theMaxClusterMass;
    const G4int theMaxProjMassINCL;
    G4double cascadeMinEnergyPerNucleon;
    G4double conservationTolerance;

    G4INCLXXInterfaceMessenger *theINCLXXInterfaceMessenger;

    G4INCL::INCL *theINCLModel;

    /// \brief Static warning counter
    G4int nWarnings;

    /// \brief Maximum number of warnings
    const G4int maxWarnings;

    std::string versionName;
};

#endif // G4INCLXXINTERFACESTORE_HH_
