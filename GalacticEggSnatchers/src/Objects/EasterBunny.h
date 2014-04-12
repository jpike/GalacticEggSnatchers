#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Input/IInputController.h"
#include "Objects/IGameObject.h"

namespace OBJECTS
{
    ////////////////////////////////////////////////////////
    /// @brief  An Easter bunny.  The input controller provided upon construction
    ///         determines how the bunny is controlled (i.e. by a player using
    ///         an input device or by some other method).
    ///
    /// @todo   Remove the copy constructor and assignment operator if they aren't needed.
    ////////////////////////////////////////////////////////
    class EasterBunny : public IGameObject
    {
    public:
        /// @brief  Constructor.  Resources provided via the constructor
        ///         may be modified by this object during its lifetime.
        /// @param  sprite - The graphical sprite for this bunny.
        /// @param  inputController - The controller supplying input to control this bunny.
        explicit EasterBunny(
            const std::shared_ptr<sf::Sprite>& sprite, 
            const std::shared_ptr<INPUT::IInputController>& inputController);

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

    private:
        /// @brief      Helper method for copying.
        /// @param[in]  bunnyToCopy - The bunny to copy.
        void Copy(const EasterBunny& bunnyToCopy);

        std::shared_ptr<sf::Sprite> m_sprite;   ///< The bunny's graphical sprite.
        std::shared_ptr<INPUT::IInputController> m_inputController; ///< The controller supplying input.
    };
}