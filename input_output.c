#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "input_output.h"

/* All Inputs in turn() and move() have bool loops to check for valid user inputs
 * A Valid User Input should be an integer within range of the values that they should be in and
 *
 * turn() will acquire the target position and check if its a square the player can interact with
 * then turn() will call move() which will ask the player for how they want to move their stack (direction and number of spaces),  then check if its a legal move, then call Capture() which executes the move and updates the board
 */


/* fgets(input, 10, stdin);
 * varaible = strtol(input, NULL, 10);
 * ^^That is the standard Error Checking that'll exist in all uiser inputs here
 */
void print_stack(piece *stack);
void move(square board[BOARD_SIZE][BOARD_SIZE], int y, int x, player players[PLAYERS_NUM]);


void turn(square board[BOARD_SIZE][BOARD_SIZE], int starting_colour, player players[PLAYERS_NUM]){

    char input[10];//Temporary input for error checking
    int choice = 1;//To see if player wants to move a stack, or use a supply
    long int x, y;//To hold Target Coordinates

    //All bools that keep input loops going until a valid input is given
    bool valid_x = false;
    bool valid_y = false;
    bool valid_pos = false;
    bool valid_choice = false;


    //If the current player has the option to use a supply, then ask him
    if (players[starting_colour].num_own > 0) {
        while (!valid_choice) {
            printf("\nMove a Stack or Use a Supply\n1. Stack\n2. Supply\n");
            fgets(input, 10, stdin);
            choice = strtol(input, NULL, 10);

            if (choice >= 1 && choice <= 2) {
                valid_choice = true;
            }
        }
    }

    //Checking for Valid and Legal Position
    while (!valid_pos) {

        //Output information for Stack or Supply
        if (choice == 1) {
            printf("Name the position you want to move: ");
        } else
            printf("Name the position you want to put the supply on: ");


        //Checking for valid x
        valid_x = false;
        while (!valid_x) {

            printf("\nX: ");
            fgets(input, 10, stdin);
            x = strtol(input, NULL, 10);

            if (x >= 1 && x <= 8) {
                valid_x = true;
            } else
                printf("\nEnter a valid coordinate\n");
        }


        //Checking for Valid Y
        valid_y = false;
        while (!valid_y) {

            printf("\nY: ");
            fgets(input, 10, stdin);
            y = strtol(input, NULL, 10);

            if (y >= 1 && y <= 8) {
                valid_y = true;
            } else
                printf("\nEnter a valid coordinate\n");
        }


        //If Player wants to move a stack, check if a piece is there and if its belongs to them,  else if they want to move a supply, check if square is valid
        if (choice == 1) {

            if (board[y][x].type == VALID && board[y][x].num_pieces != 0) {

                //Have to have second if statement for colour because memory crashes  (trying to access memory that doesn't exist so
                //num_pieces check first to see if it even is a piece and not some empty thing)
                if (board[y][x].stack->p_colour == starting_colour) {
                    valid_pos = true;

                } else {
                    printf("Enter a valid position\n\n");

                }
            } else {
                printf("Enter a valid position\n\n");

            }
        } else {

            if (board[y][x].type == VALID){
                valid_pos = true;

            } else
                printf("Enter a valid position\n\n");
        }
    }//End of valid_pos


    //When here, Target position is a valid square that the player can interact with


    if (choice == 1) {
        move(board, y, x, players);

    } else {
        supply(&board[y][x], players, starting_colour);

        printf("\nTarget Position Stack: ");
        print_stack(board[y][x].stack);
    }
}


