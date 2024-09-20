#======================================
# Create a shared library
#======================================

#--- Declare the library ---
add_library(libGravForcesProcessor STATIC GravForcesProcessor.cpp GravForcesProcessor.h)
        # STATIC because of an misunderstood issue:
        # if 'SHARED', Visual Studio looks for a .lib file instead of a .dll

# Manage includes
target_include_directories(libGravForcesProcessor
                                PUBLIC
                                "${CMAKE_CURRENT_SOURCE_DIR}" 
                                "${OpenSim_INCLUDE_DIRS}")
                                # where to find header files

get_target_property(lib_inc_dir_list libGravForcesProcessor INCLUDE_DIRECTORIES)
message(STATUS "Include folders for target 'libGravForcesProcessor': ${lib_inc_dir_list}")

# Manage links
target_link_directories(libGravForcesProcessor PUBLIC "${OpenSim_LIB_DIR}")
target_link_libraries(libGravForcesProcessor
                        PUBLIC ${OpenSim_LIBRARIES})
message(STATUS "Linked libraries for 'libGravForcesProcessor':  ${OpenSim_LIBRARIES}")

#--- End ---
message(STATUS "--> target 'libGravForcesProcessor' declared...")
