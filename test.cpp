#include <iostream>

template <class ...TParams>
class b1
{
    b1();
};

template <class ...TParams>
class b2
{
    b2;
};

class A
{
public:
    int a = 10;

    virtual void printfda() = 0;
};

template<class ...TParams>
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

    A *pointer = (A *)&object;

    pointer->printfda();
}