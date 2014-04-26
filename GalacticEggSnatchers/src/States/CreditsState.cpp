#include <stdexcept>
#include "States/CreditsState.h"

using namespace STATES;

CreditsState::CreditsState(const sf::FloatRect& screenBoundsInPixels) :
    m_screenBoundsInPixels(screenBoundsInPixels),
    m_resourceManager(),
    m_nextGameState(GAME_STATE_TYPE_INVALID),
    m_contributors()
{
    // Initialize the text for the credits screen.
    InitializeCreditsText();
}

CreditsState::~CreditsState()
{
    // Nothing else to do.
}

GameStateType CreditsState::GetStateType() const
{
    return GAME_STATE_TYPE_CREDITS;
}

GameStateType CreditsState::GetNextState() const
{
    return m_nextGameState;
}

void CreditsState::Update(const sf::Time& elapsedTime)
{
    // Nothing else to do.
}

void CreditsState::Render(sf::RenderTarget& renderTarget)
{
    // RENDER EACH OF THE CONTRIBUTORS.
    for (auto contributorText : m_contributors)
    {
        renderTarget.draw(contributorText);
    }
}

void CreditsState::HandleKeyPress(const sf::Keyboard::Key key)
{
    // Always move to the title state upon any key press.
    m_nextGameState = GAME_STATE_TYPE_TITLE;
}

void CreditsState::InitializeCreditsText()
{
    // LOAD THE FONT FOR THE CREDITS TEXT.
    const std::string CREDITS_FONT_FILEPATH = "res/fonts/Minecraftia.ttf";
    std::shared_ptr<sf::Font> creditsFont = m_resourceManager.GetFont(CREDITS_FONT_FILEPATH);
    bool creditsFontLoaded = (nullptr != creditsFont);
    if (!creditsFontLoaded)
    {
        throw std::runtime_error("Error loading credits font.");
    }

    // ADD EACH OF THE CONTRIBUTORS TO THE LIST OF CREDITS.
    const unsigned int CREDITS_FONT_HEIGHT_IN_PIXELS = 14;
    const float CONTRIBUTOR_X_POSITION_IN_PIXELS = 64.0f;
    const float FIRST_CONTRIBUTOR_Y_POSITION_IN_PIXELS = 64.0f;
    const float BUFFER_SPACE_BETWEEN_CONTRIBUTORS = 8.0f;

    sf::Text firstContributor("Jacob Pike - Team Lead, Programmer", *creditsFont, CREDITS_FONT_HEIGHT_IN_PIXELS);
    firstContributor.setPosition(CONTRIBUTOR_X_POSITION_IN_PIXELS, FIRST_CONTRIBUTOR_Y_POSITION_IN_PIXELS);
    m_contributors.push_back(firstContributor);

    sf::Text secondContributor("AleKahpwn - Art, Task Management", *creditsFont, CREDITS_FONT_HEIGHT_IN_PIXELS);
    float secondContributorYPositionInPixels = (
        FIRST_CONTRIBUTOR_Y_POSITION_IN_PIXELS + 
        CREDITS_FONT_HEIGHT_IN_PIXELS +
        BUFFER_SPACE_BETWEEN_CONTRIBUTORS);
    secondContributor.setPosition(CONTRIBUTOR_X_POSITION_IN_PIXELS, secondContributorYPositionInPixels);
    m_contributors.push_back(secondContributor);

    sf::Text thirdContributor("Johnicholas - Art", *creditsFont, CREDITS_FONT_HEIGHT_IN_PIXELS);
    float thirdContributorYPositionInPixels = (
        secondContributorYPositionInPixels + 
        CREDITS_FONT_HEIGHT_IN_PIXELS +
        BUFFER_SPACE_BETWEEN_CONTRIBUTORS);
    thirdContributor.setPosition(CONTRIBUTOR_X_POSITION_IN_PIXELS, thirdContributorYPositionInPixels);
    m_contributors.push_back(thirdContributor);

    sf::Text fourthContributor("Mercy404 - Sound", *creditsFont, CREDITS_FONT_HEIGHT_IN_PIXELS);
    float fourthContributorYPositionInPixels = (
        thirdContributorYPositionInPixels + 
        CREDITS_FONT_HEIGHT_IN_PIXELS +
        BUFFER_SPACE_BETWEEN_CONTRIBUTORS);
    fourthContributor.setPosition(CONTRIBUTOR_X_POSITION_IN_PIXELS, fourthContributorYPositionInPixels);
    m_contributors.push_back(fourthContributor);

    sf::Text fifthContributor("Andrew Tyler - Font", *creditsFont, CREDITS_FONT_HEIGHT_IN_PIXELS);
    float fifthContributorYPositionInPixels = (
        fourthContributorYPositionInPixels + 
        CREDITS_FONT_HEIGHT_IN_PIXELS +
        BUFFER_SPACE_BETWEEN_CONTRIBUTORS);
    fifthContributor.setPosition(CONTRIBUTOR_X_POSITION_IN_PIXELS, fifthContributorYPositionInPixels);
    m_contributors.push_back(fifthContributor);
}