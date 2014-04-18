#include <stdexcept>
#include "GalacticEggSnatchersGame.h"
#include "Graphics/IRenderable.h"
#include "Input/KeyboardController.h"
#include "Objects/AlienFactory.h"
#include "States/GameplayState.h"

using namespace STATES;

GameplayState::GameplayState(const sf::FloatRect& screenBoundsInPixels) :
    m_graphicsSystem(),
    m_screenBoundsInPixels(screenBoundsInPixels),
    m_collisionSystem(),
    m_playerController(),
    m_bunnyMissileFiringClock(),
    m_bunnyPlayer(),
    m_easterEggs(),
    m_aliens(),
    m_missiles(),
    m_explosions()
{
    // CREATE THE INITIAL OBJECTS FOR A NEW GAMEPLAY SESSION.
    m_playerController = std::make_shared<INPUT::KeyboardController>();
    m_bunnyPlayer = CreateInitialBunnyPlayer();
    m_easterEggs = CreateInitialEasterEggs();
    m_aliens = CreateInitialAliens();
}


GameplayState::~GameplayState()
{
    // Nothing else to do.
}

void GameplayState::Update(const sf::Time& elapsedTime)
{
    // HANDLE USER INPUT.
    HandleInput(*m_playerController, elapsedTime);

    // UPDATE THE MAIN GAME OBJECTS.
    UpdateGameObjects(elapsedTime);
    
    // HANDLE GAME OBJECT COLLISIONS.
    HandleGameObjectCollisions();

    // HANDLE COLLISIONS WITH THE SCREEN BOUNDARIES.
    HandleScreenBoundaryCollisions(m_screenBoundsInPixels);
}

void GameplayState::Render(sf::RenderTarget& renderTarget)
{
    RenderGameObjects(renderTarget);
}

std::shared_ptr<OBJECTS::EasterBunny> GameplayState::CreateInitialBunnyPlayer()
{
    // LOAD THE TEXTURE FOR THE BUNNY.
    const std::string BUNNY_TEXTURE_FILEPATH = "res/Images/bunny.png";
    std::shared_ptr<sf::Texture> bunnyTexture = m_graphicsSystem.GetTexture(BUNNY_TEXTURE_FILEPATH);
    bool bunnyTextureLoaded = (nullptr != bunnyTexture);
    if (!bunnyTextureLoaded)
    {
        throw std::runtime_error("Error loading bunny texture.");
    }

    // CREATE THE SPRITE FOR THE BUNNY.
    std::shared_ptr<sf::Sprite> bunnySprite = std::make_shared<sf::Sprite>(*bunnyTexture);
    
    // Set the initial position of the bunny sprite.
    float screenXCenter = (static_cast<float>(GalacticEggSnatchersGame::SCREEN_WIDTH_IN_PIXELS) / 2.0f);
    float bunnySpriteHalfWidth = (bunnySprite->getLocalBounds().width / 2.0f);
    float initialXScreenPosition = (screenXCenter - bunnySpriteHalfWidth);

    float screenYBottom = static_cast<float>(GalacticEggSnatchersGame::SCREEN_HEIGHT_IN_PIXELS);
    float twoSpritesAboveScreenBottom = (bunnySprite->getLocalBounds().height * 2.0f);
    float initialYScreenPosition = (screenYBottom - twoSpritesAboveScreenBottom);
        
    bunnySprite->setPosition(initialXScreenPosition, initialYScreenPosition);

    // CREATE THE BUNNY FOR THE PLAYER.
    std::shared_ptr<OBJECTS::EasterBunny> bunnyPlayer = std::make_shared<OBJECTS::EasterBunny>(bunnySprite);

    return bunnyPlayer;
}

