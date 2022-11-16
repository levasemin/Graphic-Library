#pragma once

#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Widget.h"

template<class ...TParams>
void give_event(Widget *window, void (Widget::*method)(TParams ...), TParams ...params)
{
    std::vector <Widget *> children = window->get_children();
    
    for (int i = 0; i < children.size(); i++)
    {
        ((children[i])->*method)(params ...);
    }
}


class EventManager
{

public: 
    void distribute_event(Window *window, Widget *main_window);
    void distribute_event(Widget *window, sf::Event event_);

private:
    bool is_left_button_clicked_ = false;
    bool is_right_button_clicked_ = false;
};

void EventManager::distribute_event(Widget *window, sf::Event event)
{
    switch (event.type)
    {   
        case sf::Event::MouseButtonPressed:
        {
            Vector2d point(event.mouseButton.x, event.mouseButton.y);

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                is_left_button_clicked_ = true;   
                give_event(window, &Widget::ClickLeftEvent, point);
            }

            else
            if (event.mouseButton.button == sf::Mouse::Right)
            {         
                is_right_button_clicked_ = true;
                give_event(window, &Widget::ClickRightEvent, point);
            }

            break;
        }

        case sf::Event::KeyPressed:
        {
            int key = event.key.code;
            
            give_event(window, &Widget::PressKeyEvent, key);

            break;
        }

        case sf::Event::MouseWheelScrolled:
        {
            double offset  = event.mouseWheelScroll.delta;
            Vector2d point = Vector2d(event.mouseWheelScroll.x, event.mouseWheelScroll.y);

            give_event(window, &Widget::ScrollEvent, point, Vector2d(0, offset));

            break;
        }
        
        case sf::Event::MouseMoved:
        {
            Vector2d point(event.mouseMove.x, event.mouseMove.y);
            
            give_event(window, &Widget::MoveMouseEvent, point);

            break;
        }
        
        case sf::Event::MouseButtonReleased:
        {
            Vector2d point(event.mouseButton.x, event.mouseButton.y);

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                is_left_button_clicked_ = false;
                give_event(window, &Widget::ReleasedLeftEvent, point);
            }

            else
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                is_right_button_clicked_ = false;
                give_event(window, &Widget::ReleasedRightEvent, point);            
            }

            break;
        }

        default:
        {
            break;
        }
    }
}

void EventManager::distribute_event(Window *window, Widget *main_window)
{
    while (window->window_.pollEvent(window->event_))
    {
        if (sf::Event::Closed == window->event_.type)
        {
            window->close();
            break;
        }
        
        distribute_event(main_window, window->event_);        
    }

    Vector2d point(window->event_.mouseButton.x, window->event_.mouseButton.y);

    if (is_left_button_clicked_)
    {
        give_event(main_window, &Widget::PressLeftEvent, point);
    }

    if (is_right_button_clicked_)
    {
        give_event(main_window, &Widget::PressRightEvent, point);
    }
}