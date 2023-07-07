cmake_minimum_required(VERSION 3.23)

# Project name
project(gravity_forces_processor)


#========================================================================================
# Generic configuration
#========================================================================================

#--------------------------------------------
# C++ dependencies
#--------------------------------------------

# Find and include OpenSim
find_package(OpenSim REQUIRED)

# Find and include spdlog
find_package(spdlog REQUIRED)
include_directories(${SPDLOG_INCLUDE_DIR})

#--------------------------------------------
# SWIG-Python dependencies
#--------------------------------------------

# Find and include Swig
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# Set the Python version (adjust accordingly)
set(Python_ADDITIONAL_VERSIONS 3.8)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

#--------------------------------------------
# Project configuration
#--------------------------------------------
# Set the default build type to RelWithDebInfo
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build." FORCE)
endif()

# Set the allowed build types
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "RelWithDebInfo" "Release")

# Set installation directory
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "Installation directory" FORCE)


#========================================================================================
# CPP stuff: build the C++ test executable and the C++ dynamic shared library
#========================================================================================
# Set the source files for the TestGravForcesProcessor executable
set(TEST_GRAV_FORCES_PROCESSOR
    TestGravForcesProcessor.cpp
    GravForcesProcessor.cpp
)

# Set the source files for the GravForcesProcessor library
set(GRAV_FORCES_PROCESSOR_SOURCES
    GravForcesProcessor.cpp
)

# Add an executable for the TestGravForcesProcessor
add_executable(TestGravForcesProcessor ${TEST_GRAV_FORCES_PROCESSOR})
target_link_libraries(TestGravForcesProcessor ${OpenSim_LIBRARIES})
target_link_libraries(TestGravForcesProcessor spdlog::spdlog_header_only)

# Add a shared library for GravForcesProcessor
add_library(GravForcesProcessor SHARED ${GRAV_FORCES_PROCESSOR_SOURCES})
target_link_libraries(GravForcesProcessor ${OpenSim_LIBRARIES})

#======================================================
# SWIG wrapping
#======================================================
set_source_files_properties(GravForcesProcessor.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(GravForcesProcessor.i PROPERTIES SWIG_FLAGS "-includeall")

# Add source and header files
set(SOURCE_FILES
    GravForcesProcessor.cpp
)
# set(HEADER_FILES
    # GravForcesProcessor.h
# )

# Define swig destination directory
set(DEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/wrapper")
message(NOTICE "SWIG destination directory = '${DEST_DIR}'")

# Generate SWIG wrapper
set_property(SOURCE GravForcesProcessor.i PROPERTY SWIG_MODULE_NAME GravForcesProcessor)
set_property(SOURCE GravForcesProcessor.i PROPERTY CPLUSPLUS ON)
swig_add_library(swigGravForcesProcessor
    TYPE SHARED
    LANGUAGE python
    SOURCES GravForcesProcessor.i ${SOURCE_FILES} # ${HEADER_FILES}
    OUTFILE_DIR ${DEST_DIR}
) # This last command created the target SWIG_MODULE_GravForcesProcessor_REAL_NAME

# Linking configuration
swig_link_libraries(swigGravForcesProcessor ${PYTHON_LIBRARIES} ${SPDLOG_LIBRARIES})
#swig_link_libraries(swigGravForcesProcessor ${PYTHON_LIBRARIES} spdlog::spdlog}

# Add spdlog libraries and definitions
target_include_directories(swigGravForcesProcessor PUBLIC ${SPDLOG_INCLUDE_DIRS})
target_link_libraries(swigGravForcesProcessor ${SPDLOG_LIBRARIES})
target_compile_definitions(swigGravForcesProcessor PRIVATE ${SPDLOG_COMPILE_DEFINITIONS})

# Generate Python package
set(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_SOURCE_DIR}/swig")
set_target_properties(${SWIG_MODULE_GravForcesProcessor_REAL_NAME} PROPERTIES OUTPUT_NAME "_GravForcesProcessor")
set_target_properties(${SWIG_MODULE_GravForcesProcessor_REAL_NAME} PROPERTIES PREFIX "")
set_target_properties(${SWIG_MODULE_GravForcesProcessor_REAL_NAME} PROPERTIES SUFFIX ".pyd")

# Copy the header file to the output directory so that swig can compile the "_wrap.cxx" file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/GravForcesProcessor.h ${DEST_DIR}/GravForcesProcessor.h COPYONLY)

# # Copy the generated fileGravForcesProcessor.py to the destination directory
# set_property(TARGET ${SWIG_MODULE_GravForcesProcessor_REAL_NAME} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${DEST_DIR})
# add_custom_command(TARGET ${SWIG_MODULE_GravForcesProcessor_REAL_NAME}
    # POST_BUILD
    # COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/GravForcesProcessor.py" "${DEST_DIR}/GravForcesProcessor.py"
# )

# # Copy the needed .dll files in the destination directory
# add_custom_command(TARGET ${SWIG_MODULE_GravForcesProcessor_REAL_NAME}
    # POST_BUILD
    # COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${SWIG_MODULE_GravForcesProcessor_REAL_NAME}>" "${DEST_DIR}/$<TARGET_FILE_NAME:${SWIG_MODULE_GravForcesProcessor_REAL_NAME}>"
    # COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE_DIR:${SWIG_MODULE_GravForcesProcessor_REAL_NAME}>/TestGravForcesProcessor.exe" "${DEST_DIR}/TestGravForcesProcessor.exe"
# )

# # Créer le package Python avec setuptools
# execute_process(
    # COMMAND "${PYTHON_EXECUTABLE}" setup.py build_ext --inplace
    # WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
# )

# # Supprimer les fichiers générés par SWIG après la création du package
# file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/GravForceProcessor.py)
# file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/GravForceProcessorPYTHON_wrap.cxx)
# file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/GravForcesProcessor.h)

# # Indiquer où se trouve le package Python généré
# message(STATUS "Le package Python a été créé dans le répertoire: ${CMAKE_CURRENT_BINARY_DIR}")


#========================================================================================
# VISUAL STUDIO stuff
#========================================================================================
# Set the Visual Studio solution properties
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT TestGravForcesProcessor)

# Set installation paths for executables and libraries
install(TARGETS TestGravForcesProcessor RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(TARGETS GravForcesProcessor LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
