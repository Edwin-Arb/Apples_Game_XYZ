#include "Game.h"

using namespace Apples_Game;

int main()
{    
    // Init Window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game!");

    // Game Initialization
    SGame game;
    Init_Game(game);

    // Slow down the game 
    sf::Clock game_Clock;
    float last_Time = game_Clock.getElapsedTime().asSeconds();

    // Main loop
    while (window.isOpen())
    {
        sleep(sf::milliseconds(16));

        // Calculate time delta
        float current_Time = game_Clock.getElapsedTime().asSeconds();
        float delta_Time = current_Time - last_Time;
        last_Time = current_Time;

        // Read events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
            
            Handle_Keys_Main_Menu(event, window, game);
        }

        Update_Game_State(game, delta_Time);

        // Draw everything
        window.clear();

        Draw_Game(game, window);

        window.display();
    }

    // Deinitialization
    Deinitialize_Game(game);

    return 0;
}