//Carries on from line 120
void move(square board[BOARD_SIZE][BOARD_SIZE], int y, int x, player players[PLAYERS_NUM]) {

    char input[10];//Temporary input for error checking
    bool main_valid = false;//To loop the move function is the move selected is legal so player can try to input a move again
    long int direction;//Int to remember direction
    int num_spaces;//Num of spaces player wants to move

    unsigned int delta;//variable to contain the target x or y coordinate that the player wants to move to
    //And also the original original position of x and y needs to be retained so a seperate variable for the new target pos is needed



    while (!main_valid) {


        //To get Number Direction From Player
        bool valid_direc = false;

        while (!valid_direc) {
            printf("\nSelect Direction:\n");

            printf("1. North\n");
            printf("2. South\n");
            printf("3. East\n");
            printf("4. West\n");

            fgets(input, 10, stdin);
            direction = strtol(input, NULL, 10);

            if (direction >= 1 && direction <= 4) {
                valid_direc = true;
            } else {
                printf("Enter a Valid Direction\n\n");
            }
        }




        //To Get the number of spaces from player
        bool valid_space = false;//To check for valid moves

        while (!valid_space) {

            printf("How many Spaces Do You Want To Move: \n");

            //Depending on how many pieces are in the stack, give player a choice between 1 and board[y][x].numpieces
            printf("Choice: ");
            for (int i = 1; i < board[y][x].num_pieces+1;i++){
                printf("%d\t", i);
            }
            printf("\n");

            //Error-Checking Input
            fgets(input, 10, stdin);
            num_spaces = strtol(input, NULL, 10);

            //If it is a valid number that resides in the num of pieces you can move then exit the loop and move onto Illegal Move Checking
            if (num_spaces >= 1 && num_spaces <= board[y][x].num_pieces){
                valid_space = true;
            } else {
                printf("\nInvalid Input\n");
            }
        }//End of While Loop that gets the num_spaces the player wants to move




        //This is to check if the move in question is a legal move
        switch (direction) {

            case 1:
                //This bit is to change give delta the value of the target position even if the player wants to teleport from the extreme North to extreme South
                if (y - num_spaces < 1) {
                    delta = 8 + (y - num_spaces);
                } else {
                    delta = y - num_spaces;
                }

                if (board[delta][x].type != VALID) {
                    printf("Illegal Move");

                } else {

                    main_valid = true;
                }
                break;

            case 2:
                //This bit is to change give delta the value of the target position even if the player wants to teleport from the extreme South to extreme North
                if (y + num_spaces > 8) {
                    delta = (y + num_spaces) - 8;
                } else {
                    delta = y + num_spaces;
                }

                if (board[delta][x].type != VALID) {
                    printf("Illegal Move");

                } else {

                    main_valid = true;
                }
                break;

            case 3:
                //This bit is to change give delta the value of the target position even if the player wants to teleport from the extreme East to extreme West
                if (x + num_spaces > 8) {
                    delta = (x + num_spaces) - 8;
                } else {
                    delta = x + num_spaces;
                }

                if (board[y][delta].type != VALID) {
                    printf("Illegal Move");

                } else {

                    main_valid = true;
                }
                break;

            case 4:
                //This bit is to change give delta the value of the target position even if the player wants to teleport from the extreme West to extreme East
                if (x - num_spaces < 1) {
                    delta = 8 + (x - num_spaces);
                } else {
                    delta = x - num_spaces;
                }

                if (board[y][delta].type != VALID) {
                    printf("Illegal Move");

                } else {

                    main_valid = true;
                }
                break;

        }//End of switch direc
    }//End of while (!main_valid)






    //End of All Move Checking,  if code reaches here, it is a valid and legal Move






    //Calling Capture() which will execute the move and update the board
    if (direction == 1 || direction == 2) {
        Capture(&board[y][x], &board[delta][x], num_spaces, players);


        //Print out the updated Target and Origin Stacks
        printf("Original Position Stack: ");
        print_stack(board[y][x].stack);

        printf("\nTarget Position Stack: ");
        print_stack(board[delta][x].stack);

    }
    else if (direction == 3 || direction == 4){
        Capture(&board[y][x], &board[y][delta], num_spaces, players);


        //Print out the updated Target and Origin Stacks
        printf("Original Position Stack: ");
        print_stack(board[y][x].stack);

        printf("\nTarget Position Stack: ");
        print_stack(board[y][delta].stack);
    }
}






/* Function to print the board:
 * Invalid Squares are printed as | -- |
 * Valid empty squares are printed as |    |
 * Valid squares with a GREEN piece are printed as | %dG |
 * Valid squares with a RED piece are printed as | %dR | */
void print_board(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]){
    printf("\n*************** The Board ***************\n");

    printf("      ");
    for (int i = 1;i < BOARD_SIZE; i ++){
        printf("%d    ", i);
    }
    printf("\n");
    for(int i = 1; i < BOARD_SIZE; i ++){
        printf("%d  ", i);
        for (int j = 1; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)
                    printf("|    ");
                else{
                    if (board[i][j].stack->p_colour == GREEN)
                        printf("| %dG ", board[i][j].num_pieces);
                    else if(board[i][j].stack->p_colour == RED){
                        printf("| %dR ", board[i][j].num_pieces);
                    }
                }
            }
            else
                printf("| -- ");
        }
        printf("|\n");
    }

    printf("Red_own: %d\tRed_captured: %d\nGreen_own: %d\tGreen_captured: %d\n", players[0].num_own,
           players[0].num_captured, players[1].num_own, players[1].num_captured);
}



/* Prints the stack out like
 * colour-->colour-->Bottom
 */
void print_stack(piece *stack){

    while (stack != NULL){

        if (stack->p_colour == RED){
            printf("Red-->");
        }
        else if (stack->p_colour == GREEN){
            printf("Green-->");
        }
        stack = stack->next;
    }
    printf("Bottom");
}