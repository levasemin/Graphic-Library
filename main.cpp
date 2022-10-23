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

    const char *s1 = "Hello";
    char *s2 = "Hello12";

    Window<char *> main_window(WIDTH, HEIGHT, 7);
    ClickWindowHandler handler_main_window;
    
    main_window.onButtonClick += CreateMethodEventHandler(handler_main_window, &ClickWindowHandler::print_int);
    main_window.onButtonClick += CreateMethodEventHandler(handler_main_window, &ClickWindowHandler::print_long_long);

    main_window.onButtonClick(s2);
}