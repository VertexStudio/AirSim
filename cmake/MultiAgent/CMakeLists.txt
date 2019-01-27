cmake_minimum_required(VERSION 3.5.0)
project(MultiAgent)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake-modules") 
INCLUDE("${CMAKE_CURRENT_LIST_DIR}/../cmake-modules/CommonSetup.cmake")
CommonSetup()

IncludeEigen()

SetupConsoleBuild()

## Specify additional locations of header files
include_directories(
  ${AIRSIM_ROOT}/MultiAgent
  ${AIRSIM_ROOT}/AirLib/include
  ${RPC_LIB_INCLUDES}
  ${AIRSIM_ROOT}/MavLinkCom/include
  ${AIRSIM_ROOT}/MavLinkCom/common_utils
  $ENV{MADARA_ROOT}/include
  $ENV{CAPNP_ROOT}/c++/src
  $ENV{GAMS_ROOT}/src
  ## ${AIRSIM_ROOT}/llvm-source-50/projects/libcxxabi/include
  ${AIRSIM_ROOT}/llvm-build/projects/libcxx/include/c++build
  ## ${AIRSIM_ROOT}/llvm-build/include/c++/v1
)

link_directories(
  $ENV{MADARA_ROOT}/lib
  $ENV{GAMS_ROOT}/lib
)

AddExecutableSource()
			
CommonTargetLink()
target_link_libraries(${PROJECT_NAME} AirLib)
target_link_libraries(${PROJECT_NAME} ${RPC_LIB})
target_link_libraries(${PROJECT_NAME} MavLinkCom)
target_link_libraries(${PROJECT_NAME} MADARA)
target_link_libraries(${PROJECT_NAME} GAMS)
target_link_libraries(${PROJECT_NAME} boost_system)

