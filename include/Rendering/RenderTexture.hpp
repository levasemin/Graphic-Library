/**
 * @file RenderTexture.hpp
 * @author Semin Lev (you@domain.com)
 * @brief declaration class RenderTexture
 * @version 0.1
 * @date 2023-07-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "Text.hpp"
#include "Vector2d.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"

namespace SL
{
    /**
     * @brief class RenderTexture is wrapper of sf::RenderTexture  
     * 
     * @details class is augmented with functions of copy and move semantic
     */
    class RenderTexture
    {
    public:

        /**
         * @brief Construct a new render texture object
         * 
         * @param size size of render texture
         */
        RenderTexture(Vector2d size);

        RenderTexture(const RenderTexture &source);            
        RenderTexture& operator= (const RenderTexture &source);

        ~RenderTexture() = default;
        
        /**
         * @brief Get the texture, that is drawn on Render Texture
         * 
         * @return Texture 
         */
        Texture getTexture() const;

        /**
         * @brief Get the size of render texture
         * 
         * @return Vector2d
         */
        Vector2d getSize() const;

        /**
         * @brief Set new size
         * 
         * @param size new size
         */
        void setSize(Vector2d size);

        /**
         * @brief reset render texture with new size
         * 
         * @param size new size
         */
        void create(const Vector2d &size);
        
        /**
         * @brief draw sprite on render texture
         * 
         * @param sprite drawing sprite
         */
        void draw(const Sprite &sprite);

        /**
         * @brief draw text on render texture
         * 
         * @param text drawing text
         */
        void draw(const Text &text);
        
        /**
         * @brief update the contents of the render texture.
         * @details You need to call this function at the end of rendering. 
         * Not calling it may leave the texture in an undefined state.
         */
        void display();

        /**
         * @brief clear render texture by color
         * 
         * @param color color for clearing
         */
        void clear(const Color &color = Color(0, 0, 0, 255));
    
    private:
        sf::RenderTexture render_texture_;  /// heart of class
        
    };
}