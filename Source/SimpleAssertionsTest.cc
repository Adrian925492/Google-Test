#include <gtest/gtest.h>
#include <string>

TEST(SimpleAssertions, BasicAssertions)
{
    EXPECT_FALSE(false);    //Succeeds when agument returns false
    EXPECT_TRUE(true);      //Succeeds when argument returns true
}

TEST(SimpleAssertions, ComparisonAssertions)
{
    EXPECT_EQ(1, 1);        //Succeeds when arguments are equal
    EXPECT_NE(1, 2);        //Succeeds when arguments are different
    EXPECT_GT(3, 2);        //Succeeds when argument 1 > argument 2
    EXPECT_GE(3, 3);        //Succeeds when argument 1 >= argument 2
    EXPECT_LT(2, 3);        //Succeeds when argument 1 < argument 2
    EXPECT_LE(2, 2);        //Succeeds when argument 1 <= argument 2
}

TEST(SimpleAssertions, CharChainAssertions)
{
    /* For cpp style strings we can use comparison assertions */
    std::string checkString = "checkString";
    std::string expectedString = "checkString";
    
    EXPECT_EQ(checkString, expectedString);

    /* For c style string we have set of assertions */
    char str1[] = "String1";
    char str2[] = "String2";

    EXPECT_STREQ(str1, "String1");       //Succeds when strings are equal (case - sensitive)
    EXPECT_STRNE(str1, "string1");       //Succeds when strings are different (case - sensitive)
    EXPECT_STRCASEEQ(str1, "STRING1");   //Succeeds when strings are identical (case non sensitive)
    EXPECT_STRCASENE(str1, str2);        //Succeeds when strings are not equal (case non - sensitive)
}