#include "Resources/ResourceManager.h"

using namespace RESOURCES;

ResourceManager::ResourceManager() :
    m_textures(),
    m_fonts(),
    m_sounds()
{
    // Nothing to do.
}

ResourceManager::~ResourceManager()
{
    // Nothing to do.
}

std::shared_ptr<sf::Texture> ResourceManager::GetTexture(const std::string& filepath)
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

std::shared_ptr<sf::Font> ResourceManager::GetFont(const std::string& filepath)
{
    // CHECK IF THIS SPECIFIED FONT HAS ALREADY BEEN LOADED.
    auto preloadedFontResource = m_fonts.find(filepath);
    bool fontAlreadyLoaded = (preloadedFontResource != m_fonts.end());
    if (fontAlreadyLoaded)
    {
        // Return the already loaded font resource.
        return preloadedFontResource->second;
    }

    // CREATE A FONT FROM FILE.
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

std::shared_ptr<sf::SoundBuffer> ResourceManager::GetSoundBuffer(const std::string& filepath)
{
    // CHECK IF THIS SPECIFIED SOUND BUFFER HAS ALREADY BEEN LOADED.
    auto preloadedSoundResource = m_sounds.find(filepath);
    bool soundAlreadyLoaded = (preloadedSoundResource != m_sounds.end());
    if (soundAlreadyLoaded)
    {
        // Return the already loaded sound resource.
        return preloadedSoundResource->second;
    }

    // CREATE A SOUND BUFFER FROM FILE.
    std::shared_ptr<sf::SoundBuffer> soundBuffer = std::make_shared<sf::SoundBuffer>();
    bool soundLoaded = soundBuffer->loadFromFile(filepath);
    if (soundLoaded)
    {
        // Store the sound in this object so that it persists in memory.
        m_sounds[filepath] = soundBuffer;

        return soundBuffer;
    }
    else
    {
        // No sound buffer could be loaded.
        return nullptr;
    }
}