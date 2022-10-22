#include <vector>
#include <iostream>
#include "Widget.h"


class ManagerEvent
{
    public: 
        ManagerEvent(const std::vector<Widget *> &Widgets) : Widgets_(Widgets) {};
        void get_event();

    private:
        std::vector<Widget *> Widgets_;
};


void ManagerEvent::get_event()
{
    while(Widgets_.size())
    {
        sf::Event event;

        for (int i = 0; i < Widgets_.size(); i++)
        {
            Widgets_[i]->isOpen();

            while(Widgets_[i]->window_.pollEvent(event))
            {
                switch (event.type)
                {
                    case sf::Event::Closed:
                        Widgets_[i]->close();
                        Widgets_.erase(Widgets_.begin() + i);
                        break;
                }
            }
        }
    }
}