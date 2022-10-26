#include <iostream>
#include <SFML/Graphics.hpp>

class Widget
{
public:

    virtual void function(int x) = 0;
};

class MainWindow : public Widget
{
public:
    void function(int x) override
    {
        std::cout << "MainWindow" << std::endl;
    }
}; 

class Button : public MainWindow
{
    public:
    void (*function_)(int x); 

    void function(int x)
    {
        function_(x);
    }
};

int main()
{
    Button butt{};
    butt.(*func)(5);
    butt.function(5);
}