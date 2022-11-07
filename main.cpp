#include "headers/game.h"

int main(int argc, char **argv){
    Game game;

    while(game.isRunning()){
        game.update();
        game.render();
    }
    return 0;
}

