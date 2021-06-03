cmake_minimum_required(VERSION 3.10.2)
project(SmoothedParticleHydrodynamics VERSION 1.0 DESCRIPTION "SPH implementation")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}
    CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo"
    FORCE)

#set(CMAKE_CXX_FLAGS_DEBUG
#    "-fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g -O1"
#    CACHE STRING "Flags used by the C++ compiler during AddressSanitizer builds."
#    FORCE)

set(CMAKE_CXX_FLAGS_RELEASE
    "-O3 -Wall"
    CACHE STRING "Flags used by the C++ compiler during Release builds."
    FORCE)

set(CMAKE_CXX_FLAGS_RELWITHDEBINFO
    "-O3 -Wall -g"
    CACHE STRING "Flags used by the C++ compiler during RelWithDebInfo builds."
    FORCE)

set (SFML_DIR ${SFML_DIR} CACHE STRING "The sfml cmake directory" FORCE)
find_package(SFML COMPONENTS graphics window system QUIET)
if (NOT ${SFML_FOUND})
    include(FindPkgConfig)
    if (${PKG_CONFIG_FOUND})
        pkg_search_module(SFML REQUIRED sfml-graphics sfml-window sfml-system)
    else ()
        message(ERROR "SFML not found!")
    endif()
endif()

set(sources
    ./src/core/ParticleSystem.cpp
    ./src/visualizer/Window.cpp
    ./src/visualizer/Colormap.cpp
    ./src/core/SpatialHash.cpp
)

set(api
    ./include/core/Particle.hpp
    ./include/core/ParticleSystem.hpp
    ./include/math/VectorNt.hpp
    ./include/visualizer/Window.hpp
    ./include/visualizer/Colormap.hpp
    ./include/core/SpatialHash.hpp
)

add_library(SPH SHARED "${sources}")
set_target_properties(SPH PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(SPH PROPERTIES PUBLIC_HEADER "${public_api}")
target_include_directories(SPH PRIVATE ./include)
target_link_libraries(SPH PUBLIC sfml-graphics sfml-window sfml-system)

include(GNUInstallDirs)

install(TARGETS SPH
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(simple ./app/Simple.cpp)
target_include_directories(simple PRIVATE ./include)
target_link_libraries(simple SPH)
configure_file(./resources/arial.ttf arial.ttf COPYONLY)
