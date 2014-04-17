#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Graphics/IRenderable.h"
#include "Objects/IGameObject.h"
#include "Physics/Collisions/ICollidable.h"

namespace OBJECTS
{
/// @brief  Code related to weapon game objects.
namespace WEAPONS
{
    ////////////////////////////////////////////////////////
    /// @brief  Defines the possible sources of a missile.
    ////////////////////////////////////////////////////////
    enum MissileSource
    {
        MISSILE_SOURCE_INVALID = 0, ///< An invalid missile source.
        MISSILE_SOURCE_EASTER_BUNNY = 1,    ///< The missile was fired by an Easter bunny.
        MISSILE_SOURCE_ALIEN = 2    ///< The missile was fired by an alien.
    };
    
    ////////////////////////////////////////////////////////
    /// @brief  A missile that can be fired by an object in the game.
    ///         Missiles travel in a single direction until colliding
    ///         with another object (resulting in an explosion) or
    ///         going off screen.
    ///
    /// @todo   Remove the copy constructor and assignment operator if they aren't needed.
    ////////////////////////////////////////////////////////
    class Missile : public IGameObject, public PHYSICS::COLLISIONS::ICollidable, public GRAPHICS::IRenderable
    {
    public:
        /// @brief      Constructor.  Resources provided via the constructor
        ///             may be modified by this object during its lifetime.
        /// @param[in]  source - The source of missile.
        /// @param[in]  velocity - The velocity of the missile (in pixels per second).
        /// @param      sprite - The graphical sprite for this missile.
        explicit Missile(
            const MissileSource source,
            const sf::Vector2f& velocity,
            const std::shared_ptr<sf::Sprite>& sprite);

        /// @brief      Copy constructor.
        /// @param[in]  missileToCopy - The missile to copy.
        Missile(const Missile& missileToCopy);

        /// @brief  Destructor.
        virtual ~Missile();

        /// @brief      Assignment operator.
        /// @param[in]  rhsMissile - The missile on the right-hand side of the operator.
        /// @return     This missile with data copied from the provided missile.
        Missile& operator= (const Missile& rhsMissile);

        /// @copydoc    IGameObject::Update(const sf::Time& elapsedTime)
        virtual void Update(const sf::Time& elapsedTime);

        /// @copydoc    ICollidable::GetBoundingRectangle() const
        virtual sf::FloatRect GetBoundingRectangle() const;

        /// @copydoc    ICollidable::SetTopPosition(const float topPositionInPixels)
        virtual void SetTopPosition(const float topPositionInPixels);

        /// @copydoc    ICollidable::SetBottomPosition(const float bottomPositionInPixels)
        virtual void SetBottomPosition(const float bottomPositionInPixels);

        /// @copydoc    ICollidable::SetLeftPosition(const float leftPositionInPixels)
        virtual void SetLeftPosition(const float leftPositionInPixels);

        /// @copydoc    ICollidable::SetRightPosition(const float rightPositionInPixels)
        virtual void SetRightPosition(float rightPositionInPixels);

        /// @copydoc    ICollidable::OnWorldBoundaryCollide()
        virtual void OnWorldBoundaryCollide();

        /// @copydoc    IRenderable::Render(sf::RenderTarget& renderTarget)
        virtual void Render(sf::RenderTarget& renderTarget);

    private:
        /// @brief      Helper method for copying.
        /// @param[in]  missileToCopy - The missile to copy.
        void Copy(const Missile& missileToCopy);

        MissileSource m_source; ///< The missile's source.
        sf::Vector2f m_velocity;    ///< The missile's velocity (in pixels per second).
        std::shared_ptr<sf::Sprite> m_sprite;   ///< The missile's graphical sprite.
    };
}
}