cmake_minimum_required(VERSION 3.28)

project(Asteroids LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(SFML googletest)

enable_testing()

# Shared game code
add_library(asteroids_core
    src/Player.cpp
    src/Bullet.cpp
)

target_compile_features(asteroids_core PUBLIC
    cxx_std_20
)

target_compile_options(asteroids_core PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

target_include_directories(asteroids_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(asteroids_core PUBLIC
    SFML::Graphics
)

# Main game executable
add_executable(asteroids
    src/main.cpp
)

target_compile_features(asteroids PRIVATE
    cxx_std_20
)

target_compile_options(asteroids PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

target_link_libraries(asteroids PRIVATE
    asteroids_core
)

# Test executable
add_executable(asteroids_tests
    tests/AsteroidTests.cpp
)

target_compile_features(asteroids_tests PRIVATE
    cxx_std_20
)

target_compile_options(asteroids_tests PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

target_link_libraries(asteroids_tests PRIVATE
    asteroids_core
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(asteroids_tests)

set_property(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY VS_STARTUP_PROJECT asteroids
)