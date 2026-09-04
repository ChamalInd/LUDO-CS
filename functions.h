// Declare prototypes of all the functions used in files.
#include "types.h"

// helper.c
int dice_roll(void);
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
void move_from_base_to_board(Player *player, Piece *piece, Player_Status status);
void move_inside_board(Player *player, Piece *piece);
void move_in_home_path(Player *player, Piece *piece);
void capture_players(Piece current_piece);