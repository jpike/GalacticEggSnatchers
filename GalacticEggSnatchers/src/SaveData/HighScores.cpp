#include <algorithm>
#include <stdexcept>
#include "SaveData/HighScores.h"

using namespace SAVE_DATA;

HighScores::HighScores() :
    m_highScores()
{
    // Nothing else to do.
}

HighScores::HighScores(const HighScores& highScoresToCopy)
{
    Copy(highScoresToCopy);
}

HighScores::~HighScores()
{
    // Nothing else to do.
}

HighScores& HighScores::operator= (const HighScores& rhsHighScores)
{
    // CHECK FOR SELF-ASSIGNMENT.
    bool selfAssignment = (this == &rhsHighScores);
    if (!selfAssignment)
    {
        // Copy the right-hand side object into this object.
        Copy(rhsHighScores);
    }

    return *this;
}

void HighScores::AddHighScore(const uint16_t highScore)
{
    // CHECK IF THERE IS ROOM FOR ANOTHER HIGH SCORE.
    bool roomAvailableForNewScore = (m_highScores.size() <= MAX_HIGH_SCORES_COUNT);
    if (roomAvailableForNewScore)
    {
        m_highScores.push_back(highScore);
    }
    else
    {
        throw std::runtime_error("Error adding high score - too many high scores already exist.");
    }
}

std::array<uint16_t, HighScores::MAX_HIGH_SCORES_COUNT> HighScores::GetHighScoresInDescendingOrder()
{
    // SORT THE HIGH SCORES.
    // They are sorted in ascending order by default, but we want them sorted in descending order.
    auto sortDescending = [](uint16_t leftScore, uint16_t rightScore) { return (leftScore > rightScore); };
    std::stable_sort(m_highScores.begin(), m_highScores.end(), sortDescending);
    
    // CONVERT THE HIGH SCORES TO AN ARRAY.
    std::array<uint16_t, MAX_HIGH_SCORES_COUNT> sortedHighScores;
    for (unsigned int addedHighScoreCount = 0; addedHighScoreCount < sortedHighScores.size(); ++addedHighScoreCount)
    {
        // ADD THE STORED HIGH SCORE IF AVAILABLE.
        bool highScoreForCurrentIndexExists = (m_highScores.size() > addedHighScoreCount);
        if (highScoreForCurrentIndexExists)
        {
            sortedHighScores[addedHighScoreCount] = m_highScores[addedHighScoreCount];
        }
        else
        {
            // Add a 0 for this high score index.
            sortedHighScores[addedHighScoreCount] = 0;
        }
    }

    return sortedHighScores;
}

void HighScores::Copy(const HighScores& highScoresToCopy)
{
    this->m_highScores = highScoresToCopy.m_highScores;
}
