#pragma once

#include "Widget.h"
#include "ToolCommand.h"
#include "ToolButton.h"

#include "tools.h"


class Tool : public booba::Tool
{
    
public:
    uint64_t tool_button_   = (uint64_t)nullptr;
    uint64_t tool_settings_ = (uint64_t)nullptr;

    char icon_path_[128] = "";
    bool is_on_ = false;

    Tool()
    {
        
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