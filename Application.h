#pragma once

#include <vector>
#include <iostream>
#include "VirtualWindow.h"
#include "EventManager.h"


class Application
{
    public: 
        Application(Vector2d shape):
            main_window_(shape, shape / 2, Texture(Colors::Black)),
            window_(&main_window_)
            {};
        Application(const VirtualWindow &window):
            main_window_(window),
            window_(&main_window_),
            event_manager_()
            {};

        void exec();
        void add(VirtualWindow *widget);
        void add(const VirtualWindow &main_window);
        void show(VirtualWindow *window);
        
    
        VirtualWindow main_window_;
        EventManager event_manager_;
    private:
        Window window_;
};

void Application::add(const VirtualWindow &main_window)
{
    main_window_ = main_window;
}

void Application::add(VirtualWindow *widget)
{
    main_window_.children_.push_back(widget);
}

void Application::exec()
{        
    while(window_.isOpen())
    {
        show(&main_window_);
        
        event_manager_.distribute_event(&window_);
    }
}

void Application::show(VirtualWindow *window)
{
    window_.clear();
    main_window_.draw();   
    window_.display();
    RenderTexture rend(Vector2d(720, 720));
    main_window_.render_texture_->render_texture_.clear();
}