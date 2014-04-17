#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

/// @brief  Code related to graphics.
namespace GRAPHICS
{
    ////////////////////////////////////////////////////////
    /// @brief  Responsible for managing graphics resources.
    ////////////////////////////////////////////////////////
    class GraphicsSystem
    {
    public:
        /// @brief  Constructor.
        explicit GraphicsSystem();

        /// @brief  Destructor.
        ~GraphicsSystem();

        /// @brief      Gets the specified texture resource.
        ///             It will persist in memory as long as this object is alive.
        ///             If a texture at the specified filepath has already been loaded,
        ///             the existing resource may be returned as opposed to loading
        ///             a new instance.
        /// @param[in]  filepath - The filepath (relative or absolute) path to the texture file.
        /// @return     The texture resource, if successfully loaded.  Nullptr otherwise.
        std::shared_ptr<sf::Texture> GetTexture(const std::string& filepath);

    private:
        GraphicsSystem(const GraphicsSystem& systemToCopy);   ///< Private to disallow copying.
        GraphicsSystem& operator= (const GraphicsSystem& collisionSystem);    ///< Private to disallow assignment.

        std::unordered_map< std::string, std::shared_ptr<sf::Texture> > m_textures; ///< Texture resources managed by this system.
    };
}