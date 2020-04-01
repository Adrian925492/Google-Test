#include <gtest/gtest.h>
#include <stdexcept>

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
