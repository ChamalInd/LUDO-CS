#include "functions.h"

Player players[NO_OF_PLAYERS];
Cell board[NO_OF_CELLS];
GameStatus game_status;

int main(void) 
{   
    srand(1);
    game_loop();

    return 0;
}