#pragma once

#include <array>
#include <string>

namespace OBJECTS
{
    ////////////////////////////////////////////////////////
    /// @brief  A factory class that supports creating different
    ///         types of aliens.  It is not intended to be
    ///         instantiated.
    ////////////////////////////////////////////////////////
    class AlienFactory
    {
    public:

        /// @brief  Randomly selects an alien texture.
        /// @return The filepath to the randomly selected alien texture.
        static std::string GetRandomAlienTextureFilepath();

    private:
        AlienFactory(); ///< Private constructor to prevent instantiation.
        AlienFactory(const AlienFactory& factoryToCopy);    ///< Private to disallow copying.
        ~AlienFactory();    ///< Private destructor since this class isn't supposed to be instantiated.
        AlienFactory& operator= (const AlienFactory& factoryToCopy);    ///< Private to disallow assignment.

        static const unsigned int ALIEN_TEXTURE_COUNT = 2;  ///< The 
        static const std::array<char*, ALIEN_TEXTURE_COUNT> ALIEN_TEXTURE_FILEPATHS; ///< The available alien texture filepaths.
    };
}