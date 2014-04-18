#include "ArtificialIntelligence/AlienAiBrain.h"

using namespace ARTIFICIAL_INTELLIGENCE;

AlienAiBrain::AlienAiBrain() :
    m_missileFiringClock(),
    m_minTimeBetweenMissileFiresInSeconds(),
    m_randomNumberGenerator()
{
    InitializeRandomNumberGenerator();
    InitializeTimeBetweenMissileFires();
}

AlienAiBrain::AlienAiBrain(const AlienAiBrain& brainToCopy) :
    m_missileFiringClock(),
    m_minTimeBetweenMissileFiresInSeconds(),
    m_randomNumberGenerator()
{
    Copy(brainToCopy);
}

AlienAiBrain::~AlienAiBrain()
{
    // Nothing to do.
}

AlienAiBrain& AlienAiBrain::operator= (const AlienAiBrain& rhsBrain)
{
    // CHECK FOR SELF-ASSIGNMENT.
    bool selfAssignment = ( this == &rhsBrain );
    if (!selfAssignment)
    {
        // Copy the values of the right-hand side brain into this brain.
        Copy(rhsBrain);
    }

    // RETURN THIS OBJECT.
    return (*this);
}

bool AlienAiBrain::ShouldFireMissile()
{
    // CHECK IF SUFFICIENT TIME HAS PASSED SINCE A MISSILE WAS LAST DESIRED FOR FIRING.
    // This prevents missiles from being fired too quickly and overwhelming players.
    sf::Time elapsedTimeSinceLastMissileFired = m_missileFiringClock.getElapsedTime();
    float elapsedTimeSinceLastMissileFiredInSeconds = elapsedTimeSinceLastMissileFired.asSeconds();
    bool missileFiringTimeDelayExceeded = (elapsedTimeSinceLastMissileFiredInSeconds > m_minTimeBetweenMissileFiresInSeconds);
    if (!missileFiringTimeDelayExceeded)
    {
        // We need to wait longer before firing a missile.
        return false;
    }
    
    // GENERATE A RANDOM NUMBER TO DETERMINE IF A MISSILE SHOULD BE FIRED.
    // A range of 0 - 99 is used because it is simple to understand in terms of common percentages.
    const unsigned int MAX_RANDOM_RANGE = 100;
    unsigned int randomNumber = (m_randomNumberGenerator() % MAX_RANDOM_RANGE);

    // CHECK IF THE RANDOM NUMBER WAS WITHIN THE MISSILE FIRING THRESHOLD.
    // A missile should only be fired if the random number is below a certain value.
    // This value may be adjusted later depending on how the gameplay feels.
    const unsigned int FIRE_MISSILE_MAX_THRESHOLD = 10;
    bool shouldFireMissile = (randomNumber < FIRE_MISSILE_MAX_THRESHOLD);

    // CHECK IF A MISSILE WAS DESIRED TO BE FIRED.
    if (shouldFireMissile)
    {
        // Reset the clock to allow another missile to be fired after sufficient time passes.
        m_missileFiringClock.restart();
    }

    return shouldFireMissile;
}

void AlienAiBrain::Copy(const AlienAiBrain& brainToCopy)
{
    this->m_missileFiringClock = brainToCopy.m_missileFiringClock;
    this->m_minTimeBetweenMissileFiresInSeconds = brainToCopy.m_minTimeBetweenMissileFiresInSeconds;
    this->m_randomNumberGenerator = brainToCopy.m_randomNumberGenerator;
}
        
void AlienAiBrain::InitializeRandomNumberGenerator()
{
    // Initialize the random number generator with a seed based on the address of this object.
    // This has been found to provide better randomness than seeding based on time.
    unsigned long seed = reinterpret_cast<unsigned long>(this);
    m_randomNumberGenerator.seed(seed);
}

void AlienAiBrain::InitializeTimeBetweenMissileFires()
{
    // GENERATE A RANDOM NUMBER OF SECONDS REQUIRED BETWEEN MISSILE FIRES.
    // This helps give more appearance of randomness in the alien missile firing.
    const unsigned int MIN_TIME_IN_SECONDS = 3;
    const unsigned int MAX_TIME_IN_SECONDS = 60;
    unsigned int randomSeconds = ( (m_randomNumberGenerator() % MAX_TIME_IN_SECONDS) + MIN_TIME_IN_SECONDS );
    m_minTimeBetweenMissileFiresInSeconds = static_cast<float>(randomSeconds);
}