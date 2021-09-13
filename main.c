#include <stdio.h>

#include "input_output.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>




/*
 * BOARD_SIZE is 9 so the board can be label from 1 to 8 instead of 0 to 7
 */



//Checks if every stack on the board belongs to only one player.
bool check(square board[BOARD_SIZE][BOARD_SIZE]);

int main(void) {
    srand(time(0));


    // declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];

    initialize_players(players);

    initialize_board(board, players);

    print_board(board, players);


    //Who goes first is random
    //Red is 0 and Green is 1
    int starting_colour = rand() % 2;


    //Checks if every stack on the board belongs to only one player, if not continue on playing
    while (check(board)) {

        //Outputting to user who's turn it is
        if (starting_colour == RED) {
            printf("\nIt is Red's Move\n");
        } else
            printf("\nIt is Green's Move\n");

        //calling the turn function which starts everything and printing out the board straight after
        turn(board, starting_colour, players);
        print_board(board, players);

        //Change colour to other persons colour
        starting_colour = (starting_colour + 1) % 2;
    }

    //When Code reaches here, the game is over because someone has won

    //Goes through the board until the first piece and sees who's colour it is and announces the winner of the colour detected
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {


            if (board[i][j].num_pieces > 0) {

                if (players[0].player_colour == board[i][j].stack->p_colour) {
                    printf("\n\n***************\n");
                    printf("Player %s Wins!", players[0].name);
                    printf("\n***************\n");
                    exit(0);

                } else {
                    printf("\n\n***************\n");
                    printf("Player %s Wins!", players[1].name);
                    printf("\n***************\n");
                    exit(0);
                }
            }
        }
    }

    return 0;
}


//Goes through the board to the first piece and records its colour
//Then it finds the next piece that has a different colour.  If it can't find a piece with a different colour it returns false and the game is declared to be over
bool check(square board[BOARD_SIZE][BOARD_SIZE]){
    int i, j;
    int colour = -1;

    for (i = 1;i<BOARD_SIZE; i++){
        for (j = 1;j<BOARD_SIZE;j++){

            if (board[i][j].num_pieces > 0 && colour == -1){
                colour = board[i][j].stack->p_colour;
            }

            if (colour != -1 && board[i][j].num_pieces > 0){
                if (colour != board[i][j].stack->p_colour) {
                    return true;
                }
            }
        }
    }

    return false;
}