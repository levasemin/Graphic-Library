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
    ToolManager &tool_manager_;
    ToolPalette *tool_palette_;

    Surface surface_;

    bool is_left_clicked_;

    Canvas(Vector2d shape, Vector2d center, const Image &image, ToolPalette *tool_palette, Widget *parent = nullptr) : 
        CompositeObject(shape, center, Colors::Cyan, parent),
        surface_(image.getSize(), image.getSize() / 2, image),
        tool_palette_(tool_palette),
        tool_manager_(ToolManager::getInstance())
    {   
        add(&surface_);
    }

    void MoveMouseEvent (const Event &event)
    {
        if (point_belonging(Vector2d(event.Oleg_.motion.x, event.Oleg_.motion.y)))
        {
            if (is_left_clicked_)
            {
                Event new_event = event;
                new_event.Oleg_.motion.x -= surface_.get_global_offset().x_;
                new_event.Oleg_.motion.y -= surface_.get_global_offset().y_;

                tool_manager_.apply(&surface_, &new_event);
            }
        }
    }

    void ClickLeftEvent(const Event &event) override
    {
        if (point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)))
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
        tool_palette_->add(new_tool->get_tool_widget());
    }    
};