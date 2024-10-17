/*============================================================================
    JSN, 20230704 - TestGravForcesProcessor.cpp

    Test the GravForcesProcessor class
============================================================================*/

//=============================================================================
// INCLUDES
//=============================================================================
#include <iostream>
#include "GravForcesProcessor.h"

//=============================================================================
// DEFINES
//=============================================================================
#define OSIM_ARM_MODEL      "./resources/test0.osim"
#define TEST 20

int main()
{
    // Set global log level to debug
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("Running main TestGravForcesProcessor...");

    // Create the GravForcesProcessor instance
    GravForcesProcessor myGravTest = GravForcesProcessor(TEST);
    spdlog::debug("Gravity Force Test: {}", myGravTest.getGravTorques());

    spdlog::debug("Done !");
}