#pragma once

#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ArtificialIntelligence/AlienAiBrain.h"
#include "Graphics/IRenderable.h"
#include "Objects/IGameObject.h"
#include "Objects/Weapons/Missile.h"
#include "Physics/Collisions/ICollidable.h"

namespace OBJECTS
{
    ////////////////////////////////////////////////////////
    /// @brief  An enemy alien.  Aliens fire down toward the
    ///         player in an attempt to defeat the player
    ///         and abduct Easter eggs.
    ///
    /// @todo   Remove the copy constructor and assignment operator if they aren't needed.
    ////////////////////////////////////////////////////////
    class Alien : public IGameObject, public GRAPHICS::IRenderable, public PHYSICS::COLLISIONS::ICollidable
    {
    public:
        /// @brief  The movement speed of an alien in pixels for second.
        ///         The actual value has been determined based on experimentation to
        ///         decide what feels right and what would help balance the gameplay.
        static const float MOVE_SPEED_IN_PIXELS_PER_SECOND;
        
        /// @brief  Constructor.  Resources provided via the constructor
        ///         may be modified by this object during its lifetime.
        /// @param  sprite - The graphical sprite for this alien.
        /// @param  missileTexture - The texture for missiles fired by this alien.
        /// @param  missileSound - The sound to play for missiles fired by this alien.
        explicit Alien(
            const std::shared_ptr<sf::Sprite>& sprite, 
            const std::shared_ptr<sf::Texture>& missileTexture,
            const std::shared_ptr<sf::SoundBuffer>& missileSound);

        /// @brief      Copy constructor.
        /// @param[in]  alienToCopy - The alien to copy.
        Alien(const Alien& alienToCopy);

        /// @brief  Destructor.
        virtual ~Alien();

        /// @brief      Assignment operator.
        /// @param[in]  rhsAlien - The alien on the right-hand side of the operator.
        /// @return     This alien with data copied from the provided alien.
        Alien& operator= (const Alien& rhsAlien);

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
        /// @brief      Does nothing for the bunny.
        virtual void OnWorldBoundaryCollide();

        /// @brief  Determines whether this alien desires firing a missile.
        /// @return True if the alien wants to fire a missile; false otherwise.
        bool WantsToFireMissile();

        /// @brief  Has the alien fire a missile.
        /// @return The newly fired missile from the alien.
        std::shared_ptr<WEAPONS::Missile> FireMissile() const;

    private:
        /// @brief      Helper method for copying.
        /// @param[in]  alienToCopy - The alien to copy.
        void Copy(const Alien& alienToCopy);

        std::shared_ptr<sf::Sprite> m_sprite;   ///< The alien's graphical sprite.
        sf::Vector2f m_velocity;    ///< The current velocity of the alien.
        ARTIFICIAL_INTELLIGENCE::AlienAiBrain m_brain;  ///< The AI brain of the alien.
        std::shared_ptr<sf::Texture> m_missileTexture;  ///< The texture for missiles fired by this alien.
        std::shared_ptr<sf::SoundBuffer> m_missileSoundBuffer;  ///< The sound to play for missiles fired by this alien.
    };
}