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

// Data structures of players
typedef enum 
{
    OUT_OF_GAME, IN_GAME, PLAYING
} Status;

typedef struct 
{
    char name[3];
    int place;
    Status piece_status;
} Piece;

typedef struct 
{
    char *name;
    Status player_status;
    int die_roll;
    Piece pieces[4];
} Player;

// Data structures of board
typedef struct 
{
    int current_player;
} GameStatus;

#endif