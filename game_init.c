#include <stdio.h>
#include <stdlib.h>
#include "game_init.h"


void initialize_players(player players[PLAYERS_NUM]){
    srand((time(0)));

    //Assigns a Random Colour to the player
    int random_colour = rand() % 2;
    players[0].player_colour = random_colour;


    //Getting the name
    printf("Player 1, Enter your name: ");
    fgets(players[0].name, 20, stdin);

    //Tells the player if their red or green depending on the assigned random colour and sets their num_own and num_captured to 0
    if (players[0].player_colour == RED){
        printf("You are now Red");
        random_colour = 2;
    } else {
        printf("You are now Green");
        random_colour = 3;
    }
    players[0].num_own = 0;
    players[0].num_captured = 0;



    //Getting the name
    printf("\nPlayer 2, Enter you name: ");
    fgets(players[1].name, 20, stdin);

    //Tells the player if their red or green depending on the assigned random colour and sets their num_own and num_captured to 0
    if (random_colour == 2){
        printf("You are now Green");
    } else{
        printf("you are now Red");
    }
    players[1].num_own = 0;
    players[1].num_captured = 0;
}

//Set Invalid Squares (where it is not possible to place stacks)
void set_invalid(square * s){
    s->type = INVALID;
    s->stack = NULL;
    s->num_pieces = 0;
}

//Set Empty Squares (with no pieces/stacks)
void set_empty(square * s){
    s->type = VALID;
    s->stack = NULL;
    s->num_pieces = 0;
}

//Set squares  with a GREEN piece
void set_green(square * s){
    s->type = VALID;
    s->stack = (piece *) malloc (sizeof(piece));
    s->stack->p_colour = GREEN;
    s->stack->next = NULL;
    s->num_pieces = 1;
}

//Set squares with a RED piece
void set_red(square * s){
    s->type = VALID;
    s->stack = (piece *) malloc (sizeof(piece));
    s->stack->p_colour = RED;
    s->stack->next = NULL;
    s->num_pieces = 1;
}

//initializes the board
void initialize_board(square board [BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]){
    for(int i=1; i< BOARD_SIZE; i++){
        for(int j=1; j< BOARD_SIZE; j++){

            //invalid squares
            if((i==1 && (j==1 || j==2 || j==7 || j==8)) ||
               (i==2 && (j==1 || j==8)) ||
               (i==7 && (j==1 || j==8)) ||
               (i==8 && (j==1 || j==2 || j==7 || j==8)))
                set_invalid(&board[i][j]);

            else{
                //squares with no pieces
                if(i==1 || i ==8 || j==1 || j == 8) {
                    set_empty(&board[i][j]);
                }
                else{
                    //squares with red pieces
                    if((i % 2 == 0 && (j < 4 || j > 5)) ||
                       (i % 2 == 1 && (j == 4 || j==5))) {
                        set_red(&board[i][j]);
                    }
                        //green squares
                    else set_green(&board[i][j]);
                }
            }
        }
    }
}