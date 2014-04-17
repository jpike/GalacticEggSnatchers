#pragma once

#include <SFML/Graphics.hpp>

namespace GRAPHICS
{
    ////////////////////////////////////////////////////////
    /// @brief  An interface for renderable objects.
    ////////////////////////////////////////////////////////
    class IRenderable
    {
    public:
        /// @brief  Virtual destructor to ensure proper destruction of implementing classes.
        virtual ~IRenderable() {};

        /// @brief          Renders a frame for the object.
        /// @param[in,out]  renderTarget - The render target to render to.
        virtual void Render(sf::RenderTarget& renderTarget) = 0;
    };
}