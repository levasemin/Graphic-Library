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
            window_(main_window_),
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
        
        event_manager_.distribute_event(&window_);
    }
}

void Application::show(Widget *window)
{
    window_.clear();
    main_window_->draw();   
    window_.display();
    RenderTexture rend(Vector2d(720, 720));
    main_window_->render_texture_->render_texture_.clear();
}