#include "Common.hpp"

#include <Mountain/Window.hpp>
#include <Mountain/Containers/Array.hpp>
#include <Mountain/Ecs/Component/AudioListener.hpp>
#include <Mountain/Ecs/Component/AudioSource.hpp>
#include <Mountain/Ecs/Component/Sprite.hpp>
#include <Mountain/Resource/Shader.hpp>
#include <Mountain/Utils/MetaProgramming.hpp>

struct A {};
struct B : A
{
    B() {}
    B(const B&) {}
    B(B&&) noexcept {}
    ~B() {}
    B& operator=(const B&) { return *this; }
    B& operator=(B&&) noexcept { return *this; }
};

struct C { virtual ~C() = 0; };

struct D { D(int) {} };

enum E {};
enum class Ec {};

void Func() {}

TEST(Utils_MetaProgramming, Meta_IsSame)
{
    EXPECT_TRUE((Meta::IsSame<A, A>));

    EXPECT_FALSE((Meta::IsSame<A, B>));
    EXPECT_FALSE((Meta::IsSame<B, A>));
}

TEST(Utils_MetaProgramming, Meta_Identity)
{
    EXPECT_TRUE((Meta::IsSame<A, Meta::Identity<A>>));
    EXPECT_TRUE((Meta::IsSame<Meta::Identity<A>, A>));
    EXPECT_FALSE((Meta::IsSame<A, Meta::Identity<B>>));
    EXPECT_FALSE((Meta::IsSame<B, Meta::Identity<A>>));
}

TEST(Utils_MetaProgramming, Meta_LogicalAnd)
{
    EXPECT_TRUE((Meta::LogicalAnd<Meta::IsSame<A, A>, Meta::IsSame<B, B>>));
    EXPECT_FALSE((Meta::LogicalAnd<Meta::IsSame<A, A>, Meta::IsSame<B, B>, Meta::IsSame<A, B>>));
}

TEST(Utils_MetaProgramming, Meta_LogicalOr)
{
    EXPECT_TRUE((Meta::LogicalOr<Meta::IsSame<A, A>, Meta::IsSame<B, B>>));
    EXPECT_TRUE((Meta::LogicalOr<Meta::IsSame<A, A>, Meta::IsSame<B, B>, Meta::IsSame<A, B>>));
}

TEST(Utils_MetaProgramming, Meta_IsBaseOf)
{
    EXPECT_TRUE((Meta::IsBaseOf<A, B>));
    EXPECT_TRUE((Meta::IsBaseOf<A, A>));
    EXPECT_FALSE((Meta::IsBaseOf<B, A>));
}

TEST(Utils_MetaProgramming, Meta_AllSame)
{
    EXPECT_TRUE((Meta::AllSame<A, A, A, A, A, A>));
    EXPECT_FALSE((Meta::AllSame<A, A, B, A, A, A>));
}

TEST(Utils_MetaProgramming, Meta_IsAny)
{
    EXPECT_TRUE((Meta::IsAny<A, B, B, B, A, B>));
    EXPECT_FALSE((Meta::IsAny<A, B, B, B>));
}

TEST(Utils_MetaProgramming, Meta_IsArray)
{
    EXPECT_TRUE(Meta::IsArray<int[]>);
    EXPECT_FALSE(Meta::IsArray<A>);
    EXPECT_FALSE((Meta::IsArray<Array<int, 5>>));
}

TEST(Utils_MetaProgramming, Meta_IsPointer)
{
    EXPECT_TRUE(Meta::IsPointer<int*>);
    EXPECT_FALSE(Meta::IsPointer<A>);
    EXPECT_FALSE(Meta::IsPointer<Pointer<int>>);
}

TEST(Utils_MetaProgramming, Meta_IsClass)
{
    EXPECT_TRUE(Meta::IsClass<A>);
    EXPECT_FALSE(Meta::IsClass<int>);
    EXPECT_FALSE(Meta::IsClass<int*>);
}

TEST(Utils_MetaProgramming, Meta_IsEnum)
{
    EXPECT_TRUE(Meta::IsEnum<E>);
    EXPECT_TRUE(Meta::IsEnum<Ec>);
    EXPECT_FALSE(Meta::IsEnum<int>);
    EXPECT_FALSE(Meta::IsEnum<A>);
}

