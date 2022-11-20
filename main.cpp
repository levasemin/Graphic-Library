#include "GraphicLib.h"

#include <iostream>
#include <vector>


const char *path_british = "/home/levce/projectsDED/event_handler2/Event_handler/source/british.jpg";

int main()
{          
    MainWindow main_window(Vector2d(WIDTH, HEIGHT), Texture(Colors::Yellow));
                
    Image image(path_british);
    ToolPalette tool_palette(Vector2d(100, 300), Vector2d(600, 200), Texture(Colors::Magenta));
    Canvas canvas(Vector2d(500, 500), Vector2d(300, 300), image, &tool_palette);
    ToolPaint toolpaint;
    toolpaint.buildSetupWidget();
    
    canvas.add_tool(&toolpaint);
    DecoratorScroll scroll_canvas(&canvas);

    main_window.add(&scroll_canvas);    
    main_window.add(&tool_palette);
    Application app(&main_window);

    app.exec();
}