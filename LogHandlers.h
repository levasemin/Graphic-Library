#include <iostream>

class LogClickLeftButton
{
public:
    void print_widget(int num)
    {
        std::cout << "widget: " << num << std::endl;
    }
};

class LogClickRightButton
{
public:
    void print_widget(int num)
    {
        std::cout << num << " :widget" << std::endl;
    }
};