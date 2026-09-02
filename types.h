// Declares data structures used in the program
#ifndef TYPES_H
#define TYPES_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE          1
#define FALSE         0
#define NONE         -1
#define NO_OF_PLAYERS 4
#define NO_OF_PIECES  4
#define NO_OF_CELLS  76

extern Player players[NO_OF_PLAYERS];
extern Cell board[NO_OF_CELLS];
extern GameStatus game_status;

// Data structures of pieces
typedef enum 
{
    OUT_OF_GAME, IN_BASE, IN_HOME, PLAYING, IN_HOME_PATH
} Status;

typedef enum{
    BASE = -2, HOME
} Place;

typedef struct 
{
    char name[3];
    int place;
    Status piece_status;
} Piece;

// Data structures of players
typedef struct 
{
    int based_pieces;
    int homed_pieces;
    int playing_pieces;
} Player_Status;

typedef struct 
{
    char *name;
    Status player_status;
    int die_roll;
    int six_counts;
    int x_marked_cell;
    int colored_circle;
    int home_path_begin_cell;
    Piece pieces[NO_OF_PIECES];
} Player;

// Data structures of game
typedef struct 
{
    int starting_player;
    int current_player;
    int round_count;
} GameStatus;

// Data structures of board
typedef enum
{
    STANDARD, X_MARK, COLORED_CIRCLE, COLOR_SPECIFIC_RED, COLOR_SPECIFIC_YELLOW, COLOR_SPECIFIC_GREEN, COLOR_SPECIFIC_BLUE
} Type;

typedef struct 
{
    int id;
    char name[20];
    Piece pieces[NO_OF_PIECES * NO_OF_PLAYERS];
    Type cell_type;
} Cell;

#endif