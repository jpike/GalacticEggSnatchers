#pragma once

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
        explicit HighScoresState();

        /// @brief  Destructor.
        virtual ~HighScoresState();

        /// @copydoc    IGameState::Update(const sf::Time& elapsedTime)
        virtual void Update(const sf::Time& elapsedTime);

        /// @copydoc    IGameState::Render(sf::RenderTarget& renderTarget)
        virtual void Render(sf::RenderTarget& renderTarget);

    private:
        HighScoresState(const HighScoresState& stateToCopy);    ///< Private to disallow copying.
        HighScoresState& operator= (const HighScoresState& rhsState);    ///< Private to disallow assignment.
    };
}