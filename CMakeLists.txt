cmake_minimum_required(VERSION 3.10.2)
project(SmoothedParticleHydrodynamics VERSION 1.0 DESCRIPTION "SPH implementation")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set (SFML_DIR ${SFML_DIR} CACHE STRING "The sfml cmake directory" FORCE)
find_package(SFML COMPONENTS graphics window system REQUIRED)

set(sources
    ./src/CircleMap.cc
    ./src/ColorMap.cc
    ./src/Grid.cc
    ./src/Inflow.cc
    ./src/Integrator.cc
    ./src/Kernels.cc
    ./src/Obstacle.cc
    ./src/ParticleSystem.cc
    ./src/SpatialHash.cc
    ./src/TileMap.cc
    ./src/Visualizer.cc
)


add_executable(simple "${sources}" ./examples/Simple.cc)
target_include_directories(simple PRIVATE ./include)
target_link_libraries(simple PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(splash "${sources}" ./examples/Splash.cc)
target_include_directories(splash PRIVATE ./include)
target_link_libraries(splash PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(steady "${sources}" ./examples/Steady.cc)
target_include_directories(steady PRIVATE ./include)
target_link_libraries(steady PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(obstacles_comp "${sources}" ./examples/ObstacleComp.cc)
target_include_directories(obstacles_comp PRIVATE ./include)
target_link_libraries(obstacles_comp PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(slope "${sources}" ./examples/Slope.cc)
target_include_directories(slope PRIVATE ./include)
target_link_libraries(slope PRIVATE sfml-graphics sfml-window sfml-system)

configure_file(./resources/arial.ttf arial.ttf COPYONLY)
