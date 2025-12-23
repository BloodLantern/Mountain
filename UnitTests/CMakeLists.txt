find_package(GTest CONFIG REQUIRED)

file(GLOB_RECURSE UNITTESTS_SOURCES "src/*.cpp")
file(GLOB_RECURSE UNITTESTS_HEADERS "src/*.hpp")

add_executable(UnitTests ${UNITTESTS_SOURCES} ${UNITTESTS_HEADERS})

target_include_directories(UnitTests PRIVATE src)

target_link_libraries(UnitTests PRIVATE
    Mountain
    Profiler
    GTest::gtest
    GTest::gtest_main
)

# Precompiled headers
target_precompile_headers(UnitTests PRIVATE src/Common.hpp)

include(GoogleTest)
gtest_discover_tests(UnitTests)
