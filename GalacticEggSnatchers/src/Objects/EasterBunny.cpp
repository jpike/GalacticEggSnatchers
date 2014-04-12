#include "Objects/EasterBunny.h"

using namespace OBJECTS;

EasterBunny::EasterBunny(
    const std::shared_ptr<sf::Sprite>& sprite,
    const std::shared_ptr<INPUT::IInputController>& inputController) :
    m_sprite(sprite),
    m_inputController(inputController)
{
    /// @todo
}

EasterBunny::EasterBunny(const EasterBunny& bunnyToCopy)
{
    /// @todo
}

EasterBunny::~EasterBunny()
{
    /// @todo
}

EasterBunny& EasterBunny::operator= (const EasterBunny& rhsBunny)
{
    /// @todo
    return *this;
}

void EasterBunny::Update(const sf::Time& elapsedTime)
{
    /// @todo
}

void EasterBunny::Copy(const EasterBunny& bunnyToCopy)
{
    /// @todo
}
