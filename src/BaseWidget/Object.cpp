#include "Object.hpp"

namespace SL
{
    Object::Object(Vector2d shape, Vector2d position, const Texture &texture): Widget(),
            shape_(shape),
            position_(position),    
            texture_(texture),
            sprite_(shape, texture, 0),
            render_texture_(shape)
            {                   
                sprite_.setTexture(texture);

                render_texture_.draw(sprite_);
            };
        
        void Object::clickLeftEvent      (const Event &event)  {}
        void Object::releaseLeftEvent    (const Event &event)  {}              

        void Object::clickRightEvent     (const Event &event)  {}
        void Object::releaseRightEvent   (const Event &event)  {}              
        
        void Object::moveMouseEvent      (const Event &event)  {}

        void Object::pressKeyEvent       (const Event &event)  {}
        void Object::textEvent           (const Event &event)  {}
        void Object::scrollEvent         (const Event &event)  {}

        bool Object::pointBelong (Vector2d point) const
        {
            auto field = getField();
            Vector2d start_field = field.first;
            Vector2d end_field   = field.second;

            return start_field.x_ < point.x_ && point.x_ < end_field.x_ &&
                   start_field.y_ < point.y_ && point.y_ < end_field.y_;
        }

        void Object::draw () 
        {   
            render_texture_.display();
            sprite_.setTexture(render_texture_.getTexture());

            if (parent_)
            {
                sprite_.setPosition(position_);
                parent_->getRenderTexture()->draw(sprite_);
            }
        }

        void Object::remove(Widget *child) 
        {
            std::logic_error exception("removing child to widget\n");
            throw exception;
        }

        void Object::add(Widget *child) 
        {
            std::logic_error exception("adding child to widget\n");
            throw exception;
        }

        void Object::display(Window *window) 
        {
            render_texture_.display();
            window->draw(sprite_);
            window->display();
            window->clear();
        }

        Vector2d Object::getShape() const 
        {
            return shape_; 
        }
        
        void Object::setShape (Vector2d shape) 
        {
            shape_  = shape; 
            
            render_texture_.clear();
            sprite_.setShape(shape);
            
            if (doublecmp(shape.x_, 0.f) && doublecmp(shape.y_, 0.f))
            {
                render_texture_.create(shape);
            }

            render_texture_.draw(sprite_);
        }

        Vector2d Object::getPosition() const 
        {
            return position_; 
        }

        void Object::setPosition(Vector2d position) 
        {
            position_ = position; 
        }
        
        std::pair<Vector2d, Vector2d> Object::getFieldLimits(const Widget *current, std::pair<Vector2d, Vector2d> curr_limit) const
        {
            if (current->getParent() == nullptr)
            {
                return {current->getPosition(), current->getPosition() + current->getShape()};
            }

            auto parent_limit = getFieldLimits(current->getParent(), curr_limit);

            curr_limit.first.x_ = curr_limit.first.x_ > parent_limit.first.x_  ? curr_limit.first.x_ : parent_limit.first.x_;
            curr_limit.first.x_ = curr_limit.first.x_ < parent_limit.second.x_ ? curr_limit.first.x_ : parent_limit.second.x_;
            curr_limit.first.y_ = curr_limit.first.y_ > parent_limit.first.y_  ? curr_limit.first.y_ : parent_limit.first.y_;
            curr_limit.first.y_ = curr_limit.first.y_ < parent_limit.second.y_ ? curr_limit.first.y_ : parent_limit.second.y_;

            curr_limit.second.x_ = curr_limit.second.x_ > parent_limit.first.x_  ? curr_limit.second.x_ : parent_limit.first.x_;
            curr_limit.second.x_ = curr_limit.second.x_ < parent_limit.second.x_ ? curr_limit.second.x_ : parent_limit.second.x_;
            curr_limit.second.y_ = curr_limit.second.y_ > parent_limit.first.y_  ? curr_limit.second.y_ : parent_limit.first.y_;
            curr_limit.second.y_ = curr_limit.second.y_ < parent_limit.second.y_ ? curr_limit.second.y_ : parent_limit.second.y_;

            return curr_limit;
        }

        std::pair<Vector2d, Vector2d> Object::getField() const 
        {
            const Widget *curr_widget = this;
            
            Vector2d start_field = position_;
            Vector2d end_field   = position_ + shape_;

            while (curr_widget->getParent())
            {
                curr_widget = curr_widget->getParent();
                
                start_field += curr_widget->getPosition();
                end_field   += curr_widget->getPosition();
            }

            auto limits = getFieldLimits(curr_widget, {start_field, end_field});

            return {start_field, end_field};
        }
        
        Widget *Object::getParent() const 
        {
            return parent_; 
        }

        void Object::setParent(Widget *parent) 
        { 
            parent_ = parent; 
        }

        Texture Object::getTexture() const 
        {
            return texture_;
        }

        void Object::setTexture(const Texture &texture) 
        {
            texture_ = texture;

            Sprite sprite(shape_, texture_);
            sprite_ = sprite;

            render_texture_.draw(sprite_);
        }

       RenderTexture *Object::getRenderTexture() 
        {
            return &render_texture_; 
        }

        void Object::setRenderTexture(RenderTexture render_texture) 
        {
            render_texture_ = render_texture;
        }        

        std::vector<Widget *> Object::getChildren() const 
        {
            // std::logic_error exception("try getting children from object\n");
            // throw exception;
            return {};
        }
        void Object::setChildren(std::vector<Widget *> children) 
        {
            // std::logic_error exception("try setting children to object\n");
            // throw exception;
        }
}