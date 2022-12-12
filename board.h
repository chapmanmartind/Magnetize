#ifndef BOARD_H
#define BOARD_H

#include "pos.h"

enum cell {
    EMPTY,
    BLACK,
    WHITE
};

typedef enum cell cell;


union board_rep {
    enum cell** matrix;
    unsigned int* bits;
};

typedef union board_rep board_rep;


enum type {
    MATRIX, BITS
};


struct board {
    unsigned int width, height;
    enum type type;
    board_rep u;
};

typedef struct board board;

/* returns an empty board */
board* board_new(unsigned int width, unsigned int height, enum type type);

/* frees the memory allocated to the board */
void board_free(board* b);

/* prints the board */
void board_show(board* b);

/* returns a given cell at a position on the board */
cell board_get(board* b, pos p);

/* sets a certain position on the board to a cell */
void board_set(board* b, pos p, cell c);

#endif /* BOARD_H */
