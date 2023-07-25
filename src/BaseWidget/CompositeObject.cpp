#include "CompositeObject.hpp"

namespace SL
{
    CompositeObject::CompositeObject(Vector2d shape, Vector2d position, const Texture &texture): Object(shape, position, texture),
        children_({})
        {}

    void CompositeObject::clickLeftEvent (const Event &event) 
    {   
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->clickLeftEvent(event);
        }
    }

    void CompositeObject::releaseLeftEvent (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->releaseLeftEvent(event);
        }
    }             
    
    void CompositeObject::clickRightEvent (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->clickRightEvent(event);
        }
    }

    void CompositeObject::releaseRightEvent (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->releaseLeftEvent(event);
        }
    }            
    
    void CompositeObject::moveMouseEvent      (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->moveMouseEvent(event);
        }
    }

    void CompositeObject::pressKeyEvent       (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->pressKeyEvent(event);
        }
    }

    void CompositeObject::textEvent           (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->textEvent(event);
        }
    }

    void CompositeObject::scrollEvent         (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->scrollEvent(event);
        }
    }  

    void CompositeObject::draw() 
    {
        getRenderTexture()->clear();
        
        sprite_.setTexture(texture_);
        sprite_.setPosition(Vector2d(0, 0));
        getRenderTexture()->draw(sprite_);
        
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->draw();
        }

        Object::draw();
    }

    void CompositeObject::remove(Widget *child) 
    {
        child->setParent(nullptr);

        for (size_t i = 0; i < children_.size(); i++)
        {
            if (child == children_[i])
            {
                children_.erase(children_.begin() + i);
            }
        }
    }

    void CompositeObject::add(Widget *child) 
    {
        if (child->getParent() == this)
        {
            return;
        }

        child->setParent(this);

        children_.push_back(child);
    }
    
    std::vector<Widget *> CompositeObject::getChildren() const         
    {
        return children_; 
    }
    
    void CompositeObject::setChildren(std::vector<Widget *> children)  
    { 
        children_ = children; 
    }
}