std::vector< std::shared_ptr<OBJECTS::EasterEgg> > GameplayState::CreateInitialEasterEggs()
{
    // CREATE AN INITIAL NUMBER OF EASTER EGGS.
    const unsigned int INITIAL_EASTER_EGG_COUNT = 4;
    std::vector< std::shared_ptr<OBJECTS::EasterEgg> > initialEasterEggs;
    for (unsigned int currentEasterEggCount = 0; currentEasterEggCount < INITIAL_EASTER_EGG_COUNT; ++currentEasterEggCount)
    {
        // LOAD THE TEXTURE FOR THE EASTER EGG.
        /// @todo   If multiple Easter eggs are created, then we need to create some kind of factory to
        ///         load random eggs.
        const std::string EGG_TEXTURE_FILEPATH = "res/Images/easterEgg1.png";
        std::shared_ptr<sf::Texture> eggTexture = m_graphicsSystem.GetTexture(EGG_TEXTURE_FILEPATH);
        bool eggTextureLoaded = (nullptr != eggTexture);
        if (!eggTextureLoaded)
        {
            throw std::runtime_error("Error loading egg texture.");
        }

        // CREATE A SPRITE FOR THE EASTER EGG.
        std::shared_ptr<sf::Sprite> eggSprite = std::make_shared<sf::Sprite>(*eggTexture);

        // POSITION THE SPRITE.
        // It is positioned so that all eggs are equally spaced out along a horizontal line
        // across the screen (based on which "number" egg we are currently on out of the total).
        float spacesBetweenEggsCounts = static_cast<float>(INITIAL_EASTER_EGG_COUNT + 1);
        float eggCenterXPosition = 
            static_cast<float>(GalacticEggSnatchersGame::SCREEN_WIDTH_IN_PIXELS) /
            spacesBetweenEggsCounts *
            static_cast<float>(currentEasterEggCount + 1);
        float eggHalfWidth = (eggSprite->getLocalBounds().width / 2.0f);
        float eggLeftXPosition = (eggCenterXPosition - eggHalfWidth);

        float screenYBottom = static_cast<float>(GalacticEggSnatchersGame::SCREEN_HEIGHT_IN_PIXELS);
        float fourSpritesAboveScreenBottom = (eggSprite->getLocalBounds().height * 4.0f);
        float eggTopYPosition = (screenYBottom - fourSpritesAboveScreenBottom);

        eggSprite->setPosition(eggLeftXPosition, eggTopYPosition);

        // CREATE THE EASTER EGG.
        std::shared_ptr<OBJECTS::EasterEgg> easterEgg = std::make_shared<OBJECTS::EasterEgg>(eggSprite);
        initialEasterEggs.push_back(easterEgg);
    }

    return initialEasterEggs;
}

std::list< std::shared_ptr<OBJECTS::Alien> > GameplayState::CreateInitialAliens()
{
    // CREATE A 2D GRID OF ALIENS.
    // The number of aliens may be adjusted later depending on spacing/gameplay experience.
    const unsigned int ALIEN_ROW_COUNT = 5;
    const unsigned int ALIEN_COLUMN_COUNT = 6;
    std::list< std::shared_ptr<OBJECTS::Alien> > initialAliens;

    for (unsigned int currentAlienRow = 0; currentAlienRow < ALIEN_ROW_COUNT; ++currentAlienRow)
    {
        for (unsigned int currentAlienColumn = 0; currentAlienColumn < ALIEN_COLUMN_COUNT; ++currentAlienColumn)
        {
            // LOAD THE TEXTURE FOR THE ALIEN.
            // Select a random texture to provide variety during gameplay.
            std::string alienTextureFilepath = OBJECTS::AlienFactory::GetRandomAlienTextureFilepath();
            std::shared_ptr<sf::Texture> alienTexture = m_graphicsSystem.GetTexture(alienTextureFilepath);
            bool alienTextureLoaded = (nullptr != alienTexture);
            if (!alienTextureLoaded)
            {
                throw std::runtime_error("Error loading alien texture.");
            }

            // CREATE A SPRITE FOR THE ALIEN.
            std::shared_ptr<sf::Sprite> alienSprite = std::make_shared<sf::Sprite>(*alienTexture);

            // POSITION THE SPRITE.
            // The alien is positioned show that all aliens in the grid are uniformly spaced out.
            // Adjustments to positioning may be needed at a later date.

            // Aliens will be at least this certain amount down the screen to leave space
            // for the score and other GUI elements at the top.
            const float VerticalSpacingBetweenAliens = 8.0f;
            float alienHeightInPixels = alienSprite->getGlobalBounds().height;
            float minAlienYPosition = (alienHeightInPixels * 3.0f);
            float alienYPosition = (
                minAlienYPosition + 
                (VerticalSpacingBetweenAliens + alienHeightInPixels) * static_cast<float>(currentAlienRow));

            // The X position is calculated so that all aliens in a row are equally spaced out along a horizontal line
            // across the screen (based on which "column" of aliens we are currently on for the current row).
            float horizonalSpacingBetweenAliensCount = static_cast<float>(ALIEN_COLUMN_COUNT + 1);
            float alienCenterXPosition = 
                static_cast<float>(GalacticEggSnatchersGame::SCREEN_WIDTH_IN_PIXELS) /
                horizonalSpacingBetweenAliensCount *
                static_cast<float>(currentAlienColumn + 1);
            float alienHalfWidth = (alienSprite->getLocalBounds().width / 2.0f);
            float alienLeftXPosition = (alienCenterXPosition - alienHalfWidth);

            alienSprite->setPosition(alienLeftXPosition, alienYPosition);

            // LOAD THE ALIEN MISSILE TEXTURE.
            const std::string ALIEN_MISSILE_TEXTURE_FILEPATH = "res/Images/alienMissile1.png";
            std::shared_ptr<sf::Texture> alienMissileTexture = m_graphicsSystem.GetTexture(ALIEN_MISSILE_TEXTURE_FILEPATH);;
            bool alienMissileTextureLoaded = (nullptr != alienMissileTexture);
            if (!alienMissileTextureLoaded)
            {
                throw std::runtime_error("Error loading alien missile texture.");
            }

            // CREATE THE ALIEN.
            std::shared_ptr<OBJECTS::Alien> alien = std::make_shared<OBJECTS::Alien>(alienSprite, alienMissileTexture);
            initialAliens.push_back(alien);
        }
    }

    return initialAliens;
}

