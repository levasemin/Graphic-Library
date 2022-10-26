#include "Window.h"
#include "MainWindow.h"
#include "Widget.h"
#include "Event.h"
#include "Button.h"
#include "Container.h"
#include "AbstractEventHandler.h"
#include "MethodEventHandler.h"
#include "FunctoinEventHandler.h"
#include "constants.h"
#include "Application.h"
#include <iostream>
#include <vector>

void left_click(Widget *self, point place)
{
    Button *butt = (Button *) self;
    std::cout << butt->text_ << " !!! " << place.x << " " << place.y << std::endl;
}

void right_click(Widget *self, point place)
{
    Button *butt = (Button *) self;
    std::cout << place.x << " !!!! " << place.y << " " << butt->text_ << std::endl;
}


class Window_handler
{
        
public:
    void left_click(Widget *self, point place)
    {
        MainWindow *wind = (MainWindow *) self;
        std::cout << "Window" << " " << place.x << " " << place.y << std::endl;
    }

    void right_click(Widget *self, point place)
    {
        MainWindow *wind = (MainWindow *) self;
        std::cout << place.x << " " << place.y << "Window" << std::endl; 
    }

    void press_key(Widget *self, int key)
    {
        MainWindow *wind = (MainWindow *) self;
        std::cout << "Window key " << key << std::endl;
    }
};

class Container_handler
{
public:
    void left_click(Widget *self, point place)
    {
        Container *container = (Container *)self;
        std::cout << "Container clicked" << std::endl;
    };

    void right_click(Widget *self, point place)
    {
        Container *container = (Container *)self;
        std::cout << "Container clicked" << std::endl;
    };
};


int main()
{  
    Application app(WIDTH, HEIGHT);
    
    std::vector<Widget *> buttons();

    Window_handler handler_main_window;
    MainWindow main_window(WIDTH, HEIGHT);
    
    main_window.ClickLeftEvent_  += CreateMethodEventHandler(handler_main_window, &Window_handler::left_click);
    main_window.ClickRightEvent_ += CreateMethodEventHandler(handler_main_window, &Window_handler::right_click);
    main_window.PressKeyEvent_   += CreateMethodEventHandler(handler_main_window, &Window_handler::press_key);

    Container container({300, 250}, 100, 400, Colors::White);
    Container_handler container_handler;

    container.ClickLeftEvent_  += CreateMethodEventHandler(container_handler, &Container_handler::left_click);
    container.ClickRightEvent_ += CreateMethodEventHandler(container_handler, &Container_handler::right_click);

    Button first_button ({50, 35},  100, 50, Colors::Yellow, "First");

    first_button.ClickLeftEvent_  += CreateFunctionEventHandler(left_click);
    first_button.ClickRightEvent_ += CreateFunctionEventHandler(right_click);

    Button second_button({50, 120}, 100, 100, Colors::Yellow, "Second");
    second_button.ClickLeftEvent_  += CreateFunctionEventHandler(left_click);
    second_button.ClickRightEvent_ += CreateFunctionEventHandler(right_click);

    Button third_button ({50, 280}, 100, 200, Colors::Yellow, "Third");
    third_button.ClickLeftEvent_  += CreateFunctionEventHandler(left_click);
    third_button.ClickRightEvent_ += CreateFunctionEventHandler(right_click);
    
    container.add(&first_button);
    container.add(&second_button);
    container.add(&third_button);
    main_window.add(&container);
    app.add(main_window);
    app.exec();
}