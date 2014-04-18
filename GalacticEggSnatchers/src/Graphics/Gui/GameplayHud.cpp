#pragma once

#include "Graphics/Gui/GameplayHud.h"

using namespace GRAPHICS::GUI;

// White ensures that the text can be seen against the black screen background.
const sf::Color GameplayHud::DEFAULT_TEXT_COLOR = sf::Color::White;

GameplayHud::GameplayHud(const sf::FloatRect& screenBoundsInPixels, const std::shared_ptr<sf::Font>& textFont) :
    m_livesLabel(DEFAULT_TEXT_COLOR, textFont),
    m_scoreLabel(DEFAULT_TEXT_COLOR, textFont),
    m_highScoreLabel(DEFAULT_TEXT_COLOR, textFont)
{
    // POSITION EACH OF THE LABELS.
    PositionLabels(screenBoundsInPixels);
}

GameplayHud::~GameplayHud()
{
    // Nothing to do.
}

void GameplayHud::Render(sf::RenderTarget& renderTarget)
{
    m_livesLabel.Render(renderTarget);
    m_scoreLabel.Render(renderTarget);
    m_highScoreLabel.Render(renderTarget);
}

void GameplayHud::SetLivesCount(const uint8_t livesCount)
{
    m_livesLabel.SetLivesCount(livesCount);
}

void GameplayHud::SetScore(const uint16_t score)
{
    m_scoreLabel.SetScore(score);
}

void GameplayHud::SetHighScore(const uint16_t highScore)
{
    m_highScoreLabel.SetHighScore(highScore);
}

void GameplayHud::PositionLabels(const sf::FloatRect& screenBoundsInPixels)
{
    // POSITION THE LIVES LABEL.
    // It is set to the far-left of the screen.
    m_livesLabel.SetPosition(screenBoundsInPixels.left, screenBoundsInPixels.top);

    // POSITION THE CURRENT SCORE LABEL.
    // Get the center of the screen.
    float screenCenterX = screenBoundsInPixels.left + (screenBoundsInPixels.width / 2.0f);

    // Figure out the width of the score label.
    float scoreLabelWidth = m_scoreLabel.GetTextWidthInPixels();
    float scoreLabelHalfWidth = (scoreLabelWidth / 2.0f);

    // Position the score label so that it is horizontally centered on screen.
    float scoreLabelLeftX = (screenCenterX - scoreLabelHalfWidth);
    m_scoreLabel.SetPosition(scoreLabelLeftX, screenBoundsInPixels.top);

    // POSITION THE HIGH SCORE LABEL.
    // Get the far right position of the screen.
    float screenRightX = (screenBoundsInPixels.left + screenBoundsInPixels.width);

    // Figure out the width of the high score label.
    float highScoreLabelWidth = m_highScoreLabel.GetTextWidthInPixels();
    
    // Position the high score label so that it is on the far-right of the screen.
    float highScoreLabelLeftX = (screenRightX - highScoreLabelWidth);
    m_highScoreLabel.SetPosition(highScoreLabelLeftX, screenBoundsInPixels.top);
}