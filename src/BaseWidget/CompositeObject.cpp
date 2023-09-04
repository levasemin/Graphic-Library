#include "CompositeObject.hpp"
#include "Application.hpp"

namespace SL
{
    CompositeObject::CompositeObject(Vector2d shape, Vector2d position, const Texture &texture): Object(shape, position, texture),
        children_({})
        {
            sprite_.setTexture(texture);

            render_texture_.draw(sprite_);
        }

    void CompositeObject::pressEvent (const Event &event) 
    {   
        for (auto child : children_)
        {
            child->pressEvent(event);
        }
    }

    void CompositeObject::releaseEvent (const Event &event) 
    {
        for (auto child : children_)
        {
            child->releaseEvent(event);
        }
    }                         
    
    void CompositeObject::moveMouseEvent      (const Event &event) 
    {
        for (auto child : children_)
        {
            child->moveMouseEvent(event);
        }
    }

    void CompositeObject::pressKeyEvent       (const Event &event) 
    {
        for (auto child : children_)
        {
            child->pressKeyEvent(event);
        }
    }

    void CompositeObject::textEvent           (const Event &event) 
    {
        for (auto child : children_)
        {
            child->textEvent(event);
        }
    }

    void CompositeObject::resizedEvent        (const Event &event)
    {
        Object::resizedEvent(event);

        for (auto child : children_)
        {
            child->resizedEvent(event);
        }
    }

    void CompositeObject::scrollEvent         (const Event &event) 
    {
        for (auto child : children_)
        {
            child->scrollEvent(event);
        }
    }  

    void CompositeObject::draw() 
    {
        getRenderTexture()->clear();
        
        render_texture_.setSize(shape_);
                                         
        sprite_.setShape(shape_);
        
        sprite_.setTexture(texture_);
        sprite_.setPosition(Vector2d(0, 0));

        getRenderTexture()->draw(sprite_);
        
        for (auto child : children_)
        {
            child->draw();
        }

        render_texture_.display();
        sprite_.setTexture(render_texture_.getTexture());
        
        if (parent_)
        {
            sprite_.setPosition(position_);
            parent_->getRenderTexture()->draw(sprite_);
        }
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
}