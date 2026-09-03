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
        printf("%s player moves piece %s to the starting point.\n", player->name, pieces[piece].name);
        pieces[piece].piece_status = PLAYING;
        pieces[piece].place = player->x_marked_cell;
        status.based_pieces--;
        printf("%s player now has %i/%i pieces on board and %i/%i pieces on base.\n\n", player->name, NO_OF_PIECES - status.based_pieces, NO_OF_PIECES, status.based_pieces, NO_OF_PIECES);
        capture_players(pieces[piece]);
    }
    else if (status.playing_pieces > 0) // moving other pieces
    {
        int next_location = 0, tries = 0, piece;

        while (TRUE)
        {
            while (TRUE)
            {
                piece = rand() % NO_OF_PIECES;
                if (pieces[piece].piece_status == PLAYING || pieces[piece].piece_status == IN_HOME_PATH) break;
            }

            if (pieces[piece].piece_status == PLAYING)
            {
                int i = pieces[piece].place;
                while (TRUE)
                {
                    if (board[i].id == player->colored_circle)
                    {
                        next_location = player->home_path_begin_cell + pieces[piece].place + player->die_roll - i - 1;
                        printf("%s moves piece %s from %s to %s by %i units in clockwise direction.\n\n", player->name, pieces[piece].name, board[pieces[piece].place].name, board[next_location].name, player->die_roll);
                        pieces[piece].place = next_location;
                        pieces[piece].piece_status = IN_HOME_PATH;
                        break;
                    }
                    i = (i + 1) % (NO_OF_CELLS - 24);
                    if (i == ((pieces[piece].place + player->die_roll) % (NO_OF_CELLS - 24))) break;
                }
                if (pieces[piece].piece_status == PLAYING) 
                {
                    next_location = (player->pieces[piece].place + player->die_roll) % (NO_OF_CELLS - 24);
                    printf("%s moves piece %s from %s to %s by %i units in clockwise direction.\n\n", player->name, pieces[piece].name, board[pieces[piece].place].name, board[next_location].name, player->die_roll);
                    pieces[piece].place = next_location;
                }
                capture_players(pieces[piece]);
                break;
            }
            else if (pieces[piece].piece_status == IN_HOME_PATH)
            {
                if (player->die_roll <= ((player->home_path_begin_cell + 5) - pieces[piece].place))
                {
                    next_location = player->pieces[piece].place + player->die_roll;
                    printf("%s moves piece %s from %s to %s by %i units in clockwise direction.\n\n", player->name, pieces[piece].name, board[pieces[piece].place].name, board[next_location].name, player->die_roll);
                    strcpy(board[pieces[piece].place].piece_name, "");
                    pieces[piece].place = next_location;
                    strcpy(board[pieces[piece].place].piece_name, pieces[piece].name);

                    if (pieces[piece].place == player->home_path_begin_cell + 5)
                    {
                        pieces[piece].piece_status = IN_HOME;
                        pieces[piece].place = HOME;
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
    else printf("%s has no place to move.\n\n", player->name);
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