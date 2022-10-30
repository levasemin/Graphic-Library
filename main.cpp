#include "VirtualWindow.h"
#include "MainWindow.h"
#include "Widget.h"
#include "Button.h"
#include "Container.h"
#include "ScrollContainer.h"
#include "ScrollBar.h"
#include "constants.h"
#include "Application.h"
#include <iostream>
#include <vector>
#include "Vector2d.h"

void left_click(Button *self, Vector2d point)
{
    std::cout << self->text_ << " !!! " << point.x_ << " " << point.y_ << std::endl;
}

void right_click(Button *self, Vector2d point)
{
    std::cout << point.x_ << " !!!! " << point.y_ << " " << self->text_ << std::endl;
}



void left_click(VirtualWindow *self, Vector2d point)
{
    std::cout << "Window" << " " << point.x_ << " " << point.y_ << std::endl;
}

void right_click(VirtualWindow *self, Vector2d point)
{
    std::cout << point.x_ << " " << point.y_ << "Window" << std::endl; 
}

void press_key(VirtualWindow *self, int key)
{
    std::cout << "Window key " << key << std::endl;
}

class Container_handler
{
public:
    void left_click(Widget *self, Vector2d point)
    {
        Container *container = (Container *)self;
        std::cout << "Container clicked" << std::endl;
    };

    void right_click(Widget *self, Vector2d point)
    {
        Container *container = (Container *)self;
        std::cout << "Container clicked" << std::endl;
    };
};


const char *path_britsih = "/home/levce/projectsDED/event_handler2/Event_handler/british.jpg";

int main()
{  
    Application app(Vector2d(WIDTH, HEIGHT));
    
    std::vector<Widget *> buttons();

    MainWindow main_window(Vector2d(WIDTH, HEIGHT), Texture(Vector2d(WIDTH, HEIGHT), Colors::Green));

    ScrollBar scrollbar(Vector2d(20, 400), Vector2d(10, 200), Texture(Vector2d(20, 400), Colors::Blue));
            
    ScrollContainer container(Vector2d(100, 400), Vector2d(300, 250), Texture(Vector2d(100, 400), Colors::Black));

    Button first_button (Vector2d(100, 300), Vector2d(50, 160), Texture(Vector2d(100, 300), path_britsih), "First");

    first_button.set_left_click(&left_click);
    first_button.set_right_click(&right_click);

    Button second_button(Vector2d(100, 400),  Vector2d(50, 520), Texture(Vector2d(100, 400), Colors::Blue), "Second");
    second_button.set_left_click (&left_click);
    second_button.set_right_click(&right_click);

    Button third_button (Vector2d(100, 200), Vector2d(50, 830), Texture(Vector2d(100, 200), Colors::Yellow), "Third");
    third_button.set_left_click (&left_click);
    third_button.set_right_click(&right_click);
    
    container.add(&first_button);
    container.add(&second_button);
    container.add(&third_button);
    
    container.set_scroll_bar(&scrollbar);
 
    main_window.add(&container);
    app.add(main_window);
    app.exec();
}