#pragma once

#include "Tool.h"
#include "Image.h"
#include <vector>

class ToolManager
{
private:
    ToolManager() {}
    ToolManager( const ToolManager&);  
    ToolManager& operator=( ToolManager& );

    std::vector<Tool *> tools_;
    Tool* active_tool_;
    
    std::vector <Texture *> textures_;

public:
    static ToolManager& getInstance()
    {
        static ToolManager instance;
        return instance;
    }    

    void add(Tool *new_tool)
    {
        tools_.push_back(new_tool);

        Texture *new_texture = new Texture(new_tool->getTexture()); 
        textures_.push_back(new_texture);
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
        active_tool_ = nullptr;
    }

    void set_active_tool(Tool *tool)
    {
        for (int i = 0; i < tools_.size(); i++)
        {
            if (tools_[i] != tool)
            {
                tools_[i]->apply(nullptr, nullptr);
            }
        }

        active_tool_ = tool;
    }

    Tool *get_active_tool(Tool *tool)
    {
        return active_tool_;
    }

    ~ToolManager() {};
};
