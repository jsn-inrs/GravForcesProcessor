#ifndef GRAV_FORCES_PROC_H
#define GRAV_FORCES_PROC_H

/*============================================================================
    JSN, 20230704 - GravForcesProcessor.h

    The class "GravForcesProcessor" is designed to implement Python features
    (via SWIG) to compute the effects of gravity on an OpenSim body. 
============================================================================*/

//=============================================================================
// INCLUDES
//=============================================================================

#include <spdlog/spdlog.h>

//=============================================================================
// CLASSES
//=============================================================================
class GravForcesProcessor
{
    public:
        GravForcesProcessor::GravForcesProcessor(int test);
        int getGravTorques();
    private:
        int m_test;
};
#endif