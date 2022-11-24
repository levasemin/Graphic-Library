#include "Image.h"
#include "Widget.h"
#include "Object.h"

class Surface : public Image, public Object 
{
public:

    Surface(Vector2d shape, Vector2d center, const Image &image) : Image(image), Object(shape, center, image.getTexture())
    {}

    void draw() override
    {   
        sprite_.setPosition(Vector2d(0, 0));
        sprite_.setTexture(getTexture());
        render_texture_->clear();
        render_texture_->draw(sprite_);

        Object::draw();
    }
};