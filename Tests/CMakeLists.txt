find_package(GTest CONFIG REQUIRED)

file(GLOB_RECURSE MOUNTAIN_TESTS_SOURCES "src/*.cpp")
file(GLOB_RECURSE MOUNTAIN_TESTS_HEADERS "src/*.hpp")

add_executable(Tests ${MOUNTAIN_TESTS_SOURCES} ${MOUNTAIN_TESTS_HEADERS})

target_include_directories(Tests PRIVATE src)

target_link_libraries(Tests PRIVATE
    Mountain
    Profiler
    GTest::gtest
    GTest::gtest_main
)

# Precompiled headers
target_precompile_headers(Tests PRIVATE src/Common.hpp)

include(GoogleTest)
gtest_discover_tests(Tests)
