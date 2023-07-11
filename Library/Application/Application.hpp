#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include <vector>
#include <iostream>
#include "Widget.hpp"
#include "EventManager.hpp"
#include "MainWindow.hpp"

namespace SL
{
    /**
     * @brief 
     * 
     */
    class Application
    {
        public: 
            MainWindow *main_window_ = nullptr;
            Window *window_ = nullptr;
            
            Application(MainWindow *main_window);

            Application (const Application &source);
            Application &operator= (const Application &source);

            void set_main_window(MainWindow *main_window);

            void distribute_event(const Event &event);

            void exec();
            void close();
            void show(MainWindow *window);        
    };
}