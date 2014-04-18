#include "Objects/Weapons/Missile.h"

using namespace OBJECTS::WEAPONS;

Missile::Missile(
    const MissileSource source,
    const sf::Vector2f& velocity,
    const std::shared_ptr<sf::Sprite>& sprite) :
    m_source(source),
    m_velocity(velocity),
    m_sprite(sprite)
{
    // Nothing else to do.
}

Missile::Missile(const Missile& missileToCopy)
{
    Copy(missileToCopy);
}

Missile::~Missile()
{
    // Nothing else to do.
}

Missile& Missile::operator= (const Missile& rhsMissile)
{
    // CHECK FOR SELF-ASSIGNMENT.
    bool selfAssignment = ( this == &rhsMissile );
    if (!selfAssignment)
    {
        // Copy the values of the right-hand side missile into this missile.
        Copy(rhsMissile);
    }

    // RETURN THIS OBJECT.
    return (*this);
}

void Missile::Update(const sf::Time& elapsedTime)
{
    // MOVE THE MISSILE BASED ON ITS VELOCITY.
    sf::Vector2f movementForThisFrame = elapsedTime.asSeconds() * m_velocity;
    m_sprite->move(movementForThisFrame);
}

sf::FloatRect Missile::GetBoundingRectangle() const
{
    return m_sprite->getGlobalBounds();
}


void Missile::SetTopPosition(const float topPositionInPixels)
{
    // Preserve the same horizontal position.
    float currentXPosition = m_sprite->getPosition().x;

    // The missile is positioned based on its top-left corner, so we can
    // change just its top position directly.
    m_sprite->setPosition(currentXPosition, topPositionInPixels);
}

void Missile::SetBottomPosition(const float bottomPositionInPixels)
{
    // Preserve the same horizontal position.
    float currentXPosition = m_sprite->getPosition().x;
    
    // The missile is positioned based on its top-left corner, so we need
    // to calculate a new top position for it.
    sf::FloatRect boundingRectangle = GetBoundingRectangle();
    float newTopPosition = bottomPositionInPixels - boundingRectangle.height;
    m_sprite->setPosition(currentXPosition, newTopPosition);
}

void Missile::SetLeftPosition(const float leftPositionInPixels)
{
    // Preserve the same vertical position.
    float currentYPosition = m_sprite->getPosition().y;

    // The missile is positioned based on its top-left corner, so we can
    // change just its left position directly.
    m_sprite->setPosition(leftPositionInPixels, currentYPosition);
}

void Missile::SetRightPosition(float rightPositionInPixels)
{
    // Preserve the same vertical position.
    float currentYPosition = m_sprite->getPosition().y;

    // The bunny is positioned based on its top-left corner, so we need
    // to calculate a new left position for it.
    sf::FloatRect boundingRectangle = GetBoundingRectangle();
    float newLeftPosition = rightPositionInPixels - boundingRectangle.width;
    m_sprite->setPosition(newLeftPosition, currentYPosition);
}

void Missile::OnWorldBoundaryCollide()
{
    /// @todo Have the missile disappear.
}

void Missile::Render(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(*m_sprite);
}

MissileSource Missile::GetMissileSource() const
{
    return m_source;
}

void Missile::Copy(const Missile& missileToCopy)
{
    this->m_source = missileToCopy.m_source;
    this->m_velocity = missileToCopy.m_velocity;
    this->m_sprite = missileToCopy.m_sprite;
}
