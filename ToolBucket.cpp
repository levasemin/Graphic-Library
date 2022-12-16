#include "ToolBucket.h"

bool color_eq(const Color &color1, const Color &color2, int disp)
{
    return abs(int(color1.get_r()) - int(color2.get_r())) <= disp &&
           abs(int(color1.get_g()) - int(color2.get_g())) <= disp &&
           abs(int(color1.get_b()) - int(color2.get_b())) <= disp;
}

void ToolBucket::fill_ray(booba::Image *image, Vector2d previous_position, Vector2d current_position)
{
    for (int x = int(current_position.x_); x < int(image->getX()); x ++)
    {
        if (image->getPixel(x, int(current_position.y_)) == current_color_)
        {
            image->putPixel(x, int(current_position.y_), booba::APPCONTEXT->fgColor);
        }

        else if (doublecmp(previous_position.x_, -1))
        {
            uint32_t prev_color = image->getPixel(x, int(previous_position.y_));
            Color previous_color = Color::convert_uint_color(prev_color);
            Color appcontext_color = Color::convert_uint_color(booba::APPCONTEXT->fgColor);
            
            if (!color_eq(appcontext_color, previous_color, 0))
            {
                break;            
            }
        }

        else
        {
            break;
        }
    } 

    for (int x = int(current_position.x_) - 1; x > -1; x --)
    {
        if (image->getPixel(x, int(current_position.y_)) == current_color_)
        {             
            image->putPixel(x, int(current_position.y_), booba::APPCONTEXT->fgColor);
        }

        else if (doublecmp(previous_position.x_, -1))
        {
            uint32_t prev_color = image->getPixel(x, int(previous_position.y_));
            Color previous_color = Color::convert_uint_color(prev_color);
            Color appcontext_color = Color::convert_uint_color(booba::APPCONTEXT->fgColor);
            
            if (!color_eq(appcontext_color, previous_color, 0))
            {
                break;            
            }
        }

        else
        {
            break;
        }
    } 
}

void ToolBucket::fill_part(booba::Image *image, Vector2d position, Vector2d orientation)
{
    Vector2d next_position = position - orientation;
    Vector2d left_position = next_position;
    Vector2d right_position = next_position;

    int left_flag = false;
    int right_flag = false;

    for (int x = int(right_position.x_); x < int(image->getX()); x++)
    {
        uint32_t pixel_color = image->getPixel(x, int(right_position.y_));
        
        if (pixel_color != current_color_ && image->getPixel(x, int(position.y_)) != booba::APPCONTEXT->fgColor)
        {
            break;
        }

        if (pixel_color == current_color_ && image->getPixel(x, int(position.y_)) == booba::APPCONTEXT->fgColor)        
        {
            right_position.x_ = float(x);
            right_flag = true;
        }
    }

    for (int x = int(position.x_); x > -1; x--)
    {
        uint32_t pixel_color = image->getPixel(x, int(left_position.y_));
        
        if (pixel_color != current_color_ && image->getPixel(x, int(position.y_)) != booba::APPCONTEXT->fgColor)
        {
            break;
        }

        if (pixel_color == current_color_ && image->getPixel(x, int(position.y_)) == booba::APPCONTEXT->fgColor)        
        {
            left_position.x_ = float(x);
            left_flag = true;
        }
    }

    if (left_flag)
    {
        fill_ray(image, position, next_position);
        fill_part(image, left_position, orientation);
        fill_part(image, left_position, orientation * -1);
    }
    
    if (right_flag)
    {
        fill_ray(image, position, next_position);
        fill_part(image, right_position, orientation);
        fill_part(image, right_position, orientation * -1);
    }
}


void ToolBucket::fill_field(booba::Image *image, Vector2d position)
{
    fill_ray(image, Vector2d(-1, -1), position);
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