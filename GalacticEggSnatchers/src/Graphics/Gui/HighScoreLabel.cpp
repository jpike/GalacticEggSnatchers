#include <sstream>
#include "Graphics/Gui/HighScoreLabel.h"

using namespace GRAPHICS::GUI;

HighScoreLabel::HighScoreLabel(
    const unsigned int fontSizeInPixels, 
    const sf::Color& textColor, 
    const std::shared_ptr<sf::Font>& font) :
    m_labelText()
{
    // Initialize the high score to 0.
    SetHighScore(0);

    m_labelText.setCharacterSize(fontSizeInPixels);
    m_labelText.setColor(textColor);
    m_labelText.setFont(*font);
}

HighScoreLabel::~HighScoreLabel()
{
    // Nothing else to do.
}

void HighScoreLabel::Render(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(m_labelText);
}

void HighScoreLabel::SetHighScore(const uint16_t highScore)
{
    // CREATE THE STRING TO DISPLAY IN THE LABEL.
    std::ostringstream scoreStringConverter;
    // Pad the score with zeroes on the left.
    scoreStringConverter.fill('0');
    const std::streamsize MAX_SCORE_DIGIT_COUNT = 5;
    scoreStringConverter.width(MAX_SCORE_DIGIT_COUNT);
    scoreStringConverter << std::right << highScore;
    std::string scoreLabelString = "HIGH SCORE: " + scoreStringConverter.str();

    // UPDATE THE TEXT IN THE LABEL.
    m_labelText.setString(scoreLabelString);
}

void HighScoreLabel::SetPosition(const float screenXInPixels, const float screenYInPixels)
{
    m_labelText.setPosition(screenXInPixels, screenYInPixels);
}

float HighScoreLabel::GetTextWidthInPixels() const
{
    sf::FloatRect boundingRectangle = m_labelText.getLocalBounds();
    return boundingRectangle.width;
}