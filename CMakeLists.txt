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
    ./src/Integrator.cc
    ./src/Kernels.cc
    ./src/Obstacle.cc
    ./src/ParticleSystem.cc
    ./src/SpatialHash.cc
    ./src/TileMap.cc
    ./src/Visualizer.cc
)


add_executable(simple "${sources}" ./app/Simple.cc)
target_include_directories(simple PRIVATE ./include)
target_link_libraries(simple PRIVATE sfml-graphics sfml-window sfml-system)
configure_file(./resources/arial.ttf arial.ttf COPYONLY)
