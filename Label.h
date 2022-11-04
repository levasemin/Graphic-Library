#include "Texture.h"
#include "Text.h"
#include "Sprite.h"
#include "Vector2d.h"
#include "Widget.h"
#include <string>

class Label: public Widget
{

public:
    RenderTexture label_texture_;
    Text text_;

    Label(Vector2d shape, Vector2d center, Texture texture = Texture(Colors::White), Text text = Text()): Widget(shape, center, texture),
        label_texture_(shape),
        text_(text)
    {};

    void set_text(Text text)
    {
        text_ = text;
        create();        
    }

    void set_texture(Texture texture)
    {
        sprite_.setTexture(texture);
        create();
    }

    void create()
    {
        label_texture_.draw(sprite_);
        label_texture_.draw(text_);
        label_texture_.display();
    }

    Texture get_texture()
    {
        return label_texture_.getTexture();
    }
};