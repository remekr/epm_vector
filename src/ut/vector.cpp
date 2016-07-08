#include <iostream>
#include "gtest/gtest.h"
#include "../vector.h"

namespace epam
{

class VectorTests : public ::testing::Test {
public:
   VectorTests()
   {

   };

   void SetUp() override
   {
   };

   void TearDown() override
   {

   };

   ~VectorTests()
   {

   };

  Vector<int> vector;
};


int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    //Do whatever setup here you will need for your tests here
    //
    //

    returnValue =  RUN_ALL_TESTS();

    //Do Your teardown here if required
    //
    //

    return returnValue;
}

} // end of namespace
