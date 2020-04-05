#include <gtest/gtest.h>
#include <gmock/gmock.h>

/* Testing private properties of the class (or file):
1) Include source file (#include "file.cpp"). This is the easiest way, but also not recomennded (simple, no example)
2) Prepare special tsting API header, that will have signatures of methods (private or static functions) only for test (simple, no example)
3) Friend fixture with tested class and add friend methods in fixture with tested methods in tested class (example below)
4) Add FRIEND_TEST(fixture, test) macro in tested class signeture (example below) */

//The disadvantage of solution 3 and 4 is that informaton about let the test class go into private members has to be in source class declaration.
// That means, that source class depends a little from test framework. It is strongly reomendded to test only public API members. However, 
// if it is really needed to test private one, the best solution is to prepare special test API for that (solution 2).

/* Example: friend class - fixture */
class PrivateMemberTest_1;

class TestedClass
{
    friend class PrivateMemberTest_1;
private:
    void foo() {}
};

class PrivateMemberTest_1 : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}

public:
    TestedClass oTestedClass;
    void callFoo()
    {
        oTestedClass.foo();
    }
};

TEST_F(PrivateMemberTest_1, FriendClassTest)
{
    callFoo();

    EXPECT_TRUE(true);
}

/* Example 2 - by FRIEND_TEST macro */
class TestedClass2
{
private:
    FRIEND_TEST(PrivateMemberTest_2, FriendMacroTest);
    void foo() {}
};

class PrivateMemberTest_2 : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PrivateMemberTest_2, FriendMacroTest)
{
    TestedClass2 oClass;
    oClass.foo();

    EXPECT_TRUE(true);
}