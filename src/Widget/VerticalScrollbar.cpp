#include "VerticalScrollBar.hpp"

namespace SL
{
//public:
    VerticalScrollBar::VerticalScrollBar(Vector2d shape, Vector2d position, float min_value, float max_value, const Texture &texture):
        CompositeObject  (shape, position, texture),
        up_button_    (Vector2d(shape.x_, shape.x_), Vector2d(0, 0)),
        down_button_  (Vector2d(shape.x_, shape.x_), Vector2d(0.f, shape.y_  - shape.x_)),
        scroll_button_(Vector2d(shape.x_, (shape.y_ - shape.x_ * 2) * SCROLL_COEFF),
                       Vector2d(0.f, shape.x_)),
        scroll_field_shape_(shape.x_, shape.y_ - shape.x_ * 2 - scroll_button_.getShape().y_),
        min_value_(min_value),
        max_value_(max_value),

        scroll_button_texture_(Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))))
    {
        setTexture(Texture(Color((uint8_t)92, (uint8_t)92, (uint8_t)92)));

        TextureManager &texture_manager = TextureManager::getInstance();

        scroll_button_.setTexture(scroll_button_texture_);        
        up_button_.    setTexture(texture_manager[TextureManager::Icon::UpArrow]);
        down_button_.  setTexture(texture_manager[TextureManager::Icon::DownArrow]);

        add(&up_button_);
        add(&down_button_);
        add(&scroll_button_);

        up_button_.    setLeftClick((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::scrollUp));
        down_button_.  setLeftClick((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::scrollDown));
        scroll_button_.setLeftClick((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::clickedScrollButton));

        // scroll_button_.getField().first.print_value();
    }

    VerticalScrollBar::VerticalScrollBar(const VerticalScrollBar &source): SL::CompositeObject(*(SL::CompositeObject *)&source),
        up_button_(source.up_button_),
        down_button_(source.down_button_),
        scroll_button_(source.scroll_button_),
        click_place_(Vector2d(0, 0)),
        scroll_field_shape_(source.scroll_field_shape_),
        min_value_(source.min_value_),
        max_value_(source.max_value_),
        scroll_button_texture_(source.scroll_button_texture_)
    {
        up_button_.    setLeftClick((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::scrollUp));
        down_button_.  setLeftClick((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::scrollDown));
        scroll_button_.setLeftClick((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::clickedScrollButton));
    }

    VerticalScrollBar &VerticalScrollBar::operator=(const VerticalScrollBar &source)
    {
        SL::CompositeObject::operator=(*(SL::CompositeObject *)&source);

        up_button_ = source.up_button_;
        down_button_ = source.down_button_;
        scroll_button_ = source.scroll_button_;
        click_place_ = Vector2d(0, 0);
        scroll_field_shape_ = source.scroll_field_shape_;
        min_value_ = source.min_value_;
        max_value_ = source.max_value_;
        scroll_button_texture_ = source.scroll_button_texture_;

        up_button_.    setLeftClick((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::scrollUp));
        down_button_.  setLeftClick((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::scrollDown));
        scroll_button_.setLeftClick((Command<const Event &> *) new SimpleCommand<VerticalScrollBar, const Event &>(this, &VerticalScrollBar::clickedScrollButton));

        return *this;
    }

    VerticalScrollBar::~VerticalScrollBar()
    {
        delete scroll_command_;
        delete up_button_.    getLeftClick();
        delete down_button_  .getLeftClick();
        delete scroll_button_.getLeftClick();
    }

    Command<const Event &> *VerticalScrollBar::getScrollCommand()
    {
        return scroll_command_;
    }
    
    void VerticalScrollBar::setScrollCommand(Command<const Event &> *new_command)
    {
        scroll_command_ = new_command;
    }

    float VerticalScrollBar::getValue()
    {
        float value = (scroll_button_.getPosition().y_ - up_button_.getShape().y_)  / scroll_field_shape_.y_;
        value *= max_value_ - min_value_;
        value += min_value_;

        return value;
    }

    void VerticalScrollBar::setValue(float value_)
    {
        value_ = value_ < max_value_ ? value_ : max_value_;
        value_ = value_ > min_value_ ? value_ : min_value_;
        float value = (value_ - min_value_) / (max_value_ - min_value_);
        
        Event new_event;
        new_event.type_ = EventType::ScrollbarMoved;
        new_event.Oleg_.smedata.id = uint64_t(this);
        new_event.Oleg_.smedata.value = value_ < min_value_ ? min_value_ : value_;
        new_event.Oleg_.smedata.value = value_ > max_value_ ? max_value_ : value_;
        
        float offset = scroll_field_shape_.y_ * value;
        
        scroll_button_.setPosition(Vector2d(scroll_button_.getPosition().x_, up_button_.getShape().y_ + offset));
        
        if (scroll_command_)
        {
            scroll_command_->Execute(new_event);
        }
    }   

    float VerticalScrollBar::getMinValue()
    {
        return min_value_;
    }

    void VerticalScrollBar::setMinValue(float min_value)
    {
        min_value_ = min_value;
    }

    float VerticalScrollBar::getMaxValue()
    {
        return max_value_;
    }

    void VerticalScrollBar::setMaxValue(float max_value)
    {
        max_value_ = max_value;
    }

    void VerticalScrollBar::setSideButton(bool able)
    {
        Vector2d new_shape = up_button_.getShape();
        
        if (able)
        {
            scroll_field_shape_ = Vector2d(getShape().x_, getShape().y_ - getShape().x_ * 2 - scroll_button_.getShape().y_);
            add(&up_button_);
            add(&down_button_);
        }

        else 
        {
            remove(&up_button_);
            remove(&down_button_);

            scroll_button_.setPosition(Vector2d(0.f, up_button_.getShape().y_));
            scroll_field_shape_ = Vector2d(0.f, getShape().y_ - down_button_.getShape().x_ * 2 - scroll_button_.getShape().y_);
        }        
    }

    void VerticalScrollBar::setScrollButtonShape(const Vector2d &shape)
    {
        scroll_button_.setShape(shape);
        scroll_button_.setPosition(Vector2d(0.f, up_button_.getShape().y_));
        scroll_field_shape_.y_ = getShape().y_ - down_button_.getShape().x_ * 2 - scroll_button_.getShape().y_;
        scroll_coeff_ = scroll_button_.getShape().y_ / (getShape().y_ - down_button_.getShape().y_ * 2);
    }


    void VerticalScrollBar::moveMouseEvent (const Event &event)
    {
        if (scroll_button_.isLeftClicked())
        {   
            float value = (event.Oleg_.motion.pos.y_ - click_place_.y_ + scroll_button_.getPosition().y_ - up_button_.getShape().y_) / scroll_field_shape_.y_;
            value *= max_value_ - min_value_;
            value += min_value_;
       
            setValue(value);
            
            click_place_ = event.Oleg_.motion.pos;
        }
    };

    void VerticalScrollBar::clickLeftEvent(const Event &event)
    {
//TODO
        CompositeObject::clickLeftEvent(event);

        if (pointBelong(event.Oleg_.mbedata.pos) && is_scroll_surface_click_)
        {
            float value = (event.Oleg_.motion.pos.y_ - getField().first.y_ - up_button_.getShape().y_) / scroll_field_shape_.y_ - scroll_coeff_ / 2;
            value *= max_value_ - min_value_;
            value += min_value_;
            
            setValue(value);
            
            click_place_ = event.Oleg_.motion.pos;
        }

        is_scroll_surface_click_ = true;
    }

    void VerticalScrollBar::scrollEvent(const Event &event)
    {            
        if (pointBelong(event.Oleg_.sedata.pos))
        {
            float value = (-event.Oleg_.sedata.value + scroll_button_.getPosition().y_ - up_button_.getShape().y_) / scroll_field_shape_.y_;
            value *= max_value_ - min_value_;
            value += min_value_;
            setValue(value);
        }
    }

//private:
    void VerticalScrollBar::scrollUp(const Event &event)
    {
        is_scroll_surface_click_ = false;

        float value = -scroll_coeff_ + (scroll_button_.getPosition().y_ - up_button_.getShape().y_) / scroll_field_shape_.y_;
        value *= max_value_ - min_value_;
        value += min_value_;
        setValue(value);
    }    

    void VerticalScrollBar::scrollDown(const Event &event)
    {
        is_scroll_surface_click_ = false;

        float value = scroll_coeff_ + (scroll_button_.getPosition().y_ - up_button_.getShape().y_)  / scroll_field_shape_.y_;
        value *= max_value_ - min_value_;
        value += min_value_;
        setValue(value);
    }

    void VerticalScrollBar::clickedScrollButton(const Event &event)
    {
        is_scroll_surface_click_ = false;
        click_place_ = getField().first + scroll_button_.getPosition() + scroll_button_.getShape() / 2;
    }
}