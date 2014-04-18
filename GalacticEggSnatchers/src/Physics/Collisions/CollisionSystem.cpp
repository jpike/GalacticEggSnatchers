#include "Physics/Collisions/CollisionSystem.h"

using namespace PHYSICS::COLLISIONS;

CollisionSystem::CollisionSystem()
{
    // Nothing to do.
}

CollisionSystem::~CollisionSystem()
{
    // Nothing to do.
}

bool CollisionSystem::HandleBoundaryCollisions(const sf::FloatRect& boundsInPixels, ICollidable& collidableObject) const
{
    // HANDLE COLLISIONS FOR THE OBJECT.
    // It is only expected that an object can exceed one of the boundaries at a time,
    // so we'll return after handling a collision with a single boundary.
    sf::FloatRect objectBoundingRectangle = collidableObject.GetBoundingRectangle();

    // Check for the top boundary being exceeded.
    bool objectExceededTopBounds = (objectBoundingRectangle.top < boundsInPixels.top);
    if (objectExceededTopBounds)
    {
        // Confine the object to within the top boundary.
        collidableObject.SetTopPosition(boundsInPixels.top);

        // Have the object perform any special handling it needs for colliding with the boundary.
        collidableObject.OnWorldBoundaryCollide();

        // A collision occurred.
        return true;
    }

    // Check for the bottom boundary being exceed.
    // For the bottom bounds, we need to calculate the bottom-most edge positions of the rectangles
    // since direct access to the bottom bounds do not exist.
    float objectRectangleBottomPosition = (objectBoundingRectangle.top + objectBoundingRectangle.height);
    float boundsBottomPosition = (boundsInPixels.top + boundsInPixels.height);
    bool objectExceededBottomBounds = (objectRectangleBottomPosition > boundsBottomPosition);
    if (objectExceededBottomBounds)
    {
        // Confine the object to within the bottom boundary.
        collidableObject.SetBottomPosition(boundsBottomPosition);

        // Have the object perform any special handling it needs for colliding with the boundary.
        collidableObject.OnWorldBoundaryCollide();

        // A collision occurred.
        return true;
    }

    // Check for the left boundary being exceeded.
    bool objectExceededLeftBounds = (objectBoundingRectangle.left < boundsInPixels.left);
    if (objectExceededLeftBounds)
    {
        // Confine the object to within the left boundary.
        collidableObject.SetLeftPosition(boundsInPixels.left);

        // Have the object perform any special handling it needs for colliding with the boundary.
        collidableObject.OnWorldBoundaryCollide();

        // A collision occurred.
        return true;
    }
    
    // Check for the right boundary being exceeded.
    // For the right bounds, we need to calculate the right-most edge positions of the rectangles
    // since direct access to the right bounds do not exist.
    float objectRectangleRightPosition = (objectBoundingRectangle.left + objectBoundingRectangle.width);
    float boundsRightPosition = (boundsInPixels.left + boundsInPixels.width);
    bool objectExceededRightBounds = (objectRectangleRightPosition > boundsRightPosition);
    if (objectExceededRightBounds)
    {
        // Confine the object to within the right boundary.
        collidableObject.SetRightPosition(boundsRightPosition);

        // Have the object perform any special handling it needs for colliding with the boundary.
        collidableObject.OnWorldBoundaryCollide();

        // A collision occurred.
        return true;
    }

    // NO COLLISION OCCURRED.
    return false;
}