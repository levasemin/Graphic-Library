#include "RenderTexture.h"
#include "CompositeObject.h"
#include <vector>
#include "Surface.h"

class Canvas : public CompositeObject
{
    Canvas(Vector2d shape, Vector2d center, Texture texture, Widget *parent = nullptr, std::vector<Widget *> children = {}) : 
        CompositeObject(shape, center, texture, parent, children)
    {   
    }

    void set_context(Surface *new_context)
    {
        remove(new_context);
        add(new_context);
    }

    
};