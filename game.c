// Declare game loop
#include "functions.h"

void game_loop(void) 
{
    initialize_game();
    while (TRUE)
    {
        int winner = decide_winner();
        int player = game_status.current_player;

        if (winner != NONE) {
            printf("%s player wins!!!\n", players[winner].name);
            break;
        }

        if (game_status.current_player == game_status.starting_player && players[player].six_counts == 0)
        {
            game_status.round_count++;
            print_game_round();
        }

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
    }
}