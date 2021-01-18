#include "core/Game.hpp"

int main()
{
    // Create the game and setup the window
    Game *game = new Game(800, 600, "Test Project");
    game->run(); // Start running the game

    return 0;
}