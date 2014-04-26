#pragma once

#include <array>
#include <string>

namespace OBJECTS
{
    ////////////////////////////////////////////////////////
    /// @brief  A factory class that supports creating different
    ///         types of Easter eggs.  It is not intended to be
    ///         instantiated.
    ////////////////////////////////////////////////////////
    class EasterEggFactory
    {
    public:

        /// @brief  Randomly selects an Easter egg texture.
        /// @return The filepath to the randomly selected egg texture.
        static std::string GetRandomEggTextureFilepath();

    private:
        EasterEggFactory(); ///< Private constructor to prevent instantiation.
        EasterEggFactory(const EasterEggFactory& factoryToCopy);    ///< Private to disallow copying.
        ~EasterEggFactory();    ///< Private destructor since this class isn't supposed to be instantiated.
        EasterEggFactory& operator= (const EasterEggFactory& factoryToCopy);    ///< Private to disallow assignment.

        static const unsigned int EGG_TEXTURE_COUNT = 5;  ///< The number of available egg textures.
        static const std::array<char*, EGG_TEXTURE_COUNT> EGG_TEXTURE_FILEPATHS; ///< The available egg texture filepaths.
    };
}