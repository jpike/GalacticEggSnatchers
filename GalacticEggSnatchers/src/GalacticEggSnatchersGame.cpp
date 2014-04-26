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
    // UPDATE THE CURRENT STATE.
    std::shared_ptr<STATES::IGameState>& currentState = m_gameStates.top();
    currentState->Update(elapsedTime);

    // CHECK IF THE GAME IS READY TO MOVE TO A DIFFERENT STATE.
    STATES::GameStateType nextGameState = currentState->GetNextState();
    bool validNextGameState = (STATES::GAME_STATE_TYPE_INVALID != nextGameState);
    if (validNextGameState)
    {
        SwitchToNextGameState(nextGameState);
    }
}

void GalacticEggSnatchersGame::Render(sf::RenderTarget& renderTarget)
{
    // Render the current state.
    std::shared_ptr<STATES::IGameState>& currentState = m_gameStates.top();
    currentState->Render(renderTarget);
}

void GalacticEggSnatchersGame::HandleKeyPress(const sf::Keyboard::Key key)
{
    // Have the current state handle the key press.
    std::shared_ptr<STATES::IGameState>& currentState = m_gameStates.top();
    currentState->HandleKeyPress(key);
}

sf::FloatRect GalacticEggSnatchersGame::GetScreenBoundsInPixels() const
{
    sf::FloatRect screenBoundsInPixels(
        0.0f,
        0.0f,
        static_cast<float>(SCREEN_WIDTH_IN_PIXELS), 
        static_cast<float>(SCREEN_HEIGHT_IN_PIXELS));

    return screenBoundsInPixels;
}

void GalacticEggSnatchersGame::InitializeFirstGameState()
{
    sf::FloatRect screenBoundsInPixels = GetScreenBoundsInPixels();
    std::shared_ptr<STATES::IGameState> initialState = std::make_shared<STATES::TitleState>(
        GAME_TITLE,
        screenBoundsInPixels);
    m_gameStates.push(initialState);
}

void GalacticEggSnatchersGame::SwitchToNextGameState(const STATES::GameStateType nextStateType)
{
    // REMOVE THE CURRENT STATE.
    /// @todo   The state is only currently removed to conserve memory.  Once a system is properly
    ///         implemented to go "back" to previous states, we can properly use the stack.
    ///         The old state is initially saved so that we can still "use" it if an invalid
    ///         type of next state was selected.
    std::shared_ptr<STATES::IGameState> nextGameState = m_gameStates.top();
    m_gameStates.pop();

    // GET THE SCREEN BOUNDS NEEDED FOR ALL POSSIBLE STATES.
    sf::FloatRect screenBoundsInPixels = GetScreenBoundsInPixels();

    // SWITCH TO THE NEXT SPECIFIED STATE.
    switch (nextStateType)
    {
    case STATES::GAME_STATE_TYPE_TITLE:
        nextGameState = std::make_shared<STATES::TitleState>(
            GAME_TITLE,
            screenBoundsInPixels);
        break;
    case STATES::GAME_STATE_TYPE_CREDITS:
        nextGameState = std::make_shared<STATES::CreditsState>(
            screenBoundsInPixels);
        break;
    case STATES::GAME_STATE_TYPE_GAMEPLAY:
        nextGameState = std::make_shared<STATES::GameplayState>(
            screenBoundsInPixels);
        break;
    }

    m_gameStates.push(nextGameState);
}