#include <chrono>
#include <fstream>
#include <random>
#include <stdexcept>
#include "GalacticEggSnatchersGame.h"
#include "Graphics/IRenderable.h"
#include "Input/KeyboardController.h"
#include "Objects/AlienFactory.h"
#include "Objects/EasterEggFactory.h"
#include "States/GameplayState.h"
#include <iostream>

using namespace STATES;

// STATIC CONSTANT INITIALIZATION.
const uint16_t GameplayState::DEFAULT_ALIEN_KILL_POINTS = 100;
const uint16_t GameplayState::MAX_HIGH_SCORE = 65500;

// INSTANCE METHODS.

GameplayState::GameplayState(const sf::FloatRect& screenBoundsInPixels) :
    m_resourceManager(),
    m_gameplayHud(),
    m_screenBoundsInPixels(screenBoundsInPixels),
    m_collisionSystem(),
    m_playerController(),
    m_bunnyMissileFiringClock(),
    m_nextMainState(GAME_STATE_TYPE_INVALID),
    m_currentSubState(PLAYING_GAME_SUBSTATE),
    m_currentScore(0),
    m_highScore(0),
    m_highScores(),
    m_alienParameters(),
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
    m_aliens = CreateInitialAliens(m_alienParameters);

    // LOAD THE HIGH SCORES.
    LoadHighScores();

    // INITIALIZE THE HUD.
    InitializeHud();
}


GameplayState::~GameplayState()
{
    // Nothing else to do.
}

GameStateType GameplayState::GetStateType() const
{
    return GAME_STATE_TYPE_GAMEPLAY;
}

GameStateType GameplayState::GetNextState() const
{    
    return m_nextMainState;
}

void GameplayState::Update(const sf::Time& elapsedTime)
{
    // UPDATE THE GAME ONLY IF MAIN GAMEPLAY IS GOING ON.
    // This will "freeze" the game when the player has won or lost.
    // Updates for handling the win/lost sub-states are elsewhere.
    bool gameplayOccurring = (PLAYING_GAME_SUBSTATE == m_currentSubState);
    if (gameplayOccurring)
    {
        // HANDLE USER INPUT.
        HandleInput(*m_playerController, elapsedTime);

        // UPDATE THE MAIN GAME OBJECTS.
        UpdateGameObjects(elapsedTime);
    
        // HANDLE GAME OBJECT COLLISIONS.
        HandleGameObjectCollisions();

        // HANDLE COLLISIONS WITH THE SCREEN BOUNDARIES.
        HandleScreenBoundaryCollisions(m_screenBoundsInPixels);

        // SPAWN A NEW WAVE OF ALIENS IF THEY ARE ALMOST ALL GONE.
        // This helps keep the game going and make it more fun with increasing difficulty.
        // We don't spawn a new wave if zero aliens remain.  If the player
        // has managed to do that in-between updates, congratulations!
        // Therefore, exactly one alien is require for spawning a new wave.
        const unsigned int REMAINING_ALIENS_TO_TRIGGER_NEW_WAVE = 1;
        bool moreAliensNeeded = (REMAINING_ALIENS_TO_TRIGGER_NEW_WAVE == m_aliens.size());
        if (moreAliensNeeded)
        {
            SpawnAlienWave();
        }

        // UPDATE THE HUD.
        /// @todo Scores are updated elsewhere, but maybe they should be updated here?
        m_gameplayHud->SetLivesCount(m_bunnyPlayer->GetLives());
    }

    // UPDATE THE SUB-STATE OF THE GAME TO DETECT WIN/LOSS CONDITIONS.
    UpdateSubState();
}

void GameplayState::Render(sf::RenderTarget& renderTarget)
{
    RenderGameObjects(renderTarget);
    m_gameplayHud->Render(renderTarget);
}

