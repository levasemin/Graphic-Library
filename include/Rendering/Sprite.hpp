#pragma once

#include "Texture.hpp"

namespace SL
{
    class Sprite
    {
    public:
        enum class Mode
        {
            FILL,
            FILL_X,
            FILL_Y,
            CROP,
        };
        
        Sprite(Vector2d shape, const Texture &texture, Mode mode = Mode::FILL);

        Sprite(sf::Sprite sprite);
        Sprite(const Sprite &source) = default;
        Sprite &operator= (const Sprite &source) = default;
        ~Sprite() = default;
                
        void setTextureRect(Vector2d start, Vector2d end);

        Vector2d getShape() const;
        void setShape(Vector2d shape, bool with_rescale = true);

        Color getColor() const;
        void setColor(const Color &color);

        Texture getTexture() const;
        void setTexture(const Texture &texture, bool resetRect = true);

        void setPosition(Vector2d position);

        Vector2d getScale() const;

        void rescale();

        friend class Window;
        friend class RenderTexture;

    private:
        Mode mode_;
        Vector2d shape_;
        Texture texture_;
        sf::Sprite sprite_;
    };
}