#include <gtest/gtest.h>
#include <gmock/gmock.h>

/* The #niceStrictNaggy concerns to how the gmock will react for calling methods, that we do not care.

If we expect to call some method, and other method will (also) be called, the framewrk will report a warning by default.

However, we can use template class to supress the warning or treat it as a failure.

1) If we use ::testing::NiceMock<mockClass> oMock in place of mock class instantiation, such warning will be supressed. 
2) If we use ::testing::StrictMock<mockClass> oMock in place of mock class instantiation, any call of other method than expected
        will cause a failure.

Example:

*/

class Interface3
{
public:
    virtual void method1(){}
    virtual void method2(){}
};

class TestedClass3
{
public:
    TestedClass3(Interface3* obj) : pObject(obj) {}
    
    void foo()
    {
        pObject->method1();
        pObject->method2();     //As method 2 is not expected, by default gtest will warn us abiut call it
    }

private:
    Interface3* pObject;
};

class Mock3 : public Interface3
{
public:
    MOCK_METHOD(void, method1, (), (override));     //Make mock
    MOCK_METHOD(void, method2, (), (override));     
};

TEST(niceStrictNaggy, naggyTest)
{
    Mock3 oMock;     //We use direct mock object. Not expected method2() call will give a warning.

    EXPECT_CALL(oMock, method1);

    TestedClass3 oClass(&oMock);     //Tested class instantiation
    
    oClass.foo();
}

TEST(niceStrictNaggy, niceMockTest)
{
    ::testing::NiceMock<Mock3> oMock;     //We use nice mock object. Not expected method2() call will give no effect.

    EXPECT_CALL(oMock, method1);

    TestedClass3 oClass(&oMock);     //Tested class instantiation
    
    oClass.foo();
}

TEST(niceStrictNaggy, strictMockTest)
{
    ::testing::StrictMock<Mock3> oMock;     //We use strict mock object. Not expected method2() call will give a failure.

    EXPECT_CALL(oMock, method1);

    TestedClass3 oClass(&oMock);     //Tested class instantiation
    
    oClass.foo();
}