#include <cstdlib>
#include <exception>
#include <iostream>
#if defined _WINDOWS
#include <Windows.h>
#endif
#include <SFML/Graphics.hpp>
#include "GalacticEggSnatchersGame.h"

#if defined _CONSOLE
/// @brief      The main entry point function for the game.
/// @param[in]  argumentCount - The number of command line arguments.
/// @param[in]  arguments - The command line arguments.
/// @return     EXIT_SUCCESS if the game ends successfully.
///             EXIT_FAILURE if an error occurs.
int main(int argumentCount, char* arguments[])
#elif defined _WINDOWS
/// @brief      The main entry point function for the game for release Windows builds.
///             This supports releasing the game without an additional console window.
/// @param[in]  hInstance - Handle to the current application instance.
/// @param[in]  hPrevInstance - Handle to previous application instance; always NULL.
/// @param[in]  lpCmdLine - Command line for the application, exluding the program name.
/// @param[in]  nCmdShow - How the window should be shown.  Ignored.
/// @return     EXIT_SUCCESS if the game ends successfully.
///             EXIT_FAILURE if an error occurs.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
    try
    {
        // CREATE THE GAME.
        GalacticEggSnatchersGame game;

        // CREATE THE WINDOW.
        sf::RenderWindow window(
            sf::VideoMode(GalacticEggSnatchersGame::SCREEN_WIDTH_IN_PIXELS, GalacticEggSnatchersGame::SCREEN_HEIGHT_IN_PIXELS), 
            GalacticEggSnatchersGame::GAME_TITLE);

        // PROCESS EVENTS AS LONG AS THE WINDOW REMAINS OPEN.
        sf::Clock gameLoopClock;
        while (window.isOpen())
        {
            // PROCESS WINDOW EVENTS.
            sf::Event event;
            while (window.pollEvent(event))
            {
                // Handle the current event based on its type.
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    game.HandleKeyPress(event.key.code);
                    break;
                }
            }

            // UPDATE AND DISPLAY THE GAME IN THE WINDOW.
            if (window.isOpen())
            {
                // Update the game for the new frame.
                sf::Time elapsedTime = gameLoopClock.restart();
                game.Update(elapsedTime);
            
                // Render the current state of the game.
                window.clear();
                game.Render(window);
                window.display();
            }
        }

        return EXIT_SUCCESS;
    }
    catch (std::exception& exception)
    {
        std::cerr << "Exception during game: " << exception.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Unknown error during game." << std::endl;
        return EXIT_FAILURE;
    }
}