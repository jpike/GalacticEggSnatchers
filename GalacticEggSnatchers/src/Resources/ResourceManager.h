#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

/// @brief  Code related to resources (files, etc.) for the game.
namespace RESOURCES
{
    ////////////////////////////////////////////////////////
    /// @brief  Responsible for managing resources.
    ////////////////////////////////////////////////////////
    class ResourceManager
    {
    public:
        /// @brief  Constructor.
        explicit ResourceManager();

        /// @brief  Destructor.
        ~ResourceManager();

        /// @brief      Gets the specified texture resource.
        ///             It will persist in memory as long as this object is alive.
        ///             If a texture at the specified filepath has already been loaded,
        ///             the existing resource may be returned as opposed to loading
        ///             a new instance.
        /// @param[in]  filepath - The filepath (relative or absolute) path to the texture file.
        /// @return     The texture resource, if successfully loaded.  Nullptr otherwise.
        std::shared_ptr<sf::Texture> GetTexture(const std::string& filepath);

        /// @brief      Gets the specified font resource.
        ///             It will persist in memory as long as this object is alive.
        ///             If a font at the specified filepath has already been loaded,
        ///             the existing resource may be returned as opposed to loading
        ///             a new instance.
        /// @param[in]  filepath - The filepath (relative or absolute) path to the font file.
        /// @return     The font resource, if successfully loaded.  Nullptr otherwise.
        std::shared_ptr<sf::Font> GetFont(const std::string& filepath);

        /// @brief      Gets the specified sound buffer resource.
        ///             It will persist in memory as long as this object is alive.
        ///             If a sound buffer at the specified filepath has already been loaded,
        ///             the existing resource may be returned as opposed to loading
        ///             a new instance.
        /// @param[in]  filepath - The filepath (relative or absolute) path to the sound file.
        /// @return     The sound buffer resource, if successfully loaded.  Nullptr otherwise.
        std::shared_ptr<sf::SoundBuffer> GetSoundBuffer(const std::string& filepath);

    private:
        ResourceManager(const ResourceManager& systemToCopy);   ///< Private to disallow copying.
        ResourceManager& operator= (const ResourceManager& collisionSystem);    ///< Private to disallow assignment.

        std::unordered_map< std::string, std::shared_ptr<sf::Texture> > m_textures; ///< Texture resources managed by this object.
        std::unordered_map< std::string, std::shared_ptr<sf::Font> > m_fonts;   ///< Font resources managed by this object.
        std::unordered_map< std::string, std::shared_ptr<sf::SoundBuffer> > m_sounds;   ///< Sound resources managed by this object.
    };
}