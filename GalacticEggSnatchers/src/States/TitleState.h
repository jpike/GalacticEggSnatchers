#pragma once

#include <unordered_map>
#include <vector>
#include <SFML/Window.hpp>
#include "Resources/ResourceManager.h"
#include "States/IGameState.h"

namespace STATES
{
    ////////////////////////////////////////////////////////
    /// @brief  The state that displays the title screen.
    ////////////////////////////////////////////////////////
    class TitleState : public IGameState
    {
    public:
        /// @brief      Constructor.
        /// @param[in]  title - The title to display on the screen.
        /// @param[in]  screenBoundsInPixels - The boundaries of the screen.
        explicit TitleState(
            const std::string& title,
            const sf::FloatRect& screenBoundsInPixels);

        /// @brief  Destructor.
        virtual ~TitleState();

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
        TitleState(const TitleState& stateToCopy);    ///< Private to disallow copying.
        TitleState& operator= (const TitleState& rhsState);    ///< Private to disallow assignment.

        /// @brief      Initializes the title label, giving it the proper text, formatting, and position.
        /// @param[in]  title - The title of the game to display in the label.
        void InitializeTitleLabel(const std::string& title);

        /// @brief  Initializes the menu options displayed on the title screen.
        void InitializeMenuOptions();

        sf::FloatRect m_screenBoundsInPixels;   ///< The boundaries of the screen.
        RESOURCES::ResourceManager m_resourceManager;   ///< The resource manager.
        sf::Text m_titleLabel;  ///< The label for the title.
        std::vector<sf::Text> m_menuOptions; ///< The menu options on the title screen.
        std::unordered_map<sf::Keyboard::Key, GameStateType> m_menuKeyToNextGameStateMap;   ///< Maps pressed keyboard keys to the next game state from menu options.
        GameStateType m_nextGameState;  ///< The next game state that should follow after selecting a menu option on the title screen.
    };
}