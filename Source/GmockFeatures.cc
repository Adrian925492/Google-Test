#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Interface6
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

    virtual void method3(int a) {}
    virtual void method3(uint16_t a) {}
    virtual void method3(char a) {}

    virtual bool method4(int* a) {return true;}

    virtual void method5(int a){}

    virtual bool method6(int* a, int b) {return true;}
};

class TestedClass
{
public:
    TestedClass(Interface6* obj): _obj(obj) {}

    int foo1(int a)
    {
        return _obj->method1(a);

    }

    int foo2(int a)
    {
        return _obj->method2(a);
    }

    void foo3(int a)
    {
        _obj->method3(a);
    }

    void foo3(uint16_t a)
    {
        _obj->method3(a);
    }

    void foo3(char a)
    {
        _obj->method3(a);
    }

    bool foo4(int* a)
    {
        return _obj->method4(a);
    }

    void foo5(int a)
    {
        _obj->method5(a);
    }

    bool foo6(int*a, int b)
    {
        return _obj->method6(a, b);
    }

private:
    Interface6* _obj;
};

class Mock6 : public Interface6
{
public:
    MOCK_METHOD(int, method1, (int a), (override));
    MOCK_METHOD(int, method2, (int a), (override));
    MOCK_METHOD(void, method3, (int a), (override));
    MOCK_METHOD(void, method3, (uint16_t a), (override));
    MOCK_METHOD(void, method3, (char a), (override));
    MOCK_METHOD(bool, method4, (int* a), (override));   //Pointee argument
    MOCK_METHOD(void, method5, (int a), (override));
    MOCK_METHOD(bool, method6, (int*a, int b), (override));
};

using ::testing::Return;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::AtMost;

/* Gmock matchers - matchers order */
TEST(GmockFeatures, SimpleMatchersOrder_default)
{
    Mock6 oMock;

    //Example 3: We expect 2 times calling method 1,each time with any argument
    EXPECT_CALL(oMock, method1(_)).Times(2);

    //And we expect method 2 to be called once, with argument 4, and return 8.
    EXPECT_CALL(oMock, method2(Eq(4))).WillOnce(Return(8));

    TestedClass oClass(&oMock);

    //By default, order of calls can be any.
    oClass.foo1(2);
    oClass.foo2(4);
    oClass.foo1(2);
}

TEST(GmockFeatures, SimpleMatchersOrder_withAfterMatcher)
{
    Mock6 oMock;

    //Example 3: We expect 2 times calling method 1,each time with any argument
    ::testing::ExpectationSet exp1 = EXPECT_CALL(oMock, method1(_)).Times(2);

    //And we expect method 2 to be called once, with argument 4, and return 8.
    EXPECT_CALL(oMock, method2(Eq(4))).After(exp1).WillOnce(Return(8));

    TestedClass oClass(&oMock);

    //In that case, foo2() has to be called after fulfill 1st expectation regarding foo1().
    oClass.foo1(2);
    oClass.foo1(2);
    oClass.foo2(4);
}

TEST(GmockFeatures, SimpleMatchersOrder_withSequence)
{
    Mock6 oMock;

    ::testing::InSequence seq;      //Sequence instantiation. After clause is not needed.

    //Example 3: We expect 2 times calling method 1,each time with any argument
    EXPECT_CALL(oMock, method1(_)).Times(2);

    //And we expect method 2 to be called once, with argument 4, and return 8.
    EXPECT_CALL(oMock, method2(Eq(4))).WillOnce(Return(8));

    TestedClass oClass(&oMock);

    //In that case, foo2() has to be called after in sequency, like it is ritten in test case.
    oClass.foo1(2);
    oClass.foo1(2);
    oClass.foo2(4);
}

