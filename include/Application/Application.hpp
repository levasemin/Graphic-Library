#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include <vector>
#include <iostream>
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
            Application(MainWindow *main_window);

            Application (const Application &source);
            Application &operator= (const Application &source);
            ~Application();

            void setMainWindow(MainWindow *main_window);

            void exec();
            void close();
        
        private:
            MainWindow *main_window_ = nullptr;
            Window *window_ = nullptr;

            void distribute_event(const Event &event);
    };
}