#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include "board.h"


enum turn {
    BLACKS_TURN,
    WHITES_TURN
};

typedef enum turn turn;


enum outcome {
    IN_PROGRESS,
    BLACK_WIN,
    WHITE_WIN,
    DRAW
};

typedef enum outcome outcome;


struct game {
    unsigned int square, maglock, black_rem, white_rem;
    board* b;
    turn player;
};

typedef struct game game;

//creates a new game//
game* new_game(unsigned int square, unsigned int maglock, unsigned int width,
               unsigned int height, enum type type);

//frees a game//
void game_free(game* g);

//turns on gravity//
void gravity(game* g, pos position);

//applies gravity to the board//
void gravitize_board(game* g);

//manages the turn//
void manage_turn(game* g);

//drops a piece//
bool drop_piece(game* g, unsigned int column);

//magnetizes black pieces//
void mag_black(game* g, pos position);

//magnetizes white pieces//
void mag_white(game* g, pos position);

//magnetizes the entire board//
void magnetize_board(game* g);

//copies a matrix//
cell** matrix_copy(cell** matrix, unsigned int width, unsigned int height);

//compares two matrices
bool matrix_cmp(cell** matrix1, cell** matrix2, unsigned int width, unsigned int height);

//copies an array 
unsigned int* arr_copy(game* g);

//compares two matrices
bool arr_cmp(game* g, unsigned int* copy);

//magnetizes the board//
bool magnetize(game* g);

//returns the outcome of the game//
outcome game_outcome(game* g);

#endif /* LOGIC_H */
