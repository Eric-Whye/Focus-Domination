#ifndef FOCUS_INPUT_OUTPUT_H
#define FOCUS_INPUT_OUTPUT_H

#endif //FOCUS_INPUT_OUTPUT_H


#include "move.h"

//The function to print the board
void print_board(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]);
void turn(square board[BOARD_SIZE][BOARD_SIZE], int starting_colour, player players[PLAYERS_NUM]);