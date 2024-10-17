#========================================
# Create a library, its test executable
# and wrap the library into python using
# SWIG.
#
# JSN, simMACT project, 2024
#========================================

#--------------------------------------
# Generic statements
#--------------------------------------

# CMake requirement
cmake_minimum_required(VERSION 3.30)

# Project name
project(prjGravityForcesProcessor
            VERSION 0.1
            DESCRIPTION "Test project to access OpenSim's gravity force C++ features from Python thanks to SWIG"
            LANGUAGES CXX)

# Because of OpenSim requirements
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#--------------------------------------
# Manage dependencies
#--------------------------------------

# Find Opensim
set(OpenSim_DIR "C:/OpenSim44/cmake")
find_package(OpenSim 4.4.0 REQUIRED)

#======================================
# Build the test executable
#======================================

#--- Create a target for an executable (for test purpose) ---
add_executable(exeGravForcesProcessor 
                TestGravForcesProcessor.cpp)

#--- Declare the sub-folder creating a target for the library with core features ---
add_subdirectory(GravForcesProcessor)

#--- Add include subdirectories ---
target_include_directories(exeGravForcesProcessor
                            PUBLIC
                                "${PROJECT_SOURCE_DIR}/GravForcesProcessor"
                                "${OpenSim_INCLUDE_DIRS}")
# DEBUG
#get_target_property(exe_inc_dir_list exeGravForcesProcessor INCLUDE_DIRECTORIES)
#message(STATUS "Liste des dossiers d'include pour la target 'exeGravForcesProcessor': ${exe_inc_dir_list}")

#--- Add link libraries ---
target_link_libraries(exeGravForcesProcessor
                        PUBLIC
                            libGravForcesProcessor
                            ${OpenSim_LIBRARIES})
# DEBUG
#get_target_property(exe_lnk_lib_list exeGravForcesProcessor LINK_LIBRARIES)
#message(STATUS "Liste des librairies pour linker la target 'exeGravForcesProcessor': ${exe_lnk_lib_list}")

target_link_directories(exeGravForcesProcessor PUBLIC "${OpenSim_LIB_DIR}")
# DEBUG
#get_target_property(exe_lnk_dir_list exeGravForcesProcessor LINK_DIRECTORIES)
#message(STATUS "Liste des directories des libraries pour la target 'exeGravForcesProcessor': ${exe_lnk_dir_list}")