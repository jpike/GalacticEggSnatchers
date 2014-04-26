#pragma once

#include "Graphics/Gui/HighScoreLabel.h"
#include "Graphics/Gui/LivesLabel.h"
#include "Graphics/Gui/ScoreLabel.h"
#include "Graphics/IRenderable.h"

namespace GRAPHICS
{
namespace GUI
{
    ////////////////////////////////////////////////////////
    /// @brief  The heads-up-display (HUD) displayed during main gameplay.
    ////////////////////////////////////////////////////////
    class GameplayHud : public GRAPHICS::IRenderable
    {
    public:
        static const unsigned int DEFAULT_FONT_SIZE_IN_PIXELS;  ///< The default font size for text in the hud.
        static const sf::Color DEFAULT_TEXT_COLOR;  ///< The default color for text in the hud.
        
        /// @brief      Constructor.
        /// @param[in]  screenBoundsInPixels - The bounding rectangle of the screen.
        /// @param[in]  textFont - The font to use for text in the HUD.
        explicit GameplayHud(const sf::FloatRect& screenBoundsInPixels, const std::shared_ptr<sf::Font>& textFont);

        /// @brief  Destructor.
        virtual ~GameplayHud();

        /// @copydoc    IRenderable::Render(sf::RenderTarget& renderTarget)
        virtual void Render(sf::RenderTarget& renderTarget);

        /// @brief      Sets the number of lives displayed in the HUD.
        /// @param[in]  livesCount - The number of lives to display in the HUD.
        void SetLivesCount(const uint8_t livesCount);

        /// @brief      Sets the current score displayed in the HUD.
        /// @param[in]  score - The current score to display in the HUD.
        void SetScore(const uint16_t score);

        /// @brief      Sets the high score displayed in the HUD.
        /// @param[in]  highScore - The high score to display in the HUD.
        void SetHighScore(const uint16_t highScore);

    private:
        GameplayHud(const GameplayHud& hudToCopy);  ///< Private to disallow copying.
        GameplayHud& operator= (const GameplayHud& rhsHud); ///< Private to disallow assignment.

        /// @brief      Positions the labels according to the screen bounds.
        /// @param[in]  screenBoundsInPixels - The bounding rectangle of the screen.
        void PositionLabels(const sf::FloatRect& screenBoundsInPixels);

        LivesLabel m_livesLabel;    ///< The label displaying the player's lives.
        ScoreLabel m_scoreLabel;    ///< The label displaying the current score.
        HighScoreLabel m_highScoreLabel;    ///< The label displaying the all-time high score.
    };
}
}