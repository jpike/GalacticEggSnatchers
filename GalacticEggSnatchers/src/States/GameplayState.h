#pragma once

#include <list>
#include <memory>
#include <vector>
#include "Objects/AllObjects.h"
#include "States/IGameState.h"

namespace STATES
{
    ////////////////////////////////////////////////////////
    /// @brief  The main gameplay state of the Galactic Egg Snatchers game.
    ///         This state has the player (an Easter bunny) defending
    ///         eggs from abduction by alien invaders.
    ////////////////////////////////////////////////////////
    class GameplayState : public IGameState
    {
    public:
        /// @brief  Constructor.
        explicit GameplayState();

        /// @brief  Destructor.
        virtual ~GameplayState();

        /// @copydoc    IGameState::Update(const sf::Time& elapsedTime)
        virtual void Update(const sf::Time& elapsedTime);

        /// @copydoc    IGameState::Render(sf::RenderTarget& renderTarget)
        virtual void Render(sf::RenderTarget& renderTarget);

    private:
        GameplayState(const GameplayState& stateToCopy);    ///< Private to disallow copying.
        GameplayState& operator= (const GameplayState& rhsState);    ///< Private to disallow assignment.

        /// @todo   Rethink the return values fo the "Create" helper methods below
        ///         because they also generate sprites within the m_sprites list.

        /// @brief  Creates the initial Easter bunny for the player.
        /// @return The player Easter bunny in its initial state for a new gameplay session.
        std::shared_ptr<OBJECTS::EasterBunny> CreateInitialBunnyPlayer();
        /// @brief  Creates the initial Easter eggs.
        /// @return The Easter eggs in their initial state for a new gameplay session.
        std::vector< std::shared_ptr<OBJECTS::EasterEgg> > CreateInitialEasterEggs();
        /// @brief  Creates the initial enemy aliens.
        /// @return The aliens in their initial state for a new gameplay session.
        std::list< std::shared_ptr<OBJECTS::Alien> > CreateInitialAliens();

        std::shared_ptr<OBJECTS::EasterBunny> m_bunnyPlayer;    ///< The Easter bunny controlled by the player.
        std::vector< std::shared_ptr<OBJECTS::EasterEgg> > m_easterEggs;    ///< The Easter eggs to be protected by the player.
        std::list< std::shared_ptr<OBJECTS::Alien> > m_aliens;  ///< The enemy aliens attempting to abduct Easter eggs.
        std::list< std::shared_ptr<OBJECTS::WEAPONS::Missile> > m_missiles;  ///< The missiles fired by the player or enemies.

        std::list< std::shared_ptr<sf::Sprite> > m_sprites;   ///< All sprites to be rendered by this state.
        std::list< std::shared_ptr<sf::Texture> > m_textures;   ///< Stores texture data for sprites.  @todo Rethink how this texture data is managed.
    };
}