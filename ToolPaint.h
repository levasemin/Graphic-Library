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
        hsv_palette_(Vector2d(200, 360), Vector2d(120, 240)),
        r_editor_(Vector2d(50, 30), Vector2d(270, 75)),
        g_editor_(Vector2d(50, 30), Vector2d(270, 115)),
        b_editor_(Vector2d(50, 30), Vector2d(270, 155)),
        hsv_window_(&hsv_palette_, &r_editor_, &g_editor_, &b_editor_),
        points_({}),
        drawing_object_(1.f)
    {
        r_editor_.set_color_text(Color(uint8_t(190), uint8_t(190), uint8_t(190)));
        g_editor_.set_color_text(Color(uint8_t(190), uint8_t(190), uint8_t(190)));
        b_editor_.set_color_text(Color(uint8_t(190), uint8_t(190), uint8_t(190)));

        r_editor_.set_texture(Color(uint8_t(31), uint8_t(31), uint8_t(31)));
        g_editor_.set_texture(Color(uint8_t(31), uint8_t(31), uint8_t(31)));
        b_editor_.set_texture(Color(uint8_t(31), uint8_t(31), uint8_t(31)));

        hsv_window_.set_command(             (Command<const Color &> *) new SimpleCommand<SuperToolPaint, const Color &>(this, &SuperToolPaint::set_color));
        width_scroll_bar_.set_scroll_command((Command<const Event &> *) new SimpleCommand<SuperToolPaint, const Event &>(this, &SuperToolPaint::set_width));
                
        char icon_path[128] = "source/Brush.png";
        std::memcpy(icon_path_, icon_path, 128);
        booba::addTool(this);
        
        buildSetupWidget();
    }

    SuperToolPaint(const SuperToolPaint &) = default;
    SuperToolPaint &operator=(const SuperToolPaint &) = default;

    void set_color(const Color &color)
    {
        drawing_object_.set_color(color);
    }

    void set_width(const Event & event)
    {
        drawing_object_.set_radius(int(event.Oleg_.smedata.value * 30.f));
    }

    void paint(booba::Image *image)
    {
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
            case booba::EventType::CanvasMPressed:
            {
                clicked_ = true;

                Vector2d new_point((float)event->Oleg.cedata.x, (float)event->Oleg.cedata.y);

                points_.push_back(new_point);
                paint(image);
                points_.pop_back();

                break;
            }

            case booba::EventType::CanvasMReleased:
            {
                clicked_ = false;
                break;
            }

            case booba::EventType::CanvasMMoved:
            {
                if (clicked_)
                {
                    Vector2d new_point((float)event->Oleg.cedata.x, (float)event->Oleg.cedata.y);

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
            case booba::EventType::MouseMoved:
            {
                clicked_ = false;
                break;
            }
            case booba::EventType::MousePressed:
            case booba::EventType::MouseReleased:
            {
                clicked_ = false;
                break;
            }
            
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
        tool_manager.setting_palettes_.back()->add(&hsv_palette_);
        tool_manager.setting_palettes_.back()->add(&r_editor_);
        tool_manager.setting_palettes_.back()->add(&g_editor_);
        tool_manager.setting_palettes_.back()->add(&b_editor_);
    }

private:
    HorizontalScrollBar width_scroll_bar_;

    HSVpalette hsv_palette_;
    Editor r_editor_;
    Editor g_editor_;
    Editor b_editor_;

    HSVwindow hsv_window_;

    std::deque<Vector2d> points_;

    Circle drawing_object_;
};