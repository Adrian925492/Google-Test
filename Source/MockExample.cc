#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>

/* Way 1: mocking virtual methods with given interface */
class Interface
{
public:
    virtual void method1(){};               //Ordinary method
    virtual void method2(int a) noexcept {};     //Noexcept method
    virtual void method3(int a, int b) const {};        //Const qualified method
    virtual void method4()=0;               //Pure virtual method
};

class InterfaceImplementation : public Interface
{
public:
    virtual void method1()
    {
        std::cout << "InterfaceImplementation: method1() \n";
    };     //Ordinary method
    virtual void method2(int a) noexcept 
    {
        std::cout << "InterfaceImplementation: method2(); arguments: " << a << "\n";
    };     //Noexcept method
    virtual void method3(int a, int b) const 
    {
        std::cout << "InterfaceImplementation: method3(); arguments: " << a << ", " << b << "\n";
    };     //Const qualified method
    virtual void method4()
    {
         std::cout << "InterfaceImplementation: method4() \n";       
    }
};

class TestedClass       //Class that will be tested
{
public:
    TestedClass(Interface* pClass) : _pClass(pClass) {}     //Apply dependency injection pattern

    void foo1()
    {
        _pClass->method1();
        _pClass->method2(1);
        _pClass->method3(1,2);
        _pClass->method4();
    }

private:
    Interface* _pClass;
};

class MockClass : public Interface
{
public:
    MOCK_METHOD(void, method1, (), (override));                     //Here we create mock concrete class with mock implementations
    MOCK_METHOD(void, method2, (int a), (noexcept, override));
    MOCK_METHOD(void, method3, (int a, int b), (const, override));
    MOCK_METHOD(void, method4, (), (override));
};

TEST(MockExampleTest, InheritanceMock)
{
    TestedClass oClass(new MockClass);    //We pass pointer to mock class
}

/* Way2: we have non virtual methods to mock */

class SomeConcreteClass
{
public:
    void method1()
    {
        std::cout << "SomeCOncreteClassImplementation: method1() \n";
    };     //Ordinary method
    void method2(int a) noexcept 
    {
        std::cout << "SomeCOncreteClassImplementation: method2(); arguments: " << a << "\n";
    };     //Noexcept method
    void method3(int a, int b) const 
    {
        std::cout << "SomeCOncreteClassImplementation: method3(); arguments: " << a << ", " << b << "\n";
    };     //Const qualified method
    void method4()
    {
         std::cout << "SomeCOncreteClassImplementation: method4() \n";       
    }
};

template <typename T>       //Here we realize dependency injection in compile time, by template
class TestedClass2
{
public:
    TestedClass2(){}

    void foo1()
    {
        _oClass.method1();
        _oClass.method2(1);
        _oClass.method3(1,2);
        _oClass.method4();
    }
private:
    T _oClass;
};

class MockClass2        //We have mock klas which, just, hase same methods signature as mocked class
{
public:
    MOCK_METHOD(void, method1, (), ());       //Do not type override - beacouse no override               
    MOCK_METHOD(void, method2, (int a), (noexcept));
    MOCK_METHOD(void, method3, (int a, int b), (const));
    MOCK_METHOD(void, method4, (), ());
};

TEST(MockExampleTest, TemplateMock)
{
    TestedClass2<MockClass2> oClass;    //We pass mock instead of impementation
}

/* Mocking free functions */
void foo()
{
    std::cout << "Foo function original \n";
}

class FreeFunctionInterface     //1st we have to do interface
{
public:
    virtual void callFoo(){}
};

//And then as with normal inheritance mocking

class FreeFunctionInterface_Implementation : public FreeFunctionInterface
{
public:
    void callFoo() override
    {
        foo();      //Wrapper method
    }
};

class FreeFunction_TestedClass
{
public:
    FreeFunction_TestedClass(FreeFunctionInterface* interface): _oFreeFunction(interface){}

    void method()
    {
        _oFreeFunction->callFoo();
    }
private:
    FreeFunctionInterface* _oFreeFunction;
};

class FreeFunction_Mock : public FreeFunctionInterface
{
public:
    MOCK_METHOD(void, callFoo, (), (override));     //Mock wrapper method
};

TEST(MockExampleTest, FreeFunctionMock)
{
    FreeFunction_TestedClass oTestedClass(new FreeFunction_Mock);   //Use dependency injection to pass mock object
}