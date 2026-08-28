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
        .current_player = 0
    };

    initialize_players();
    initialize_board();
    print_start();
	decide_player_order();
}

void initialize_board(void)
{
    int prev = 0;
    for (int i = 0 ; i < NO_OF_CELLS - 20; i++)
    {
        if (i % 13 == 0)
        {
            board[i].cell_type = X_MARK;
            prev = i;
        }
        else if ((i - prev) % 11 == 0) board[i].cell_type = COLORED_CIRCLE;
        else board[i].cell_type = STANDARD;
    }

    // Color specific cells;
    for (int i = NO_OF_CELLS - 20; i < NO_OF_CELLS - 15; i++) board[i].cell_type = COLOR_SPECIFIC_RED;
    for (int i = NO_OF_CELLS - 15; i < NO_OF_CELLS - 10; i++) board[i].cell_type = COLOR_SPECIFIC_YELLOW;
    for (int i = NO_OF_CELLS - 10; i < NO_OF_CELLS - 5; i++) board[i].cell_type = COLOR_SPECIFIC_GREEN;
    for (int i = NO_OF_CELLS - 5; i < NO_OF_CELLS; i++) board[i].cell_type = COLOR_SPECIFIC_BLUE;
}

void initialize_players(void)
{
    char *player_names[NO_OF_PLAYERS] = {"Red", "Green", "Yellow", "Blue"};
    char *piece_names[NO_OF_PLAYERS] = {"R", "G", "Y", "B"};
    int x_marked_cells[NO_OF_PLAYERS] = {0, 13, 26, 39};
    int colored_circle_cells[NO_OF_PLAYERS] = {11, 24, 37, 50};

    for (int i = 0; i < NO_OF_PLAYERS; i++) 
    {
        players[i] = (Player) 
        {
            .name = player_names[i],
            .player_status = OUT_OF_GAME,
            .die_roll = 0,
            .x_marked_cell = x_marked_cells[i],
            .colored_circle = colored_circle_cells[i]
        };

        char *piece_specifier = piece_names[i];

        for (int j = 0; j < NO_OF_PLAYERS; j++) 
        {
            snprintf(players[i].pieces[j].name, sizeof(players[i].pieces[j].name), "%s%i", piece_specifier, j + 1);
            players[i].pieces[j].place = BASE;
            players[i].pieces[j].piece_status = OUT_OF_GAME;
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

        for (int i = 0; i < NO_OF_PLAYERS; i++)
        {
            printf("%s rolls %i.\n", players[i].name, players[i].die_roll);
            players[i].player_status = IN_GAME;
        }

        printf("\n%s player has the highest roll and will begin the game.\n\nThe order of a single round is ", players[place].name);

        count = 0;
        while (count < 4)
        {
            printf("%s", players[(place + count) % NO_OF_PLAYERS].name);
            if (count == (NO_OF_PLAYERS - 2)) printf(", and ");
            else if (count == (NO_OF_PLAYERS - 1)) printf("\n");
            else printf(", ");
            count++;
        }
        break;
    }
}

void print_start(void)
{
    printf("-------------------------- LUDO CS --------------------------\n\n");

    for (int i = 0; i < NO_OF_PLAYERS; i++)
    {
        printf("The %s player has four (0%i) pieces named ", players[i].name, NO_OF_PIECES);
        for (int j = 0; j < NO_OF_PIECES; j++)
        {
            printf("%s", players[i].pieces[j].name);
            if (j == (NO_OF_PIECES - 1)) printf("\n");
            else if (j == (NO_OF_PIECES - 2)) printf(", and");
            else printf(", ");
        }
    }
    printf("\n");
}

int count_based_pieces(Player player)
{
    int count = 0;
    for (int i = 0; i < NO_OF_PIECES; i++)
    {
        if (player.pieces[i].piece_status == OUT_OF_GAME) count++;
    }
    return count;
}