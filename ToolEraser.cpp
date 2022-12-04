#include "ToolEraser.h"

void ToolEraser::paint(booba::Image *image)
{
    drawing_object_.draw_on_image(image, Vector2d(points_.back().x, points_.back().y));

    if (points_.size() == 4)
    {
        for (float t = 0; t <= 1.f; t += 0.1f)
        {
            point new_point = interpolator_(t, points_[0], points_[1], points_[2], points_[3]);
            
            drawing_object_.draw_on_image(image, Vector2d(new_point.x, new_point.y));
        }
    }
}

void ToolEraser::apply(booba::Image* image, const booba::Event* event)
{    
    if (image == nullptr && event == nullptr)
    {
        return;
    }

    switch (event->type)
    {
        case booba::EventType::CanvasMPressed:
        {
            clicked_ = true;
            break;
        }

        case booba::EventType::CanvasMReleased:
        {
            clicked_ = false;
            break;
        }

        case booba::EventType::CanvasMMoved:
        {
            if (clicked_)
            {
                point new_point = {(float)event->Oleg.motion.x, (float)event->Oleg.motion.y};

                if (points_.size() > 0)
                {
                    if (abs(points_.back().x - new_point.x) > float(image->getX()) / 100.f + 1.f || abs(points_.back().y - new_point.y) > float(image->getH()) / 10.f + 1.f)
                    {
                        points_.clear();
                    }
                }

                points_.push_back(new_point);
                
                if (points_.size() > 4)
                {
                    points_.pop_front();
                }

                paint(image);
            }
            
            break;
        }

        case booba::EventType::ButtonClicked:

        case booba::EventType::ScrollbarMoved:
        {
            if (width_scroll_bar_ == event->Oleg.smedata.id)
            {
                drawing_object_.set_radius(int(event->Oleg.smedata.value * 100.f));
            }

            break;
        }

        case booba::EventType::NoEvent:
        case booba::EventType::MouseMoved:
        {
            clicked_ = false;
            break;
        }
        case booba::EventType::MousePressed:
        case booba::EventType::MouseReleased:
        {
            clicked_ = false;
            break;
        }
        
        default:
            break;
    }
}



void booba::init_module()
{
    new ToolEraser();
}