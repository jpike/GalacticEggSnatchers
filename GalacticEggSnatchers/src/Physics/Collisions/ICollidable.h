#pragma once

#include <SFML/Graphics.hpp>

/// @brief  Code related to physics.
namespace PHYSICS
{
/// @brief  Code related to collisions.
namespace COLLISIONS
{
    ////////////////////////////////////////////////////////
    /// @brief  An interface for collidable objects.
    ////////////////////////////////////////////////////////
    class ICollidable
    {
    public:
        /// @brief  Virtual destructor to ensure proper destruction of implementing classes.
        virtual ~ICollidable() {};

        /// @brief      Returns the bounding rectangle of the object, in screen coordinates.
        /// @return     The bounding rectangle of the object on the screen (in pixels).
        virtual sf::FloatRect GetBoundingRectangle() const = 0;

        /// @brief      Sets the top position of the object, in screen coordinates.
        /// @param[in]  topPositionInPixels - The top position of the object (in pixels).
        virtual void SetTopPosition(const float topPositionInPixels) = 0;

        /// @brief      Sets the bottom position of the object, in screen coordinates.
        /// @param[in]  bottomPositionInPixels - The bottom position of the object (in pixels).
        virtual void SetBottomPosition(const float bottomPositionInPixels) = 0;

        /// @brief      Sets the left position of the object, in screen coordinates.
        /// @param[in]  leftPositionInPixels - The left position of the object (in pixels).
        virtual void SetLeftPosition(const float leftPositionInPixels) = 0;

        /// @brief      Sets the right position of the object, in screen coordinates.
        /// @param[in]  rightPositionInPixels - The right position of the object (in pixels).
        virtual void SetRightPosition(float rightPositionInPixels) = 0;

        /// @brief      Handles responses to the object colliding with a world (screen) boundary.
        ///             The specific world boundary that was collided with is not provided to this
        ///             method because this method is intended to be called after the collision
        ///             system has already adjusted the object's bounding rectangle for the
        ///             boundary collision.
        virtual void OnWorldBoundaryCollide() = 0;
    };
}
}