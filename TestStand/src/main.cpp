#include <iostream>
#include "GraphLib.hpp"

int main()
{
    SL::MainWindow window(SL::Vector2d(200, 200));
    SL::Application app(&window);
    
    
    app.exec();
}