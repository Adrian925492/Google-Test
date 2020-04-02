#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Fixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::cout << "SetUpFixture \n";       //Called before going to test case
    }
    void TearDown() override
    {
        std::cout << "TearDownFixture \n";    //Called fter leaving test case
    }

    //The gtest creates fixture class member for each test that ises it. However, if we want to have some shared
    //resources between test cases, we can use static setup, teardown methods and static members.

    static void SetUpTestSuite()        //Static set up - common for all tests that uses the fixture. Called before 1st test form suite.
    {
        std::cout << "Static set up test suite \n";
        std::cout << "Static property value: " << stat_n << std::endl;
    }

    static void TearDownTestSuite()     //Static tear down - common for all tests in suite. Called after last test that uses the fixture.
    {
        std::cout << "Static tear down test suite \n";
        std::cout << "Static property value: " << stat_n << std::endl;
    }

    static int stat_n;  //Static property. The value is same for each test.
};

int Fixture::stat_n = 2;

TEST_F(Fixture, FixtureTestCase1)   //Fixture usage examples. Break the test and take a look at console output.
{
    EXPECT_TRUE(true); //Fake test
}

TEST_F(Fixture, FixtureTestCase2)
{
    EXPECT_TRUE(true); //Fake test
}