TEST(Utils_MetaProgramming, Meta_IsIntegral)
{
    EXPECT_TRUE(Meta::IsIntegral<int>);
    EXPECT_TRUE(Meta::IsIntegral<bool>);
    EXPECT_TRUE(Meta::IsIntegral<char>);
    EXPECT_FALSE(Meta::IsIntegral<float>);
    EXPECT_FALSE(Meta::IsIntegral<A>);
    EXPECT_FALSE(Meta::IsIntegral<E>);
    EXPECT_FALSE(Meta::IsIntegral<Ec>);
}

TEST(Utils_MetaProgramming, Meta_IsFloatingPoint)
{
    EXPECT_TRUE(Meta::IsFloatingPoint<float>);
    EXPECT_TRUE(Meta::IsFloatingPoint<double>);
    EXPECT_FALSE(Meta::IsFloatingPoint<int>);
    EXPECT_FALSE(Meta::IsFloatingPoint<A>);
    EXPECT_FALSE(Meta::IsFloatingPoint<E>);
    EXPECT_FALSE(Meta::IsFloatingPoint<Ec>);
}

TEST(Utils_MetaProgramming, Meta_IsAbstract)
{
    EXPECT_TRUE(Meta::IsAbstract<C>);
    EXPECT_FALSE(Meta::IsAbstract<A>);
    EXPECT_FALSE(Meta::IsAbstract<E>);
    EXPECT_FALSE(Meta::IsAbstract<Ec>);
}

TEST(Utils_MetaProgramming, Meta_IsDefaultConstructible)
{
    EXPECT_TRUE(Meta::IsDefaultConstructible<A>);
    EXPECT_TRUE(Meta::IsDefaultConstructible<E>);
    EXPECT_FALSE(Meta::IsDefaultConstructible<C>);
    EXPECT_FALSE(Meta::IsDefaultConstructible<D>);
}

TEST(Utils_MetaProgramming, Meta_IsCopyAssignable)
{
    EXPECT_TRUE(Meta::IsCopyAssignable<A>);
    EXPECT_TRUE(Meta::IsCopyAssignable<E>);
    EXPECT_FALSE(Meta::IsCopyAssignable<Window>);
}

TEST(Utils_MetaProgramming, Meta_IsMoveAssignable)
{
    EXPECT_TRUE(Meta::IsMoveAssignable<A>);
    EXPECT_TRUE(Meta::IsMoveAssignable<E>);
    EXPECT_FALSE(Meta::IsMoveAssignable<Window>);
}

TEST(Utils_MetaProgramming, Meta_IsTriviallyCopyable)
{
    EXPECT_TRUE(Meta::IsTriviallyCopyable<A>);
    EXPECT_TRUE(Meta::IsTriviallyCopyable<E>);
    EXPECT_FALSE(Meta::IsTriviallyCopyable<B>);
    EXPECT_FALSE(Meta::IsTriviallyCopyable<Window>);
}

TEST(Utils_MetaProgramming, Meta_IsTriviallyAssignable)
{
    EXPECT_TRUE((Meta::IsTriviallyAssignable<A, A>));
    EXPECT_FALSE((Meta::IsTriviallyAssignable<B, B>));
}

TEST(Utils_MetaProgramming, Meta_IsTriviallyConstructible)
{
    EXPECT_TRUE(Meta::IsTriviallyConstructible<A>);
    EXPECT_FALSE(Meta::IsTriviallyConstructible<B>);
}

TEST(Utils_MetaProgramming, Meta_IsTriviallyCopyAssignable)
{
    EXPECT_TRUE(Meta::IsTriviallyCopyAssignable<A>);
    EXPECT_FALSE(Meta::IsTriviallyCopyAssignable<B>);
}

TEST(Utils_MetaProgramming, Meta_IsTriviallyCopyConstructible)
{
    EXPECT_TRUE(Meta::IsTriviallyCopyConstructible<A>);
    EXPECT_FALSE(Meta::IsTriviallyCopyConstructible<B>);
}

