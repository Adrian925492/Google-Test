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