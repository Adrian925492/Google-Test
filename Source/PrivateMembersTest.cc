#include <gtest/gtest.h>
#include <gmock/gmock.h>

/* Testing private properties of the class (or file):
1) Include source file (#include "file.cpp"). This is the easiest way, but also not recomennded
2) Prepare special tsting API header, that will have signatures of methods (private or static functions) only for test
3) Friend fixture with tested class and add friend methods in fixture with tested methods in tested class
4) Add FRIEND_TEST(fixture, test) macro in tested class signeture */

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