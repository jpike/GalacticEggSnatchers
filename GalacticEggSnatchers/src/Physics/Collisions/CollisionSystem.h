#pragma once

#include <SFML/Graphics.hpp>
#include "Physics/Collisions/ICollidable.h"

namespace PHYSICS
{
namespace COLLISIONS
{
    ////////////////////////////////////////////////////////
    /// @brief  A responsible responsible for managing collisions
    ///         between collidable objects.
    ////////////////////////////////////////////////////////
    class CollisionSystem
    {
    public:
        /// @brief  Constructor.
        explicit CollisionSystem();

        /// @brief  Destructor.
        ~CollisionSystem();

        /// @brief          Handles boundary collisions for a collidable object, restricting it to be within
        ///                 the provided boundaries.  An object is only expected to exceed one of the
        ///                 boundaries of the provided rectangle, so the object's bounding rectangle
        ///                 should be smaller that than of the provided boundaries.
        /// @param[in]      boundsInPixels - The boundaries for which to confine the object.
        /// @param[in,out]  collidableObject - The object for which to handle boundary collisions.
        void HandleBoundaryCollisions(const sf::FloatRect& boundsInPixels, ICollidable& collidableObject);

    private:
        CollisionSystem(const CollisionSystem& systemToCopy);   ///< Private to disallow copying.
        CollisionSystem& operator= (const CollisionSystem& collisionSystem);    ///< Private to disallow assignment.
    };
}
}