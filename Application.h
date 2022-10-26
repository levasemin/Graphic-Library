#pragma once

#include <vector>
#include <iostream>
#include "Widget.h"
#include "constants.h"
#include "MainWindow.h"
#include "Event.h"
#include "EventManager.h"
#include <SFML/Graphics.hpp>


class Application
{
    public: 
        Application(int width, int height):
            main_window_(width, height, {width / 2, height / 2}),
            window_(&main_window_)
            {};
        Application(const MainWindow &window):
            main_window_(window),
            window_(&main_window_),
            event_manager_()
            {};

        void exec();
        void add(MainWindow *widget);
        void add(const MainWindow &main_window);
        
    
        MainWindow main_window_;
        EventManager event_manager_;
    private:
        Window window_;
};

void Application::add(const MainWindow &main_window)
{
    main_window_ = main_window;
}

void Application::add(MainWindow *widget)
{
    main_window_.children_.push_back(widget);
}

void Application::exec()
{        
    while(window_.isOpen())
    {
        main_window_.draw(main_window_.width_);
        
        event_manager_.distribute_event(&window_);

        window_.display();
    }
}