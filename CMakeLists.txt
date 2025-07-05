cmake_minimum_required(VERSION 3.14)

project(Mountain LANGUAGES CXX C)

option(MOUNTAIN_BUILD_TESTS "Build tests" OFF)
option(MOUNTAIN_BUILD_UNIT_TESTS "Build unit tests" OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MATH_DEFINE_FORMATTER ON)

if (MSVC)
    add_compile_options(/MP /Zc:__cplusplus) # Manually add some specific compilation flags on MSVC
endif ()

find_package(OpenGL REQUIRED)

# Build Math as a static library but still using shared library export declarations
# as we integrate it in a shared library
add_compile_definitions(MATH_SHARED)
add_subdirectory(MathToolbox)
target_compile_definitions(Math PUBLIC MATH_EXPORT)

# Add global Mountain macros
add_compile_definitions(IMGUI_EXPORT RAPID_XML_EXPORT AL_ALEXT_PROTOTYPES MATH_DEFINE_FORMATTER)

# Add global Mountain include directories
include_directories(SYSTEM ${MathLibrary_SOURCE_DIR} ${OpenGL_INCLUDE_DIRS})

add_subdirectory(externals/src)
add_subdirectory(src)

if (MOUNTAIN_BUILD_TESTS)
    add_subdirectory(tests)
endif ()

if (MOUNTAIN_BUILD_UNIT_TESTS)
    add_subdirectory(unit_tests)
endif ()
