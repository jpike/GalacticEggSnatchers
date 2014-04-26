#pragma once

#include <vector>
#include "Resources/ResourceManager.h"
#include "States/IGameState.h"

namespace STATES
{
    ////////////////////////////////////////////////////////
    /// @brief  The state that displays the credits.
    ////////////////////////////////////////////////////////
    class CreditsState : public IGameState
    {
    public:
        /// @brief      Constructor.
        /// @param[in]  screenBoundsInPixels - The boundaries of the screen.
        explicit CreditsState(const sf::FloatRect& screenBoundsInPixels);

        /// @brief  Destructor.
        virtual ~CreditsState();

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
        CreditsState(const CreditsState& stateToCopy);    ///< Private to disallow copying.
        CreditsState& operator= (const CreditsState& rhsState);    ///< Private to disallow assignment.

        /// @brief  Initializes the text displayed for the credits.
        void InitializeCreditsText();

        sf::FloatRect m_screenBoundsInPixels;   ///< The boundaries of the screen.
        RESOURCES::ResourceManager m_resourceManager;   ///< The resource manager.
        GameStateType m_nextGameState;  ///< The next game state that should follow when the user is done viewing credits.
        std::vector<sf::Text> m_contributors;    ///< The text displayed for contributors in the credits.
    };
}