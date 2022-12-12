#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "logic.h"
#include "board.h"

game* new_game(unsigned int square, unsigned int maglock, unsigned int width,
               unsigned int height, enum type type) {
    
    if ((square * square) >= (height * width)) {
        fprintf(stderr, "square too large for game board");
        exit(1);
    }
    game* res = (game *) malloc(sizeof(game));
    board* b = board_new(width, height, type);
    res->square = square;
    res->maglock = maglock;
    res->black_rem = 0;
    res->white_rem = 0;
    res->b = b;
    res->player = BLACKS_TURN;
    
    return res;
}


void game_free(game* g) {
    board_free(g->b);
    free(g);
}


void gravity (game* g, pos position) {
    pos original = position;
    cell color = board_get(g->b, position);
    
    if (((color == WHITE) && (g->white_rem > 0)) ||
        ((color == BLACK) && (g->black_rem > 0))) {
        return;
    }
        
    for (unsigned int i = position.r; i < g->b->height; i++) {
        position.r = i + 1;
        
        if (i + 1 >= g->b->height) {
            position.r = i;
            board_set(g->b, original, EMPTY);
            board_set(g->b, position, color);
            break;
        }
        else if (board_get(g->b, position) != EMPTY) {
            position.r = i;
            board_set(g->b, original, EMPTY);
            board_set(g->b, position, color);
            break;
        }
    }
}

void gravitize_board(game* g) {
    for (int i = g->b->height - 1; i >= 0; i--) {
        for (int j = 0; j < g->b->width; j++) {
            pos position;
            position.r = i;
            position.c = j;
            if (board_get(g->b, position) != EMPTY) {
                gravity(g, position);
            }
        }
    }
}

void manage_turn(game* g) {
   
    if (g->player == WHITES_TURN) {
        if (g->black_rem == 0) {
            g->player = BLACKS_TURN;
            gravitize_board(g);
        }
        else {
            g->black_rem--;
            gravitize_board(g);
        }
    }
    else {
        if (g->white_rem == 0) {
            g->player = WHITES_TURN;
            gravitize_board(g);
        }
        else {
            g->white_rem--;
            gravitize_board(g);
        }
    }
}

bool drop_piece(game* g, unsigned int column) {
   
    pos position;
    position.r = 0;
    position.c = column;

    if ((board_get(g->b, position) != EMPTY) || (column < 0) || (column > g->b->height)) {
        printf("Illegal move, try again\n");
        return false;   
    }
    cell color;
    if (g->player == WHITES_TURN) {
        color = WHITE;
    }

    else {
        color = BLACK;
    }

    board_set(g->b, position, color);
    gravity(g, position);
    manage_turn(g);
 
    return true;
}

    
void mag_black(game* g, pos position) {
    
    pos original = position;
    for (unsigned int i = position.c; i >= 0; i--) {
        position.c = i - 1;
        if (i == 0) {
            position.c = 0;
            board_set(g->b, original, EMPTY);
            board_set(g->b, position, BLACK);
            break;
        }
        if (board_get(g->b, position) != EMPTY) {
            position.c = i;
            board_set(g->b, original, EMPTY);
            board_set(g->b, position, BLACK);
            break;
        }
    }
}    

void mag_white(game* g, pos position) {

    pos original = position;
    for (unsigned int i = position.c; i < g->b->width; i++) {
        position.c = i + 1;
        if (i + 1 == g->b->width) {
            position.c = i;
            board_set(g->b, original, EMPTY);
            board_set(g->b, position, WHITE);
            break;
        }
        if (board_get(g->b, position) != EMPTY) {
            position.c = i;
            board_set(g->b, original, EMPTY);
            board_set(g->b, position, WHITE);
            break;
        }
    }
}

void magnetize_board(game* g) {
    if (g->player == BLACKS_TURN) {
        for (unsigned int i = 0; i < g->b->height; i++) {
            for (unsigned int j = 0; j < g->b->width; j++) {
                pos position;
                position.c = j;
                position.r = i;
                if (board_get(g->b, position) == BLACK) {
                    mag_black(g, position);
                } 
            }
        }
    }
    
    else {
        for (int i = 0; i < g->b->height; i++) {
            for (int j = g->b->width - 1; j >= 0; j--) {
                pos position;
                position.c = j;
                position.r = i;
                if (board_get(g->b, position) == WHITE) {
                    mag_white(g, position);
                }
            }
        }
    }
}


