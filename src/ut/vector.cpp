#include <iostream>
#include <string>
#include <type_traits>
#include <memory>
#include "gtest/gtest.h"
#include "../vector.h"

namespace epm
{

class VectorTests : public ::testing::Test
{
  public:
    VectorTests(){};

    void SetUp() override{};

    void TearDown() override{};

    ~VectorTests(){};

    Vector<int> vector;

    Vector<double> getDoubles()
    {
        Vector<double> d{1.0, 2.0, 3.0, 4.0, 5.0};
        return d;
    }
};

TEST_F(VectorTests, IsInitialCapacitySetTo10)
{
    ASSERT_EQ(vector.getCapacity(), 10);
}

TEST_F(VectorTests, IsInitialSizeSetTo0)
{
    ASSERT_EQ(vector.getSize(), 0);
}

TEST_F(VectorTests, CheckIfOnePushedElementIsTheOnlyOne)
{
    vector.push_back(42);
    ASSERT_EQ(vector.getSize(), 1);
    ASSERT_EQ(vector[0], 42);
}

TEST_F(VectorTests, CheckIfOrderOfElementsReflectsOrderOfPushing)
{
    vector.push_back(3);
    vector.push_back(2);
    vector.push_back(1);
    ASSERT_EQ(vector[0], 3);
    ASSERT_EQ(vector[1], 2);
    ASSERT_EQ(vector[2], 1);
}

TEST_F(VectorTests, CheckIfVectorHas3ElementsAfterPushing3)
{
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    ASSERT_EQ(vector.getSize(), 3);
}

TEST_F(VectorTests, CheckIfCapacityIsShrinkAfterDownsizing)
{
    ASSERT_EQ(vector.getCapacity(), 10);
    vector.resize(7);
    ASSERT_EQ(vector.getCapacity(), 7);
}

TEST_F(VectorTests, CheckIfElementsAreDeletedAfterResizingDown)
{
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    vector.resize(3);
    ASSERT_EQ(vector.getSize(), 3);
}

TEST_F(VectorTests, CheckIfCapacityIsProperlySetAfterResizingUp)
{
    ASSERT_EQ(vector.getCapacity(), 10);
    vector.resize(17);
    ASSERT_EQ(vector.getCapacity(), 17);
}

TEST_F(VectorTests,
       CheckIfVectorDoesNotLostElementsAfterRelocationCausedByResizingUp)
{
    vector.push_back(9);
    vector.push_back(8);
    vector.push_back(7);
    vector.push_back(6);
    vector.resize(17);
    ASSERT_EQ(vector[0], 9);
    ASSERT_EQ(vector[1], 8);
    ASSERT_EQ(vector[2], 7);
    ASSERT_EQ(vector[3], 6);
}

TEST_F(VectorTests,
       CheckIfVectorDoesNotLostElementsAfterRelocationCausedByResizingDown)
{
    vector.push_back(9);
    vector.push_back(8);
    vector.push_back(7);
    vector.push_back(6);
    vector.push_back(5);
    vector.push_back(4);
    vector.push_back(3);
    vector.push_back(2);
    vector.resize(8);
    ASSERT_EQ(vector[0], 9);
    ASSERT_EQ(vector[1], 8);
    ASSERT_EQ(vector[2], 7);
    ASSERT_EQ(vector[3], 6);
    ASSERT_EQ(vector[4], 5);
    ASSERT_EQ(vector[5], 4);
    ASSERT_EQ(vector[6], 3);
    ASSERT_EQ(vector[7], 2);
}

TEST_F(VectorTests, CheckIfEmptyReturnsTrueWhenVectorIsReallyEmpty)
{
    ASSERT_EQ(vector.empty(), true);
}

TEST_F(VectorTests, CheckIfEmptyReturnsFalseWhenVectorIsNotEmpty)
{
    vector.push_back(0);
    ASSERT_EQ(vector.empty(), false);
}

TEST_F(VectorTests, CheckIfEmptyReturnsTrueWhenVectorIsResizedToZero)
{
    vector.push_back(0);
    vector.push_back(1);
    vector.resize(0);
    ASSERT_EQ(vector.empty(), true);
}

TEST_F(VectorTests, CheckIfValueTypeIsReturnedProperly)
{
    ::testing::StaticAssertTypeEq<float, Vector<float>::value_type>();
}

TEST_F(VectorTests, CheckIfReferenceTypeIsReturnedProperly)
{
    ::testing::StaticAssertTypeEq<float&, Vector<float>::reference>();
}

TEST_F(VectorTests, CheckIfConstReferenceTypeIsReturnedProperly)
{
    ::testing::StaticAssertTypeEq<const float&,
                                  Vector<float>::const_reference>();
}

TEST_F(VectorTests, CheckIfOneElementIsRemoved)
{
    vector.push_back(5);
    vector.pop_back();
    ASSERT_EQ(vector.getSize(), 0);
}

TEST_F(VectorTests,
       CheckIfVectorHasOneElementAfterPushingPopingAndPushinAgain)
{
    vector.push_back(5);
    vector.pop_back();
    vector.push_back(7);
    ASSERT_EQ(vector.getSize(), 1);
    ASSERT_EQ(vector[0], 7);
}

TEST_F(VectorTests, CheckIfPoppingElementDoesNotAffectCapacity)
{
    vector.push_back(5);
    ASSERT_EQ(vector.getCapacity(), 10);
    vector.pop_back();
    ASSERT_EQ(vector.getCapacity(), 10);
}

TEST_F(VectorTests, CheckIfPopBackOnEmptyVectorDoesNothing)
{
    vector.pop_back();
    ASSERT_EQ(vector.getSize(), 0);
}

TEST_F(VectorTests, CheckIfAtReturnsProperElements)
{
    vector.push_back(99);
    vector.push_back(89);
    vector.push_back(79);
    ASSERT_EQ(vector.at(0), 99);
    ASSERT_EQ(vector.at(1), 89);
    ASSERT_EQ(vector.at(2), 79);
}

TEST_F(VectorTests, CheckIfFrontReturnsLastElement)
{
    vector.push_back(99);
    vector.push_back(89);
    vector.push_back(79);
    ASSERT_EQ(vector.front(), 99);
}

TEST_F(VectorTests, CheckIfBackReturnsLastElement)
{
    vector.push_back(99);
    vector.push_back(89);
    vector.push_back(79);
    ASSERT_EQ(vector.back(), 79);
}

TEST_F(VectorTests, CheckIfAtThrowsWhenIndexIsBelowBounds)
{
    ASSERT_THROW(vector.at(-1), std::out_of_range);
}

TEST_F(VectorTests, CheckIfAtThrowsWhenIndexIsAboveBounds)
{
    ASSERT_THROW(vector.at(1), std::out_of_range);
}

TEST_F(VectorTests, CheckIfAtDoesNotThrowWhenIndexIsOk)
{
    vector.push_back(99);
    ASSERT_NO_THROW(vector.at(0));
}

TEST_F(VectorTests, CheckIfAtThrowsLogicErrorWhenEmptyAndAtCalled)
{
    ASSERT_THROW(vector.at(0), std::logic_error);
}

TEST_F(VectorTests, GetIteratorToTheBeginAndCheckItsValue)
{
    vector.push_back(11);
    vector.push_back(12);
    auto begin = vector.begin();
    ASSERT_EQ(*begin, 11);
}

TEST_F(VectorTests, GetIteratorToTheEndAndCheckItsValue)
{
    vector.push_back(11);
    vector.push_back(22);
    auto end = vector.end();
    end--;
    ASSERT_EQ(*end, 22);
}

TEST_F(VectorTests, TryToUseIteratorsWithForEach)
{
    for (auto i = 0; i < 10; ++i)
        vector.push_back(i);
    auto i = 0;
    for (auto num : vector)
    {
        ASSERT_EQ(num, i++);
    }
}

TEST_F(VectorTests, TryToUseConstIteratorsWithinFor)
{
    for (auto i = 0; i < 10; ++i)
        vector.push_back(i);
    auto i = 0;
    for (auto it = vector.cbegin(); it != vector.cend(); ++it, ++i)
    {
        ASSERT_EQ(*it, i);
    }
}

TEST_F(VectorTests, ConstructUsingStdInitializersList)
{
    Vector<int> v{1, 2, 3, 4, 5};
    auto i = 0;
    for (auto it = vector.cbegin(); it != vector.cend(); ++it, ++i)
    {
        ASSERT_EQ(*it, i);
    }
}

TEST_F(VectorTests, ConstructVectorOfStrings)
{
    Vector<std::string> v;
    v.push_back(std::string("1"));
    v.push_back(std::string("2"));
    ASSERT_EQ(v[0], "1");
    ASSERT_EQ(v[1], "2");
}

TEST_F(VectorTests, ConstructUsingStdInitializersListAndReadByOrdinaryFor)
{
    Vector<int> v{1, 2, 3, 4, 5};
    auto i = 0;
    for (auto i = 0u; i < vector.getSize(); ++i)
    {
        ASSERT_EQ(vector[i], i);
    }
}

TEST_F(VectorTests, ConstructUsingNumberOfElementsAndValue)
{
    Vector<int> v(5, 42);
    ASSERT_EQ(v.getSize(), 5);
    for (auto i = 0u; i < v.getSize(); ++i)
    {
        ASSERT_EQ(v[i], 42);
    }
}

TEST_F(VectorTests, ConstructUsingCopyConstructorAndTrivialType)
{
    Vector<int> v1(5, 123);
    Vector<int> v2(v1);
    ASSERT_EQ(v1.getSize(), v2.getSize());
    for (auto i = 0u; i < v2.getSize(); ++i)
    {
        ASSERT_EQ(v2[i], 123);
    }
}

TEST_F(VectorTests, CheckIfElementsAreDeletedAfterCallingClear)
{
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.clear();
    ASSERT_EQ(vector.getSize(), 0);
}

TEST_F(VectorTests, CheckIfTwoEqualVectorsAreConsideredAsEqual)
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{1, 2, 3};
    ASSERT_TRUE(v1 == v2);
}

