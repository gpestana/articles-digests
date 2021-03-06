cmake_minimum_required( VERSION 2.6 FATAL_ERROR )
project( test22 )
find_package( Geant4 REQUIRED )
include( ${Geant4_USE_FILE} )
include_directories( ${PROJECT_SOURCE_DIR}/include
                     ${PROJECT_SOURCE_DIR}/src )

#--- Library of common code ---
file( GLOB test22_common_sources ${PROJECT_SOURCE_DIR}/src/*.cc 
                                 ${PROJECT_SOURCE_DIR}/src/*.icc )
file( GLOB test22_common_headers ${PROJECT_SOURCE_DIR}/include/*.hh )
add_library( test22_common EXCLUDE_FROM_ALL ${test22_common_sources} ${test22_common_headers} )
target_link_libraries( test22_common ${Geant4_LIBRARIES} )

#--- Individual applications ---

#- ChipsX
add_executable( test22_ChipsX EXCLUDE_FROM_ALL ChipsX/test22_ChipsX.cc )
target_link_libraries( test22_ChipsX test22_common )
install( TARGETS test22_ChipsX DESTINATION bin )

#- hA
add_executable( test22_E941 EXCLUDE_FROM_ALL hA/test22_E941.cc )
target_link_libraries( test22_E941 test22_common )
install( TARGETS test22_E941 DESTINATION bin )

add_executable( test22_hA100 EXCLUDE_FROM_ALL hA/test22_hA100.cc )
target_link_libraries( test22_hA100 test22_common )
install( TARGETS test22_hA100 DESTINATION bin )

add_executable( test22_hA120 EXCLUDE_FROM_ALL hA/test22_hA120.cc )
target_link_libraries( test22_hA120 test22_common )
install( TARGETS test22_hA120 DESTINATION bin )

add_executable( test22_HARP EXCLUDE_FROM_ALL hA/test22_HARP.cc )
target_link_libraries( test22_HARP test22_common )
install( TARGETS test22_HARP DESTINATION bin )

add_executable( test22_NA35 EXCLUDE_FROM_ALL hA/test22_NA35.cc )
target_link_libraries( test22_NA35 test22_common )
install( TARGETS test22_NA35 DESTINATION bin )

add_executable( test22_NA49 EXCLUDE_FROM_ALL hA/test22_NA49.cc )
target_link_libraries( test22_NA49 test22_common )
install( TARGETS test22_NA49 DESTINATION bin )

add_executable( test22_NA61 EXCLUDE_FROM_ALL hA/test22_NA61.cc )
target_link_libraries( test22_NA61 test22_common )
install( TARGETS test22_NA61 DESTINATION bin )

add_executable( test22_pA200 EXCLUDE_FROM_ALL hA/test22_pA200.cc )
target_link_libraries( test22_pA200 test22_common )
install( TARGETS test22_pA200 DESTINATION bin )

#- KmPchan
add_executable( test22_KmPchan EXCLUDE_FROM_ALL KmPchan/test22_KmPchan.cc )
target_link_libraries( test22_KmPchan test22_common )
install( TARGETS test22_KmPchan DESTINATION bin )

#- KpPchan
add_executable( test22_KpPchan EXCLUDE_FROM_ALL KpPchan/test22_KpPchan.cc )
target_link_libraries( test22_KpPchan test22_common )
install( TARGETS test22_KpPchan DESTINATION bin )

#- PbarA
add_executable( test22_Nb_C_750 EXCLUDE_FROM_ALL PbarA/test22_Nb_C_750.cc )
target_link_libraries( test22_Nb_C_750 test22_common )
install( TARGETS test22_Nb_C_750 DESTINATION bin )

add_executable( test22_PbA_1p22_nE EXCLUDE_FROM_ALL PbarA/test22_PbA_1p22_nE.cc )
target_link_libraries( test22_PbA_1p22_nE test22_common )
install( TARGETS test22_PbA_1p22_nE DESTINATION bin )

add_executable( test22_PbA_Rest EXCLUDE_FROM_ALL PbarA/test22_PbA_Rest.cc )
target_link_libraries( test22_PbA_Rest test22_common )
install( TARGETS test22_PbA_Rest DESTINATION bin )

add_executable( test22_PbC_608 EXCLUDE_FROM_ALL PbarA/test22_PbC_608.cc )
target_link_libraries( test22_PbC_608 test22_common )
install( TARGETS test22_PbC_608 DESTINATION bin )

add_executable( test22_PbDNe_Rest EXCLUDE_FROM_ALL PbarA/test22_PbDNe_Rest.cc )
target_link_libraries( test22_PbDNe_Rest test22_common )
install( TARGETS test22_PbDNe_Rest DESTINATION bin )

add_executable( test22_PbTa_4 EXCLUDE_FROM_ALL PbarA/test22_PbTa_4.cc )
target_link_libraries( test22_PbTa_4 test22_common )
install( TARGETS test22_PbTa_4 DESTINATION bin )

add_executable( test22_PbU_608 EXCLUDE_FROM_ALL PbarA/test22_PbU_608.cc )
target_link_libraries( test22_PbU_608 test22_common )
install( TARGETS test22_PbU_608 DESTINATION bin )

#- PbarA_X
add_executable( test22_PbarA_X EXCLUDE_FROM_ALL PbarA_X/test22_PbarA_X.cc )
target_link_libraries( test22_PbarA_X test22_common )
install( TARGETS test22_PbarA_X DESTINATION bin )

#- PbarPchan
add_executable( test22_PbarPchan EXCLUDE_FROM_ALL PbarPchan/test22_PbarPchan.cc )
target_link_libraries( test22_PbarPchan test22_common )
install( TARGETS test22_PbarPchan DESTINATION bin )

#- PbarPinclusive
add_executable( test22_PbarP100 EXCLUDE_FROM_ALL PbarPinclusive/test22_PbarP100.cc )
target_link_libraries( test22_PbarP100 test22_common )
install( TARGETS test22_PbarP100 DESTINATION bin )

add_executable( test22_PbarP14p8 EXCLUDE_FROM_ALL PbarPinclusive/test22_PbarP14p8.cc )
target_link_libraries( test22_PbarP14p8 test22_common )
install( TARGETS test22_PbarP14p8 DESTINATION bin )

add_executable( test22_PbarP22p4 EXCLUDE_FROM_ALL PbarPinclusive/test22_PbarP22p4.cc )
target_link_libraries( test22_PbarP22p4 test22_common )
install( TARGETS test22_PbarP22p4 DESTINATION bin )

add_executable( test22_PbarP32 EXCLUDE_FROM_ALL PbarPinclusive/test22_PbarP32.cc )
target_link_libraries( test22_PbarP32 test22_common )
install( TARGETS test22_PbarP32 DESTINATION bin )

add_executable( test22_PbarP4p6 EXCLUDE_FROM_ALL PbarPinclusive/test22_PbarP4p6.cc )
target_link_libraries( test22_PbarP4p6 test22_common )
install( TARGETS test22_PbarP4p6 DESTINATION bin )

add_executable( test22_PbarP5p7 EXCLUDE_FROM_ALL PbarPinclusive/test22_PbarP5p7.cc )
target_link_libraries( test22_PbarP5p7 test22_common )
install( TARGETS test22_PbarP5p7 DESTINATION bin )

add_executable( test22_PbarP7p3 EXCLUDE_FROM_ALL PbarPinclusive/test22_PbarP7p3.cc )
target_link_libraries( test22_PbarP7p3 test22_common )
install( TARGETS test22_PbarP7p3 DESTINATION bin )

add_executable( test22_PbarP9p1 EXCLUDE_FROM_ALL PbarPinclusive/test22_PbarP9p1.cc )
target_link_libraries( test22_PbarP9p1 test22_common )
install( TARGETS test22_PbarP9p1 DESTINATION bin )

#- PimPchan
add_executable( test22_PimPchan EXCLUDE_FROM_ALL PimPchan/test22_PimPchan.cc )
target_link_libraries( test22_PimPchan test22_common )
install( TARGETS test22_PimPchan DESTINATION bin )

#- PiPinclusive
add_executable( test22_PimP100 EXCLUDE_FROM_ALL PiPinclusive/test22_PimP100.cc )
target_link_libraries( test22_PimP100 test22_common )
install( TARGETS test22_PimP100 DESTINATION bin )

add_executable( test22_PimP16 EXCLUDE_FROM_ALL PiPinclusive/test22_PimP16.cc )
target_link_libraries( test22_PimP16 test22_common )
install( TARGETS test22_PimP16 DESTINATION bin )

add_executable( test22_PimP40 EXCLUDE_FROM_ALL PiPinclusive/test22_PimP40.cc )
target_link_libraries( test22_PimP40 test22_common )
install( TARGETS test22_PimP40 DESTINATION bin )

add_executable( test22_PipP100 EXCLUDE_FROM_ALL PiPinclusive/test22_PipP100.cc )
target_link_libraries( test22_PipP100 test22_common )
install( TARGETS test22_PipP100 DESTINATION bin )

add_executable( test22_PipP16 EXCLUDE_FROM_ALL PiPinclusive/test22_PipP16.cc )
target_link_libraries( test22_PipP16 test22_common )
install( TARGETS test22_PipP16 DESTINATION bin )

add_executable( test22_PipP175 EXCLUDE_FROM_ALL PiPinclusive/test22_PipP175.cc )
target_link_libraries( test22_PipP175 test22_common )
install( TARGETS test22_PipP175 DESTINATION bin )

add_executable( test22_PipP8 EXCLUDE_FROM_ALL PiPinclusive/test22_PipP8.cc )
target_link_libraries( test22_PipP8 test22_common )
install( TARGETS test22_PipP8 DESTINATION bin )

#- PipPchan
add_executable( test22_PipPchan EXCLUDE_FROM_ALL PipPchan/test22_PipPchan.cc )
target_link_libraries( test22_PipPchan test22_common )
install( TARGETS test22_PipPchan DESTINATION bin )

#- PPchan
add_executable( test22_PPchan EXCLUDE_FROM_ALL PPchan/test22_PPchan.cc )
target_link_libraries( test22_PPchan test22_common )
install( TARGETS test22_PPchan DESTINATION bin )

#- PPinclusive
add_executable( test22_PP100 EXCLUDE_FROM_ALL PPinclusive/test22_PP100.cc )
target_link_libraries( test22_PP100 test22_common )
install( TARGETS test22_PP100 DESTINATION bin )

add_executable( test22_PP12 EXCLUDE_FROM_ALL PPinclusive/test22_PP12.cc )
target_link_libraries( test22_PP12 test22_common )
install( TARGETS test22_PP12 DESTINATION bin )

add_executable( test22_PP158 EXCLUDE_FROM_ALL PPinclusive/test22_PP158.cc )
target_link_libraries( test22_PP158 test22_common )
install( TARGETS test22_PP158 DESTINATION bin )

add_executable( test22_PP175 EXCLUDE_FROM_ALL PPinclusive/test22_PP175.cc )
target_link_libraries( test22_PP175 test22_common )
install( TARGETS test22_PP175 DESTINATION bin )

add_executable( test22_PP205 EXCLUDE_FROM_ALL PPinclusive/test22_PP205.cc )
target_link_libraries( test22_PP205 test22_common )
install( TARGETS test22_PP205 DESTINATION bin )

add_executable( test22_PP24 EXCLUDE_FROM_ALL PPinclusive/test22_PP24.cc )
target_link_libraries( test22_PP24 test22_common )
install( TARGETS test22_PP24 DESTINATION bin )

add_executable( test22_PP360 EXCLUDE_FROM_ALL PPinclusive/test22_PP360.cc )
target_link_libraries( test22_PP360 test22_common )
install( TARGETS test22_PP360 DESTINATION bin )

add_executable( test22_PP400 EXCLUDE_FROM_ALL PPinclusive/test22_PP400.cc )
target_link_libraries( test22_PP400 test22_common )
install( TARGETS test22_PP400 DESTINATION bin )

add_executable( test22_PP69 EXCLUDE_FROM_ALL PPinclusive/test22_PP69.cc )
target_link_libraries( test22_PP69 test22_common )
install( TARGETS test22_PP69 DESTINATION bin )

#--- Test definition ---

GEANT4_ADD_TEST( test22_NA49-build BUILD test22_NA49 
                       LABELS Nightly Continuous ) 

GEANT4_ADD_TEST( test22_NA49-exerciser
                       COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test22_NA49 ${CMAKE_CURRENT_SOURCE_DIR}/hA/NA49pC.mac
                       DEPENDS test22_NA49-build
                       LABELS Nightly Continuous
                       ENVIRONMENT ${GEANT4_TEST_ENVIRONMENT} )
