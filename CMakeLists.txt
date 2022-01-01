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
    ./src/Interact.cc
    ./src/Kernels.cc
    ./src/Obstacle.cc
    ./src/ParticleSystem.cc
    ./src/SpatialHash.cc
    ./src/TextureMap.cc
    ./src/TileMap.cc
    ./src/Visualizer.cc
)

add_library(sph "${sources}")
target_include_directories(sph PRIVATE ./include)

add_executable(simple ./examples/Simple.cc)
target_include_directories(simple PRIVATE ./include)
target_link_libraries(simple PRIVATE sph sfml-graphics sfml-window sfml-system)

add_executable(splash ./examples/Splash.cc)
target_include_directories(splash PRIVATE ./include)
target_link_libraries(splash PRIVATE sph sfml-graphics sfml-window sfml-system)

add_executable(steady ./examples/Steady.cc)
target_include_directories(steady PRIVATE ./include)
target_link_libraries(steady PRIVATE sph sfml-graphics sfml-window sfml-system)

add_executable(obstacles_comp ./examples/ObstacleComp.cc)
target_include_directories(obstacles_comp PRIVATE ./include)
target_link_libraries(obstacles_comp PRIVATE sph sfml-graphics sfml-window sfml-system)

add_executable(slope ./examples/Slope.cc)
target_include_directories(slope PRIVATE ./include)
target_link_libraries(slope PRIVATE sph sfml-graphics sfml-window sfml-system)

add_executable(dam_break ./examples/DamBreak.cc)
target_include_directories(dam_break PRIVATE ./include)
target_link_libraries(dam_break PRIVATE sph sfml-graphics sfml-window sfml-system)

add_executable(horizontal ./examples/Horizontal.cc)
target_include_directories(horizontal PRIVATE ./include)
target_link_libraries(horizontal PRIVATE sph sfml-graphics sfml-window sfml-system)

add_executable(flow ./examples/Flow.cc)
target_include_directories(flow PRIVATE ./include)
target_link_libraries(flow PRIVATE sph sfml-graphics sfml-window sfml-system)

add_executable(explode ./examples/Explode.cc)
target_include_directories(explode PRIVATE ./include)
target_link_libraries(explode PRIVATE sph sfml-graphics sfml-window sfml-system)

add_executable(pools ./examples/Pools.cc)
target_include_directories(pools PRIVATE ./include)
target_link_libraries(pools PRIVATE sph sfml-graphics sfml-window sfml-system)

configure_file(./resources/arial.ttf arial.ttf COPYONLY)
