// Declare game loop
#include "functions.h"

void game_loop(void) 
{
    initialize_game();
    while (TRUE)
    {
        int player = game_status.current_player;
        decide_winner();

        if (game_status.no_of_winners == NO_OF_PLAYERS) {
            print_game_over();
            break;
        }

        if (players[player].player_status == FINISHED) 
        {
            game_status.current_player = (player + 1) % NO_OF_PLAYERS;
            game_status.turn_count++;
            continue;
        }        

        if (players[player].six_counts == 0)
        {
            game_status.turn_count++;
            if (game_status.round_count == 0 || game_status.turn_count >= NO_OF_PLAYERS)
            {
                game_status.round_count++;
                game_status.turn_count = 0;
                print_game_round();
            }
        }

        players[player].die_roll = dice_roll();
        print_movements(0, players[player], players[player].pieces[0], NONE, NONE, NONE, NONE);

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