TEST_F(VectorTests, CheckIfTwoNotEqualVectorsAreConsideredAsNotEqual)
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{1, 2, 4};
    ASSERT_FALSE(v1 == v2);
}

TEST_F(VectorTests, CheckIfTwoEqualVectorsAreConsideredAsEqual_1)
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{1, 2, 3};
    ASSERT_FALSE(v1 != v2);
}

TEST_F(VectorTests, CheckIfTwoNotEqualVectorsAreConsideredAsNotEqual_1)
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{1, 2, 4};
    ASSERT_TRUE(v1 != v2);
}

TEST_F(VectorTests, CheckIfVectorWithDifferentSizesAreNotEqual)
{
    Vector<int> v1{1, 2, 3, 4};
    Vector<int> v2{1, 2, 3};
    ASSERT_FALSE(v1 == v2);
}

TEST_F(VectorTests, CheckIfVectorWithDifferentSizesAreNotEqual_1)
{
    Vector<int> v1{1, 2, 3, 4};
    Vector<int> v2{1, 2, 3};
    ASSERT_TRUE(v1 != v2);
}

TEST_F(VectorTests, CheckIfVectorWithDifferentTypesAreEqual)
{
    Vector<int> v1{1, 2, 3};
    Vector<float> v2{1.0, 2.0, 3.0};
    ASSERT_TRUE(v1 != v2);
}

