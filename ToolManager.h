#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Tool.h"
#include "Image.h"
#include "ToolPalette.h"
#include "Container.h"
#include <vector>
#include "SimpleCommand.h"

class ToolManager
{
private:
    std::vector<booba::Tool *> tools_;

    booba::Tool* active_tool_ = nullptr;
    
    ToolManager(): 
        tools_({}),
        setting_palettes_({})
    {}

    ToolManager( const ToolManager &source):
        tools_(source.tools_),
        active_tool_(source.active_tool_),
        tool_palette_(source.tool_palette_),
        setting_field_(source.setting_field_),
        setting_palettes_(source.setting_palettes_)
    {}

public:
    booba::Tool *init_tool_ = nullptr;

    ToolPalette *tool_palette_ = nullptr;
    Container *setting_field_ = nullptr;
    
    std::vector<Container *> setting_palettes_;

    ToolManager& operator=(const ToolManager& source)
    {
        tools_            = source.tools_;
        active_tool_      = source.active_tool_;
        tool_palette_     = source.tool_palette_;
        setting_field_    = source.setting_field_;
        setting_palettes_ = source.setting_palettes_;

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

    void set_setting_field(Container *setting_palette)
    {
        setting_field_ = setting_palette;
    }

    void add(booba::Tool *new_tool)
    {
        tools_.push_back(new_tool);
        
        Button *tool_button_ = new Button(Vector2d(25, 25), Vector2d(50, 50));
        tool_button_->set_left_click((Command<const Event &> *) new SimpleCommand<ToolManager, const Event &>(this, &ToolManager::tool_choose));
        
        tool_palette_->add(tool_button_);
        
        Container *setting_palette = new Container(Vector2d(setting_field_->get_shape()), Vector2d(setting_field_->get_shape()));
        setting_palettes_.push_back(setting_palette);
        init_tool_ = new_tool;
    }
    
    void tool_choose(const Event &event)
    {        
        std::vector<Widget *> tool_palette_children = tool_palette_->get_children();
        
        for (size_t i = 0; i < tool_palette_children.size(); i++)
        {
            if ((uint64_t)tool_palette_children[i] == event.Oleg_.bcedata.id)
            {
                if (active_tool_ != tools_[i])
                {
                    set_active_tool(tools_[i]);
                }
                
                else
                {
                    remove_active_tool(); 
                }
            }
        }
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
        // setting_field_->remove((Container *) active_tool_->get_setting_widget());
        active_tool_ = nullptr;
    }

    void set_active_tool(booba::Tool *tool)
    {
        size_t current_tool = -1;

        for (size_t i = 0; i < tools_.size(); i++)
        {
            if (tools_[i] == tool)
            {
                current_tool = i;
                break;   
            }
        }

        active_tool_    = tool;

        std::vector<Widget *> setting_field_children = setting_field_->get_children();

        for (size_t i = 0; i < setting_field_children.size(); i++)
        {
            setting_field_->remove(setting_field_children[i]);
        }
    
        setting_field_->add(setting_palettes_[current_tool]);
    }

    booba::Tool *get_active_tool(booba::Tool *tool)
    {
        return active_tool_;
    }

    ~ToolManager() {};
};
