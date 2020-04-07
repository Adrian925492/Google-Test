#include <gtest/gtest.h>
#include <gmock/gmock.h>

//Interface class to mock
class Interface5
{
public:
    virtual int method(int a)
    {
        std::cout << "Interface implementation called \n";
        return 1;
    }
};

class TestedClass5
{
public:
    TestedClass5(Interface5* obj): _obj(obj) {}  

    void foo()
    {
        std::cout << "Tested method called \n";
        _obj->method(1);
    }
private:
    Interface5* _obj;
};


/* Example 1: delegate to fake implementation */

// Custom fake
class Fake5 : public Interface5
{
public:
    virtual int method(int a) override
    {
        std::cout << "Fake implementation called \n";
        return 5;       
    }
};

class Mock5 : public Interface5
{
public:
    MOCK_METHOD(int, method, (int a), (override));      //We create standard mock - so we can use it if want

    //And delegation method
    void DelegateToFake()
    {
        ON_CALL(*this, method).WillByDefault([this](int n){return _fake.method(n);});   //Set the delegation to fake
    }

private:
    Fake5 _fake;
};

TEST(DelegationTest, DelegationToFakeTest)
{
    Mock5 oMockObj;

    oMockObj.DelegateToFake();          //If we call that method - we delegate to fake implementation. If not called - mock will be used.

    EXPECT_CALL(oMockObj, method);      //Set up call expectation

    TestedClass5 oClass(&oMockObj);     //Create tested class impl

    oClass.foo();
}

/* Example 2: delegate to base class */

class Mock5_1 : public Interface5
{
public:
    MOCK_METHOD(int, method, (int a), (override));      //We create standard mock - so we can use it if want

    //And delegation method
    void DelegateToBaseClass()
    {
        ON_CALL(*this, method).WillByDefault([this](int n){return Interface5::method(n);});   //Set the delegation to base class
    }
};

TEST(DelegationTest, DelegationToBaseClassTest)
{
    Mock5_1 oMockObj;

    oMockObj.DelegateToBaseClass();     //If we call that method - we delegate to base class implementation. If not called - mock will be used.

    EXPECT_CALL(oMockObj, method);      //Set up call expectation

    TestedClass5 oClass(&oMockObj);     //Create tested class impl

    oClass.foo();
}

/* Example 2: delegate to original implementation class */

class OriginalImplementation : public Interface5
{
public:
    virtual int method(int a) override
    {
        std::cout << "Original implementation called \n";
        return 2;
    }
};

class Mock5_2 : public Interface5
{
public:
    MOCK_METHOD(int, method, (int a), (override));      //We create standard mock - so we can use it if want

    //And delegation method
    void DelegateToOriginalImplementation()
    {
        ON_CALL(*this, method).WillByDefault([this](int n){return _real.method(n);});   //Set the delegation to original
    }

private:
    OriginalImplementation _real;
};

TEST(DelegationTest, DelegationToOriginalImplementationTest)
{
    Mock5_2 oMockObj;

    oMockObj.DelegateToOriginalImplementation();        //If we call that method - we delegate to real implementation. If not called - mock will be used.

    EXPECT_CALL(oMockObj, method);      //Set up call expectation

    TestedClass5 oClass(&oMockObj);     //Create tested class impl

    oClass.foo();
}