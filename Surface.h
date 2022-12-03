#include "Image.h"
#include "Widget.h"
#include "Object.h"

class Surface : public Image, public Object 
{
public:

    Surface(Vector2d shape, Vector2d center, const Image &image = Image()) : Image(image), Object(shape, center, image.getTexture())
    {}

    void draw() override
    {   
        Sprite sprite(shape_, getTexture());
        render_texture_->clear();
        render_texture_->draw(sprite);

        Object::draw();
    }
};