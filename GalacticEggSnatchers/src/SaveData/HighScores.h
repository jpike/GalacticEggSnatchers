#pragma once

#include <array>
#include <cstdint>
#include <vector>

/// @brief  Code related to saved data.
namespace SAVE_DATA
{
    ////////////////////////////////////////////////////////
    /// @brief  A collection of high scores for the game.
    ////////////////////////////////////////////////////////
    class HighScores
    {
    public:
        static const unsigned int MAX_HIGH_SCORES_COUNT = 5;    ///< The maximum number of high scores supported.

        /// @brief  Constructor.
        explicit HighScores();

        /// @brief      Copy constructor.
        /// @param[in]  highScoresToCopy - The high scores to copy.
        HighScores(const HighScores& highScoresToCopy);

        /// @brief  Destructor.
        ~HighScores();

        /// @brief      Assignment operator.
        /// @param[in]  rhsHighScores - The high scores on the right-hand side of the assignment operator.
        HighScores& operator= (const HighScores& rhsHighScores);

        /// @brief      Adds the provided high score to the collection of high scores,
        ///             if room is available.  If MAX_HIGH_SCORES_COUNT high scores
        ///             are already in this collection, them an exception is thrown.
        /// @param[in]  highScore - The high score to add.
        void AddHighScore(const uint16_t highScore);

        /// @brief      Gets the high scores in descending (decreasing) order.
        /// @return     The high scores in descending order.
        std::array<uint16_t, MAX_HIGH_SCORES_COUNT> GetHighScoresInDescendingOrder();

    private:

        /// @brief      Copies the provided high scores into this object.
        /// @param[in]  highScoresToCopy - The high scores to copy.
        void Copy(const HighScores& highScoresToCopy);

        std::vector<uint16_t> m_highScores; ///< A list of the high scores.  Not guaranteed to be in any particular order.
    };
}