#pragma once

#include "Tool.h"
#include "Command.h"
#include "ToolCommand.h"
#include "ToolManager.h"

uint64_t createButton   (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* object);

class ToolPaint : public Tool
{
public:
    
    ToolPaint() : Tool()
    {
        buildSetupWidget();
    }

    void apply(booba::Image* image, const booba::Event* event) override
    {    
        switch (event->type)
        {
            case booba::EventType::MouseMoved:
            {
                if (is_on_)
                {
                    image->putPixel(event->Oleg.motion.x, event->Oleg.motion.y, 0);
                }

                break;
            }

            case booba::EventType::ButtonClicked:
            {
                if (event->Oleg.bcedata.id == tool_button_)
                {
                    std::cout << is_on_ << std::endl;
                    
                    if (!is_on_)
                    {
                        ToolManager &tool_manager = ToolManager::getInstance();
                        tool_manager.set_active_tool(this);
                    }

                    is_on_ = !is_on_;
                }
            }
            
            default:
                break;
        }
    }

    const char* getTexture() override
    {
        return icon_path_;
    } 

    void buildSetupWidget()
    {
        tool_button_ = booba::createButton(25, 25, 50, 50, (char *)this);   
    }
};