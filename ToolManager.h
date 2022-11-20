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
            std::cout << event->Oleg.motion.x << " " << event->Oleg.motion.y << std::endl;

        if (active_tool_)
        {
            booba::Event new_event;
            new_event.type = (booba::EventType) event->type_;
            new_event.Oleg.motion.x = event->Oleg_.motion.x;
            new_event.Oleg.motion.y = event->Oleg_.motion.y;

            active_tool_->apply(image, &new_event);
        }
    }

    void distribute_tool(Widget *)
    {

    }

    void set_active_tool(Tool *tool)
    {
        active_tool_ = tool;
    }

    Tool *get_active_tool(Tool *tool)
    {
        return active_tool_;
    }

    ~ToolManager() {};
};
