#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

/// @brief  Code related to game states.
namespace STATES
{
    ////////////////////////////////////////////////////////
    /// @brief  An interface for different game states.
    ////////////////////////////////////////////////////////
    class IGameState
    {
    public:
        /// @brief  Virtual destructor to allow proper destruction of implementing classes.
        virtual ~IGameState() {};

        /// @brief      Updates the game state for the next frame of processing.
        /// @param[in]  elapsedTime - The elapsed time since the last iteration
        ///             of the main game loop.
        virtual void Update(const sf::Time& elapsedTime) = 0;

        /// @brief          Renders a frame for the current game state.
        /// @param[in,out]  renderTarget - The render target to render to.
        virtual void Render(sf::RenderTarget& renderTarget) = 0;
    };
}