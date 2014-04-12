#pragma once

#include "States/IGameState.h"

namespace STATES
{
    ////////////////////////////////////////////////////////
    /// @brief  The state that displays the title screen.
    ////////////////////////////////////////////////////////
    class TitleState : public IGameState
    {
    public:
        /// @brief  Constructor.
        explicit TitleState();

        /// @brief  Destructor.
        virtual ~TitleState();

        /// @copydoc    IGameState::Update(const sf::Time& elapsedTime)
        virtual void Update(const sf::Time& elapsedTime);

        /// @copydoc    IGameState::Render(sf::RenderTarget& renderTarget)
        virtual void Render(sf::RenderTarget& renderTarget);

    private:
        TitleState(const TitleState& stateToCopy);    ///< Private to disallow copying.
        TitleState& operator= (const TitleState& rhsState);    ///< Private to disallow assignment.
    };
}