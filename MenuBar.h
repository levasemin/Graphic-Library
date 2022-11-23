#include "CompositeObject.h"
#include "Button.h"
#include "Container.h"
#include "ComboBox.h"

class MenuBar : public CompositeObject
{
public:

    MenuBar(Vector2d shape, Vector2d center, Texture texture = Texture(Colors::White)) : 
        CompositeObject(shape, center, texture)
        {

        }

    void add(Widget *) override
    {
        
    }
};
