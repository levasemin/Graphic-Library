#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include <vector>
#include <iostream>
#include "../Widget/Widget.h"
#include "../Event/EventManager.h"
#include "../Application/MainWindow.h"

namespace SL
{
    class Application
    {
        public: 
            static Application *current_;

            MainWindow *main_window_ = nullptr;
            Window *window_ = nullptr;
            
            EventManager event_manager_;

            Application(MainWindow *main_window):
                main_window_(main_window),
                event_manager_()
                {
                    current_ = this;
                };

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
            
            static Application *get_current()
            {
                return current_;
            }

            void exec();
            void close();
            void set_main_window(MainWindow *main_window);
            void show(MainWindow *window);        
    };
}