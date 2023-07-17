#include "VerticalScrollBar.hpp"

namespace SL
{
    VerticalScrollBar::VerticalScrollBar(Vector2d shape, Vector2d position, float min_value, float max_value):
        CompositeObject  (shape, position),
        scroll_coeff_(SCROLL_COEFF),
        click_place_(0, 0),
        up_button_    (Vector2d(shape.x_, shape.x_), Vector2d(0, 0)),
        down_button_  (Vector2d(shape.x_, shape.x_), Vector2d(0.f, shape_.y_  - shape.x_)),
        scroll_button_(Vector2d(shape.x_, (shape.y_ - shape.x_ * 2) * SCROLL_COEFF),
                    Vector2d(0.f, shape.x_)),
        scroll_field_shape(shape_.x_, shape_.y_ - shape_.x_ * 2 - scroll_button_.getShape().y_),
        min_value_(min_value),
        max_value_(max_value)
    {
        setTexture(Texture(Color((uint8_t)92, (uint8_t)92, (uint8_t)92)));
        
        TextureManager &texture_manager = TextureManager::getInstance();

        up_button_.    setTexture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
        down_button_.  setTexture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
        scroll_button_.setTexture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
        
        up_button_.  setTexture(texture_manager[TextureManager::Icon::UpArrow]);
        down_button_.setTexture(texture_manager[TextureManager::Icon::DownArrow]);

        add(&up_button_);
        add(&down_button_);
        add(&scroll_button_);
        
        down_button_.setHasLocalOffset(false);
        up_button_.setHasLocalOffset(false);
        
        up_button_.set_left_click    ((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::scroll_up));
        down_button_.set_left_click  ((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::scroll_down));
        scroll_button_.set_left_click((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::clicked_scroll_button));
    }

    VerticalScrollBar::VerticalScrollBar(const VerticalScrollBar &source) : CompositeObject(*(const CompositeObject *)&source),
        scroll_coeff_(source.scroll_coeff_),
        click_place_(0, 0),
        up_button_(source.up_button_),
        down_button_(source.down_button_),    
        scroll_button_(source.scroll_button_),
        scroll_field_shape(source.scroll_field_shape),
        scroll_command_(source.scroll_command_)
    {}

    VerticalScrollBar &VerticalScrollBar::operator =(const VerticalScrollBar &source)
    {
        CompositeObject::operator=(*(const CompositeObject *)&source);
        scroll_coeff_      = source.scroll_coeff_;
        click_place_       = Vector2d(0, 0);
        up_button_         = source.up_button_;
        down_button_       = source.down_button_;    
        scroll_button_     = source.scroll_button_;
        scroll_field_shape = source.scroll_field_shape;
        scroll_command_    = source.scroll_command_;

        return *this;
    }

    VerticalScrollBar::~VerticalScrollBar()
    {
        delete up_button_.get_left_click();
        delete down_button_.get_left_click();
        delete scroll_button_.get_left_click();
    }

    void VerticalScrollBar::set_button(bool able)
    {
        Vector2d new_shape = up_button_.getShape();
        
        if (!able)
        {
            new_shape = Vector2d(0, 0);    
        }

        else 
        {
            new_shape = Vector2d(shape_.x_, shape_.x_);
        }

        up_button_.setShape(new_shape);
        down_button_.setShape(new_shape);
        
        scroll_button_.setPosition(Vector2d(0.f, up_button_.getShape().y_));
        scroll_field_shape.y_ = shape_.y_ - down_button_.getShape().x_ * 2 - scroll_button_.getShape().y_;
    }

    void VerticalScrollBar::set_scroll_button_size(const Vector2d &shape)
    {
        scroll_button_.setShape(shape);
        scroll_button_.setPosition(Vector2d(0.f, up_button_.getShape().y_));
        scroll_field_shape.y_ = shape_.y_ - down_button_.getShape().x_ * 2 - scroll_button_.getShape().y_;
        scroll_coeff_ = scroll_button_.getShape().y_ / (shape_.y_ - down_button_.getShape().y_ * 2);
    }


