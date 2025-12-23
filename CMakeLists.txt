cmake_minimum_required(VERSION 3.20)

project(Mountain VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable vcpkg integration if the toolchain file is not provided via command line
if (NOT CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif ()

# Find dependencies via vcpkg
find_package(freetype CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
# stb and minimp3 are usually header-only or custom-built from vcpkg,
# but they might not provide CONFIG files.
# Looking at vcpkg.json, they are listed.

# Common options
#add_compile_options(/MP /Gw)
#add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# Subdirectories
add_subdirectory(Profiler)
add_subdirectory(Mountain)
add_subdirectory(Tests)
add_subdirectory(UnitTests)
