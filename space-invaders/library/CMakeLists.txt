cmake_minimum_required(VERSION 3.10)
project(Library)

set(SOURCE_FILES
    include/Game.h
    src/Game.cpp
    include/HUD.h
    src/HUD.cpp
    include/Entity.h
    src/Entity.cpp
    include/KillableEntity.h
    src/KillableEntity.cpp
    include/Player.h
    src/Player.cpp
    include/Bullet.h
    src/Bullet.cpp
    include/Enemy.h
    src/Enemy.cpp
    include/ShootingAlien.h
    src/ShootingAlien.cpp
    include/Alien.h
    src/Alien.cpp
    include/Crab.h
    src/Crab.cpp
    include/Squid.h
    src/Squid.cpp
    include/Octopus.h
    src/Octopus.cpp
    include/EnemyManager.h
    src/EnemyManager.cpp
    include/Storage.h
    src/Storage.cpp
    include/UFO.h
    src/UFO.cpp
    include/Shield.h
    src/Shield.cpp
   )
#create shared library of type STATIC, SHARED or MODULE using following source files
add_library(Library ${SOURCE_FILES} )

target_include_directories(Library PUBLIC include ${SFML_INCLUDE_DIRS})

target_link_libraries(Library sfml-graphics sfml-window sfml-system ${SFML_DEPENDENCIES})
        
find_package (Boost COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../library/include
    ${Boost_INCLUDE_DIRS}
)
            
# GameTest
set(SOURCE_TEST_GAME
    test/master.cpp
    test/GameTest.cpp
)
add_executable(TestGame ${SOURCE_TEST_GAME})
target_link_libraries(TestGame
    Library
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

# ShieldTest
set(SOURCE_TEST_SHIELD
    test/master.cpp
    test/ShieldTest.cpp
)
add_executable(TestShield ${SOURCE_TEST_SHIELD})
target_link_libraries(TestShield
    Library
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

# EnemyManagerTest
set(SOURCE_TEST_ENEMYMANAGER
    test/master.cpp
    test/EnemyManagerTest.cpp
)
add_executable(TestEnemyManager ${SOURCE_TEST_ENEMYMANAGER})
target_link_libraries(TestEnemyManager
Library
${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

enable_testing()

add_test(NAME TestGame COMMAND TestGame
    --report_level=detailed
    --log_level=all
    --color_output=yes
)

add_test(NAME TestShield COMMAND TestShield
    --report_level=detailed
    --log_level=all
    --color_output=yes
)

add_test(TestEnemyManager TestEnemyManager
--report_level=detailed
--log_level=all
--color_output=yes
)

add_custom_target(
    check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
    ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)