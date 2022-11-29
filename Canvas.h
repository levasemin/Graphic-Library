#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "RenderTexture.h"
#include "CompositeObject.h"
#include <vector>
#include "Surface.h"
#include "ToolManager.h"
#include "ToolPalette.h"
#include "Vector2d.h"

class Canvas : public CompositeObject
{
public:
    Surface surface_;

    ToolManager &tool_manager_;

    bool is_left_clicked_ = false;

    Canvas(Vector2d shape, Vector2d center, const Image &image, ToolPalette *tool_palette, Container * setting_palette) : 
        CompositeObject(shape, center, Color::Cyan),
        surface_(image.getSize(), image.getSize() / 2, image),
        tool_manager_(ToolManager::getInstance())
    {   
        add(&surface_);

        tool_manager_.set_tool_palette(tool_palette);
        tool_manager_.set_setting_palette(setting_palette);
    }

    Canvas (const Canvas &source): CompositeObject(*(const CompositeObject *)&source),
        surface_(source.surface_),
        tool_manager_(source.tool_manager_)
    {} 

    Canvas &operator= (const Canvas &source)
    { 
        CompositeObject::operator=(*(const CompositeObject *)&source);
        surface_         = source.surface_;
        tool_manager_    = source.tool_manager_;

        return *this;
    }

    void MoveMouseEvent (const Event &event) override
    {
        if (point_belonging(event.Oleg_.motion.pos))
        {
            if (is_left_clicked_)
            {
                Event new_event = event;

                new_event.Oleg_.motion.pos -= surface_.get_global_offset() + (surface_.get_center() - surface_.get_shape() / 2);

                tool_manager_.apply(&surface_, &new_event);
            }
        }
    }

    void ClickLeftEvent(const Event &event) override
    {
        if (point_belonging(event.Oleg_.mbedata.pos))
        {
            is_left_clicked_ = true;
        }
    }

    void ReleasedLeftEvent (const Event &event) override
    {
        is_left_clicked_ = false;
    }

    void set_image(Image *new_image)
    {
        surface_ = Surface(new_image->getSize(), new_image->getSize() / 2, *new_image);
    }

    void add_tool(Tool *new_tool)
    {
        tool_manager_.add(new_tool);
    }    
};