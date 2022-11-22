#include "CompositeObject.h"
#include "Button.h"
#include "Container.h"

class MenuBar : public CompositeObject
{
public:

    MenuBar(Vector2d shape, Vector2d center, Texture texture = Texture(Colors::White), Widget *parent = nullptr, std::vector<Widget *> children = {}) : 
        CompositeObject(shape, center, texture, parent, children)
        {

        }
};
