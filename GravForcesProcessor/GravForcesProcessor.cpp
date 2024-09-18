/*============================================================================
    JSN, 20230704 - GravForcesProcessor.cpp

    Implement the "GravForcesProcessor" class
  ============================================================================*/

//=============================================================================
// INCLUDES
//=============================================================================
#include "GravForcesProcessor.h"

//=============================================================================
// STATICS
//=============================================================================


/*-------------------------------------------
    Constructor
  -------------------------------------------*/
GravForcesProcessor::GravForcesProcessor(int test)
{
//    spdlog::debug("Creating GravForcesProcessor instance with value: {}", test);
    std::cout << "Creating GravForcesProcessor instance with value: " << test << std::endl;
    m_test = test;
    return;
}

/*-------------------------------------------
    getGravTorques

    Returns the Gravity Torques
    TODO !
  -------------------------------------------*/
int GravForcesProcessor::getGravTorques()
{
//    spdlog::debug("Running ComputeGravTorques, m_test = {}", m_test);
    std::cout << "Running ComputeGravTorques, m_test = " << m_test  << std::endl;
    return m_test;
}