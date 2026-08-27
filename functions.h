// Declare prototypes of all the functions used in files.
#include "types.h"

// helper.c
int dice_roll(void);
void initialize_board(void);
void initialize_players(void);
void decide_player_order(void);
void print_start(void);
int count_based_pieces(Player player);

// game.c
void game_loop(void);

// players.c
void decide_player_actions(void);