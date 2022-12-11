#include "GraphicLib.h"
#include "SaveWindow.h"
#include "OpenWindow.h"

#include <iostream>
#include <vector>
#include <string>

const std::string path_mountain = "/home/levce/projectsDED/event_handler2/Event_handler/source/mountain.jpg";

SaveWindow create_save_window()
{
    Button *save_button = new Button(Vector2d(60, 30), Vector2d(70, 215), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    save_button->setString("Save");
    
    Editor *path_editor = new Editor(Vector2d(200, 50), Vector2d(150, 125));
    path_editor->setAlignment(Label::Alignment::LeftCenter);
    Button *cancel_button = new Button(Vector2d(60, 30), Vector2d(150, 215), Texture(Color::Grey));
    cancel_button->setString("Cancel");

    SaveWindow save_window(Vector2d(400, 300), save_button, cancel_button, path_editor);

    return save_window;
}

OpenWindow create_open_window()
{
    Button *open_button = new Button(Vector2d(60, 30), Vector2d(70, 215), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    open_button->setString("Open");
    
    Editor *path_editor = new Editor(Vector2d(200, 50), Vector2d(150, 125));
    path_editor->setAlignment(Label::Alignment::LeftCenter);

    Button *cancel_button = new Button(Vector2d(60, 30), Vector2d(150, 215), Texture(Color::Grey));
    cancel_button->setString("Cancel");

    OpenWindow open_window(Vector2d(400, 300), open_button, cancel_button, path_editor);

    return open_window;
}

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


    Button file_save_button(Vector2d(50, 30), Vector2d(25, 15), Texture(Color::Grey));

    file_save_button.setCharacterSize(16);
    file_save_button.setString("Save");
    file_save_button.setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));

    SaveWindow save_window = create_save_window();
    save_window.set_canvas(&canvas);
    file_save_button.set_left_click((Command<const Event &> *) new SimpleCommand<SaveWindow, const Event &>(&save_window, &SaveWindow::exec));


    Button file_open_button(Vector2d(50, 30), Vector2d(25, 45), Texture(Color::Grey));
    
    file_open_button.setCharacterSize(16);
    file_open_button.setString("Open");
    file_open_button.setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));

    OpenWindow open_window = create_open_window();
    open_window.set_canvas(&canvas);
    file_open_button.set_left_click((Command<const Event &> *) new SimpleCommand<OpenWindow, const Event &>(&open_window, &OpenWindow::exec));


    file_button.add(&file_save_button);
    file_button.add(&file_open_button);

    main_window.add(&scroll_bar_canvas);    
    main_window.add(&tool_palette);
    main_window.add(&setting_container);
    main_window.add(&file_button);

    Editor edit(Vector2d(100, 20), Vector2d(300, 300));
    
    Application app(&main_window);
    
    app.exec();
}