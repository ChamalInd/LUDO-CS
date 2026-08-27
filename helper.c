// Declare all the helper functions
#include "functions.h"

extern Player players[NO_OF_PLAYERS];
extern GameStatus game_status;

int dice_roll()
{
    return rand() % 6 + 1;
}

void initialize_board()
{
    game_status = (GameStatus)
    {
        .current_player = 0
    };

    initialize_players();
    print_start();
	decide_player_order();
}

void initialize_players()
{
    char *player_names[NO_OF_PLAYERS] = {"Red", "Green", "Yellow", "Blue"};
    char *piece_names[NO_OF_PLAYERS] = {"R", "G", "Y", "B"};

    for (int i = 0; i < NO_OF_PLAYERS; i++) 
    {
        players[i] = (Player) 
        {
            .name = player_names[i],
            .player_status = OUT_OF_GAME,
            .die_roll = 0
        };

        char *piece_specifier = piece_names[i];

        for (int j = 0; j < NO_OF_PLAYERS; j++) 
        {
            snprintf(players[i].pieces[j].name, sizeof(players[i].pieces[j].name), "%s%i", piece_specifier, j + 1);
            players[i].pieces[j].place = 0;
            players[i].pieces[j].piece_status = OUT_OF_GAME;
        }
    }
}

void decide_player_order()
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

void print_start()
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