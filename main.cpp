#include "Window.h"
#include "MainWindow.h"
#include "Widget.h"
#include "Event.h"
#include "Button.h"
#include "Container.h"
#include "AbstractEventHandler.h"
#include "MethodEventHandler.h"
#include "constants.h"
#include "Application.h"
#include <iostream>
#include <vector>

class Widget_handler
{
public:
    void left_click(Widget *self, point place)
    {
        Button *butt = (Button *) self;
        std::cout << butt->text_ << " " << place.x << " " << place.y << std::endl;
    }

    void right_click(Widget *self, point place)
    {
        Button *butt = (Button *) self;
        std::cout << place.x << " " << place.y << " " << butt->text_ << std::endl;
    }
};

class Window_handler
{
        
public:
    void left_click(Window *self, point place)
    {
        MainWindow *wind = (MainWindow *) self;
        std::cout << "Window" << " " << place.x << " " << place.y << std::endl;
    }

    void right_click(Window *self, point place)
    {
        MainWindow *wind = (MainWindow *) self;
        std::cout << place.x << " " << place.y << "Window" << std::endl; 
    }

    void press_key(Window *self, int key)
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
        printf("keft");
        Container *container = (Container *)self;
        for (int i = 0; i < container->widgets_.size(); i++)
        {
            if (container->widgets_[i]->point_belonging(place))
            {
                container->widgets_[i]->ClickLeftEvent_(container->widgets_[i], place);
            }
            
            else
            {
                container->widgets_[i]->MissClickLeftEvent_(container->widgets_[i], place);
            }
        }
    };

    void right_click(Widget *self, point place)
    {
        Container *container = (Container *)self;
        for (int i = 0; i < container->widgets_.size(); i++)
        {
            if (container->widgets_[i]->point_belonging(place))
            {
                container->widgets_[i]->ClickRightEvent_(container->widgets_[i], place);
            }
            
            else
            {
                container->widgets_[i]->MissClickLeftEvent_(container->widgets_[i], place);
            }
        }
    };
};


int main()
{  
    Button first_button ({50, 50}, 100, 50, Colors::Yellow, "First");
    Widget_handler click_handler;
    first_button.ClickLeftEvent_  += CreateMethodEventHandler(click_handler, &Widget_handler::left_click);
    first_button.ClickRightEvent_ += CreateMethodEventHandler(click_handler, &Widget_handler::right_click);

    Button second_button({225, 225}, 100, 100, Colors::Yellow, "Second");
    second_button.ClickLeftEvent_  += CreateMethodEventHandler(click_handler, &Widget_handler::left_click);
    second_button.ClickRightEvent_ += CreateMethodEventHandler(click_handler, &Widget_handler::right_click);

    Button third_button ({500, 500}, 100, 200, Colors::Yellow, "Third");
    third_button.ClickLeftEvent_  += CreateMethodEventHandler(click_handler, &Widget_handler::left_click);
    third_button.ClickRightEvent_ += CreateMethodEventHandler(click_handler, &Widget_handler::right_click);
    
    std::vector<Widget *> buttons = {(Widget *)&first_button, (Widget *)&second_button, (Widget *)&third_button};

    Container_handler container_handler;
    Container container({300, 250}, 100, 400, buttons, Colors::White, 10);
    container.ClickLeftEvent_  += CreateMethodEventHandler(container_handler, &Container_handler::left_click);
    container.ClickRightEvent_ += CreateMethodEventHandler(container_handler, &Container_handler::right_click);
    
    const char *s1 = "Hello";
    char *s2 = "Hello12";

    Window_handler handler_main_window;
    MainWindow main_window(WIDTH, HEIGHT, 7);
    main_window.ClickLeftEvent_  += CreateMethodEventHandler(handler_main_window, &Window_handler::left_click);
    main_window.ClickRightEvent_ += CreateMethodEventHandler(handler_main_window, &Window_handler::right_click);
    main_window.PressKeyEvent_   += CreateMethodEventHandler(handler_main_window, &Window_handler::press_key);

    std::vector<Widget *> widgets = {(Widget *)&first_button, (Widget *)&second_button, (Widget *)&third_button, (Widget *)&container};
    Application app(&main_window, widgets);
    app.exec();
}