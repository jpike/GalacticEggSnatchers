#include "Objects/Alien.h"

using namespace OBJECTS;

// STATIC CONSTANTS.
const float Alien::DEFAULT_MOVE_SPEED_IN_PIXELS_PER_SECOND = 64.0f;

// INSTANCE METHODS.

Alien::Alien(
    const unsigned int minTimeBetweenMissileFiresInSeconds,
    const unsigned int maxTimeBetweenMissileFiresInSeconds,
    const float moveSpeedInPixelsPerSecond, 
    const std::shared_ptr<sf::Sprite>& sprite, 
    const std::shared_ptr<sf::Texture>& missileTexture,
    const std::shared_ptr<sf::SoundBuffer>& missileSound) :

    m_sprite(sprite),
    // The velocity is initialized so that the alien moves right initially.
    m_velocity(moveSpeedInPixelsPerSecond, 0.0f),
    m_brain(minTimeBetweenMissileFiresInSeconds, maxTimeBetweenMissileFiresInSeconds),
    m_missileTexture(missileTexture),
    m_missileSoundBuffer(missileSound)
{
    // Nothing else to do.
}

/// @todo   Rethink this copy constructor and the copy helper method
///         since we must directly copy the alien anyway with no
///         default constructor for all members.
Alien::Alien(const Alien& alienToCopy) :
    m_sprite(alienToCopy.m_sprite),
    m_velocity(alienToCopy.m_velocity),
    m_brain(alienToCopy.m_brain),
    m_missileTexture(alienToCopy.m_missileTexture),
    m_missileSoundBuffer(alienToCopy.m_missileSoundBuffer)
{
    Copy(alienToCopy);
}

Alien::~Alien()
{
    // Nothing else to do.
}

Alien& Alien::operator= (const Alien& rhsAlien)
{
    // CHECK FOR SELF-ASSIGNMENT.
    bool selfAssignment = ( this == &rhsAlien );
    if (!selfAssignment)
    {
        // Copy the values of the right-hand side alien into this alien.
        Copy(rhsAlien);
    }

    // RETURN THIS OBJECT.
    return (*this);
}

void Alien::Update(const sf::Time& elapsedTime)
{
    // MOVE THE ALIEN BASED ON ITS VELOCITY.
    sf::Vector2f movementForThisFrame = elapsedTime.asSeconds() * m_velocity;
    m_sprite->move(movementForThisFrame);
}

void Alien::Render(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(*m_sprite);
}

sf::FloatRect Alien::GetBoundingRectangle() const
{
    return m_sprite->getGlobalBounds();
}

void Alien::SetTopPosition(const float topPositionInPixels)
{
    // Preserve the same horizontal position.
    float currentXPosition = m_sprite->getPosition().x;

    // The alien is positioned based on its top-left corner, so we can
    // change just its top position directly.
    m_sprite->setPosition(currentXPosition, topPositionInPixels);
}

void Alien::SetBottomPosition(const float bottomPositionInPixels)
{
    // Preserve the same horizontal position.
    float currentXPosition = m_sprite->getPosition().x;
    
    // The alien is positioned based on its top-left corner, so we need
    // to calculate a new top position for it.
    sf::FloatRect boundingRectangle = GetBoundingRectangle();
    float newTopPosition = bottomPositionInPixels - boundingRectangle.height;
    m_sprite->setPosition(currentXPosition, newTopPosition);
}

void Alien::SetLeftPosition(const float leftPositionInPixels)
{
    // Preserve the same vertical position.
    float currentYPosition = m_sprite->getPosition().y;

    // The alien is positioned based on its top-left corner, so we can
    // change just its left position directly.
    m_sprite->setPosition(leftPositionInPixels, currentYPosition);
}

void Alien::SetRightPosition(float rightPositionInPixels)
{
    // Preserve the same vertical position.
    float currentYPosition = m_sprite->getPosition().y;

    // The alien is positioned based on its top-left corner, so we need
    // to calculate a new left position for it.
    sf::FloatRect boundingRectangle = GetBoundingRectangle();
    float newLeftPosition = rightPositionInPixels - boundingRectangle.width;
    m_sprite->setPosition(newLeftPosition, currentYPosition);
}

void Alien::OnWorldBoundaryCollide()
{
    // MOVE THE ALIEN CLOSER TO THE GROUND.
    // The alien has reached either the left/right boundary, so move it further down
    // so that it gets closer to the player/eggs/bottom of the screen.
    const float ALIEN_VERTICAL_MOVEMENT_IN_PIXELS_PER_COLLISION = 8.0f;
    m_sprite->move(0.0f, ALIEN_VERTICAL_MOVEMENT_IN_PIXELS_PER_COLLISION);
    
    // MAKE THE ALIEN MOVE IN THE OPPOSITE DIRECTION.
    // We simply flip the velocity.
    m_velocity *= -1.0f;
}

bool Alien::WantsToFireMissile()
{
    return m_brain.ShouldFireMissile();
}

std::shared_ptr<WEAPONS::Missile> Alien::FireMissile() const
{
    // POSITION THE MISSILE SPRITE SO THAT IT FIRES FROM THE ALIEN.
    // Ensure that the missile is fired from the horizontal center of the alien.
    const sf::Vector2f& alienPosition = m_sprite->getPosition();
    float alienXPosition = alienPosition.x;
    sf::FloatRect alienBoundingRectangle = GetBoundingRectangle();
    float halfAlienWidth = (alienBoundingRectangle.width / 2.0f);
    float xPositionInCenterOfAlien = (alienPosition.x + halfAlienWidth);

    // Ensure that the missile is fired from below the alien.
    float yPositionBelowAlien = (alienPosition.y + alienBoundingRectangle.height);

    // Adjust the position from the center of the alien based on how wide the missile is.
    float missileWidth = static_cast<float>(m_missileTexture->getSize().x);
    float halfMissileWidth = (missileWidth / 2.0f);
    float missileXPosition = (xPositionInCenterOfAlien - halfMissileWidth);

    // Create the sprite for the missile.
    std::shared_ptr<sf::Sprite> missileSprite = std::make_shared<sf::Sprite>(*m_missileTexture);
    missileSprite->setPosition(missileXPosition, yPositionBelowAlien);

    // CREATE A SOUND FOR THE MISSILE.
    std::shared_ptr<sf::Sound> missileSound = std::make_shared<sf::Sound>(*m_missileSoundBuffer);

    // FIRE THE MISSILE DOWNWARD FROM THE ALIEN.
    const float NO_HORIZONTAL_MOVEMENT = 0.0f;
    const float MISSILE_Y_VELOCITY_IN_PIXELS_PER_SECOND = 192.0f;
    sf::Vector2f missileVelocity(NO_HORIZONTAL_MOVEMENT, MISSILE_Y_VELOCITY_IN_PIXELS_PER_SECOND);
    
    std::shared_ptr<OBJECTS::WEAPONS::Missile> alienMissile = std::make_shared<OBJECTS::WEAPONS::Missile>(
        OBJECTS::WEAPONS::MISSILE_SOURCE_ALIEN,
        missileVelocity,
        missileSprite,
        missileSound);

    return alienMissile;
}

void Alien::Copy(const Alien& alienToCopy)
{
    this->m_sprite = alienToCopy.m_sprite;
}
