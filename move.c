#include <stdlib.h>
#include "move.h"

#define MAX_STACK_SIZE 5

//Remove() Goes to the 5th piece in the stack and increments players[0 or 1].num.own and num.captured according to whos turn it it and frees the piece accordingly
void Remove(square *Target_Ptr, player players[PLAYERS_NUM]);

//points the pointers to the right places and if the updated Target Stack greater than MAX_STACK_SIZE then call Remove()
void Capture (square * Origin_Ptr, square * Target_Ptr, int num_spaces, player players[PLAYERS_NUM]) {
    //Pointers to go through Linked lists
    piece *target = Target_Ptr->stack;
    piece *origin = Origin_Ptr->stack;

    //Going through origin until origin is still in stack and origin->next on the NULL candidate
    for (int i = 1; i<num_spaces; i++) {
        origin = origin->next;
    }

    //Next 6 lines is just placing origin stack on top of target stack
    //Changing Target pointer to point to Original position Stack
    Target_Ptr->stack = Origin_Ptr->stack;
    //Original position stack_head is now pointing lower in the stack
    Origin_Ptr->stack = origin->next;
    //The bottom of target stack will now point to th e top of the old target stack
    origin->next = target;


    //If moving entire stack then set the original position to null
    if (Origin_Ptr->num_pieces == num_spaces) {
        Origin_Ptr->stack = NULL;
    }

    //Changing the appropriate amount of num_pieces for both Target and Origin
    Target_Ptr->num_pieces = Target_Ptr->num_pieces + num_spaces;
    Origin_Ptr->num_pieces = Origin_Ptr->num_pieces - num_spaces;



    //If the Updated Target stack is greater than MAX_STACK_SIZE then call Remove() function
    if (Target_Ptr->num_pieces > MAX_STACK_SIZE) {

        Remove(Target_Ptr, players);

    }//End of Target_Ptr->num_pieces > MAX_STACK_SIZE  (5)


}




//Using a player's supply to put a piece anywhere on the board
void supply(square *Target_Ptr, player players[PLAYERS_NUM], int colour){


    //Allocating Space for New Piece and giving it the colour of the current player
    piece *supply = malloc(sizeof(piece));
    supply->p_colour = colour;

    //Putting on top of the Target Stack
    supply->next = Target_Ptr->stack;
    //Making TargetPtr point to the new top of the stack
    Target_Ptr->stack = supply;
    //Increasing the num_pieces by 1
    Target_Ptr->num_pieces++;
    //Decrementing the number of supply for the current player
    players[colour].num_own--;

    //If the updated stack is larger than MAX_STACK_SIZE call Remove()
    if (Target_Ptr->num_pieces > MAX_STACK_SIZE){
        Remove(Target_Ptr, players);
    }
}

/*
 * If the capturer is red, a red piece would add to the supply and a green piece would add to num_captured, expelling that piece from the game forever
 * and vice versa
 */

void Remove(square *Target_Ptr, player players[PLAYERS_NUM]) {
    //Pointers to go through Linked Lists and a temp to hold a pointer before freeing it
    piece *target = Target_Ptr->stack;
    piece *temp;

    //Going through stack until target is on the Null Candidate and next is deeper into the stack that needs to be freed
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        target = target->next;
    }

    //If statement to increment num_own and num_captured based on whos capturing who
    if (Target_Ptr->stack->p_colour == RED) {

        while (target != NULL) {

            if (target->p_colour == RED) {
                players[0].num_own++;
            } else if (target->p_colour == GREEN) {
                players[0].num_captured++;
            }

            //temp hold current piece in the stack, then free it after target has moved onto the next one in the stack,  when freed one piece, decrement one piece from Target
            temp = target;
            target = target->next;
            free(temp);
            Target_Ptr->num_pieces--;
        }
    } else if (Target_Ptr->stack->p_colour == GREEN) {

        while (target != NULL) {

            if (target->p_colour == RED) {
                players[1].num_captured++;
            } else if (target->p_colour == GREEN) {
                players[1].num_own++;
            }

            //temp hold current piece in the stack, then free it after target has moved onto the next one in the stack,  when freed one piece, decrement one piece from Target
            temp = target;
            target = target->next;
            free(temp);
            Target_Ptr->num_pieces--;
        }
    }


    /*Cutting off stack at 5 because target->next needs to be explicitly told that the next one is the end since free still leaves the pointer*/
    //Go back to the start then move through stack until target->next is on the NULL candidate.
    target = Target_Ptr->stack;
    for (int i = 1; i < MAX_STACK_SIZE; i++) {
        target = target->next;
    }
    target->next = NULL;

}