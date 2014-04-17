#include "Objects/EasterEgg.h"

using namespace OBJECTS;

EasterEgg::EasterEgg(const std::shared_ptr<sf::Sprite>& sprite) :
    m_sprite(sprite)
{
    /// @todo
}

EasterEgg::EasterEgg(const EasterEgg& eggToCopy)
{
    /// @todo
}

EasterEgg::~EasterEgg()
{
    /// @todo
}

EasterEgg& EasterEgg::operator= (const EasterEgg& rhsEgg)
{
    /// @todo
    return *this;
}

void EasterEgg::Update(const sf::Time& elapsedTime)
{
    /// @todo
}

void EasterEgg::Render(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(*m_sprite);
}

void EasterEgg::Copy(const EasterEgg& eggToCopy)
{
    /// @todo
}
