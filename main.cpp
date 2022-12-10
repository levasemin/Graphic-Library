#include "GraphicLib.h"

#include <iostream>
#include <vector>


const char *path_british = "/home/levce/projectsDED/event_handler2/Event_handler/source/british.jpg";
const char *path_mountain = "/home/levce/projectsDED/event_handler2/Event_handler/source/mountain.jpg";



int main()
{          
    MainWindow main_window(Vector2d(WIDTH, HEIGHT), Texture(Color::Grey));

    TextureManager &texture_manager = TextureManager::getInstance();
    texture_manager.load_textures("Textures");

    Image image(path_mountain);
    ToolPalette tool_palette(Vector2d(300, 300), Vector2d(160, 173), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    Container setting_container(Vector2d(300, 588), Vector2d(160, 700));
    setting_container.set_texture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
    
    Canvas canvas(Vector2d(1400, 970), Vector2d(1020, 508), &tool_palette, &setting_container);

    canvas.set_image(image);
    
    SuperToolPaint super_tool_paint;

    DecoratorScrollBar scroll_bar_canvas(&canvas);
    
    ComboBox file_button(Vector2d(60, 20), Vector2d(30, 10), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    file_button.setString("File");
    file_button.setCharacterSize(16);
    file_button.set_box_texture(Texture(Color::Grey));

    Button save_button(Vector2d(50, 30), Vector2d(25, 15), Texture(Color::Grey));
    save_button.setCharacterSize(16);
    save_button.setString("Save");
    save_button.setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));

    Button open_button(Vector2d(50, 30), Vector2d(25, 45), Texture(Color::Grey));
    open_button.setCharacterSize(16);
    open_button.setString("Open");
    open_button.setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));

    file_button.add(&save_button);
    file_button.add(&open_button);

    MainWindow path_window(Vector2d(300, 200), Texture(Color::Grey));
    Editor path_editor(Vector2d(200, 50), Vector2d(150, 125));
    path_window.add(&path_editor);

        

    main_window.add(&scroll_bar_canvas);    
    main_window.add(&tool_palette);
    main_window.add(&setting_container);
    main_window.add(&file_button);

    Editor edit(Vector2d(100, 20), Vector2d(300, 300));
    
    Application app(&main_window);
    
    app.exec();
}