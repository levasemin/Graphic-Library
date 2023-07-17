#include "CompositeObject.hpp"

namespace SL
{
    CompositeObject::CompositeObject(Vector2d shape, Vector2d position, const Texture &texture): Object(shape, position, texture),
        global_shape_(0, 0),
        children_({}),
        indent_(0, 0)
        {
        }

    CompositeObject::CompositeObject::CompositeObject(const CompositeObject &source) : Object(*(const Object *)&source),
        global_shape_(source.global_shape_),
        children_(source.children_),
        indent_(source.indent_)
        {}

    CompositeObject &CompositeObject::operator=(const CompositeObject &source)
    {
        Object::operator=(*(const Object *)&source);
        global_shape_ = source.global_shape_;
        children_ = source.children_;
        indent_ = source.indent_;
        return *this;
    }

    void CompositeObject::clickLeftEvent      (const Event &event) 
    {   
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->clickLeftEvent(event);
        }
    }

    void CompositeObject::releaseLeftEvent   (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->releaseLeftEvent(event);
        }
    }             
    
    void CompositeObject::clickRightEvent     (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->clickRightEvent(event);
        }
    }

    void CompositeObject::releaseRightEvent  (const Event &event) 
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
    
    void CompositeObject::textEvent           (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->textEvent(event);
        }
    }

    void CompositeObject::pressKeyEvent       (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->pressKeyEvent(event);
        }
    }
    
    void CompositeObject::scrollEvent         (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->scrollEvent(event);
        }
    }  

    void CompositeObject::setGlobalOffset(Vector2d offset) 
    {
        Object::setGlobalOffset(offset);

        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->setGlobalOffset(offset + position_ + local_offset_);
        }
    }

    void CompositeObject::draw() 
    {
        render_texture_.clear();
        
        sprite_.setTexture(texture_);
        sprite_.setPosition(Vector2d(0, 0));
        render_texture_.draw(sprite_);
        
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

        child->setGlobalOffset(Vector2d(0, 0));
    }

    void CompositeObject::add(Widget *child) 
    {
        if (child->getParent() == this)
        {
            return;
        }

        child->setParent(this);
        child->setGlobalOffset(global_offset_ + position_ + local_offset_);

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

    Vector2d CompositeObject::getGlobalShape() const             
    {
        Vector2d global_end_field  (INT32_MIN, INT32_MIN);
        Vector2d global_start_field(0, 0);
        Vector2d global_shape_     (0, 0);

        for (size_t i = 0; i < children_.size(); i++)
        {
            global_start_field.x_ = children_[i]->getPosition().x_ < global_start_field.x_ ? 
                                    children_[i]->getPosition().x_ : global_start_field.x_;
        
            global_start_field.y_ = children_[i]->getPosition().y_ < global_start_field.y_ ? 
                                    children_[i]->getPosition().y_ : global_start_field.y_;

            global_end_field.x_   = children_[i]->getPosition().x_ +  children_[i]->getShape().x_ > global_end_field.x_ ? 
                                    children_[i]->getPosition().x_ +  children_[i]->getShape().x_ : global_end_field.x_;
        
            global_end_field.y_   = children_[i]->getPosition().y_ + children_[i]->getShape().y_ > global_end_field.y_ ? 
                                    children_[i]->getPosition().y_ + children_[i]->getShape().y_ : global_end_field.y_;

            global_shape_ = global_end_field - global_start_field;
        }

        global_shape_.x_ = global_shape_.x_ > shape_.x_ ? global_shape_.x_ : shape_.x_;
        global_shape_.y_ = global_shape_.y_ > shape_.y_ ? global_shape_.y_ : shape_.y_;

        return global_shape_; 
    }

    Vector2d CompositeObject::getLocalOffset() const 
    {
        return local_offset_; 
    }

    void CompositeObject::setLocalOffset(Vector2d offset) 
    { 
        std::vector <Widget *> children = getChildren();

        for (size_t i = 0; i < children.size(); i++)
        {
            children[i]->setGlobalOffset(children[i]->getGlobalOffset() + (offset - local_offset_) * children[i]->getHasLocalOffset());
        }

        local_offset_ = offset; 
    }
}