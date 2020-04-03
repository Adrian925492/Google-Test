#include <gtest/gtest.h>
#include <gmock/gmock.h>

/* Streaming to assertion */
// Gtest allows to stream to assertions. The stream text will be showed on output only on failure the assertion.
TEST(GtestFeatures, StreamToAssertionsTest)
{
    int a = 2, b = 2;
    EXPECT_EQ(a, b) << "A is not equal B";
}

/* Scoped trace */
// Alows to add trace message for every failure asserion in test scope where macro or object of scopedTrace is used
TEST(GtestFeatures, ScopedTraceMessageTest)
{
    int a = 2, b = 2;

    SCOPED_TRACE("MyMessage");      //Adds message to every assertion failed in that test scope

    ::testing::ScopedTrace scopedTrace("myMessage2", 2, "file.cc"); //Adds scoped trace message with explicitly given file and line nr

    EXPECT_EQ(a, b);
}

/* Fatal failure inside sub - outines */
void foo(bool property)
{
    ASSERT_TRUE(property); //Cause fatal failure. It will break ONLY the subroutine, not the test that calls that subroutine
}

TEST(GtestFeatures, FatalFailureTest)
{
    foo(true);

    //However, we can propagate the fatal failure using special assertion
    ASSERT_NO_FATAL_FAILURE(foo(true));     //Than the fatal failure occurence will propagate t test scope

    EXPECT_TRUE(true);     //And we will not reach that point

    //Or we can check if fatal failure has been occured during test
    if (HasFatalFailure())
    {
        SCOPED_TRACE("Fatal faiure!");
    }
}