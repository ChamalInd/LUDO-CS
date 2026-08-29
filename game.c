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
        int player = game_status.current_player;
        players[player].die_roll = dice_roll();
        printf("%s player rolled %i.\n", players[player].name, players[player].die_roll);

        decide_player_actions();

        game_status.current_player = (player + 1) % NO_OF_PLAYERS;
        count++;

        int game_over = TRUE;
        for (int i = 0; i < NO_OF_PLAYERS; i++)
        {
            Player_Status status = calculate_player_status(players[i]);
            if (status.homed_pieces < NO_OF_PIECES)
            {
                game_over = FALSE;
                break;
            }
        }

        if (game_over) {
            printf("Game Over\n");
            break;
        }
    }
}