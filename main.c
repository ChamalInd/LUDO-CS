#include "functions.h"

Player players[NO_OF_PLAYERS];
GameStatus game_status;

int main() 
{   
    srand(1);
    game_loop();

    return 0;
}