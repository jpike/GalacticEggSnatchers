#pragma once

#include <vector>
#include "Resources/ResourceManager.h"
#include "SaveData/HighScores.h"
#include "States/IGameState.h"

namespace STATES
{
    ////////////////////////////////////////////////////////
    /// @brief  The state that displays all of the high scores.
    ////////////////////////////////////////////////////////
    class HighScoresState : public IGameState
    {
    public:
        /// @brief  Constructor.
        /// @param[in]  screenBoundsInPixels - The boundaries of the screen.
        explicit HighScoresState(const sf::FloatRect& screenBoundsInPixels);

        /// @brief  Destructor.
        virtual ~HighScoresState();

        /// @copydoc    IGameState::GetStateType() const
        virtual GameStateType GetStateType() const;

        /// @copydoc    IGameState::GetNextState() const
        virtual GameStateType GetNextState() const;

        /// @copydoc    IGameState::Update(const sf::Time& elapsedTime)
        virtual void Update(const sf::Time& elapsedTime);

        /// @copydoc    IGameState::Render(sf::RenderTarget& renderTarget)
        virtual void Render(sf::RenderTarget& renderTarget);

        /// @copydoc    IGameState::HandleKeyPress(const sf::Keyboard::Key key)
        virtual void HandleKeyPress(const sf::Keyboard::Key key);

    private:
        HighScoresState(const HighScoresState& stateToCopy);    ///< Private to disallow copying.
        HighScoresState& operator= (const HighScoresState& rhsState);    ///< Private to disallow assignment.

        /// @brief  Loads high scores for this state.
        /// @return A collection of the high scores.
        SAVE_DATA::HighScores LoadHighScores() const;

        /// @brief      Initializes the high score text displayed on screen.
        /// @param[in]  highScores - The high scores to display.
        void InitializeHighScoresText(SAVE_DATA::HighScores& highScores);

        sf::FloatRect m_screenBoundsInPixels;   ///< The boundaries of the screen.
        RESOURCES::ResourceManager m_resourceManager;   ///< The resource manager.
        GameStateType m_nextGameState;  ///< The next game state that should follow when the user is done viewing high scores.
        sf::Text m_highScoresTitle; ///< A title displayed on the screen to identify that high scores are displayed.
        std::vector<sf::Text> m_highScores; ///< The high scores displayed on screen.
    };
}