# Build a shared library to call opensim features
add_library(libGravForcesProcessor STATIC GravForcesProcessor.cpp GravForcesProcessor.h)
        # déclaré en STATIC car pb incompréhensible: si SHARED, Visual Studio cherche un fichier .lib au lieu de .dll
target_include_directories(libGravForcesProcessor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
        # 'public' so that any target that links with libGravForcesProcessor
        # shall also include this directory...
message(STATUS "Target 'libGravForcesProcessor' created...")