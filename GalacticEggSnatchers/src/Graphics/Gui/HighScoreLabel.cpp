#include <sstream>
#include "Graphics/Gui/HighScoreLabel.h"

using namespace GRAPHICS::GUI;

HighScoreLabel::HighScoreLabel(const sf::Color& textColor, const std::shared_ptr<sf::Font>& font) :
    m_labelText()
{
    // Initialize the high score to 0.
    SetHighScore(0);

    m_labelText.setColor(textColor);
    m_labelText.setFont(*font);

    /// @todo Remove or alter the setting of the text size here once we have a final font.
    m_labelText.setCharacterSize(14);
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