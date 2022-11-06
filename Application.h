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
        void add(Widget *main_window);
        void show(Widget *window);
        
    
        Widget *main_window_ = nullptr;
        EventManager event_manager_;
    private:
        Window window_;
};

void Application::add(Widget *main_window)
{
    main_window_ = main_window;
}

void Application::exec()
{        
    while(window_.isOpen())
    {
        show(main_window_);
        
        event_manager_.distribute_event(&window_, main_window_);
    }
}

void Application::show(Widget *window)
{
    window_.clear();
    main_window_->draw();   
    main_window_->display(&window_);
}