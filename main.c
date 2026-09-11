#include "functions.h"

Player players[NO_OF_PLAYERS];
Cell board[NO_OF_CELLS];
GameStatus game_status;

int main(void) 
{   
    int key = 1; //time(NULL);
    printf("Key : %i\n", key);
    srand(key);
    game_loop();

    return 0;
}