cmake_minimum_required(VERSION 3.20)

project(Mountain VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure DLLs and EXEs end up in the same directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Enable vcpkg integration if the toolchain file is not provided via command line
if (NOT CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif ()

# Find dependencies via vcpkg
find_package(freetype CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)

# Common options
#add_compile_options(/MP /Gw)
#add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# Subdirectories
add_subdirectory(Profiler)
add_subdirectory(Mountain)
add_subdirectory(TestProject)
add_subdirectory(UnitTests)
