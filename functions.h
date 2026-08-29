// Declare prototypes of all the functions used in files.
#include "types.h"

// helper.c
int dice_roll(void);
void initialize_game(void);
void initialize_board(void);
void initialize_players(void);
void decide_player_order(void);
Player_Status calculate_player_status(Player player);
int decide_winner(void);
void print_start(void);
void print_game_over(int winner);

// game.c
void game_loop(void);

// players.c
void decide_player_actions(void);