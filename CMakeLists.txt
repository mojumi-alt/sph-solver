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

add_executable(splash_big "${sources}" ./examples/Splash_big.cc)
target_include_directories(splash_big PRIVATE ./include)
target_link_libraries(splash_big PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(splash_mid "${sources}" ./examples/Splash_mid.cc)
target_include_directories(splash_mid PRIVATE ./include)
target_link_libraries(splash_mid PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(splash_tiny "${sources}" ./examples/Splash_tiny.cc)
target_include_directories(splash_tiny PRIVATE ./include)
target_link_libraries(splash_tiny PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(steady_big "${sources}" ./examples/Steady_big.cc)
target_include_directories(steady_big PRIVATE ./include)
target_link_libraries(steady_big PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(steady_mid "${sources}" ./examples/Steady_mid.cc)
target_include_directories(steady_mid PRIVATE ./include)
target_link_libraries(steady_mid PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(steady_tiny "${sources}" ./examples/Steady_tiny.cc)
target_include_directories(steady_tiny PRIVATE ./include)
target_link_libraries(steady_tiny PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(obstacles_comp_big "${sources}" ./examples/Obstacle_comp_big.cc)
target_include_directories(obstacles_comp_big PRIVATE ./include)
target_link_libraries(obstacles_comp_big PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(obstacles_comp_mid "${sources}" ./examples/Obstacle_comp_mid.cc)
target_include_directories(obstacles_comp_mid PRIVATE ./include)
target_link_libraries(obstacles_comp_mid PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(obstacles_comp_tiny "${sources}" ./examples/Obstacle_comp_tiny.cc)
target_include_directories(obstacles_comp_tiny PRIVATE ./include)
target_link_libraries(obstacles_comp_tiny PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(slope_big "${sources}" ./examples/Slope_big.cc)
target_include_directories(slope_big PRIVATE ./include)
target_link_libraries(slope_big PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(slope_mid "${sources}" ./examples/Slope_mid.cc)
target_include_directories(slope_mid PRIVATE ./include)
target_link_libraries(slope_mid PRIVATE sfml-graphics sfml-window sfml-system)

add_executable(slope_tiny "${sources}" ./examples/Slope_tiny.cc)
target_include_directories(slope_tiny PRIVATE ./include)
target_link_libraries(slope_tiny PRIVATE sfml-graphics sfml-window sfml-system)


configure_file(./resources/arial.ttf arial.ttf COPYONLY)
