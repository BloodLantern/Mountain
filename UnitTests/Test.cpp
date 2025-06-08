#include <gtest/gtest.h>

#include "Mountain/Containers/Allocator.hpp"

using namespace Mountain;

TEST(Allocator, Allocate)
{
    constexpr uint64_t arraySize = 10;

    const uint64_t previousAllocatedBytes = Allocator::GetAllocatedSize();

    int* array = Allocator::Allocate<int>(arraySize);

    EXPECT_NE(array, nullptr);
    EXPECT_EQ(Allocator::GetAllocatedSize() - previousAllocatedBytes, arraySize * sizeof(int));

    array[0] = 1;
    array[9] = 10;

    Allocator::Deallocate(array);

    EXPECT_EQ(Allocator::GetAllocatedSize() - previousAllocatedBytes, 0);
}

TEST(Allocator, Construct)
{
    const uint64_t previousAllocatedBytes = Allocator::GetAllocatedSize();

    int* value = Allocator::Construct<int>(17);

    EXPECT_NE(value, nullptr);
    EXPECT_EQ(Allocator::GetAllocatedSize() - previousAllocatedBytes, sizeof(int));

    EXPECT_EQ(*value, 17);

    *value = 11;

    Allocator::Destroy(value);

    EXPECT_EQ(Allocator::GetAllocatedSize() - previousAllocatedBytes, 0);
}

// TODO - Unit tests
