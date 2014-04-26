#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

/// @brief  Code related to game states.
namespace STATES
{
    ////////////////////////////////////////////////////////
    /// @brief  Defines all of the different types of game states.
    ////////////////////////////////////////////////////////
    enum GameStateType
    {
        GAME_STATE_TYPE_INVALID = 0,    ///< An invalid type of game state.
        GAME_STATE_TYPE_TITLE = 1,  ///< The title screen state.
        GAME_STATE_TYPE_CREDITS = 2,    ///< The state for viewing credits.
        GAME_STATE_TYPE_HIGH_SCORES = 3,    ///< The state for viewing high scores.
        GAME_STATE_TYPE_GAMEPLAY = 4,   ///< The main gameplay state.
    };

    ////////////////////////////////////////////////////////
    /// @brief  An interface for different game states.
    ////////////////////////////////////////////////////////
    class IGameState
    {
    public:
        /// @brief  Virtual destructor to allow proper destruction of implementing classes.
        virtual ~IGameState() {};

        /// @brief  Gets the type of this game state.
        /// @return The type of this game state.
        virtual GameStateType GetStateType() const = 0;

        /// @brief  Gets the next state that should follow after this one.
        ///         Intended for use to allow external code to switch
        ///         to different states, if the current state indicates
        ///         if it is ready to move to a different state.
        /// @return The next state that should be switched to.
        virtual GameStateType GetNextState() const = 0;
        
        /// @brief      Updates the game state for the next frame of processing.
        /// @param[in]  elapsedTime - The elapsed time since the last iteration
        ///             of the main game loop.
        virtual void Update(const sf::Time& elapsedTime) = 0;

        /// @brief          Renders a frame for the current game state.
        /// @param[in,out]  renderTarget - The render target to render to.
        virtual void Render(sf::RenderTarget& renderTarget) = 0;

        /// @brief      Handles a key being pressed.
        /// @param[in]  key - The key that was pressed.
        virtual void HandleKeyPress(const sf::Keyboard::Key key) = 0;
    };
}