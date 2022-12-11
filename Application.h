#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include <vector>
#include <iostream>
#include "Widget.h"
#include "EventManager.h"


class Application
{
    public: 
        MainWindow *main_window_ = nullptr;
        Window window_;

        EventManager event_manager_;

        Application(MainWindow *main_window):
            main_window_(main_window),
            window_(main_window->get_shape(), main_window->style_),
            event_manager_()
            {};

        Application (const Application &source):
            main_window_(source.main_window_),
            window_(source.window_),
            event_manager_(source.event_manager_)
        {}
        
        Application &operator=(const Application &source)
        {
            main_window_   = source.main_window_;
            window_        = source.window_;
            event_manager_ = source.event_manager_;

            return *this;
        }

        void exec();
        void close();
        void set_main_window(MainWindow *main_window);
        void show(MainWindow *window);
        
    
        
};

void Application::set_main_window(MainWindow *main_window)
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

void Application::close()
{
    window_.close();
}

void Application::show(MainWindow *window)
{
    window_.clear();
    main_window_->draw();   
    main_window_->display(&window_);
}