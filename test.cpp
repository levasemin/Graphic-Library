#include <iostream>
#include <SFML/Graphics.hpp>

class A
{
public:
    int a = 10;

    virtual void printfda() = 0;
};

class B : public A
{
public:
    int b = 20;
    
    void printfda() override
    {
        std::cout << b;
    }
    
};


void func()
{
    std::cout << "Hello" << std::endl;
}

int main()
{
    
    B object;
    B object1(object);

    A *pointer = (A *)&object;

    pointer->printfda();
}