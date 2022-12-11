#include "GraphicLib.h"
#include "SaveButton.h"
#include "CanvasButton.h"
#include "CancleButton.h"

#include <iostream>
#include <vector>
#include <string>

const std::string path_mountain = "/home/levce/projectsDED/event_handler2/Event_handler/source/mountain.jpg";


void create_open_window(const Event &, Canvas *canvas)
{
    MainWindow open_window(Vector2d(400, 300), Texture(Color::Grey));
    Application dialog_window(&open_window);
    
    SaveButton open_button(Vector2d(60, 30), Vector2d(70, 215), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    open_button.set_left_click((Command<std::string> *) new SimpleCommand<Canvas, const std::string &>(canvas, &Canvas::set_image));
    open_button.setString("Open");

    Editor path_editor(Vector2d(200, 50), Vector2d(150, 125));
    path_editor.set_editor_command((Command<std::string> *) new SimpleCommand<SaveButton, std::string>(&open_button, &SaveButton::set_file_path));

    CancleButton cancle_button(Vector2d(60, 30), Vector2d(150, 215), Texture(Color::Grey));
    cancle_button.set_left_click((Command<> *) new SimpleCommand<Application>(&dialog_window, &Application::close));
    cancle_button.setString("Cancle");

    open_window.add(&path_editor);
    open_window.add(&open_button);
    open_window.add(&cancle_button);
    
    dialog_window.exec();
}


void create_save_window(const Event &, Canvas *canvas)
{
    MainWindow save_window(Vector2d(400, 300), Texture(Color::Grey));
    Application dialog_window(&save_window);
    
    SaveButton save_button(Vector2d(60, 30), Vector2d(70, 215), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    save_button.set_left_click((Command<std::string> *) new SimpleCommand<Image, const std::string &>(canvas->get_image(), &Image::saveToFile));
    save_button.setString("Save");

    Editor path_editor(Vector2d(200, 50), Vector2d(150, 125));
    path_editor.set_editor_command((Command<std::string> *) new SimpleCommand<SaveButton, std::string>(&save_button, &SaveButton::set_file_path));

    CancleButton cancle_button(Vector2d(60, 30), Vector2d(150, 215), Texture(Color::Grey));
    cancle_button.set_left_click((Command<> *) new SimpleCommand<Application>(&dialog_window, &Application::close));
    cancle_button.setString("Cancle");

    save_window.add(&path_editor);
    save_window.add(&save_button);
    save_window.add(&cancle_button);
    
    dialog_window.exec();
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

    CanvasButton save_button(Vector2d(50, 30), Vector2d(25, 15), Texture(Color::Grey));
    save_button.setCharacterSize(16);
    save_button.setString("Save");
    save_button.setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));
    save_button.set_canvas(&canvas);
    save_button.set_left_click((Command<const Event &, Canvas *> *) new FunctorCommand<const Event &, Canvas *>(&create_save_window));


    CanvasButton open_button(Vector2d(50, 30), Vector2d(25, 45), Texture(Color::Grey));
    open_button.setCharacterSize(16);
    open_button.setString("Open");
    open_button.setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));
    open_button.set_canvas(&canvas);
    open_button.set_left_click((Command<const Event &, Canvas *> *) new FunctorCommand<const Event &, Canvas *>(&create_open_window));

    file_button.add(&save_button);
    file_button.add(&open_button);

    
    

    main_window.add(&scroll_bar_canvas);    
    main_window.add(&tool_palette);
    main_window.add(&setting_container);
    main_window.add(&file_button);

    Editor edit(Vector2d(100, 20), Vector2d(300, 300));
    
    Application app(&main_window);
    
    app.exec();
}