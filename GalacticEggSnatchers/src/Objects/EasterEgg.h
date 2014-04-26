#pragma once

#include <cstdint>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Graphics/IRenderable.h"
#include "Objects/IGameObject.h"
#include "Physics/Collisions/ICollidable.h"

namespace OBJECTS
{
    ////////////////////////////////////////////////////////
    /// @brief  An Easter egg.  Easter eggs are intended to be stationary objects that
    ///         are protected by Easter bunnies.  Aliens attempt to abduct Easter eggs.
    ///
    /// @todo   Remove the copy constructor and assignment operator if they aren't needed.
    ////////////////////////////////////////////////////////
    class EasterEgg : public IGameObject, public GRAPHICS::IRenderable, public PHYSICS::COLLISIONS::ICollidable
    {
    public:
        static const uint8_t DEFAULT_HEALTH;   ///< The default amount of health for an egg.
        
        /// @brief  Constructor.  Resources provided via the constructor
        ///         may be modified by this object during its lifetime.
        /// @param  sprite - The graphical sprite for this egg.
        explicit EasterEgg(const std::shared_ptr<sf::Sprite>& sprite);

        /// @brief      Copy constructor.
        /// @param[in]  eggToCopy - The egg to copy.
        EasterEgg(const EasterEgg& eggToCopy);

        /// @brief  Destructor.
        virtual ~EasterEgg();

        /// @brief      Assignment operator.
        /// @param[in]  rhsEgg - The egg on the right-hand side of the operator.
        /// @return     This egg with data copied from the provided egg.
        EasterEgg& operator= (const EasterEgg& rhsEgg);

        /// @copydoc    IGameObject::Update(const sf::Time& elapsedTime)
        virtual void Update(const sf::Time& elapsedTime);

        /// @copydoc    IRenderable::Render(sf::RenderTarget& renderTarget)
        virtual void Render(sf::RenderTarget& renderTarget);

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
        /// @brief      Does nothing for the egg.
        virtual void OnWorldBoundaryCollide();

        /// @brief  Gets the egg's current health.
        /// @return The egg's health.
        uint8_t GetHealth() const;
        
        /// @brief  Causes the egg to lose a unit of health.
        void LoseHealth();

    private:
        /// @brief      Helper method for copying.
        /// @param[in]  eggToCopy - The egg to copy.
        void Copy(const EasterEgg& eggToCopy);

        uint8_t m_health;  ///< The current health of the egg.
        std::shared_ptr<sf::Sprite> m_sprite;   ///< The egg's graphical sprite.
    };
}