#pragma once

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Graphics/IRenderable.h"
#include "Objects/IGameObject.h"

namespace OBJECTS
{
    ////////////////////////////////////////////////////////
    /// @brief  An enemy alien.  Aliens fire down toward the
    ///         player in an attempt to defeat the player
    ///         and abduct Easter eggs.
    ///
    /// @todo   Remove the copy constructor and assignment operator if they aren't needed.
    ////////////////////////////////////////////////////////
    class Alien : public IGameObject, public GRAPHICS::IRenderable
    {
    public:
        /// @brief  Constructor.  Resources provided via the constructor
        ///         may be modified by this object during its lifetime.
        /// @param  sprite - The graphical sprite for this alien.
        explicit Alien(const std::shared_ptr<sf::Sprite>& sprite);

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

    private:
        /// @brief      Helper method for copying.
        /// @param[in]  alienToCopy - The alien to copy.
        void Copy(const Alien& alienToCopy);

        std::shared_ptr<sf::Sprite> m_sprite;   ///< The alien's graphical sprite.
    };
}