TEST_F(VectorTests, CheckIfVectorWithDifferentTypesAreEqual_1)
{
    Vector<int> v1{1, 2, 3, 4};
    Vector<float> v2{1.0, 2.0, 3.0};
    ASSERT_FALSE(v1 == v2);
}

TEST_F(VectorTests, SwapContentOfTwoVectors)
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{3, 2, 1};
    v1.swap(v2);

    ASSERT_EQ(v1[0], 3);
    ASSERT_EQ(v1[1], 2);
    ASSERT_EQ(v1[2], 1);
    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v2[1], 2);
    ASSERT_EQ(v2[2], 3);
}

TEST_F(VectorTests, SwapContentOfTwoVectorsUsingStdSwap)
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{3, 2, 1};
    std::swap(v1, v2);

    ASSERT_EQ(v1[0], 3);
    ASSERT_EQ(v1[1], 2);
    ASSERT_EQ(v1[2], 1);
    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v2[1], 2);
    ASSERT_EQ(v2[2], 3);
}

TEST_F(VectorTests, CheckIfVectorIsMoveAssignable)
{
    ASSERT_TRUE(std::is_move_assignable<Vector<int>>());
    ASSERT_TRUE(std::is_move_assignable<Vector<std::string>>());
}

TEST_F(VectorTests, CheckIfVectorIsMoveConstructible)
{
    ASSERT_TRUE(std::is_move_constructible<Vector<int>>());
    ASSERT_TRUE(std::is_move_constructible<Vector<std::string>>());
}

