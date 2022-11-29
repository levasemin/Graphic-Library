#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Tool.h"
#include "Image.h"
#include "ToolPalette.h"
#include "Container.h"
#include <vector>

class ToolManager
{
private:
    std::vector<Tool *> tools_;
    Tool* active_tool_ = nullptr;

    ToolPalette *tool_palette_ = nullptr;
    Container *setting_palette_ = nullptr;
    
    ToolManager(): 
        tools_({})
    {}

    ToolManager( const ToolManager &source):
        tools_(source.tools_),
        active_tool_(source.active_tool_),
        tool_palette_(source.tool_palette_),
        setting_palette_(source.setting_palette_)
    {}

    

public:

    ToolManager& operator=(const ToolManager& source)
    {
        tools_           = source.tools_;
        active_tool_     = source.active_tool_;
        tool_palette_    = source.tool_palette_;
        setting_palette_ = source.setting_palette_;

        return *this;
    }

    static ToolManager& getInstance()
    {
        static ToolManager instance;
        return instance;
    }    

    void set_tool_palette(ToolPalette *tool_palette)
    {
        tool_palette_ = tool_palette;
    }

    void set_setting_palette(Container *setting_palette)
    {
        setting_palette_ = setting_palette;
    }

    void add(Tool *new_tool)
    {
        tools_.push_back(new_tool);

        tool_palette_->add(new_tool->get_tool_widget());
    }
    
    void apply(Image *image, const Event *event)
    {
        if (active_tool_)
        {
            booba::Event booba_event = convert_event(*event);
            active_tool_->apply(image, &booba_event);
        }
    }

    void remove_active_tool()
    {
        setting_palette_->remove((Container *) active_tool_->get_setting_widget());
        active_tool_ = nullptr;
    }

    void set_active_tool(Tool *tool)
    {
        for (size_t i = 0; i < tools_.size(); i++)
        {
            if (tools_[i] != tool)
            {
                tools_[i]->apply(nullptr, nullptr);
            }
        }

        active_tool_    = tool;

        std::vector<Widget *> setting_palette_children = setting_palette_->get_children();

        for (size_t i = 0; i < setting_palette_children.size(); i++)
        {
            setting_palette_->remove(setting_palette_children[i]);
        }

        setting_palette_->add((Container *)tool->tool_settings_);
    }

    Tool *get_active_tool(Tool *tool)
    {
        return active_tool_;
    }

    ~ToolManager() {};
};
