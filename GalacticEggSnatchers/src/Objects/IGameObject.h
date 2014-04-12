#pragma once

#include <SFML/System.hpp>

/// @brief  Code related to game objects.
namespace OBJECTS
{
    ////////////////////////////////////////////////////////
    /// @brief  An interface for different game objects.
    ////////////////////////////////////////////////////////
    class IGameObject
    {
    public:
        /// @brief  Virtual destructor to allow proper destruction of implementing classes.
        virtual ~IGameObject() {};

        /// @brief      Updates the game object for the next frame of processing.
        /// @param[in]  elapsedTime - The elapsed time since the last iteration
        ///             of the main game loop.
        virtual void Update(const sf::Time& elapsedTime) = 0;
    };
}