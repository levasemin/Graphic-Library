#include "ToolBucket.h"

void ToolBucket::fill_ray(booba::Image *image, Vector2d position, int step)
{
    if (image->getPixel(int(position.x_), int(position.y_)) == booba::APPCONTEXT->fgColor)
    {
        position += Vector2d(float(step), 0);
    }

    for (int x = int(position.x_); 0 < x && x < int(image->getX()); x += step)
    {
        if (image->getPixel(x, int(position.y_)) == current_color_)
        {
            // std::cout << int(Color::convert_uint_color(booba::APPCONTEXT->fgColor).get_sf_color().r) << std::endl;
            // std::cout << int(Color::convert_uint_color(booba::APPCONTEXT->fgColor).get_sf_color().g) << std::endl;
            // std::cout << int(Color::convert_uint_color(booba::APPCONTEXT->fgColor).get_sf_color().b) << std::endl;
            // std::cout << int(Color::convert_uint_color(booba::APPCONTEXT->fgColor).get_sf_color().a) << std::endl << std::endl;
            
            image->putPixel(x, int(position.y_), booba::APPCONTEXT->fgColor);
        }

        else
        {
            return;
        }
    } 
}

void ToolBucket::fill_part(booba::Image *image, Vector2d position, Vector2d orientation)
{
    Vector2d next_position = position - orientation;

    for (int x = int(next_position.x_); x < int(image->getX()) && image->getPixel(x, int(position.y_)) == booba::APPCONTEXT->fgColor; x++)
    {
        if (image->getPixel(x, int(next_position.y_)) == current_color_)
        {
            next_position.x_ = float(x);

            fill_field(image, next_position);
            
            return;
        }
    }

    for (int x = int(position.x_); 0 < x && image->getPixel(x, int(position.y_)) == booba::APPCONTEXT->fgColor; x--)
    {
        if (image->getPixel(x, int(position.y_)) == current_color_)
        {
            next_position.x_ = float(x);

            fill_field(image, next_position);

            return;
        }
    }
}


void ToolBucket::fill_field(booba::Image *image, Vector2d position)
{
    fill_ray(image, position, 1);
    fill_ray(image, position, -1);

    fill_part(image, position, Vector2d(0, 1));
    fill_part(image, position, Vector2d(0, -1));
}

void ToolBucket::apply(booba::Image* image, const booba::Event* event)
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

            Vector2d position((float)event->Oleg.mbedata.x, (float)event->Oleg.mbedata.y);
            current_color_ = image->getPixel(int(position.x_), int(position.y_));

            fill_field(image, position);

            break;
        }

        case booba::EventType::MouseReleased:
        {
            clicked_ = false;
            break;
        }

        case booba::EventType::MouseMoved:
        case booba::EventType::ButtonClicked:
        case booba::EventType::ScrollbarMoved:
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
    new ToolBucket();
}