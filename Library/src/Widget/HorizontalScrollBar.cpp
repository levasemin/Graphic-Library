#include "HorizontalScrollBar.hpp"

namespace SL
{
    HorizontalScrollBar::HorizontalScrollBar(Vector2d shape, Vector2d position, float min_value, float max_value):
        CompositeObject  (shape, position),
        left_button_   (Vector2d(shape.y_, shape.y_), Vector2d(0, 0)),
        right_button_  (Vector2d(shape.y_, shape.y_), Vector2d(shape.x_   - shape.y_, 0.f)),
        scroll_button_ (Vector2d((shape.x_ - shape.y_ * 2) * SCROLL_COEFF, shape.y_), Vector2d(left_button_.get_shape().x_, 0.f)),
        scroll_field_shape(shape.x_ - left_button_.get_shape().x_ * 2 - scroll_button_.get_shape().x_, shape.y_),
        min_value_(min_value),
        max_value_(max_value),
        click_place_(0.f, 0.f)
        {
            set_texture(Texture(Color((uint8_t)92, (uint8_t)92, (uint8_t)92)));
            
            TextureManager &texture_manager = TextureManager::getInstance();

            left_button_.  set_texture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
            right_button_. set_texture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
            scroll_button_.set_texture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
            
            left_button_. set_texture (texture_manager[TextureManager::Icon::LeftArrow]);
            right_button_.set_texture(texture_manager[TextureManager::Icon::RightArrow]);

            add(&left_button_);
            add(&right_button_);
            add(&scroll_button_);
            
            right_button_.set_has_local_offset(false);
            left_button_.set_has_local_offset(false);
            
            left_button_.set_left_click  ((Command<const Event &> *) new SimpleCommand<HorizontalScrollBar, const Event &>(this, &HorizontalScrollBar::scroll_up));
            right_button_.set_left_click ((Command<const Event &> *) new SimpleCommand<HorizontalScrollBar, const Event &>(this, &HorizontalScrollBar::scroll_down));
            scroll_button_.set_left_click((Command<const Event &> *) new SimpleCommand<HorizontalScrollBar, const Event &>(this, &HorizontalScrollBar::clicked_scroll_button));
        };

    HorizontalScrollBar::HorizontalScrollBar(const HorizontalScrollBar &source) : CompositeObject(*(const CompositeObject *)&source),
        left_button_(source.left_button_),
        right_button_(source.right_button_),
        scroll_button_(source.scroll_button_),
        scroll_field_shape(source.scroll_field_shape),
        min_value_(source.min_value_),
        max_value_(source.max_value_),
        click_place_(0.f, 0.f)
    {}

    HorizontalScrollBar &HorizontalScrollBar::operator=(const HorizontalScrollBar &source)
    {
        CompositeObject::operator=(*(const CompositeObject *)&source);
        left_button_       = source.left_button_;
        right_button_      = source.right_button_;
        scroll_button_     = source.scroll_button_;
        scroll_field_shape = source.scroll_field_shape;
        min_value_         = source.min_value_;
        max_value_         = source.max_value_; 
        click_place_ = Vector2d(0.f, 0.f);

        return *this;
    }

    void HorizontalScrollBar::set_button(bool able)
    {
        Vector2d new_shape = left_button_.get_shape();
        
        if (!able)
        {
            new_shape = Vector2d(0, 0);    
        }

        else 
        {
            new_shape = Vector2d(shape_.y_, shape_.y_);
        }

        set_up_right_button_shape(new_shape);
    }

    void HorizontalScrollBar::set_scroll_button_shape(const Vector2d &shape)
    {
        scroll_button_.set_shape(shape);
        scroll_button_.set_position(Vector2d(left_button_.get_shape().x_, 0.f));
        scroll_field_shape = Vector2d(shape_.x_ - left_button_.get_shape().x_ - right_button_.get_shape().x_ - scroll_button_.get_shape().x_, shape_.y_);
        scroll_coeff_ = scroll_button_.get_shape().x_ / (shape_.x_ - right_button_.get_shape().x_ * 2);
    }

