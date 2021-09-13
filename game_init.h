#ifndef FOCUS_GAME_INIT_H
#define FOCUS_GAME_INIT_H

#endif //FOCUS_GAME_INIT_H

#include <time.h>
#define BOARD_SIZE 8+1
#define PLAYERS_NUM 2

//colours that a piece can have
typedef enum PieceColours {
    RED,
    GREEN
}colour;

// Square types
//INVALID: squares that are on the sides and where no piece can be placed
//VALID: squares where it is possible to place a piece or a stack
typedef enum square_type {
    VALID,
    INVALID
}square_type;

//Player
typedef struct player{
    //the color associated with the player
    colour player_colour;

    char name[20];

    int num_captured;

    //The supply that each player has
    int num_own;
    /*
     * A player should also be characterized by:
     * name,
     * number of adversary's pieces captured,
     * number of own pieces kept.
     *
    */
}player;

// A piece
typedef struct piece {
    //the color associated with a piece
    colour p_colour;

    // This is a pointer to the next pieces
    struct piece * next;

}piece;

// A Square of the board
typedef struct square {
    // type of the square (VALID/INVALID)
    square_type type;

    //the piece or the bottom on the stack
    piece * stack;

    //number of pieces on the square
    int num_pieces;

}square;

//Function to create the players
void initialize_players(player players[PLAYERS_NUM]);

//Function to create the board
void initialize_board(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]);

//To be used in move.c
void set_empty(square *s);

void set_green(square *s);

void set_red(square *s);