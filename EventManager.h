#pragma once

#include <SFML/Graphics.hpp>
#include "Window.h"

template<class InheritanceClass>
VirtualWindow *get_chosen_window(VirtualWindow *window, Vector2d point)
{
    VirtualWindow *chosen_window = nullptr;
    
    if (window->point_belonging(point) && dynamic_cast<InheritanceClass *> (window))
    {
        chosen_window = window;
    }

    for (int i = 0; i < window->children_.size(); i++)
    {
        VirtualWindow *chosen_child = get_chosen_window<InheritanceClass>(window->children_[i], point);

        if (chosen_child != nullptr)
        {
            chosen_window = chosen_child;
        }
    }

    return chosen_window;
}

template<class ...TParams>
void give_event(VirtualWindow *window, void (VirtualWindow::*method)(TParams ...), TParams ...params)
{
    for (int i = 0; i < window->children_.size(); i++)
    {
        give_event<TParams ...>(window->children_[i], method, params ...);
        ((window->children_[i])->*method)(params ...);
    }
}

VirtualWindow *get_chosen_window(VirtualWindow *window, Vector2d point);

class EventManager
{

public: 
    void distribute_event(Window *window);
    void distribute_event(VirtualWindow *window, sf::Event event_);
};

void EventManager::distribute_event(VirtualWindow *window, sf::Event event)
{
    switch (event.type)
    {   
        case sf::Event::MouseButtonPressed:
        {
            Vector2d point(event.mouseButton.x, event.mouseButton.y);

            if (event.mouseButton.button == sf::Mouse::Left)
            {   
                get_chosen_window<VirtualWindow>(window, point)->ClickLeftEvent(point);
                give_event(window, &VirtualWindow::MissClickLeftEvent, point);
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {                     
                get_chosen_window<VirtualWindow>(window, point)->ClickRightEvent(point);
                give_event(window, &VirtualWindow::MissClickRightEvent, point);
            }

            break;
        }

        case sf::Event::KeyPressed:
        {
            int key = event.key.code;
            
            give_event(window, &VirtualWindow::PressKeyEvent, key);

            break;
        }

        case sf::Event::MouseWheelScrolled:
        {
            double offset  = event.mouseWheelScroll.delta;
            Vector2d point = Vector2d(event.mouseWheelScroll.x, event.mouseWheelScroll.y);
            get_chosen_window<ScrollVirtualWindow>(window, point)->ScrollEvent(point, offset);

            break;
        }
        
        case sf::Event::MouseMoved:
        {
            Vector2d point(event.mouseMove.x, event.mouseMove.y);
            get_chosen_window<VirtualWindow>(window, point)->MoveMouse(point);

            break;
        }

        case sf::Event::MouseButtonReleased:
        {
            Vector2d point(event.mouseButton.x, event.mouseButton.y);

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                give_event(window, &VirtualWindow::ReleasedLeftEvent, point);
            }

            else
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                give_event(window, &VirtualWindow::ReleasedRightEvent, point);            
            }
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