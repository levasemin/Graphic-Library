#include "ToolManager.h"

int ToolManager::numCommands_(0);
std::vector<booba::Tool *> ToolManager::toolList_(20);
std::vector<booba::Event>  ToolManager::commandList_(20);
std::vector<Memento *>     ToolManager:: mementoList_(20);