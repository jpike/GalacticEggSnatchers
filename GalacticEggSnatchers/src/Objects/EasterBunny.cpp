#include "Objects/EasterBunny.h"

using namespace OBJECTS;

// STATIC CONSTANTS.
const float EasterBunny::MOVE_SPEED_IN_PIXELS_PER_SECOND = 128.0f;

// INSTANCE METHODS.

EasterBunny::EasterBunny(const std::shared_ptr<sf::Sprite>& sprite) :
    m_sprite(sprite)
{
    // Nothing else to do.
}

EasterBunny::EasterBunny(const EasterBunny& bunnyToCopy)
{
    Copy(bunnyToCopy);
}

EasterBunny::~EasterBunny()
{
    // Nothing else to do.
}

EasterBunny& EasterBunny::operator= (const EasterBunny& rhsBunny)
{
    // CHECK FOR SELF-ASSIGNMENT.
    bool selfAssignment = ( this == &rhsBunny );
    if (!selfAssignment)
    {
        // Copy the values of the right-hand side bunny into this bunny.
        Copy(rhsBunny);
    }

    // RETURN THIS OBJECT.
    return (*this);
}

sf::FloatRect EasterBunny::GetBoundingRectangle() const
{
    return m_sprite->getGlobalBounds();
}


void EasterBunny::SetTopPosition(const float topPositionInPixels)
{
    // Preserve the same horizontal position.
    float currentXPosition = m_sprite->getPosition().x;

    // The bunny is positioned based on its top-left corner, so we can
    // change just its top position directly.
    m_sprite->setPosition(currentXPosition, topPositionInPixels);
}

void EasterBunny::SetBottomPosition(const float bottomPositionInPixels)
{
    // Preserve the same horizontal position.
    float currentXPosition = m_sprite->getPosition().x;
    
    // The bunny is positioned based on its top-left corner, so we need
    // to calculate a new top position for it.
    sf::FloatRect boundingRectangle = GetBoundingRectangle();
    float newTopPosition = bottomPositionInPixels - boundingRectangle.height;
    m_sprite->setPosition(currentXPosition, newTopPosition);
}

void EasterBunny::SetLeftPosition(const float leftPositionInPixels)
{
    // Preserve the same vertical position.
    float currentYPosition = m_sprite->getPosition().y;

    // The bunny is positioned based on its top-left corner, so we can
    // change just its left position directly.
    m_sprite->setPosition(leftPositionInPixels, currentYPosition);
}

void EasterBunny::SetRightPosition(float rightPositionInPixels)
{
    // Preserve the same vertical position.
    float currentYPosition = m_sprite->getPosition().y;

    // The bunny is positioned based on its top-left corner, so we need
    // to calculate a new left position for it.
    sf::FloatRect boundingRectangle = GetBoundingRectangle();
    float newLeftPosition = rightPositionInPixels - boundingRectangle.width;
    m_sprite->setPosition(newLeftPosition, currentYPosition);
}

void EasterBunny::OnWorldBoundaryCollide()
{
    // Nothing needs to be done for the bunny.  The collision
    // system should be responsible for confining the bunny to
    // screen boundaries, and that is all that needs to happen
    // to the bunny when it collides with a screen boundary.
}

void EasterBunny::Update(const sf::Time& elapsedTime)
{
    // Nothing else to do yet.
}

void EasterBunny::MoveLeft(const sf::Time& elapsedTime)
{
    const float NO_VERTICAL_MOVEMENT = 0.0f;
    float leftMovementInPixels = -1.0f * MOVE_SPEED_IN_PIXELS_PER_SECOND * elapsedTime.asSeconds();

    m_sprite->move(leftMovementInPixels, NO_VERTICAL_MOVEMENT);
}

void EasterBunny::MoveRight(const sf::Time& elapsedTime)
{
    const float NO_VERTICAL_MOVEMENT = 0.0f;
    float rightMovementInPixels = MOVE_SPEED_IN_PIXELS_PER_SECOND * elapsedTime.asSeconds();

    m_sprite->move(rightMovementInPixels, NO_VERTICAL_MOVEMENT);
}

std::shared_ptr<OBJECTS::WEAPONS::Missile> EasterBunny::FireMissile()
{
    /// @todo
    return std::shared_ptr<OBJECTS::WEAPONS::Missile>();
}

void EasterBunny::Copy(const EasterBunny& bunnyToCopy)
{
    this->m_sprite = bunnyToCopy.m_sprite;
}
