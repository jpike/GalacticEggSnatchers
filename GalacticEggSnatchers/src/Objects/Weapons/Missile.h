#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Objects/IGameObject.h"

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
    class Missile : public IGameObject
    {
    public:
        /// @brief      Constructor.  Resources provided via the constructor
        ///             may be modified by this object during its lifetime.
        /// @param[in]  initialPosition - The initial position of the missile.
        /// @param[in]  velocity - The velocity of the missile.
        /// @param      sprite - The graphical sprite for this missile.
        explicit Missile(
            const MissileSource source,
            const sf::Vector2f& initialPosition,
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

    private:
        /// @brief      Helper method for copying.
        /// @param[in]  missileToCopy - The missile to copy.
        void Copy(const Missile& missileToCopy);

        sf::Vector2f m_velocity;    ///< The missile's velocity.
        std::shared_ptr<sf::Sprite> m_sprite;   ///< The missile's graphical sprite.
    };
}
}