#include "EventManager.hpp"

namespace SL
{
    void EventManager::distribute_event(Widget *window, const Event &event)
    {
        switch (event.type_)
        {   
            case EventType::MousePressed:
            {
                if (event.Oleg_.mbedata.button == MouseButton::Left)
                {
                    is_left_button_clicked_ = true; 
                    window->clickLeftEvent(event);
                }

                else if (event.Oleg_.mbedata.button == MouseButton::Right)
                {         
                    is_right_button_clicked_ = true;
                    window->clickRightEvent(event);
                }

                break;
            }

            case EventType::KeyPressed:
            {
                window->pressKeyEvent(event);

                break;
            }
            case EventType::textEvent:
            {
                window->textEvent(event);

                break;
            }
            case EventType::ScrollbarMoved:
            {            
                window->scrollEvent(event);
                
                break;
            }
            
            case EventType::MouseMoved:
            {            
                window->moveMouseEvent(event);

                break;
            }
            
            case EventType::MouseReleased:
            {
                if (event.Oleg_.mredata.button == MouseButton::Left)
                {
                    is_left_button_clicked_ = false;
                    window->releaseLeftEvent(event);
                }

                else if (event.Oleg_.mredata.button == MouseButton::Right)
                {
                    is_right_button_clicked_ = false;
                    window->releaseRightEvent(event);            
                }

                break;
            }

            case EventType::NoEvent:
            case EventType::ButtonClicked:
            case EventType::CanvasMPressed:
            case EventType::CanvasMReleased:
            case EventType::CanvasMMoved:
            case EventType::TimerEvent:
            case EventType::Closed:
            default:
            {
                break;
            }
        }
    }
}