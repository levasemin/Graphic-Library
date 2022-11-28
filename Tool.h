#pragma once

#include "Widget.h"
#include "ToolCommand.h"
#include "ToolButton.h"
#include "tools.h"

uint64_t setup_widget_ = (uint64_t)nullptr;

class Tool : public booba::Tool
{
    
public:

    uint64_t tool_button_   = (uint64_t)nullptr;
    uint64_t tool_settings_ = (uint64_t)nullptr;

    char icon_path_[128] = "";
    bool is_on_ = false;

    Tool() 
    {
        setup_widget_ = (uint64_t)this;
    };

    ~Tool() override {};

    Widget *get_tool_widget()
    {
        return (Widget *)tool_button_;
    }

    Widget *get_setting_widget()
    {
        return (Widget *)tool_settings_;
    }
};

uint64_t booba::createButton   (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* object)
{   
    Tool *tool = (Tool *)setup_widget_;

    ToolButton *tool_button = new ToolButton(Vector2d((float)w, (float)h), Vector2d((float)x, (float)y), Texture(tool->getTexture()));

    tool_button->set_left_click((Command<const Event &> *) new ToolCommand<Tool>(tool, &Tool::apply));

    return (int64_t)tool_button;
}