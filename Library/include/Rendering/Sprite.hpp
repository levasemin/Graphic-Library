#pragma once

#include "Texture.hpp"

namespace SL
{
    const int FILL   = 0;
    const int FILL_X = 1;
    const int FILL_Y = 2;
    const int CROP   = 3;

    class Sprite
    {

    private:
        int mode_;
        Vector2d shape_;
        Texture texture_;
        sf::Sprite sprite_;
    public:

        Sprite(Vector2d shape, const Texture &texture, int mode = FILL);

        Sprite(sf::Sprite sprite);
        
        void setTextureRect(Vector2d start, Vector2d end);

        Vector2d getShape();
        void setShape(Vector2d shape, bool with_rescale = true);

        Color getColor();
        void setColor(const Color &color);

        Texture getTexture();
        void setTexture(const Texture &texture, bool resetRect = true);

        void setPosition(Vector2d position);

        Vector2d getScale();

        void rescale();

        friend class Window;
        friend class RenderTexture;
    };
}