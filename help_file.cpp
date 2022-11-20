#include <iostream>
using namespace std;

class A
{
public:
    int type;
};

class B : public A
{
public:
    int type;
};

int main()
{
    B object;
    object.type = 5;

    std::cout << (((A *)&object)->type == object.type); 
}