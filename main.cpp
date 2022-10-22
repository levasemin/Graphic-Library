#include "Widget.h"
#include "Window.h"
#include "Event.h"
#include "AbstractEventHandler.h"
#include "MethodEventHandler.h"
#include "constants.h"

#include <iostream>
#include <vector>


int main()
{  
    Widget first_window (WIDTH, HEIGHT);
    Widget second_window(WIDTH / 2, HEIGHT / 2);
    Widget third_window (WIDTH / 4, HEIGHT / 4);

    std::vector<Widget *> Widgets = {&first_window, &second_window, &third_window};

    char *s1 = "Hello";
    const char *s2 = "Hello12";

    Window<int> main_window(WIDTH, HEIGHT, 7);
    ClickWindowHandler handler_main_window;
    
    main_window.onButtonClick += CreateMethodEventHandler<ClickWindowHandler, int>(handler_main_window);
    main_window.onButtonClick += CreateMethodEventHandler<ClickWindowHandler, int>(handler_main_window);

    main_window.onButtonClick((long long)5);
}