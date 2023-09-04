#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "Application.hpp"

namespace SL
{    
    Application *Application::current_app = nullptr;

    Application::Application(MainWindow *main_window):
        main_window_(main_window)
    {
        default_shape_ = main_window_->getShape();
    };

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
        default_shape_ = main_window_->getShape();
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
                    main_window_->pressEvent(event);
        
                    break;
            }

            case Event::KeyPressed:
            {
                main_window_->pressKeyEvent(event);

                break;
            }
            case Event::TextEntered:
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
                main_window_->releaseEvent(event);
            
                break;
            }

            case Event::Resized:
            {
                Event ev = event;
                
                std::cout << window_->window_.getSize().x << " " << window_->window_.getSize().y << std::endl;

                sf::FloatRect view(0, 0, ev.Oleg_.redata.shape.x_, ev.Oleg_.redata.shape.y_);
                window_->window_.setView(sf::View(view));
                
                ev.Oleg_.redata.shape = Vector2d(ev.Oleg_.redata.shape.x_ / main_window_->getShape().x_, 
                                                 ev.Oleg_.redata.shape.y_ / main_window_->getShape().y_);

                main_window_->resizedEvent(ev);
                
                break;
            }
            case Event::NoEvent:
            default:
            {
                break;
            }
        }
    }

    Vector2d Application::getCoeff()
    {
        if (current_app)
        {
            if (current_app->window_ && current_app->main_window_)
            {
                return Vector2d(current_app->window_->window_.getSize().x / current_app->default_shape_.x_, 
                                current_app->window_->window_.getSize().y / current_app->default_shape_.y_);
            }
        }

        return Vector2d(1, 1);
    }

    void Application::exec()
    {    
        current_app = this;

        if (!window_)
        {
            window_ = new Window (main_window_->getShape(), static_cast<int>(main_window_->style_));
        }
        
        window_->create(main_window_->getShape(), "", static_cast<int>(main_window_->style_));

        while(window_->isOpen() && window_->getVisible())
        {
            Event event;
            window_->clear();

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