    void VerticalScrollBar::scrollEvent(const Event &event)
    {            
        if (pointBelong(event.Oleg_.sedata.pos))
        {
            float value = (-event.Oleg_.sedata.value + local_offset_.y_) / scroll_field_shape.y_;
            value *= max_value_ - min_value_;
            value += min_value_;
            scroll_bar(value);
        }
    }

    void VerticalScrollBar::scroll_bar(float value_)
    {
        float value = (value_ - min_value_) / (max_value_ - min_value_);
        Event new_event;
        new_event.type_ = EventType::ScrollbarMoved;
        new_event.Oleg_.smedata.id = (uint64_t)this; 
        new_event.Oleg_.smedata.value = value_ < min_value_ ? min_value_ : value_;
        new_event.Oleg_.smedata.value = value_ > max_value_ ? max_value_ : value_;
        
        Vector2d offset = Vector2d(0.f, scroll_field_shape.y_);
        offset *= value;

        offset.x_ = offset.x_ >= 0 ? offset.x_ : 0;
        offset.y_ = offset.y_ >= 0 ? offset.y_ : 0;
        
        Vector2d max_offset = Vector2d(0.f, shape_.y_ - up_button_.getShape().y_ * 2 - scroll_button_.getShape().y_);
        offset.x_ = offset.x_ <= max_offset.x_ ? offset.x_ : max_offset.x_;
        offset.y_ = offset.y_ <= max_offset.y_ ? offset.y_ : max_offset.y_;
        
        setLocalOffset(offset);

        if (scroll_command_)
        {
            scroll_command_->Execute(new_event);
        }
    }   

    void VerticalScrollBar::moveMouseEvent (const Event &event)
    {
        if (scroll_button_.is_left_clicked_)
        {   
            float value = (event.Oleg_.motion.pos.y_ - click_place_.y_) / scroll_field_shape.y_ + local_offset_.y_ / scroll_field_shape.y_;
            value *= max_value_ - min_value_;
            value += min_value_;
            scroll_bar(value);
            
            click_place_ = event.Oleg_.motion.pos;
        }
    };

    void VerticalScrollBar::scroll_up(const Event &event)
    {
        float value = -scroll_coeff_ + local_offset_.y_ / scroll_field_shape.y_;
        value *= max_value_ - min_value_;
        value += min_value_;
        scroll_bar(value);
    }    

    void VerticalScrollBar::scroll_down(const Event &event)
    {
        float value = scroll_coeff_ + local_offset_.y_ / scroll_field_shape.y_;
        value *= max_value_ - min_value_;
        value += min_value_;
        scroll_bar(value);
    }

    void VerticalScrollBar::clickLeftEvent(const Event &event)
    {
        if (pointBelong(event.Oleg_.mbedata.pos) &&
        !scroll_button_.pointBelong(event.Oleg_.mbedata.pos) &&
        !up_button_.pointBelong(event.Oleg_.mbedata.pos) &&
        !down_button_.pointBelong(event.Oleg_.mbedata.pos))
        {                
            float value = (event.Oleg_.motion.pos.y_ - getStartField().y_ - up_button_.getShape().y_) / scroll_field_shape.y_ - scroll_coeff_ / 2;
            value *= max_value_ - min_value_;
            value += min_value_;
            scroll_bar(value);
            
            click_place_ = event.Oleg_.motion.pos;
        }
        
        CompositeObject::clickLeftEvent(event);
    }

    void VerticalScrollBar::clicked_scroll_button(const Event &event)
    {
        click_place_ = Vector2d((scroll_button_.getStartField() + scroll_button_.getEndField()) / 2);
    }

    void VerticalScrollBar::set_scroll_command(Command<const Event &> *new_command)
    {
        scroll_command_ = new_command;
    }
}