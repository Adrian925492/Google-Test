#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Interface4
{
public:
    virtual void longMethod(int a, int b, int c){}      //We have long method, but in mock we care ony about a argument/ We want to shortern argument list of mock.
};

class TestedClass4      //Tested class
{
public:
    TestedClass4(Interface4* obj) : _obj(obj) {}

    void foo()
    {
        _obj->longMethod(1,2,3);
    }
private:
    Interface4* _obj;
};

class Mock4 : public Interface4
{
public:
    virtual void longMethod(int a, int b, int c)  override  //We override long method by own impementation
    {
        shortMethod(a);     //In which we call mocked short method
    }
    MOCK_METHOD(void, shortMethod, (int a), ());    //And provide imple,entation (mock) of short method
};

TEST(ShorternArgumentListTest, Test1)
{
    Mock4 oMock;

    EXPECT_CALL(oMock, shortMethod);    //We check if short method has been called (we do not care ab. arguments, so..)

    TestedClass4 oClass(&oMock);

    oClass.foo();
}