cmake_minimum_required(VERSION 3.20)

project(
        Mountain
        VERSION "1.0.0"
        HOMEPAGE_URL "https://github.com/BloodLantern/Mountain"
        DESCRIPTION "A simple game framework similar to MonoGame written in C++23."
        LANGUAGES C CXX
)

include(GNUInstallDirs)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(IS_TOPLEVEL_PROJECT TRUE)
else ()
    set(IS_TOPLEVEL_PROJECT FALSE)
endif ()

option(MOUNTAIN_OPT_BUILD_EXAMPLES "Build Mountain example projects" OFF)
option(MOUNTAIN_OPT_BUILD_TESTS "Build and perform Mountain unit tests" OFF)
option(MOUNTAIN_OPT_INSTALL "Generate and install Mountain targets" OFF)
option(MOUNTAIN_OPT_PROFILE "Enable profiling with Tracy" OFF)

set(EXPORT_NAMESPACE "${PROJECT_NAME}::")

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

# Subdirectories
add_subdirectory(Mountain)

if (MOUNTAIN_OPT_PROFILE)
    add_subdirectory(Profiler)
endif ()

if (MOUNTAIN_OPT_BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif ()

if (MOUNTAIN_OPT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(Tests)
endif ()

if (MOUNTAIN_OPT_INSTALL)
    # Install the library and its headers
    install(
            TARGETS ${PROJECT_NAME}
            EXPORT ${PROJECT_NAME}Targets
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )
    install(FILES ${MOUNTAIN_HEADERS} DESTINATION "include")
endif ()