/* Partial sequence */
TEST(GmockFeatures, SimpleMatchersOrder_withPartialSequence)
{
    Mock6 oMock;

    //Here we are interested to method1 be called before method2 and 3; but order of calling methods 2 and 3 does not matter.

    ::testing::Sequence s1, s2;     //We define 2 sequences, one for method 1->2 order, and other formethod 1->3 order

    EXPECT_CALL(oMock, method1).InSequence(s1, s2);
    EXPECT_CALL(oMock, method2).InSequence(s1);
    EXPECT_CALL(oMock, method3(::testing::TypedEq<char>('c'))).InSequence(s2);

    TestedClass oClass(&oMock);

    oClass.foo1(3);
    oClass.foo2(1);
    oClass.foo3('c');
}

/* Steering when expectation expires */
TEST(GmockFeatures, SimpleMatchersOrder_expectationRetires)
{
    Mock6 oMock;

    //Here we expect, that only first call of method1 with argument 1 will return 1. Every other call 
    //shall match to 2nd expect, and return 2. Normally, saturated expects does not expire after matching, so ot will
    //not work. We have to use .RetiresOnSaturation() to expire by hand expectation after 1st match.

    EXPECT_CALL(oMock, method1(_)).WillRepeatedly(Return(2));
    EXPECT_CALL(oMock, method1(1)).RetiresOnSaturation();

    TestedClass oClass(&oMock);

    EXPECT_EQ(oClass.foo1(1), 0);   //Here expect 2 is saturated
    EXPECT_EQ(oClass.foo1(2), 2);
    EXPECT_EQ(oClass.foo1(1), 2);
}

/* Returning live values from mocks */
using ::testing::ReturnPointee;

TEST(GmockFeatures, SimpleMatchersOrder_returnLiveValues)
{
    int x = 0;
    Mock6 oMock;

    EXPECT_CALL(oMock, method1(_)).WillRepeatedly(ReturnPointee(&x));

    TestedClass oClass(&oMock);

    EXPECT_EQ(oClass.foo1(1), 0);
    x = 2;      //Here we can change live value returned by mock method 1!
    EXPECT_EQ(oClass.foo1(1), 2);    
}

/* Defining own matcher */
MATCHER(IsEven, ""){return (arg % 2) == 0;}     //Non argument matcher
MATCHER_P(IsEqual, a, ""){return (arg == a);}     //One argument matcher
MATCHER_P2(IsSumEqual, a, b, ""){return (a + arg) == b;}   //Two argument matcher

TEST(GmockFeatures, OwnMatchersTest)
{
    Mock6 oMock;

    //Example 3: We expect at least 2 times calling method 1,each time with own matcher matching argument
    EXPECT_CALL(oMock, method1(IsEqual(2))).Times(AtLeast(2));

    //And we expect method 2 to be called once, with own matcher matching, and return 8.
    EXPECT_CALL(oMock, method2(IsSumEqual(1, 5))).WillOnce(Return(8));

    TestedClass oClass(&oMock);

    oClass.foo1(2);
    oClass.foo1(2);
    oClass.foo2(4);
}

/* Selecting between overloaded methods */
TEST(GmockFeatures, SelectingBetweenOverloadedMethods)
{
    Mock6 oMock;

    //If we have multiple overloaded methods with difference in argument type we can distinguish it like this:

    //By An<type>()
    EXPECT_CALL(oMock, method3(::testing::An<int>()));

    //By matcher casting to explicit type
    EXPECT_CALL(oMock, method3(::testing::Matcher<uint16_t>(1)));

    //By typeEq matcher
    EXPECT_CALL(oMock, method3(::testing::TypedEq<char>('c')));    

    TestedClass oClass(&oMock);

    oClass.foo3(static_cast<int>(1));
    oClass.foo3(static_cast<uint16_t>(1));
    oClass.foo3('c');
}

/* Different expect basing on argument value */

TEST(GmockFeatures, DifferentExpectationBasingOnArgumentValue)
{
    Mock6 oMock;

    //If we have multiple overloaded methods with difference in argument type we can distinguish it like this:

    EXPECT_CALL(oMock, method2(_)); //Expected call method 2 with ay arg
    EXPECT_CALL(oMock, method2(2)).WillOnce(Return(4)); //But if it will be called with argument 2, it shall return 4

    TestedClass oClass(&oMock);

    oClass.foo2(1);     //Matches expect 1
    oClass.foo2(2);     //Matches expect 2
}

