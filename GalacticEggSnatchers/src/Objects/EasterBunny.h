#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Objects/IGameObject.h"
#include "Objects/Weapons/Missile.h"
#include "Physics/Collisions/ICollidable.h"

namespace OBJECTS
{
    ////////////////////////////////////////////////////////
    /// @brief  An Easter bunny.  Intended to be controlled (by external code)
    ///         by a player for moving and firing missiles at invading aliens.
    ///
    /// @todo   Remove the copy constructor and assignment operator if they aren't needed.
    ////////////////////////////////////////////////////////
    class EasterBunny : public IGameObject, public PHYSICS::COLLISIONS::ICollidable
    {
    public:
        /// @brief  The movement speed of the bunny in pixels for second.
        ///         The actual value has been determined based on experimentation to
        ///         decide what feels right and what would help balance the gameplay.
        static const float MOVE_SPEED_IN_PIXELS_PER_SECOND;
        
        /// @brief  Constructor.  Resources provided via the constructor
        ///         may be modified by this object during its lifetime.
        /// @param  sprite - The graphical sprite for this bunny.
        explicit EasterBunny(const std::shared_ptr<sf::Sprite>& sprite);

        /// @brief      Copy constructor.
        /// @param[in]  bunnyToCopy - The bunny to copy.
        EasterBunny(const EasterBunny& bunnyToCopy);

        /// @brief  Destructor.
        virtual ~EasterBunny();

        /// @brief      Assignment operator.
        /// @param[in]  rhsBunny - The bunny on the right-hand side of the operator.
        /// @return     This bunny with data copied from the provided bunny.
        EasterBunny& operator= (const EasterBunny& rhsBunny);

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
        /// @brief      Does nothing for the bunny.
        virtual void OnWorldBoundaryCollide();

        /// @brief      Moves the bunny left based on the amount of elapsed time.
        /// @param[in]  elapsedTime - The amount of time to move the bunny, intended
        ///             to be the elapsed time since the last update frame.
        void MoveLeft(const sf::Time& elapsedTime);

        /// @brief      Moves the bunny right based on the amount of elapsed time.
        /// @param[in]  elapsedTime - The amount of time to move the bunny, intended
        ///             to be the elapsed time since the last update frame.
        void MoveRight(const sf::Time& elapsedTime);

        /// @brief      Has the bunny fire a missile.
        /// @return     The newly fired missile from the bunny.
        std::shared_ptr<OBJECTS::WEAPONS::Missile> FireMissile();

    private:
        /// @brief      Helper method for copying.
        /// @param[in]  bunnyToCopy - The bunny to copy.
        void Copy(const EasterBunny& bunnyToCopy);

        std::shared_ptr<sf::Sprite> m_sprite;   ///< The bunny's graphical sprite.
    };
}