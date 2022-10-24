#include <vector>
#include <iostream>
#include "Widget.h"
#include "constants.h"
#include "MainWindow.h"
#include "Event.h"
#include <SFML/Graphics.hpp>


class Application
{
    public: 
        Application(int width, int height, int style = sf::Style::Default):
            main_window_(width, height, style),
            window_(&main_window_)
            {};
        Application(const MainWindow &window):
            main_window_(window),
            window_(&main_window_)
            {};

        void exec();
        void add(Widget *widget);
        void add(const MainWindow &main_window);
        
    
        MainWindow main_window_;

    private:
        Window window_;
};

void Application::add(const MainWindow &main_window)
{
    main_window_ = main_window;
}

void Application::add(Widget *widget)
{
    main_window_.child_widgets_.push_back(widget);
}

void Application::exec()
{
    sf::Event event;
        
    while(window_.isOpen())
    {
        main_window_.draw(nullptr, 0);
        while(window_.window_.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window_.close();
                    break;
                }
                
                case sf::Event::MouseButtonPressed:
                {
                    point place = {event.mouseButton.x, event.mouseButton.y};

                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        main_window_.ClickLeftEvent_(&main_window_, place);

                        for (int i = 0; i < main_window_.child_widgets_.size(); i++)
                        {
                            if (main_window_.child_widgets_[i]->point_belonging(place))
                            {
                                main_window_.child_widgets_[i]->ClickLeftEvent_(main_window_.child_widgets_[i], place);
                            }

                            else
                            {
                                main_window_.child_widgets_[i]->MissClickLeftEvent_(main_window_.child_widgets_[i], place);
                            }
                        }
                    }

                    if (event.mouseButton.button == sf::Mouse::Right)
                    {                        
                        main_window_.ClickRightEvent_(&main_window_, place);

                        for (int i = 0; i < main_window_.child_widgets_.size(); i++)
                        {
                            if (main_window_.child_widgets_[i]->point_belonging(place))
                            {
                                main_window_.child_widgets_[i]->ClickRightEvent_(main_window_.child_widgets_[i], place);
                            }

                            else
                            {
                                main_window_.child_widgets_[i]->MissClickRightEvent_(main_window_.child_widgets_[i], place);
                            }
                        }    
                    }

                    break;
                }

                case sf::Event::KeyPressed:
                {
                    int key = event.key.code;

                    main_window_.PressKeyEvent_(&main_window_, key);

                    for (int i = 0; i < main_window_.child_widgets_.size(); i++)
                    {
                        main_window_.child_widgets_[i]->PressKeyEvent_(main_window_.child_widgets_[i], key);
                    }

                    break;
                }

                default:
                {
                    break;
                }
            }
        }

        window_.display();
    }
}