#include "Image.h"
#include "Event.h"
class ToolPaint
{

public:
    ToolPaint();
    
    void apply(Image* image, const Event* event) override
    {
        printf("WHOOO\n");
    }

    const char* getTexture() override
    {

    } 

    void buildSetupWidget() override
    {

    }

    ~ToolPaint();
};
