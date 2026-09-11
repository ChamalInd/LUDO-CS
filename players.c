// Define player behaviors
#include "functions.h"

void decide_player_movement(void)
{   
    Player *player = &players[game_status.current_player];
    Piece *pieces = player->pieces;
    Player_Status status = calculate_player_status(*player);

    if (status.based_pieces > 0 && player->die_roll == 6) // base to starting point X
    {
        move_from_base_to_board(player, pieces, status);
    }
    else if (status.playing_pieces > 0) // moving other pieces
    {
        move_inside_board(player, pieces, status);
    }
    else printf("%s has no place to move.\n\n", player->name);
}

void decide_player_direction(Piece *piece)
{
    int toss = coin_toss();
    char *dir, *toss_name;
    if (toss == HEAD)
    {
        piece->direction = CLOCKWISE;
        dir = "Clockwise";
        toss_name = "Head";
    }
    else
    {
        piece->direction = ANTI_CLOCKWISE;
        dir = "Counter Clockwise";
        toss_name = "Tail";
    }
    printf("%s tossed a coin and got %s.\n%s will move in %s direction.\n\n", piece->name, toss_name, piece->name, dir);
}

void move_from_base_to_board(Player *player, Piece pieces[], Player_Status status)
{
    int piece = 0;
    while (TRUE)
    {
        if (pieces[piece].piece_status == IN_BASE) break;
        piece++;
    }

    pieces[piece].piece_status = PLAYING;
    pieces[piece].place = player->x_marked_cell;
    status.based_pieces--;
    print_movements(1, *player, pieces[piece], NO_OF_PIECES - status.based_pieces, status.based_pieces, NO_OF_PIECES, NONE);
    decide_player_direction(&pieces[piece]);
    capture_players(pieces[piece]);
}

void move_inside_board(Player *player, Piece pieces[], Player_Status status)
{   
    int tries = 0, next_location = 0, piece;

    while (TRUE)
    {
        while (TRUE)
        {
            piece = rand() % NO_OF_PIECES;
            if (pieces[piece].piece_status == PLAYING || pieces[piece].piece_status == IN_HOME_PATH)
            {
                int safe = TRUE;

                for (int i = 0; i < NO_OF_PIECES; i++)
                {
                    if (i == piece) continue;
                    if (pieces[i].place == ((pieces[piece].place + player->die_roll) % (NO_OF_CELLS - 24)))
                    {
                        safe = FALSE;
                        break;
                    }
                }

                if (safe) break;
            }
        }

        if (pieces[piece].piece_status == PLAYING)
        {
            int i = pieces[piece].place;
            while (TRUE)
            {
                if (board[i].id == player->colored_circle)
                {
                    next_location = player->home_path_begin_cell + pieces[piece].place + player->die_roll - i - 1;
                    print_movements(2, *player, pieces[piece], NONE, NONE, NONE, next_location);
                    pieces[piece].place = next_location;
                    pieces[piece].piece_status = IN_HOME_PATH;

                    if (pieces[piece].place == player->home_path_begin_cell + 5)
                    {
                        pieces[piece].piece_status = IN_HOME;
                    }
                    
                    break;
                }
                i = (i + 1) % (NO_OF_CELLS - 24);
                if (i == ((pieces[piece].place + player->die_roll) % (NO_OF_CELLS - 24))) break;
            }
            if (pieces[piece].piece_status == PLAYING) 
            {
                if (pieces[piece].direction == CLOCKWISE)
                {
                    next_location = (pieces[piece].place + player->die_roll) % (NO_OF_CELLS - 24);
                }
                else
                {
                    next_location = (pieces[piece].place - player->die_roll) % (NO_OF_CELLS - 24);
                }
                print_movements(2, *player, pieces[piece], NONE, NONE, NONE, next_location);
                pieces[piece].place = next_location;
            }
            
            capture_players(pieces[piece]);
            break;
        }
        else if (pieces[piece].piece_status == IN_HOME_PATH)
        {
            if (player->die_roll <= ((player->home_path_begin_cell + 5) - pieces[piece].place))
            {
                next_location = pieces[piece].place + player->die_roll;
                print_movements(2, *player, pieces[piece], NONE, NONE, NONE, next_location);
                pieces[piece].place = next_location;

                if (pieces[piece].place == player->home_path_begin_cell + 5)
                {
                    pieces[piece].piece_status = IN_HOME;
                }
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