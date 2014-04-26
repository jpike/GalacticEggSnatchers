#include "Objects/Explosion.h"

using namespace OBJECTS;

// STATIC CONSTANT INITIALIZATION.
const float Explosion::MAX_LIFETIME_IN_SECONDS = 1.0f;

Explosion::Explosion(const std::shared_ptr<sf::Sprite>& sprite, const std::shared_ptr<sf::Sound>& sound) :
    m_lifetime(sf::Time::Zero),
    m_sprite(sprite),
    m_sound(sound)
{
    // Play the explosion sound.
    m_sound->play();
}

Explosion::~Explosion()
{
    // Nothing else to do.
}

void Explosion::Update(const sf::Time& elapsedTime)
{
    // TRACK THE TOTAL TIME THIS OBJECT HAS BEEN ALIVE.
    m_lifetime += elapsedTime;
}

void Explosion::Render(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(*m_sprite);
}

bool Explosion::LifetimeExceeded() const
{
    bool lifetimeExceeded = (m_lifetime.asSeconds() > MAX_LIFETIME_IN_SECONDS);
    return lifetimeExceeded;
}