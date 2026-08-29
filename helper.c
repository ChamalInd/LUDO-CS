// Declare all the helper functions
#include "functions.h"

extern Player players[NO_OF_PLAYERS];
extern Cell board[NO_OF_CELLS];
extern GameStatus game_status;

int dice_roll(void)
{
    return rand() % 6 + 1;
}

void initialize_game(void)
{
    game_status = (GameStatus)
    {
        .starting_player = NONE,
        .current_player = NONE,
        .round_count = 0
    };

    initialize_players();
    initialize_board();
    print_start();
	decide_player_order();
}

void initialize_board(void)
{
    for (int i = 0; i < NO_OF_CELLS; i++) 
    {
        for (int j = 0; j < NO_OF_PIECES * NO_OF_PLAYERS; j++)
        {
            board[i].pieces[j] = (Piece) {};
        }
    }

    int prev = 0;
    for (int i = 0 ; i < NO_OF_CELLS - 24; i++)
    {
        if (i % 13 == 0)
        {
            board[i].cell_type = X_MARK;
            prev = i;
        }
        else if ((i - prev) % 11 == 0) board[i].cell_type = COLORED_CIRCLE;
        else board[i].cell_type = STANDARD;
        board[i].id = i;
        snprintf(board[i].name, sizeof(board[i].name), "%i", i);
    }

    // Color specific cells;
    for (int i = NO_OF_CELLS - 24; i < NO_OF_CELLS - 18; i++) 
    {
        board[i].cell_type = COLOR_SPECIFIC_GREEN;
        board[i].id = i;
        if (i == NO_OF_CELLS - 19) strcpy(board[i].name, "GreenHome");
        else snprintf(board[i].name, sizeof(board[i].name), "GreenHomePath%i", i % (NO_OF_CELLS - 24));

    }
    for (int i = NO_OF_CELLS - 18; i < NO_OF_CELLS - 12; i++) 
    {
        board[i].cell_type = COLOR_SPECIFIC_YELLOW;
        board[i].id = i;
        if (i == NO_OF_CELLS - 13) strcpy(board[i].name, "YellowHome");
        else snprintf(board[i].name, sizeof(board[i].name), "YellowHomePath%i", i % (NO_OF_CELLS - 18));
    }
    for (int i = NO_OF_CELLS - 12; i < NO_OF_CELLS - 6; i++) 
    {
        board[i].cell_type = COLOR_SPECIFIC_BLUE;
        board[i].id = i;
        if (i == NO_OF_CELLS - 7) strcpy(board[i].name, "BlueHome");
        else snprintf(board[i].name, sizeof(board[i].name), "BlueHomePath%i", i % (NO_OF_CELLS - 12));
    }
    for (int i = NO_OF_CELLS - 6; i < NO_OF_CELLS; i++) 
    {
        board[i].cell_type = COLOR_SPECIFIC_RED;
        board[i].id = i;
        if (i == NO_OF_CELLS - 1) strcpy(board[i].name, "RedHome");
        else snprintf(board[i].name, sizeof(board[i].name), "RedHomePath%i", i % (NO_OF_CELLS - 6));
    }
}

void initialize_players(void)
{
    char *player_names[] = {"Red", "Green", "Yellow", "Blue"};
    char *piece_names[] = {"R", "G", "Y", "B"};
    int x_marked_cells[] = {39, 0, 13, 26};
    int colored_circle_cells[] = {37, 50, 11, 24};
    int home_path_cells[] = {70, 52, 58, 64};

    for (int i = 0; i < NO_OF_PLAYERS; i++) 
    {
        players[i] = (Player) 
        {
            .name = player_names[i],
            .player_status = OUT_OF_GAME,
            .die_roll = 0,
            .six_counts = 0,
            .x_marked_cell = x_marked_cells[i],
            .colored_circle = colored_circle_cells[i],
            .home_path_begin_cell = home_path_cells[i]
        };

        char *piece_specifier = piece_names[i];

        for (int j = 0; j < NO_OF_PIECES; j++) 
        {
            snprintf(players[i].pieces[j].name, sizeof(players[i].pieces[j].name), "%s%i", piece_specifier, j + 1);
            players[i].pieces[j].place = BASE;
            players[i].pieces[j].piece_status = IN_BASE;
        }
    }
}

