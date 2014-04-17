#include "Graphics/GraphicsSystem.h"

using namespace GRAPHICS;

GraphicsSystem::GraphicsSystem() :
    m_textures()
{
    // Nothing to do.
}

GraphicsSystem::~GraphicsSystem()
{
    // Nothing to do.
}

std::shared_ptr<sf::Texture> GraphicsSystem::GetTexture(const std::string& filepath)
{
    // CHECK IF THIS SPECIFIED TEXTURE HAS ALREADY BEEN LOADED.
    auto preloadedTextureResource = m_textures.find(filepath);
    bool textureAlreadyLoaded = (preloadedTextureResource != m_textures.end());
    if (textureAlreadyLoaded)
    {
        // Return the already loaded texture resource.
        return preloadedTextureResource->second;
    }

    // LOAD THE TEXTURE FROM FILE.
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    bool textureLoaded = texture->loadFromFile(filepath);
    if (textureLoaded)
    {
        // Store the texture in this object so that it persists in memory.
        m_textures[filepath] = texture;

        return texture;
    }
    else
    {
        /// @todo Once all texture resources have been created, this should 
        // return nullptr, not a blank texture.
        const int DUMMY_TEXTURE_SIZE = 32;
        texture->create(DUMMY_TEXTURE_SIZE, DUMMY_TEXTURE_SIZE);
        m_textures[filepath] = texture;
        return texture;

        // No texture could be loaded.
        return nullptr;
    }
}