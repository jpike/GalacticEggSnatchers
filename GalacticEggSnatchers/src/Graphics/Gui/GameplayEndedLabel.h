#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Graphics/IRenderable.h"

namespace GRAPHICS
{
/// @brief  Code related to GUI components.
namespace GUI
{
    ////////////////////////////////////////////////////////
    /// @brief  A label for displaying either a win or loss message to the player.
    ///         Smaller instruction text that cannot be changed is also displayed
    ///         below the main message.
    ///         It must be explicitly made visible before it can be rendered.
    ////////////////////////////////////////////////////////
    class GameplayEndedLabel : public GRAPHICS::IRenderable
    {
    public:
        /// @brief      Constructor.
        /// @param[in]  screenBoundsInPixels - The boundaries of the screen, in pixels.
        /// @param[in]  textColor - The color for the label's text.
        /// @param[in]  font - The font for the label's text.
        explicit GameplayEndedLabel(
            const sf::FloatRect& screenBoundsInPixels,
            const sf::Color& textColor, 
            const std::shared_ptr<sf::Font>& font);

        /// @brief  Destructor.
        virtual ~GameplayEndedLabel();

        /// @copydoc    IRenderable::Render(sf::RenderTarget& renderTarget)
        virtual void Render(sf::RenderTarget& renderTarget);

        /// @brief  Returns whether or not the label is visible for rendering.
        /// @return The visibility of the label.
        bool IsVisible() const;

        /// @brief      Sets the visibility of the label.
        /// @param[in]  visibility - True to make visible; false to make invisible.
        void SetVisible(bool visibility);

        /// @brief      Sets the text for the main message of the label.
        /// @param[in]  mainMessageText - The new main message text of the label.
        void SetText(const std::string& mainMessageText);

    private:
        GameplayEndedLabel(const GameplayEndedLabel& labelToCopy);  ///< Private to disallow copying.
        GameplayEndedLabel& operator= (const GameplayEndedLabel& rhsLabel); ///< Private to disallow assignment.

        /// @brief  Sets the position of the main message text to ensure
        ///         that it is in its proper position on screen.
        void SetMainMessageTextPosition();

        /// @brief  Sets the position of the secondary instruction text to ensure
        ///         that it is in its proper position on screen.
        void SetSecondaryInstructionTextPosition();

        sf::FloatRect m_screenBoundsInPixels;   ///< The boundaries of the screen (in pixels).
        bool m_isVisible;   ///< Whether or not the label is visible.
        sf::Text m_mainMessageText;   ///< The main message displayed in the label.
        sf::Text m_secondaryInstructionText;    ///< Secondary instruction text displayed in the label.
    };
}
}