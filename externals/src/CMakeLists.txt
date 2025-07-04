cmake_minimum_required(VERSION 3.14)

project(MountainExternals LANGUAGES CXX C)

include_directories(".")

file(GLOB_RECURSE SOURCE_FILES "*.cpp")
file(GLOB_RECURSE SOURCE_FILES "*.c")
file(GLOB_RECURSE SOURCE_FILES "*.cc")
file(GLOB_RECURSE SOURCE_FILES "*.cxx")

add_library(Externals STATIC ${SOURCE_FILES})

target_link_libraries(Externals Math)
