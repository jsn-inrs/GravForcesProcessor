#======================================
# Create a shared library and wrap it
# into Python via SWIG
#======================================

#--------------------------------------
# Declare the library
#--------------------------------------
add_library(libGravForcesProcessor GravForcesProcessor.cpp GravForcesProcessor.h)

# Manage includes
target_include_directories(libGravForcesProcessor
                                PUBLIC
                                "${CMAKE_CURRENT_SOURCE_DIR}" 
                                "${OpenSim_INCLUDE_DIRS}")      # where to find header files

target_link_directories(libGravForcesProcessor PUBLIC "${OpenSim_LIB_DIR}")
target_link_libraries(libGravForcesProcessor
                        PUBLIC
                          ${OpenSim_LIBRARIES})

#--------------------------------------
# Manage SWIG stuff
#--------------------------------------
# Find Python for wrapping
find_package(Python COMPONENTS Development Interpreter)

#--- Find Swig for wrapping ---
set(SWIG_EXECUTABLE "C:/swigwin-4.2.1/swig.exe")
# ***
# according to a post, CMake is able to derive `SWIG_DIR` and `SWIG_LIB` from `SWIG_EXECUTABLE` ***
#set(SWIG_DIR "C:/swigwin-4.2.1/Tools/cmake")
#set(SWIG_LIB "C:/swigwin-4.2.1/Lib" "C:/swigwin-4.2.1/Lib/Python")
# *** 

find_package(SWIG REQUIRED)
include(UseSWIG)
if(SWIG_FOUND)
  message("Found SWIG ${SWIG_VERSION}")
else()
  message("No SWIG found.")
  return()
endif()

#--- declare the module to be built ---
set_property(SOURCE GravForcesProcessor.i PROPERTY CPLUSPLUS ON)
swig_add_library(pyGravForcesProcessor
  TYPE SHARED
  LANGUAGE python
  SOURCES GravForcesProcessor.i)
target_include_directories(pyGravForcesProcessor
                            PUBLIC
                              "C:/Python38/include"
                              "${CMAKE_CURRENT_SOURCE_DIR}" 
                              "${OpenSim_INCLUDE_DIRS}")      # where to find header files

target_link_directories(pyGravForcesProcessor
                          PUBLIC
                            "${OpenSim_LIB_DIR}"
                            "C:/Python38/libs"
                            "${CMAKE_BINARY_DIR}/GravForcesProcessor/RelWithDebInfo")
target_link_libraries(pyGravForcesProcessor
                        PUBLIC
                          ${OpenSim_LIBRARIES})
