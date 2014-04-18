#include <chrono>
#include <random>
#include "Objects/AlienFactory.h"

using namespace OBJECTS;

// INITIALIZE THE STATIC MEMBERS.
const std::array<char*, AlienFactory::ALIEN_TEXTURE_COUNT> AlienFactory::ALIEN_TEXTURE_FILEPATHS =
{
    "res/Images/alien1.png",
    "res/Images/alien2.png"
};

// STATIC METHODS.

std::string AlienFactory::GetRandomAlienTextureFilepath()
{
    // MAKE SURE THAT THE RANDOM NUMBER GENERATOR HAS BEEN INITIALIZED.
    static bool randomNumberGeneratorInitialized = false;
    static std::default_random_engine randomNumberGenerator;
    if (!randomNumberGeneratorInitialized)
    {
        // Initialize the random number generator with a seed based on the current time.
        unsigned long seed = static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count());
        randomNumberGenerator.seed(seed);

        randomNumberGeneratorInitialized = true;
    }

    // SELECT A RANDOM ALIEN TEXTURE.
    // An random index is selected that is restricted to the valid range of indices
    // into the alien texture array.
    unsigned int randomAlienTextureIndex = ( randomNumberGenerator() % ALIEN_TEXTURE_FILEPATHS.size() );
    return ALIEN_TEXTURE_FILEPATHS[randomAlienTextureIndex];
}