#include "GraphicLib.h"
#include "SaveWindow.h"
#include "OpenWindow.h"
#include "ColorPicker.h"

#include <iostream>
#include <vector>
#include <string>

const std::string path_mountain = "/home/levce/projectsDED/event_handler2/Event_handler/source/british.jpg";

SaveWindow create_save_window()
{
    Button *save_button = new Button(Vector2d(60, 30), Vector2d(70, 215), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    save_button->setString("Save");
    
    Editor *path_editor = new Editor(Vector2d(200, 50), Vector2d(150, 125));
    path_editor->setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));
    path_editor->set_texture(Texture(Color(uint(31), uint8_t(31), uint8_t(31))));
    path_editor->setAlignment(Label::Alignment::LeftCenter);
    
    Button *cancel_button = new Button(Vector2d(60, 30), Vector2d(150, 215), Texture(Color::Grey));
    cancel_button->setString("Cancel");

    SaveWindow save_window(Vector2d(300, 400), save_button, cancel_button, path_editor);

    return save_window;
}

OpenWindow create_open_window()
{
    Button *open_button = new Button(Vector2d(60, 30), Vector2d(70, 215), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    open_button->setString("Open");
    
    Editor *path_editor = new Editor(Vector2d(200, 50), Vector2d(150, 125));
    path_editor->setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));
    path_editor->set_texture(Texture(Color(uint(31), uint8_t(31), uint8_t(31))));
    path_editor->set_texture(Texture(Color(uint(31), uint8_t(31), uint8_t(31))));
    path_editor->setAlignment(Label::Alignment::LeftCenter);

    Button *cancel_button = new Button(Vector2d(60, 30), Vector2d(150, 215), Texture(Color::Grey));
    cancel_button->setString("Cancel");

    OpenWindow open_window(Vector2d(400, 300), open_button, cancel_button, path_editor);

    return open_window;
}

HSVwindow create_hsv_window(const Texture &texture)
{
    HSVpalette *hsv_palette = new HSVpalette(Vector2d(175, 315), Vector2d(120, 200));
    Editor *r_editor        = new Editor(Vector2d(50, 30), Vector2d(270, 35));
    Editor *g_editor        = new Editor(Vector2d(50, 30), Vector2d(270, 75));
    Editor *b_editor        = new Editor(Vector2d(50, 30), Vector2d(270, 115));
    Button *cancel_button   = new Button(Vector2d(50, 20), Vector2d(100, 370), Texture(Color::Grey));
    Button *ok_button       = new Button(Vector2d(50, 20), Vector2d(200, 370), Texture(Color::Grey));
    
    ok_button->setString("OK");
    cancel_button->setString("Cancel");
    
    HSVwindow hsv_window(Vector2d(300, 400), texture, hsv_palette, r_editor, g_editor, b_editor,ok_button, cancel_button);
    return hsv_window;
}

ComboBox create_file_combobox(Canvas *canvas)
{
    ComboBox file_button(Vector2d(60, 20), Vector2d(30, 10), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    file_button.setString("File");
    file_button.setCharacterSize(16);
    file_button.set_box_texture(Texture(Color::Grey));


    Button *file_save_button = new Button(Vector2d(50, 30), Vector2d(25, 15), Texture(Color::Grey));
    file_save_button->setCharacterSize(16);
    file_save_button->setString("Save");
    file_save_button->setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));

    SaveWindow save_window = create_save_window();
    save_window.set_canvas(canvas);
    file_save_button->set_left_click((Command<const Event &> *) new SimpleCommand<SaveWindow, const Event &>(&save_window, &SaveWindow::exec));


    Button *file_open_button = new  Button(Vector2d(50, 30), Vector2d(25, 45), Texture(Color::Grey));
    
    file_open_button->setCharacterSize(16);
    file_open_button->setString("Open");
    file_open_button->setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));

    OpenWindow open_window = create_open_window();
    open_window.set_canvas(canvas);
    file_open_button->set_left_click((Command<const Event &> *) new SimpleCommand<OpenWindow, const Event &>(&open_window, &OpenWindow::exec));


    file_button.add(file_save_button);
    file_button.add(file_open_button);

    return file_button;
}

ColorPicker create_color_picker()
{
    TextureManager &texture_manager = TextureManager::getInstance();

    Button *foreground_button = new Button(Vector2d(50, 50), Vector2d(400, 200), Texture(Color::White));
    Button *background_button = new Button(Vector2d(50, 50), Vector2d(450, 250), Texture(Color::Black));    
    Button *swap_button       = new Button(Vector2d(20, 20), Vector2d(438, 212), Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));    
    swap_button->set_texture(texture_manager[TextureManager::Icon::Swap]);
    booba::APPCONTEXT->fgColor = Color::convert_color_uint(Color::White);
    booba::APPCONTEXT->bgColor = Color::convert_color_uint(Color::Black);

    HSVwindow *hsv_window = new HSVwindow(create_hsv_window(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48))));

    return ColorPicker(foreground_button, background_button, swap_button, hsv_window);
}

booba::ApplicationContext* booba::APPCONTEXT = nullptr;

int main()
{   
    booba::APPCONTEXT = new booba::ApplicationContext();
    booba::APPCONTEXT->fgColor = 0xFF000000;
    booba::APPCONTEXT->bgColor = 0xFF000000;
    
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
    
    ComboBox file_button = create_file_combobox(&canvas);

    ColorPicker color_picker = create_color_picker();

    main_window.add(&scroll_bar_canvas);    
    main_window.add(&tool_palette);
    main_window.add(&setting_container);
    main_window.add(&file_button);
    main_window.add(&color_picker);
    main_window.add(color_picker.background_button_);
    main_window.add(color_picker.foreground_button_);
    main_window.add(color_picker.swap_button_);
    Application app(&main_window);
    
    app.exec();
}