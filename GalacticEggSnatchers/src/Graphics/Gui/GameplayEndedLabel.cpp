#include "Graphics/Gui/GameplayEndedLabel.h"

using namespace GRAPHICS::GUI;

GameplayEndedLabel::GameplayEndedLabel(
    const sf::FloatRect& screenBoundsInPixels,
    const sf::Color& textColor, 
    const std::shared_ptr<sf::Font>& font) :
    m_screenBoundsInPixels(screenBoundsInPixels),
    m_isVisible(false),
    m_mainMessageText(),
    m_secondaryInstructionText()
{
    // INITIALIZE THE MAIN MESSAGE TEXT.
    // We don't need to position it yet since its text has not been set.
    const unsigned int MAIN_MESSAGE_TEXT_HEIGHT_IN_PIXELS = 32;
    m_mainMessageText.setCharacterSize(MAIN_MESSAGE_TEXT_HEIGHT_IN_PIXELS);
    m_mainMessageText.setColor(textColor);
    m_mainMessageText.setFont(*font);
    
    // INITIALIZE THE SECONDARY INSTRUCTION TEXT.
    const unsigned int INSTRUCTION_TEXT_HEIGHT_IN_PIXELS = 12;
    m_secondaryInstructionText.setCharacterSize(INSTRUCTION_TEXT_HEIGHT_IN_PIXELS);
    m_secondaryInstructionText.setColor(textColor);
    m_secondaryInstructionText.setFont(*font);
    m_secondaryInstructionText.setString("(Press Enter to return to the title screen.)");
    SetSecondaryInstructionTextPosition();    
}

GameplayEndedLabel::~GameplayEndedLabel()
{
    // Nothing to do.
}

void GameplayEndedLabel::Render(sf::RenderTarget& renderTarget)
{
    // REQUIRE THAT THE LABEL IS VISIBLE.
    if (IsVisible())
    {
        renderTarget.draw(m_mainMessageText);
        renderTarget.draw(m_secondaryInstructionText);
    }
}

bool GameplayEndedLabel::IsVisible() const
{
    return m_isVisible;
}

void GameplayEndedLabel::SetVisible(bool visibility)
{
    m_isVisible = visibility;
}

void GameplayEndedLabel::SetText(const std::string& mainMessageText)
{
    m_mainMessageText.setString(mainMessageText);

    // Reposition the main message text since its value has changed.
    SetMainMessageTextPosition();
}

void GameplayEndedLabel::SetMainMessageTextPosition()
{
    // HORIZONTALLY CENTER THE TEXT ON THE SCREEN.
    // Get the center of the screen.
    float screenCenterX = m_screenBoundsInPixels.left + (m_screenBoundsInPixels.width / 2.0f);

    // Figure out the width of the main message text.
    sf::FloatRect mainMessageBounds = m_mainMessageText.getLocalBounds();
    float mainMessageTextWidth = mainMessageBounds.width;
    float mainMessageTextHalfWidth = (mainMessageTextWidth / 2.0f);

    // Position the text so that it is horizontally centered on screen.
    float mainMessageTextLeftXPosition = (screenCenterX - mainMessageTextHalfWidth);

    // The y position is set so that it appears slightly above the middle of the screen.
    float oneThirdDownScreen = m_screenBoundsInPixels.top + (m_screenBoundsInPixels.height * 1.0f / 3.0f);
    float mainMessageTextHeight = mainMessageBounds.height;
    float mainMessageTextTopYPosition = oneThirdDownScreen - mainMessageTextHeight;

    // Set the position of the main text.
    m_mainMessageText.setPosition(mainMessageTextLeftXPosition, mainMessageTextTopYPosition);
}

void GameplayEndedLabel::SetSecondaryInstructionTextPosition()
{
    // HORIZONTALLY CENTER THE TEXT ON THE SCREEN.
    // Get the center of the screen.
    float screenCenterX = m_screenBoundsInPixels.left + (m_screenBoundsInPixels.width / 2.0f);

    // Figure out the width of the instruction text.
    float instructionTextWidth = m_secondaryInstructionText.getLocalBounds().width;
    float instructionTextHalfWidth = (instructionTextWidth / 2.0f);

    // Position the text so that it is horizontally centered on screen.
    float instructionTextLeftXPosition = (screenCenterX - instructionTextHalfWidth);

    // The y position is set so that it appears slightly below the middle of the screen.
    float twoThirdsDownScreen = m_screenBoundsInPixels.top + (m_screenBoundsInPixels.height * 2.0f / 3.0f);
    float instructionTextTopYPosition = twoThirdsDownScreen;

    // Set the position of the instruction text.
    m_secondaryInstructionText.setPosition(instructionTextLeftXPosition, instructionTextTopYPosition);
}