void GameplayState::HandleInput(const INPUT::IInputController& playerController, const sf::Time& elapsedTime)
{
    // CHECK IF MOVEMENT INPUT WAS PROVIDED.
    bool leftButtonPressed = playerController.LeftButtonPressed();
    bool rightButtonPressed = playerController.RightButtonPressed();
    // We don't want to move the bunny if both (opposite) direction buttons are pressed.
    bool onlyLeftButtonPressed = (leftButtonPressed && !rightButtonPressed);
    bool onlyRightButtonPressed = (rightButtonPressed && !leftButtonPressed);

    if (onlyLeftButtonPressed)
    {
        m_bunnyPlayer->MoveLeft(elapsedTime);
    }
    else if (onlyRightButtonPressed)
    {
        m_bunnyPlayer->MoveRight(elapsedTime);
    }

    // CHECK IF FIRING INPUT WAS PROVIDED.
    if (playerController.FireButtonPressed())
    {
        // CHECK IF SUFFICIENT TIME HAS PASSED BETWEEN THE LAST TIME A BUNNY FIRED A MISSILE.
        // We don't want the player to be able to fire missiles too quickly.
        const float TIME_DELAY_BETWEEN_BUNNY_MISSILE_FIRING_IN_SECONDS = 0.5f;
        sf::Time elapsedTimeSinceLastBunnyMissileFired = m_bunnyMissileFiringClock.getElapsedTime();
        float elapsedTimeSinceLastBunnyMissileFiredInSeconds = elapsedTimeSinceLastBunnyMissileFired.asSeconds();
        bool bunnyMissileFiringTimeDelayExceeded = (elapsedTimeSinceLastBunnyMissileFiredInSeconds > TIME_DELAY_BETWEEN_BUNNY_MISSILE_FIRING_IN_SECONDS);
        if (!bunnyMissileFiringTimeDelayExceeded)
        {
            // Don't fire a missile since enough time hasn't passed yet.
            return;
        }

        // LOAD THE CARROT MISSILE TEXTURE.
        const std::string CARROT_MISSILE_TEXTURE_FILEPATH = "res/Images/carrot.png";
        std::shared_ptr<sf::Texture> carrotMissileTexture = m_graphicsSystem.GetTexture(CARROT_MISSILE_TEXTURE_FILEPATH);;
        bool carrotMissileTextureLoaded = (nullptr != carrotMissileTexture);
        if (!carrotMissileTextureLoaded)
        {
            throw std::runtime_error("Error loading carrot missile texture.");
        }

        // CREATE THE SPRITE FOR THE MISSILE.
        std::shared_ptr<sf::Sprite> carrotMissileSprite = std::make_shared<sf::Sprite>(*carrotMissileTexture);

        // CREATE THE BUNNY'S MISSILE.
        std::shared_ptr<OBJECTS::WEAPONS::Missile> missile = m_bunnyPlayer->FireMissile(carrotMissileSprite);
        m_missiles.push_back(missile);

        // RESET THE CLOCK TRACKING WHEN THE BUNNY FIRED A MISSILE.
        // This will allow another missile to be fired after sufficient time passes.
        m_bunnyMissileFiringClock.restart();
    }
}

