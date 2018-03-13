#include <iostream>
#include "Game.h"

int main(int, char**) {

    Game game;

    while (!game.IsOver()) {
        game.Update();
        game.Render();
        game.Synchronize();
    }

    std::cout << "Finishing..." << std::endl;

    return 0;
}
