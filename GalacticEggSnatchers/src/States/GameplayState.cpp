#include <stdexcept>
#include "GalacticEggSnatchersGame.h"
#include "Input/KeyboardController.h"
#include "States/GameplayState.h"

using namespace STATES;

GameplayState::GameplayState() :
    m_bunnyPlayer(),
    m_easterEggs(),
    m_aliens(),
    m_missiles(),
    m_sprites()
{
    // CREATE THE INITIAL OBJECTS FOR A NEW GAMEPLAY SESSION.
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
    /// @todo
}

void GameplayState::Render(sf::RenderTarget& renderTarget)
{
    // RENDER ALL OF THE SPRITES.
    for(const std::shared_ptr<sf::Sprite>& sprite : m_sprites)
    {
        renderTarget.draw(*sprite);
    }
}

std::shared_ptr<OBJECTS::EasterBunny> GameplayState::CreateInitialBunnyPlayer()
{
    // LOAD THE TEXTURE FOR THE BUNNY.
    const std::string BUNNY_TEXTURE_FILEPATH = "res/Images/bunny.png";
    std::shared_ptr<sf::Texture> bunnyTexture = std::make_shared<sf::Texture>();
    bool bunnyTextureLoaded = bunnyTexture->loadFromFile(BUNNY_TEXTURE_FILEPATH);
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

    // CREATE THE KEYBOARD CONTROLLER FOR THE BUNNY.
    std::shared_ptr<INPUT::IInputController> bunnyPlayerController = std::make_shared<INPUT::KeyboardController>();

    // CREATE THE BUNNY FOR THE PLAYER.
    std::shared_ptr<OBJECTS::EasterBunny> bunnyPlayer = std::make_shared<OBJECTS::EasterBunny>(bunnySprite, bunnyPlayerController);

    // Save the sprite for rendering later.
    m_sprites.push_back(bunnySprite);
    m_textures.push_back(bunnyTexture);

    return bunnyPlayer;
}

std::vector< std::shared_ptr<OBJECTS::EasterEgg> > GameplayState::CreateInitialEasterEggs()
{
    // CREATE AN INITIAL NUMBER OF EASTER EGGS.
    const unsigned int INITIAL_EASTER_EGG_COUNT = 4;
    std::vector< std::shared_ptr<OBJECTS::EasterEgg> > initialEasterEggs;
    for (unsigned int currentEasterEggCount = 0; currentEasterEggCount < INITIAL_EASTER_EGG_COUNT; ++currentEasterEggCount)
    {
        // CREATE A SPRITE FOR THE EASTER EGG.
        /// @todo   A random texture needs to be selected once texture(s) exist.
        std::shared_ptr<sf::Texture> eggTexture = std::make_shared<sf::Texture>();
        const int EGG_SPRITE_WIDTH_IN_PIXELS = 32;
        const int EGG_SPRITE_HEIGHT_IN_PIXELS = 32;
        eggTexture->create(EGG_SPRITE_WIDTH_IN_PIXELS, EGG_SPRITE_HEIGHT_IN_PIXELS);

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

        // Save the sprite for rendering later.
        m_sprites.push_back(eggSprite);
        m_textures.push_back(eggTexture);
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
            // CREATE A SPRITE FOR THE ALIEN.
            /// @todo   A random texture needs to be selected once texture(s) exist.
            std::shared_ptr<sf::Texture> alienTexture = std::make_shared<sf::Texture>();
            const int ALIEN_SPRITE_WIDTH_IN_PIXELS = 32;
            const int ALIEN_SPRITE_HEIGHT_IN_PIXELS = 32;
            alienTexture->create(ALIEN_SPRITE_WIDTH_IN_PIXELS, ALIEN_SPRITE_HEIGHT_IN_PIXELS);

            std::shared_ptr<sf::Sprite> alienSprite = std::make_shared<sf::Sprite>(*alienTexture);

            // POSITION THE SPRITE.
            // The alien is positioned show that all aliens in the grid are uniformly spaced out.
            // Adjustments to positioning may be needed at a later date.

            // Aliens will be at least this certain amount down the screen to leave space
            // for the score and other GUI elements at the top.
            const float VerticalSpacingBetweenAliens = 8.0f;
            float minAlienYPosition = (ALIEN_SPRITE_HEIGHT_IN_PIXELS * 3.0f);
            float alienYPosition = (
                minAlienYPosition + 
                (VerticalSpacingBetweenAliens + ALIEN_SPRITE_HEIGHT_IN_PIXELS) * static_cast<float>(currentAlienRow));

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

            // CREATE THE ALIEN.
            std::shared_ptr<OBJECTS::Alien> alien = std::make_shared<OBJECTS::Alien>(alienSprite);
            initialAliens.push_back(alien);

            // Save the sprite for rendering later.
            m_sprites.push_back(alienSprite);
            m_textures.push_back(alienTexture);
        }
    }

    return initialAliens;
}