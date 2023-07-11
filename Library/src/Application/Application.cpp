#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "Application.hpp"

namespace SL
{    
    Application::Application(MainWindow *main_window):
        main_window_(main_window)
    {};

    Application::Application (const Application &source):
        main_window_(source.main_window_),
        window_(source.window_)
    {}
    
    Application &Application::operator= (const Application &source)
    {
        main_window_   = source.main_window_;
        window_        = source.window_;

        return *this;
    }

    void Application::set_main_window(MainWindow *main_window)
    {
        main_window_ = main_window;
    }

    void Application::distribute_event(const Event &event)
    {
        switch (event.type_)
        {   
            case EventType::Closed:
            {
                close();
            }

            case EventType::MousePressed:
            {
                if (event.Oleg_.mbedata.button == MouseButton::Left)
                {
                    main_window_->ClickLeftEvent(event);
                }

                else if (event.Oleg_.mbedata.button == MouseButton::Right)
                {         
                    main_window_->ClickRightEvent(event);
                }

                break;
            }

            case EventType::KeyPressed:
            {
                main_window_->PressKeyEvent(event);

                break;
            }
            case EventType::TextEvent:
            {
                main_window_->TextEvent(event);

                break;
            }
            case EventType::ScrollbarMoved:
            {            
                main_window_->ScrollEvent(event);
                
                break;
            }
            
            case EventType::MouseMoved:
            {            
                main_window_->MoveMouseEvent(event);

                break;
            }
            
            case EventType::MouseReleased:
            {
                if (event.Oleg_.mredata.button == MouseButton::Left)
                {
                    main_window_->ReleasedLeftEvent(event);
                }

                else if (event.Oleg_.mredata.button == MouseButton::Right)
                {
                    main_window_->ReleasedRightEvent(event);            
                }

                break;
            }

            case EventType::NoEvent:
            case EventType::ButtonClicked:
            case EventType::CanvasMPressed:
            case EventType::CanvasMReleased:
            case EventType::CanvasMMoved:
            case EventType::TimerEvent:
            default:
            {
                break;
            }
        }
    }

    void Application::exec()
    {    
        if (!window_)
        {
            window_ = new Window (main_window_->get_shape(), main_window_->style_);
        }
        
        window_->create(main_window_->get_shape(), "", main_window_->style_);

        while(window_->isOpen() && window_->getVisible())
        {
            Event event;

            while (window_->pollEvent(event))
            {
                distribute_event(event);
            }

            show(main_window_);
        }
    }

    void Application::close()
    {
        if (window_)
        {
            window_->close();
        }
    }

    void Application::show(MainWindow *window)
    {
        window_->clear();
        main_window_->draw();   
        main_window_->display(window_);
    }

}