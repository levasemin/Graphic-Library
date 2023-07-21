#include "HorizontalScrollBar.hpp"

namespace SL
{
//public:
    HorizontalScrollBar::HorizontalScrollBar(Vector2d shape, Vector2d position, float min_value, float max_value, const Texture &texture):
        CompositeObject (shape, position, texture),
        left_button_    (Vector2d(shape.y_, shape.y_), Vector2d(0, 0)),
        right_button_   (Vector2d(shape.y_, shape.y_), Vector2d(shape.x_   - shape.y_, 0.f)),
        scroll_button_  (Vector2d((shape.x_ - shape.y_ * 2) * SCROLL_COEFF, shape.y_), Vector2d(left_button_.getShape().x_, 0.f)),
        scroll_field_shape_(shape.x_ - left_button_.getShape().x_ * 2 - scroll_button_.getShape().x_, shape.y_),
        min_value_(min_value),
        max_value_(max_value),

        scroll_button_texture_(Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))))
        {            
            TextureManager &texture_manager = TextureManager::getInstance();

            scroll_button_.setTexture(scroll_button_texture_);
            left_button_.  setTexture(texture_manager[TextureManager::Icon::LeftArrow]);
            right_button_. setTexture(texture_manager[TextureManager::Icon::RightArrow]);

            add(&left_button_);
            add(&right_button_);
            add(&scroll_button_);
                        
            left_button_.  setLeftClick((Command<const Event &> *) new SimpleCommand<HorizontalScrollBar, const Event &>(this, &HorizontalScrollBar::scrollUp));
            right_button_. setLeftClick((Command<const Event &> *) new SimpleCommand<HorizontalScrollBar, const Event &>(this, &HorizontalScrollBar::scrollDown));
            scroll_button_.setLeftClick((Command<const Event &> *) new SimpleCommand<HorizontalScrollBar, const Event &>(this, &HorizontalScrollBar::clickedScrollButton));
        };

    // HorizontalScrollBar::~HorizontalScrollBar()
    // {
    //     delete left_button_.  getLeftClick();
    //     delete right_button_. getLeftClick();
    //     delete scroll_button_.getLeftClick();
    // }

    Command<const Event &> *HorizontalScrollBar::getScrollCommand()
    {
        return scroll_command_;
    }

    void HorizontalScrollBar::setScrollCommand(Command<const Event &> *new_command)
    {
        scroll_command_ = new_command;
    }
    
    float HorizontalScrollBar::getValue()
    {
        float value = (scroll_button_.getPosition().x_ - left_button_.getShape().x_)  / scroll_field_shape_.x_;
        value *= max_value_ - min_value_;
        value += min_value_;

        return value;
    }

    void HorizontalScrollBar::setValue(float value_)
    {
        float value = (value_ - min_value_) / (max_value_ - min_value_);
        Event new_event;
        new_event.type_ = EventType::ScrollbarMoved;
        new_event.Oleg_.smedata.id = uint64_t(this);
        new_event.Oleg_.smedata.value = value_ < min_value_ ? min_value_ : value_;
        new_event.Oleg_.smedata.value = value_ > max_value_ ? max_value_ : value_;
        
        float offset = scroll_field_shape_.x_ * value;

        offset = offset >= 0 ? offset : 0;
        
        float max_offset = getShape().x_ - left_button_.getShape().x_ * 2 - scroll_button_.getShape().x_;
        offset = offset <= max_offset ? offset : max_offset;
        
        scroll_button_.setPosition(Vector2d(left_button_.getShape().x_ + offset, scroll_button_.getPosition().y_));
        
        if (scroll_command_)
        {
            scroll_command_->Execute(new_event);
        }
    }

    void HorizontalScrollBar::setMinValue(float min_value)
    {
        min_value_ = min_value;
    }
    
    float HorizontalScrollBar::getMinValue()
    {
        return min_value_;
    }

    void HorizontalScrollBar::setMaxValue(float max_value)
    {
        max_value_ = max_value;
    }

    float HorizontalScrollBar::getMaxValue()
    {
        return max_value_;
    }

    void HorizontalScrollBar::setSideButton(bool able)
    {
        Vector2d new_shape = left_button_.getShape();
        
        if (able)
        {
            scroll_field_shape_ = Vector2d(getShape().x_ - left_button_.getShape().x_ * 2 - scroll_button_.getShape().x_, getShape().y_);
            add(&left_button_);
            add(&right_button_);
        }

        else 
        {
            remove(&left_button_);
            remove(&right_button_);

            scroll_button_.setPosition(Vector2d(0.f, getShape().y_ + getShape().x_));
            scroll_field_shape_ = Vector2d(getShape().x_ - left_button_.getShape().x_ - right_button_.getShape().x_ - scroll_button_.getShape().x_, getShape().y_);
        }
    }

    void HorizontalScrollBar::setScrollButtonShape(const Vector2d &shape)
    {
        scroll_button_.setShape(shape);
        scroll_button_.setPosition(Vector2d(left_button_.getShape().x_, 0.f));
        scroll_field_shape_ = Vector2d(getShape().x_ - left_button_.getShape().x_ - right_button_.getShape().x_ - scroll_button_.getShape().x_, getShape().y_);
        scroll_coeff_ = scroll_button_.getShape().x_ / (getShape().x_ - right_button_.getShape().x_ * 2);
    }   


    void HorizontalScrollBar::moveMouseEvent (const Event &event)
    {
        if (scroll_button_.isLeftClicked())
        {   
            float value = (event.Oleg_.motion.pos.x_ - click_place_.x_ + scroll_button_.getPosition().x_ - left_button_.getShape().x_) / scroll_field_shape_.x_;
            value *= max_value_ - min_value_;
            value += min_value_;
            
            setValue(value);
            
            click_place_ = event.Oleg_.motion.pos;
        }
    };

    void HorizontalScrollBar::clickLeftEvent(const Event &event)
    {        
        if (pointBelong(event.Oleg_.mbedata.pos) &&
            !scroll_button_.pointBelong(event.Oleg_.mbedata.pos) &&
            !left_button_.  pointBelong(event.Oleg_.mbedata.pos) &&
            !right_button_. pointBelong(event.Oleg_.mbedata.pos))
        {                
            float value = (event.Oleg_.motion.pos.x_ - getField().first.x_ - left_button_.getShape().x_) / scroll_field_shape_.x_ - scroll_coeff_ / 2;
            value *= max_value_ - min_value_;
            value += min_value_;
            setValue(value);
            
            click_place_ = event.Oleg_.motion.pos;
        }

        CompositeObject::clickLeftEvent(event);
    }

//private:
    void HorizontalScrollBar::scrollUp(const Event &event)
    {
        float value = -scroll_coeff_ + (scroll_button_.getPosition().x_ - left_button_.getShape().x_) / scroll_field_shape_.x_;
        value *= max_value_ - min_value_;
        value += min_value_;
                
        setValue(value);
    }    

    void HorizontalScrollBar::scrollDown(const Event &event)
    {
        float value = scroll_coeff_ + (scroll_button_.getPosition().x_ - left_button_.getShape().x_)  / scroll_field_shape_.x_;
        value *= max_value_ - min_value_;
        value += min_value_;
        
        setValue(value);
    }

    void HorizontalScrollBar::clickedScrollButton(const Event &event)
    {
        click_place_ = scroll_button_.getField().first + scroll_button_.getShape() / 2;
    }
}