#include <vector>
#include <iostream>
#include "Widget.h"
#include "constants.h"
#include "Window.h"
#include "Event.h"
#include <SFML/Graphics.hpp>


class Application
{
    public: 
        Application(Window *main_window, const std::vector<Widget *> &widgets) :
            main_window_(main_window),
            widgets_(widgets) 
            {};

        void exec();

    private:
        Window *main_window_;
        std::vector<Widget *> widgets_;
};


void Application::exec()
{
    sf::Event event;

    while(main_window_->isOpen())
    {
        main_window_->draw(widgets_);

        while(main_window_->window_.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    main_window_->close();
                    break;
                }
                
                case sf::Event::MouseButtonPressed:
                {
                    point place = {event.mouseButton.x, event.mouseButton.y};

                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        main_window_->ClickLeftEvent_(main_window_, place);

                        for (int i = 0; i < widgets_.size(); i++)
                        {
                            if (widgets_[i]->point_belonging(place))
                            {
                                widgets_[i]->ClickLeftEvent_(widgets_[i], place);
                            }

                            else
                            {
                                widgets_[i]->MissClickLeftEvent_(widgets_[i], place);
                            }
                        }
                    }

                    if (event.mouseButton.button == sf::Mouse::Right)
                    {                        
                        main_window_->ClickRightEvent_(main_window_, place);

                        for (int i = 0; i < widgets_.size(); i++)
                        {
                            if (widgets_[i]->point_belonging(place))
                            {
                                widgets_[i]->ClickRightEvent_(widgets_[i], place);
                            }

                            else
                            {
                                widgets_[i]->MissClickRightEvent_(widgets_[i], place);
                            }
                        }    
                    }

                    break;
                }

                case sf::Event::KeyPressed:
                {
                    int key = event.key.code;

                    main_window_->PressKeyEvent_(main_window_, key);

                    for (int i = 0; i < widgets_.size(); i++)
                    {
                        widgets_[i]->PressKeyEvent_(widgets_[i], key);
                    }

                    break;
                }

                default:
                {
                    break;
                }
            }
        }

        main_window_->display();
    }
}