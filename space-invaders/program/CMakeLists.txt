cmake_minimum_required(VERSION 3.10)

project(SpaceInvaders CXX)

# Store in a local variable SOURCE_FILES set of project's source files
set(SOURCE_FILES
        src/main.cpp
    )

#add following files to executable file 'Program'
add_executable(invaders ${SOURCE_FILES})

#add libraries from 'Library' project
target_link_libraries(invaders Library sfml-graphics sfml-window sfml-system ${SFML_DEPENDENCIES})

#add header files from 'include' directory of main project
target_include_directories(invaders PUBLIC include ${SFML_INCLUDE_DIRS})

# Copy resources
if(CMAKE_GENERATOR MATCHES "Visual Studio") 
    add_custom_command(TARGET invaders POST_BUILD
                       COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/resources" "${CMAKE_BINARY_DIR}/$<CONFIGURATION>/resources")
else()
    add_custom_command(TARGET invaders POST_BUILD
                       COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/resources" "${CMAKE_BINARY_DIR}/resources")
endif()
