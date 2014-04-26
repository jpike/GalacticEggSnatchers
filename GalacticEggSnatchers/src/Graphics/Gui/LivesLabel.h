#pragma once

#include <cstdint>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Graphics/IRenderable.h"

namespace GRAPHICS
{
/// @brief  Code related to GUI components.
namespace GUI
{
    ////////////////////////////////////////////////////////
    /// @brief  A label for displaying the lives of a player.
    ////////////////////////////////////////////////////////
    class LivesLabel : public GRAPHICS::IRenderable
    {
    public:
        /// @brief      Constructor.
        /// @param[in]  fontSizeInPixels - The size of the font in pixels.
        /// @param[in]  textColor - The color for the label's text.
        /// @param[in]  font - The font for the label's text.
        explicit LivesLabel(
            const unsigned int fontSizeInPixels, 
            const sf::Color& textColor, 
            const std::shared_ptr<sf::Font>& font);

        /// @brief  Destructor.
        virtual ~LivesLabel();

        /// @copydoc    IRenderable::Render(sf::RenderTarget& renderTarget)
        virtual void Render(sf::RenderTarget& renderTarget);

        /// @brief      Sets the number of lives displayed in the label.
        /// @param[in]  livesCount - The number of lives to display in the label.
        void SetLivesCount(const uint8_t livesCount);

        /// @brief      Sets the screen position of the label.
        /// @param[in]  screenXInPixels - The screen X position in pixels.
        /// @param[in]  screenYInPixels - The screen Y position in pixels.
        void SetPosition(const float screenXInPixels, const float screenYInPixels);

    private:
        LivesLabel(const LivesLabel& labelToCopy);  ///< Private to disallow copying.
        LivesLabel& operator= (const LivesLabel& rhsLabel); ///< Private to disallow assignment.

        sf::Text m_labelText;   ///< The text displayed in the label.
    };
}
}