void decide_player_order(void)
{   
    while (TRUE) 
    {
        int max = 0, place = 0, count = 0;
    
        for (int i = 0; i < NO_OF_PLAYERS; i++)
        {
            if (players[i].player_status == OUT_OF_GAME)
            {
                players[i].die_roll = dice_roll();
            }
        }

        for (int i = 0; i < NO_OF_PLAYERS; i++) 
        {
            if (players[i].player_status == OUT_OF_GAME && max < players[i].die_roll)
            {
                max = players[i].die_roll;
                place = i;
            }
        }

        for (int i = 0; i < NO_OF_PLAYERS; i++) 
        {
            if (players[place].die_roll == players[i].die_roll)
            {
                count++;
            }
        }

        if (count > 1)
        {
            return decide_player_order();
        }
        game_status.current_player = place;
        game_status.starting_player = place;


        for (int i = 0; i < NO_OF_PLAYERS; i++)
        {
            printf("%s rolls %i.\n", players[i].name, players[i].die_roll);
            players[i].player_status = PLAYING;
        }

        printf("\n%s player has the highest roll and will begin the game.\n\nThe order of a single round is ", players[place].name);

        count = 0;
        while (count < NO_OF_PLAYERS)
        {
            printf("%s", players[(place + count) % NO_OF_PLAYERS].name);
            if (count == (NO_OF_PLAYERS - 2)) printf(", and ");
            else if (count == (NO_OF_PLAYERS - 1)) printf(".\n\n");
            else printf(", ");
            count++;
        }
        break;
    }
}

Player_Status calculate_player_status(Player player)
{
    Player_Status status;
    status.based_pieces = status.homed_pieces = status.playing_pieces = 0;

    for (int i = 0; i < NO_OF_PIECES; i++)
    {
        if (player.pieces[i].piece_status == IN_BASE) status.based_pieces++;
        if (player.pieces[i].piece_status == IN_HOME) status.homed_pieces++;
    }
    
    status.playing_pieces = NO_OF_PIECES - status.based_pieces - status.homed_pieces;

    return status;
}

int decide_winner(void)
{
    int winner = NONE;

    for (int i = 0; i < NO_OF_PLAYERS; i++)
    {
        Player_Status status = calculate_player_status(players[i]);
        if (status.homed_pieces == NO_OF_PIECES) 
        {
            winner = i; 
            break;
        }
    }

    return winner;
}

void print_start(void)
{
    printf("----------------------------------------------------------- LUDO CS -----------------------------------------------------------\n\n");

    for (int i = 0; i < NO_OF_PLAYERS; i++)
    {
        printf("The %s player has four (0%i) pieces named ", players[i].name, NO_OF_PIECES);
        for (int j = 0; j < NO_OF_PIECES; j++)
        {
            printf("%s", players[i].pieces[j].name);
            if (j == (NO_OF_PIECES - 1)) printf(".\n");
            else if (j == (NO_OF_PIECES - 2)) printf(", and ");
            else printf(", ");
        }
    }
    printf("\n");
}

void print_game_round(void)
{
    
    printf("----------------------------------------------------------- Round %2i -----------------------------------------------------------\n\n", game_status.round_count);
    for (int i = 0; i < NO_OF_PLAYERS; i++)
    {
        Player_Status status = calculate_player_status(players[i]);
        printf("%s player now has %i/%i pieces on the board and %i/%i pieces on the base.\n", players[i].name, (NO_OF_PIECES - status.based_pieces), NO_OF_PIECES, status.based_pieces, NO_OF_PIECES);
        printf("Locations of Pieces of %s player : \n", players[i].name);
        for (int j = 0; j < NO_OF_PIECES; j++)
        {
            char *place;

            if (players[i].pieces[j].place == HOME) place = "Home";
            else if (players[i].pieces[j].place == BASE) place = "Base";
            else place = board[players[i].pieces[j].place].name;

            printf("\t%s : %s\n", players[i].pieces[j].name, place);
            
        }
        printf("\n");
    }
}