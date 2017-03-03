cmake_minimum_required(VERSION 2.6)
project(gamejam)

# Add sources
file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/*.cpp"
)

# Add directory containing FindSFML.cmake to module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}")

# Copy assets to build directory
file(COPY assets DESTINATION .)

# Find SFML
if (SFML_OS_WINDOWS AND SFML_COMPILER_MSVC)
    find_package( SFML 2 COMPONENTS main audio graphics window system REQUIRED)
else()
    find_package( SFML 2 COMPONENTS audio graphics window system REQUIRED)
endif()

if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
else()
        set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
        message("\nSFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
        message("Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

add_executable(gamejam ${SOURCES})
target_link_libraries(gamejam ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

install(TARGETS gamejam RUNTIME DESTINATION bin)

set_property(TARGET gamejam PROPERTY CXX_STANDARD 11)
set_property(TARGET gamejam PROPERTY CXX_STANDARD_REQUIRED ON)
