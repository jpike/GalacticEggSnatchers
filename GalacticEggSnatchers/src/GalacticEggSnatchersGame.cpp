#include "GalacticEggSnatchersGame.h"
#include "States/AllStates.h"

// STATIC CONSTANT INITIALIZATION.
const unsigned int GalacticEggSnatchersGame::SCREEN_WIDTH_IN_PIXELS = 448;
const unsigned int GalacticEggSnatchersGame::SCREEN_HEIGHT_IN_PIXELS = 512;
const sf::String GalacticEggSnatchersGame::GAME_TITLE = "Galactic Egg Snatchers";

// METHOD IMPLEMENTATION.

GalacticEggSnatchersGame::GalacticEggSnatchersGame() :
    m_gameStates()
{
    InitializeFirstGameState();
}
    
GalacticEggSnatchersGame::~GalacticEggSnatchersGame()
{
    // Nothing else to do.
}

void GalacticEggSnatchersGame::Update(const sf::Time& elapsedTime)
{
    // Update the current state.
    std::shared_ptr<STATES::IGameState>& currentState = m_gameStates.top();
    currentState->Update(elapsedTime);
}

void GalacticEggSnatchersGame::Render(sf::RenderTarget& renderTarget)
{
    // Render the current state.
    std::shared_ptr<STATES::IGameState>& currentState = m_gameStates.top();
    currentState->Render(renderTarget);
}

void GalacticEggSnatchersGame::InitializeFirstGameState()
{
    /// @todo   Change the initial state to the title state once it is implemented.
    sf::FloatRect screenBoundsInPixels(
        0.0f,
        0.0f,
        static_cast<float>(SCREEN_WIDTH_IN_PIXELS), 
        static_cast<float>(SCREEN_HEIGHT_IN_PIXELS));
    std::shared_ptr<STATES::IGameState> initialState = std::make_shared<STATES::GameplayState>(screenBoundsInPixels);
    m_gameStates.push(initialState);
}