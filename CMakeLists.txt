cmake_minimum_required(VERSION 3.14)

project(Mountain LANGUAGES CXX C)

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_UNIT_TESTS "Build unit tests" OFF)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/MP /Zc:__cplusplus) # Manually add some specific global macros on MSVC
endif ()

# Build Math as a static library but still using shared library export declarations
# as we integrate it in a shared library
add_compile_definitions(MATH_SHARED)
add_subdirectory(MathToolbox)
target_compile_definitions(Math MATH_EXPORT)

add_subdirectory(externals/src)
add_subdirectory(src)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()

if (BUILD_UNIT_TESTS)
    add_subdirectory(unit_tests)
endif ()