/* Validating only class atribute and property, not whole class */
class ClassForCheck
{
public:
    int field;
    int foo() const {return 1;}
};

using ::testing::Field;
using ::testing::Property;

TEST(GmockFeatures, ClassPropertyMatch)
{
    ClassForCheck oClass;
    oClass.field = 2;

    EXPECT_THAT(oClass, Field(&ClassForCheck::field, 2));    //We match only atribute not whole class. The matcher will copy only the property.
    EXPECT_THAT(oClass, Property(&ClassForCheck::foo, 1));                        //We match only property of the class. The property must be declared as const
}

/* Sharing matchers */
using ::testing::AllOf;
using ::testing::Le;

::testing::Matcher<int> in_range = AllOf(Ge(2), Le(4));     //We define matcher in range, which specifies tht argument has to be in range 2 to 4

TEST(GmockFeatures, MultiusageMatcher)
{
    int a = 3, b = 4;

    EXPECT_THAT(a, in_range);
    EXPECT_THAT(b, in_range);       //Thus, as we have defined matcher, we can use it multiple times
}

/* Expectation set */

/*
ON_CALL - defines behaviour of method, without checking envinroment in which it was called.
EXPECT_CALL - defines behaviour of the method, and allows to check envinroment in which it was called

By default we shall use ON_CALL, as EXPECT_CALL can cause a failure if the expectation defined by mtchers is not fullfilled

*/
TEST(GmockFeatures, OnCallBehaviour)
{
    Mock6 oMock;

    ON_CALL(oMock, method1).WillByDefault(Return(1));   //We set method 1 to return always 1. We do not care about passed argument.

    TestedClass oClass(&oMock);

    EXPECT_EQ(oClass.foo1(2), 1);    //And we expect foo1 to return 1, even if we pass 2 to foo1()
}

TEST(GmockFeatures, ExpectCallBehaviour)
{
    Mock6 oMock;

    EXPECT_CALL(oMock, method1(1)).WillOnce(Return(1));   //We set method 1 to return always 1. We will get a failure if passed arg will not be 1

    TestedClass oClass(&oMock);

    EXPECT_EQ(oClass.foo1(1), 1);    //And we expect foo1 to return 1, even if we pass 2 to foo1()
}

/* Setting pointer argument */
using ::testing::SetArgPointee;
using ::testing::DoAll;

TEST(GmockFeatures, WorkingOnPointerArguments)
{
    Mock6 oMock;
    int a = 1; //As firts, we have specified value 1

    /* Here we have case ahen return value is passed as pointer argument. The SetArgPointee action allows
    method to set specified value on a variable pointed by passed pointer. Than, we can chack, if
    mock actually set the variable. We expect to set value equal 5. */

    EXPECT_CALL(oMock, method4(_)).WillOnce(DoAll(SetArgPointee<0>(5), Return(true)));

    TestedClass oClass(&oMock);

    EXPECT_TRUE(oClass.foo4(&a));   
    EXPECT_EQ(a, 5);
}  

/* Setting default value for return type */
using ::testing::DefaultValue;

TEST(GmockFeatures, SettingTypeDefaultReturnValue)
{
    bool default_val = true;
    DefaultValue<bool>::Set(default_val);   //Here we set default return value for any mock that returns bool type
    
    Mock6 oMock;

    EXPECT_CALL(oMock, method4(_));     //Expect method4 - that returns bool type

    TestedClass oClass(&oMock);

    EXPECT_EQ(oClass.foo4(nullptr), true);      //And without setting the specific retval, we shall have defaut ret val, which now is true

    DefaultValue<bool>::Clear();        //And we clear default value setting
}  