void GameplayState::UpdateGameObjects(const sf::Time& elapsedTime)
{    
    // UPDATE ANY EXPLOSIONS.
    // We don't automatically increment the iterator during the for loop because we may need to
    // erase from the container during the loop for explosions that have expired.
    for (auto explosion = m_explosions.begin(); explosion != m_explosions.end(); )
    {
        (*explosion)->Update(elapsedTime);

        // Remove the explosion if it has exceeded its lifetime.
        bool explosionLifetimeExceeded = (*explosion)->LifetimeExceeded();
        if (explosionLifetimeExceeded)
        {
            explosion = m_explosions.erase(explosion);
        }
        else
        {
            ++explosion;
        }
    }
    
    // UPDATE THE PLAYER BUNNY.
    m_bunnyPlayer->Update(elapsedTime);

    // UPDATE THE EASTER EGGS.
    for (std::shared_ptr<OBJECTS::EasterEgg>& easterEgg : m_easterEggs)
    {
        easterEgg->Update(elapsedTime);
    }

    // UPDATE THE ALIENS.
    for (std::shared_ptr<OBJECTS::Alien>& alien : m_aliens)
    {
        alien->Update(elapsedTime);

        // Check if the alien wants to fire a missile.
        if (alien->WantsToFireMissile())
        {
            // Fire an alien missile.
            std::shared_ptr<OBJECTS::WEAPONS::Missile> alienMissile = alien->FireMissile();
            m_missiles.push_back(alienMissile);
        }
    }

    // UPDATE THE MISSILES.
    for (std::shared_ptr<OBJECTS::WEAPONS::Missile>& missile : m_missiles)
    {
        missile->Update(elapsedTime);
    }
}

void GameplayState::HandleGameObjectCollisions()
{
    // CHECK FOR COLLISIONS WITH MISSILES.
    // We don't automatically increment the iterator during the for loop because we may need to
    // erase from the container during the loop for missiles that collide with objects.
    for (auto missile = m_missiles.begin(); missile != m_missiles.end();)
    {
        // HANDLE THE MISSILE DIFFERENTLY DEPENDING ON WHAT TYPE OF OBJECT FIRED IT.
        bool missileCollided = false;
        sf::FloatRect collidedObjectRectangle;
        OBJECTS::WEAPONS::MissileSource missileSource = (*missile)->GetMissileSource();
        switch (missileSource)
        {
        case OBJECTS::WEAPONS::MISSILE_SOURCE_ALIEN:
            missileCollided = HandleAlienMissileCollisions(**missile, collidedObjectRectangle);
            break;
        case OBJECTS::WEAPONS::MISSILE_SOURCE_EASTER_BUNNY:
            missileCollided = HandleBunnyMissileCollisions(**missile, collidedObjectRectangle);
            break;
        default:
            // This case is never expected, but if we receive a missile of a different
            // type, we don't have anything to do for it.
            break;
        }

        // CHECK IF THE MISSILE COLLIDED.
        if (missileCollided)
        {
            // GENERATE AN EXPLOSION AT THE LOCATION OF THE MISSILE.
            // Load the explosion texture.
            const std::string EXPLOSION_TEXTURE_FILEPATH = "res/Images/explosion1.png";
            std::shared_ptr<sf::Texture> explosionTexture = m_graphicsSystem.GetTexture(EXPLOSION_TEXTURE_FILEPATH);;
            bool explosionTextureLoaded = (nullptr != explosionTexture);
            if (!explosionTextureLoaded)
            {
                throw std::runtime_error("Error loading explosion texture.");
            }

            // Create the sprite for the explosion.
            std::shared_ptr<sf::Sprite> explosionSprite = std::make_shared<sf::Sprite>(*explosionTexture);
            sf::FloatRect missileBounds = (*missile)->GetBoundingRectangle();
            explosionSprite->setPosition(collidedObjectRectangle.left, collidedObjectRectangle.top);

            // Create the explosion.
            std::shared_ptr<OBJECTS::Explosion> explosion = std::make_shared<OBJECTS::Explosion>(explosionSprite);
            m_explosions.push_back(explosion);

            // REMOVE THE MISSILE SINCE IT HAS EXPLODED.
            missile = m_missiles.erase(missile);
        }
        else
        {
            // Move to the checking collisions for the next missile.
            ++missile;
        }
    }
}

bool GameplayState::HandleAlienMissileCollisions(const OBJECTS::WEAPONS::Missile& missile,  sf::FloatRect& collidedObjectRectangle)
{
    // VERIFY THAT THE MISSILE CAME FROM AN ALIEN.
    bool missileFromAlien = (OBJECTS::WEAPONS::MISSILE_SOURCE_ALIEN == missile.GetMissileSource());
    if (!missileFromAlien)
    {
        // We don't want to check for collisions with the provided missile.
        return false;
    }

    /// @todo CHECK IF THE MISSILE COLLIDED WITH ANY EASTER EGGS.

    // CHECK IF THE MISSILE COLLIDED WITH THE EASTER BUNNY.
    sf::FloatRect missileBounds = missile.GetBoundingRectangle();
    sf::FloatRect bunnyBounds = m_bunnyPlayer->GetBoundingRectangle();
    bool missileHitBunny = missileBounds.intersects(bunnyBounds);
    if (missileHitBunny)
    {
        collidedObjectRectangle = bunnyBounds;
    }

    return missileHitBunny;
}

