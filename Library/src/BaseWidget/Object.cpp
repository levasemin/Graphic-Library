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
            Vector2d start_field = getStartField();
            Vector2d end_field   = getEndField();

            return start_field.x_ < point.x_ && point.x_ < end_field.x_ &&
                   start_field.y_ < point.y_ && point.y_ < end_field.y_;
        }

        void Object::draw() 
        {   
            render_texture_.display();
            sprite_.setTexture(render_texture_.getTexture());

            if (parent_)
            {
                sprite_.setPosition(parent_->getLocalOffset() * has_local_offset_ + position_);
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


        Vector2d Object::getPosition() const 
        {
            return position_; 
        }
        void Object::setPosition(Vector2d position) 
        {
            position_ = position; 
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

        Vector2d Object::getGlobalShape() const 
        {
            return shape_; 
        }

        Vector2d Object::getGlobalOffset() const 
        {
            return global_offset_; 
        }   
        void Object::setGlobalOffset(Vector2d offset) 
        {
            global_offset_ = offset; 
        }

        Vector2d Object::getLocalOffset() const 
        {
            return local_offset_;
        }

        void Object::setLocalOffset(Vector2d diff_offset) 
        { 
        }
        
        bool Object::getHasLocalOffset () const 
        {
            return has_local_offset_;
        }
        void Object::setHasLocalOffset(bool has) 
        {
            has_local_offset_ = has;
        }
        
        Vector2d Object::getStartField() const 
        {
            Vector2d start_field = position_ + global_offset_;
            Vector2d down_limit  = parent_ != nullptr ? parent_->getStartField() : position_;

            start_field.x_ = start_field.x_ < down_limit.x_ ? down_limit.x_ : start_field.x_;
            start_field.y_ = start_field.y_ < down_limit.y_ ? down_limit.y_ : start_field.y_;

            return start_field;
        }
        
        Vector2d Object::getEndField() const 
        {
            Vector2d end_field = position_ + shape_ + global_offset_;
            Vector2d hight_limit = parent_ != nullptr ? parent_->getEndField()   : position_ + shape_;

            end_field.x_ = end_field.x_ > hight_limit.x_ ? hight_limit.x_ : end_field.x_;
            end_field.y_ = end_field.y_ > hight_limit.y_ ? hight_limit.y_ : end_field.y_;

            return end_field;
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