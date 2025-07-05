cmake_minimum_required(VERSION 3.14)

project(MountainLibrary LANGUAGES CXX)

add_compile_definitions(MOUNTAIN_EXPORT)

include_directories(".")
include_directories(SYSTEM ${MathLibrary_SOURCE_DIR} ${MountainExternals_SOURCE_DIR})

file(GLOB_RECURSE SOURCE_FILES "*.cpp")

add_library(Mountain SHARED ${SOURCE_FILES})

target_link_libraries(Mountain Math MountainExternals)
