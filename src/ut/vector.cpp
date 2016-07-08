#include <iostream>
#include "gtest/gtest.h"
#include "../vector.h"

namespace epam {

class VectorTests : public ::testing::Test {
   public:
    VectorTests(){

    };

    void SetUp() override{};

    void TearDown() override{

    };

    ~VectorTests(){

    };

    Vector<int> vector;
};

TEST_F(VectorTests, IsInitialCapacitySetTo10) {
    ASSERT_EQ(vector.getCapacity(), 10);
}

TEST_F(VectorTests, IsInitialSizeSetTo0) { ASSERT_EQ(vector.getSize(), 0); }

TEST_F(VectorTests, CheckIfOnePushedElementIsTheOnlyOne) {
    vector.push_back(42);
    ASSERT_EQ(vector.getSize(), 1);
    ASSERT_EQ(vector[0], 42);
}

TEST_F(VectorTests, CheckIfOrderOfElementsReflectsOrderOfPushing) {
    vector.push_back(3);
    vector.push_back(2);
    vector.push_back(1);
    ASSERT_EQ(vector[0], 3);
    ASSERT_EQ(vector[1], 2);
    ASSERT_EQ(vector[2], 1);
}

TEST_F(VectorTests, CheckIfVectorHas3ElementsAfterPushing3) {
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    ASSERT_EQ(vector.getSize(), 3);
}

TEST_F(VectorTests, CheckIfCapacityIsShrinkAfterDownsizing) {
    ASSERT_EQ(vector.getCapacity(), 10);
    vector.resize(7);
    ASSERT_EQ(vector.getCapacity(), 7);
}

TEST_F(VectorTests, CheckIfElementsAreDeletedAfterResizingDown) {
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    vector.resize(3);
    ASSERT_EQ(vector.getSize(), 3);
}

int main(int argc, char** argv) {
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

}  // end of namespace