TEST(Utils_MetaProgramming, Meta_IsTriviallyDefaultConstructible)
{
    EXPECT_TRUE(Meta::IsTriviallyDefaultConstructible<A>);
    EXPECT_FALSE(Meta::IsTriviallyDefaultConstructible<B>);
}

TEST(Utils_MetaProgramming, Meta_IsTriviallyDestructible)
{
    EXPECT_TRUE(Meta::IsTriviallyDestructible<A>);
    EXPECT_FALSE(Meta::IsTriviallyDestructible<B>);
}

TEST(Utils_MetaProgramming, Meta_IsTriviallyMoveAssignable)
{
    EXPECT_TRUE(Meta::IsTriviallyMoveAssignable<A>);
    EXPECT_FALSE(Meta::IsTriviallyMoveAssignable<B>);
}

TEST(Utils_MetaProgramming, Meta_IsTriviallyMoveConstructible)
{
    EXPECT_TRUE(Meta::IsTriviallyMoveConstructible<A>);
    EXPECT_FALSE(Meta::IsTriviallyMoveConstructible<B>);
}

TEST(Utils_MetaProgramming, Meta_IsConst)
{
    EXPECT_TRUE(Meta::IsConst<const A>);
    EXPECT_FALSE(Meta::IsConst<A>);
}

TEST(Utils_MetaProgramming, Meta_IsVolatile)
{
    EXPECT_TRUE(Meta::IsVolatile<volatile A>);
    EXPECT_FALSE(Meta::IsVolatile<A>);
}

TEST(Utils_MetaProgramming, Meta_IsConstVolatileQualified)
{
    EXPECT_TRUE(Meta::IsConstVolatileQualified<volatile A>);
    EXPECT_TRUE(Meta::IsConstVolatileQualified<const A>);
    EXPECT_TRUE(Meta::IsConstVolatileQualified<const volatile A>);
    EXPECT_FALSE(Meta::IsConstVolatileQualified<A>);
}

TEST(Utils_MetaProgramming, Meta_IsReference)
{
    EXPECT_TRUE(Meta::IsReference<A&>);
    EXPECT_TRUE(Meta::IsReference<A&&>);
    EXPECT_FALSE(Meta::IsReference<A>);
}

TEST(Utils_MetaProgramming, Meta_IsInvocable)
{
    EXPECT_TRUE(Meta::IsInvocable<decltype(Func)>);
    EXPECT_TRUE(Meta::IsInvocable<decltype([]{})>);
    EXPECT_TRUE(Meta::IsInvocable<std::function<void()>>);
    EXPECT_TRUE((Meta::IsInvocable<Identity, int>));
    EXPECT_TRUE((Meta::IsInvocable<std::identity, int>));
    EXPECT_FALSE(Meta::IsInvocable<A>);
}

TEST(Utils_MetaProgramming, Meta_EnableIf)
{
    EXPECT_TRUE((Meta::IsSame<Meta::EnableIf<true>, void>));
    // We cannot check for EnableIf<false> as it wouldn't compile
}

TEST(Utils_MetaProgramming, Meta_RemoveArraySpecifier)
{
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveArraySpecifier<int[]>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveArraySpecifier<int>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveArraySpecifier<const int*&>, const int*&>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveArraySpecifier<const int[]>, const int>));
    EXPECT_FALSE((Meta::IsSame<Meta::RemoveArraySpecifier<float[]>, int>));
}

TEST(Utils_MetaProgramming, Meta_RemovePointerSpecifier)
{
    EXPECT_TRUE((Meta::IsSame<Meta::RemovePointerSpecifier<int*>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemovePointerSpecifier<int>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemovePointerSpecifier<const int*&>, const int*&>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemovePointerSpecifier<const int*>, const int>));
    EXPECT_FALSE((Meta::IsSame<Meta::RemovePointerSpecifier<float*>, int>));
}

TEST(Utils_MetaProgramming, Meta_RemoveConstSpecifier)
{
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveConstSpecifier<const int>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveConstSpecifier<int>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveConstSpecifier<const int*&>, const int*&>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveConstSpecifier<const int* const>, const int*>));
    EXPECT_FALSE((Meta::IsSame<Meta::RemoveConstSpecifier<const float>, int>));
}

