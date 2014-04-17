#include "Objects/Alien.h"

using namespace OBJECTS;

Alien::Alien(const std::shared_ptr<sf::Sprite>& sprite) :
    m_sprite(sprite)
{
    /// @todo
}

Alien::Alien(const Alien& alienToCopy)
{
    /// @todo
}

Alien::~Alien()
{
    /// @todo
}

Alien& Alien::operator= (const Alien& rhsAlien)
{
    /// @todo
    return *this;
}

void Alien::Update(const sf::Time& elapsedTime)
{
    /// @todo
}

void Alien::Render(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(*m_sprite);
}

void Alien::Copy(const Alien& alienToCopy)
{
    /// @todo
}
