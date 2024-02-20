#Minimal version of cmake required to build this project
cmake_minimum_required(VERSION 3.10)

#Configuration parameters for development platform and compiler flags
set(CMAKE_CXX_COMPILER g++)  #g++ as C++ compiler
set(CMAKE_C_COMPILER gcc)    #gcc as C compiler
set(CMAKE_CXX_STANDARD 17)   #Standard C++17, without this g++ will use its defaults. For g++ since version 6 it is C++14
set(CMAKE_CXX_STANDARD_REQUIRED True)  #Defined above version of C++ standard is required

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(SFML_DIR "/usr/lib/x86_64-linux-gnu/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

#Set the Debug profile, maximum level of debug info g3, and format of debug info to dwarf-4 (debugger gdb in version 7 will be required).
#BUILD_TYPE can be set to może być ustawiony na:
#empty,
#Debug,
#Release,
#RelWithDebInfo
#MinSizeRel
#Enable additional flags to generate information for debugger
set(CMAKE_BUILD_TYPE Debug)
if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS_DEBUG "-g3 -gdwarf-4")
endif()
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-4")
endif()
#Set name of the project and language used to C++
project(crane)
enable_language(CXX)
#In extra file compile_commands.json you can look at all compiler commands with parameters.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
set(CMAKE_VERBOSE_MAKEFILE TRUE) 
#Include subproject residing in subdirectory program. Inside this subdirectory the file CMakeLists.txt has to be present there.
add_subdirectory(program)
#Enabling unit tests will add additional target test in Makefile files.
enable_testing()

#Include subproject residing in subdirectory library.
add_subdirectory(library)
