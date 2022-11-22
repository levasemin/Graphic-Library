#pragma once

#include "Tool.h"
#include "Command.h"
#include "ToolCommand.h"
#include "ToolManager.h"
#include <deque>

uint64_t createButton   (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* object);

class ToolPaint : public Tool
{

public:
    struct point
    {
        float x;
        float y;
    }; 

    std::deque<point> points_;

    ToolPaint() : Tool()
    {
        buildSetupWidget();
    }
    
    point interpolate(float t)
    {
        float x = points_.back().x;
        float y = points_.back().y;

        if (points_.size() == 4)
        {
            float coeff_0 = -t * pow(1.0 - t, 2.0);
            float coeff_1 = (2.0 - 5.0*pow(t, 2) + 3.0*pow(t, 3));
            float coeff_2 = t * (1.0 + 4.0*t - 3.0*pow(t, 2));
            float coeff_3 = pow(t, 2) * (1.0 - t);

            x = 0.5 * (coeff_0 * points_[0].x + coeff_1 * points_[1].x + coeff_2 * points_[2].x - coeff_3 * points_[3].x);
            y = 0.5 * (coeff_0 * points_[0].y + coeff_1 * points_[1].y + coeff_2 * points_[2].y - coeff_3 * points_[3].y);
        }

        return {x, y};
    }

    void apply(booba::Image* image, const booba::Event* event) override
    {    
        switch (event->type)
        {
            case booba::EventType::MouseMoved:
            {
                point new_point = {(float)event->Oleg.motion.x, (float)event->Oleg.motion.y};

                if (points_.size() > 0)
                {
                    if (abs(points_.back().x - new_point.x) > 10 || abs(points_.back().y - new_point.y) > 10)
                    {
                        points_.clear();
                    }
                }

                points_.push_back(new_point);
                
                if (points_.size() > 4)
                {
                    points_.pop_front();
                }

                for (float t = 0; t <= 1.0; t += 0.005)
                {
                    point new_point = interpolate(t);
                    image->putPixel(new_point.x, new_point.y, 0);
                }

                break;
            }

            case booba::EventType::ButtonClicked:
            {
                if (event->Oleg.bcedata.id == tool_button_)
                {
                    std::cout << is_on_ << std::endl;

                    ToolManager &tool_manager = ToolManager::getInstance();
                    
                    if (!is_on_)
                    {
                        tool_manager.set_active_tool(this);
                    }
                    
                    else
                    {
                        tool_manager.remove_active_tool();                        
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