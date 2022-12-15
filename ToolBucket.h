#pragma once

#include "Tool.h"
#include "Command.h"
#include "ToolCommand.h"
#include "ToolManager.h"
#include "Color.h"
#include "Circle.h"
#include <deque>


class ToolBucket : public Tool
{
public:
    bool clicked_ = false;
    int dispersion_ = 0;
    uint32_t current_color_ = 0;

    ToolBucket() : Tool()
    {                
        char icon_path[128] = "source/Bucket.png";
        std::memcpy(icon_path_, icon_path, 128);
        booba::addTool(this);
    }

    ToolBucket(const ToolBucket &) = default;
    ToolBucket &operator=(const ToolBucket &) = default;

    void set_dispersion(const Event & event)
    {
        dispersion_ = 10;
    }

    void apply(booba::Image* image, const booba::Event* event) override;
    void fill_field(booba::Image *image, Vector2d position);
    void fill_part(booba::Image *image, Vector2d position, Vector2d orientation);
    void fill_ray(booba::Image *image, Vector2d previous_position, Vector2d current_position);



    const char* getTexture() override
    {
        return icon_path_;
    } 

    void buildSetupWidget() override
    {
    }

private:
};

