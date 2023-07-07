# Project : GravForcesProcessor
OpenSim is a great software for biomechanical simulation, and it's Python API helps graetly for quick prototyping of scientific applications. However, this Python wrapping doesn't include all the features available in C++ (for instance when it comes to [retrieve Gravity Forces](https://simtk.org/plugins/phpBB/viewtopicPhpbb.php?f=91&t=15254&p=0&start=0&view=&sid=a0e31360639a2913b8ef9ac8db387005) and process them in a Python script).

The main goal is to write a C++ class (named **GravForcesProcessor**) and the associated SWIG-Python wrapped module in order to retrieve the forces and torques resulting from gravity at a given frame attached to a given body (for instance the elbow joint center) of a given model. The following snippet of fictional Python code illustrates how it should be used:

    myGravProc = GravForcesProcessor(myModel)
    torques, forces = myGravProc(myFrame)

Hence, this project includes 4 "parts":
- the C++ implementation of the class **GravForcesProcessor**;
- the C++ implementation of a CLI executable named **TestGravForcesProcessor** for C++ debugging. It comes with a simple OsimModel for development purpose;
- the SWIG C++ -> Python wrapping;
- the creation of the Python package from the SWIG wrapped code and the dynamic library.

This project is currently only developed for Windows 10, using Visual Studio 2019, CMake 3.23, SWIG 4.0, Python 3.8 and OpenSim 4.4.

NOTE this project is to be developped step by step. The first step to complete is simply to have a very simplistic feature being compiled, linked, executed and wrapped into Python using SWIG.

## Global architecture of the project
### C++ dynamic library and test application
This part uses the following files:
- *GravForcesProcessor.h* the header file;
- *GravForcesProcessor.cpp* the source file that implements the GravForcesProcessor class;
- *TestGravForcesProcessor.cpp* that implements the CLI develoment and test application;
- a minimum OpenSim model (located in a subdirectory named Resources).

**NOTE:** to date, the file GravForcesProcessor.cpp implements only the minimum code to build the whole framework. I'd like to have it compile and link correctly to test all parts of the project before working on the core features.

### SWIG wrapping
This part uses only one SWIG interface file: *GravForcesProcessor.i*.

### Python package creation
This step relies on Python's **setuptools**. It uses a Python *setup.py* file to create the Python module from the SWIG *.cxx* wrapped file and the **GravForcesProcessor** dynamic library.

### Building the whole project
All steps required to compile, link, wrap and create intermediate and final files and applications are managed through the CMake tool and Visual Studio framework. The draft of a unique *CMakeLists.txt* file is provided (and is to be improved).

### Development roadmap
Current state (2023-07-07)
The CLI minimum application is compiled, linked and run without problem :

    C:\WIP>TestGravForcesProcessor.exe
    [2023-07-07 15:55:23.894] [debug] Running main TestGravForcesProcessor...
    [2023-07-07 15:55:23.897] [debug] Creating GravForcesProcessor instance with value: 10
    [2023-07-07 15:55:23.899] [debug] Running ComputeGravTorques, m_test = 10
    [2023-07-07 15:55:23.900] [debug] Gravity Force Test: 10
    [2023-07-07 15:55:23.901] [debug] Done !

The creation of the SWIG wrapper fails because of dependencies and includes issues:

    L'op�ration de g�n�ration a d�marr�...
    1>------ D�but de la g�n�ration : Projet : ZERO_CHECK, Configuration : RelWithDebInfo x64 ------
    1>Checking Build System
    2>------ D�but de la g�n�ration : Projet : swigGravForcesProcessor, Configuration : RelWithDebInfo x64 ------
    2>Swig compile GravForcesProcessor.i for python
    2>C:\Users\jonathan.savin\Documents\WIP\SwigGravityForcesProcessor\GravForcesProcessor.h(15): error : Unable to find 'spdlog\spdlog.h'
    2>C:\Users\jonathan.savin\Documents\WIP\SwigGravityForcesProcessor\GravForcesProcessor.i(20): error : Unable to find 'spdlog\spdlog.h'
    2>C:\Users\jonathan.savin\Documents\WIP\SwigGravityForcesProcessor\GravForcesProcessor.i(23): error : Unable to find 'spdlog\common.h'
    2>C:\Users\jonathan.savin\Documents\WIP\SwigGravityForcesProcessor\GravForcesProcessor.i(24): error : Unable to find 'spdlog\logger.h'
    2>C:\Users\jonathan.savin\Documents\WIP\SwigGravityForcesProcessor\GravForcesProcessor.i(25): error : Unable to find 'spdlog\sinks\stdout_color_sinks.h'
    2>C:\Users\jonathan.savin\Documents\WIP\SwigGravityForcesProcessor\GravForcesProcessor.i(26): error : Unable to find 'spdlog\fmt\ostr.h'
    2>C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Microsoft\VC\v160\Microsoft.CppCommon.targets(241,5): error MSB8066: la build personnalis�e de 'C:\Users\jonathan.savin\Documents \WIP\SwigGravityForcesProcessor\GravForcesProcessor.i' s'est arr�t�e. Code�1.
    2>G�n�ration du projet "swigGravForcesProcessor.vcxproj" termin�e -- �CHEC.
    ========== G�n�ration : 1 a r�ussi, 1 a �chou�, 0 � jour, 0 a �t� ignor� ==========# Project : GravForcesProcessor

