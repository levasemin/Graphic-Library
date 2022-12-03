#pragma once

#include "Tool.h"
#include "Command.h"
#include "ToolCommand.h"
#include "ToolManager.h"
#include "HorizontalScrollBar.h"
#include <deque>

class ToolEraser : public Tool
{

public:
    struct point
    {
        float x;
        float y;
    }; 

    std::deque<point> points_;

    HorizontalScrollBar width_scroll_bar_;
    Container settings_container_;

    uint32_t *default_image_ = nullptr;

    ToolEraser() : Tool(),
        points_({}),
        width_scroll_bar_(Vector2d(100, 30), Vector2d(150, 40)),
        settings_container_(Vector2d(300, 400), Vector2d(150, 200))
    {
        char icon_path[128] = "source/eraser.png";
        settings_container_.add(&width_scroll_bar_);
        std::memcpy(icon_path_, icon_path, 128);
        buildSetupWidget();
    }
    
    ToolEraser(const ToolEraser &source) : Tool(*(const Tool *)&source),
        points_(source.points_),
        width_scroll_bar_(source.width_scroll_bar_),
        settings_container_(source.settings_container_),
        default_image_(source.default_image_)
    {}

    ToolEraser &operator=(const ToolEraser &source)
    {
        Tool::operator=(*(const Tool *)&source);
        points_             = source.points_;
        width_scroll_bar_   = source.width_scroll_bar_;
        settings_container_ = source.settings_container_;
        default_image_      = source.default_image_;

        return *this;
    }

    void paint(booba::Image *image)
    {
        float x = points_.back().x;
        float y = points_.back().y;

        if (points_.size() == 4)
        {
            for (float t = 0; t <= 1.f; t += 0.001f)
            {
                float coeff_0 = -t * pow(1.f - t, 2.f);
                float coeff_1 = (2.f - 5.f*pow(t, 2.f) + 3.f*pow(t, 3.f));
                float coeff_2 = t * (1.f + 4.f*t - 3.f*pow(t, 2.f));
                float coeff_3 = pow(t, 2.f) * (1.f - t);

                x = 0.5f * (coeff_0 * points_[0].x + coeff_1 * points_[1].x + coeff_2 * points_[2].x - coeff_3 * points_[3].x);
                y = 0.5f * (coeff_0 * points_[0].y + coeff_1 * points_[1].y + coeff_2 * points_[2].y - coeff_3 * points_[3].y);
                
                image->putPixel((int)x, (int)y, default_image_[(int)y * image->getX() + (int)x]);
            }
        }
    }

    void create_default_image(booba::Image *image)
    {
        printf("reserve window was created\n");
        default_image_ = new uint32_t[image->getH() * image->getX()];
        
        for (size_t y = 0; y < image->getH(); y++)
        {
            for (size_t x = 0; x < image->getX(); x++)
            {
                default_image_[y * image->getX() + x] = image->getPixel((int)x, (int)y);
            }
        }
    }

    void apply(booba::Image* image, const booba::Event* event) override
    {    
        if (image == nullptr && event == nullptr)
        {
            settings_container_.set_shape(Vector2d(0, 0));

            return;
        }

        switch (event->type)
        {
            case booba::EventType::CanvasMMoved:
            {
                if (!default_image_)
                {
                    create_default_image(image);
                }   

                point new_point = {(float)event->Oleg.motion.x, (float)event->Oleg.motion.y};

                if (points_.size() > 0)
                {
                    if (abs(points_.back().x - new_point.x) > float(image->getX()) / 100.f + 1.f || abs(points_.back().y - new_point.y) > float(image->getH()) / 10.f + 1.f)
                    {
                        points_.clear();
                    }
                }

                points_.push_back(new_point);
                
                if (points_.size() > 4)
                {
                    points_.pop_front();
                }

                paint(image);

                break;
            }

            case booba::EventType::ButtonClicked:
            {
                if (event->Oleg.bcedata.id == tool_button_)
                {
                    settings_container_.set_shape(Vector2d(300, 400));
                    
                    std::cout << "Eraser " << is_on_ << std::endl;

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
            
            case booba::EventType::NoEvent:
            case booba::EventType::MouseMoved:
            case booba::EventType::MousePressed:
            case booba::EventType::MouseReleased:
            case booba::EventType::ScrollbarMoved:
            case booba::EventType::CanvasMPressed:
            case booba::EventType::CanvasMReleased:
            
            default:
            {
                break;
            }
        }
    }

    const char* getTexture() override
    {
        return icon_path_;
    } 

    void buildSetupWidget() override
    {
        tool_button_ = booba::createButton(25, 25, 50, 50, (char *)this);   
    }
};