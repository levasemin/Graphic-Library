#include "Tool.h"
#include <vector>

class ToolManager
{
private:
    
    std::vector<booba::Tool *> tools_;
    booba::Tool* active_tool_;
public:
    ToolManager(const std::vector<booba::Tool *> &tools):
        tools_(tools)
    {}

    void add(booba::Tool *new_tool)
    {
        tools_.push_back(new_tool);
    }
    
    void apply(booba::Image *image, const booba::Event *event)
    {
        if (active_tool_)
        {
            active_tool_->apply(image, event);
        }
    }

    void distribute_tool(Widget *)
    {

    }

    ~ToolManager();
};
