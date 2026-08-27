// Define player behaviors
#include "functions.h"

extern Player players[NO_OF_PLAYERS];
extern GameStatus game_status;

void decide_player_actions(void)
{   
    int player = game_status.current_player;
    int based_pieces = count_based_pieces(players[player]);

    if (based_pieces > 0 && players[player].die_roll == 6) // base to starting point X
    {
        printf("%s player moves piece %s to the starting point.\n", players[player].name, players[player].pieces[NO_OF_PIECES - based_pieces].name);
        players[player].pieces[NO_OF_PIECES - based_pieces].piece_status = PLAYING;
        based_pieces--;
        printf("%s player now has %i/4 pieces on board and %i/4 pieces on base.\n\n", players[player].name, (NO_OF_PIECES - based_pieces), based_pieces);
    }
}