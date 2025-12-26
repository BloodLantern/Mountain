enable_testing()

find_package(GTest CONFIG REQUIRED)

set(MOUNTAIN_TESTS_SOURCES
        src/Main.cpp
        src/Containers/TestArray.cpp
        src/Containers/TestList.cpp
        src/Math/TestCalc.cpp
        src/Math/TestEasing.cpp
        src/Math/TestMatrix.cpp
        src/Math/TestMatrix2.cpp
        src/Math/TestMatrix3.cpp
        src/Math/TestQuaternion.cpp
        src/Math/TestVector2.cpp
        src/Math/TestVector2i.cpp
        src/Math/TestVector3.cpp
        src/Math/TestVector4.cpp
        src/Utils/TestColor.cpp
        src/Utils/TestDateTime.cpp
        src/Utils/TestEvent.cpp
        src/Utils/TestGuid.cpp
        src/Utils/TestLogger.cpp
        src/Utils/TestMetaProgramming.cpp
        src/Utils/TestPointer.cpp
        src/Utils/TestStopwatch.cpp
        src/Utils/TestTimeSpan.cpp
        src/Utils/TestUtils.cpp
)

set(MOUNTAIN_TESTS_HEADERS
        src/PrecompiledHeader.hpp
)

add_executable(Tests ${MOUNTAIN_TESTS_SOURCES} ${MOUNTAIN_TESTS_HEADERS})

target_include_directories(Tests PRIVATE src)

target_link_libraries(Tests PRIVATE
        Mountain
        GTest::gtest
        GTest::gtest_main
)

if (MOUNTAIN_OPT_PROFILE)
    target_link_libraries(Tests PRIVATE Profiler)
endif ()

# Precompiled headers
target_precompile_headers(Tests PRIVATE src/PrecompiledHeader.hpp)

include(GoogleTest)
gtest_discover_tests(Tests)
