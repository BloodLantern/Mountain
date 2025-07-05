cmake_minimum_required(VERSION 3.14)

project(MountainUnitTests LANGUAGES CXX)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

include_directories(SYSTEM ${MathLibrary_SOURCE_DIR} ${MountainExternals_SOURCE_DIR} ${Mountain_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/c67de117379f4d1c889c7581a0a76aa0979c2083.zip # Commit from June 28, 2025
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    MountainUnitTests
    test.cpp
)

target_link_libraries(
    MountainUnitTests
    GTest::gtest_main
    Mountain
)

if (WIN32)
    if (MATH_BUILD_SHARED_LIBS)
        add_custom_command(TARGET MountainUnitTests POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Math>
            $<TARGET_FILE_DIR:MountainUnitTests>
            COMMENT "Copy Math shared library to MountainUnitTests output directory"
        )
    endif ()

    add_custom_command(TARGET MountainUnitTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Mountain>
        $<TARGET_FILE_DIR:MountainUnitTests>
        COMMENT "Copy Mountain shared library to MountainUnitTests output directory"
    )

    add_custom_command(
        TARGET MountainUnitTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:MountainUnitTests> $<TARGET_FILE_DIR:MountainUnitTests>
        COMMAND_EXPAND_LISTS
        COMMENT "Copy GTest shared library to MountainUnitTests output directory"
    )
endif ()

include(GoogleTest)
gtest_discover_tests(MountainUnitTests)
