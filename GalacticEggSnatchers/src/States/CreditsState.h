#pragma once

#include "States/IGameState.h"

namespace STATES
{
    ////////////////////////////////////////////////////////
    /// @brief  The state that displays the credits.
    ////////////////////////////////////////////////////////
    class CreditsState : public IGameState
    {
    public:
        /// @brief  Constructor.
        explicit CreditsState();

        /// @brief  Destructor.
        virtual ~CreditsState();

        /// @copydoc    IGameState::Update(const sf::Time& elapsedTime)
        virtual void Update(const sf::Time& elapsedTime);

        /// @copydoc    IGameState::Render(sf::RenderTarget& renderTarget)
        virtual void Render(sf::RenderTarget& renderTarget);

    private:
        CreditsState(const CreditsState& stateToCopy);    ///< Private to disallow copying.
        CreditsState& operator= (const CreditsState& rhsState);    ///< Private to disallow assignment.
    };
}