void GameplayState::HandleKeyPress(const sf::Keyboard::Key key)
{
    // CHECK IF THE GAMEPLAY HAS ENDED.
    bool playerWon = (VICTORY_SUBSTATE == m_currentSubState);
    bool playerLost = (GAME_OVER_SUBSTATE == m_currentSubState);
    bool gameplayEnded = (playerWon || playerLost);
    if (gameplayEnded)
    {
        // CHECK IF AN APPROPRIATE KEY WAS PRESSED.
        // We restrict the key pressed to just the Enter key for returning
        // to the title screen to avoid having to handle the issue of the player
        // still pressing the game controls as soon as the game ends.
        // This could obviously be handled in a better way.
        bool enterKeyPressed = (sf::Keyboard::Return == key);
        if (enterKeyPressed)
        {
            // Have the game return to the title screen since the gameplay
            // has ended and the user has pressed an appropriate key.
            m_nextMainState = GAME_STATE_TYPE_TITLE;

            // Save the updated set of high scores.
            SaveHighScores();
        }
    }
}

std::shared_ptr<OBJECTS::EasterBunny> GameplayState::CreateInitialBunnyPlayer()
{
    // LOAD THE TEXTURE FOR THE BUNNY.
    const std::string BUNNY_TEXTURE_FILEPATH = "res/Images/bunny.png";
    std::shared_ptr<sf::Texture> bunnyTexture = m_resourceManager.GetTexture(BUNNY_TEXTURE_FILEPATH);
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
        const std::string EGG_TEXTURE_FILEPATH = OBJECTS::EasterEggFactory::GetRandomEggTextureFilepath();
        std::shared_ptr<sf::Texture> eggTexture = m_resourceManager.GetTexture(EGG_TEXTURE_FILEPATH);
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

std::list< std::shared_ptr<OBJECTS::Alien> > GameplayState::CreateInitialAliens(const AlienDifficultyParameters& alienParameters)
{
    // LOAD THE MISSILE SOUND DATA FOR ALIENS.
    const std::string MISSILE_SOUND_FILEPATH = "res/Sounds/MissileLaunch.wav";
    std::shared_ptr<sf::SoundBuffer> missileSoundBuffer = m_resourceManager.GetSoundBuffer(MISSILE_SOUND_FILEPATH);
    bool missileSoundBufferLoaded = (nullptr != missileSoundBuffer);
    if (!missileSoundBufferLoaded)
    {
        throw std::runtime_error("Error loading missile sound.");
    }
    
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
            std::shared_ptr<sf::Texture> alienTexture = m_resourceManager.GetTexture(alienTextureFilepath);
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
            std::shared_ptr<sf::Texture> alienMissileTexture = m_resourceManager.GetTexture(ALIEN_MISSILE_TEXTURE_FILEPATH);;
            bool alienMissileTextureLoaded = (nullptr != alienMissileTexture);
            if (!alienMissileTextureLoaded)
            {
                throw std::runtime_error("Error loading alien missile texture.");
            }

            // CREATE THE ALIEN.
            // Note that std::make_shared is not used here simply because Visual Studio 2012
            // doesn't seem to have a version that supports more than 5 arguments.
            std::shared_ptr<OBJECTS::Alien> alien(new OBJECTS::Alien(
                alienParameters.MinTimeBetweenMissileFiresInSeconds,
                alienParameters.MaxTimeBetweenMissileFiresInSeconds,
                alienParameters.HorizontalMoveSpeedInPixelsPerSecond,
                alienSprite, 
                alienMissileTexture,
                missileSoundBuffer) );
            initialAliens.push_back(alien);
        }
    }

    return initialAliens;
}

