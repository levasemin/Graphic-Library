#pragma once

#include "Tool.h"
#include "Command.h"
#include "ToolCommand.h"
#include "ToolManager.h"
#include "Color.h"
#include "Circle.h"
#include "HorizontalScrollBar.h"
#include "HSVwindow.h"
#include "Interpolator.h"
#include <deque>


class SuperToolPaint : public Tool
{
public:
    Interpolator interpolator_;

    bool clicked_ = false;

    SuperToolPaint() : Tool(),
        interpolator_(Interpolator::CATMULL_ROM),
        width_scroll_bar_(Vector2d(200, 20), Vector2d(150, 30)),
        points_({}),
        drawing_object_(1.f)
    {
        width_scroll_bar_.set_scroll_command((Command<const Event &> *) new SimpleCommand<SuperToolPaint, const Event &>(this, &SuperToolPaint::set_width));
                
        char icon_path[128] = "source/Brush.png";
        std::memcpy(icon_path_, icon_path, 128);
        booba::addTool(this);
        
        buildSetupWidget();
    }

    SuperToolPaint(const SuperToolPaint &) = default;
    SuperToolPaint &operator=(const SuperToolPaint &) = default;

    void set_width(const Event & event)
    {
        drawing_object_.set_radius(int(event.Oleg_.smedata.value * 30.f));
    }

    void paint(booba::Image *image)
    {
        drawing_object_.set_color(Color::convert_uint_color(booba::APPCONTEXT->fgColor));
        drawing_object_.draw_on_image(image, points_.back());

        if (points_.size() == 4)
        {
            for (float t = 0; t <= 1.f; t += 0.1f)
            {
                Vector2d new_point = interpolator_(t, points_[0], points_[1], points_[2], points_[3]);
                
                drawing_object_.draw_on_image(image, new_point);
            }
        }
    }

    void apply(booba::Image* image, const booba::Event* event) override
    {    
        if (image == nullptr && event == nullptr)
        {
            return;
        }

        switch (event->type)
        {
            case booba::EventType::MousePressed:
            {
                clicked_ = true;

                Vector2d new_point((float)event->Oleg.mbedata.x, (float)event->Oleg.mbedata.y);

                points_.push_back(new_point);
                paint(image);
                points_.pop_back();

                break;
            }

            case booba::EventType::MouseReleased:
            {
                clicked_ = false;
                break;
            }

            case booba::EventType::MouseMoved:
            {
                if (clicked_)
                {
                    Vector2d new_point((float)event->Oleg.mbedata.x, (float)event->Oleg.mbedata.y);

                    if (points_.size() > 0)
                    {
                        if (abs(points_.back().x_ - new_point.x_) > float(image->getX()) / 100.f + 1.f || abs(points_.back().y_ - new_point.y_) > float(image->getH()) / 10.f + 1.f)
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
                }
                
                break;
            }

            case booba::EventType::ButtonClicked:
            case booba::EventType::ScrollbarMoved:
            case booba::EventType::NoEvent:
            case booba::EventType::CanvasMMoved:
            case booba::EventType::CanvasMPressed:
            case booba::EventType::CanvasMReleased:
            
            default:
                break;
        }
    }

    const char* getTexture() override
    {
        return icon_path_;
    } 

    void buildSetupWidget() override
    {
        ToolManager &tool_manager = ToolManager::getInstance();

        tool_manager.setting_palettes_.back()->add(&width_scroll_bar_);
    }

private:
    HorizontalScrollBar width_scroll_bar_;

    std::deque<Vector2d> points_;

    Circle drawing_object_;
};