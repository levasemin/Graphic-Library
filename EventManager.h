#pragma once

#include <SFML/Graphics.hpp>
#include "Window.h"


template<class ...TParams>
void give_event(MainWindow *window, void (MainWindow::*method)(TParams ...), TParams ...params)
{
    for (int i = 0; i < window->children_.size(); i++)
    {
        give_event<TParams ...>(window->children_[i], method, params ...);
        ((window->children_[i])->*method)(params ...);
    }
}

MainWindow *get_clicked_window(MainWindow *window, Vector2d point);

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
            Vector2d point(event.mouseButton.x, event.mouseButton.y);

            if (event.mouseButton.button == sf::Mouse::Left)
            {   
                get_clicked_window(window, point)->ClickLeftEvent(point);
                give_event(window, &MainWindow::MissClickLeftEvent, point);
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {                     
                get_clicked_window(window, point)->ClickRightEvent(point);
                give_event(window, &MainWindow::MissClickRightEvent, point);
            }

            break;
        }

        case sf::Event::KeyPressed:
        {
            int key = event.key.code;
            
            give_event(window, &MainWindow::PressKeyEvent, key);

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

MainWindow *get_clicked_window(MainWindow *window, Vector2d point)
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