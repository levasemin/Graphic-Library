#include "Object.hpp"

namespace SL
{
    Object::Object(Vector2d shape, Vector2d position, const Texture &texture): Widget(),
            shape_(shape),
            position_(position),    
            texture_(texture),
            sprite_(shape, texture, 0),
            local_offset_(0, 0),
            global_offset_(0, 0),
            render_texture_(shape)
            {
                if (!doublecmp(position_.x_, -1.f) && !doublecmp(position_.y_, -1))
                {
                    position_ = Vector2d(0, 0);
                }
                                
                sprite_.setTexture(texture);

                render_texture_.draw(sprite_);
            };

        Object::Object(const Object& source):
            shape_(source.shape_),
            position_(source.position_),    
            texture_(source.texture_),
            sprite_(source.sprite_),
            local_offset_(source.local_offset_),
            global_offset_(source.global_offset_),
            render_texture_(source.render_texture_)
        {
        }

        Object &Object::operator=(const Object& source)
        {
            shape_         = source.shape_;
            position_      = source.position_;    
            texture_       = source.texture_;
            sprite_        = source.sprite_;
            local_offset_  = source.local_offset_;
            global_offset_ = source.global_offset_;

            render_texture_ = RenderTexture(shape_);
            
            return *this;
        }
        
        void Object::ClickLeftEvent      (const Event &event)  {}
        void Object::ReleasedLeftEvent   (const Event &event)  {}              

        void Object::ClickRightEvent     (const Event &event)  {}
        void Object::ReleasedRightEvent  (const Event &event)  {}              
        
        void Object::MoveMouseEvent      (const Event &event)  {}

        void Object::PressKeyEvent       (const Event &event)  {}
        void Object::TextEvent           (const Event &event)  {}
        void Object::ScrollEvent         (const Event &event)  {}

        bool Object::point_belonging(Vector2d point) const 
        {
            Vector2d start_field = get_start_field();
            Vector2d end_field   = get_end_field();

            return start_field.x_ < point.x_ && point.x_ < end_field.x_ &&
                   start_field.y_ < point.y_ && point.y_ < end_field.y_;
        }

        void Object::draw() 
        {   
            render_texture_.display();
            sprite_.setTexture(render_texture_.getTexture());

            if (parent_)
            {
                sprite_.setPosition(parent_->get_local_offset() * has_local_offset_ + position_);
                parent_->get_render_texture()->draw(sprite_);
            }
        }

        void Object::remove(Widget *window) 
        {
            std::logic_error exception("removing child to widget\n");
            throw exception;
        }

        void Object::add(Widget *window) 
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


        Vector2d Object::get_position() const 
        {
            return position_; 
        }
        void Object::set_position(Vector2d position) 
        {
            position_ = position; 
        }

        Vector2d Object::get_shape() const 
        {
            return shape_; 
        }
        
        void Object::set_shape (Vector2d shape) 
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

        Widget *Object::get_parent() const 
        {
            return parent_; 
        }
        void Object::set_parent(Widget *parent) 
        { 
            parent_ = parent; 
        }

        Texture Object::get_texture() const 
        {
            return texture_;
        }

        void Object::set_texture(const Texture &texture) 
        {
            texture_ = texture;

            Sprite sprite(shape_, texture_);
            sprite_ = sprite;

            render_texture_.draw(sprite_);
        }

       RenderTexture *Object::get_render_texture() 
        {
            return &render_texture_; 
        }

        void Object::set_render_texture(RenderTexture render_texture) 
        {
            render_texture_ = render_texture;
        }

        Vector2d Object::get_indent() const  { return Vector2d(0, 0); }
        
        void Object::set_indent(Vector2d indent)  {}

        Vector2d Object::get_global_shape() const 
        {
            return shape_; 
        }
        void Object::set_global_shape(Vector2d global_shape) 
        {
            shape_ = global_shape; 
        }

        Vector2d Object::get_global_offset() const 
        {
            return global_offset_; 
        }   
        void Object::set_global_offset(Vector2d offset) 
        {
            global_offset_ = offset; 
        }

        Vector2d Object::get_local_offset() const 
        {
            return local_offset_;
        }

        void Object::set_local_offset(Vector2d diff_offset) 
        { 
        }
        
        bool Object::get_has_local_offset () const 
        {
            return has_local_offset_;
        }
        void Object::set_has_local_offset(bool has) 
        {
            has_local_offset_ = has;
        }
        
        Vector2d Object::get_start_field() const 
        {
            Vector2d start_field = position_ + global_offset_;
            Vector2d down_limit  = parent_ != nullptr ? parent_->get_start_field() : position_;

            start_field.x_ = start_field.x_ < down_limit.x_ ? down_limit.x_ : start_field.x_;
            start_field.y_ = start_field.y_ < down_limit.y_ ? down_limit.y_ : start_field.y_;

            return start_field;
        }
        
        Vector2d Object::get_end_field() const 
        {
            Vector2d end_field = position_ + shape_ + global_offset_;
            Vector2d hight_limit = parent_ != nullptr ? parent_->get_end_field()   : position_ + shape_;

            end_field.x_ = end_field.x_ > hight_limit.x_ ? hight_limit.x_ : end_field.x_;
            end_field.y_ = end_field.y_ > hight_limit.y_ ? hight_limit.y_ : end_field.y_;

            return end_field;
        }

        std::vector<Widget *> Object::get_children() const 
        {
            // std::logic_error exception("try getting children from object\n");
            // throw exception;
            return {};
        }
        void Object::set_children(std::vector<Widget *> children) 
        {
            // std::logic_error exception("try setting children to object\n");
            // throw exception;
        }
}