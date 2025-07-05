cmake_minimum_required(VERSION 3.14)

project(MountainExternals LANGUAGES CXX C)


include_directories(".")

file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.c" "*.cc" "*.cxx")
file(GLOB_RECURSE STATIC_LIBS "*.lib")

add_library(MountainExternals STATIC ${SOURCE_FILES})

target_link_libraries(MountainExternals Math ${OpenGL_LIBRARIES} ${STATIC_LIBS})
