#pragma once

#include <memory>
#include <stack>
#include <SFML/Graphics.hpp>
#include "States/IGameState.h"

////////////////////////////////////////////////////////
/// @brief  Encapsulates logic for managing the entire
///         Galactic Egg Snatchers game.
////////////////////////////////////////////////////////
class GalacticEggSnatchersGame
{
public:
    // STATIC CONSTANTS.
    static const unsigned int SCREEN_WIDTH_IN_PIXELS;  ///< The width of the game screen, in pixels.
    static const unsigned int SCREEN_HEIGHT_IN_PIXELS;  ///< The height of the game screen, in pixels.
    static const sf::String GAME_TITLE; ///< The title of the game.

    /// @brief  Constructor.
    explicit GalacticEggSnatchersGame();
    
    /// @brief  Destructor.
    ~GalacticEggSnatchersGame();

    /// @brief      Updates the game for the next frame of processing.
    /// @param[in]  elapsedTime - The elapsed time since the last iteration
    ///             of the main game loop.
    void Update(const sf::Time& elapsedTime);

    /// @brief          Renders the current state of the game.
    /// @param[in,out]  renderTarget - The render target to render to.
    void Render(sf::RenderTarget& renderTarget);

    /// @brief      Handles a key being pressed.
    /// @param[in]  key - The key that was pressed.
    void HandleKeyPress(const sf::Keyboard::Key key);

private:
    GalacticEggSnatchersGame(const GalacticEggSnatchersGame& gameToCopy);   ///< Private to disallow copying.
    GalacticEggSnatchersGame& operator= (const GalacticEggSnatchersGame& rhsGame);  ///< Private to disallow assignment.

    /// @brief  Helper method to get the screen bounds in pixels.
    /// @return The screen bounds in pixels.
    sf::FloatRect GetScreenBoundsInPixels() const;

    /// @brief  Helper method to initialize the first state of the game.
    void InitializeFirstGameState();

    /// @brief      Switches the game to the specified next state.
    /// @param[in]  nextStateType - The type of the state to switch to.
    void SwitchToNextGameState(const STATES::GameStateType nextStateType);

    std::stack< std::shared_ptr<STATES::IGameState> > m_gameStates; ///< The states in the game, with the current state on top.
};