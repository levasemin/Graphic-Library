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


int main()
{  
    Application app(Vector2d(WIDTH, HEIGHT));
    
    std::vector<Widget *> buttons();

    MainWindow main_window(Vector2d(WIDTH, HEIGHT), Colors::Green);

    ScrollBar scrollbar(Vector2d(20, 400), Vector2d(10, 200), Colors::Blue);
            
    ScrollContainer container(Vector2d(100, 400), Vector2d(300, 250), Colors::Black);

    Button first_button (Vector2d(100, 50), Vector2d(50, 35), Colors::Yellow, "First");

    first_button.set_left_click(&left_click);
    first_button.set_right_click(&right_click);

    Button second_button(Vector2d(100, 100),  Vector2d(50, 120), Colors::Yellow, "Second");
    second_button.set_left_click (&left_click);
    second_button.set_right_click(&right_click);

    Button third_button (Vector2d(100, 200), Vector2d(50, 280), Colors::Yellow, "Third");
    third_button.set_left_click (&left_click);
    third_button.set_right_click(&right_click);
    
    container.add(&first_button);
    container.add(&second_button);
    container.add(&third_button);
    container.set_scroll_bar(&scrollbar);
    std::cout <<std::endl << container.children_.size();
 
    main_window.add(&container);
    
    app.add(main_window);
    app.exec();
}