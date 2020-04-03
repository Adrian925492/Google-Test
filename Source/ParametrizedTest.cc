#include <gtest/gtest.h>
#include <gmock/gmock.h>

/* Value parametried tests */

// Step1: define fixture
class ValParamFixture : public ::testing::TestWithParam<int>
{

};

//Step2: define tests
TEST_P(ValParamFixture, test1)
{
    EXPECT_TRUE(true) << "Value parametried test 1, parameter: " << GetParam() << std::endl;
}

TEST_P(ValParamFixture, test2)
{
    EXPECT_TRUE(true) << "Value parametried test 2, parameter: " << GetParam() << std::endl;
}

//Step3: Register suite
INSTANTIATE_TEST_SUITE_P(valSuite, ValParamFixture, ::testing::Values(1,2,3));

//To instantiate we use generators from ::testing namespace. Available generators:
// Values(n1, ... nn) - Produce tests for each value from given range
// Range (begin, end, step) - produce test for each value from given range
// ValuesIn(array); ValuesIn(begin, end) - produce tests for values from C-style array, or stl container given by begin and end iterators
// Bool() - produces test for boolean true and false values
// Combine (g1, ... g2) - produces test for each combination of g1 to gn arguments


/* Type parametrized tests */

//step1: define fixture with template
template <typename T>
class TypeParamFixture : public ::testing::Test
{
};

//Step2: register test types (has to be before test instantiation)
using MyTypes = ::testing::Types<uint8_t, uint16_t>;
TYPED_TEST_SUITE(TypeParamFixture, MyTypes);

//step3: define test cases
TYPED_TEST(TypeParamFixture, test1)
{
    EXPECT_TRUE(true);
}

TYPED_TEST(TypeParamFixture, test2)
{
    EXPECT_TRUE(true);
}

