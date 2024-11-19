cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

# B2D - Box2D phyics library
# add_subdirectory("lib/b2d/Box2D")
#include_directories("lib/b2d/Box2D/")
#set(B2D_INCS "lib/b2d/Box2D/")
#link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)

#### Practical 1 ####
file(GLOB_RECURSE SOURCES practical_1/*.cpp practical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)

## Space invaders
file(GLOB_RECURSE SOURCES practical_2/*.cpp practical_2/*.h)
add_executable(PRACTICAL_2 ${SOURCES} )
target_include_directories(PRACTICAL_2 SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_2 sfml-graphics)
set_target_properties(PRACTICAL_2 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_dependencies(PRACTICAL_2 copy_resources)

## physics
#file(GLOB_RECURSE SOURCES 5_physics/*.cpp 5_physics/*.h)
#add_executable(5_PHYSICS ${SOURCES})
#target_include_directories(5_PHYSICS SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
#target_link_libraries(5_PHYSICS Box2D sfml-graphics)
#set(EXECUTABLES ${EXECUTABLES} PRACTICAL_5_PHYSICS)