TEST(Utils_MetaProgramming, Meta_RemoveVolatileSpecifier)
{
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveVolatileSpecifier<volatile int>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveVolatileSpecifier<int>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveVolatileSpecifier<volatile int*&>, volatile int*&>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveVolatileSpecifier<volatile int* volatile>, volatile int*>));
    EXPECT_FALSE((Meta::IsSame<Meta::RemoveVolatileSpecifier<volatile float>, int>));
}

TEST(Utils_MetaProgramming, Meta_RemoveCvSpecifier)
{
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveCvSpecifier<const volatile int>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveCvSpecifier<int>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveCvSpecifier<const int* const>, const int*>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveCvSpecifier<volatile int* volatile>, volatile int*>));
    EXPECT_FALSE((Meta::IsSame<Meta::RemoveCvSpecifier<const volatile float>, int>));
}

TEST(Utils_MetaProgramming, Meta_RemoveReferenceSpecifier)
{
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveReferenceSpecifier<int&>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveReferenceSpecifier<int>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveReferenceSpecifier<const int&>, const int>));
    EXPECT_FALSE((Meta::IsSame<Meta::RemoveReferenceSpecifier<float&>, int>));
}

TEST(Utils_MetaProgramming, Meta_RemoveCvRefSpecifier)
{
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveCvRefSpecifier<const volatile int&>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveCvRefSpecifier<int>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveCvRefSpecifier<const int&>, int>));
    EXPECT_FALSE((Meta::IsSame<Meta::RemoveCvRefSpecifier<const volatile float&>, int>));
}

TEST(Utils_MetaProgramming, Meta_RemoveCvPointerSpecifier)
{
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveCvPointerSpecifier<const volatile int*>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveCvPointerSpecifier<int>, int>));
    EXPECT_TRUE((Meta::IsSame<Meta::RemoveCvPointerSpecifier<const int*>, int>));
    EXPECT_FALSE((Meta::IsSame<Meta::RemoveCvPointerSpecifier<const volatile float*>, int>));
}

TEST(Utils_MetaProgramming, Meta_IsFunction)
{
    EXPECT_TRUE(Meta::IsFunction<decltype(Func)>);
    EXPECT_FALSE(Meta::IsFunction<decltype([]{})>);
    EXPECT_FALSE(Meta::IsFunction<std::function<void()>>);
    EXPECT_FALSE(Meta::IsFunction<Identity>);
    EXPECT_FALSE(Meta::IsFunction<std::identity>);
    EXPECT_FALSE(Meta::IsFunction<A>);
}

TEST(Utils_MetaProgramming, Meta_IsStandardFunction)
{
    EXPECT_FALSE(Meta::IsStandardFunction<decltype(Func)>);
    EXPECT_FALSE(Meta::IsStandardFunction<decltype([]{})>);
    EXPECT_TRUE(Meta::IsStandardFunction<std::function<void()>>);
    EXPECT_FALSE(Meta::IsStandardFunction<Identity>);
    EXPECT_FALSE(Meta::IsStandardFunction<std::identity>);
    EXPECT_FALSE(Meta::IsStandardFunction<A>);
}

TEST(Utils_MetaProgramming, Meta_IsMountainPointer)
{
    EXPECT_FALSE(Meta::IsMountainPointer<int*>);
    EXPECT_FALSE(Meta::IsMountainPointer<Window*>);
    EXPECT_TRUE(Meta::IsMountainPointer<Pointer<int>>);
    EXPECT_FALSE(Meta::IsMountainPointer<A>);
}

TEST(Utils_MetaProgramming, Meta_IsException)
{
    EXPECT_TRUE(Meta::IsException<std::exception>);
    EXPECT_TRUE(Meta::IsException<Exception>);
    EXPECT_TRUE(Meta::IsException<std::logic_error>);
    EXPECT_TRUE(Meta::IsException<ArgumentException>);
    EXPECT_FALSE(Meta::IsException<A>);
    EXPECT_FALSE(Meta::IsException<int>);
}

