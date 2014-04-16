#include <SFML/Window.hpp>
#include "Input/KeyboardController.h"

using namespace INPUT;

KeyboardController::KeyboardController()
{
    // Nothing else to do.
}
        
KeyboardController::~KeyboardController()
{
    // Nothing else to do.
}

bool KeyboardController::LeftButtonPressed() const
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}

bool KeyboardController::RightButtonPressed() const
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}

bool KeyboardController::FireButtonPressed() const
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}