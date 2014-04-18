#pragma once

#include <random>
#include <SFML/System.hpp>

/// @brief  Code related to artificial intelligence.
namespace ARTIFICIAL_INTELLIGENCE
{
    ////////////////////////////////////////////////////////
    /// @brief  The artificial intelligence "brain" that is used
    ///         to make decisions for aliens.
    ////////////////////////////////////////////////////////
    class AlienAiBrain
    {
    public:
        /// @brief  Constructor.
        explicit AlienAiBrain();
        
        /// @brief      Copy constructor.
        /// @param[in]  brainToCopy - The brain to copy from.
        AlienAiBrain(const AlienAiBrain& brainToCopy);

        /// @brief  Destructor.
        ~AlienAiBrain();

        /// @brief      Assignment operator.
        /// @param[in]  rhsBrain - The brain on the right-hand side of the operator.
        /// @return     This brain with data copied from the provided brain.
        AlienAiBrain& operator= (const AlienAiBrain& rhsBrain);

        /// @brief  Determines whether this alien brain desires firing a missile.
        /// @return True if the brain wants to fire a missile; false otherwise.
        bool ShouldFireMissile();

    private:
        /// @brief      Helper method for copying.
        /// @param[in]  brainToCopy - The brain to copy.
        void Copy(const AlienAiBrain& brainToCopy);
        
        /// @brief  Initializes the internal random number generator.
        void InitializeRandomNumberGenerator();

        /// @brief  Initializes the minimum required time between missile fires.
        void InitializeTimeBetweenMissileFires();

        sf::Clock m_missileFiringClock;    ///< A clock for tracking how much time passes between desiring firing a missile.
        float m_minTimeBetweenMissileFiresInSeconds;    ///< The minimum amount of time required between missile fires in seconds.
        std::default_random_engine m_randomNumberGenerator; ///< The random number generator used for making decisions.
    };
}