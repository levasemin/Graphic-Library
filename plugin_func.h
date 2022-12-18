// #pragma once

// #include "ToolManager.h"
// #include "ToolButton.h"
// #include "Label.h"
// #include "HorizontalScrollBar.h"
// #include "Canvas.h"

// #include "stdint.h"
// #include "tools.h"

// uint64_t booba::createButton   (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* text)
// {   
//     Tool *tool = (Tool *)setup_tool_;

//     ToolButton *tool_button = new ToolButton(Vector2d((float)w, (float)h), Vector2d((float)x, (float)y), Texture(tool->getTexture()));

//     tool_button->set_left_click((Command<const Event &> *) new ToolCommand<Tool>(tool, &Tool::apply));

//     ToolManager &tool_manager = ToolManager::getInstance();
//     tool_manager.tool_palette_->add(tool_button);

//     return (int64_t)tool_button;
// }

// uint64_t createLabel    (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* text)
// {
//     Label *label = new Label(Vector2d(float(w), float(h)), Vector2d(float(x), float(y)));
//     label->setString(text);

//     ToolManager &tool_manager = ToolManager::getInstance();
//     tool_manager.tool_palette_->add(label);

//     return (int64_t)label;    
// }   

// uint64_t createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h)
// {
//     HorizontalScrollBar *scroll_bar = new HorizontalScrollBar(Vector2d(float(w), float(h)), Vector2d(float(x), float(y)));

//     ToolManager &tool_manager = ToolManager::getInstance();
//     tool_manager.tool_palette_->add(scroll_bar);

//     return (int64_t)scroll_bar;     
// }

// uint64_t createCanvas(int32_t x, int32_t y, int32_t w, int32_t h)
// {
//     Canvas *canvas = new Canvas(Vector2d(float(w), float(h)), Vector2d(float(x), float(y)));

//     return (int64_t)canvas;
// }

// uint64_t setPixel (uint64_t canvas, int32_t x, int32_t y, uint32_t color)
// {
//     if (canvas)
//     {
//         Canvas *my_canvas = (Canvas *)canvas;
//         my_canvas->surface_.setPixel(x, y, color);
//     }

//     return canvas;
// }

// uint64_t putSprite(uint64_t canvas, int32_t x, int32_t y, uint32_t w, uint32_t h, const char* texture)
// {
//     // if (canvas)
//     // {
//     //     Canvas *my_canvas = (Canvas *)canvas;
//     //     my_canvas->surface_.   
//     // }
    
//     return canvas;
// }

// void addTool(booba::Tool* tool)
// {
//     ToolManager &tool_manager = ToolManager::getInstance();
//     tool_manager.add(tool);  
// }

// void addFilter(booba::Tool* tool)
// {

// }