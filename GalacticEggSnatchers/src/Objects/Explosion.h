#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Graphics/IRenderable.h"
#include "Objects/IGameObject.h"

namespace OBJECTS
{
    ////////////////////////////////////////////////////////
    /// @brief  An explosion that occurs when a missile hits another object.
    ////////////////////////////////////////////////////////
    class Explosion : public IGameObject, public GRAPHICS::IRenderable
    {
    public:
        static const float MAX_LIFETIME_IN_SECONDS; ///< The maximum lifetime of an explosion.
        
        /// @brief      Constructor.
        /// @param[in]  sprite - The graphical sprite to use for the explosion.
        explicit Explosion(const std::shared_ptr<sf::Sprite>& sprite);

        /// @brief  Destructor.
        ~Explosion();

        /// @copydoc    IGameObject::Update(const sf::Time& elapsedTime)
        virtual void Update(const sf::Time& elapsedTime);

        /// @copydoc    IRenderable::Render(sf::RenderTarget& renderTarget)
        virtual void Render(sf::RenderTarget& renderTarget);

        /// @brief  Checks if this explosion's lifetime has been exceeded.
        /// @return True if this explosion's lifetime has ended; false otherwise.
        bool LifetimeExceeded() const;

    private:
        Explosion(const Explosion& explosionToCopy);    ///< Private to disallow copying.
        Explosion& operator= (const Explosion& rhsExplosion);   ///< Private to disallow assignment.

        sf::Time m_lifetime;    ///< The time this explosion has been alive.
        std::shared_ptr<sf::Sprite> m_sprite;   ///< The graphical sprite for the explosion.
    };
}