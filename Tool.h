#include "Widget.h"
#include "tools.h"

class Tool : booba::Tool
{
private:
    
public:
    Tool();
    ~Tool();

    virtual void apply(Image* image, const Event* event) = 0;
    virtual const char* getTexture() = 0; 
    virtual void buildSetupWidget() = 0;
};
