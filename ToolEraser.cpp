#include "ToolEraser.h"

void ToolEraser::paint(booba::Image *image)
{
    drawing_object_.draw_on_image(image, Vector2d(points_.back().x_, points_.back().y_));

    if (points_.size() == 4)
    {
        for (float t = 0; t <= 1.f; t += 0.1f)
        {
            Vector2d new_point = interpolator_(t, points_[0], points_[1], points_[2], points_[3]);
            
            drawing_object_.draw_on_image(image, new_point);
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
        case booba::EventType::MousePressed:
        {
            clicked_ = true;

            Vector2d new_point((float)event->Oleg.mbedata.x, (float)event->Oleg.mbedata.y);

            points_.push_back(new_point);
            paint(image);
            points_.pop_back();

            break;
        }

        case booba::EventType::MouseReleased:
        {
            clicked_ = false;
            break;
        }

        case booba::EventType::MouseMoved:
        {
            if (clicked_)
            {
                Vector2d new_point((float)event->Oleg.mbedata.x, (float)event->Oleg.mbedata.y);

                if (points_.size() > 0)
                {
                    if (abs(points_.back().x_ - new_point.x_) > float(image->getX()) / 100.f + 1.f || abs(points_.back().y_ - new_point.y_) > float(image->getH()) / 10.f + 1.f)
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
                drawing_object_.set_radius(int(event->Oleg.smedata.value * 30.f));
            }

            break;
        }

        case booba::EventType::NoEvent:
        case booba::EventType::CanvasMMoved:
        case booba::EventType::CanvasMPressed:
        case booba::EventType::CanvasMReleased:
        
        default:
            break;
    }
}



void booba::init_module()
{
    new ToolEraser();
}