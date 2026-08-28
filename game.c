// Declare game loop
#include "functions.h"

extern Player players[NO_OF_PLAYERS];
extern GameStatus game_status;

void game_loop(void) 
{
    initialize_game();
    int count = 0;
    while (count < 100)
    {
        int player = game_status.current_player;
        players[player].die_roll = dice_roll();
        printf("%s player rolled %i.\n", players[player].name, players[player].die_roll);

        decide_player_actions();

        game_status.current_player = (player + 1) % NO_OF_PLAYERS;
        count++;
    }
}