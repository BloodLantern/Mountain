#include "Common.hpp"

#include <Mountain/Utils/Pointer.hpp>

TEST(Utils_Pointer, Basics)
{
    const Pointer<int> ptr = Pointer<int>::New(0);

    EXPECT_EQ(ptr.GetReferenceCounter()->GetStrong(), 1);
    EXPECT_EQ(ptr.GetReferenceCounter()->GetWeak(), 0);

    EXPECT_NE(ptr.Get(), nullptr);
}

TEST(Utils_Pointer, WeakReference)
{
    Pointer<int> weakRef;

    {
        const Pointer<int> ptr = Pointer<int>::New(2);

        weakRef = ptr;

        EXPECT_EQ(ptr.GetReferenceCounter()->GetStrong(), 1);
        EXPECT_EQ(weakRef.GetReferenceCounter()->GetStrong(), 1);

        EXPECT_EQ(ptr.GetReferenceCounter()->GetWeak(), 1);
        EXPECT_EQ(weakRef.GetReferenceCounter()->GetWeak(), 1);

        EXPECT_EQ(weakRef.Get(), ptr.Get());

        {
            const Pointer<int> copy = ptr;  // NOLINT(performance-unnecessary-copy-initialization)

            EXPECT_EQ(ptr.GetReferenceCounter()->GetStrong(), 1);
            EXPECT_EQ(ptr.GetReferenceCounter()->GetWeak(), 2);

            EXPECT_EQ(copy.GetReferenceCounter()->GetStrong(), 1);
            EXPECT_EQ(copy.GetReferenceCounter()->GetWeak(), 2);
        }

        EXPECT_EQ(ptr.GetReferenceCounter()->GetStrong(), 1);
        EXPECT_EQ(ptr.GetReferenceCounter()->GetWeak(), 1);

        EXPECT_TRUE(weakRef.IsValid());
    }

    EXPECT_FALSE(weakRef.IsValid());
}

TEST(Utils_Pointer, StrongReference)
{
    Pointer<int> strongRef;

    {
        const Pointer<int> ptr = Pointer<int>::New(-17);

        strongRef = ptr.CreateStrongReference();

        EXPECT_EQ(ptr.GetReferenceCounter()->GetStrong(), 2);
        EXPECT_EQ(strongRef.GetReferenceCounter()->GetStrong(), 2);

        EXPECT_EQ(ptr.GetReferenceCounter()->GetWeak(), 0);
        EXPECT_EQ(strongRef.GetReferenceCounter()->GetWeak(), 0);

        EXPECT_EQ(strongRef.Get(), ptr.Get());

        EXPECT_TRUE(strongRef.IsValid());
    }

    EXPECT_EQ(strongRef.GetReferenceCounter()->GetStrong(), 1);

    EXPECT_TRUE(strongRef.IsValid());
}
