#include "ToolEyeDropper.h"

void ToolEyeDropper::apply(booba::Image* image, const booba::Event* event)
{
    switch (event->type)
    {
        case booba::EventType::CanvasMPressed:
        {
            clicked_ = true;
            Color color = Color::convert_uint_color(image->getPixel(event->Oleg.cedata.x, event->Oleg.cedata.y));
            
            set_color(color);

            break;
        }

        case booba::EventType::CanvasMMoved:
        {
            if (clicked_)
            {
                Color color = Color::convert_uint_color(image->getPixel(event->Oleg.cedata.x, event->Oleg.cedata.y));
            
                set_color(color);
            }

            break;
        }

        case booba::EventType::MouseReleased:
        {
            clicked_ = false;
            break;
        }

        case booba::EventType::CanvasMReleased:
        {
            clicked_ = false;
            break;
        }

        case booba::EventType::NoEvent:
        case booba::EventType::MouseMoved:
        case booba::EventType::MousePressed:
        case booba::EventType::ButtonClicked:
        case booba::EventType::ScrollbarMoved:
    default:
        break;
    }
}

void booba::init_module()
{
    new ToolEyeDropper;
}