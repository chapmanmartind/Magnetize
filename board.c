#include "pos.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

board* board_new(unsigned int width, unsigned int height, enum type type) {
    if (type == BITS) {
        unsigned int size;
        if (((width * height) % 16) == 0) {
            size = (width * height) / 16;
        }
        else {
            size = ((width * height) / 16) + 1;
        }
        
        unsigned int* new_board = (unsigned int *) malloc(size * sizeof (unsigned int));
        if (new_board == NULL) {
            fprintf(stderr, "Memory error, please restart the game");
            exit(1);
        }
        for (unsigned int i = 0; i < size; i ++) {
            new_board[i] = 0;
        }
        board* res = (board *) malloc(sizeof (board));
        if (res == NULL) {
            fprintf(stderr, "Memory error, please restart the game");
            exit(1);
        }
        res->u.bits = new_board;
        res->width = width;
        res->height = height;
        res->type = type;
        return res;
    }
    else { 
        cell** new_board = (cell **) malloc (height * sizeof(cell*));
        if (new_board == NULL) {
            fprintf(stderr, "Memory error, please restart the game");
            exit(1);
        }

        for (unsigned int i = 0; i < height; i++) {
            cell* row = (cell *) malloc (width * sizeof(cell));
            for (unsigned int j = 0; j < width; j++) {
                cell single;
                single = EMPTY;
                row[j] = single;
            }
            new_board[i] = row;
        }
        board* res = (board *) malloc(sizeof(board));
        if (res == NULL) {
            fprintf(stderr, "Memory error, please restart the game");
            exit(1);
        }
        res->u.matrix = new_board;
        res->width = width;
        res->height = height;
        res->type = type;
        return res;
    }
}
        
void board_free(board* b) {
    if (b->type == BITS) {
        free(b->u.bits);
        free(b);
    }
    else {
        free(b->u.matrix);
        free(b);
    }
 }

void print_char(cell c) {
    if (c == EMPTY) {
        printf("%c", '.');
    }
    else if (c == BLACK) {
        printf("%c", '*');
    }
    else {
        printf("%c", 'o');
    }
}

void print_top(board* b) {
    
    char header[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    printf("  ");
    
    for (unsigned int i = 0; i< b->width; i++) {
        if (i < strlen(header)) {
            printf("%c", header[i]);
        }
        else {
            printf("?");
        }
    }
    printf("\n");
    printf("  ");
    
    for (unsigned int i = 0; i< b->width; i++) {
        printf(" ");
    }
    printf("\n");
}

void board_show(board* b) {
    
    char header[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    print_top(b);
    
    for (unsigned int i = 0; i< b->height; i++) { 
        for (unsigned int j = 0; j< b->width + 2; j++) {
            if (j == 0) {
                if (i < strlen(header)) {
                    printf("%c", header[i]);
                }
                else {
                    printf("?");
                }
            }
            else if (j == 1) {
                printf(" ");
            }
            else {
                pos p;
                p.r = i;
                p.c = j - 2;
                print_char(board_get(b, p));
            }
        }
        printf("\n");
    }
    printf("\n");
}
       
cell board_get(board* b, pos p) {
    if ((p.r > b->width) || (p.r < 0) || (p.c > b->height) || (p.c < 0)) {
        fprintf(stderr, "out of bounds");
        exit(1);
    }
    
    if (b->type == BITS) {
        unsigned int square = p.r * b->width + p.c;
        unsigned int section = square / 16;
        square = square % 16;
        unsigned int value = b->u.bits[section];
        unsigned int shifted = (value >> (2 * square)) & 3;
        if (shifted == 0) {
            return EMPTY;
        }
        else if (shifted == 1) {
            return BLACK;
        }
        else {
            return WHITE;
        }
    }
    return(b->u.matrix[p.r][p.c]);
}

void board_set(board* b, pos p, cell c) {
    if ((p.r > b->width) || (p.r < 0) || (p.c > b->height) || (p.c < 0)) {
        fprintf(stderr, "out of bounds");
        exit(1);
    }
    if (b->type == BITS) {
        unsigned int add = 0;
        if (c == BLACK) {
            add = 1;
        }
        if (c == WHITE) {
            add = 2;
        }
           
        unsigned int square = p.r * b->width + p.c;
        unsigned int section = square / 16;
        square = square % 16;
        unsigned int value = b->u.bits[section];
        unsigned int mask = ~(3 << (2 * square));
        value = value & mask;
        add = add << (2 * square);
        value = (value | add);
        b->u.bits[section] = value;        
    }
    else { 
        b->u.matrix[p.r][p.c] = c;
    }
}    






 
        















                        
        
    


















    