cell** matrix_copy(cell** matrix, unsigned int width, unsigned int height) {
    cell** copy = (cell **) malloc (height * sizeof(cell*));
    for (unsigned int i = 0; i < height; i++) {
        cell* row = (cell *) malloc (width * sizeof(cell));
        for (unsigned int j = 0; j < width; j++) {
            row[j] = matrix[i][j];
        }
        copy[i] = row;
    }
    return copy;
}
        
bool matrix_cmp(cell** matrix1, cell** matrix2, unsigned int width, unsigned int height) {
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

unsigned int* arr_copy(game* g) {
    unsigned int len = (g->b->height * g->b->width) / 16 + 1;
    unsigned int* copy = (unsigned int*) malloc(len * sizeof(unsigned int));
    for (unsigned int i = 0; i < len; i++) {
        copy[i] = g->b->u.bits[i];
    }
    return copy;
}

bool arr_cmp(game* g, unsigned int* copy) {
    unsigned int len = (g->b->height * g->b->width) / 16 + 1;
    for (unsigned int i = 0; i < len + 1; i++) {
        if (g->b->u.bits[i] != copy[i]) {
            return false;
        }
    }
    return true;
}


bool magnetize(game* g) {

    if (((g->black_rem > 0) && (g->player == BLACKS_TURN)) ||
        ((g->white_rem > 0) && (g->player == WHITES_TURN))) {
        return false;
    }
    
    if (g->player == BLACKS_TURN) {
        g->black_rem = g->maglock;
    }
    
    else {
        g->white_rem = g->maglock;
    } 
    
    if (g->b->type == MATRIX) {
        cell** holder_matrix = matrix_copy(g->b->u.matrix, g->b->width, g->b->height);
        
        magnetize_board(g);
        while (! (matrix_cmp(g->b->u.matrix, holder_matrix, g->b->width, g->b->height))) {
            holder_matrix = matrix_copy(g->b->u.matrix, g->b->width, g->b->height);
            gravitize_board(g);
            magnetize_board(g);
        }
    }
    else {
        unsigned int* copy = arr_copy(g);
        magnetize_board(g);
        while (! arr_cmp(g, copy)) {
            copy = arr_copy(g);
            gravitize_board(g);
            magnetize_board(g);
        }
    }
            
    switch(g->player) {
        case BLACKS_TURN:
            g->player = WHITES_TURN;
            break;
        case WHITES_TURN:
            g->player = BLACKS_TURN;
            break;
    }
    return true;
}

outcome game_outcome(game* g) {
    
    outcome res; 
    bool white_win = false;
    bool black_win = false;
    unsigned int count_white = 0;
    unsigned int count_black = 0;
    pos p;

    for (unsigned int i = 0; i <= g->b->height - g->square; i++) {
        for (unsigned int j = 0; j <= g->b->width - g->square; j++) {
            count_white = 0;
            count_black = 0;
            for (unsigned int k = 0; k < g->square; k++) {
                for (unsigned int l = 0; l < g->square; l++) {
                    p.r = i + k;
                    p.c = j + l;
                    if (board_get(g->b, p) == WHITE) {
                        count_white ++;
                    }
                    if (board_get(g->b, p) == BLACK) {
                        count_black ++;
                    }
                }
            }
            if (count_white == (g->square * g->square)) {
                white_win = true;
            }
            if (count_black == (g->square * g->square)) {
                black_win = true;
            }
        }
    }
    count_white = 0;
    count_black = 0;
    
    for (unsigned int i = 0; i < g->b->height; i++) {
        for (unsigned int j = 0; j < g->b->width; j++) {
            p.r = i;
            p.c = j;
            if (board_get(g->b, p) == WHITE) {
                count_white ++;
            }
            if (board_get(g->b, p) == BLACK) {
                count_black ++;
            }
        }
    }
    
    if (white_win && black_win) {
        res = DRAW;
    }
    else if (white_win) {
        res = WHITE_WIN;
    }
    else if (black_win) {
        res = BLACK_WIN;
    }
    else if ((count_white + count_black) == (g->b->width * g->b->height)) {
        res = DRAW;
    }
    else {
        res = IN_PROGRESS;
    }
    return res;
}



        




