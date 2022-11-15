#include "Tool.h"
#include <vector>
#inc
class ToolManager
{
private:
    
    std::vector<booba::Tool *> tools_;

public:
    ToolManager(std::vector<Tool *> tools):
        tools_(tools)
    {}

    void add(Tool *new_tool)
    {
        tools_.push_back(new_tool);
    }
    
    void distribute_tool(Widget *)
    {

    }

    ~ToolManager();
};
