#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdexcept>
#include <float.h>

TEST(SuitableAssertions, ExplicitAssertionsTest)
{
    int value = 1;

    switch(value)
    {
        case 0:
            FAIL(); //Generates fatal assertion
            break;
        case 1:
            SUCCEED();  //Generates succeed 
            break;
        case 2:
            ADD_FAILURE();  //Generates non-fatal assertion
            break;
        case 3:
            ADD_FAILURE_AT("SuitbleAssertions.cc", 18); //Generates non - fatal assertion with explicitly given file and line
            break;
    }
}


/* Exception assertions test */
struct foo
{
    int bar(int i) {
        if (i > 100) {
            throw std::out_of_range("Out of range");
        }
        return i;
    }
};

TEST(SuitableAssertions, ExceptionAssertionTest)
{
    foo f;

    EXPECT_NO_THROW(f.bar(1));      //No assertion expected
    EXPECT_ANY_THROW(f.bar(101));   //Any kind assertion expected
    EXPECT_THROW(f.bar(101), std::out_of_range);    //Expected exception throw with specified type
}

/* Predictate assertions */
bool predFunc1(int i)
{
    if (i == 1)
        return false;
    return true;
}
bool predFunc2(int i, int j)
{
    if (j == 1)
        return false;
    return true;
}

TEST(SuitableAssertions, PredictateAssertionTest)
{
    EXPECT_PRED1(predFunc1, 12);
    EXPECT_PRED2(predFunc2, 12, 12);    //Predictate assertions test
}

/* User defined assertion results */
::testing::AssertionResult isEven(int i)
{
    if ((i%2) == 0)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << i << " is Odd" ;    
}

TEST(SuitableAssertions, ReturneAssertionTest)
{
    EXPECT_TRUE(isEven(2));
}

/* Predictate formatter */
bool isEven2(int i)
{
     return ((i%2) == 0); 
}

::testing::AssertionResult AssertIsEven(const char* m_expr, int m)
{
    if (isEven2(m))
    {
        return ::testing::AssertionSuccess();
    }
    return ::testing::AssertionFailure() << m_expr << " is not Even! ";
}

TEST(SuitableAssertions, PrimeFormatterAssertionTest)
{
    EXPECT_PRED_FORMAT1(AssertIsEven, 2);   //Will result printing out own assertion fail text! 
}

/* Floating point assertions */
TEST(SuitableAssertions, FloatAssertionTest)
{
    float a = 3.14;
    float b = 3.140000001;

    EXPECT_FLOAT_EQ(a, b);  //A nd B are ALMOST equal (expect_eq would return failure)

    double c = 3.14;
    double d = 3.140000000000001;

    EXPECT_DOUBLE_EQ(c, d);
}

/* Assertion using gmock matcher */
using ::testing::StartsWith;

TEST(SuitableAssertions, GmockMatcherAssertionTest)
{
    std::string word = "HelloWorld";

    EXPECT_THAT(word, StartsWith("Hello"));     //Use "startwith" matcher, case sensitive!
}
/* Type assertion */
TEST(SuitableAssertions, StaticAssertionTest)
{
    ::testing::StaticAssertTypeEq<int, int>();  //Call compile error if types are not fit together
}