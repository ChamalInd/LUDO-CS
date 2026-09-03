// Define player behaviors
#include "functions.h"

void decide_player_movement(void)
{   
    Player *player = &players[game_status.current_player];
    Piece *pieces = player->pieces;
    Player_Status status = calculate_player_status(*player);

    if (status.based_pieces > 0 && player->die_roll == 6) // base to starting point X
    {
        int piece = 0;
        while (TRUE)
        {
            if (pieces[piece].piece_status == IN_BASE) break;
            piece++;
        }
        
        move_from_base_to_board(player, &pieces[piece], status);
        capture_players(pieces[piece]);
    }
    else if (status.playing_pieces > 0) // moving other pieces
    {
        int tries = 0, piece;

        while (TRUE)
        {
            while (TRUE)
            {
                piece = rand() % NO_OF_PIECES;
                if (pieces[piece].piece_status == PLAYING || pieces[piece].piece_status == IN_HOME_PATH) break;
            }

            if (pieces[piece].piece_status == PLAYING)
            {
                move_inside_board(player, &pieces[piece]);
                capture_players(pieces[piece]);
                break;
            }
            else if (pieces[piece].piece_status == IN_HOME_PATH)
            {
                if (player->die_roll <= ((player->home_path_begin_cell + 5) - pieces[piece].place))
                {
                    move_in_home_path(player, &pieces[piece]);
                    break;
                }
            }

            if (tries >= status.playing_pieces) 
            {
                printf("%s has no place to move.\n\n", player->name);
                break;
            }

            tries++;
        }
    }
    else printf("%s has no place to move.\n\n", player->name);
}

void move_from_base_to_board(Player *player, Piece *piece, Player_Status status)
{
    piece->piece_status = PLAYING;
    piece->place = player->x_marked_cell;
    status.based_pieces--;
    print_movements(1, *player, *piece, NO_OF_PIECES - status.based_pieces, status.based_pieces, NO_OF_PIECES, NONE);
}

void move_inside_board(Player *player, Piece *piece)
{   
    int next_location = 0;
    int i = piece->place;

    while (TRUE)
    {
        if (board[i].id == player->colored_circle)
        {
            next_location = player->home_path_begin_cell + piece->place + player->die_roll - i - 1;
            print_movements(2, *player, *piece, NONE, NONE, NONE, next_location);
            piece->place = next_location;
            piece->piece_status = IN_HOME_PATH;
            break;
        }
        i = (i + 1) % (NO_OF_CELLS - 24);
        if (i == ((piece->place + player->die_roll) % (NO_OF_CELLS - 24))) break;
    }
    if (piece->piece_status == PLAYING) 
    {
        next_location = (piece->place + player->die_roll) % (NO_OF_CELLS - 24);
        print_movements(2, *player, *piece, NONE, NONE, NONE, next_location);
        piece->place = next_location;
    }
}

void move_in_home_path(Player *player, Piece *piece)
{
    int next_location = piece->place + player->die_roll;
    print_movements(2, *player, *piece, NONE, NONE, NONE, next_location);
    piece->place = next_location;

    if (piece->place == player->home_path_begin_cell + 5)
    {
        piece->piece_status = IN_HOME;
        piece->place = HOME;
    }
}

void capture_players(Piece current_piece)
{
    for (int i = 0; i < NO_OF_PLAYERS; i++)
    {
        if (game_status.current_player == i) continue;
        for (int j = 0; j < NO_OF_PIECES; j++)
        {
            if (players[i].pieces[j].piece_status == PLAYING && players[i].pieces[j].place == current_piece.place)
            {
                players[i].pieces[j].place = BASE;
                players[i].pieces[j].piece_status = IN_BASE;
                printf("%s player's piece %s, captured %s.\n", players[game_status.current_player].name, current_piece.name, players[i].pieces[j].name);
                printf("Piece %s returned to Base.\n\n", players[i].pieces[j].name);
            }
        }
    }
}