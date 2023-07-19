#include "Object.hpp"

namespace SL
{
    Object::Object(Vector2d shape, Vector2d position, const Texture &texture): Widget(),
            shape_(shape),
            position_(position),    
            texture_(texture),
            sprite_(shape, texture, 0),
            real_position_(position),
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
                sprite_.setPosition(real_position_);
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
            real_position_ += position - position_;
            position_ = position; 
        }

        std::pair<Vector2d, Vector2d> Object::getField() const 
        {
            if (parent_ != nullptr)
            {   
                auto parent_field = parent_->getField();
                Vector2d parent_start_field = parent_field.first;
                Vector2d parent_end_field   = parent_field.second;

                Vector2d start_field = parent_start_field + real_position_;
                Vector2d end_field   = parent_start_field + real_position_ + shape_;

                start_field.x_ = start_field.x_ > parent_start_field.x_ ? start_field.x_ : parent_start_field.x_;
                start_field.x_ = start_field.x_ < parent_end_field.x_   ? start_field.x_ : parent_end_field.x_;
                start_field.y_ = start_field.y_ > parent_start_field.y_ ? start_field.y_ : parent_start_field.y_;
                start_field.y_ = start_field.y_ < parent_end_field.y_   ? start_field.y_ : parent_end_field.y_;

                end_field.x_ = end_field.x_ > parent_start_field.x_ ? end_field.x_ : parent_start_field.x_;
                end_field.x_ = end_field.x_ < parent_end_field.x_   ? end_field.x_ : parent_end_field.x_;
                end_field.y_ = end_field.y_ > parent_start_field.y_ ? end_field.y_ : parent_start_field.y_;
                end_field.y_ = end_field.y_ < parent_end_field.y_   ? end_field.y_ : parent_end_field.y_;

                return {start_field, end_field};
            }

            return {real_position_, real_position_ + shape_};
        }

        Vector2d Object::getGlobalShape() const 
        {
            auto field = getField();

            return field.second - field.first;
        }

        Vector2d Object::getVirtualShape() const
        {
            return shape_;
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