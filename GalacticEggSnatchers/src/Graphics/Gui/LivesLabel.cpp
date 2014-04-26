#include <sstream>
#include "Graphics/Gui/LivesLabel.h"

using namespace GRAPHICS::GUI;

LivesLabel::LivesLabel(
    const unsigned int fontSizeInPixels, 
    const sf::Color& textColor, 
    const std::shared_ptr<sf::Font>& font) :
    m_labelText()
{    
    // Initialize the lives to 0.
    SetLivesCount(0);

    m_labelText.setCharacterSize(fontSizeInPixels);
    m_labelText.setColor(textColor);
    m_labelText.setFont(*font);
}

LivesLabel::~LivesLabel()
{
    // Nothing else to do.
}

void LivesLabel::Render(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(m_labelText);
}

void LivesLabel::SetLivesCount(const uint8_t livesCount)
{
    // CREATE THE STRING TO DISPLAY IN THE LABEL.
    std::ostringstream livesStringConverter;
    // The cast is necessary to prevent the 8-bit lives count from being interpretted as a char.
    livesStringConverter << "LIVES: " << static_cast<uint16_t>(livesCount);
    std::string livesLabelString = livesStringConverter.str();

    // UPDATE THE TEXT IN THE LABEL.
    m_labelText.setString(livesLabelString);
}

void LivesLabel::SetPosition(const float screenXInPixels, const float screenYInPixels)
{
    m_labelText.setPosition(screenXInPixels, screenYInPixels);
}