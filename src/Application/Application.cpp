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

    Application::~Application()
    {
        if (window_)
        {
            delete window_;
        }
    }

    void Application::setMainWindow(MainWindow *main_window)
    {
        main_window_ = main_window;
    }

    void Application::distribute_event(const Event &event)
    {
        switch (event.type_)
        {   
            case Event::Closed:
            {
                close();
            }

            case Event::MousePressed:
            {
                if (event.Oleg_.mpedata.button == Event::MouseButton::Left)
                {
                    main_window_->clickLeftEvent(event);
                }

                else if (event.Oleg_.mpedata.button == Event::MouseButton::Right)
                {         
                    main_window_->clickRightEvent(event);
                }

                break;
            }

            case Event::KeyPressed:
            {
                main_window_->pressKeyEvent(event);

                break;
            }
            case Event::textEvent:
            {
                main_window_->textEvent(event);

                break;
            }
            case Event::MouseWheelScrolled:
            {            
                main_window_->scrollEvent(event);
                
                break;
            }
            
            case Event::MouseMoved:
            {            
                main_window_->moveMouseEvent(event);

                break;
            }
            
            case Event::MouseReleased:
            {
                if (event.Oleg_.mredata.button == Event::MouseButton::Left)
                {
                    main_window_->releaseLeftEvent(event);
                }

                else if (event.Oleg_.mredata.button == Event::MouseButton::Right)
                {
                    main_window_->releaseRightEvent(event);            
                }

                break;
            }

            case Event::NoEvent:
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
            window_ = new Window (main_window_->getShape(), static_cast<int>(main_window_->style_));
        }
        
        window_->create(main_window_->getShape(), "", static_cast<int>(main_window_->style_));

        while(window_->isOpen() && window_->getVisible())
        {
            Event event;

            while (window_->pollEvent(event))
            {
                distribute_event(event);
            }

            window_->clear();
            main_window_->draw();   
            main_window_->display(window_);
        }
    }

    void Application::close()
    {
        if (window_)
        {
            window_->close();
        }
    }
}