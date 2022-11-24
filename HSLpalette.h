#include "Object.h"
#include "ScrollBar.h"
#include "Image.h"

class HSVpalette : public Object
{   
public:
    float h_ = 360.0;
    float s_;
    float v_;

    ScrollBar scroll_bar_;
    Image palette_;

    HSVpalette(Vector2d shape, Vector2d center) : Object(shape, center),
        scroll_bar_(Vector2d(10, shape.y_), Vector2d(center.x_ + shape.x_ / 2 + 5, center.y_)),
        palette_(shape)
    {
        scroll_bar_.set_scroll_command((Command<const Event &> *) new SimpleCommand<HSVpalette, const Event&>(this, &HSVpalette::change_H));
        
        Image scroll_bar_image(scroll_bar_.get_shape());
        
        for (float y = 0; y < scroll_bar_image.getSize().y_; y++)
        {
            for (float x = 0; x < scroll_bar_image.getSize().x_; x++)
            {
                scroll_bar_image.setPixel(Vector2d(x, y), Color(convert_hsv_rgb((1.0 - y / scroll_bar_.get_shape().y_) * 360.0, 1.0, 1.0)));
            }
        }

        scroll_bar_.set_texture(scroll_bar_image.getTexture());
    }

    Color convert_hsv_rgb(float h, float s, float v)
    {
        float c = v * s;
        float mod_2 = (float)((int)(h / 60 * 10000) % 20000) / 10000.0;
        float x = c * (1 - abs( mod_2 - 1));
        float m = v - c;
        float r = 0, g = 0, b = 0;

        if (h < 60)
        {
            r = c;
            g = x;
            b = 0;
        }

        else if (h < 120)
        {
            r = x;
            g = c;
            b = 0;
        }

        else if (h < 180)
        {
            r = 0;
            g = c;
            b = x;
        }

        else if (h < 240)
        {
            r = 0;
            g = x;
            b = c;
        }

        else if (h < 300)
        {
            r = x;
            g = 0;
            b = c;
        }

        else
        {
            r = c;
            g = 0;
            b = x;
        }
        
        // std::cout << "r': " << r << std::endl;
        // std::cout << "g': " << g << std::endl;
        // std::cout << "b': " << b << std::endl;
        // std::cout << "m': " << m << std::endl;

        Color color_rgb((uint8_t)(int)((r + m) * 255.0), (uint8_t)(int)((g + m) * 255.0), (uint8_t)(int)((b + m) * 255.0));

        return color_rgb;
    }
    

    void draw() override
    {   
        for (float y = 0; y < shape_.y_; y++)
        {
            for (float x = 0; x < shape_.x_; x++)
            {
                palette_.setPixel(Vector2d(x, y), Color(convert_hsv_rgb(h_, x / shape_.x_, 1.0 - y / shape_.y_)));
            }
        }

        Sprite sprite(shape_, palette_.getTexture());
        render_texture_->clear();
        render_texture_->draw(sprite);
        render_texture_->display();
        
        scroll_bar_.draw();
        Object::draw();
    }

    void set_parent(Widget *parent) override
    {
        parent_ = parent;
        parent_->add(&scroll_bar_);
    }

    void ClickLeftEvent(const Event &event) override
    {
        if (point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)))
        {
            s_ = (event.Oleg_.mbedata.x - get_start_field().x_) / shape_.x_;
            v_ = 1.0 - (event.Oleg_.mbedata.y - get_start_field().y_) / shape_.y_;
        }
    }

    void change_H(const Event &event)
    {
        h_ += 360.0 * event.Oleg_.smedata.value;
    }
};