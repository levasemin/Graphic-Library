#include "Object.hpp"
#include "Application.hpp"

namespace SL
{
    class Application;

    Object::Object(Vector2d shape, Vector2d position, const Texture &texture): Widget(),
            shape_(shape),
            position_(position),    
            texture_(texture),
            sprite_(shape, texture, Sprite::Mode::CROP),
            render_texture_(shape)
            {                   
                sprite_.setTexture(texture);

                render_texture_.draw(sprite_);
            };
        
        void Object::pressEvent      (const Event &event)  {}
        void Object::releaseEvent    (const Event &event)  {}              
        
        void Object::moveMouseEvent  (const Event &event)  {}

        void Object::pressKeyEvent   (const Event &event)  {}
        void Object::textEvent       (const Event &event)  {}
        void Object::scrollEvent     (const Event &event)  {}

        void Object::resizedEvent    (const Event &event)
        {
            shape_    = Vector2d(getShape().x_    * event.Oleg_.redata.shape.x_, getShape().y_    * event.Oleg_.redata.shape.y_);
            position_ = Vector2d(getPosition().x_ * event.Oleg_.redata.shape.x_, getPosition().y_ * event.Oleg_.redata.shape.y_);
        }

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
            sprite_.setPosition(Vector2d(0, 0));
                                
            sprite_.setShape(shape_);

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
            return Vector2d(shape_.x_ / Application::getCoeff().x_, 
                            shape_.y_ / Application::getCoeff().y_); 
        }
        
        void Object::setShape (Vector2d shape) 
        {
            shape_  = Vector2d(shape.x_ * Application::getCoeff().x_,
                               shape.y_ * Application::getCoeff().y_); 
        }

        Vector2d Object::getPosition() const 
        {
            return Vector2d(position_.x_ / Application::getCoeff().x_, 
                            position_.y_ / Application::getCoeff().y_); 
        }

        void Object::setPosition(Vector2d position) 
        {
            position_ = Vector2d(position.x_ * Application::getCoeff().x_, 
                                 position.y_ * Application::getCoeff().y_); 
        }
        
        Vector2d Object::getFieldLimits(const Widget *current, std::pair<Vector2d, Vector2d> *curr_value) const
        {
            Vector2d curr_start = current->getPosition();
            Vector2d curr_end   = current->getPosition() + current->getShape();
            
            curr_value->first  += curr_start;
            curr_value->second += curr_end;
                        
            if (current->getParent() != nullptr)
            {                
                auto parent_start = getFieldLimits(current->getParent(), curr_value);
                curr_start += parent_start;
                curr_end   += parent_start; 
            }
            
            curr_value->first.x_  = curr_value->first.x_  > curr_start.x_  ? curr_value->first.x_  : curr_start.x_;
            curr_value->first.x_  = curr_value->first.x_  < curr_end.x_    ? curr_value->first.x_  : curr_end.x_;
            curr_value->first.y_  = curr_value->first.y_  > curr_start.y_  ? curr_value->first.y_  : curr_start.y_;
            curr_value->first.y_  = curr_value->first.y_  < curr_end.y_    ? curr_value->first.y_  : curr_end.y_;

            curr_value->second.x_ = curr_value->second.x_ > curr_start.x_  ? curr_value->second.x_ : curr_start.x_;
            curr_value->second.x_ = curr_value->second.x_ < curr_end.x_    ? curr_value->second.x_ : curr_end.x_;
            curr_value->second.y_ = curr_value->second.y_ > curr_start.y_  ? curr_value->second.y_ : curr_start.y_;
            curr_value->second.y_ = curr_value->second.y_ < curr_end.y_    ? curr_value->second.y_ : curr_end.y_;

            return curr_start;
        }
        
        std::pair<Vector2d, Vector2d> Object::getField() const 
        {
            std::pair<Vector2d, Vector2d> field = {Vector2d(0, 0), Vector2d(0, 0)};

            getFieldLimits(this, &field);
            
            return field;
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

        Color Object::getColor() const
        {
            return sprite_.getColor();
        }

        void Object::setColor(Color color)
        {
            sprite_.setColor(color);
        }

        RenderTexture *Object::getRenderTexture() 
        {
            return &render_texture_; 
        }      

        std::vector<Widget *> Object::getChildren() const 
        {
            std::logic_error exception("try getting children from object\n");
            throw exception;
        }
}