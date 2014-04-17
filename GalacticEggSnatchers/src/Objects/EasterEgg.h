#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Graphics/IRenderable.h"
#include "Objects/IGameObject.h"

namespace OBJECTS
{
    ////////////////////////////////////////////////////////
    /// @brief  An Easter egg.  Easter eggs are intended to be stationary objects that
    ///         are protected by Easter bunnies.  Aliens attempt to abduct Easter eggs.
    ///
    /// @todo   Remove the copy constructor and assignment operator if they aren't needed.
    ////////////////////////////////////////////////////////
    class EasterEgg : public IGameObject, public GRAPHICS::IRenderable
    {
    public:
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

    private:
        /// @brief      Helper method for copying.
        /// @param[in]  eggToCopy - The egg to copy.
        void Copy(const EasterEgg& eggToCopy);

        std::shared_ptr<sf::Sprite> m_sprite;   ///< The egg's graphical sprite.
    };
}