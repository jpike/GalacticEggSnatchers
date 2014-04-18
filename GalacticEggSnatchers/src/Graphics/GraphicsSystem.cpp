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

    // LOAD THE TEXTURE IMAGE FROM FILE.
    std::shared_ptr<sf::Image> textureImage = std::make_shared<sf::Image>();
    bool imageLoaded = textureImage->loadFromFile(filepath);
    if (!imageLoaded)
    {
        return nullptr;
    }
    // Set the standard transparent color for the images.
    const sf::Color TRANSPARENT_COLOR = sf::Color::Magenta;
    textureImage->createMaskFromColor(TRANSPARENT_COLOR);

    // CREATE A TEXTURE FROM THE IMAGE.
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    bool textureLoaded = texture->loadFromImage(*textureImage);
    if (textureLoaded)
    {
        // Store the texture in this object so that it persists in memory.
        m_textures[filepath] = texture;

        return texture;
    }
    else
    {
        // No texture could be loaded.
        return nullptr;
    }
}

std::shared_ptr<sf::Font> GraphicsSystem::GetFont(const std::string& filepath)
{
    // CHECK IF THIS SPECIFIED FONT HAS ALREADY BEEN LOADED.
    auto preloadedFontResource = m_fonts.find(filepath);
    bool fontAlreadyLoaded = (preloadedFontResource != m_fonts.end());
    if (fontAlreadyLoaded)
    {
        // Return the already loaded font resource.
        return preloadedFontResource->second;
    }

    // CREATE A TEXTURE FROM FILE.
    std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
    bool fontLoaded = font->loadFromFile(filepath);
    if (fontLoaded)
    {
        // Store the font in this object so that it persists in memory.
        m_fonts[filepath] = font;

        return font;
    }
    else
    {
        // No font could be loaded.
        return nullptr;
    }
}