bool GameplayState::HandleBunnyMissileCollisions(const OBJECTS::WEAPONS::Missile& missile, sf::FloatRect& collidedObjectRectangle)
{
    // VERIFY THAT THE MISSILE CAME FROM A BUNNY.
    bool missileFromBunny = (OBJECTS::WEAPONS::MISSILE_SOURCE_EASTER_BUNNY == missile.GetMissileSource());
    if (!missileFromBunny)
    {
        // We don't want to check for collisions with the provided missile.
        return false;
    }

    // CHECK IF THE MISSILE COLLIDED WITH ANY ALIENS.
    sf::FloatRect missileBounds = missile.GetBoundingRectangle();
    // We don't automatically increment the iterator during the for loop because we may need to
    // erase from the container during the loop for aliens that were hit.
    for (auto alien = m_aliens.begin(); alien != m_aliens.end();)
    {
        // Check if the missile hit the current alien.
        sf::FloatRect alienBounds = (*alien)->GetBoundingRectangle();
        bool missileHitAlien = missileBounds.intersects(alienBounds);
        if (missileHitAlien)
        {            
            // Get the bounding rectangle of the collided alien.
            collidedObjectRectangle = alienBounds;
            
            // Remove the alien itself so that it is no longer updated.
            alien = m_aliens.erase(alien);
            return true;
        }
        else
        {
            // Move to the checking collisions for the next alien.
            ++alien;
        }
    }

    // NO COLLISIONS OCCURRED.
    return false;
}

void GameplayState::HandleScreenBoundaryCollisions(const sf::FloatRect& screenBoundsInPixels)
{
    // HANDLE COLLISIONS FOR THE BUNNY.
    // The return value is intentionally ignored since we don't need to perform
    // any additional response if the bunny hit the screen boundaries.
    m_collisionSystem.HandleBoundaryCollisions(screenBoundsInPixels, *m_bunnyPlayer);

    // HANDLE COLLISIONS FOR THE ALIENS.
    for (auto alien = m_aliens.begin(); alien != m_aliens.end(); ++alien)
    {
        // The return value is intentionally ignored since we don't need to perform
        // any additional response if the bunny hit the screen boundaries.
        m_collisionSystem.HandleBoundaryCollisions(screenBoundsInPixels, **alien);
    }

    // HANDLE COLLISIONS FOR THE MISSILES.
    // We don't automatically increment the iterator during the for loop because we may need to
    // erase from the container during the loop for missiles that hit the screen boundaries.
    for (auto missile = m_missiles.begin(); missile != m_missiles.end();)
    {
        bool missileHitScreenBoundary = m_collisionSystem.HandleBoundaryCollisions(screenBoundsInPixels, **missile);

        // Check if the missile went off screen.
        if (missileHitScreenBoundary)
        {            
            // Remove the missile itself so that it is no longer updated.
            missile = m_missiles.erase(missile);
        }
        else
        {
            // Move to the checking collisions for the next missile.
            ++missile;
        }
    }

    // No other game objects (easter eggs, etc.) need to have collisions with the screen
    // boundaries handled since they don't move.
}

void GameplayState::RenderGameObjects(sf::RenderTarget& renderTarget)
{
    // Note that the rendering order here is intentionally chosen for
    // what hopefully makes the most sense in terms of layering objects
    // on top of one another.

    // RENDER THE EASTER EGGS.
    for (std::shared_ptr<OBJECTS::EasterEgg> easterEgg : m_easterEggs)
    {
        easterEgg->Render(renderTarget);
    }

    // RENDER THE ALIENS.
    for (std::shared_ptr<OBJECTS::Alien> alien : m_aliens)
    {
        alien->Render(renderTarget);
    }

    // RENDER THE BUNNY PLAYER.
    m_bunnyPlayer->Render(renderTarget);

    // RENDER THE MISSILES.
    for (std::shared_ptr<OBJECTS::WEAPONS::Missile> missile : m_missiles)
    {
        missile->Render(renderTarget);
    }

    // RENDER THE EXPLOSIONS.
    for (std::shared_ptr<OBJECTS::Explosion> explosion : m_explosions)
    {
        explosion->Render(renderTarget);
    }
}