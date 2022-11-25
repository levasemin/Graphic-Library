#pragma once

#include <vector>
#include <iostream>
#include "Widget.h"
#include "EventManager.h"


class Application
{
    public: 
        Application(Widget *window):
            main_window_(window),
            window_(window->get_shape()),
            event_manager_()
            {};

        void exec();
        void set_main_window(Widget *main_window);
        void show(Widget *window);
        
    
        Widget *main_window_ = nullptr;
        EventManager event_manager_;
    private:
        Window window_;
};

void Application::set_main_window(Widget *main_window)
{
    main_window_ = main_window;
}

void Application::exec()
{        
    while(window_.isOpen())
    {
        Event event;

        while (window_.pollEvent(event))
        {
            event_manager_.distribute_event(main_window_, event);
        }

        show(main_window_);
    }
}

void Application::show(Widget *window)
{
    window_.clear();
    main_window_->draw();   
    main_window_->display(&window_);
}