TEST(Utils_MetaProgramming, Meta_IsMountainException)
{
    EXPECT_FALSE(Meta::IsMountainException<std::exception>);
    EXPECT_TRUE(Meta::IsMountainException<Exception>);
    EXPECT_FALSE(Meta::IsMountainException<std::logic_error>);
    EXPECT_TRUE(Meta::IsMountainException<ArgumentException>);
    EXPECT_FALSE(Meta::IsMountainException<A>);
    EXPECT_FALSE(Meta::IsMountainException<int>);
}

TEST(Utils_MetaProgramming, Meta_IsNativeType)
{
    EXPECT_TRUE(Meta::IsNativeType<int>);
    EXPECT_TRUE(Meta::IsNativeType<bool>);
    EXPECT_TRUE(Meta::IsNativeType<char>);
    EXPECT_TRUE(Meta::IsNativeType<float>);
    EXPECT_FALSE(Meta::IsNativeType<A>);
}

TEST(Utils_MetaProgramming, Meta_IsIntegralOrFloating)
{
    EXPECT_TRUE(Meta::IsIntegralOrFloating<int>);
    EXPECT_TRUE(Meta::IsIntegralOrFloating<bool>);
    EXPECT_TRUE(Meta::IsIntegralOrFloating<char>);
    EXPECT_TRUE(Meta::IsIntegralOrFloating<float>);
    EXPECT_FALSE(Meta::IsIntegralOrFloating<A>);
}

TEST(Utils_MetaProgramming, Meta_IsMathType)
{
    EXPECT_TRUE(Meta::IsMathType<Vector2>);
    EXPECT_TRUE(Meta::IsMathType<Matrix>);
    EXPECT_TRUE(Meta::IsMathType<Quaternion>);
    EXPECT_TRUE(Meta::IsMathType<Vector2i>);
    EXPECT_FALSE(Meta::IsMathType<int>);
    EXPECT_FALSE(Meta::IsMathType<float>);
    EXPECT_FALSE(Meta::IsMathType<A>);
}

TEST(Utils_MetaProgramming, Meta_IsColorType)
{
    EXPECT_TRUE(Meta::IsColor<Color>);
    EXPECT_TRUE(Meta::IsColor<ColorHsva>);
    EXPECT_FALSE(Meta::IsColor<Vector2>);
    EXPECT_FALSE(Meta::IsColor<float>);
    EXPECT_FALSE(Meta::IsColor<A>);
}

TEST(Utils_MetaProgramming, Meta_IsConvertibleTo)
{
    EXPECT_TRUE((Meta::IsConvertibleTo<int, float>));
    EXPECT_TRUE((Meta::IsConvertibleTo<int, bool>));
    EXPECT_FALSE((Meta::IsConvertibleTo<Color, ColorHsva>));
    EXPECT_FALSE((Meta::IsConvertibleTo<ColorHsva, Color>));
    EXPECT_TRUE((Meta::IsConvertibleTo<B*, A*>));
    EXPECT_FALSE((Meta::IsConvertibleTo<A*, B*>));
}

TEST(Utils_MetaProgramming, Meta_IsEqualityComparable)
{
    EXPECT_TRUE(Meta::IsEqualityComparable<int>);
    EXPECT_TRUE(Meta::IsEqualityComparable<Guid>);
    EXPECT_TRUE(Meta::IsEqualityComparable<Color>);
    EXPECT_TRUE(Meta::IsEqualityComparable<Vector2>);
    EXPECT_FALSE(Meta::IsEqualityComparable<A>);
}

TEST(Utils_MetaProgramming, Meta_IsEqualityComparableWith)
{
    EXPECT_TRUE((Meta::IsEqualityComparableWith<int, float>));
    EXPECT_TRUE((Meta::IsEqualityComparableWith<int, bool>));
    EXPECT_TRUE((Meta::IsEqualityComparableWith<Color, Color>));
    EXPECT_TRUE((Meta::IsEqualityComparableWith<ColorHsva, ColorHsva>));
    EXPECT_FALSE((Meta::IsEqualityComparableWith<Color, ColorHsva>));
    EXPECT_FALSE((Meta::IsEqualityComparableWith<ColorHsva, Color>));
    EXPECT_FALSE((Meta::IsEqualityComparableWith<A, A>));
}
