// Declares data structures used in the program
#ifndef TYPES_H
#define TYPES_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE          1
#define FALSE         0
#define NO_OF_PLAYERS 4
#define NO_OF_PIECES  4
#define NO_OF_CELLS  72

// Data structures of pieces
typedef enum 
{
    OUT_OF_GAME, IN_GAME, PLAYING
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
    char *name;
    Status player_status;
    int die_roll;
    int x_marked_cell;
    int colored_circle;
    Piece pieces[4];
} Player;

// Data structures of game
typedef struct 
{
    int current_player;
} GameStatus;

// Data structures of board
typedef enum
{
    STANDARD, X_MARK, COLORED_CIRCLE, COLOR_SPECIFIC_RED, COLOR_SPECIFIC_YELLOW, COLOR_SPECIFIC_GREEN, COLOR_SPECIFIC_BLUE
} Type;

typedef struct 
{
    int id;
    Piece pieces[16];
    Type cell_type;
} Cell;

#endif