void GameplayState::SpawnAlienWave()
{
    // INCREASE THE ALIEN DIFFICULTY PARAMETERS.
    // First try decreasing the minimum frequency of alien missile fires.
    bool minMissileFiringTimeCanDecrease = (
        m_alienParameters.MinTimeBetweenMissileFiresInSeconds > AlienDifficultyParameters::MIN_TIME_BETWEEN_MISSILE_FIRES_IN_SECONDS);
    if (minMissileFiringTimeCanDecrease)
    {
        // Make the new aliens potentially fire missiles more frequently.
        m_alienParameters.MinTimeBetweenMissileFiresInSeconds--;
        std::list< std::shared_ptr<OBJECTS::Alien> > newAliens = CreateInitialAliens(m_alienParameters);
        m_aliens.insert(m_aliens.end(), newAliens.begin(), newAliens.end());
        return;
    }

    // Next try decreasing the maximum frequency of alien missile fires.
    // An absolute "minimum" for the missile fire max time decreases is specified
    // to provide more variety in difficulty increases (high chance of the player
    // encountering speed increases later in this function).
    const unsigned int MINIMUM_MAX_TIME_BETWEEN_MISSILE_FIRES_IN_SECONDS = 30;
    bool maxMissileFiringTimeCanDecrease = (
        m_alienParameters.MaxTimeBetweenMissileFiresInSeconds > m_alienParameters.MinTimeBetweenMissileFiresInSeconds &&
        m_alienParameters.MaxTimeBetweenMissileFiresInSeconds > MINIMUM_MAX_TIME_BETWEEN_MISSILE_FIRES_IN_SECONDS);
    if (maxMissileFiringTimeCanDecrease)
    {
        // Make the new aliens potentially fire missiles more frequently.
        const unsigned int MISSILE_FIRE_MAX_TIME_DECREASE_PER_WAVE = 4;
        m_alienParameters.MaxTimeBetweenMissileFiresInSeconds -= MISSILE_FIRE_MAX_TIME_DECREASE_PER_WAVE;
        std::list< std::shared_ptr<OBJECTS::Alien> > newAliens = CreateInitialAliens(m_alienParameters);
        m_aliens.insert(m_aliens.end(), newAliens.begin(), newAliens.end());
        return;
    }

    // Next try increasing the speed of the aliens.
    // It is restricted to halfway across the screen to avoid having them move too fast.
    float screenHalfWidth = m_screenBoundsInPixels.width / 2.0f;
    bool alienSpeedCanIncrease = (
        m_alienParameters.HorizontalMoveSpeedInPixelsPerSecond < screenHalfWidth);
    if (alienSpeedCanIncrease)
    {
        // Make the new aliens move faster.
        const float ALIEN_SPEED_INCREASE_PER_WAVE = 4.0f;
        m_alienParameters.HorizontalMoveSpeedInPixelsPerSecond += ALIEN_SPEED_INCREASE_PER_WAVE;
        std::list< std::shared_ptr<OBJECTS::Alien> > newAliens = CreateInitialAliens(m_alienParameters);
        m_aliens.insert(m_aliens.end(), newAliens.begin(), newAliens.end());
        return;
    }
}

void GameplayState::LoadHighScores()
{   
    // OPEN THE HIGH SCORES FILE.
    const std::string HIGH_SCORES_FILEPATH = "res/highScores.txt";
    std::ifstream highScoresFile(HIGH_SCORES_FILEPATH, std::ios_base::in);
    if (highScoresFile.is_open())
    {
        // READ IN EACH HIGH SCORE.
        unsigned int highScoresCount = 0;
        while (highScoresFile.good())
        {
            // READ THE NEXT HIGH SCORE FROM THE FILE.
            uint16_t highScore = 0;
            highScoresFile >> highScore;
            
            // CHECK IF THERE IS ROOM FOR ANOTHER HIGH SCORE.
            bool roomForAnotherHighScore = (highScoresCount < SAVE_DATA::HighScores::MAX_HIGH_SCORES_COUNT);
            if (roomForAnotherHighScore)
            {
                highScoresCount++;
                m_highScores.AddHighScore(highScore);
            }
            else
            {
                // Stop reading high scores.
                break;
            }
        }

        // CLOSE THE OPEN FILE.
        highScoresFile.close();
    }

    // GET THE TOP HIGH SCORE FOR THE GAME.
    std::array<uint16_t, SAVE_DATA::HighScores::MAX_HIGH_SCORES_COUNT> sortedHighScores = 
        m_highScores.GetHighScoresInDescendingOrder();
    m_highScore = sortedHighScores.front();
}

