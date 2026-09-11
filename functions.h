// Declare prototypes of all the functions used in files.
#include "types.h"

// helper.c
int dice_roll(void);
int coin_toss(void);
void initialize_game(void);
void initialize_board(void);
void initialize_players(void);
void decide_player_order(void);
Player_Status calculate_player_status(Player player);
void decide_winner(void);
void print_start(void);
void print_game_round(void);
void print_game_over(void);
void print_movements(int situation, Player player, Piece piece, int playing_count, int based_count, int total_pieces, int next_location);

// game.c
void game_loop(void);

// players.c
void decide_player_movement(void);
void decide_player_direction(Piece *piece);
void move_from_base_to_board(Player *player, Piece pieces[], Player_Status status);
void move_inside_board(Player *player, Piece pieces[], Player_Status status);
void capture_players(Piece current_piece);