#include <stdexcept>
#include "States/TitleState.h"

using namespace STATES;

TitleState::TitleState(
    const std::string& title, 
    const sf::FloatRect& screenBoundsInPixels) :
    m_screenBoundsInPixels(screenBoundsInPixels),
    m_resourceManager(),
    m_titleLabel(),
    m_menuOptions(),
    m_menuKeyToNextGameStateMap(),
    m_nextGameState(GAME_STATE_TYPE_INVALID)
{
    InitializeTitleLabel(title);
    InitializeMenuOptions();
}

TitleState::~TitleState()
{
    // Nothing else to do.
}

GameStateType TitleState::GetStateType() const
{
    return GAME_STATE_TYPE_TITLE;
}

GameStateType TitleState::GetNextState() const
{
    return m_nextGameState;
}

void TitleState::Update(const sf::Time& elapsedTime)
{
    // Nothing else to do.
}

void TitleState::Render(sf::RenderTarget& renderTarget)
{
    // RENDER THE TITLE TEXT.
    renderTarget.draw(m_titleLabel);

    // RENDER EACH OF THE MENU OPTIONS.
    for (auto menuOption : m_menuOptions)
    {
        renderTarget.draw(menuOption);
    }
}

void TitleState::HandleKeyPress(const sf::Keyboard::Key key)
{
    // CHECK IF THE PRESSED KEY IS MAPPED TO A MENU OPTION.
    auto nextGameState = m_menuKeyToNextGameStateMap.find(key);
    bool keyMappedToMenuOption = (m_menuKeyToNextGameStateMap.end() != nextGameState);
    if (keyMappedToMenuOption)
    {
        // Set the next game state based on the pressed key.
        m_nextGameState = nextGameState->second;
    }
}

void TitleState::InitializeTitleLabel(const std::string& title)
{
    // SET THE FONT FOR THE TITLE TEXT.
    const std::string TITLE_FONT_FILEPATH = "res/fonts/Minecraftia.ttf";
    std::shared_ptr<sf::Font> titleFont = m_resourceManager.GetFont(TITLE_FONT_FILEPATH);
    bool titleFontLoaded = (nullptr != titleFont);
    if (!titleFontLoaded)
    {
        throw std::runtime_error("Error loading title font.");
    }

    // SET BASIC PARAMETERS FOR THE TITLE.
    const unsigned int TITLE_FONT_SIZE_IN_PIXELS = 24;
    m_titleLabel.setCharacterSize(TITLE_FONT_SIZE_IN_PIXELS);
    m_titleLabel.setFont(*titleFont);
    m_titleLabel.setString(title);

    // POSITION THE TITLE LABEL.    
    // Center it horizontally.
    float screenBoundsHalfWidth = m_screenBoundsInPixels.width / 2.0f;
    float screenCenterXInPixels = m_screenBoundsInPixels.left + screenBoundsHalfWidth;
    float titleWidthInPixels = m_titleLabel.getLocalBounds().width;
    float titleHalfWidth = titleWidthInPixels / 2.0f;
    float titleLeftXPositionInPixels = screenCenterXInPixels - titleHalfWidth;

    const float TITLE_Y_POSITION_IN_PIXELS = 64.0f;
    m_titleLabel.setPosition(titleLeftXPositionInPixels, TITLE_Y_POSITION_IN_PIXELS);
}

void TitleState::InitializeMenuOptions()
{
    // LOAD THE RESOURCES FOR THE MENU OPTIONS.
    const std::string MENU_OPTION_FONT_FILEPATH = "res/fonts/Minecraftia.ttf";
    std::shared_ptr<sf::Font> menuOptionFont = m_resourceManager.GetFont(MENU_OPTION_FONT_FILEPATH);
    bool menuOptionFontLoaded = (nullptr != menuOptionFont);
    if (!menuOptionFontLoaded)
    {
        throw std::runtime_error("Error loading menu option font.");
    }

    const unsigned int MENU_OPTION_FONT_HEIGHT_IN_PIXELS = 14;

    // ADD THE START GAME MENU OPTION.
    sf::Text startGameMenuOptionText("(1) Start Game", *menuOptionFont, MENU_OPTION_FONT_HEIGHT_IN_PIXELS);
    m_menuOptions.push_back(startGameMenuOptionText);
    m_menuKeyToNextGameStateMap[sf::Keyboard::Key::Num1] = GAME_STATE_TYPE_GAMEPLAY;
    m_menuKeyToNextGameStateMap[sf::Keyboard::Key::Numpad1] = GAME_STATE_TYPE_GAMEPLAY;

    // ADD THE HIGH SCORES MENU OPTION.
    sf::Text highScoresMenuOptionText("(2) High Scores", *menuOptionFont, MENU_OPTION_FONT_HEIGHT_IN_PIXELS);
    m_menuOptions.push_back(highScoresMenuOptionText);
    m_menuKeyToNextGameStateMap[sf::Keyboard::Key::Num2] = GAME_STATE_TYPE_HIGH_SCORES;
    m_menuKeyToNextGameStateMap[sf::Keyboard::Key::Numpad2] = GAME_STATE_TYPE_HIGH_SCORES;

    // ADD THE CREDITS MENU OPTION.
    sf::Text creditsMenuOptionText("(3) Credits", *menuOptionFont, MENU_OPTION_FONT_HEIGHT_IN_PIXELS);
    m_menuOptions.push_back(creditsMenuOptionText);
    m_menuKeyToNextGameStateMap[sf::Keyboard::Key::Num3] = GAME_STATE_TYPE_CREDITS;
    m_menuKeyToNextGameStateMap[sf::Keyboard::Key::Numpad3] = GAME_STATE_TYPE_CREDITS;

    // POSITION ALL OF THE MENU OPTIONS.
    // Start the menu about halfway down the screen.
    float screenBoundsHalfHeight = m_screenBoundsInPixels.height / 2.0f;
    float topMenuOptionYPositionInPixels = m_screenBoundsInPixels.top + screenBoundsHalfHeight;

    // Figure out the maximum width of the menu options.
    float maxMenuOptionWidthInPixels = 0.0f;
    for (auto menuOption : m_menuOptions)
    {
        // Check if the current menu option's width is greater the the maximum width found so far.
        float currentMenuOptionWidth = menuOption.getLocalBounds().width;
        bool newMaxMenuOptionWidthFound = (currentMenuOptionWidth > maxMenuOptionWidthInPixels);
        if (newMaxMenuOptionWidthFound)
        {
            // Store the newly found max width.
            maxMenuOptionWidthInPixels = currentMenuOptionWidth;
        }
    }
    float maxMenuOptionHalfWidth = maxMenuOptionWidthInPixels / 2.0f;

    // Left align all of the menu options, approximately in the center.
    float screenBoundsHalfWidth = m_screenBoundsInPixels.width / 2.0f;
    float screenBoundsCenterX = m_screenBoundsInPixels.left + screenBoundsHalfWidth;
    float menuOptionXPosition = screenBoundsCenterX - maxMenuOptionHalfWidth;

    // Position each of the menu options, each one slightly below the previous one.
    float currentMenuOptionYPosition = topMenuOptionYPositionInPixels;
    for (auto& menuOption : m_menuOptions)
    {
        menuOption.setPosition(menuOptionXPosition, currentMenuOptionYPosition);

        // Update the y position for the next menu option.
        float BUFFER_SPACE_BETWEEN_MENU_OPTIONS = 2.0f;
        currentMenuOptionYPosition += (BUFFER_SPACE_BETWEEN_MENU_OPTIONS + MENU_OPTION_FONT_HEIGHT_IN_PIXELS);
    }
}