TEST_F(VectorTests, AssignSomeElementsToExistingVectorAndCheckThem)
{
    Vector<double> d{1.0, 2.0, 3.0, 4.0, 5.0};
    d.assign(8, 3.14);
    ASSERT_EQ(d.getSize(), 8);
    ASSERT_EQ(d[0], 3.14);
    ASSERT_EQ(d[7], 3.14);
}

TEST_F(VectorTests, AssignMoreThanCapacityElementsToExistingVectorAndCheckThem)
{
    Vector<double> d{1.0, 2.0, 3.0, 4.0, 5.0};
    d.assign(100, 3.14);
    ASSERT_EQ(d.getSize(), 100);
    ASSERT_EQ(d[0], 3.14);
    ASSERT_EQ(d[99], 3.14);
}

TEST_F(VectorTests, AssignNewElementsUsingStdInitializerList)
{
    Vector<double> d{1.0, 2.0, 3.0, 4.0, 5.0};
    d.assign({6.0, 7.0});
    ASSERT_EQ(d.getSize(), 2);
    ASSERT_EQ(d[0], 6.0);
    ASSERT_EQ(d[1], 7.0);
}

TEST_F(VectorTests, AssignMoreThanCapacityElementsUsingStdInitializerList)
{
    Vector<double> d{1.0, 2.0, 3.0, 4.0, 5.0};
    d.assign({6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0});
    ASSERT_EQ(d.getSize(), 12);
    ASSERT_EQ(d[0], 6.0);
    ASSERT_EQ(d[11], 17.0);
}

TEST_F(VectorTests, CreateVectorUsingCopyMoveConstructor)
{
    Vector<double> e{1.0, 2.0, 3.0, 4.0, 5.0};
    Vector<double> d = e;
    ASSERT_EQ(d.getSize(), 5);
    ASSERT_EQ(d[0], 1.0);
    ASSERT_EQ(d[4], 5.0);
}

TEST_F(VectorTests, CreateVectorUsingCopyMoveConstructor_1)
{
    Vector<double> e = std::move(getDoubles());
    ASSERT_EQ(e.getSize(), 5);
    ASSERT_EQ(e[0], 1.0);
    ASSERT_EQ(e[4], 5.0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    // Do whatever setup here you will need for your tests here
    //
    //

    returnValue = RUN_ALL_TESTS();

    // Do Your teardown here if required
    //
    //

    return returnValue;
}

} // end of namespace