void GameplayState::InitializeHud()
{
    // LOAD THE FONT RESOURCE.
    std::shared_ptr<sf::Font> hudFont = m_resourceManager.GetFont("res/Fonts/Minecraftia.ttf");
    bool fontLoaded = (nullptr != hudFont);
    if (!fontLoaded)
    {
        throw std::runtime_error("Error loading HUD font.");
    }

    // INITIALIZE THE GAMEPLAY HUD.
    m_gameplayHud = std::make_shared<GRAPHICS::GUI::GameplayHud>(m_screenBoundsInPixels, hudFont);
    m_gameplayHud->SetHighScore(m_highScore);
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
        std::shared_ptr<sf::Texture> carrotMissileTexture = m_resourceManager.GetTexture(CARROT_MISSILE_TEXTURE_FILEPATH);;
        bool carrotMissileTextureLoaded = (nullptr != carrotMissileTexture);
        if (!carrotMissileTextureLoaded)
        {
            throw std::runtime_error("Error loading carrot missile texture.");
        }

        // CREATE THE SPRITE FOR THE MISSILE.
        std::shared_ptr<sf::Sprite> carrotMissileSprite = std::make_shared<sf::Sprite>(*carrotMissileTexture);

        // LOAD THE MISSILE SOUND DATA.
        const std::string MISSILE_SOUND_FILEPATH = "res/Sounds/MissileLaunch.wav";
        std::shared_ptr<sf::SoundBuffer> missileSoundBuffer = m_resourceManager.GetSoundBuffer(MISSILE_SOUND_FILEPATH);
        bool missileSoundBufferLoaded = (nullptr != missileSoundBuffer);
        if (!missileSoundBufferLoaded)
        {
            throw std::runtime_error("Error loading missile sound.");
        }

        // CREATE THE SOUND FOR THE MISSILE.
        std::shared_ptr<sf::Sound> missileSound = std::make_shared<sf::Sound>(*missileSoundBuffer);

        // CREATE THE BUNNY'S MISSILE.
        std::shared_ptr<OBJECTS::WEAPONS::Missile> missile = m_bunnyPlayer->FireMissile(carrotMissileSprite, missileSound);
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
    // INITIALIZE A RANDOM NUMBER GENERATOR FOR RANDOMLY ROTATING EXPLOSION SPRITES.
    /// @todo Refactor this randomness logic to a more central location.
    // The random number generator variables are static to ensure randomness over multiple calls to this function.
    static bool randomNumberGeneratorInitialized = false;
    static std::default_random_engine randomNumberGenerator;
    if (!randomNumberGeneratorInitialized)
    {
        // Initialize the random number generator with a seed based on the current time.
        unsigned long seed = static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count());
        randomNumberGenerator.seed(seed);

        randomNumberGeneratorInitialized = true;
    }
    
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
            std::shared_ptr<sf::Texture> explosionTexture = m_resourceManager.GetTexture(EXPLOSION_TEXTURE_FILEPATH);;
            bool explosionTextureLoaded = (nullptr != explosionTexture);
            if (!explosionTextureLoaded)
            {
                throw std::runtime_error("Error loading explosion texture.");
            }

            // Create the sprite for the explosion.
            std::shared_ptr<sf::Sprite> explosionSprite = std::make_shared<sf::Sprite>(*explosionTexture);
            // Set the origin for transformations to the center of the sprite to make rotation work properly.
            sf::FloatRect explosionBounds = explosionSprite->getLocalBounds();
            float explosionHalfWidth = explosionBounds.width / 2.0f;
            float explosionCenterX = explosionBounds.left + explosionHalfWidth;
            float explosionHalfHeight = explosionBounds.height / 2.0f;
            float explosionCenterY = explosionBounds.top + explosionHalfHeight;
            explosionSprite->setOrigin(explosionCenterX, explosionCenterY);

            // Rotate the explosion by a random amount to add more variety.
            /// @todo Refactor this randomness logic to a more central location.
            const unsigned int MAX_ROTATION_IN_DEGREES = 360;
            unsigned int randomRotationInDegrees = ( randomNumberGenerator() % MAX_ROTATION_IN_DEGREES );
            explosionSprite->setRotation(static_cast<float>(randomRotationInDegrees));

            // Position the explosion to correspond with the position of the collided object.
            // Since we needed to set the origin of the explosion to the center (as opposed to top-left)
            // for rotation, we need to calculate the center of the object's bounding box.
            float collidedObjectHalfWidth = collidedObjectRectangle.width / 2.0f;
            float collidedObjectCenterX = collidedObjectRectangle.left + collidedObjectHalfWidth;
            float collidedObjectHalfHeight = collidedObjectRectangle.height / 2.0f;
            float collidedObjectCenterY = collidedObjectRectangle.top + collidedObjectHalfHeight;
            explosionSprite->setPosition(collidedObjectCenterX, collidedObjectCenterY);

            // Load the explosion sound data.
            const std::string EXPLOSION_SOUND_FILEPATH = "res/Sounds/Explosion.wav";
            std::shared_ptr<sf::SoundBuffer> explosionSoundBuffer = m_resourceManager.GetSoundBuffer(EXPLOSION_SOUND_FILEPATH);
            bool explosionSoundBufferLoaded = (nullptr != explosionSoundBuffer);
            if (!explosionSoundBufferLoaded)
            {
                throw std::runtime_error("Error loading explosion sound.");
            }

            // Create the sound for the explosion.
            std::shared_ptr<sf::Sound> explosionSound = std::make_shared<sf::Sound>(*explosionSoundBuffer);

            // Create the explosion.
            std::shared_ptr<OBJECTS::Explosion> explosion = std::make_shared<OBJECTS::Explosion>(explosionSprite, explosionSound);
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

    // CHECK FOR COLLISIONS OF THE ALIENS WITH THE EASTER EGGS OR PLAYER.
    for (auto alien : m_aliens)
    {
        sf::FloatRect alienBounds = alien->GetBoundingRectangle();

        // CHECK IF THE ALIEN COLLIDED WITH THE EASTER BUNNY.
        sf::FloatRect bunnyBounds = m_bunnyPlayer->GetBoundingRectangle();
        bool alienHitBunny = alienBounds.intersects(bunnyBounds);
        if (alienHitBunny)
        {
            m_bunnyPlayer->LoseLife();
        }

        // CHECK IF THE ALIEN COLLIDED WITH ANY EASTER EGGS.
        // We don't automatically increment the iterator during the for loop because we may need to
        // erase from the container during the loop for eggs that have lost all health.
        for (auto easterEgg = m_easterEggs.begin(); easterEgg != m_easterEggs.end();)
        {
            // Check if the alien hit an egg.
            sf::FloatRect eggBounds = (*easterEgg)->GetBoundingRectangle();
            bool alienHitEgg = alienBounds.intersects(eggBounds);
            if (alienHitEgg)
            {
                (*easterEgg)->LoseHealth();

                // Check if the alien killed the egg.
                uint8_t eggHealth = (*easterEgg)->GetHealth();
                bool eggAlive = (eggHealth > 0);
                if (!eggAlive)
                {            
                    // Remove the egg so that it is no longer updated.
                    easterEgg = m_easterEggs.erase(easterEgg);
                }
            }
            else
            {
                // Move to the checking collisions for the next egg.
                ++easterEgg;
            }
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

    // CHECK IF THE MISSILE COLLIDED WITH ANY EASTER EGGS.
    sf::FloatRect missileBounds = missile.GetBoundingRectangle();
    // We don't automatically increment the iterator during the for loop because we may need to
    // erase from the container during the loop for eggs that have lost all health.
    for (auto easterEgg = m_easterEggs.begin(); easterEgg != m_easterEggs.end();)
    {
        // Check if the missile hit an egg.
        sf::FloatRect eggBounds = (*easterEgg)->GetBoundingRectangle();
        bool missileHitEgg = missileBounds.intersects(eggBounds);
        if (missileHitEgg)
        {
            collidedObjectRectangle = eggBounds;

            (*easterEgg)->LoseHealth();

            // Check if the missile killed the egg.
            uint8_t eggHealth = (*easterEgg)->GetHealth();
            bool eggAlive = (eggHealth > 0);
            if (!eggAlive)
            {            
                // Remove the egg so that it is no longer updated.
                easterEgg = m_easterEggs.erase(easterEgg);
            }

            return true;
        }
        else
        {
            // Move to the checking collisions for the next egg.
            ++easterEgg;
        }
    }

    // CHECK IF THE MISSILE COLLIDED WITH THE EASTER BUNNY.
    sf::FloatRect bunnyBounds = m_bunnyPlayer->GetBoundingRectangle();
    bool missileHitBunny = missileBounds.intersects(bunnyBounds);
    if (missileHitBunny)
    {
        collidedObjectRectangle = bunnyBounds;

        m_bunnyPlayer->LoseLife();
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

            // Add points to the player's score for killing the alien.
            AddToScore(DEFAULT_ALIEN_KILL_POINTS);

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

void GameplayState::AddToScore(const uint16_t pointsToAdd)
{
    // Update the player's current score.
    // The max high score is the largest 100-based multiple that can fit within
    // the data type limits.  It is unlikely that a player will reach this high
    // score due to difficulty increases in the game, but this check is provided
    // just in case to prevent annoying the player with a wrap-around score.
    bool maxHighScoreReached = (m_currentScore >= MAX_HIGH_SCORE);
    if (!maxHighScoreReached)
    {
        m_currentScore += pointsToAdd;
        m_gameplayHud->SetScore(m_currentScore);
    }

    // Update the high score, if needed.
    bool newHighestScoreReached = (m_currentScore > m_highScore);
    if (newHighestScoreReached)
    {
        m_highScore = m_currentScore;
        m_gameplayHud->SetHighScore(m_highScore);
    }
}

void GameplayState::UpdateSubState()
{
    // CHECK IF THE PLAYER HAS WON.
    // The max high score is the largest 100-based multiple that can fit within
    // the data type limits.  It is unlikely that a player will reach this high
    // score due to difficulty increases in the game, but this check is provided
    // just in case to prevent annoying the player with a wrap-around score.
    bool maxHighScoreReached = (m_currentScore >= MAX_HIGH_SCORE);
    bool allAliensKilled = (m_aliens.size() <= 0);
    bool playerWon = (maxHighScoreReached || allAliensKilled);
    if (playerWon)
    {
        m_currentSubState = VICTORY_SUBSTATE;

        m_gameplayHud->ShowPlayerWonText();
    }

    // CHECK IF THE PLAYER HAS LOST.
    bool playerCompletelyDead = (m_bunnyPlayer->GetLives() <= 0);
    bool easterEggsAllGone = (m_easterEggs.size() <= 0);
    bool playerLost = (playerCompletelyDead || easterEggsAllGone);
    if (playerLost)
    {
        // In the event that the player defeated all aliens but simultaneously
        // lost all lives or eggs, we still want to consider that a game over.
        m_currentSubState = GAME_OVER_SUBSTATE;

        m_gameplayHud->ShowPlayerLostText();
    }
}

void GameplayState::SaveHighScores()
{
    /// @todo   Rethink refactoring the HighScores class to support
    ///         these kinds of operations.  We may also be able
    ///         to consider using the heap operations provided in
    ///         the C++11 algorithm library.

    // ADD THE CURRENT PLAYER'S SCORE AS A POTENTIAL HIGH SCORE.
    std::vector<uint16_t> highScores;
    highScores.push_back(m_currentScore);

    // ADD ALL OF THE PREVIOUS HIGH SCORE'S AS POTENTIAL HIGH SCORES.
    std::array<uint16_t, SAVE_DATA::HighScores::MAX_HIGH_SCORES_COUNT> originalHighScores =
        m_highScores.GetHighScoresInDescendingOrder();
    for (uint16_t originalHighScore : originalHighScores)
    {
        highScores.push_back(originalHighScore);
    }

    // SORT ALL OF THE POTENTIAL HIGH SCORES SO THAT THE HIGHEST ONES ARE FIRST.
    auto sortDescending = [](uint16_t leftScore, uint16_t rightScore) { return (leftScore > rightScore); };
    std::stable_sort(highScores.begin(), highScores.end(), sortDescending);

    // WRITE THE TOP HIGH SCORES TO FILE.
    const std::string HIGH_SCORES_FILEPATH = "res/highScores.txt";
    std::ofstream highScoresFile(HIGH_SCORES_FILEPATH, std::ios_base::out | std::ios_base::trunc);
    if (highScoresFile.is_open())
    {
        for (unsigned int savedHighScoreCount = 0;
            (savedHighScoreCount < SAVE_DATA::HighScores::MAX_HIGH_SCORES_COUNT &&
            savedHighScoreCount < highScores.size());
            ++savedHighScoreCount)
        {
            highScoresFile << highScores[savedHighScoreCount] << std::endl;
        }

        highScoresFile.close();
    }
}