    void HorizontalScrollBar::set_up_right_button_shape(const Vector2d &shape)
    {
        left_button_.set_shape(shape);
        right_button_.set_shape(shape);
        
        scroll_button_.set_position(Vector2d(0.f, shape.y_ + shape_.x_));
        scroll_field_shape = Vector2d(shape_.x_ - left_button_.get_shape().x_ - right_button_.get_shape().x_ - scroll_button_.get_shape().x_, shape_.y_);
    }

    void HorizontalScrollBar::scroll_bar(float value_)
    {
        float value = (value_ - min_value_) / (max_value_ - min_value_);
        Event new_event;
        new_event.type_ = EventType::ScrollbarMoved;
        new_event.Oleg_.smedata.id = uint64_t(this);
        new_event.Oleg_.smedata.value = value_ < min_value_ ? min_value_ : value_;
        new_event.Oleg_.smedata.value = value_ > max_value_ ? max_value_ : value_;
        
        Vector2d offset = Vector2d(scroll_field_shape.x_, 0.f);
        offset *= value;

        offset.x_ = offset.x_ >= 0 ? offset.x_ : 0;
        offset.y_ = offset.y_ >= 0 ? offset.y_ : 0;
        
        Vector2d max_offset = Vector2d(shape_.x_ - left_button_.get_shape().x_ * 2 - scroll_button_.get_shape().x_, 0.f);
        offset.x_ = offset.x_ <= max_offset.x_ ? offset.x_ : max_offset.x_;
        offset.y_ = offset.y_ <= max_offset.y_ ? offset.y_ : max_offset.y_;
        
        set_local_offset(offset);
        
        if (scroll_command_)
        {
            scroll_command_->Execute(new_event);
        }
    }   

    void HorizontalScrollBar::MoveMouseEvent (const Event &event)
    {
        if (scroll_button_.is_left_clicked_)
        {   
            Event new_event;

            float value = (event.Oleg_.motion.pos.x_ - click_place_.x_) / scroll_field_shape.x_ + local_offset_.x_ / scroll_field_shape.x_;
            value *= max_value_ - min_value_;
            value += min_value_;
            
            scroll_bar(value);
            
            click_place_ = event.Oleg_.motion.pos;
        }
    };

    void HorizontalScrollBar::scroll_up(const Event &event)
    {
        float value = -scroll_coeff_ + local_offset_.x_ / scroll_field_shape.x_;
        value *= max_value_ - min_value_;
        value += min_value_;
        scroll_bar(value);
    }    

    void HorizontalScrollBar::scroll_down(const Event &event)
    {
        float value = scroll_coeff_ + local_offset_.x_ / scroll_field_shape.x_;
        value *= max_value_ - min_value_;
        value += min_value_;
        scroll_bar(value);
    }
    
    void HorizontalScrollBar::ClickLeftEvent(const Event &event)
    {
        if (point_belonging(event.Oleg_.mbedata.pos) &&
        !scroll_button_.point_belonging(event.Oleg_.mbedata.pos) &&
        !left_button_.point_belonging(event.Oleg_.mbedata.pos) &&
        !right_button_.point_belonging(event.Oleg_.mbedata.pos))
        {                
            float value = (event.Oleg_.motion.pos.x_ - get_start_field().x_ - left_button_.get_shape().x_) / scroll_field_shape.x_ - scroll_coeff_ / 2;
            value *= max_value_ - min_value_;
            value += min_value_;
            scroll_bar(value);
            
            click_place_ = event.Oleg_.motion.pos;
        }
        
        CompositeObject::ClickLeftEvent(event);
    }

    void HorizontalScrollBar::clicked_scroll_button(const Event &event)
    {
        click_place_ = Vector2d((scroll_button_.get_start_field() + scroll_button_.get_end_field()) / 2);
    }

    void HorizontalScrollBar::set_scroll_command(Command<const Event &> *new_command)
    {
        scroll_command_ = new_command;
    }

}