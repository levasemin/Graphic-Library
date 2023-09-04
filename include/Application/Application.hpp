#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include <vector>
#include <iostream>
#include "MainWindow.hpp"

namespace SL
{
    /**
     * @brief class Application manages the GUI application's control flow and main settings. 
     * 
     */
    class Application
    {
        public:

            /**
             * @brief Construct a new Application object.
             * 
             * @param main_window virtual window, that will be drawn in window.
             */
            Application(MainWindow *main_window);

            Application (const Application &source) = default;
            Application &operator= (const Application &source) = default;
            ~Application();

            /**
             * @brief Set the Main Window object
             * 
             * @param main_window new virtual window.
             */
            void setMainWindow(MainWindow *main_window);

            static Vector2d getCoeff();

            /**
             * @brief start application.
             * @details others application will be frozen until this is closed.
             */
            void exec();

            /**
             * @brief close application.
             */
            void close();

        private:
            Vector2d default_shape_;

            MainWindow *main_window_ = nullptr;
            Window *window_ = nullptr;
            /**
             * @brief spread the caught event among widgets.
             * 
             * @param event 
             */
            void distribute_event(const Event &event);
            
            static Application *current_app;
    };
}