cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(test12)
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

GEANT4_EXECUTABLE(test12 test12.cc src/*.cc)
GEANT4_EXECUTABLE(test12_hadronic_exerciser test12_hadronic_exerciser.cc)
add_dependencies(test12 test12_hadronic_exerciser) # Artificial to force serialization (problem on windows)

#---Test definitions----------------------------------------------------------------------------------
GEANT4_ADD_TEST(test12-build BUILD test12)
GEANT4_ADD_TEST(test12_hadronic_exerciser COMMAND test12_hadronic_exerciser
                                          OUTPUT  test12.in
                                          DEPENDS test12-build)
GEANT4_ADD_TEST(test12 COMMAND test12 test12.in
                       ENVIRONMENT ${GEANT4_TEST_ENVIRONMENT}
                       DEPENDS test12_hadronic_exerciser)
GEANT4_ADD_TEST(test12-FTFBIC COMMAND test12 test12.in FTF_BIC
                              ENVIRONMENT ${GEANT4_TEST_ENVIRONMENT}
                              DEPENDS test12
                              TIMEOUT 2000)
GEANT4_ADD_TEST(test12-QGSBIC COMMAND test12 test12.in QGS_BIC
                              ENVIRONMENT ${GEANT4_TEST_ENVIRONMENT}
                              DEPENDS test12)
GEANT4_ADD_TEST(test12-QGSP_FTFP_BERT COMMAND test12 test12.in QGSP_FTFP_BERT
                              ENVIRONMENT ${GEANT4_TEST_ENVIRONMENT}
                              DEPENDS test12)

