cmake_minimum_required(VERSION 3.14)

project(MountainTests LANGUAGES CXX)

add_compile_definitions(MOUNTAIN_EXPORT)

include_directories(".")
include_directories(SYSTEM ${MathLibrary_SOURCE_DIR} ${MountainExternals_SOURCE_DIR} ${Mountain_SOURCE_DIR})

file(GLOB_RECURSE SOURCE_FILES "*.cpp")

add_executable(MountainTests ${SOURCE_FILES})

target_link_libraries(MountainTests Mountain)

if (WIN32)
    if (MATH_BUILD_SHARED_LIBS)
        add_custom_command(TARGET MountainTests POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Math>
            $<TARGET_FILE_DIR:MountainTests>
            COMMENT "Copy Math shared library to MountainTests output directory"
        )
    endif ()

    add_custom_command(TARGET MountainTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Mountain>
        $<TARGET_FILE_DIR:MountainTests>
        COMMENT "Copy Mountain shared library to MountainTests output directory"
    )
endif ()
