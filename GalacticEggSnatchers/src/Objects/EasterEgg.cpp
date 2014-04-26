#include "Objects/EasterEgg.h"

using namespace OBJECTS;

// STATIC MEMBER INITIALIZATION.
const uint8_t EasterEgg::DEFAULT_HEALTH = 4;

// INSTANCE METHODS.

EasterEgg::EasterEgg(const std::shared_ptr<sf::Sprite>& sprite) :
    m_sprite(sprite),
    m_health(DEFAULT_HEALTH)
{
    // Nothing else to do.
}

EasterEgg::EasterEgg(const EasterEgg& eggToCopy)
{
    Copy(eggToCopy);
}

EasterEgg::~EasterEgg()
{
    // Nothing else to do.
}

EasterEgg& EasterEgg::operator= (const EasterEgg& rhsEgg)
{
    // CHECK FOR SELF-ASSIGNMENT.
    bool selfAssignment = ( this == &rhsEgg );
    if (!selfAssignment)
    {
        // Copy the values of the right-hand side egg into this egg.
        Copy(rhsEgg);
    }

    // RETURN THIS OBJECT.
    return (*this);
}

void EasterEgg::Update(const sf::Time& elapsedTime)
{
    // FADE THE SPRITE'S COLOR BASED ON HEALTH.
    /// @todo   Replace this with a more advanced shader if time permits.
    const uint8_t MAX_HEALTH = DEFAULT_HEALTH;
    const uint8_t MAX_COLOR_COMPONENT = 255;

    uint8_t fadedColorComponent = m_health * (MAX_COLOR_COMPONENT / MAX_HEALTH);
    sf::Color fadedColor(fadedColorComponent, fadedColorComponent, fadedColorComponent);
    m_sprite->setColor(fadedColor);
}

void EasterEgg::Render(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(*m_sprite);
}

sf::FloatRect EasterEgg::GetBoundingRectangle() const
{
    return m_sprite->getGlobalBounds();
}


void EasterEgg::SetTopPosition(const float topPositionInPixels)
{
    // Preserve the same horizontal position.
    float currentXPosition = m_sprite->getPosition().x;

    // The egg is positioned based on its top-left corner, so we can
    // change just its top position directly.
    m_sprite->setPosition(currentXPosition, topPositionInPixels);
}

void EasterEgg::SetBottomPosition(const float bottomPositionInPixels)
{
    // Preserve the same horizontal position.
    float currentXPosition = m_sprite->getPosition().x;
    
    // The egg is positioned based on its top-left corner, so we need
    // to calculate a new top position for it.
    sf::FloatRect boundingRectangle = GetBoundingRectangle();
    float newTopPosition = bottomPositionInPixels - boundingRectangle.height;
    m_sprite->setPosition(currentXPosition, newTopPosition);
}

void EasterEgg::SetLeftPosition(const float leftPositionInPixels)
{
    // Preserve the same vertical position.
    float currentYPosition = m_sprite->getPosition().y;

    // The egg is positioned based on its top-left corner, so we can
    // change just its left position directly.
    m_sprite->setPosition(leftPositionInPixels, currentYPosition);
}

void EasterEgg::SetRightPosition(float rightPositionInPixels)
{
    // Preserve the same vertical position.
    float currentYPosition = m_sprite->getPosition().y;

    // The egg is positioned based on its top-left corner, so we need
    // to calculate a new left position for it.
    sf::FloatRect boundingRectangle = GetBoundingRectangle();
    float newLeftPosition = rightPositionInPixels - boundingRectangle.width;
    m_sprite->setPosition(newLeftPosition, currentYPosition);
}

void EasterEgg::OnWorldBoundaryCollide()
{
    // Nothing needs to be done for the egg.  Eggs
    // aren't supposed to move, so they should never
    // collide with a world boundary.
}

uint8_t EasterEgg::GetHealth() const
{
    return m_health;
}

void EasterEgg::LoseHealth()
{
    // Only remove health if some health exists.
    bool healthRemains = (m_health > 0);
    if (healthRemains)
    {
        --m_health;
    }
}

void EasterEgg::Copy(const EasterEgg& eggToCopy)
{
    this->m_health = eggToCopy.m_health;
    this->m_sprite = eggToCopy.m_sprite;
}