/* Using function/ functor/ callback as mock action */
bool userAction(int* a)
{
    return (*a == 2);   //Return true if a == 2
}

using ::testing::Invoke;

TEST(GmockFeatures, UsinFunctionAsAction)
{
  
    Mock6 oMock;

    EXPECT_CALL(oMock, method4(_)).WillRepeatedly(Invoke(userAction));     //Expect method4 - that returns bool type

    TestedClass oClass(&oMock);

    int a = 2, b = 3;

    EXPECT_EQ(oClass.foo4(&a), true);      //As we have invoked function, we shall return true only if arg = 2 is passed
    EXPECT_EQ(oClass.foo4(&b), false);
}

using ::testing::InvokeWithoutArgs;

bool userAction2()
{
    return true;    //Return true without checking the argument
}

TEST(GmockFeatures, InvokeWithoutArguments)
{
  
    Mock6 oMock;

    EXPECT_CALL(oMock, method4(_)).WillRepeatedly(InvokeWithoutArgs(userAction2));     //Expect method4 - that returns bool type

    TestedClass oClass(&oMock);

    int a = 2, b = 3;

    EXPECT_EQ(oClass.foo4(&a), true);      //As we have invoked function, we shall return true always
    EXPECT_EQ(oClass.foo4(&b), true);
}

/* Ignoring actions result */
using ::testing::IgnoreResult;

// bool userAction3(int a)
// {
//     return true;
// }

// TEST(GmockFeatures, InvokeWithIgnoreResults)
// {
  
//     Mock6 oMock;

//     EXPECT_CALL(oMock, method5(_)).WillOnce(IgnoreResult(userAction));     //Expect method4 - that returns bool type

//     TestedClass oClass(&oMock);

//     oClass.foo5(1);
// }

/* Invoke function as action with not fit argument list */
bool userAction4(int* a)
{
    return (*a == 4);   //Return true if a == 2
}

using ::testing::WithArgs;

TEST(GmockFeatures, InvokeWithArgs)
{
    Mock6 oMock;

    EXPECT_CALL(oMock, method6).WillRepeatedly(WithArgs<0>(Invoke(userAction4)));     //Here we want to bind useraction4 which takes 1 arg to mock, which takes 2 args.
    //WithArgs<0> have created adapter that would call out invoked function passing only 0th arg from original interface to it.

    TestedClass oClass(&oMock);

    int a = 4, b = 3;

    EXPECT_EQ(oClass.foo6(&a, 1), true);      //As we have invoked function, we shall return true only if arg = 4 is passed
    EXPECT_EQ(oClass.foo6(&b, 2), false);
}

//Other way to do it is to declate some of arguments as unused, as follows

using ::testing::Unused;

bool userAction5(int* a, Unused)    //Hwre we have fitted signature, but 1 arg we say "do not matter"
{
    return (*a == 4);   //Return true if a == 2
}

TEST(GmockFeatures, InvokeWithUnused)
{
    Mock6 oMock;

    EXPECT_CALL(oMock, method6).WillRepeatedly(Invoke(userAction5));     //Here we want to bind useraction4 which takes 1 arg and 1 is unused to mock, which takes 2 args. 
    
    TestedClass oClass(&oMock);

    int a = 4, b = 3;

    EXPECT_EQ(oClass.foo6(&a, 1), true);      //As we have invoked function, we shall return true only if arg = 4 is passed
    EXPECT_EQ(oClass.foo6(&b, 2), false);
}

/* Sharing actions */
using ::testing::Action;

Action<bool(int*)> action = DoAll(SetArgPointee<0>(5), Return(true));   
//We save action, which will save 5 unter arg pointer, and returns true

TEST(GmockFeatures, SharingActionTest)
{
    Mock6 oMock;
    int a = 0;

    EXPECT_CALL(oMock, method4).WillRepeatedly(action);

    TestedClass oClass(&oMock);

    EXPECT_TRUE(oClass.foo4(&a));
    EXPECT_EQ(a, 5);    
}