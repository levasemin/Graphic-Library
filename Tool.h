#pragma once

#include "Widget.h"
#include "ToolCommand.h"
#include "ToolButton.h"

#include "tools.h"


class Tool : public booba::Tool
{
    
public:
    char icon_path_[128] = "";
    bool is_on_ = false;

    Tool()
    {
        
    };

    ~Tool() override {};
};