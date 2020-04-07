#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

class Interface7
{
public:
    virtual int method1(int a)
    {
        return a;
    }

    virtual int method2(int a)
    {
        return 2*a;
    }

    virtual void method3() {}
    virtual void method4() {}
    virtual void method5() {}
    virtual std::string method6(std::string a, std::string b) 
    {
        return a + b;
    }
    virtual void method7(float a, double b) {}
};

class TestedClass
{
public:
    TestedClass(Interface7* obj): _obj(obj) {}

    int foo1(int a)
    {
        return _obj->method1(a);

    }

    int foo2(int a)
    {
        return _obj->method2(a);
    }

    void foo3()
    {
        _obj->method3();
    }

    void foo4()
    {
        _obj->method4();
    }

    void foo5()
    {
        _obj->method5();
    }

    std::string foo6(std::string a, std::string b)
    {
        return  _obj->method6(a, b);
    }

    void foo7(float a, double b)
    {
        _obj->method7(a, b);
    }

private:
    Interface7* _obj;
};

class Mock7 : public Interface7
{
public:
    MOCK_METHOD(int, method1, (int a), (override));
    MOCK_METHOD(int, method2, (int a), (override));
    MOCK_METHOD(void, method3, (), (override));
    MOCK_METHOD(void, method4, (), (override));
    MOCK_METHOD(void, method5, (), (override));
    MOCK_METHOD(std::string, method6, (std::string a, std::string b), (override));
    MOCK_METHOD(void, method7, (float a, double b), (override));
};

/* Using simple matchers */
TEST(GmockMatchers, SimpleMatchers_ex1)
{
    Mock7 oMock;

    //Example 1: We expect 2 times calling method 1,each time with argument >= 2
    EXPECT_CALL(oMock, method1(::testing::Ge(2))).Times(2);

    TestedClass oClass(&oMock);

    oClass.foo1(2);
    oClass.foo1(3);
}

using ::testing::Return;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::_;

TEST(GmockMatchers, SimpleMatchers_ex2)
{
    Mock7 oMock;

    //Example 2: We expect 2 times calling method 1,each time with argument == 2. At first call is shall return 2, at second == 2.
    EXPECT_CALL(oMock, method1(Eq(2))).Times(2).WillOnce(Return(2)).WillOnce(Return(2));

    TestedClass oClass(&oMock);

    oClass.foo1(2);
    oClass.foo1(2);
}

/* Cardinalities matchers */
using ::testing::AtLeast;
using ::testing::AtMost;
using ::testing::AnyNumber;
using ::testing::Exactly;
using ::testing::Between;

TEST(GmockMatchers, SimpleMatchers_cardinalities)
{
    Mock7 oMock;

    EXPECT_CALL(oMock, method1(_)).Times(AtLeast(2));       //Expect to call at least 2 times
    EXPECT_CALL(oMock, method2(_)).Times(AtMost(2));        //Expect to call maximum 2 times
    EXPECT_CALL(oMock, method3()).Times(AnyNumber());       //Expect to call any nr of times
    EXPECT_CALL(oMock, method4()).Times(Exactly(1));        //Expect to call exactly 1 time
    EXPECT_CALL(oMock, method5()).Times(Between(1, 2));     //Expect to call between 1 and 2 times

    TestedClass oClass(&oMock);

    oClass.foo1(1);
    oClass.foo1(1);      //Expect 1
    oClass.foo2(1);      //Expect 2
    oClass.foo3();       //Expect 3
    oClass.foo4();       //Expect 4
    oClass.foo5();  
    oClass.foo5();       //Expect 5
}

/* String mathers */
using ::testing::ContainsRegex;
using ::testing::EndsWith;
using ::testing::HasSubstr;
using ::testing::MatchesRegex;
using ::testing::StartsWith;
using ::testing::StrCaseEq;
using ::testing::StrCaseNe;

using ::testing::AllOf;     //Combining matchers

TEST(GmockMatchers, SimpleMatchers_stringMatchers)
{
    Mock7 oMock;

    EXPECT_CALL(oMock, method6(AllOf(StartsWith("A"), EndsWith("C"), HasSubstr("B")), StrCaseEq("ELO")));

    TestedClass oClass(&oMock);

    oClass.foo6("ABC", "ELO");        
}

/* Floating point matchers */
using ::testing::DoubleEq;
using ::testing::FloatEq;
using ::testing::NanSensitiveDoubleEq;
using ::testing::NanSensitiveFloatEq;
using ::testing::IsNan;

TEST(GmockMatchers, SimpleMatchers_floatMatchers)
{
    Mock7 oMock;

    EXPECT_CALL(oMock, method7(NanSensitiveFloatEq(3.14), DoubleEq(5.2300)));

    TestedClass oClass(&oMock);

    oClass.foo7(3.14, 5.2300);        
}