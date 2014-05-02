#include <fstream>
#include <sstream>
#include <stdexcept>
#include "States/HighScoresState.h"

using namespace STATES;

HighScoresState::HighScoresState(const sf::FloatRect& screenBoundsInPixels) :
    m_screenBoundsInPixels(screenBoundsInPixels),
    m_resourceManager(),
    m_nextGameState(GAME_STATE_TYPE_INVALID),
    m_highScoresTitle(),
    m_highScores()
{
    // Initialize the text for the high scores screen.
    SAVE_DATA::HighScores highScores = LoadHighScores();
    InitializeHighScoresText(highScores);
}

HighScoresState::~HighScoresState()
{
    // Nothing else to do.
}

GameStateType HighScoresState::GetStateType() const
{
    return GAME_STATE_TYPE_HIGH_SCORES;
}

GameStateType HighScoresState::GetNextState() const
{
    return m_nextGameState;
}

void HighScoresState::Update(const sf::Time& elapsedTime)
{
    // Nothing else to do.
}

void HighScoresState::Render(sf::RenderTarget& renderTarget)
{
    // RENDER THE HIGH SCORES TITLE.
    renderTarget.draw(m_highScoresTitle);
    
    // RENDER EACH OF THE HIGH SCORES.
    for (auto highScoreText : m_highScores)
    {
        renderTarget.draw(highScoreText);
    }
}

void HighScoresState::HandleKeyPress(const sf::Keyboard::Key key)
{
    // Always move to the title state upon any key press.
    m_nextGameState = GAME_STATE_TYPE_TITLE;
}

SAVE_DATA::HighScores HighScoresState::LoadHighScores() const
{
    SAVE_DATA::HighScores highScores;
    
    // OPEN THE HIGH SCORES FILE.
    const std::string HIGH_SCORES_FILEPATH = "res/data/highScores.txt";
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
                highScores.AddHighScore(highScore);
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

    // We don't need to do anything else.  The available high scores
    // will remain in their default initialzed state.
    return highScores;
}

void HighScoresState::InitializeHighScoresText(SAVE_DATA::HighScores& highScores)
{
    // LOAD THE FONT FOR THE HIGH SCORES TEXT.
    const std::string HIGH_SCORES_FONT_FILEPATH = "res/fonts/Minecraftia.ttf";
    std::shared_ptr<sf::Font> highScoresFont = m_resourceManager.GetFont(HIGH_SCORES_FONT_FILEPATH);
    bool highScoresFontLoaded = (nullptr != highScoresFont);
    if (!highScoresFontLoaded)
    {
        throw std::runtime_error("Error loading high scores font.");
    }

    // SET THE TITLE FOR THE HIGH SCORES SCREEN.
    const unsigned int HIGH_SCORE_TITLE_TEXT_HEIGHT_IN_PIXELS = 24;
    m_highScoresTitle.setCharacterSize(HIGH_SCORE_TITLE_TEXT_HEIGHT_IN_PIXELS);
    m_highScoresTitle.setFont(*highScoresFont);
    m_highScoresTitle.setString("High Scores");

    // Center the title label horizontally.
    float screenBoundsHalfWidth = m_screenBoundsInPixels.width / 2.0f;
    float screenCenterXInPixels = m_screenBoundsInPixels.left + screenBoundsHalfWidth;
    float titleWidthInPixels = m_highScoresTitle.getLocalBounds().width;
    float titleHalfWidth = titleWidthInPixels / 2.0f;
    float titleLeftXPositionInPixels = screenCenterXInPixels - titleHalfWidth;

    const float TITLE_Y_POSITION_IN_PIXELS = 64.0f;
    m_highScoresTitle.setPosition(titleLeftXPositionInPixels, TITLE_Y_POSITION_IN_PIXELS);

    // ADD EACH OF THE HIGH SCORES TO THE LIST OF HIGH SCORES.
    const unsigned int SCORE_FONT_HEIGHT_IN_PIXELS = 18;
    const float FIRST_SCORE_Y_POSITION_IN_PIXELS = 160.0f;
    const float BUFFER_SPACE_BETWEEN_SCORES = 8.0f;

    std::array<uint16_t, SAVE_DATA::HighScores::MAX_HIGH_SCORES_COUNT> sortedHighScores = 
        highScores.GetHighScoresInDescendingOrder();

    float currentScoreYPositionInPixels = FIRST_SCORE_Y_POSITION_IN_PIXELS;
    for (uint16_t score : sortedHighScores)
    {
        // Pad the score with zeroes on the left.
        std::ostringstream scoreString;
        scoreString.fill('0');
        const std::streamsize MAX_SCORE_DIGIT_COUNT = 5;
        scoreString.width(MAX_SCORE_DIGIT_COUNT);
        scoreString << std::right << score;

        // Create drawable text for the score.
        sf::Text currentScoreText(scoreString.str(), *highScoresFont, SCORE_FONT_HEIGHT_IN_PIXELS);

        // Center it horizontally.
        float scoreWidth = currentScoreText.getLocalBounds().width;
        float scoreHalfWidth = scoreWidth / 2.0f;
        float scoreXPositionInPixels = screenCenterXInPixels - scoreHalfWidth;
        currentScoreText.setPosition(scoreXPositionInPixels, currentScoreYPositionInPixels);


        m_highScores.push_back(currentScoreText);

        // Adjust the score position for the next score.
        currentScoreYPositionInPixels += BUFFER_SPACE_BETWEEN_SCORES + SCORE_FONT_HEIGHT_IN_PIXELS;
    }
}