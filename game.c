// Declare game loop
#include "functions.h"

extern Player players[NO_OF_PLAYERS];
extern GameStatus game_status;

void game_loop(void) 
{
    initialize_game();
    int count = 0;
    while (count < 1000)
    {
        int winner = decide_winner();

        if (winner != NONE) {
            print_game_over(winner);
            break;
        }

        int player = game_status.current_player;
        players[player].die_roll = dice_roll();
        printf("%s player rolled %i.\n", players[player].name, players[player].die_roll);

        decide_player_movement();

        if (players[player].die_roll == 6 && players[player].six_counts < 2)
        {
            game_status.current_player = player;
            players[player].six_counts++;
        }
        else
        {
            game_status.current_player = (player + 1) % NO_OF_PLAYERS;
            players[player].six_counts = 0;
        }

        count++;
    }
}