#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "RenderTexture.h"
#include "CompositeObject.h"
#include <vector>
#include "Surface.h"
#include "ToolManager.h"
#include "ToolPalette.h"
#include "Vector2d.h"
#include <filesystem>
#include <dlfcn.h>

class Canvas : public CompositeObject
{
public:
    Surface surface_;

    ToolManager &tool_manager_;

    bool is_left_clicked_ = false;

    Canvas(Vector2d shape, Vector2d center, const Image &image = Image(), ToolPalette *tool_palette = nullptr, Container * setting_palette = nullptr) : 
        CompositeObject(shape, center, Color::Cyan),
        surface_(image.getSize(), image.getSize() / 2, image),
        tool_manager_(ToolManager::getInstance())
    {   
        add(&surface_);
        
        tool_manager_.set_suface(&surface_);

        if (tool_palette)
        {
            tool_manager_.set_tool_palette(tool_palette);
        }
        if (setting_palette)
        {
            tool_manager_.set_setting_field(setting_palette);
        }
               
        std::string dlPath = "./Plugins";
        
        for (const auto& curFile : std::filesystem::directory_iterator(dlPath)) {
            if (curFile.is_directory()) {
                continue;
            }

            void* dlHandler = dlopen(curFile.path().c_str(), RTLD_LAZY);
            
            if (dlHandler) {
                void (*initFunc)()   = nullptr; 
                *((void**)&initFunc) = dlsym(dlHandler, "init_module");

                (*initFunc)();
            }
            else {
                fprintf(stderr, "Unable to open lib: %s\n", dlerror());
            }
        }
    }
    
    Canvas (const Canvas &source): CompositeObject(*(const CompositeObject *)&source),
        surface_(source.surface_),
        tool_manager_(source.tool_manager_)
    {} 

    Canvas &operator= (const Canvas &source)
    { 
        CompositeObject::operator=(*(const CompositeObject *)&source);
        surface_         = source.surface_;
        
        return *this;
    }

    void MoveMouseEvent (const Event &event) override
    {
        Event new_event = event;

        if (point_belonging(event.Oleg_.motion.pos))
        {
            new_event.type_ = EventType::CanvasMMoved;
        }
        
        new_event.Oleg_.motion.pos -= surface_.get_global_offset() + (surface_.get_center() - surface_.get_shape() / 2);

        tool_manager_.apply(&surface_, &new_event);
    }

    void ClickLeftEvent(const Event &event) override
    {
        Event new_event = event;

        if (point_belonging(event.Oleg_.mbedata.pos))
        {
            new_event.type_ = EventType::CanvasMPressed;
        }

        new_event.Oleg_.motion.pos -= surface_.get_global_offset() + (surface_.get_center() - surface_.get_shape() / 2);

        tool_manager_.apply(&surface_, &new_event);

        is_left_clicked_ = true;
        
    }

    void ReleasedLeftEvent (const Event &event) override
    {
        Event new_event = event;

        if (point_belonging(event.Oleg_.mbedata.pos))
        {
            new_event.type_ = EventType::CanvasMReleased;
        }
        
        new_event.Oleg_.motion.pos -= surface_.get_global_offset() + (surface_.get_center() - surface_.get_shape() / 2);

        tool_manager_.apply(&surface_, &new_event);   
        

        is_left_clicked_ = false;
    }

    void PressKeyEvent(const Event &event) override
    {
        if (event.Oleg_.kpedata.ctrl)
        {
            if (event.Oleg_.kpedata.code == Key::Z)
            {
                if (event.Oleg_.kpedata.shift)
                {
                    printf("Ctrl SHift Z\n");
                    tool_manager_.redo(&surface_);
                }

                else
                {
                    printf("Ctrl Z\n");
                    tool_manager_.undo(&surface_);
                }
            }
        }
    }

    void set_image(Image *new_image)
    {
        surface_ = Surface(new_image->getSize(), new_image->getSize() / 2, *new_image);
    }

    void add_tool(Tool *new_tool)
    {
        tool_manager_.add(new_tool);
    }    
};