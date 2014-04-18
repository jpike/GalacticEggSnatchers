#pragma once

#include <cstdint>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Graphics/IRenderable.h"

namespace GRAPHICS
{
namespace GUI
{
    ////////////////////////////////////////////////////////
    /// @brief  A label for displaying the player's current score.
    ////////////////////////////////////////////////////////
    class ScoreLabel : public GRAPHICS::IRenderable
    {
    public:
        /// @brief      Constructor.
        /// @param[in]  textColor - The color for the label's text.
        /// @param[in]  font - The font for the label's text.
        explicit ScoreLabel(const sf::Color& textColor, const std::shared_ptr<sf::Font>& font);

        /// @brief  Destructor.
        virtual ~ScoreLabel();

        /// @copydoc    IRenderable::Render(sf::RenderTarget& renderTarget)
        virtual void Render(sf::RenderTarget& renderTarget);

        /// @brief      Sets the score displayed in the label.
        /// @param[in]  score - The score to display in the label.
        void SetScore(const uint16_t score);

        /// @brief      Sets the screen position of the label.
        /// @param[in]  screenXInPixels - The screen X position in pixels.
        /// @param[in]  screenYInPixels - The screen Y position in pixels.
        void SetPosition(const float screenXInPixels, const float screenYInPixels);

        /// @brief  Gets the width of the text.
        /// @return The width of the label text (in pixels).
        float GetTextWidthInPixels() const;

    private:
        ScoreLabel(const ScoreLabel& labelToCopy);  ///< Private to disallow copying.
        ScoreLabel& operator= (const ScoreLabel& rhsLabel); ///< Private to disallow assignment.

        sf::Text m_labelText;   ///< The text displayed in the label.
    };
}
}