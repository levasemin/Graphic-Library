#pragma once

#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Widget.h"

template<class ...TParams>
void give_event(Widget *window, void (Widget::*method)(TParams ...), TParams ...params)
{
    for (int i = 0; i < window->children_.size(); i++)
    {
        ((window->children_[i])->*method)(params ...);
    }
}

Widget *get_chosen_window(Widget *window, Vector2d point);

class EventManager
{

public: 
    void distribute_event(Window *window);
    void distribute_event(Widget *window, sf::Event event_);
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
                give_event(window, &Widget::ClickLeftEvent, point);
            }

            else
            if (event.mouseButton.button == sf::Mouse::Right)
            {         
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
            
            give_event(window, &Widget::MoveMouse, point);

            break;
        }

        case sf::Event::MouseButtonReleased:
        {
            Vector2d point(event.mouseButton.x, event.mouseButton.y);

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                give_event(window, &Widget::ReleasedLeftEvent, point);
            }

            else
            if (event.mouseButton.button == sf::Mouse::Right)
            {
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

void EventManager::distribute_event(Window *window)
{
    while (window->window_.pollEvent(window->event_))
    {
        if (sf::Event::Closed == window->event_.type)
        {
            window->close();
            break;
        }
        
        distribute_event(window->main_window_, window->event_);        
    }
}