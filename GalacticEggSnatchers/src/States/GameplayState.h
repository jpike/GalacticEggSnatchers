#pragma once

#include <list>
#include <memory>
#include <vector>
#include "Graphics/Gui/GameplayHud.h"
#include "Graphics/GraphicsSystem.h"
#include "Input/IInputController.h"
#include "Objects/AllObjects.h"
#include "Physics/Collisions/CollisionSystem.h"
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
        static const uint16_t DEFAULT_ALIEN_KILL_POINTS;    ///< The default number of points awarded for killing an alien.
        
        /// @brief      Constructor.
        /// @param[in]  screenBoundsInPixels - The boundaries of the screen for which to confine game objects.
        explicit GameplayState(const sf::FloatRect& screenBoundsInPixels);

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

        /// @brief  Initializes the gameplay HUD.
        void InitializeHud();

        /// @brief      Handles input for the player for a single update frame.
        /// @param[in]  playerController - The controller supplying input for the player.
        /// @param[in]  elapsedTime - The elapsed time since the last frame of updating.
        void HandleInput(const INPUT::IInputController& playerController, const sf::Time& elapsedTime);

        /// @brief      Updates all of the game objects in this state for a single update frame.
        /// @param[in]  elapsedTime - The elapsed time since the last frame of updating.
        void UpdateGameObjects(const sf::Time& elapsedTime);

        /// @brief  Handles collisions between game objects.
        void HandleGameObjectCollisions();
        
        /// @brief          Handles collisions of the provided alien-sourced missile with any non-alien game objects.
        /// @param[in]      missile - The missile, assumed to have been fired by an alien, for which to handle collisions.
        /// @param[in,out]  collidedObjectRectangle - The bounding rectangle of the collided object, if any.
        /// @return         True if the missile collided with anything; false otherwise.
        bool HandleAlienMissileCollisions(const OBJECTS::WEAPONS::Missile& missile, sf::FloatRect& collidedObjectRectangle);

        /// @brief          Handles collisions of the provided bunny-sourced missile with any alien game objects.
        /// @param[in]      missile - The missile, assumed to have been fired by the bunny, for which to handle collisions.
        /// @param[in,out]  collidedObjectRectangle - The bounding rectangle of the collided object, if any.
        /// @return         True if the missile collided with anything; false otherwise.
        bool HandleBunnyMissileCollisions(const OBJECTS::WEAPONS::Missile& missile, sf::FloatRect& collidedObjectRectangle);

        /// @brief      Handles screen boundary collisions for game objects in this state.
        /// @param[in]  screenBoundsInPixels - The boundaries of the screen for which to confine game objects.
        void HandleScreenBoundaryCollisions(const sf::FloatRect& screenBoundsInPixels);

        /// @brief          Renders all renderable game objects on the provided render target.
        /// @param[in,out]  renderTarget - The render target to render to.
        void RenderGameObjects(sf::RenderTarget& renderTarget);

        /// @brief      Adds points to the score.
        /// @param[in]  pointsToAdd - The number of points to add to the current score.
        void AddToScore(const uint16_t pointsToAdd);

        // GRAPHICS MEMBER VARIABLES.
        GRAPHICS::GraphicsSystem m_graphicsSystem;  ///< The system that handles graphics resources.
        std::shared_ptr<GRAPHICS::GUI::GameplayHud> m_gameplayHud;   ///< The HUD for the gameplay state.
        
        // COLLISION MEMBER VARIABLES.
        sf::FloatRect m_screenBoundsInPixels;   ///< The boundaries of the screen for which to confine game objects.
        PHYSICS::COLLISIONS::CollisionSystem m_collisionSystem; ///< The system that handles collisions.

        // INPUT MEMBER VARIABLES.
        std::shared_ptr<INPUT::IInputController> m_playerController;    ///< The controller supplying input for the player.
        sf::Clock m_bunnyMissileFiringClock;    ///< A clock for tracking how much time passes between the bunny firing a missile.

        // GAMEPLAY STATISTICS.
        uint16_t m_currentScore;    ///< The player's current score.
        uint16_t m_highScore;   ///< The all-time high score.

        // GAME OBJECT MEMBER VARIABLES.
        std::shared_ptr<OBJECTS::EasterBunny> m_bunnyPlayer;    ///< The Easter bunny controlled by the player.
        std::vector< std::shared_ptr<OBJECTS::EasterEgg> > m_easterEggs;    ///< The Easter eggs to be protected by the player.
        std::list< std::shared_ptr<OBJECTS::Alien> > m_aliens;  ///< The enemy aliens attempting to abduct Easter eggs.
        std::list< std::shared_ptr<OBJECTS::WEAPONS::Missile> > m_missiles;  ///< The missiles fired by the player or enemies.
        std::list< std::shared_ptr<OBJECTS::Explosion> > m_explosions;    ///< Explosions created from missile collisions.
    };
}