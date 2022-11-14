#include "Widget.h"
#include "MainWindow.h"
#include "Widget.h"
#include "Button.h"
#include "Container.h"
#include "ScrollContainer.h"
#include "ScrollBar.h"
#include "DecoratorScrollBar.h"
#include "constants.h"
#include "Application.h"
#include "SimpleCommand.h"
#include "Command.h"
#include <iostream>
#include <vector>
#include "Vector2d.h"

void left_click(Button *self, Vector2d point)
{
    std::cout << " !!! " << point.x_ << " " << point.y_ << std::endl;
}

void right_click(Button *self, Vector2d point)
{
    std::cout << point.x_ << " !!!! " << point.y_ << " " << std::endl;
}



void left_click(Widget *self, Vector2d point)
{
    std::cout << "Window" << " " << point.x_ << " " << point.y_ << std::endl;
}

void right_click(Widget *self, Vector2d point)
{
    std::cout << point.x_ << " " << point.y_ << "Window" << std::endl; 
}

void press_key(Widget *self, int key)
{
    std::cout << "Window key " << key << std::endl;
}


const char *path_britsih = "/home/levce/projectsDED/event_handler2/Event_handler/source/british.jpg";

int main()
{          
    MainWindow main_window(Vector2d(WIDTH, HEIGHT), Texture(Colors::Yellow));
            
    Container container(Vector2d(100, 400), Vector2d(300, 250), Texture(Colors::Black));

    Button first_button (Vector2d(100, 301), Vector2d(50, 160), Texture(Colors::Red));

    Command<Vector2d> *command = (Command<Vector2d> *)new SimpleCommand<Button, Vector2d>(&first_button, &Button::print);

    first_button.set_left_click(command);
    first_button.set_right_click(command);

    Button second_button(Vector2d(100, 400),  Vector2d(50, 520), Texture(path_britsih));
    second_button.set_left_click (command);
    second_button.set_right_click(command);

    Button third_button (Vector2d(100, 200), Vector2d(50, 830), Texture(path_britsih));
    third_button.set_left_click (command);
    third_button.set_right_click(command);
    
    container.add(&first_button);
    container.add(&second_button);
    container.add(&third_button);
        
    DecoratorScrollBar decorator(&container);

    Application app(&main_window);

    main_window.add(&decorator);
    app.exec();
}