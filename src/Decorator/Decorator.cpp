#include "Decorator.hpp"

namespace SL
{
    Decorator::Decorator (Widget *widget): Widget(),
        widget_(widget)
    {
    }

    Decorator::Decorator(const Decorator &source)
    {
        *widget_ = *source.widget_;
    }
    
    Decorator &Decorator::operator=(const Decorator &source)
    {
        *widget_ = *source.widget_;
    }

    Decorator::Decorator(Decorator &&source)
    {
        widget_ = source.widget_;
    }

    Decorator &Decorator::operator=(Decorator &&source)
    {
        widget_ = source.widget_;
    }

    Decorator::~Decorator()
    {
        delete widget_;
    }

    void Decorator::clickLeftEvent      (const Event &event) 
    {
        widget_->clickLeftEvent(event);
    }
    void Decorator::releaseLeftEvent   (const Event &event) 
    {
        widget_->releaseLeftEvent(event);
    }              

    void Decorator::clickRightEvent (const Event &event) 
    {
        widget_->clickRightEvent(event);
    }
            
    void Decorator::releaseRightEvent (const Event &event) 
    {
        widget_->releaseRightEvent(event);
    }              
    
    void Decorator::moveMouseEvent (const Event &event) 
    {
        widget_->moveMouseEvent(event);
    }

    void Decorator::pressKeyEvent (const Event &event) 
    {
        widget_->pressKeyEvent(event);
    }

    void Decorator::textEvent (const Event &event) 
    {
        widget_->textEvent(event);
    }
    
    void Decorator::scrollEvent (const Event &event) 
    {
        widget_->scrollEvent(event);
    }
    

    bool Decorator::pointBelong(Vector2d point) const 
    {
        return widget_->pointBelong(point);
    }

    void Decorator::draw() 
    {
        widget_->draw();
    }
    
    void Decorator::remove(Widget *window) 
    {
        widget_->remove(window);
    }

    void Decorator::add(Widget *window) 
    {
        widget_->add(window);
    }

    void Decorator::display(Window *window) 
    {
        widget_->display(window);
    }


    Vector2d Decorator::getPosition() const 
    {
        return widget_->getPosition();
    }
    void Decorator::setPosition(Vector2d position) 
    {
        widget_->setPosition(position);
    }

    Vector2d Decorator::getShape() const 
    {
        return widget_->getShape();
    }
    void Decorator::setShape(Vector2d shape) 
    {
        widget_->setShape(shape);
    }

    Widget *Decorator::getParent() const 
    {
        return widget_->getParent();
    }
    void Decorator::setParent(Widget *parent) 
    {
        widget_->setParent(parent);
    }

    Texture Decorator::getTexture() const 
    {
        return widget_->getTexture();
    }
    void Decorator::setTexture(const Texture &texture) 
    {
        return widget_->setTexture(texture);
    }

    RenderTexture *Decorator::getRenderTexture() 
    {
        return widget_->getRenderTexture();   
    }
    void Decorator::setRenderTexture(RenderTexture render_texture) 
    {
        widget_->setRenderTexture(render_texture);
    }
    
    Vector2d Decorator::getGlobalShape() const
    {
        return widget_->getGlobalShape();
    }

    Vector2d Decorator::getVirtualShape() const 
    {
        return widget_->getVirtualShape();
    }

    std::pair<Vector2d, Vector2d> Decorator::getField() const
    {
        return widget_->getField();
    }

    std::vector<Widget *> Decorator::getChildren() const 
    {
        return widget_->getChildren();
    }

    void Decorator::setChildren(std::vector<Widget *> children) 
    {
        widget_->setChildren(children);
    }
}