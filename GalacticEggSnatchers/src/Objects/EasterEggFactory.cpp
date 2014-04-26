#include <chrono>
#include <random>
#include "Objects/EasterEggFactory.h"

using namespace OBJECTS;

// INITIALIZE THE STATIC MEMBERS.
const std::array<char*, EasterEggFactory::EGG_TEXTURE_COUNT> EasterEggFactory::EGG_TEXTURE_FILEPATHS =
{
    "res/Images/Egg04.png",
    "res/Images/Egg05.png",
    "res/Images/Egg06.png",
    "res/Images/Egg07.png",
    "res/Images/Egg08.png"
};

// STATIC METHODS.

std::string EasterEggFactory::GetRandomEggTextureFilepath()
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

    // SELECT A RANDOM EGG TEXTURE.
    // An random index is selected that is restricted to the valid range of indices
    // into the egg texture array.
    unsigned int randomEggTextureIndex = ( randomNumberGenerator() % EGG_TEXTURE_FILEPATHS.size() );
    return EGG_TEXTURE_FILEPATHS[randomEggTextureIndex];
}