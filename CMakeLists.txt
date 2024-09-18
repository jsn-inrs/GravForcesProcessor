# CMake requirement
cmake_minimum_required(VERSION 3.30)

# Project name
project(prjGravityForcesProcessor
            VERSION 0.1
            DESCRIPTION "Test project to access OpenSim's gravity force C++ features from Python thanks to SWIG"
            LANGUAGES CXX)


#======================================
# Build the test executable
#======================================

#--- Create a target for an executable (for test purpose) ---
add_executable(exeGravForcesProcessor 
                TestGravForcesProcessor.cpp)
#                ${PROJECT_SOURCE_DIR}/GravForcesProcessor/GravForcesProcessor.h)

#--- Declare the sub-folder creating a target for the library with core features ---
add_subdirectory(GravForcesProcessor)

#--- Add include subdirectories ---
target_include_directories(exeGravForcesProcessor PRIVATE "${PROJECT_SOURCE_DIR}/GravForcesProcessor")
get_target_property(inc_dir_list exeGravForcesProcessor INCLUDE_DIRECTORIES)
message(STATUS "Liste des dossiers d'include pour la target 'exeGravForcesProcessor': ${inc_dir_list}")

#--- Add link libraries ---
target_link_libraries(exeGravForcesProcessor PRIVATE libGravForcesProcessor)
get_target_property(link_lib_list exeGravForcesProcessor LINK_LIBRARIES)
message(STATUS "Liste des librairies pour linker la target 'exeGravForcesProcessor': ${link_lib_list}")

