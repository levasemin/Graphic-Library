#pragma once

#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Event.h"


template<class ...TParams>
void give_event(MainWindow *window, Event<TParams ...> Widget::*event, TParams ...params)
{
    for (int i = 0; i < window->children_.size(); i++)
    {
        give_event<TParams ...>(window->children_[i], event, params ...);
        ((window->children_[i])->*event)(params ...);
    }
}

MainWindow *get_clicked_window(MainWindow *window, point point);

class EventManager
{

public: 
    void distribute_event(Window *window);
    void distribute_event(MainWindow *window, sf::Event event_);
};

void EventManager::distribute_event(MainWindow *window, sf::Event event)
{
    switch (event.type)
    {   
        case sf::Event::MouseButtonPressed:
        {
            point place = {event.mouseButton.x, event.mouseButton.y};

            if (event.mouseButton.button == sf::Mouse::Left)
            {   
                get_clicked_window(window, place)->ClickLeftEvent_(window, place);
                give_event(window, &Widget::MissClickLeftEvent_, (Widget *)window, place);
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {                     
                get_clicked_window(window, place)->ClickRightEvent_(window, place);
   
                give_event(window, &Widget::MissClickRightEvent_, (Widget *)window, place);
            }

            break;
        }

        case sf::Event::KeyPressed:
        {
            int key = event.key.code;
            
            give_event(window, &Widget::PressKeyEvent_, (Widget *)window, key);

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

MainWindow *get_clicked_window(MainWindow *window, point point)
{
    MainWindow *clicked_window = nullptr;
    
    if (window->point_belonging(point))
    {
        clicked_window = window;
    }

    for (int i = 0; i < window->children_.size(); i++)
    {
        MainWindow *res = get_clicked_window(window->children_[i], point);

        if (res != nullptr)
        {
            clicked_window = res;
        }
    }

    return clicked_window;
}