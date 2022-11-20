#pragma once

#include "Widget.h"
#include "ToolCommand.h"
#include "tools.h"

uint64_t booba::createButton   (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* object);

class Tool : public booba::Tool
{
    
public:

    uint64_t tool_button_;

    char *icon_path_ = "source/paint-brush.png";
    bool is_on_ = false;

    Tool() {};
    ~Tool() {};

    Widget *get_tool_widget()
    {
        return (Widget *)tool_button_;
    }
};

uint64_t booba::createButton   (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* object)
{   
    Tool *tool = (Tool *)object;

    Button *tool_button = new Button(Vector2d(w, h), Vector2d(x, y), Texture(tool->getTexture()));
    
    tool_button->set_left_click((Command<const Event &> *) new ToolCommand<Tool>(tool, &Tool::apply));

    return (int64_t)tool_button;
}